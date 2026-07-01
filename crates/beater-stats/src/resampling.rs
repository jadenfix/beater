//! Shared bootstrap-resampling core.
//!
//! Every bootstrap routine in this crate (percentile difference, BCa, paired,
//! clustered) resamples the same way: draw `n_resamples` replicates, then read
//! percentile endpoints off the replicate distribution. Centralising that here
//! gives all of them the same three properties for free:
//!
//! * **Reproducible & order-independent** — each replicate is a pure function of
//!   its index (seed the RNG with [`crate::Xorshift64::for_resample`]), so the
//!   result never depends on evaluation order.
//! * **Parallel when it helps** — under the default-on `parallel` feature the
//!   replicates are evaluated across cores; `into_par_iter().map().collect()`
//!   preserves index order, so the parallel and sequential paths are
//!   bit-identical.
//! * **Endpoint extraction without a full sort** — only the two percentile order
//!   statistics are quickselected (expected `O(n_resamples)`), not the whole
//!   sorted distribution (`O(n_resamples log n_resamples)`).

/// Evaluate `replicate(i)` for `i in 0..n_resamples` and collect the results.
///
/// `replicate` must be a pure function of the index (all randomness derived from
/// `i` via [`crate::Xorshift64::for_resample`]) so the sequential and parallel
/// paths agree. Runs across cores under the `parallel` feature.
pub(crate) fn replicates<F>(n_resamples: usize, replicate: F) -> Vec<f64>
where
    F: Fn(usize) -> f64 + Sync + Send,
{
    #[cfg(feature = "parallel")]
    {
        use rayon::prelude::*;
        (0..n_resamples).into_par_iter().map(replicate).collect()
    }
    #[cfg(not(feature = "parallel"))]
    {
        (0..n_resamples).map(replicate).collect()
    }
}

/// The percentile order statistics at `lo_idx` and `hi_idx` (with
/// `lo_idx <= hi_idx`), extracted by quickselect. `values` is reordered in place
/// and must be non-empty with all entries finite (so `total_cmp` is a total
/// order). Returns `(values-sorted[lo_idx], values-sorted[hi_idx])`.
///
/// After `select_nth_unstable_by(hi_idx)` the slice `values[..hi_idx]` holds
/// exactly the `hi_idx` smallest elements (unordered), so selecting `lo_idx`
/// within it yields the lower endpoint without a second full pass.
pub(crate) fn percentile_endpoints(values: &mut [f64], lo_idx: usize, hi_idx: usize) -> (f64, f64) {
    debug_assert!(lo_idx <= hi_idx && hi_idx < values.len());
    values.select_nth_unstable_by(hi_idx, |x, y| x.total_cmp(y));
    let upper = values[hi_idx];
    let lower = if lo_idx < hi_idx {
        values[..hi_idx].select_nth_unstable_by(lo_idx, |x, y| x.total_cmp(y));
        values[lo_idx]
    } else {
        values[lo_idx]
    };
    (lower, upper)
}

/// Standard floored percentile indices for a two-sided interval at level
/// `1 - alpha` over `n_resamples` replicates, each clamped to a valid index.
/// `n_resamples` must be `>= 1`.
pub(crate) fn two_sided_indices(alpha: f64, n_resamples: usize) -> (usize, usize) {
    let last = n_resamples - 1;
    let lo = (((alpha / 2.0) * n_resamples as f64).floor() as usize).min(last);
    let hi = (((1.0 - alpha / 2.0) * n_resamples as f64).floor() as usize).min(last);
    (lo, hi)
}
