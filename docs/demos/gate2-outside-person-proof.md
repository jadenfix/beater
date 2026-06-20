# Gate 2 Outside-Person Proof

Status: not yet completed.

Gate 2 is not passed until this file is replaced with evidence from a person
outside the project who runs the flow unaided from a fresh clone.

## Runner

- Name:
- Organization or relationship to project:
- Prior Beater repo exposure: none / describe:
- Date:
- Machine and OS:
- Docker version:
- Docker Compose version:
- Browser:
- Network notes:

## Repository

- Clone URL: `https://github.com/jadenfix/beater.git`
- Commit SHA:
- Branch:
- OS/arch:
- Beater image digest:
- Dashboard image digest:
- Started at:
- Ended at:
- Time-to-first-trace:
- Time-to-quickstart-click:
- Total proof duration:

## Commands

```bash
git clone https://github.com/jadenfix/beater.git
cd beater
BEATER_GATE2_WRITE_PROOF=1 BEATER_GATE2_BROWSER_PROOF=1 scripts/gate2-compose-stopwatch.sh
```

No project maintainer may provide step-by-step help beyond public repo docs
during the timed run.

After the script prints the dashboard URLs, the runner must open
`http://127.0.0.1:3000` in a normal browser, click the quickstart trace, click
the `llm.call` span, and capture the evidence below. Cleanup can happen after
the recording.

## Required Evidence

- Stopwatch proof file:
- Screen recording:
- Screen recording SHA256:
- Terminal output excerpt:
- `docker compose images` excerpt:
- Quickstart trace ID:
- Quickstart dashboard URL: `http://127.0.0.1:3000/...`
- All-kind nested trace ID:
- All-kind dashboard URL: `http://127.0.0.1:3000/...`
- `docker compose` logs saved:
- Failure notes, if any:

## Pass Checklist

- [ ] Fresh clone was used.
- [ ] Default ports were used: API `127.0.0.1:8080`, OTLP `127.0.0.1:4317`,
      dashboard `127.0.0.1:3000`.
- [ ] `BEATER_GATE2_REUSE` was not set.
- [ ] The script reported `Clean start: yes`.
- [ ] Time-to-first-trace was 300 seconds or less.
- [ ] Time-to-quickstart-click was 300 seconds or less.
- [ ] The five-line stock OpenTelemetry trace appeared in `localhost:3000`.
- [ ] Clicking the `llm.call` span showed prompt, completion, model, tokens,
      cost, and latency.
- [ ] The all-kind trace rendered run -> turn -> step -> tool -> MCP nesting in
      the waterfall.
- [ ] The browser proof passed for both the quickstart trace and all-kind
      waterfall.
- [ ] A screen recording of the full flow is committed under `docs/demos/`.
- [ ] The runner completed the flow using only public repository instructions.

## Runner Notes

Add any confusing step, missing prerequisite, slow pull, failing command, or UI
ambiguity here. These notes are blocking feedback until fixed or explicitly
triaged.
