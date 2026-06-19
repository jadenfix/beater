use std::process::Command;

#[test]
fn calibration_fixture_persists_judge_human_agreement_report() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let output = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("calibration-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;

    assert!(
        output.status.success(),
        "calibration fixture stderr: {}",
        String::from_utf8_lossy(&output.stderr)
    );
    let stdout = String::from_utf8(output.stdout)?;
    assert!(stdout.contains(r#""sample_count": 4"#));
    assert!(stdout.contains(r#""cohen_kappa": 0.5"#));
    assert!(stdout.contains(r#""human_fail_judge_pass": 1"#));
    assert!(!stdout.contains("sk-local-calibration-judge-secret"));
    Ok(())
}
