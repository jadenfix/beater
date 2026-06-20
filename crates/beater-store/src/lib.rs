use async_trait::async_trait;
use beater_core::{IdempotencyKey, Page, PageRequest, ProjectId, TenantId, TraceId};
use beater_schema::{
    ArtifactRef, CanonicalTraceBatch, RawEnvelope, RunFilter, RunSummary, SpanFilter, SpanSummary,
    TraceView, WriteAck,
};

pub type StoreResult<T> = Result<T, StoreError>;

#[derive(Debug, thiserror::Error, Clone, PartialEq, Eq)]
pub enum StoreError {
    #[error("not found: {0}")]
    NotFound(String),
    #[error("conflict: {0}")]
    Conflict(String),
    #[error("backpressure: {0}")]
    Backpressure(String),
    #[error("integrity error: {0}")]
    Integrity(String),
    #[error("backend error: {0}")]
    Backend(String),
}

impl StoreError {
    pub fn backend(error: impl std::fmt::Display) -> Self {
        Self::Backend(error.to_string())
    }

    pub fn integrity(error: impl std::fmt::Display) -> Self {
        Self::Integrity(error.to_string())
    }
}

#[async_trait]
pub trait ArtifactStore: Send + Sync {
    async fn put_bytes(
        &self,
        tenant_id: &TenantId,
        project_id: &ProjectId,
        mime_type: &str,
        redaction_class: beater_schema::RedactionClass,
        bytes: &[u8],
    ) -> StoreResult<ArtifactRef>;

    async fn get_bytes(&self, artifact_ref: &ArtifactRef) -> StoreResult<Vec<u8>>;
}

#[async_trait]
pub trait TraceStore: Send + Sync {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> StoreResult<WriteAck>;

    async fn get_trace(&self, tenant: TenantId, trace: TraceId) -> StoreResult<TraceView>;

    async fn get_raw_envelope(
        &self,
        tenant: TenantId,
        project: ProjectId,
        idempotency_key: IdempotencyKey,
    ) -> StoreResult<Option<RawEnvelope>>;

    async fn query_runs(
        &self,
        tenant: TenantId,
        filter: RunFilter,
        page: PageRequest,
    ) -> StoreResult<Page<RunSummary>>;

    async fn query_spans(
        &self,
        tenant: TenantId,
        filter: SpanFilter,
        page: PageRequest,
    ) -> StoreResult<Page<SpanSummary>>;
}

#[derive(Clone, Default)]
pub struct InMemoryTraceStore {
    state: std::sync::Arc<std::sync::Mutex<InMemoryTraceState>>,
}

#[derive(Clone, Default)]
struct InMemoryTraceState {
    raw_envelopes: Vec<RawEnvelope>,
    spans: Vec<beater_schema::CanonicalSpan>,
}

impl InMemoryTraceStore {
    pub fn new() -> Self {
        Self::default()
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, InMemoryTraceState>> {
        self.state.lock().map_err(|err| {
            StoreError::backend(format!("in-memory trace store mutex poisoned: {err}"))
        })
    }
}

#[async_trait]
impl TraceStore for InMemoryTraceStore {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> StoreResult<WriteAck> {
        let mut state = self.lock()?;
        let mut accepted_raw = 0;
        let mut duplicate_raw = 0;
        for raw in batch.raw_envelopes {
            let exists = state.raw_envelopes.iter().any(|existing| {
                existing.tenant_id == raw.tenant_id
                    && existing.project_id == raw.project_id
                    && existing.idempotency_key == raw.idempotency_key
            });
            if exists {
                duplicate_raw += 1;
            } else {
                state.raw_envelopes.push(raw);
                accepted_raw += 1;
            }
        }

        let mut accepted_spans = 0;
        let mut duplicate_spans = 0;
        for span in batch.spans {
            let exists = state.spans.iter().any(|existing| {
                existing.tenant_id == span.tenant_id
                    && existing.project_id == span.project_id
                    && existing.trace_id == span.trace_id
                    && existing.span_id == span.span_id
                    && existing.seq == span.seq
            });
            if exists {
                duplicate_spans += 1;
            } else {
                state.spans.push(span);
                accepted_spans += 1;
            }
        }

        Ok(WriteAck {
            accepted_raw,
            accepted_spans,
            duplicate_raw,
            duplicate_spans,
        })
    }

    async fn get_trace(&self, tenant: TenantId, trace: TraceId) -> StoreResult<TraceView> {
        let state = self.lock()?;
        let mut spans = state
            .spans
            .iter()
            .filter(|span| span.tenant_id == tenant && span.trace_id == trace)
            .cloned()
            .collect::<Vec<_>>();
        spans.sort_by(|left, right| {
            left.seq
                .cmp(&right.seq)
                .then_with(|| left.start_time.cmp(&right.start_time))
        });
        Ok(TraceView {
            tenant_id: tenant,
            trace_id: trace,
            spans,
        })
    }

    async fn get_raw_envelope(
        &self,
        tenant: TenantId,
        project: ProjectId,
        idempotency_key: IdempotencyKey,
    ) -> StoreResult<Option<RawEnvelope>> {
        let state = self.lock()?;
        Ok(state
            .raw_envelopes
            .iter()
            .find(|raw| {
                raw.tenant_id == tenant
                    && raw.project_id == project
                    && raw.idempotency_key == idempotency_key
            })
            .cloned())
    }

    async fn query_runs(
        &self,
        tenant: TenantId,
        filter: RunFilter,
        page: PageRequest,
    ) -> StoreResult<Page<RunSummary>> {
        let spans = self
            .query_spans(
                tenant.clone(),
                SpanFilter {
                    trace_id: filter.trace_id,
                    span_id: None,
                    kind: filter.kind,
                    status: filter.status,
                },
                PageRequest {
                    limit: u32::MAX,
                    cursor: None,
                },
            )
            .await?
            .items;

        Ok(page_vec(roll_up_runs(tenant, spans), page))
    }

    async fn query_spans(
        &self,
        tenant: TenantId,
        filter: SpanFilter,
        page: PageRequest,
    ) -> StoreResult<Page<SpanSummary>> {
        let state = self.lock()?;
        let mut spans = state
            .spans
            .iter()
            .filter(|span| span.tenant_id == tenant && span_matches(span, &filter))
            .map(|span| SpanSummary {
                tenant_id: span.tenant_id.clone(),
                trace_id: span.trace_id.clone(),
                span_id: span.span_id.clone(),
                kind: span.kind.clone(),
                name: span.name.clone(),
                status: span.status.clone(),
                started_at: span.start_time,
                ended_at: span.end_time,
            })
            .collect::<Vec<_>>();
        spans.sort_by(|left, right| {
            right
                .started_at
                .cmp(&left.started_at)
                .then_with(|| left.trace_id.cmp(&right.trace_id))
                .then_with(|| left.span_id.cmp(&right.span_id))
        });
        Ok(page_vec(spans, page))
    }
}

pub fn span_matches(span: &beater_schema::CanonicalSpan, filter: &SpanFilter) -> bool {
    if let Some(trace_id) = &filter.trace_id {
        if span.trace_id != *trace_id {
            return false;
        }
    }
    if let Some(span_id) = &filter.span_id {
        if span.span_id != *span_id {
            return false;
        }
    }
    if let Some(kind) = &filter.kind {
        if span.kind != *kind {
            return false;
        }
    }
    if let Some(status) = &filter.status {
        if span.status != *status {
            return false;
        }
    }
    true
}

pub fn roll_up_runs(tenant: TenantId, spans: Vec<SpanSummary>) -> Vec<RunSummary> {
    let mut runs = Vec::<RunSummary>::new();
    for span in spans {
        if let Some(run) = runs.iter_mut().find(|run| run.trace_id == span.trace_id) {
            run.span_count += 1;
            if run.status != beater_schema::SpanStatus::Error
                && span.status == beater_schema::SpanStatus::Error
            {
                run.status = beater_schema::SpanStatus::Error;
            }
            run.ended_at = match (run.ended_at, span.ended_at) {
                (Some(left), Some(right)) => Some(left.max(right)),
                (None, Some(right)) => Some(right),
                (left, None) => left,
            };
        } else {
            runs.push(RunSummary {
                tenant_id: tenant.clone(),
                trace_id: span.trace_id,
                first_span_name: span.name,
                span_count: 1,
                status: span.status,
                started_at: span.started_at,
                ended_at: span.ended_at,
            });
        }
    }

    runs.sort_by(|left, right| right.started_at.cmp(&left.started_at));
    runs
}

pub fn page_vec<T>(mut items: Vec<T>, page: PageRequest) -> Page<T> {
    let limit = page.limit.max(1) as usize;
    let offset = page
        .cursor
        .and_then(|cursor| cursor.parse::<usize>().ok())
        .unwrap_or(0);

    if offset >= items.len() {
        return Page::new(Vec::new(), None);
    }

    let next_offset = offset.saturating_add(limit);
    let next_cursor = if next_offset < items.len() {
        Some(next_offset.to_string())
    } else {
        None
    };
    let end = next_offset.min(items.len());
    let selected = items.drain(offset..end).collect();
    Page::new(selected, next_cursor)
}
