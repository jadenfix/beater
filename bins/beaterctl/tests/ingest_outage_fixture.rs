use std::process::Command;

#[test]
fn ingest_outage_fixture_buffers_retries_and_recovers() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let output = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("ingest-outage-fixture")
        .arg("--data-dir")
        .arg(tempdir.path())
        .output()?;

    assert!(
        output.status.success(),
        "fixture failed\nstdout:\n{}\nstderr:\n{}",
        String::from_utf8_lossy(&output.stdout),
        String::from_utf8_lossy(&output.stderr)
    );
    let stdout = String::from_utf8(output.stdout)?;
    assert!(stdout.contains(r#""retried": 1"#));
    assert!(stdout.contains(r#""written_spans": 1"#));
    assert!(stdout.contains(r#""trace_span_count": 1"#));
    assert!(stdout.contains(r#""trace_ingested_depth": 1"#));
    Ok(())
}
