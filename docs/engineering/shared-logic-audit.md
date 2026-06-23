# Shared Logic Audit

Status: active audit for keeping Beater's Gate 2, dashboard, and Rust service
contracts narrow, shared, and testable.

## Shipped in this pass

- `scripts/gate2_proof_contract.py` owns the Gate 2 image catalog, required
  image platforms, default outside-run endpoints, full-run port contract, and
  confirmation-code hash function plus test vector.
- Gate 2 readiness, public handoff, proof generation, and proof validation now
  consume that shared contract instead of each owning independent image/platform
  constants.
- `bins/beaterd/tests/self_host_contract.rs` now asserts that scripts use the
  shared contract while still keeping independent black-box sentinel coverage for
  public handoff behavior.
- `web/dashboard/lib/gate2-confirmation-request.ts` owns the browser
  confirmation request shape plus trace/span id validation, and the route/client
  now consume that shared contract.

## Keep Independent

- Rust string-contract tests should keep independent expected outcomes for
  outside-run evidence, docs, workflow snippets, and validator failures. Those
  tests are guardrails against accidental coupling, not production helpers.
- Shell preflight scripts may keep local operational implementations until a
  dedicated shell library can be introduced without hiding user-facing failure
  messages.

## Next Shared-Logic Targets

- Gate 2 proof schema: move required proof field names, fixed values, artifact
  path rules, and SLO field names behind a shared Python proof-schema helper.
- Runtime preflight: extract common Docker endpoint checks, default port checks,
  cleanup command constants, and process-owner hints into a small shell helper
  plus matching Python constants.
- Span taxonomy: add `AgentSpanKind::all()` in `beater-schema`, then validate or
  generate dashboard, migration, shell, and E2E span-kind lists from that source.
- OTLP normalization: keep dialect aliases local, but normalize aliases through
  `AgentSpanKind::parse` so canonical span-kind strings are not re-listed.
- Ingest crate: split internal modules into `normalize`, `queue`, `policy`, and
  `test_support`; extract shared canonical span assembly and retry accounting.
- Store helpers: add small shared helpers for span storage identity and trace
  span ordering while leaving SQLite and memory persistence mechanics separate.
- Eval context: introduce a typed `TraceEvalContext` builder so latency/cost
  evaluators, alerts, datasets, and experiments depend on one trace metric shape.
- Evaluator lanes: add `ensure_deterministic` / `ensure_judge` helpers on
  evaluator specs and use them in datasets, experiments, judge broker paths, and
  API route guards.
- API redaction: move span I/O redaction helpers out of route code and make
  dataset promotion explicitly choose redacted or unmasked capture policy.
- Dashboard query model: replace repeated query field mappings with a
  table-driven helper for search-param parsing, API params, hidden inputs,
  filter chips, and href construction.
- Dashboard Gate 2 confirmation: keep the request/id contract shared; next reduce
  the recorder's copied confirmation hash with a shared JS-compatible helper or
  a contract-vector test.
- Dashboard timeline/view helpers: extract pure timeline bounds, axis, run
  summary, artifact formatting, and query helpers before splitting components.
- CLI/runtime main files: move `beaterctl` command handlers and repeated
  full-stack test setup into focused modules or per-crate test-support helpers.
