#!/usr/bin/env python3
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path


REPO = Path(__file__).resolve().parent.parent
TRAIT_SCAN_CRATES = [
    "crates/beater-store",
    "crates/beater-auth",
    "crates/beater-datasets",
    "crates/beater-experiments",
    "crates/beater-gates",
    "crates/beater-human",
    "crates/beater-judge",
    "crates/beater-usage",
    "crates/beater-eval",
]


def fail(message: str) -> None:
    print(f"Gate 0 foundation contract failed: {message}", file=sys.stderr)
    raise SystemExit(1)


def run(command: list[str]) -> str:
    result = subprocess.run(
        command,
        cwd=REPO,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.stdout:
        print(result.stdout, end="" if result.stdout.endswith("\n") else "\n")
    if result.returncode != 0:
        fail(f"command failed: {' '.join(command)}")
    return result.stdout


def read(path: str) -> str:
    return (REPO / path).read_text()


def check_store_crate_has_no_sqlite_dependency() -> None:
    tree = run(["cargo", "tree", "-p", "beater-store"])
    forbidden = ["rusqlite", "beater-store-sql", "sqlite"]
    hits = [needle for needle in forbidden if needle in tree.lower()]
    if hits:
        fail("beater-store must stay trait/types-only; found dependency text: " + ", ".join(hits))


def check_trace_store_conformance_runs_on_two_backends() -> None:
    conformance = read("crates/beater-store-conformance/src/lib.rs")
    for symbol in [
        "assert_trace_store_conformance",
        "assert_metadata_store_conformance",
        "assert_quota_limiter_conformance",
    ]:
        if symbol not in conformance:
            fail(f"beater-store-conformance must define {symbol}")

    sql = read("crates/beater-store-sql/src/lib.rs")
    memory = read("crates/beater-store-memory/src/lib.rs")
    for symbol in [
        "assert_trace_store_conformance",
        "assert_metadata_store_conformance",
        "assert_quota_limiter_conformance",
    ]:
        if symbol not in sql:
            fail(f"beater-store-sql tests must call {symbol}")
        if symbol not in memory:
            fail(f"beater-store-memory tests must call {symbol}")

    run(
        [
            "cargo",
            "test",
            "-p",
            "beater-store-conformance",
            "-p",
            "beater-store-memory",
            "-p",
            "beater-store-sql",
        ]
    )


def check_metadata_store_boundary() -> None:
    store = read("crates/beater-store/src/lib.rs")
    if "pub trait MetadataStore" not in store:
        fail("beater-store must define MetadataStore")

    api = read("crates/beater-api/src/lib.rs")
    if "metadata: Arc<dyn MetadataStore>" not in api:
        fail("beater-api must store metadata behind Arc<dyn MetadataStore>")
    if "with_metadata(mut self, metadata: Arc<dyn MetadataStore>)" not in api:
        fail("beater-api must expose MetadataStore injection for consumers")


def check_no_anyhow_in_public_traits() -> None:
    trait_start = re.compile(r"^\s*(?:pub\s+)?trait\s+[A-Za-z0-9_]+")
    failures: list[str] = []
    for crate in TRAIT_SCAN_CRATES:
        for path in sorted((REPO / crate).glob("src/**/*.rs")):
            in_trait = False
            brace_depth = 0
            trait_line = 0
            for line_no, line in enumerate(path.read_text().splitlines(), start=1):
                if not in_trait and trait_start.search(line):
                    in_trait = True
                    trait_line = line_no
                    brace_depth = line.count("{") - line.count("}")
                elif in_trait:
                    brace_depth += line.count("{") - line.count("}")

                if in_trait and "anyhow::Result" in line:
                    failures.append(
                        f"{path.relative_to(REPO)}:{line_no} inside trait starting at line {trait_line}"
                    )

                if in_trait and brace_depth <= 0 and (line_no != trait_line or "}" in line):
                    in_trait = False
                    trait_line = 0

    if failures:
        fail("public storage/eval trait methods must use typed errors, not anyhow::Result:\n  " + "\n  ".join(failures))


def check_core_schema_clock_boundary() -> None:
    failures = []
    for crate in ["crates/beater-core", "crates/beater-schema"]:
        for path in sorted((REPO / crate).glob("src/**/*.rs")):
            for line_no, line in enumerate(path.read_text().splitlines(), start=1):
                if "Utc::now()" in line:
                    failures.append(f"{path.relative_to(REPO)}:{line_no}")
    if failures:
        fail("found direct Utc::now() in core/schema; use Clock injection:\n  " + "\n  ".join(failures))


def check_schema_owns_rollups_and_mappings() -> None:
    schema = read("crates/beater-schema/src/lib.rs")
    for symbol in [
        "pub fn span_matches",
        "pub fn span_summary",
        "pub fn roll_up_runs",
        "pub fn filter_run_summaries",
        "impl AgentSpanKind",
        "impl SpanStatus",
        "pub fn as_str(&self)",
        "pub fn parse(value: &str)",
    ]:
        if symbol not in schema:
            fail(f"beater-schema must own {symbol}")

    for path in ["crates/beater-store-memory/src/lib.rs", "crates/beater-store-sql/src/lib.rs"]:
        text = read(path)
        for symbol in ["roll_up_runs", "filter_run_summaries", "span_summary"]:
            if symbol not in text:
                fail(f"{path} must use schema {symbol}")
        for forbidden in ["fn roll_up_runs", "fn filter_run_summaries", "fn aggregate_run_status"]:
            if forbidden in text:
                fail(f"{path} must not define backend-local {forbidden}")


def main() -> None:
    check_store_crate_has_no_sqlite_dependency()
    check_trace_store_conformance_runs_on_two_backends()
    check_metadata_store_boundary()
    check_no_anyhow_in_public_traits()
    check_core_schema_clock_boundary()
    check_schema_owns_rollups_and_mappings()
    print("Gate 0 foundation contract passed.")


if __name__ == "__main__":
    main()
