//! SSRF URL policy for browser navigation.
//!
//! `UrlPolicy` is a lightweight, pure-function guard that classifies a
//! navigation target as **allowed** or **blocked** before it is handed to a
//! browser driver. Parsing goes through the WHATWG URL parser (the `url`
//! crate), so alternate IPv4 encodings — decimal (`2130706433`), hex
//! (`0x7f000001`), octal (`0177.0.0.1`) and short-form (`127.1`) — plus IPv6
//! literals are normalized to a real `IpAddr` before the private-range check,
//! and trailing-dot hostnames (`localhost.`) are handled. There are no DNS
//! lookups, so DNS-rebind attacks are out of scope and documented as future
//! work.
//!
//! ## Modes
//!
//! | Constructor | Behaviour |
//! |---|---|
//! | `UrlPolicy::allow_all()` | Passes every URL through unchanged (backwards-compatible default). |
//! | `UrlPolicy::block_private()` | Blocks non-`http`/`https` schemes, loopback, RFC 1918 private, link-local (169.254.x.x / fe80::), and cloud-metadata addresses. |
//!
//! ## Wiring
//!
//! The policy type lives in the core `beater-browser` crate so every driver
//! backend (`beater-browser-cdp`, `beater-browser-playwright`,
//! `beater-browser-webdriver`) can import it without pulling in store or API
//! dependencies. Every real driver enforces the guard on the live navigation
//! path: each `goto` implementation calls `self.policy.enforce(url)?` before
//! issuing the real CDP/WebDriver/Playwright navigate command, and the real
//! drivers default to [`UrlPolicy::block_private`] (secure by default — pass
//! [`UrlPolicy::allow_all`] via their `with_policy` builders for trusted
//! callers or local fixtures).
//!
//! `MockDriver` accepts an optional `UrlPolicy` via
//! [`crate::MockDriver::with_policy`] so tests can exercise policy enforcement
//! without a real browser.
//!
//! ## Future work
//!
//! - DNS-rebind mitigation: resolve the hostname and re-check the resulting IP
//!   after navigation, or use a DNS-over-HTTPS resolver before launch.
//! - Per-tenant allowlist: extend `UrlPolicy` with an explicit `Vec<String>`
//!   allowlist of domains that bypass the block list.
//! - CIDR-based allowlist: allow callers to opt specific private ranges back in
//!   (e.g. an on-prem app running on 192.168.x.x).

use std::net::{IpAddr, Ipv4Addr};

use url::Url;

use crate::BrowserError;

/// Decides whether a navigation target URL may be visited.
///
/// Construct with [`UrlPolicy::allow_all`] (default, back-compat) or
/// [`UrlPolicy::block_private`] (secure default for production use).
#[derive(Clone, Debug)]
pub struct UrlPolicy {
    mode: PolicyMode,
}

#[derive(Clone, Debug, PartialEq, Eq)]
enum PolicyMode {
    /// Every URL is permitted — legacy / test back-compat mode.
    AllowAll,
    /// Block non-http(s) schemes + private/loopback/link-local/metadata hosts.
    BlockPrivate,
}

/// The outcome of a policy check.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum PolicyVerdict {
    /// The URL may be navigated to.
    Allow,
    /// The URL must not be navigated to; the reason string is human-readable.
    Block(String),
}

impl UrlPolicy {
    /// Permit any URL. Use for backwards compatibility or trusted callers.
    pub fn allow_all() -> Self {
        Self {
            mode: PolicyMode::AllowAll,
        }
    }

    /// Block private/loopback/link-local/metadata addresses and non-http(s)
    /// schemes. This is the recommended constructor for production drivers.
    pub fn block_private() -> Self {
        Self {
            mode: PolicyMode::BlockPrivate,
        }
    }

    /// Evaluate `url` against the policy.
    ///
    /// Returns `PolicyVerdict::Allow` when the URL is safe to visit, or
    /// `PolicyVerdict::Block(reason)` when it must be rejected.
    ///
    /// A URL that cannot be parsed is always blocked (fail-closed).
    pub fn check(&self, url: &str) -> PolicyVerdict {
        if self.mode == PolicyMode::AllowAll {
            return PolicyVerdict::Allow;
        }

        // Parse with the WHATWG URL parser (the `url` crate). For the special
        // schemes we permit (`http`/`https`) this normalizes the host for us:
        // decimal (`2130706433`), hex (`0x7f000001`), octal (`0177.0.0.1`), and
        // short-form (`127.1`) IPv4 literals all decode to a real `Ipv4Addr`,
        // and bracketed IPv6 literals to an `Ipv6Addr`. This closes the
        // encoding-bypass holes the previous hand-rolled `split_once("://")`
        // parser missed. A URL that cannot be parsed is blocked (fail-closed).
        let parsed = match Url::parse(url) {
            Ok(parsed) => parsed,
            Err(err) => {
                return PolicyVerdict::Block(format!(
                    "rejected: unparseable URL ({err}): {url}"
                ));
            }
        };

        // --- scheme check (the parser lowercases the scheme) ---
        let scheme = parsed.scheme();
        if scheme != "http" && scheme != "https" {
            return PolicyVerdict::Block(format!(
                "rejected: scheme '{scheme}' is not http or https: {url}"
            ));
        }

        // --- host check ---
        let Some(host) = parsed.host() else {
            return PolicyVerdict::Block(format!("rejected: URL has no host: {url}"));
        };

        match host {
            url::Host::Ipv4(v4) => {
                if let Some(reason) = check_ip_blocked(&IpAddr::V4(v4)) {
                    return PolicyVerdict::Block(format!("rejected: {reason}: {url}"));
                }
            }
            url::Host::Ipv6(v6) => {
                if let Some(reason) = check_ip_blocked(&IpAddr::V6(v6)) {
                    return PolicyVerdict::Block(format!("rejected: {reason}: {url}"));
                }
            }
            url::Host::Domain(domain) => {
                // `url` lowercases and IDNA-encodes the domain. Strip a single
                // trailing dot (`localhost.` / `example.com.`): the root label
                // is equivalent to the dotless form and must not bypass the
                // loopback check.
                let domain = domain.strip_suffix('.').unwrap_or(domain);
                if domain == "localhost" || domain.ends_with(".localhost") {
                    return PolicyVerdict::Block(format!(
                        "rejected: 'localhost' hostname resolves to loopback: {url}"
                    ));
                }
                // Defense in depth: if the parser left an opaque domain that is
                // really a bare integer or non-dotted IPv4 form, normalize it to
                // an `IpAddr` and re-check. (For http/https the parser already
                // does this, so this only fires for hosts it left untouched.)
                if let Some(ip) = normalize_host_to_ip(domain) {
                    if let Some(reason) = check_ip_blocked(&ip) {
                        return PolicyVerdict::Block(format!("rejected: {reason}: {url}"));
                    }
                }
            }
        }

        PolicyVerdict::Allow
    }

    /// Convenience wrapper: returns `Err(BrowserError::SsrfBlocked)` when
    /// `check` would block, or `Ok(())` when the URL is allowed. Suitable for
    /// use inside a driver's `goto` implementation via `policy.enforce(url)?`.
    pub fn enforce(&self, url: &str) -> Result<(), BrowserError> {
        match self.check(url) {
            PolicyVerdict::Allow => Ok(()),
            PolicyVerdict::Block(reason) => Err(BrowserError::SsrfBlocked(reason)),
        }
    }
}

/// Best-effort normalization of a host literal that the URL parser left as an
/// opaque domain into an [`IpAddr`]. Handles a textual IP, a bare decimal
/// integer (`2130706433`), a hex integer (`0x7f000001`), and a leading-zero
/// (octal) 32-bit value. Returns `None` for genuine hostnames.
///
/// This is a backstop: for `http`/`https` URLs the `url` crate already decodes
/// these forms into [`url::Host::Ipv4`], so this only matters if a future
/// caller reaches `check` with a host the parser left intact.
fn normalize_host_to_ip(host: &str) -> Option<IpAddr> {
    // Already a valid textual IP (v4, or a bare v6 without brackets).
    if let Ok(ip) = host.parse::<IpAddr>() {
        return Some(ip);
    }
    if host.is_empty() {
        return None;
    }
    // Bare 32-bit integer forms collapse to an IPv4 address.
    let as_u32 = if let Some(hex) = host.strip_prefix("0x").or_else(|| host.strip_prefix("0X")) {
        u32::from_str_radix(hex, 16).ok()
    } else if host.len() > 1 && host.starts_with('0') && host.bytes().all(|b| b.is_ascii_digit()) {
        // Leading-zero ⇒ octal (e.g. `017700000001`).
        u32::from_str_radix(host, 8).ok()
    } else if host.bytes().all(|b| b.is_ascii_digit()) {
        host.parse::<u32>().ok()
    } else {
        None
    };
    as_u32.map(|n| IpAddr::V4(Ipv4Addr::from(n)))
}

/// Returns `Some(reason)` if the given IP address is in a blocked range, or
/// `None` if it is a routable public address.
fn check_ip_blocked(ip: &IpAddr) -> Option<String> {
    match ip {
        IpAddr::V4(v4) => {
            let octets = v4.octets();
            // 127.0.0.0/8 — loopback
            if octets[0] == 127 {
                return Some(format!("{ip} is a loopback address (127.0.0.0/8)"));
            }
            // 10.0.0.0/8 — RFC 1918 private
            if octets[0] == 10 {
                return Some(format!("{ip} is in RFC 1918 private range (10.0.0.0/8)"));
            }
            // 172.16.0.0/12 — RFC 1918 private (172.16.0.0 – 172.31.255.255)
            if octets[0] == 172 && (octets[1] >= 16 && octets[1] <= 31) {
                return Some(format!(
                    "{ip} is in RFC 1918 private range (172.16.0.0/12)"
                ));
            }
            // 192.168.0.0/16 — RFC 1918 private
            if octets[0] == 192 && octets[1] == 168 {
                return Some(format!(
                    "{ip} is in RFC 1918 private range (192.168.0.0/16)"
                ));
            }
            // 169.254.0.0/16 — link-local / cloud metadata (AWS IMDSv1, GCP, etc.)
            if octets[0] == 169 && octets[1] == 254 {
                return Some(format!(
                    "{ip} is a link-local / cloud-metadata address (169.254.0.0/16)"
                ));
            }
            // 0.0.0.0/8 — "this" network (unspecified)
            if octets[0] == 0 {
                return Some(format!("{ip} is an unspecified address (0.0.0.0/8)"));
            }
            None
        }
        IpAddr::V6(v6) => {
            let segments = v6.segments();
            // ::1 — loopback
            if *v6 == std::net::Ipv6Addr::LOCALHOST {
                return Some(format!("{ip} is the IPv6 loopback address (::1)"));
            }
            // :: — unspecified
            if *v6 == std::net::Ipv6Addr::UNSPECIFIED {
                return Some(format!("{ip} is the IPv6 unspecified address (::)"));
            }
            // fe80::/10 — link-local (first 10 bits = 1111 1110 10)
            // segments[0] in range [0xfe80, 0xfebf]
            if (segments[0] & 0xffc0) == 0xfe80 {
                return Some(format!("{ip} is an IPv6 link-local address (fe80::/10)"));
            }
            // fc00::/7 — unique-local (RFC 4193, analogous to RFC 1918)
            // segments[0] in range [0xfc00, 0xfdff]
            if (segments[0] & 0xfe00) == 0xfc00 {
                return Some(format!(
                    "{ip} is an IPv6 unique-local address (fc00::/7)"
                ));
            }
            // ::ffff:0:0/96 — IPv4-mapped IPv6; re-check the embedded IPv4
            if segments[0] == 0
                && segments[1] == 0
                && segments[2] == 0
                && segments[3] == 0
                && segments[4] == 0
                && segments[5] == 0xffff
            {
                let embedded = v6.to_ipv4_mapped().unwrap_or_else(|| {
                    // Safety: we checked the mapping prefix above; this branch
                    // is unreachable in practice, but avoids unwrap.
                    std::net::Ipv4Addr::new(0, 0, 0, 0)
                });
                if let Some(reason) = check_ip_blocked(&IpAddr::V4(embedded)) {
                    return Some(format!(
                        "{ip} is an IPv4-mapped IPv6 address whose embedded IPv4 is blocked: {reason}"
                    ));
                }
            }
            None
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // ── helper ──────────────────────────────────────────────────────────────

    fn allows(policy: &UrlPolicy, url: &str) {
        assert_eq!(
            policy.check(url),
            PolicyVerdict::Allow,
            "expected ALLOW for {url:?}"
        );
    }

    fn blocks(policy: &UrlPolicy, url: &str) {
        assert!(
            matches!(policy.check(url), PolicyVerdict::Block(_)),
            "expected BLOCK for {url:?}"
        );
    }

    // ── allow_all ───────────────────────────────────────────────────────────

    #[test]
    fn allow_all_passes_everything() {
        let p = UrlPolicy::allow_all();
        // Public HTTPS
        allows(&p, "https://example.com/path?q=1");
        // Loopback — still allowed under allow_all
        allows(&p, "http://127.0.0.1");
        allows(&p, "http://localhost");
        allows(&p, "http://10.0.0.1");
        // Metadata endpoint
        allows(&p, "http://169.254.169.254/latest/meta-data/");
        // Non-http schemes — still allowed under allow_all
        allows(&p, "file:///etc/passwd");
        allows(&p, "gopher://evil.com");
        // Malformed — even unparseable URLs are allowed under allow_all
        allows(&p, "not-a-url");
    }

    // ── block_private: public URLs (allowed) ────────────────────────────────

    #[test]
    fn block_private_allows_public_https() {
        let p = UrlPolicy::block_private();
        allows(&p, "https://example.com");
        allows(&p, "https://example.com/path?q=1#anchor");
        allows(&p, "http://example.com");
        allows(&p, "https://sub.domain.example.com");
    }

    #[test]
    fn block_private_allows_public_ipv4() {
        let p = UrlPolicy::block_private();
        // Publicly-routable IPs
        allows(&p, "https://8.8.8.8");       // Google DNS
        allows(&p, "https://1.1.1.1");       // Cloudflare
        allows(&p, "https://203.0.113.5");   // TEST-NET-3 (documentation range, public)
        allows(&p, "https://198.51.100.1");  // TEST-NET-2 (documentation range, public)
    }

    #[test]
    fn block_private_allows_non_reserved_port() {
        let p = UrlPolicy::block_private();
        allows(&p, "https://example.com:8443/api");
        allows(&p, "http://example.com:3000/");
    }

    // ── block_private: loopback (blocked) ───────────────────────────────────

    #[test]
    fn block_private_blocks_ipv4_loopback() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://127.0.0.1");
        blocks(&p, "http://127.0.0.1:8080/path");
        blocks(&p, "https://127.0.0.1");
        // Entire 127.0.0.0/8
        blocks(&p, "http://127.1.2.3");
        blocks(&p, "http://127.255.255.255");
    }

    #[test]
    fn block_private_blocks_localhost_hostname() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://localhost");
        blocks(&p, "http://localhost:3000");
        blocks(&p, "https://localhost/admin");
        // Subdomains of localhost
        blocks(&p, "http://api.localhost");
        blocks(&p, "http://db.localhost:5432");
    }

    #[test]
    fn block_private_blocks_ipv6_loopback() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://[::1]");
        blocks(&p, "http://[::1]:8080");
        blocks(&p, "https://[::1]/admin");
    }

    // ── block_private: RFC 1918 (blocked) ───────────────────────────────────

    #[test]
    fn block_private_blocks_10_0_0_0_8() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://10.0.0.1");
        blocks(&p, "http://10.10.10.10");
        blocks(&p, "https://10.255.255.255");
        blocks(&p, "http://10.0.0.1:9200/"); // Elasticsearch-style internal
    }

    #[test]
    fn block_private_blocks_172_16_0_0_12() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://172.16.0.1");
        blocks(&p, "http://172.20.0.1");
        blocks(&p, "http://172.31.255.255");
        // Edge: 172.15.x.x is NOT in the range (public)
        allows(&p, "https://172.15.0.1");
        // Edge: 172.32.x.x is NOT in the range (public)
        allows(&p, "https://172.32.0.1");
    }

    #[test]
    fn block_private_blocks_192_168_0_0_16() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://192.168.0.1");
        blocks(&p, "http://192.168.1.1");
        blocks(&p, "https://192.168.255.255");
    }

    // ── block_private: link-local / metadata (blocked) ──────────────────────

    #[test]
    fn block_private_blocks_169_254_link_local_and_metadata() {
        let p = UrlPolicy::block_private();
        // AWS/GCP/Azure IMDS endpoint
        blocks(&p, "http://169.254.169.254");
        blocks(&p, "http://169.254.169.254/latest/meta-data/iam/security-credentials/");
        // Generic 169.254.x.x
        blocks(&p, "http://169.254.0.1");
        blocks(&p, "http://169.254.255.255");
    }

    #[test]
    fn block_private_blocks_ipv6_link_local() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://[fe80::1]");
        blocks(&p, "http://[fe80::1%25eth0]"); // zone-id stripped during host parse
        blocks(&p, "https://[fe80::dead:beef]");
        // fe80::/10 covers up to febf::
        blocks(&p, "http://[fea0::1]");
        blocks(&p, "http://[febf::1]");
        // ff02:: is multicast, not link-local — should be allowed
        // (not in blocked ranges we cover)
    }

    #[test]
    fn block_private_blocks_ipv6_unique_local() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://[fc00::1]");
        blocks(&p, "http://[fd12:3456:789a::1]");
    }

    // ── block_private: non-http(s) schemes (blocked) ────────────────────────

    #[test]
    fn block_private_blocks_file_scheme() {
        let p = UrlPolicy::block_private();
        blocks(&p, "file:///etc/passwd");
        blocks(&p, "file:///C:/Windows/System32/drivers/etc/hosts");
        blocks(&p, "file://localhost/etc/shadow");
    }

    #[test]
    fn block_private_blocks_gopher_and_other_schemes() {
        let p = UrlPolicy::block_private();
        blocks(&p, "gopher://evil.com");
        blocks(&p, "ftp://ftp.example.com/pub");
        blocks(&p, "data:text/html,<h1>xss</h1>");
        blocks(&p, "javascript:alert(1)");
        blocks(&p, "dict://127.0.0.1:11111/");
    }

    // ── block_private: parse failures (blocked, fail-closed) ────────────────

    #[test]
    fn block_private_blocks_unparseable_urls() {
        let p = UrlPolicy::block_private();
        // No scheme at all
        blocks(&p, "not-a-url");
        blocks(&p, "example.com/path");
        blocks(&p, "");
        // Scheme but no host
        blocks(&p, "http://");
    }

    // ── enforce() wrapper ───────────────────────────────────────────────────

    #[test]
    fn enforce_returns_ok_for_allowed_url() {
        let p = UrlPolicy::block_private();
        assert!(p.enforce("https://example.com").is_ok());
    }

    #[test]
    fn enforce_returns_ssrf_blocked_error_for_blocked_url() {
        let p = UrlPolicy::block_private();
        let Err(err) = p.enforce("http://127.0.0.1") else {
            panic!("expected enforce to block loopback");
        };
        assert!(
            matches!(err, BrowserError::SsrfBlocked(_)),
            "expected SsrfBlocked, got: {err:?}"
        );
        // Error message should carry the reason
        let msg = err.to_string();
        assert!(
            msg.contains("127.0.0.1"),
            "error message should mention the blocked address, got: {msg}"
        );
    }

    #[test]
    fn enforce_returns_ssrf_blocked_for_metadata_endpoint() {
        let p = UrlPolicy::block_private();
        let Err(err) = p.enforce("http://169.254.169.254/latest/meta-data/") else {
            panic!("expected enforce to block metadata endpoint");
        };
        assert!(matches!(err, BrowserError::SsrfBlocked(_)));
    }

    // ── IPv4-mapped IPv6 (blocked) ───────────────────────────────────────────

    #[test]
    fn block_private_blocks_ipv4_mapped_ipv6_loopback() {
        let p = UrlPolicy::block_private();
        // ::ffff:127.0.0.1 — IPv4-mapped IPv6 loopback
        blocks(&p, "http://[::ffff:127.0.0.1]");
        blocks(&p, "http://[::ffff:7f00:1]"); // same in hex
    }

    #[test]
    fn block_private_blocks_ipv4_mapped_ipv6_private() {
        let p = UrlPolicy::block_private();
        // ::ffff:10.0.0.1
        blocks(&p, "http://[::ffff:10.0.0.1]");
        // ::ffff:192.168.1.1
        blocks(&p, "http://[::ffff:192.168.1.1]");
        // ::ffff:169.254.169.254
        blocks(&p, "http://[::ffff:169.254.169.254]");
    }

    // ── unspecified addresses (blocked) ─────────────────────────────────────

    #[test]
    fn block_private_blocks_unspecified_addresses() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://0.0.0.0");
        blocks(&p, "http://[::]/");
    }

    // ── case-insensitive scheme / hostname ──────────────────────────────────

    #[test]
    fn block_private_is_case_insensitive_for_scheme() {
        let p = UrlPolicy::block_private();
        // Uppercase scheme must still be blocked
        blocks(&p, "FILE:///etc/passwd");
        blocks(&p, "FTP://ftp.example.com");
        // HTTPS (uppercase) is allowed
        allows(&p, "HTTPS://example.com");
        allows(&p, "HTTP://example.com");
    }

    #[test]
    fn block_private_is_case_insensitive_for_localhost() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://LOCALHOST");
        blocks(&p, "http://Localhost:8080");
        blocks(&p, "http://LOCALHOST/admin");
    }

    // ── encoded-IPv4 bypass vectors (blocked) ───────────────────────────────
    //
    // The old hand-rolled `split_once("://")` parser only recognized
    // dotted-quad literals, so these alternate encodings of 127.0.0.1 /
    // 10.0.0.1 / 169.254.169.254 sailed straight past the loopback/private
    // checks. The `url` crate normalizes them to a real `Ipv4Addr` first.

    #[test]
    fn block_private_blocks_decimal_ipv4_loopback() {
        let p = UrlPolicy::block_private();
        // 2130706433 == 0x7F000001 == 127.0.0.1
        blocks(&p, "http://2130706433");
        blocks(&p, "http://2130706433:8080/path");
    }

    #[test]
    fn block_private_blocks_hex_ipv4_loopback() {
        let p = UrlPolicy::block_private();
        // 0x7f000001 == 127.0.0.1
        blocks(&p, "http://0x7f000001");
        blocks(&p, "http://0x7F000001/admin");
    }

    #[test]
    fn block_private_blocks_octal_ipv4_loopback() {
        let p = UrlPolicy::block_private();
        // 0177.0.0.1 == 127.0.0.1 (octal first octet)
        blocks(&p, "http://0177.0.0.1");
    }

    #[test]
    fn block_private_blocks_short_form_ipv4_loopback() {
        let p = UrlPolicy::block_private();
        // 127.1 == 127.0.0.1 (short-form, last part fills the low 24 bits)
        blocks(&p, "http://127.1");
        // 127.0.1 == 127.0.0.1
        blocks(&p, "http://127.0.1");
    }

    #[test]
    fn block_private_blocks_encoded_private_and_metadata() {
        let p = UrlPolicy::block_private();
        // 167772161 == 10.0.0.1 (RFC 1918)
        blocks(&p, "http://167772161");
        // 0xa000001 == 10.0.0.1
        blocks(&p, "http://0xa000001");
        // 2852039166 == 169.254.169.254 (cloud metadata)
        blocks(&p, "http://2852039166");
        // 0xA9FEA9FE == 169.254.169.254
        blocks(&p, "http://0xA9FEA9FE/latest/meta-data/");
    }

    #[test]
    fn block_private_allows_decimal_public_ipv4() {
        let p = UrlPolicy::block_private();
        // 134744072 == 8.8.8.8 (public) — normalization must not over-block.
        allows(&p, "http://134744072");
    }

    // ── trailing-dot hostnames (blocked) ────────────────────────────────────

    #[test]
    fn block_private_blocks_trailing_dot_localhost() {
        let p = UrlPolicy::block_private();
        // `localhost.` (root-label form) resolves to loopback just like
        // `localhost`, so it must be blocked too.
        blocks(&p, "http://localhost.");
        blocks(&p, "http://localhost.:8080/admin");
        blocks(&p, "http://api.localhost.");
    }

    // ── IPv6 private ranges via the url-crate host parser (blocked) ──────────

    #[test]
    fn block_private_blocks_ipv6_loopback_normalized() {
        let p = UrlPolicy::block_private();
        // ::1 loopback in various textual forms.
        blocks(&p, "http://[::1]");
        blocks(&p, "http://[0:0:0:0:0:0:0:1]");
    }

    #[test]
    fn block_private_blocks_ipv6_ula_fc00_7() {
        let p = UrlPolicy::block_private();
        // fc00::/7 unique-local addresses.
        blocks(&p, "http://[fc00::1]");
        blocks(&p, "http://[fd00::1]");
        blocks(&p, "http://[fdff:ffff::1]");
    }

    #[test]
    fn block_private_blocks_ipv6_link_local_fe80() {
        let p = UrlPolicy::block_private();
        blocks(&p, "http://[fe80::1]");
        blocks(&p, "http://[fe80::dead:beef]");
        blocks(&p, "http://[febf::1]");
    }

    // ── normalize_host_to_ip unit coverage ──────────────────────────────────

    #[test]
    fn normalize_host_to_ip_decodes_integer_forms() {
        // Decimal, hex, and octal all collapse to 127.0.0.1.
        assert_eq!(
            normalize_host_to_ip("2130706433"),
            Some(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)))
        );
        assert_eq!(
            normalize_host_to_ip("0x7f000001"),
            Some(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)))
        );
        assert_eq!(
            normalize_host_to_ip("017700000001"),
            Some(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)))
        );
        // Genuine hostnames are not IPs.
        assert_eq!(normalize_host_to_ip("example.com"), None);
        assert_eq!(normalize_host_to_ip(""), None);
    }
}
