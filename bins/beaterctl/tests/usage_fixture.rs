use std::process::Command;

#[test]
fn usage_fixture_meters_judge_spend_idempotently() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let output = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("usage-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;

    assert!(
        output.status.success(),
        "usage fixture stderr: {}",
        String::from_utf8_lossy(&output.stderr)
    );
    let stdout = String::from_utf8(output.stdout)?;
    assert!(stdout.contains(r#""judge_cost_micros": {"#));
    assert!(stdout.contains(r#""quantity": 25"#));
    assert!(stdout.contains(r#""charged_cost": {"#));
    assert!(stdout.contains(r#""amount_micros": 0"#));
    assert!(!stdout.contains("sk-local-usage-judge-secret"));
    Ok(())
}
