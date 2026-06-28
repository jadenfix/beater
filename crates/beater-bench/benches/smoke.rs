//! Smoke benchmark — verifies the criterion harness compiles, links, and runs.
//!
//! This bench measures a trivially cheap operation so that:
//! - `cargo bench -p beater-bench --no-run` succeeds in CI (§22 `backend` gate).
//! - The criterion HTML report plumbing is exercised end-to-end.
//!
//! Replace or supplement this bench with real store-level measurements in a
//! future `benches/store.rs` (§20.2 #0.3).

use beater_bench::span_batch_placeholder;
use criterion::{black_box, criterion_group, criterion_main, Criterion};

fn bench_span_batch_placeholder(c: &mut Criterion) {
    c.bench_function("span_batch_placeholder/1k", |b| {
        b.iter(|| span_batch_placeholder(black_box(1_000)))
    });
}

criterion_group!(benches, bench_span_batch_placeholder);
criterion_main!(benches);
