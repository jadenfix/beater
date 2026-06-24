# Beater Rust SDK

Ergonomic, OpenTelemetry-native agent observability for [Beater](https://github.com/beater/beater).

This is the **Layer 2** (hand-written, ergonomic) SDK — a thin, idiomatic
wrapper over the OpenTelemetry API, mirroring the Python (`sdks/python`) and
TypeScript (`sdks/typescript`) SDKs. It exposes `init`, `observe`, `span`,
`set_input`/`set_output`, and a shared `semconv` module kept in lockstep with the
server normalizer in `crates/beater-otlp`.

## Quickstart (5 lines)

```rust
use beater::{span_kind, BeaterConfig};

beater::init(BeaterConfig::from_env());                       // OTLP/HTTP -> beaterd
let out = beater::observe("handle", span_kind::AGENT_RUN, || {
    beater::set_input("user query");                         // input.value
    beater::set_output("done");                              // output.value
    "done"
});
beater::shutdown();                                           // flush before exit
```

All `BeaterConfig` fields fall back to `BEATER_*` env vars
(`BEATER_BASE_URL` default `http://127.0.0.1:8080`, `BEATER_TENANT_ID`/
`BEATER_PROJECT_ID`/`BEATER_ENVIRONMENT_ID` default `demo`/`demo`/`local`,
`BEATER_API_KEY`, `BEATER_SERVICE_NAME`, `BEATER_RELEASE_ID`), so
`BeaterConfig::from_env()` works with no explicit args.

## API

- `init(config)` — wire up an OTLP/HTTP (protobuf) exporter pointed at
  `{base}/v1/otlp/{tenant}/{project}/{environment}/v1/traces` and install it as
  the global tracer.
- `observe(name, kind, f)` / `observe_async(name, kind, fut).await` — run a
  closure/future inside a Beater span, setting `openinference.span.kind`,
  `beater.seq`, and `agent.release_id`, then mark status OK.
- `span(name, kind)` — open a span as an RAII guard; call `set_input`/
  `set_output`/`set_attribute`/`ok`/`error` on it; the span ends on drop.
- `set_input(v)` / `set_output(v)` / `set_attribute(k, v)` — operate on the
  current span.
- `flush()` / `shutdown()` — flush pending spans before a short-lived program
  exits.
- `span_kind` / `attr` — the 11 span kinds and canonical attribute keys.

## Example

```sh
BEATER_TENANT_ID=demo BEATER_PROJECT_ID=demo BEATER_ENVIRONMENT_ID=local \
    cargo run --example quickstart
```

Emits an `agent.run -> agent.plan -> llm.call` trace.
