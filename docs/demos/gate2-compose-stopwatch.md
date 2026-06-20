# Gate 2 Compose Stopwatch Proof

- Timing start source: script
- Clone started at: not provided
- Script started at: 2026-06-20T20:16:16Z
- Started: 2026-06-20T20:16:16Z
- Ended: 2026-06-20T20:17:35Z
- Time-to-first-trace: 29s
- Script-to-first-trace: 29s
- Time-to-quickstart-click: 40s
- Script-to-quickstart-click: 40s
- Total duration: 79s
- Script duration: 79s
- Limit: 300s
- Git SHA: `7298707d450007ee5135caab7c4a08c727d6744c`
- Git branch: `main`
- Git origin: `https://github.com/jadenfix/beater.git`
- Git worktree clean: yes
- OS/arch: `Darwin arm64`
- Docker: `Docker version 29.2.0, build 0b9d198`
- Docker Compose: `Docker Compose version v5.0.2`
- Startup mode: prebuilt-image
- Clean start: yes
- Reuse override: `BEATER_GATE2_REUSE=0`
- Outside-run wrapper: no
- Prebuilt pull policy: `always`
- Compose project: beater-stopwatch
- Beater image reference: `ghcr.io/jadenfix/beater/beaterd:7298707d450007ee5135caab7c4a08c727d6744c`
- Dashboard image reference: `ghcr.io/jadenfix/beater/dashboard:7298707d450007ee5135caab7c4a08c727d6744c`
- Dashboard e2e image reference: `ghcr.io/jadenfix/beater/dashboard-e2e:7298707d450007ee5135caab7c4a08c727d6744c`
- OTEL Python image reference: `ghcr.io/jadenfix/beater/otel-python:7298707d450007ee5135caab7c4a08c727d6744c`
- Beater image digest: `ghcr.io/jadenfix/beater/beaterd@sha256:ba70ab0487bd4d0ae52a5b39323a360c06a4a5361e4af5f517ebd7b01b5337d8`
- Dashboard image digest: `ghcr.io/jadenfix/beater/dashboard@sha256:0569ca50316d912ff4dc3437b2978de3a4013dee287cbf6acb2dde1d661ba838`
- Dashboard e2e image digest: `ghcr.io/jadenfix/beater/dashboard-e2e@sha256:fd97d7c50e85794e87398d20fbcb3747d42772ff9dfa869e9f58ef24daeaa1f7`
- OTEL Python image digest: `ghcr.io/jadenfix/beater/otel-python@sha256:29b91431cc45713d80474972a4540fe7250fbdb0717f9a292741168639c0c192`
- Quickstart snippet: `examples/python/five_line_otel.py`
- API endpoint: `http://127.0.0.1:18080`
- OTLP endpoint: `http://127.0.0.1:14318`
- Dashboard base: `http://127.0.0.1:13080`
- Quickstart trace: `5daf8b3430985d346f1ea272bc8f579c`
- Quickstart dashboard: http://127.0.0.1:13080/?tenant=demo&project=demo&environment=local&trace=5daf8b3430985d346f1ea272bc8f579c
- Quickstart browser proof: passed
- All-kind nested trace: `42215a4443efb0b4907da0a3ae06405c`
- All-kind dashboard: http://127.0.0.1:13080/?tenant=demo&project=demo&environment=local&trace=42215a4443efb0b4907da0a3ae06405c
- All-kind waterfall browser proof: passed
- Browser recording: passed
- Browser recording artifact: `docs/demos/gate2-compose-browser-demo.webm`
- Browser recording notes: `docs/demos/gate2-compose-browser-demo.md`
- Browser recording SHA256: `011b41bcad6d2cd6ba982dd457b3da445a82b140d5d89b16adfd4836c2db0251`

## Compose Images

```text
CONTAINER                      REPOSITORY                          TAG                                        PLATFORM            IMAGE ID            SIZE                CREATED
beater-stopwatch-beaterd-1     ghcr.io/jadenfix/beater/beaterd     7298707d450007ee5135caab7c4a08c727d6744c   linux/arm64         ba70ab0487bd        88.4MB              9 hours ago
beater-stopwatch-dashboard-1   ghcr.io/jadenfix/beater/dashboard   7298707d450007ee5135caab7c4a08c727d6744c   linux/arm64         0569ca50316d        99.2MB              7 minutes ago
beater-stopwatch-minio-1       minio/minio                         latest                                     linux/arm64         14cea493d9a3        57.5MB              9 months ago
beater-stopwatch-nats-1        nats                                2.11-alpine                                linux/arm64/v8      e4bf19f15fd3        10.5MB              7 weeks ago
beater-stopwatch-postgres-1    postgres                            17-alpine                                  linux/arm64/v8      dc17045ccfd3        115MB               3 days ago
```

This is an automated local stopwatch proof. The mandate still requires an
outside-person run to fully close Gate 2.

Regenerate:

```bash
BEATER_GATE2_WRITE_PROOF=1 BEATER_GATE2_BROWSER_PROOF=1 BEATER_GATE2_RECORD_DEMO=1 scripts/gate2-compose-stopwatch.sh
```
