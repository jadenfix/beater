use std::process::Command;

#[test]
fn gate_run_exits_nonzero_for_latest_regression() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let fixture = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("gate-run-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;
    assert!(
        fixture.status.success(),
        "fixture stderr: {}",
        String::from_utf8_lossy(&fixture.stderr)
    );

    let gate_run = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("gate-run")
        .arg("--data-dir")
        .arg(tempdir.path())
        .arg("--tenant-id")
        .arg("demo")
        .arg("--project-id")
        .arg("demo")
        .arg("--gate-id")
        .arg("main")
        .output()?;

    assert!(
        !gate_run.status.success(),
        "gate run should fail on latest regression"
    );
    let stdout = String::from_utf8(gate_run.stdout)?;
    assert!(stdout.contains(r#""passed": false"#));
    assert!(stdout.contains(r#""experiment_run_id": "gate-latest-fail""#));
    Ok(())
}
