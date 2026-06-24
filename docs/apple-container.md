# Running Beater on Apple `container` or Docker

Beater builds and runs on either [Docker](https://www.docker.com/) or Apple's
native [`container`](https://github.com/apple/container) runtime (Apple silicon,
macOS 26+). The same `Dockerfile` is used for both — Apple `container build` is
BuildKit-compatible.

## Pick a runtime

A small shim, `scripts/container-runtime.sh`, abstracts the differences. Select
the runtime explicitly or let it auto-detect (prefers Docker when both exist):

```bash
export BEATER_CONTAINER_RUNTIME=container   # or: docker
```

## Build

```bash
scripts/build-image.sh beaterd:local
```

## Run

```bash
scripts/run-beaterd.sh beaterd:local
# prints the reachable address and waits for /health
```

Docker publishes the port to `127.0.0.1:8080`. Apple `container` gives each
container its own IP, so `run-beaterd.sh` resolves the address via
`container inspect` and prints it.

## Differences the shim handles

| Concern | Docker | Apple `container` |
| --- | --- | --- |
| Daemon | Docker Desktop / `dockerd` | `container system start` (auto-run by the shim) |
| Build | `docker build` | `container build` (same Dockerfile) |
| Networking | `-p host:guest` to localhost | per-container IP (`crt_address` resolves it) |
| Compose | `docker-compose.yml` supported | no compose — use `scripts/run-beaterd.sh` |

## CI

`.github/workflows/apple-container-build.yml` installs Apple `container` on an
Apple-silicon macOS runner, builds the image, and smoke-runs `beaterd` — proving
the Docker and Apple-container build paths stay in lockstep.

## Notes

- Apple `container` requires **macOS 26 on Apple silicon**.
- Multi-container topologies that use `docker-compose.yml` today run as before on
  Docker; on Apple `container` launch services individually (the single
  `beaterd` service is covered by `run-beaterd.sh`). Compose-equivalent
  orchestration for Apple `container` can be added when it ships native support.
