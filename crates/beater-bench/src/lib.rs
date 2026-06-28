//! `beater-bench` — criterion benchmarks and load-test fixtures for Beater.
//!
//! # Purpose
//!
//! This crate is the home for all performance evidence required by the Tech Rider
//! (§23.10) and the §20.2 gap-closure plan.  Specifically it targets the §20.2 #0.3
//! acceptance criterion: *criterion benches for `write_batch` throughput and
//! `query_*` latency on seeded 1 M / 10 M / 100 M-span fixtures, meeting the §16
//! SLOs in CI*.
//!
//! Nothing in this crate is wired into `beaterd` or any runtime path.  It exists
//! solely to give future bench + load-test work a stable home with the right
//! Cargo plumbing already in place.
//!
//! # Architecture references
//!
//! * **§16** — Self-Observability SLOs (the target numbers benches gate on).
//! * **§20.2 #0.3** — "Measured query p95 SLOs" gap-closure item; the `backend`
//!   Metronome CI gate that runs `cargo bench -p beater-bench`.
//! * **§23.10** — Perf observability + SLO gates (Heartbeat + Tech Rider); describes
//!   the advisory → required promotion path for this bench gate.
//!
//! # Layout
//!
//! ```text
//! crates/beater-bench/
//!   src/lib.rs          — this file; shared helpers / load-fixture builders
//!   benches/smoke.rs    — trivial smoke bench (verifies harness compiles & links)
//!   benches/store.rs    — [planned] write_batch throughput + query_* latency benches
//!                         on in-memory / SQLite / Postgres / ClickHouse backends
//! ```
//!
//! # Adding a new bench
//!
//! 1. Add a `[[bench]]` entry in `Cargo.toml` with `harness = false`.
//! 2. Import `criterion::{criterion_group, criterion_main, Criterion}`.
//! 3. Use [`span_batch`] / [`seed_store`] (planned helpers below) to get fixtures.
//! 4. Wire the SLO assertion as a `criterion` throughput target or a custom
//!    post-bench assertion so CI fails on regression.

/// Placeholder for a seeded span-batch fixture builder.
///
/// Future implementation will produce `n` synthetic [`beater_schema::CanonicalSpan`]
/// objects spread across a configurable time window, suitable for seeding any
/// [`beater_store::TraceStore`] backend and then running `query_spans` /
/// `query_runs` latency measurements against it.
///
/// # Arguments
///
/// * `n` — number of spans to generate.
///
/// # Returns
///
/// An opaque `Vec` of serialised spans (type will harden once this is wired).
pub fn span_batch_placeholder(n: usize) -> Vec<u8> {
    // Intentionally trivial until store deps are wired in (§20.2 #0.3).
    // Returns a zero-filled sentinel so callers can size buffers proportionally.
    vec![0u8; n]
}
