# Beater SDKs

Every SDK, the MCP server, the CLI, and the docs derive from **one** artifact:
[`sdks/openapi/beater-api.json`](openapi/beater-api.json), generated from the
Rust API handlers. This is what makes drift structurally impossible.

```
crates/beater-api handlers  (#[utoipa::path] + ToSchema on the real types)
            │  cargo run --example dump_openapi
            ▼
   sdks/openapi/beater-api.json   ← THE single source of truth
   ├── sdks/clients/<lang>/   7 generated control-plane clients (Layer 1)
   ├── /mcp tools             one tool per operationId
   ├── beater api <op>        CLI generic invoker
   └── web/dashboard /docs    rendered API reference + tool catalog
```

## Two layers

**Layer 1 — generated control-plane clients** (`sdks/clients/<lang>/`): typed
CRUD against `/v1` (datasets, experiments, gates, evals, judge, usage, audit,
api-keys, traces read, …). Generated for **rust, python, typescript, go, java,
c, cpp** by [`openapi-generator`](https://openapi-generator.tech) from the spec.
Resource **tags** become API classes and `removeOperationIdPrefix` yields clean
methods — e.g. `datasets_create` → `DatasetsApi.create()`.

**Layer 2 — hand-written ergonomic SDKs** (`sdks/<lang>/`): the "nice wrappers" —
`init()`, the `@observe`/`observe()` decorators, drop-in `wrap_openai()` /
`wrap_anthropic()`, and LangChain/LlamaIndex callbacks. Built on OpenTelemetry
(ingest is OTLP). Span kinds and attribute keys live in one `semconv` module per
language that mirrors the server normalizer (`crates/beater-otlp`).

| Language | Layer 1 (generated) | Layer 2 (ergonomic) |
| --- | --- | --- |
| Python | `sdks/clients/python` (`beater_client`) | `sdks/python` (`beater-sdk`) ✅ |
| TypeScript | `sdks/clients/typescript` (`@beater/client`) | `sdks/typescript` (`@beater/sdk`) ✅ |
| Rust | `sdks/clients/rust` (`beater-client`) | (uses Layer 1 + tracing) |
| Go / Java / C / C++ | `sdks/clients/{go,java,c,cpp}` | tracing helpers (planned) |

## Generation status

All 7 Layer-1 clients **generate** from the spec, with correct tag-namespaced
shapes (verified: Go emits `DatasetsAPIService.Create()`, one API class per tag).
Compile-clean status per toolchain:

| Target | Generates | Compiles clean | Note |
| --- | --- | --- | --- |
| go, typescript, python, java | ✅ | ✅ (expected) | permissive `oneOf` handling |
| rust, cpp | ✅ | ⚠️ needs polish | the `EvaluatorKind` mixed `oneOf` (string + object variants) trips the Rust/C++ enum templates; fix via a mustache template override or a flatter contract shape for mixed `oneOf` enums |

## Regenerating (zero-drift)

```bash
scripts/regen-sdks.sh          # regenerate spec + all 7 clients
scripts/regen-sdks.sh --check  # CI mode: fail if anything is stale
```

Requires Docker (the generator runs in the pinned
`openapitools/openapi-generator-cli` image — no local Java needed). CI runs
`--check` so a handler change that isn't regenerated cannot merge, and `oasdiff`
blocks breaking contract changes. On release, all packages bump to one
synchronized version and publish together.
