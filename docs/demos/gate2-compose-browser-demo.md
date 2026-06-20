# Gate 2 Compose Browser Demo

Recorded from the Docker Compose stopwatch path using the literal five-line
stock OpenTelemetry quickstart and the all-kind stock OpenTelemetry agent trace.

- Artifact: `gate2-compose-browser-demo.webm`
- SHA256: `011b41bcad6d2cd6ba982dd457b3da445a82b140d5d89b16adfd4836c2db0251`
- Dashboard base: `http://127.0.0.1:13080`
- Quickstart trace: `5daf8b3430985d346f1ea272bc8f579c`
- All-kind trace: `42215a4443efb0b4907da0a3ae06405c`
- Shows: open dashboard -> click five-line trace -> click `llm.call` span -> read prompt, completion, model, tokens, cost, and latency -> inspect run -> turn -> step -> tool -> MCP waterfall.

Regenerate with:

```bash
BEATER_GATE2_WRITE_PROOF=1 BEATER_GATE2_BROWSER_PROOF=1 BEATER_GATE2_RECORD_DEMO=1 scripts/gate2-compose-stopwatch.sh
```

The mandate still requires the outside-person run recorded in
`docs/demos/gate2-outside-person-proof.md` before Gate 2 can close.
