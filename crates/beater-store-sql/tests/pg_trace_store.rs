//! Live Postgres `TraceStore` conformance.
//!
//! Boots a throwaway Postgres container, runs the checked-in migration, and runs
//! the shared store-conformance suite against `PgTraceStore`. The test is
//! `#[ignore]`d so a Docker-less `cargo test` still passes; run it explicitly on
//! a Docker CI runner with:
//!
//! ```sh
//! cargo test -p beater-store-sql --test pg_trace_store -- --ignored
//! ```

#![cfg(feature = "postgres")]

use beater_store_conformance::assert_trace_store_conformance;
use beater_store_sql::PgTraceStore;
use testcontainers::{
    core::{IntoContainerPort, WaitFor},
    runners::AsyncRunner,
    GenericImage, ImageExt,
};

#[tokio::test]
#[ignore = "requires Docker; run with --ignored on a Docker CI runner"]
async fn pg_trace_store_conforms() {
    let container = GenericImage::new("postgres", "16-alpine")
        .with_wait_for(WaitFor::message_on_stderr(
            "database system is ready to accept connections",
        ))
        .with_exposed_port(5432.tcp())
        .with_env_var("POSTGRES_USER", "beater")
        .with_env_var("POSTGRES_PASSWORD", "beater")
        .with_env_var("POSTGRES_DB", "beater")
        .start()
        .await
        .unwrap_or_else(|err| panic!("start postgres container: {err}"));

    let host = container
        .get_host()
        .await
        .unwrap_or_else(|err| panic!("container host: {err}"));
    let port = container
        .get_host_port_ipv4(5432)
        .await
        .unwrap_or_else(|err| panic!("container port: {err}"));
    let connection_string =
        format!("host={host} port={port} user=beater password=beater dbname=beater");

    let store = PgTraceStore::connect(&connection_string)
        .await
        .unwrap_or_else(|err| panic!("connect/migrate postgres: {err}"));

    assert_trace_store_conformance(store).await;
}
