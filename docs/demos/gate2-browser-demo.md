# Gate 2 Browser Demo

Recorded from the stock OpenTelemetry Python trace produced by `examples/python/otel_smoke.py`.

- Artifact: `gate2-browser-demo.webm`
- Dashboard: `http://127.0.0.1:13003/?tenant=demo&project=demo&environment=local&trace=4a71a620e5f09a4193bf8cab2a3b4427`
- Shows: trace table, color/icon-coded all-kind agent waterfall, run -> turn -> step -> tool -> MCP nesting, `llm.call` prompt/completion/model/tokens/cost/latency, and tool-call I/O.

Regenerate with:

```bash
BEATER_GATE2_RECORD_DEMO=1 scripts/gate2-proof.sh
```

For the Docker Compose stopwatch proof that uses the literal five-line snippet,
run the prebuilt-image path:

```bash
BEATER_GATE2_WRITE_PROOF=1 KEEP_BEATER_COMPOSE=0 scripts/gate2-compose-stopwatch.sh
```

For a local source build measurement, add `BEATER_GATE2_LOCAL_BUILD=1`.
