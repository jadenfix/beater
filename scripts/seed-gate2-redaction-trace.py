#!/usr/bin/env python3
import argparse
import datetime as dt
import hashlib
import json
import sys
import urllib.error
import urllib.request


SENSITIVE_PROMPT = (
    "Gate 2 redaction check: customer SSN 123-45-6789 and card "
    "4242-4242-4242-4242 need review."
)
SENSITIVE_COMPLETION = (
    "Gate 2 unmasked completion: route the sensitive customer account to "
    "privacy review before replay."
)
UNMASK_REASON = "gate2-redaction-review"


def stable_hex(prefix: str, release_id: str, length: int) -> str:
    digest = hashlib.sha256(f"{prefix}:{release_id}".encode()).hexdigest()
    return digest[:length]


def utc_timestamp(offset_ms: int = 0) -> str:
    now = dt.datetime.now(dt.timezone.utc) + dt.timedelta(milliseconds=offset_ms)
    return now.isoformat(timespec="milliseconds").replace("+00:00", "Z")


def post_json(url: str, payload: dict, timeout_seconds: float) -> dict:
    body = json.dumps(payload).encode()
    request = urllib.request.Request(
        url,
        data=body,
        headers={"content-type": "application/json"},
        method="POST",
    )
    try:
        with urllib.request.urlopen(request, timeout=timeout_seconds) as response:
            response_body = response.read().decode()
            return json.loads(response_body) if response_body else {}
    except urllib.error.HTTPError as err:
        detail = err.read().decode(errors="replace")
        raise SystemExit(f"redaction trace ingest failed: HTTP {err.code}: {detail}") from None
    except urllib.error.URLError as err:
        raise SystemExit(f"redaction trace ingest failed: {err}") from None


def build_payload(release_id: str) -> tuple[dict, str, str]:
    trace_id = stable_hex("gate2-redaction-trace", release_id, 32)
    span_id = stable_hex("gate2-redaction-span", release_id, 16)
    payload = {
        "scope": {
            "tenant_id": "demo",
            "project_id": "demo",
            "environment_id": "local",
        },
        "trace_id": trace_id,
        "span_id": span_id,
        "parent_span_id": None,
        "seq": 1,
        "kind": "llm.call",
        "name": "sensitive-redaction-review",
        "status": "ok",
        "start_time": utc_timestamp(),
        "end_time": utc_timestamp(240),
        "model": {"provider": "openai", "name": "gpt-redaction"},
        "cost": {"amount_micros": 700, "currency": "USD"},
        "tokens": {"input": 10, "output": 8, "reasoning": 0, "cache_read": 0},
        "input": SENSITIVE_PROMPT,
        "output": SENSITIVE_COMPLETION,
        "attributes": {
            "agent.release_id": release_id,
            "privacy.test_case": "gate2-redacted-io",
            "privacy.unmask_reason": UNMASK_REASON,
        },
        "redaction_class": "sensitive",
        "idempotency_key": f"gate2-redaction-{stable_hex('idempotency', release_id, 24)}",
        "auth_context": None,
    }
    return payload, trace_id, span_id


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Seed the Gate 2 sensitive native trace used by browser redaction proof."
    )
    parser.add_argument("--api-url", default="http://127.0.0.1:8080")
    parser.add_argument("--release-id", required=True)
    parser.add_argument("--timeout-seconds", type=float, default=10.0)
    args = parser.parse_args()

    api_url = args.api_url.rstrip("/")
    payload, trace_id, span_id = build_payload(args.release_id)
    post_json(f"{api_url}/v1/traces/native", payload, args.timeout_seconds)
    print(
        json.dumps(
            {
                "trace_id": trace_id,
                "span_id": span_id,
                "release_id": args.release_id,
                "model": "gpt-redaction",
                "unmask_reason": UNMASK_REASON,
            },
            sort_keys=True,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
