# Contributing to Beater

## The one rule: the OpenAPI contract is the single source of truth

The HTTP API, the 7 SDK clients, the MCP tools, the CLI, and the docs are **all
generated from one artifact** — `sdks/openapi/beater-api.json`, which is itself
generated from the Rust handlers in `crates/beater-api`. Never hand-edit a
generated client, the spec snapshot, or `sdks/semconv/conventions.json`.

### When you add or change a `/v1` endpoint

Do all of this in the same change (CI enforces it — see below):

1. **Handler + contract.** Add the axum route in `crates/beater-api/src/lib.rs`
   and annotate the handler with `#[utoipa::path(...)]`: a unique camelCase
   `operation_id`, a resource `tag`, params, `request_body`, and **every**
   response it can return (including `4xx`/`429`/`413`/`422`), each error using
   the shared `ErrorResponse` body. Request/response types must derive
   `utoipa::ToSchema`.
2. **Regenerate everything from the contract** — one command:
   ```bash
   cargo xtask regen-spec      # spec + dashboard snapshot
   scripts/regen-sdks.sh       # 7 clients (+ reproducible C/C++ patches)
   cargo xtask regen-semconv   # sdks/semconv/conventions.json (if conventions changed)
   ```
3. **If you touched span kinds / attribute keys**, change them ONLY in
   `crates/beater-schema` (`conventions` module) and re-run `regen-semconv`; then
   update each SDK's `semconv` to match (the gate will tell you what's missing).
4. **Commit the regenerated output** (generated clients are committed on purpose).

### Verify there is no drift — one command

```bash
scripts/check-contract-sync.sh
```

This runs every drift gate: spec ↔ served routes, spec ↔ all 7 SDK clients,
the API-shape audit, and semantic-conventions ↔ all 5 SDKs. CI runs the same
gates in `.github/workflows/sdk-contract.yml`, so **a handler change that isn't
regenerated into the spec, SDKs, MCP tools, and docs cannot merge**, and
`oasdiff` blocks breaking contract changes.

Because the MCP tools and CLI resolve operations from the spec at runtime, they
update automatically — no separate step. The docs site renders the committed
spec, so it updates too.

## Building & testing

- `cargo build --workspace` / `cargo test --workspace`
- `cargo clippy --workspace --all-targets` (unwrap/expect are denied in non-test code)
- Live SDK conformance (needs Docker + language toolchains):
  `scripts/e2e-clients-live.sh`
