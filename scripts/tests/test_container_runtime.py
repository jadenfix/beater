#!/usr/bin/env python3
from __future__ import annotations

import os
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "scripts" / "container-runtime.sh"


def write_executable(path: Path, body: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(body)
    path.chmod(0o755)


def run_bash(command: str, *, path: Path | None = None, env: dict[str, str] | None = None):
    merged_env = os.environ.copy()
    if env:
        merged_env.update(env)
    if path is not None:
        merged_env["PATH"] = f"{path}{os.pathsep}{merged_env['PATH']}"
    return subprocess.run(
        ["bash", "-c", f"source {SCRIPT}; {command}"],
        cwd=ROOT,
        env=merged_env,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )


def test_explicit_runtime_does_not_require_cli_detection() -> None:
    result = run_bash("crt_cli", env={"BEATER_CONTAINER_RUNTIME": "container"})

    assert result.returncode == 0, result.stderr
    assert result.stdout.strip() == "container"


def test_auto_detection_prefers_docker_when_both_runtimes_exist() -> None:
    with tempfile.TemporaryDirectory() as temp:
        bin_dir = Path(temp)
        write_executable(bin_dir / "docker", "#!/usr/bin/env bash\nexit 0\n")
        write_executable(bin_dir / "container", "#!/usr/bin/env bash\nexit 0\n")

        result = run_bash("crt_cli", path=bin_dir, env={"BEATER_CONTAINER_RUNTIME": ""})

    assert result.returncode == 0, result.stderr
    assert result.stdout.strip() == "docker"


def test_docker_ensure_up_reports_stopped_daemon() -> None:
    with tempfile.TemporaryDirectory() as temp:
        bin_dir = Path(temp)
        write_executable(
            bin_dir / "docker",
            """#!/usr/bin/env bash
if [ "$1" = "info" ]; then
  exit 1
fi
exit 0
""",
        )

        result = run_bash("crt_ensure_up", path=bin_dir, env={"CRT": "docker"})

    assert result.returncode == 1
    assert "docker daemon not running" in result.stderr


def test_container_address_uses_inspect_address() -> None:
    with tempfile.TemporaryDirectory() as temp:
        bin_dir = Path(temp)
        write_executable(
            bin_dir / "container",
            """#!/usr/bin/env bash
if [ "$1" = "inspect" ]; then
  printf '{"network":{"address":"10.88.0.42"}}\n'
  exit 0
fi
exit 0
""",
        )

        result = run_bash(
            "crt_address beaterd-local 8080",
            path=bin_dir,
            env={"CRT": "container"},
        )

    assert result.returncode == 0, result.stderr
    assert result.stdout.strip() == "10.88.0.42:8080"


def main() -> None:
    for test in (
        test_explicit_runtime_does_not_require_cli_detection,
        test_auto_detection_prefers_docker_when_both_runtimes_exist,
        test_docker_ensure_up_reports_stopped_daemon,
        test_container_address_uses_inspect_address,
    ):
        test()
    print("container-runtime tests passed")


if __name__ == "__main__":
    main()
