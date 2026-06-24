//! Integration test for the `beaterctl secret-rotate` operator entrypoint (R9.3):
//! it must re-wrap stored provider secrets onto a new active key while keeping the
//! retiring key available to decrypt the rows it is migrating.

use beater_secrets::SecretEncryptionKey;
use std::fs;
use std::process::Command;

#[test]
fn secret_rotate_rewraps_stored_secrets_onto_the_new_active_key() -> anyhow::Result<()> {
    let tempdir = tempfile::tempdir()?;
    let data_dir = tempdir.path();

    // Seed a provider secret encrypted under the default key (`local-v1`). The
    // judge fixture creates the key file and writes one encrypted secret row.
    let seed = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("judge-fixture")
        .arg("--data-dir")
        .arg(data_dir)
        .output()?;
    assert!(
        seed.status.success(),
        "seed fixture failed\nstdout:\n{}\nstderr:\n{}",
        String::from_utf8_lossy(&seed.stdout),
        String::from_utf8_lossy(&seed.stderr)
    );

    // The retiring key is whatever the fixture wrote to the key file.
    let key_path = data_dir.join("provider-secrets.key");
    let retiring_base64 = fs::read_to_string(&key_path)?.trim().to_string();

    // Promote a brand-new key to active by overwriting the key file with v2.
    let new_key = SecretEncryptionKey::generate("local-v2")?;
    fs::write(&key_path, format!("{}\n", new_key.to_base64()))?;

    // Rotate: re-wrap the v1 row under v2, supplying v1 as the retiring key so the
    // row can still be decrypted.
    let rotate = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("secret-rotate")
        .arg("--data-dir")
        .arg(data_dir)
        .arg("--active-key-id")
        .arg("local-v2")
        .arg("--retiring-key-base64")
        .arg(&retiring_base64)
        .arg("--retiring-key-id")
        .arg("local-v1")
        .output()?;
    assert!(
        rotate.status.success(),
        "rotate failed\nstdout:\n{}\nstderr:\n{}",
        String::from_utf8_lossy(&rotate.stdout),
        String::from_utf8_lossy(&rotate.stderr)
    );
    let stdout = String::from_utf8(rotate.stdout)?;
    assert!(
        stdout.contains(r#""active_key_id": "local-v2""#),
        "unexpected rotate output:\n{stdout}"
    );
    assert!(
        stdout.contains(r#""rotated_rows": 1"#),
        "expected exactly one re-wrapped row:\n{stdout}"
    );
    assert!(
        stdout.contains("no concurrent writers"),
        "rotation output must surface the no-concurrent-writers requirement:\n{stdout}"
    );

    // Idempotent: a second rotation under the same active key re-wraps nothing.
    let again = Command::new(env!("CARGO_BIN_EXE_beaterctl"))
        .arg("secret-rotate")
        .arg("--data-dir")
        .arg(data_dir)
        .arg("--active-key-id")
        .arg("local-v2")
        .output()?;
    assert!(
        again.status.success(),
        "second rotate failed\nstdout:\n{}\nstderr:\n{}",
        String::from_utf8_lossy(&again.stdout),
        String::from_utf8_lossy(&again.stderr)
    );
    let stdout = String::from_utf8(again.stdout)?;
    assert!(
        stdout.contains(r#""rotated_rows": 0"#),
        "second rotation should be a no-op:\n{stdout}"
    );

    Ok(())
}
