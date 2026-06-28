#!/usr/bin/env python3
"""Guard the client-platform architecture note against contract drift."""

from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parent.parent
DOC = ROOT / "docs" / "sdk-platform-architecture.md"
CONTRACT_CHECK = ROOT / "scripts" / "check-contract-sync.sh"


def missing_needles(label: str, text: str, needles: list[str]) -> list[str]:
    return [f"{label}: {needle}" for needle in needles if needle not in text]


def ordered_tokens(label: str, text: str, tokens: list[str]) -> list[str]:
    position = -1
    failures = []
    for token in tokens:
        next_position = text.find(token, position + 1)
        if next_position == -1:
            failures.append(f"{label}: missing or out of order: {token}")
        else:
            position = next_position
    return failures


def main() -> int:
    doc = DOC.read_text(encoding="utf-8")
    contract_check = CONTRACT_CHECK.read_text(encoding="utf-8")

    failures: list[str] = []
    failures.extend(
        missing_needles(
            "contract graph",
            doc,
            [
                "crates/beater-api handlers",
                "sdks/openapi/beater-api.json",
                "7 SDK clients",
                "/mcp tools",
                "beater CLI",
                "docs site",
                "conformance",
            ],
        )
    )
    failures.extend(
        missing_needles(
            "validation gates",
            doc,
            [
                "sdk-contract.yml",
                "oasdiff",
                "openapi_coverage",
                "live conformance",
                "MCP has parity tests vs direct HTTP",
                "scripts/check-contract-sync.sh",
            ],
        )
    )
    failures.extend(
        ordered_tokens(
            "local regeneration chain",
            doc,
            [
                "cargo xtask regen-spec",
                "scripts/regen-sdks.sh",
                "cargo xtask regen-semconv",
                "scripts/check-contract-sync.sh",
            ],
        )
    )
    failures.extend(
        missing_needles(
            "api shape conventions",
            doc,
            [
                "operationId",
                "ApiErrorBody { error, status }",
                "Cursor pagination",
                "tenant",
                "project",
                "environment",
                "All routes under `/v1`",
            ],
        )
    )
    failures.extend(
        missing_needles(
            "client surfaces",
            doc,
            [
                "init()",
                "@observe",
                "wrap_openai()",
                "wrap_anthropic()",
                "OpenTelemetry",
                "semconv",
                "client.datasets.createDataset",
                "beater api <operationId>",
                "/mcp",
                "/docs",
            ],
        )
    )
    failures.extend(
        missing_needles(
            "contract check script",
            contract_check,
            [
                "One-command drift test",
                "the 7 SDK clients",
                "MCP",
                "docs",
                "scripts/regen-sdks.sh --check",
                "No drift: API, 7 SDKs, MCP tools, docs, and conventions are all in sync.",
            ],
        )
    )

    if failures:
        print("SDK platform docs contract drift:", file=sys.stderr)
        for failure in failures:
            print(f"  - {failure}", file=sys.stderr)
        return 1

    print("SDK platform docs cover the API/spec/SDK/MCP/CLI/docs contract.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
