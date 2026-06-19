# Beater Architecture

Beater is a Rust-first, open-source agent observability, replay, and eval platform.
It is designed to be credible as an OSS project, viable as a hosted API product, and
agent-native enough to compete with Arize Phoenix, Braintrust, LangSmith, Langfuse,
and Judgment-style agent debugging systems.

The core product loop is the definition of "shipped":

```text
instrument agent
  -> inspect trace/span tree
  -> promote failure to dataset
  -> run evals
  -> compare candidate change
  -> block or allow CI
  -> monitor production after deploy
```

If that loop is not excellent end to end, the rest of the platform is premature.

## 1. Non-Negotiable Principles

1. Ship one Rust binary first.
   Crates are modular, but the MVP runs as one `beaterd` process. Later service
   splits are thin bins over the same crates and are justified only by measured
   scale pressure.

2. Use standards at the edge, not proprietary lock-in.
   OTLP, W3C trace-context, OpenInference, OpenTelemetry GenAI conventions, and
   common framework exporters are first-class. The native Rust SDK is an
   accelerator, not the adoption gate.

3. Store immutable raw data and normalized projections.
   Every ingest event keeps its raw envelope, source schema URL/version, payload
   hash, normalizer version, and unmapped attributes. The normalized model is a
   canonical superset used for queries and UI. Lossless round-trip is promised
   only through the raw copy, not through lossy standards projections.

4. Design privacy and tenancy before hosted ingest.
   Tenant isolation, regional pinning, redaction, crypto-shredding, retention,
   scoped keys, audited PII access, and artifact encryption are v1 constraints.

5. Split deterministic evals from model-dependent evals.
   User-supplied deterministic evaluators run in a WASI Component Model sandbox
   via Wasmtime with no network. LLM-judge and embedding evals run through a
   judge broker with budgets, redaction, model versioning, and audit trails.

6. Be honest about replay.
   Deterministic replay requires provider, tool, memory, and clock cassettes.
   Without cassettes, the product calls it forked replay or simulation.

7. Scope Vercel correctly.
   Vercel runs the dashboard, stateless Rust functions, edge/control-plane API,
   webhooks, Blob, Queues, and Cron. Long-running ingest listeners, ClickHouse
   writers, eval pools, replay pools, and stateful workers run in hosted cells or
   in the OSS all-in-one process.

8. No cloud dependency in OSS.
   The open-source edition must run without calling Beater Cloud. Self-host
   telemetry is opt-out, and all hosted-specific APIs degrade cleanly to local
   equivalents or are absent.

## 2. Editions

| Capability | OSS self-host | Hosted |
| --- | --- | --- |
| All-in-one Rust binary | Required | Used for cells and local dev |
| OTLP and native ingest | Required | Required |
| Trace viewer and span tree | Required | Required |
| Datasets, experiments, offline evals | Required | Required |
| WASI deterministic evaluator sandbox | Required | Required |
| Judge broker with BYOK | Required | Required |
| Managed judge routing and shared judge fleet | Optional BYOK only | Required |
| Online eval sampling and alerts | OSS local/basic | Hosted scaled/commercial |
| Multi-tenant orgs, billing, quotas | Single-cell/basic | Required |
| SSO/SAML, regional pinning UI, advanced audit export | Optional enterprise | Commercial |
| No-cloud operation | Required | Not applicable |

Open-core boundary:

- Apache-2.0 core: ingest, canonical schema, local auth, trace UI, datasets,
  deterministic evals, WASI ABI, judge broker BYOK, replay cassettes, CI gate,
  import/export, Docker Compose, plugin APIs.
- Commercial/hosted: managed multi-region cells, billing, SSO/SAML, enterprise
  audit reporting, regional compliance controls, managed alerts, hosted judge
  fleet, high-scale replay/eval pools, support SLAs.
- Security-critical primitives such as audit event generation and redaction are
  not withheld from OSS. The paid boundary is managed scale and governance UX,
  not the ability to self-host safely.

## 3. Deployment Shape

### 3.1 OSS

```text
docker compose up
  beaterd       # one Rust process: API, OTLP, jobs, eval, replay
  postgres      # metadata and optional local TraceStore
  clickhouse    # optional scale TraceStore
  nats          # JetStream durable bus
  minio         # object storage
```

Local development can run with SQLite plus local filesystem object storage, but
the same code paths must work with Postgres, ClickHouse, NATS JetStream, and
S3-compatible storage.

### 3.2 Hosted

```text
Vercel
  dashboard
  Rust Functions for stateless /v1 API routes
  Vercel Queues for Vercel-native async boundaries
  Vercel Blob for small/control-plane artifacts where appropriate
  Cron for short scheduled tasks

Hosted Rust cells
  long-running OTLP gRPC/HTTP ingest
  queue consumers
  ClickHouse writers
  replay/eval/judge workers
  WebSocket/SSE fanout if needed

Managed data
  Postgres for metadata
  ClickHouse for hot trace analytics
  S3/R2/GCS for artifacts and raw envelopes
  Parquet/DataFusion for cold retention
```

Current platform constraints, verified June 19, 2026:

- Vercel's official Rust runtime is beta, runs on Fluid Compute, and uses
  `vercel_runtime` handlers in `api/`.
- Vercel Functions have request/response and body-size limits; the documented
  payload limit is 4.5 MB.
- Vercel Functions do not act as WebSocket servers.
- Vercel Queues are beta durable append-only topics with at-least-once delivery,
  idempotency keys, push consumers, and poll consumers. Poll mode is suitable for
  off-Vercel workers.
- Therefore Vercel can be the hosted control plane and stateless API surface, but
  not the only runtime for stateful ingest and long-running workers.

Primary source links:

- https://vercel.com/docs/functions/runtimes/rust
- https://vercel.com/docs/functions/limitations
- https://vercel.com/docs/queues
- https://vercel.com/docs/queues/poll-mode

## 4. Rust Workspace

The operational split is logical first, physical later.

```text
beater/
  Cargo.toml
  crates/
    beater-core/          # IDs, entity types, errors, time, money, tenant scope
    beater-schema/        # canonical event/run/span/eval schemas and versions
    beater-otlp/          # tonic/prost OTLP receive and export
    beater-normalize/     # OTLP/OI/GenAI/Vercel/LangSmith/Phoenix -> canonical
    beater-ingest/        # auth, quota, raw append, normalization, sampling
    beater-store/         # TraceStore, MetadataStore, ArtifactStore traits
    beater-store-sql/     # SQLite/Postgres TraceStore for dev/small installs
    beater-store-ch/      # ClickHouse TraceStore for scale
    beater-store-obj/     # object_store-backed artifacts and raw envelopes
    beater-bus/           # NATS JetStream default, Vercel Queues, Kafka adapter
    beater-eval/          # evaluator catalog, scoring contracts, aggregation
    beater-calibration/   # judge-vs-human agreement and kappa reports
    beater-usage/         # usage ledger, billing meters, spend summaries
    beater-sandbox/       # Wasmtime/WASI Component Model evaluator runtime
    beater-secrets/       # opaque provider-secret refs, BYOK metadata, revocation
    beater-judge/         # LLM/embedding judge broker, BYOK, calibration
    beater-replay/        # cassettes, forked replay, deterministic replay
    beater-datasets/      # datasets, versions, examples, trace promotion
    beater-experiments/   # candidate-vs-baseline comparisons and statistics
    beater-gates/         # CI/CD gates and policy evaluation
    beater-human/         # review queues, annotations, human labels
    beater-auth/          # API keys, JWT/session, RBAC, audit scopes
    beater-api/           # axum routers, OpenAPI, SSE/read APIs
    beater-sdk/           # native Rust SDK and tracing layers
    beater-telemetry/     # dogfooding, metrics, health, SLO instrumentation
  bins/
    beaterd/              # default all-in-one binary
    beaterctl/            # CLI: init, ingest test, eval run, gate, export
    beater-worker/        # later thin bin over worker modules
    beater-ingestd/       # later thin bin over ingest modules
  api/
    *.rs                  # Vercel Rust Function entrypoints where needed
  web/
    dashboard/            # Next.js dashboard consuming generated OpenAPI client
  migrations/
    postgres/
    clickhouse/
  docker-compose.yml
```

The dashboard can use TypeScript/React for product velocity, but all platform
logic, ingestion, storage, eval, replay, API contracts, and SDK primitives remain
Rust-owned.

### 4.1 Implementation Picks

The default Rust stack should be boring and production-proven:

| Concern | Pick |
| --- | --- |
| async runtime | `tokio` |
| HTTP API | `axum`, `tower`, `hyper` |
| OTLP gRPC | `tonic`, `prost`, `opentelemetry-proto` |
| Vercel Rust Functions | `vercel_runtime` |
| serialization | `serde`, `serde_json`, `rmp-serde` where useful |
| schema/OpenAPI | `utoipa` |
| metadata DB | `sqlx` with Postgres and SQLite |
| ClickHouse | official `clickhouse` crate |
| object storage | `object_store` |
| durable bus | `async-nats` JetStream by default; Kafka adapter for enterprise |
| Vercel queue adapter | Vercel Queues HTTP API |
| WASI sandbox | `wasmtime` Component Model |
| cold analytics | `arrow`, `parquet`, `datafusion` |
| full-text search | `tantivy` |
| auth/secrets | `argon2`, `jsonwebtoken`, KMS/Vault-compatible traits |
| CLI | `clap` |
| testing | `cargo-nextest`, `testcontainers`, `insta`, `proptest` |
| build/release | `cargo-chef`, multi-stage Docker, `cargo-deny` |

The stack can change when implementation evidence demands it, but each
replacement must preserve the architecture contracts in this document.

## 5. Canonical Data Model

### 5.1 Entity Set

- `Organization`
- `User`
- `Project`
- `Environment`
- `Agent`
- `AgentRelease`
- `Run`
- `Span`
- `Event`
- `Artifact`
- `ReplayCassette`
- `Dataset`
- `DatasetVersion`
- `DatasetCase`
- `Experiment`
- `ExperimentRun`
- `Evaluator`
- `EvaluatorVersion`
- `EvalResult`
- `Gate`
- `GateRun`
- `ReviewQueue`
- `ReviewTask`
- `Annotation`
- `Prompt`
- `PromptVersion`
- `UsageLedger`
- `UsageRecord`
- `ApiKey`
- `WebhookEndpoint`
- `RedactionPolicy`
- `RetentionPolicy`
- `AuditEvent`

### 5.2 Agent Span Taxonomy

These span kinds are canonical, regardless of incoming dialect:

```text
agent.run
agent.turn
agent.plan
agent.step
llm.call
tool.call
mcp.request
retrieval.query
memory.read
memory.write
guardrail.check
human.review
evaluator.run
replay.run
```

Additional provider/framework kinds are retained as original attributes and can
be projected into OpenInference or OTel GenAI exports.

### 5.3 Raw Envelope and Normalized Projection

Every write path stores both forms:

```rust
pub struct RawEnvelope {
    pub schema_version: u32,
    pub tenant_id: TenantId,
    pub project_id: ProjectId,
    pub environment_id: EnvironmentId,
    pub source: SourceDialect,
    pub source_schema_url: Option<String>,
    pub source_schema_version: Option<String>,
    pub received_at: Timestamp,
    pub idempotency_key: IdempotencyKey,
    pub payload_hash: Sha256,
    pub body_ref: ArtifactRef,
    pub auth_context: AuthContext,
}

pub struct CanonicalSpan {
    pub schema_version: u32,
    pub normalizer_version: String,
    pub tenant_id: TenantId,
    pub trace_id: TraceId,
    pub span_id: SpanId,
    pub parent_span_id: Option<SpanId>,
    pub seq: u64,
    pub kind: AgentSpanKind,
    pub status: SpanStatus,
    pub start_time: Timestamp,
    pub end_time: Option<Timestamp>,
    pub model: Option<ModelRef>,
    pub cost: Option<Money>,
    pub tokens: Option<TokenCounts>,
    pub input_ref: Option<ArtifactRef>,
    pub output_ref: Option<ArtifactRef>,
    pub attributes: CanonicalAttrs,
    pub unmapped_attrs: serde_json::Value,
    pub raw_ref: ArtifactRef,
}
```

Idempotency key:

```text
tenant_id + project_id + trace_id + span_id + seq + payload_hash
```

Late spans are accepted. Out-of-order writes are normal. Trace completeness is a
state machine, not a boolean.

## 6. Standards and Normalization

Input dialects:

- OTLP traces over gRPC and HTTP.
- OpenInference attributes and span kinds.
- OpenTelemetry GenAI conventions.
- Vercel AI SDK telemetry shapes.
- OpenLLMetry/Traceloop-compatible attributes.
- Native Beater `/v1` JSON ingest.
- Future imports from Phoenix, LangSmith, Langfuse, and Braintrust exports.

Output dialects:

- OTLP export.
- OpenInference-compatible export.
- Parquet export.
- JSONL dataset/eval export.
- Post-training export for SFT/RL pipelines.

OpenTelemetry GenAI note:

- The old OpenTelemetry docs now point to the standalone
  `open-telemetry/semantic-conventions-genai` repository.
- The repository currently contains generated docs/model definitions for GenAI
  clients, MCP, events, spans, metrics, and provider-specific conventions.
- Pin by commit or generated schema snapshot. Do not assume stability. The
  normalizer must support both old and new forms.

Source links:

- https://opentelemetry.io/docs/specs/semconv/gen-ai/
- https://github.com/open-telemetry/semantic-conventions-genai

## 7. Storage Architecture

### 7.1 Trait Boundary

`TraceStore` exists before any ClickHouse-specific behavior leaks into product
code.

```rust
#[async_trait::async_trait]
pub trait TraceStore: Send + Sync {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> anyhow::Result<WriteAck>;
    async fn get_trace(
        &self,
        tenant: TenantId,
        trace: TraceId,
    ) -> anyhow::Result<TraceView>;
    async fn query_runs(
        &self,
        tenant: TenantId,
        filter: RunFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<RunSummary>>;
    async fn query_spans(
        &self,
        tenant: TenantId,
        filter: SpanFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<SpanSummary>>;
}
```

Backends:

- `SqlTraceStore`: SQLite for tiny local installs, Postgres for small teams and
  tests.
- `ClickHouseTraceStore`: hot analytical trace store for production scale.
- `ParquetTraceArchive`: cold tier queried through DataFusion.

Product code depends on `TraceStore`, not ClickHouse tables.

### 7.2 Data Planes

| Plane | Default OSS | Hosted scale | Purpose |
| --- | --- | --- | --- |
| Metadata | Postgres, SQLite dev | Postgres | orgs, projects, prompts, datasets, RBAC, billing metadata |
| Hot traces | Postgres/SQLite dev, ClickHouse optional | ClickHouse | runs, spans, events, scores, indexed attrs |
| Raw/artifacts | filesystem dev, MinIO/S3 | S3/R2/GCS/Vercel Blob where suitable | raw envelopes, payloads, cassettes, exports |
| Durable bus | NATS JetStream | Vercel Queues at edge, NATS or Kafka in cells | ingest buffering, eval jobs, replay jobs |
| Cold traces | Parquet + DataFusion | Parquet + DataFusion | long retention and export |
| Full text | Tantivy | Tantivy or managed equivalent | prompt/output/error search |

Redis is optional cache/pubsub, not the default durability primitive.

### 7.3 ClickHouse Rules

- Tenant ID leads sort keys and all query filters.
- Updates are modeled as new events or versioned replacing rows.
- Object storage holds large inputs, outputs, attachments, raw payloads, and
  cassettes. ClickHouse stores refs, hashes, sizes, MIME types, and redaction
  classifications.
- TTL moves hot rows to cold Parquet before deletion.
- Query APIs must not require `FINAL` for normal paths.

### 7.4 Queue and Job Lanes

Do not collapse every async concern into one queue. The platform has distinct
lanes with different guarantees:

| Lane | OSS default | Hosted default | Required semantics |
| --- | --- | --- | --- |
| in-process smoothing | bounded Tokio channels | bounded Tokio channels | absorbs short spikes, rejects when full |
| ingest durability | NATS JetStream | Vercel Queues at edge, NATS/Kafka in cells | at-least-once, idempotency keys, replay until retention |
| background jobs | NATS JetStream or Postgres-backed scheduler | NATS/Kafka/cell scheduler | retries, backoff, poison-message isolation |
| DLQ | NATS stream plus object refs | regional DLQ stream plus object refs | reason codes, replay tooling, alerts |
| cache/pubsub | optional Redis or in-process | Redis/managed cache where needed | never source of durability |
| enterprise bus | Kafka adapter | Kafka adapter | large customer integration and audit needs |

Poison messages are messages that repeatedly fail for deterministic reasons.
They must be moved to DLQ with a reason, source envelope ref, attempt history,
and replay command. They must not block a partition or consumer group forever.

## 8. Ingest Pipeline

```text
receive OTLP/native request
  -> authenticate API key and project/environment
  -> enforce per-project quotas and payload limits
  -> create RawEnvelope and artifact refs
  -> append raw envelope durably
  -> normalize with pinned normalizer version
  -> enforce cardinality/payload governance
  -> buffer for tail-sampling and trace completion
  -> write canonical projection through TraceStore
  -> enqueue online eval/replay/alert jobs
  -> acknowledge or DLQ
```

Required survivability behavior:

- Backpressure with bounded queues.
- At-least-once delivery reconciled by idempotency keys.
- Dead-letter queue for invalid, unauthenticated, unnormalizable, or repeatedly
  unwritable events.
- Poison-message isolation so one bad tenant payload cannot stall a shard.
- No silent drops.
- Per-project ingest quotas with explicit 429 semantics.
- Payload size caps. Oversized prompts/completions truncate to artifact refs.
- Per-attribute cardinality budgets.
- Attribute allow/deny lists at project and environment scope.
- Tail-based sampling that keeps all errors, slow traces, high-cost traces, and
  traces selected by policy while sampling routine traffic.
- Trace completion semantics based on root-span end, idle timeout, and late-span
  window.
- Clock-skew correction and out-of-order handling across distributed agents.

Trace states:

```text
open
root_ended
idle_complete
late_window_closed
complete
incomplete
```

Online evals trigger only when policy says the trace is complete enough.

## 9. Evaluator Architecture

### 9.1 Execution Lanes

Deterministic lane:

- Runtime: Wasmtime using the WASI Component Model.
- Network: none.
- Inputs: trace/case data, expected outputs, evaluator config, artifact reads
  through explicit host functions.
- Outputs: structured score, labels, evidence refs, diagnostics.
- Examples: exact match, regex, JSON schema, tool-call correctness,
  trajectory-structure checks, latency budgets, cost budgets, token budgets,
  loop detection, citation presence, PII-pattern checks.

Judge lane:

- Runtime: `judge-broker` Rust service/module.
- Network: broker only, never evaluator WASM.
- Secrets: provider keys held behind opaque `ProviderSecretId` refs. The OSS
  SQLite implementation stores ChaCha20-Poly1305 ciphertext with tenant/project/
  secret/provider associated data; hosted cells can swap the same trait for KMS
  or customer vault unwrap. API responses and ledgers expose metadata only,
  never secret material.
- Controls: redaction, preflight budget reservation, rate limit, model pinning,
  retries, request-hash caching, and append-only audit logging.
- Usage: judge calls emit idempotent `UsageRecord`s keyed by tenant/project,
  meter, source kind, and source ID. Billing summaries use charged cost, while
  cached calls remain visible as zero-cost audit records.
- Provider clients: OpenAI-compatible chat completions and Anthropic messages
  are first-class Rust judge providers behind the same broker trait, with
  retry/backoff for `429` and `5xx` responses and structured JSON score parsing.
- Dataset execution: dataset-version evals support both deterministic WASI
  scorers and judge-broker scorers. Judge-backed reports persist through the
  same `DatasetEvalReport`/`EvalResult` schema, with model/provider/request
  hashes, cache status, and charged cost pinned in reproducibility metadata.
- Experiment execution: candidate-vs-baseline gates support judge-broker
  scorers as well as deterministic scorers. Per-case experiment scores retain
  judge call IDs, charged costs, and cache status so noisy/model-dependent gates
  remain auditable. Experiment reports also retain the `GatePolicy` that
  produced the stored pass/fail/inconclusive decision.
- Examples: faithfulness, pairwise judge, trajectory quality, retrieval
  relevance, handoff quality, rubric grading, semantic safety checks.

### 9.2 EvalResult Reproducibility Contract

Every `EvalResult` pins:

- dataset version
- dataset case ID
- candidate agent release
- prompt version
- evaluator ID and version
- evaluator code hash or WASM hash
- WASI ABI version if deterministic
- judge model ID, provider, parameters, seed when available
- judge prompt/rubric version
- normalizer version
- trace schema version
- input artifact hashes
- execution timestamp
- cost and token usage
- reason if an old result cannot be reproduced

### 9.3 Statistical Rigor

Experiment comparison must include:

- candidate vs baseline deltas
- N-trial repetition for noisy evaluators
- confidence intervals
- variance by case and metric
- significance testing before declaring wins
- minimum sample-size policy per metric and gate
- explicit test choice by metric type, such as paired bootstrap, permutation
  test, McNemar, or t-test only when assumptions are met
- multiple-comparison handling when one experiment evaluates many metrics or
  cohorts
- pairwise position-bias mitigation by swapping A/B order
- judge calibration artifact with judge-vs-human agreement, confusion counts,
  and Cohen's kappa where applicable
- recalibration triggers for model deprecation, provider drift, rubric changes,
  and kappa degradation

The CI gate must be able to fail on confidence-bound regressions, not only raw
mean score deltas.

## 10. Replay and Failure Attribution

Replay substrate:

- Immutable event stream.
- Provider cassettes for LLM requests/responses, streaming chunks, tool calls,
  embeddings, retrievals, memory reads/writes, guardrail checks, random seeds,
  clock reads, and human-review stubs.
- Versioned tool schemas and MCP request/response bodies.

Replay modes:

- `deterministic_replay`: all required cassettes present and hashes match.
- `forked_replay`: starts from a captured trace, then calls live providers/tools
  after a fork point.
- `simulation`: substitutes models/tools with configured simulators.

Failure attribution pipeline:

```text
failed trace
  -> span-level deterministic checks
  -> judge or human checks where needed
  -> compare against similar passing traces
  -> replay or fork candidate corrections
  -> identify earliest span whose correction flips outcome
  -> write root-cause annotation and regression candidate
```

The product should surface:

- root-cause span
- confidence/evidence
- failed-vs-passed diff
- replay mode and guarantee level
- one-click "add to dataset"

## 11. Agent Harness

The harness lets the platform become an open-source eval runner, not just a
trace viewer.

```rust
#[async_trait::async_trait]
pub trait AgentAdapter {
    async fn run_case(
        &self,
        case: DatasetCase,
        ctx: HarnessContext,
    ) -> anyhow::Result<AgentRunOutput>;
}

#[async_trait::async_trait]
pub trait ToolProxy {
    async fn call_tool(&self, request: ToolRequest) -> anyhow::Result<ToolResponse>;
}

#[async_trait::async_trait]
pub trait TraceEmitter {
    async fn emit(&self, event: CanonicalEvent) -> anyhow::Result<()>;
}
```

Harness components:

- `ScenarioRunner`: runs dataset cases, seeds, timeouts, and concurrency.
- `ProviderProxy`: records provider cassettes and enforces budgets.
- `ToolProxy`: records tool/MCP cassettes and validates schemas.
- `JudgeRunner`: routes model-dependent evals through judge broker.
- `ExperimentRunner`: runs baseline and candidate releases.
- `GateRunner`: converts persisted experiment reports into CI pass/fail. A gate
  run may target an explicit experiment run ID or the latest tenant/project
  report matching the gate's dataset/evaluator selectors; the gate-run report
  snapshots the gate definition, experiment gate policy, comparison, decision,
  and pass/fail reason.
- `HumanReviewRunner`: queues trace/span review tasks, stores human annotations,
  and promotes corrected human references into dataset cases through the same
  dataset store used by automated evals.
- `TraceEmitter`: emits canonical traces and raw refs.

The same harness must run locally, in CI, and in hosted workers.

## 12. Query, UI, and Alerting

Core UI requirements:

- trace table with project/environment/release filters
- span tree and waterfall
- agent turn/plan/step view
- MCP/tool-call visibility
- prompt/input/output/artifact inspector with redaction controls
- cost/token/latency analytics
- dataset promotion from trace/span
- experiment comparison
- eval result drilldown
- replay/cassette view
- human review queues
- failure clustering and root-cause annotations

Search:

- structured filters by status, time, trace ID, span kind, model, tool, cost,
  latency, token counts, environment, agent release, evaluator, and tags
- full-text search over inputs, outputs, errors, tool names, and selected attrs
  through Tantivy or equivalent
- natural-language search is later; fast structured search is v1

Alerting:

- online eval sampling policies
- baselines by project/environment/release
- dedupe and grouping
- maintenance windows
- Slack/webhook integrations
- alert budgets and suppression
- links back to trace clusters, dataset candidates, and gates

## 13. Compliance, Security, and Data Lifecycle

Data lifecycle:

- per-project retention policies
- hot ClickHouse -> cold Parquet -> delete
- referential consistency across rows, artifacts, cassettes, indexes, and exports
- orphan artifact sweeps
- restore drills before hosted GA

Deletion:

- immutable raw rows conflict with subject deletion unless encryption is designed
  correctly
- use envelope encryption with per-tenant keys and, where enterprise requires,
  per-subject data encryption keys
- deletion can be implemented as crypto-shredding plus deletion of lookup rows
  and object refs
- deleted data must become unreadable across hot, cold, and artifact stores

Security:

- API keys are scoped, rotatable, hashed, environment-bound, and audited
- PII unmask is a separate RBAC scope from ordinary trace read
- sensitive-data access emits audit events
- BYOK for judge/model providers
- encryption at rest for metadata, artifacts, cassettes, and cold files
- key rotation and key revocation workflows
- outbound webhooks use HMAC signatures, timestamp/replay protection, retries,
  and idempotency keys
- all tenant-scoped storage APIs take `TenantId` explicitly
- hosted cells enforce region/project pinning; PII does not cross regions

## 14. Public API and DX

DX SLO:

```text
time to first trace <= 5 minutes
```

Required onboarding paths:

- zero-SDK OTLP endpoint for any OpenInference/OpenLLMetry/OTel app
- native Rust SDK with `tracing`, `opentelemetry-rust`, `reqwest`, `axum`,
  `tonic`, MCP client/server, and tool-call helpers
- Python and TypeScript examples through standards-based OTLP first
- seeded demo project
- one-command Docker Compose
- copy/paste framework quickstarts
- `beaterctl smoke` to emit a known trace and verify ingestion

Public API:

- stable `/v1`
- OpenAPI-generated clients
- deprecation policy
- request IDs and idempotency keys
- pagination and time-bounded queries
- export endpoints for OTLP, Parquet, and JSONL
- import paths from Phoenix/LangSmith/Langfuse where feasible

No lock-in:

- export traces and evals without hosted dependency
- import existing datasets/traces
- keep raw source attributes for migration and round-trip use

## 15. Self-Observability SLOs

Beater dogfoods itself. Hosted cannot launch without dashboards and alerts for:

| Signal | Initial target |
| --- | --- |
| ingest accepted write success | >= 99.9 percent over 30 days |
| ingest-to-queryable lag p95 | <= 5s hosted hot path, <= 15s OSS compose |
| DLQ age p95 | <= 5m before alert |
| query p95 for indexed 24h searches | <= 1s for normal tenant workloads |
| query p95 for 30d filtered searches | <= 3s for normal tenant workloads |
| eval queue depth | bounded by project policy and worker count |
| judge spend | attributed to org/project/experiment/evaluator |
| artifact orphan rate | zero tolerated after sweeper window |
| tail-sampling decision lag p95 | <= trace completion target |

These numbers will change with load testing, but the product must expose them
from day one.

## 16. Execution Reality

### 16.1 Minimum Shippable OSS Product

The first serious open-source release needs all of this, not a smaller demo:

- Rust all-in-one `beaterd`
- OTLP and native ingest
- canonical trace schema
- immutable raw envelopes
- `TraceStore` abstraction
- SQLite/Postgres local mode
- ClickHouse scale backend
- artifact storage
- NATS JetStream durable bus
- trace table and span tree UI
- Rust SDK and tracing layer
- dataset creation from traces
- offline deterministic evals
- WASI evaluator ABI
- judge broker with BYOK
- experiment comparison with confidence intervals
- CI gate command
- Docker Compose
- import/export for OTLP, Parquet, and JSONL

That is the smallest version that can be called a serious OSS project.

### 16.2 Team Needed for Hosted SOTA

A solo founder can ship a focused OSS MVP, but not a hosted SOTA platform quickly.
The realistic team is:

- Rust infra lead
- backend/product engineer
- frontend/product engineer
- data/observability engineer
- evals/agent-systems engineer
- infra/security engineer part-time early and full-time before hosted GA

### 16.3 Hardest Problems

The hard parts are not CRUD:

- schema evolution without breaking old traces
- multi-tenant privacy and artifact security
- accurate standards translation
- ingest survivability during storage outages and traffic spikes
- evaluator reproducibility
- judge reliability and calibration
- replay correctness
- query speed over high-cardinality span volumes
- UX that makes agent failures obvious
- open-core trust and governance

## 17. Milestones

### v0: Substrate

Acceptance:

- `beaterd` starts as one binary.
- OTLP HTTP/gRPC and native ingest accept traces.
- Raw envelopes and canonical projections are both stored.
- `TraceStore` exists with SQL and ClickHouse implementations.
- NATS JetStream buffers writes and DLQ paths are visible.
- A seeded demo trace renders in the UI.
- `beaterctl smoke` proves time-to-first-trace.

### v1: OSS Observability and Offline Evals

Acceptance:

- trace table, span tree, waterfall, and agent step views work
- dataset promotion from trace/span works
- deterministic evals run in WASI sandbox
- judge broker runs BYOK LLM evals
- experiments compare baseline vs candidate with confidence intervals
- CI gate blocks regressions
- Docker Compose is the supported self-host path

### v2: Agent-Native Debugging

Acceptance:

- replay cassettes support deterministic replay where complete
- forked replay and simulation are labeled honestly
- root-cause attribution identifies the earliest likely failing span on seeded
  multi-step agent failures
- human review queues feed datasets
- online eval sampling and alert grouping work
- MCP/tool/memory spans are first-class

### v3: Hosted GA

Acceptance:

- Vercel-hosted dashboard and Rust control-plane functions
- hosted Rust cells for ingest/eval/replay
- org/project/environment isolation
- quotas, rate limits, billing ledger, and usage metering
- retention, crypto-shredding, data residency, audit, BYOK, and key rotation
- backups and restore drills
- SLO dashboards
- Slack/webhook alerts
- regional deployment story

## 18. Bar for Done

The platform is real when a team can replace ad hoc Phoenix, LangSmith,
Braintrust, and spreadsheet workflows and answer:

- What did my agent do?
- Why did it fail?
- Has this happened before?
- Can I reproduce it?
- Can I test the fix?
- Did the fix regress anything?
- Can I block deploys on that?
- Can I monitor it in production?
- Can I self-host without calling your cloud?

If any answer is no, that area is not shipped.
