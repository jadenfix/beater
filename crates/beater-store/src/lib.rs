use async_trait::async_trait;
use beater_core::{
    EnvironmentId, IdempotencyKey, OrganizationId, Page, PageRequest, ProjectId, TenantId,
    Timestamp, TraceId,
};
use beater_schema::{
    filter_run_summaries, roll_up_runs, span_matches, span_summary, ArtifactRef,
    CanonicalTraceBatch, RawEnvelope, RunFilter, RunSummary, SpanFilter, SpanSummary, TraceView,
    WriteAck,
};
use std::collections::BTreeSet;

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

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct OrganizationMetadata {
    pub tenant_id: TenantId,
    pub organization_id: OrganizationId,
    pub display_name: String,
    pub created_at: Timestamp,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ProjectMetadata {
    pub tenant_id: TenantId,
    pub organization_id: OrganizationId,
    pub project_id: ProjectId,
    pub display_name: String,
    pub created_at: Timestamp,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct EnvironmentMetadata {
    pub tenant_id: TenantId,
    pub project_id: ProjectId,
    pub environment_id: EnvironmentId,
    pub display_name: String,
    pub created_at: Timestamp,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct RoleBinding {
    pub tenant_id: TenantId,
    pub project_id: Option<ProjectId>,
    pub principal_id: String,
    pub role: String,
    pub permissions: BTreeSet<String>,
    pub created_at: Timestamp,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct QuotaReservationRequest {
    pub tenant_id: TenantId,
    pub project_id: ProjectId,
    pub amount: u64,
    pub limit: u64,
    pub window_start: Timestamp,
    pub reset_at: Timestamp,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct QuotaDecision {
    pub accepted: bool,
    pub used: u64,
    pub limit: u64,
    pub reset_at: Timestamp,
}

#[async_trait]
pub trait QuotaLimiter: Send + Sync {
    async fn reserve_quota(&self, request: QuotaReservationRequest) -> StoreResult<QuotaDecision>;
}

#[async_trait]
pub trait MetadataStore: Send + Sync {
    async fn put_organization(&self, organization: OrganizationMetadata) -> StoreResult<()>;

    async fn get_organization(
        &self,
        tenant_id: TenantId,
        organization_id: OrganizationId,
    ) -> StoreResult<Option<OrganizationMetadata>>;

    async fn put_project(&self, project: ProjectMetadata) -> StoreResult<()>;

    async fn get_project(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
    ) -> StoreResult<Option<ProjectMetadata>>;

    async fn put_environment(&self, environment: EnvironmentMetadata) -> StoreResult<()>;

    async fn get_environment(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
        environment_id: EnvironmentId,
    ) -> StoreResult<Option<EnvironmentMetadata>>;

    async fn put_role_binding(&self, binding: RoleBinding) -> StoreResult<()>;

    async fn list_role_bindings(
        &self,
        tenant_id: TenantId,
        project_id: Option<ProjectId>,
        principal_id: String,
    ) -> StoreResult<Vec<RoleBinding>>;
}

#[derive(Clone, Default)]
pub struct InMemoryTraceStore {
    state: std::sync::Arc<std::sync::Mutex<InMemoryTraceState>>,
}

#[derive(Clone, Default)]
pub struct InMemoryMetadataStore {
    state: std::sync::Arc<std::sync::Mutex<InMemoryMetadataState>>,
}

#[derive(Clone, Default)]
pub struct InMemoryQuotaLimiter {
    state: std::sync::Arc<std::sync::Mutex<InMemoryQuotaState>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
struct InMemoryQuotaCounter {
    tenant_id: TenantId,
    project_id: ProjectId,
    window_start: Timestamp,
    used: u64,
}

#[derive(Clone, Default)]
struct InMemoryQuotaState {
    counters: Vec<InMemoryQuotaCounter>,
}

#[derive(Clone, Default)]
struct InMemoryMetadataState {
    organizations: Vec<OrganizationMetadata>,
    projects: Vec<ProjectMetadata>,
    environments: Vec<EnvironmentMetadata>,
    role_bindings: Vec<RoleBinding>,
}

impl InMemoryMetadataStore {
    pub fn new() -> Self {
        Self::default()
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, InMemoryMetadataState>> {
        self.state
            .lock()
            .map_err(|err| StoreError::backend(format!("metadata store mutex poisoned: {err}")))
    }
}

impl InMemoryQuotaLimiter {
    pub fn new() -> Self {
        Self::default()
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, InMemoryQuotaState>> {
        self.state
            .lock()
            .map_err(|err| StoreError::backend(format!("quota limiter mutex poisoned: {err}")))
    }
}

#[async_trait]
impl QuotaLimiter for InMemoryQuotaLimiter {
    async fn reserve_quota(&self, request: QuotaReservationRequest) -> StoreResult<QuotaDecision> {
        let mut state = self.lock()?;
        let counter = state.counters.iter_mut().find(|counter| {
            counter.tenant_id == request.tenant_id
                && counter.project_id == request.project_id
                && counter.window_start == request.window_start
        });
        let current_used = counter.as_ref().map(|counter| counter.used).unwrap_or(0);
        let Some(new_used) = current_used.checked_add(request.amount) else {
            return Err(StoreError::integrity("quota counter overflow"));
        };
        if new_used > request.limit {
            return Ok(QuotaDecision {
                accepted: false,
                used: current_used,
                limit: request.limit,
                reset_at: request.reset_at,
            });
        }

        if let Some(counter) = counter {
            counter.used = new_used;
        } else {
            state.counters.push(InMemoryQuotaCounter {
                tenant_id: request.tenant_id,
                project_id: request.project_id,
                window_start: request.window_start,
                used: new_used,
            });
        }
        Ok(QuotaDecision {
            accepted: true,
            used: new_used,
            limit: request.limit,
            reset_at: request.reset_at,
        })
    }
}

#[async_trait]
impl MetadataStore for InMemoryMetadataStore {
    async fn put_organization(&self, organization: OrganizationMetadata) -> StoreResult<()> {
        let mut state = self.lock()?;
        if let Some(existing) = state.organizations.iter_mut().find(|existing| {
            existing.tenant_id == organization.tenant_id
                && existing.organization_id == organization.organization_id
        }) {
            *existing = organization;
        } else {
            state.organizations.push(organization);
        }
        Ok(())
    }

    async fn get_organization(
        &self,
        tenant_id: TenantId,
        organization_id: OrganizationId,
    ) -> StoreResult<Option<OrganizationMetadata>> {
        let state = self.lock()?;
        Ok(state
            .organizations
            .iter()
            .find(|organization| {
                organization.tenant_id == tenant_id
                    && organization.organization_id == organization_id
            })
            .cloned())
    }

    async fn put_project(&self, project: ProjectMetadata) -> StoreResult<()> {
        let mut state = self.lock()?;
        if let Some(existing) = state.projects.iter_mut().find(|existing| {
            existing.tenant_id == project.tenant_id && existing.project_id == project.project_id
        }) {
            *existing = project;
        } else {
            state.projects.push(project);
        }
        Ok(())
    }

    async fn get_project(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
    ) -> StoreResult<Option<ProjectMetadata>> {
        let state = self.lock()?;
        Ok(state
            .projects
            .iter()
            .find(|project| project.tenant_id == tenant_id && project.project_id == project_id)
            .cloned())
    }

    async fn put_environment(&self, environment: EnvironmentMetadata) -> StoreResult<()> {
        let mut state = self.lock()?;
        if let Some(existing) = state.environments.iter_mut().find(|existing| {
            existing.tenant_id == environment.tenant_id
                && existing.project_id == environment.project_id
                && existing.environment_id == environment.environment_id
        }) {
            *existing = environment;
        } else {
            state.environments.push(environment);
        }
        Ok(())
    }

    async fn get_environment(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
        environment_id: EnvironmentId,
    ) -> StoreResult<Option<EnvironmentMetadata>> {
        let state = self.lock()?;
        Ok(state
            .environments
            .iter()
            .find(|environment| {
                environment.tenant_id == tenant_id
                    && environment.project_id == project_id
                    && environment.environment_id == environment_id
            })
            .cloned())
    }

    async fn put_role_binding(&self, binding: RoleBinding) -> StoreResult<()> {
        let mut state = self.lock()?;
        if let Some(existing) = state.role_bindings.iter_mut().find(|existing| {
            existing.tenant_id == binding.tenant_id
                && existing.project_id == binding.project_id
                && existing.principal_id == binding.principal_id
                && existing.role == binding.role
        }) {
            *existing = binding;
        } else {
            state.role_bindings.push(binding);
        }
        Ok(())
    }

    async fn list_role_bindings(
        &self,
        tenant_id: TenantId,
        project_id: Option<ProjectId>,
        principal_id: String,
    ) -> StoreResult<Vec<RoleBinding>> {
        let state = self.lock()?;
        Ok(state
            .role_bindings
            .iter()
            .filter(|binding| {
                binding.tenant_id == tenant_id
                    && binding.project_id == project_id
                    && binding.principal_id == principal_id
            })
            .cloned()
            .collect())
    }
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
                    project_id: filter.project_id.clone(),
                    environment_id: filter.environment_id.clone(),
                    trace_id: filter.trace_id.clone(),
                    span_id: None,
                    kind: None,
                    status: None,
                },
                PageRequest {
                    limit: u32::MAX,
                    cursor: None,
                },
            )
            .await?
            .items;

        let runs = filter_run_summaries(roll_up_runs(tenant, spans.clone()), &spans, &filter);
        Ok(page_vec(runs, page))
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
            .cloned()
            .map(span_summary)
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
