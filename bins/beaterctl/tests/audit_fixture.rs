use std::process::Command;

#[test]
fn audit_fixture_persists_pii_unmask_events() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let output = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("audit-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;

    assert!(
        output.status.success(),
        "audit fixture stderr: {}",
        String::from_utf8_lossy(&output.stderr)
    );
    let stdout = String::from_utf8(output.stdout)?;
    assert!(stdout.contains(r#""action": "pii_unmask""#));
    assert!(stdout.contains(r#""outcome": "denied""#));
    assert!(stdout.contains(r#""outcome": "allowed""#));
    assert!(stdout.contains(r#""reason": "incident-123""#));
    Ok(())
}
