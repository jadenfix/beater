use std::process::Command;

#[test]
fn review_fixture_promotes_human_annotation_to_eval_ready_dataset() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let output = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("review-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;

    assert!(
        output.status.success(),
        "review fixture stderr: {}",
        String::from_utf8_lossy(&output.stderr)
    );
    let stdout = String::from_utf8(output.stdout)?;
    assert!(stdout.contains(r#""verdict": "pass""#));
    assert!(stdout.contains(r#""reference": {"#));
    assert!(stdout.contains(r#""aggregate_score": 1.0"#));
    Ok(())
}
