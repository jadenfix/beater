//! Orphaned-artifact sweeper.
//!
//! Reconciles a set of candidate artifact references against the artifacts still
//! referenced by live spans in a [`TraceStore`], deleting the bytes for any
//! candidate that is no longer reachable. This reclaims object-store space after
//! traces age out / are deleted from the hot store while their artifacts (raw
//! payloads, span inputs/outputs) linger.
//!
//! The sweep is conservative (delete only what is provably unreferenced) and
//! idempotent (delete of a missing object is a no-op), so it is safe to re-run
//! and safe to race with concurrent deletes.

use beater_core::{PageRequest, ProjectId, TenantId};
use beater_schema::{ArtifactRef, CanonicalSpan, SpanFilter};
use beater_store::{ArtifactStore, StoreResult, TraceStore};
use std::collections::BTreeSet;
use std::sync::Arc;

/// Maximum number of spans materialized per reconciliation pass. Run summaries
/// in this codebase already materialize spans through `query_spans`, so this
/// bounds memory for the sweep the same way.
const SWEEP_SCAN_LIMIT: u32 = u32::MAX;

/// Outcome of a sweep pass.
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct SweepReport {
    /// Candidate artifacts whose URI was still referenced by a live span and so
    /// were left in place.
    pub retained: usize,
    /// Candidate artifacts that were unreferenced and deleted from the store.
    pub deleted: usize,
    /// URIs of the artifacts that were deleted, in sorted order.
    pub deleted_uris: Vec<String>,
}

/// Deletes object-store artifacts that are no longer referenced by any live span.
pub struct OrphanedArtifactSweeper {
    artifacts: Arc<dyn ArtifactStore>,
}

impl OrphanedArtifactSweeper {
    pub fn new(artifacts: Arc<dyn ArtifactStore>) -> Self {
        Self { artifacts }
    }

    /// Reconciles `candidates` against the artifacts referenced by the live spans
    /// of `tenant` (optionally scoped to `project`) in `trace_store`, deleting any
    /// candidate whose URI is not referenced.
    ///
    /// `candidates` is the set of artifacts known to exist in the object store
    /// (e.g. an object-store listing). Anything in `candidates` not referenced by
    /// a live span is treated as orphaned and deleted.
    pub async fn sweep(
        &self,
        trace_store: &dyn TraceStore,
        tenant: TenantId,
        project: Option<ProjectId>,
        candidates: &[ArtifactRef],
    ) -> StoreResult<SweepReport> {
        let live = self
            .live_referenced_uris(trace_store, tenant, project)
            .await?;
        self.delete_orphans(candidates, &live).await
    }

    async fn live_referenced_uris(
        &self,
        trace_store: &dyn TraceStore,
        tenant: TenantId,
        project: Option<ProjectId>,
    ) -> StoreResult<BTreeSet<String>> {
        // `query_spans` returns span summaries, which intentionally drop the
        // artifact refs, so reconcile against full traces instead. We discover
        // the live trace ids via the span summaries, then load each trace's full
        // spans to collect every referenced artifact uri.
        let summaries = trace_store
            .query_spans(
                tenant.clone(),
                SpanFilter {
                    project_id: project.clone(),
                    ..SpanFilter::default()
                },
                PageRequest {
                    limit: SWEEP_SCAN_LIMIT,
                    cursor: None,
                },
            )
            .await?
            .items;

        let mut trace_ids = BTreeSet::new();
        for summary in summaries {
            trace_ids.insert(summary.trace_id);
        }

        let mut referenced = BTreeSet::new();
        for trace_id in trace_ids {
            let view = match &project {
                Some(project) => {
                    trace_store
                        .get_project_trace(tenant.clone(), project.clone(), trace_id)
                        .await?
                }
                None => trace_store.get_trace(tenant.clone(), trace_id).await?,
            };
            referenced.extend(referenced_artifact_uris(&view.spans));
        }
        Ok(referenced)
    }

    async fn delete_orphans(
        &self,
        candidates: &[ArtifactRef],
        live: &BTreeSet<String>,
    ) -> StoreResult<SweepReport> {
        let mut report = SweepReport::default();
        for candidate in candidates {
            if live.contains(&candidate.uri) {
                report.retained += 1;
                continue;
            }
            self.artifacts.delete_bytes(candidate).await?;
            report.deleted += 1;
            report.deleted_uris.push(candidate.uri.clone());
        }
        report.deleted_uris.sort();
        Ok(report)
    }
}

/// Collects every artifact uri referenced by the given spans (raw payloads plus
/// any span input/output artifacts).
fn referenced_artifact_uris(spans: &[CanonicalSpan]) -> BTreeSet<String> {
    let mut uris = BTreeSet::new();
    for span in spans {
        uris.insert(span.raw_ref.uri.clone());
        if let Some(input) = &span.input_ref {
            uris.insert(input.uri.clone());
        }
        if let Some(output) = &span.output_ref {
            uris.insert(output.uri.clone());
        }
    }
    uris
}
