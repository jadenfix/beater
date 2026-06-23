# Shared Logic Audit

Status: active audit for keeping Beater's Gate 2, dashboard, and Rust service
contracts narrow, shared, and testable.

## Audit Method

- Scan first-party Rust, TypeScript, Python, Node ESM, and shell sources for
  repeated hashing, typed-id parsing, SQLite DDL/store adapters, span-kind
  literals, OTLP smoke fixture construction, runtime wiring, and large
  main/test files. Exclude vendored dashboard dependencies from size analysis.
- Prefer extracting policy-bearing production helpers first. Keep black-box
  contract tests and independent failure-message assertions local unless they
  are only restating a shared constant.
- Treat large files as a direction signal, not an automatic refactor target:
  split them only when a stable helper boundary exists and tests can pin the
  behavior before/after the move.

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
- `web/dashboard/tests/e2e/gate2-confirmation-code.mjs` owns the recorder-side
  confirmation helper and test vector; dashboard tests assert parity with the
  TypeScript app helper.
- `web/dashboard/lib/api.ts` now uses the generated OpenAPI
  `PageRunSummaryDoc` shape instead of a hand-rolled generic page wrapper.
- Rust JSON/content hashes now use `beater_core::sha256_hex` in judge,
  dataset, replay, store, and ingest code instead of local implementations.
- `beater_core::sha256_json_hash` now owns the serde-json-bytes-to-SHA-256
  policy for dataset evaluator specs, judge request/response cache keys, and
  replay cassette request/response hashes, with a core golden test pinning the
  byte serialization contract.
- `beater_core::lower_hex` owns generic lowercase byte-to-hex formatting for
  OTLP id normalization, CLI smoke fixtures, and live-smoke tests.
- Gate 2 self-host contract tests now assert the shared dashboard confirmation
  helper directly, rather than the removed quickstart-local wrapper.
- `beater-search::index_project_trace` owns trace-ingested readback plus search
  indexing, so API drain and `beaterd` background workers share the same
  downstream processing path.
- `beater-search::TraceIngestedSearchProcessor` now wraps that readback/index
  helper for trace-ingested queue callbacks, so API manual drains and `beaterd`
  workers share the same downstream callback and retry/DLQ reason conversion.
- `ApiState` now has one private base constructor plus explicit opt-in setters
  for search, archive, dataset, and experiment integrations. The public
  constructors delegate through that path, and a regression test pins default
  optional-service behavior.
- `beater_store::query_runs_by_materializing_spans` now owns the local
  SQLite/memory run-summary fallback and names it as materialized-span behavior,
  so future ClickHouse work has a clear backend-aggregation boundary instead of
  inheriting duplicated dev-store rollup logic.

## Keep Independent

- Rust string-contract tests should keep independent expected outcomes for
  outside-run evidence, docs, workflow snippets, and validator failures. Those
  tests are guardrails against accidental coupling, not production helpers.
- Shell preflight scripts may keep local operational implementations until a
  dedicated shell library can be introduced without hiding user-facing failure
  messages.
- Runtime-specific Gate 2 confirmation implementations may exist in TypeScript,
  Python, shell, and Node ESM, but each implementation must stay tied to the
  shared prefix and golden vector.

## Audit Findings

- SQLite schema ownership is the largest remaining duplication. `beaterd`
  applies one local all-tables migration across several store databases while
  individual store crates also own `CREATE TABLE` blocks. The safe direction is
  either one local SQLite database with one migration manager, or per-store
  migrations exported by the owning crate and consumed by runtime wiring.
- Store boilerplate is repeated across auth, audit, datasets, gates, human,
  replay, search, secrets, usage, experiments, and calibration. A small SQLite
  support module should own connection setup, the repeated `IntoStoreResult`
  adapter, JSON column helpers, and timestamp/id decoding without becoming an
  ORM. Candidate owner: `beater-store-sql::support`; keep `beater-store`
  trait-only so persistence mechanics do not leak into domain contracts.
- Ingest preparation still has parallel native/raw/OTLP paths. The right shared
  contract is one internal canonical span input plus shared artifact hashing,
  idempotency, redaction, and span assembly.
- Trace-ingested search processing now shares both the readback/index helper and
  queue-callback processor, but higher-level queue draining, retry reporting,
  and worker hooks still live at their API/runtime boundaries.
- JSON value hashing now shares the serialization and SHA-256 policy through
  `beater_core::sha256_json_hash`. Dataset, judge, and replay keep only local
  boundary wrappers for domain-specific error text and return types.
- OpenAPI doc schemas mirror real API and schema DTOs. Prefer deriving or
  sharing public response DTOs rather than maintaining doc-only copies for
  canonical spans, run summaries, money, artifact refs, and query params.
- API handlers repeat route id parsing for tenant, project, environment,
  dataset, version, trace, span, queue, task, annotation, gate, and experiment
  ids. Introduce typed path structs in a new `crates/beater-api/src/path.rs` or
  `routes/support.rs` module before splitting handlers, so auth checks and
  domain calls receive validated ids consistently. Start with common shapes
  such as `ProjectPath`, `EnvironmentPath`, `TracePath`, `TraceSpanPath`,
  `DatasetVersionPath`, and human-review queue/task/annotation paths.
- API handlers and CLI fixtures rebuild similar eval, dataset, and experiment
  specs. Keep HTTP request structs local, but centralize conversion into domain
  specs after route-id parsing is shared; otherwise the conversion helpers will
  still own too much HTTP-specific error mapping.
- `bins/beaterctl/src/main.rs` repeats the smoke-to-dataset-to-experiment flow
  across deterministic, judge, and agent experiment commands. A
  `bins/beaterctl/src/fixtures.rs` module or narrow domain test-support helpers
  should own "smoke dataset version" construction without hiding command I/O.
- Dashboard query state is mapped across `web/dashboard/lib/api.ts`,
  `web/dashboard/app/page.tsx`, hidden form controls, filter chips, links, and
  E2E tests. A table-driven `web/dashboard/lib/dashboard-query.ts` helper should
  own field names, defaults, URL serialization, and link preservation.
- Local runtime wiring is concentrated in large first-party files:
  `bins/beaterctl/src/main.rs`, `bins/beaterd/src/main.rs`,
  `crates/beater-api/tests/full_stack.rs`, and the Gate 2 validator/proof
  scripts. `LocalStorePaths`, `LocalStackBuilder`, `demo_scope()`, smoke trace
  builders, and fixture setup helpers would reduce main/test file size while
  preserving all-in-one operational simplicity.
- OTLP smoke export fixture assembly is repeated in `beaterctl`, `beaterd`
  live-smoke tests, and API tests. Move only the stable test-support pieces
  (`smoke_ids`, metadata values, smoke export construction) into `beater-otlp`;
  keep endpoint assertions local to each runtime.
- `TraceStore::query_runs` is still only proven through the SQLite/memory
  materialized-span fallback. A ClickHouse-scale implementation must aggregate
  runs, model/release/cost/latency filters, and stable pagination in the backend
  rather than calling the fallback helper.

## Next Shared-Logic Targets

- SQLite schema: choose the one-database versus per-store migration model before
  touching migrations, then remove the duplicate all-tables/per-store DDL.
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
- TraceStore scale contract: add a ClickHouse-oriented run query conformance
  suite that rejects span materialization on normal `query_runs` paths and pins
  stable cursor behavior under equal timestamps.
- Eval context: introduce a typed `TraceEvalContext` builder so latency/cost
  evaluators, alerts, datasets, and experiments depend on one trace metric shape.
- API route parsing: add typed path/query helpers for `TenantId`, `ProjectId`,
  `EnvironmentId`, `TraceId`, `SpanId`, `DatasetId`, `DatasetVersionId`,
  `ReviewQueueId`, `ReviewTaskId`, `AnnotationId`, `GateId`, and
  `ExperimentRunId`, then migrate handlers by route family with auth tests.
- Eval/spec conversion: move deterministic/judge dataset and experiment request
  conversion into small API-local builder helpers that return domain specs and
  preserve 400-level id/hash validation.
- Evaluator lanes: add `ensure_deterministic` / `ensure_judge` helpers on
  evaluator specs and use them in datasets, experiments, judge broker paths, and
  API route guards.
- API redaction: move span I/O redaction helpers out of route code and make
  dataset promotion explicitly choose redacted or unmasked capture policy.
- Dashboard query model: replace repeated query field mappings with a
  table-driven helper for search-param parsing, API params, hidden inputs,
  filter chips, and href construction.
- Dashboard Gate 2 confirmation: keep the request/id contract shared and the
  recorder helper pinned to the app helper with the shared vector.
- Dashboard timeline/view helpers: extract pure timeline bounds, axis, run
  summary, artifact formatting, and query helpers before splitting components.
- Rust store result helpers: evaluate whether repeated `IntoStoreResult`
  adapter traits should move into `beater-store` or a small persistence helper.
  Move that trait before attempting timestamp/id decode helpers, so local
  rusqlite row-shape errors stay explicit and readable.
- SQLite timestamp decoding: centralize repeated RFC3339 decode/error mapping
  once the store crates settle on a common error helper.
- CLI/runtime main files: move `beaterctl` command handlers and repeated
  full-stack test setup into focused modules or per-crate test-support helpers.
- OTLP test support: share smoke export construction from `beater-otlp` test
  support once the API, CLI, and runtime tests agree on which fields are
  contractually stable.
