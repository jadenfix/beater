use async_trait::async_trait;
use beater_core::{
    EnvironmentId, IdempotencyKey, OrganizationId, Page, PageRequest, ProjectId, TenantId,
    Timestamp, TraceId,
};
use beater_schema::{
    filter_run_summaries, roll_up_runs, span_summary, CanonicalSpan, CanonicalTraceBatch,
    RawEnvelope, RunFilter, RunSummary, SpanFilter, SpanSummary, TraceView, WriteAck,
};
use beater_store::{
    page_vec, EnvironmentMetadata, MetadataStore, OrganizationMetadata, ProjectMetadata,
    QuotaDecision, QuotaLimiter, QuotaReservationRequest, RoleBinding, StoreError, StoreResult,
    TraceStore,
};
use chrono::{DateTime, Utc};
use rusqlite::{params, Connection, OptionalExtension};
use std::collections::BTreeSet;
use std::fs;
use std::path::Path;
use std::sync::{Arc, Mutex};

#[derive(Clone)]
pub struct SqliteTraceStore {
    connection: Arc<Mutex<Connection>>,
}

#[derive(Clone)]
pub struct SqliteMetadataStore {
    connection: Arc<Mutex<Connection>>,
}

#[derive(Clone)]
pub struct SqliteQuotaLimiter {
    connection: Arc<Mutex<Connection>>,
}

impl SqliteQuotaLimiter {
    pub fn in_memory() -> StoreResult<Self> {
        let connection = Connection::open_in_memory().map_err(StoreError::backend)?;
        let limiter = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        limiter.init()?;
        Ok(limiter)
    }

    pub fn open(path: impl AsRef<Path>) -> StoreResult<Self> {
        let path = path.as_ref();
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent).map_err(StoreError::backend)?;
        }
        let connection = Connection::open(path).map_err(StoreError::backend)?;
        let limiter = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        limiter.init()?;
        Ok(limiter)
    }

    fn init(&self) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute_batch(
                r#"
                PRAGMA journal_mode = WAL;
                PRAGMA foreign_keys = ON;

                CREATE TABLE IF NOT EXISTS quota_counters (
                    tenant_id TEXT NOT NULL,
                    project_id TEXT NOT NULL,
                    window_start TEXT NOT NULL,
                    reset_at TEXT NOT NULL,
                    used_events INTEGER NOT NULL,
                    updated_at TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id, window_start)
                );
                "#,
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, Connection>> {
        self.connection
            .lock()
            .map_err(|err| StoreError::backend(format!("quota sqlite mutex poisoned: {err}")))
    }
}

#[async_trait]
impl QuotaLimiter for SqliteQuotaLimiter {
    async fn reserve_quota(&self, request: QuotaReservationRequest) -> StoreResult<QuotaDecision> {
        let mut connection = self.lock()?;
        let tx = connection.transaction().map_err(StoreError::backend)?;
        let current_used = tx
            .query_row(
                r#"
                SELECT used_events
                FROM quota_counters
                WHERE tenant_id = ?1 AND project_id = ?2 AND window_start = ?3
                "#,
                params![
                    request.tenant_id.as_str(),
                    request.project_id.as_str(),
                    request.window_start.to_rfc3339(),
                ],
                |row| row.get::<_, i64>(0),
            )
            .optional()
            .map_err(StoreError::backend)?
            .unwrap_or(0);
        if current_used < 0 {
            return Err(StoreError::integrity("negative quota counter"));
        }
        let current_used = current_used as u64;
        let Some(new_used) = current_used.checked_add(request.amount) else {
            return Err(StoreError::integrity("quota counter overflow"));
        };
        if new_used > request.limit {
            tx.commit().map_err(StoreError::backend)?;
            return Ok(QuotaDecision {
                accepted: false,
                used: current_used,
                limit: request.limit,
                reset_at: request.reset_at,
            });
        }

        tx.execute(
            r#"
            INSERT INTO quota_counters
              (tenant_id, project_id, window_start, reset_at, used_events, updated_at)
            VALUES (?1, ?2, ?3, ?4, ?5, ?6)
            ON CONFLICT(tenant_id, project_id, window_start) DO UPDATE SET
              reset_at = excluded.reset_at,
              used_events = excluded.used_events,
              updated_at = excluded.updated_at
            "#,
            params![
                request.tenant_id.as_str(),
                request.project_id.as_str(),
                request.window_start.to_rfc3339(),
                request.reset_at.to_rfc3339(),
                new_used as i64,
                Utc::now().to_rfc3339(),
            ],
        )
        .map_err(StoreError::backend)?;
        tx.commit().map_err(StoreError::backend)?;

        Ok(QuotaDecision {
            accepted: true,
            used: new_used,
            limit: request.limit,
            reset_at: request.reset_at,
        })
    }
}

impl SqliteMetadataStore {
    pub fn in_memory() -> StoreResult<Self> {
        let connection = Connection::open_in_memory().map_err(StoreError::backend)?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    pub fn open(path: impl AsRef<Path>) -> StoreResult<Self> {
        let path = path.as_ref();
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent).map_err(StoreError::backend)?;
        }
        let connection = Connection::open(path).map_err(StoreError::backend)?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    fn init(&self) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute_batch(
                r#"
                PRAGMA journal_mode = WAL;
                PRAGMA foreign_keys = ON;

                CREATE TABLE IF NOT EXISTS organizations (
                    tenant_id TEXT NOT NULL,
                    organization_id TEXT NOT NULL,
                    display_name TEXT NOT NULL,
                    created_at TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, organization_id)
                );

                CREATE TABLE IF NOT EXISTS projects (
                    tenant_id TEXT NOT NULL,
                    organization_id TEXT NOT NULL,
                    project_id TEXT NOT NULL,
                    display_name TEXT NOT NULL,
                    created_at TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id)
                );

                CREATE TABLE IF NOT EXISTS environments (
                    tenant_id TEXT NOT NULL,
                    project_id TEXT NOT NULL,
                    environment_id TEXT NOT NULL,
                    display_name TEXT NOT NULL,
                    created_at TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id, environment_id)
                );

                CREATE TABLE IF NOT EXISTS role_bindings (
                    tenant_id TEXT NOT NULL,
                    project_id TEXT,
                    principal_id TEXT NOT NULL,
                    role TEXT NOT NULL,
                    permissions_json TEXT NOT NULL,
                    created_at TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id, principal_id, role)
                );
                "#,
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, Connection>> {
        self.connection
            .lock()
            .map_err(|err| StoreError::backend(format!("metadata sqlite mutex poisoned: {err}")))
    }
}

#[async_trait]
impl MetadataStore for SqliteMetadataStore {
    async fn put_organization(&self, organization: OrganizationMetadata) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute(
                r#"
                INSERT INTO organizations (tenant_id, organization_id, display_name, created_at)
                VALUES (?1, ?2, ?3, ?4)
                ON CONFLICT(tenant_id, organization_id) DO UPDATE SET
                  display_name = excluded.display_name,
                  created_at = excluded.created_at
                "#,
                params![
                    organization.tenant_id.as_str(),
                    organization.organization_id.as_str(),
                    organization.display_name,
                    organization.created_at.to_rfc3339(),
                ],
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    async fn get_organization(
        &self,
        tenant_id: TenantId,
        organization_id: OrganizationId,
    ) -> StoreResult<Option<OrganizationMetadata>> {
        let connection = self.lock()?;
        connection
            .query_row(
                r#"
                SELECT tenant_id, organization_id, display_name, created_at
                FROM organizations
                WHERE tenant_id = ?1 AND organization_id = ?2
                "#,
                params![tenant_id.as_str(), organization_id.as_str()],
                decode_organization,
            )
            .optional()
            .map_err(StoreError::backend)
    }

    async fn put_project(&self, project: ProjectMetadata) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute(
                r#"
                INSERT INTO projects
                  (tenant_id, organization_id, project_id, display_name, created_at)
                VALUES (?1, ?2, ?3, ?4, ?5)
                ON CONFLICT(tenant_id, project_id) DO UPDATE SET
                  organization_id = excluded.organization_id,
                  display_name = excluded.display_name,
                  created_at = excluded.created_at
                "#,
                params![
                    project.tenant_id.as_str(),
                    project.organization_id.as_str(),
                    project.project_id.as_str(),
                    project.display_name,
                    project.created_at.to_rfc3339(),
                ],
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    async fn get_project(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
    ) -> StoreResult<Option<ProjectMetadata>> {
        let connection = self.lock()?;
        connection
            .query_row(
                r#"
                SELECT tenant_id, organization_id, project_id, display_name, created_at
                FROM projects
                WHERE tenant_id = ?1 AND project_id = ?2
                "#,
                params![tenant_id.as_str(), project_id.as_str()],
                decode_project,
            )
            .optional()
            .map_err(StoreError::backend)
    }

    async fn put_environment(&self, environment: EnvironmentMetadata) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute(
                r#"
                INSERT INTO environments
                  (tenant_id, project_id, environment_id, display_name, created_at)
                VALUES (?1, ?2, ?3, ?4, ?5)
                ON CONFLICT(tenant_id, project_id, environment_id) DO UPDATE SET
                  display_name = excluded.display_name,
                  created_at = excluded.created_at
                "#,
                params![
                    environment.tenant_id.as_str(),
                    environment.project_id.as_str(),
                    environment.environment_id.as_str(),
                    environment.display_name,
                    environment.created_at.to_rfc3339(),
                ],
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    async fn get_environment(
        &self,
        tenant_id: TenantId,
        project_id: ProjectId,
        environment_id: EnvironmentId,
    ) -> StoreResult<Option<EnvironmentMetadata>> {
        let connection = self.lock()?;
        connection
            .query_row(
                r#"
                SELECT tenant_id, project_id, environment_id, display_name, created_at
                FROM environments
                WHERE tenant_id = ?1 AND project_id = ?2 AND environment_id = ?3
                "#,
                params![
                    tenant_id.as_str(),
                    project_id.as_str(),
                    environment_id.as_str()
                ],
                decode_environment,
            )
            .optional()
            .map_err(StoreError::backend)
    }

    async fn put_role_binding(&self, binding: RoleBinding) -> StoreResult<()> {
        let connection = self.lock()?;
        let permissions_json =
            serde_json::to_string(&binding.permissions).map_err(StoreError::backend)?;
        connection
            .execute(
                r#"
                INSERT INTO role_bindings
                  (tenant_id, project_id, principal_id, role, permissions_json, created_at)
                VALUES (?1, ?2, ?3, ?4, ?5, ?6)
                ON CONFLICT(tenant_id, project_id, principal_id, role) DO UPDATE SET
                  permissions_json = excluded.permissions_json,
                  created_at = excluded.created_at
                "#,
                params![
                    binding.tenant_id.as_str(),
                    binding.project_id.as_ref().map(|project| project.as_str()),
                    binding.principal_id,
                    binding.role,
                    permissions_json,
                    binding.created_at.to_rfc3339(),
                ],
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    async fn list_role_bindings(
        &self,
        tenant_id: TenantId,
        project_id: Option<ProjectId>,
        principal_id: String,
    ) -> StoreResult<Vec<RoleBinding>> {
        let connection = self.lock()?;
        let mut statement = connection
            .prepare(
                r#"
                SELECT tenant_id, project_id, principal_id, role, permissions_json, created_at
                FROM role_bindings
                WHERE tenant_id = ?1
                  AND ((?2 IS NULL AND project_id IS NULL) OR project_id = ?2)
                  AND principal_id = ?3
                ORDER BY role ASC
                "#,
            )
            .map_err(StoreError::backend)?;
        let rows = statement
            .query_map(
                params![
                    tenant_id.as_str(),
                    project_id.as_ref().map(|project| project.as_str()),
                    principal_id,
                ],
                decode_role_binding,
            )
            .map_err(StoreError::backend)?;
        let mut bindings = Vec::new();
        for row in rows {
            bindings.push(row.map_err(StoreError::backend)?);
        }
        Ok(bindings)
    }
}

impl SqliteTraceStore {
    pub fn in_memory() -> StoreResult<Self> {
        let connection = Connection::open_in_memory().map_err(StoreError::backend)?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    pub fn open(path: impl AsRef<Path>) -> StoreResult<Self> {
        let path = path.as_ref();
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent).map_err(StoreError::backend)?;
        }
        let connection = Connection::open(path).map_err(StoreError::backend)?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    fn init(&self) -> StoreResult<()> {
        let connection = self.lock()?;
        connection
            .execute_batch(
                r#"
                PRAGMA journal_mode = WAL;
                PRAGMA foreign_keys = ON;

                CREATE TABLE IF NOT EXISTS raw_envelopes (
                    tenant_id TEXT NOT NULL,
                    project_id TEXT NOT NULL,
                    idempotency_key TEXT NOT NULL,
                    trace_id TEXT,
                    payload_hash TEXT NOT NULL,
                    received_at TEXT NOT NULL,
                    raw_json TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id, idempotency_key)
                );

                CREATE TABLE IF NOT EXISTS spans (
                    tenant_id TEXT NOT NULL,
                    project_id TEXT NOT NULL,
                    environment_id TEXT NOT NULL,
                    trace_id TEXT NOT NULL,
                    span_id TEXT NOT NULL,
                    seq INTEGER NOT NULL,
                    kind TEXT NOT NULL,
                    status TEXT NOT NULL,
                    name TEXT NOT NULL,
                    start_time TEXT NOT NULL,
                    end_time TEXT,
                    span_json TEXT NOT NULL,
                    PRIMARY KEY (tenant_id, project_id, trace_id, span_id, seq)
                );

                CREATE INDEX IF NOT EXISTS idx_spans_tenant_trace
                ON spans (tenant_id, trace_id, seq);

                CREATE INDEX IF NOT EXISTS idx_spans_tenant_kind_status
                ON spans (tenant_id, kind, status, start_time);
                "#,
            )
            .map_err(StoreError::backend)?;
        Ok(())
    }

    fn lock(&self) -> StoreResult<std::sync::MutexGuard<'_, Connection>> {
        self.connection
            .lock()
            .map_err(|err| StoreError::backend(format!("sqlite connection mutex poisoned: {err}")))
    }
}

#[async_trait]
impl TraceStore for SqliteTraceStore {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> StoreResult<WriteAck> {
        let mut connection = self.lock()?;
        let tx = connection.transaction().map_err(StoreError::backend)?;

        let mut accepted_raw = 0;
        let mut duplicate_raw = 0;
        for raw in &batch.raw_envelopes {
            let raw_json = serde_json::to_string(raw).map_err(StoreError::backend)?;
            let changed = tx
                .execute(
                    r#"
                    INSERT OR IGNORE INTO raw_envelopes
                      (tenant_id, project_id, idempotency_key, trace_id, payload_hash, received_at, raw_json)
                    VALUES
                      (?1, ?2, ?3, NULL, ?4, ?5, ?6)
                    "#,
                    params![
                        raw.tenant_id.as_str(),
                        raw.project_id.as_str(),
                        raw.idempotency_key.as_str(),
                        raw.payload_hash.as_str(),
                        raw.received_at.to_rfc3339(),
                        raw_json
                    ],
                )
                .map_err(StoreError::backend)?;
            if changed == 0 {
                duplicate_raw += 1;
            } else {
                accepted_raw += 1;
            }
        }

        let mut accepted_spans = 0;
        let mut duplicate_spans = 0;
        for span in &batch.spans {
            let span_json = serde_json::to_string(span).map_err(StoreError::backend)?;
            let changed = tx
                .execute(
                    r#"
                    INSERT OR IGNORE INTO spans
                      (tenant_id, project_id, environment_id, trace_id, span_id, seq, kind, status,
                       name, start_time, end_time, span_json)
                    VALUES
                      (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12)
                    "#,
                    params![
                        span.tenant_id.as_str(),
                        span.project_id.as_str(),
                        span.environment_id.as_str(),
                        span.trace_id.as_str(),
                        span.span_id.as_str(),
                        span.seq as i64,
                        span.kind.as_str(),
                        span.status.as_str(),
                        span.name,
                        span.start_time.to_rfc3339(),
                        span.end_time.map(|time| time.to_rfc3339()),
                        span_json
                    ],
                )
                .map_err(StoreError::backend)?;
            if changed == 0 {
                duplicate_spans += 1;
            } else {
                accepted_spans += 1;
            }
        }

        tx.commit().map_err(StoreError::backend)?;
        Ok(WriteAck {
            accepted_raw,
            accepted_spans,
            duplicate_raw,
            duplicate_spans,
        })
    }

    async fn get_trace(&self, tenant: TenantId, trace: TraceId) -> StoreResult<TraceView> {
        let connection = self.lock()?;
        let mut statement = connection
            .prepare(
                r#"
                SELECT span_json
                FROM spans
                WHERE tenant_id = ?1 AND trace_id = ?2
                ORDER BY seq ASC, start_time ASC
                "#,
            )
            .map_err(StoreError::backend)?;
        let rows = statement
            .query_map(params![tenant.as_str(), trace.as_str()], |row| {
                row.get::<_, String>(0)
            })
            .map_err(StoreError::backend)?;

        let mut spans = Vec::new();
        for row in rows {
            let json = row.map_err(StoreError::backend)?;
            spans.push(serde_json::from_str::<CanonicalSpan>(&json).map_err(StoreError::backend)?);
        }

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
        let connection = self.lock()?;
        let raw_json = connection
            .query_row(
                r#"
                SELECT raw_json
                FROM raw_envelopes
                WHERE tenant_id = ?1 AND project_id = ?2 AND idempotency_key = ?3
                "#,
                params![tenant.as_str(), project.as_str(), idempotency_key.as_str()],
                |row| row.get::<_, String>(0),
            )
            .optional()
            .map_err(StoreError::backend)?;
        raw_json
            .map(|json| serde_json::from_str::<RawEnvelope>(&json).map_err(StoreError::backend))
            .transpose()
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
        let connection = self.lock()?;
        let mut statement = connection
            .prepare(
                r#"
                SELECT span_json
                FROM spans
                WHERE tenant_id = ?1
                  AND (?2 IS NULL OR project_id = ?2)
                  AND (?3 IS NULL OR environment_id = ?3)
                  AND (?4 IS NULL OR trace_id = ?4)
                  AND (?5 IS NULL OR span_id = ?5)
                  AND (?6 IS NULL OR kind = ?6)
                  AND (?7 IS NULL OR status = ?7)
                ORDER BY start_time DESC, seq ASC
                "#,
            )
            .map_err(StoreError::backend)?;
        let rows = statement
            .query_map(
                params![
                    tenant.as_str(),
                    filter
                        .project_id
                        .as_ref()
                        .map(|project_id| project_id.as_str()),
                    filter
                        .environment_id
                        .as_ref()
                        .map(|environment_id| environment_id.as_str()),
                    filter.trace_id.as_ref().map(|trace_id| trace_id.as_str()),
                    filter.span_id.as_ref().map(|span_id| span_id.as_str()),
                    filter.kind.as_ref().map(|kind| kind.as_str()),
                    filter.status.as_ref().map(|status| status.as_str()),
                ],
                |row| row.get::<_, String>(0),
            )
            .map_err(StoreError::backend)?;

        let mut spans = Vec::new();
        for row in rows {
            let json = row.map_err(StoreError::backend)?;
            let span = serde_json::from_str::<CanonicalSpan>(&json).map_err(StoreError::backend)?;
            spans.push(span_summary(span));
        }

        Ok(page_vec(spans, page))
    }
}

fn decode_organization(row: &rusqlite::Row<'_>) -> rusqlite::Result<OrganizationMetadata> {
    Ok(OrganizationMetadata {
        tenant_id: id_from_row(row, 0)?,
        organization_id: id_from_row(row, 1)?,
        display_name: row.get(2)?,
        created_at: parse_timestamp(row.get(3)?)?,
    })
}

fn decode_project(row: &rusqlite::Row<'_>) -> rusqlite::Result<ProjectMetadata> {
    Ok(ProjectMetadata {
        tenant_id: id_from_row(row, 0)?,
        organization_id: id_from_row(row, 1)?,
        project_id: id_from_row(row, 2)?,
        display_name: row.get(3)?,
        created_at: parse_timestamp(row.get(4)?)?,
    })
}

fn decode_environment(row: &rusqlite::Row<'_>) -> rusqlite::Result<EnvironmentMetadata> {
    Ok(EnvironmentMetadata {
        tenant_id: id_from_row(row, 0)?,
        project_id: id_from_row(row, 1)?,
        environment_id: id_from_row(row, 2)?,
        display_name: row.get(3)?,
        created_at: parse_timestamp(row.get(4)?)?,
    })
}

fn decode_role_binding(row: &rusqlite::Row<'_>) -> rusqlite::Result<RoleBinding> {
    let project_id = row
        .get::<_, Option<String>>(1)?
        .map(|value| parse_id::<ProjectId>(value, 1))
        .transpose()?;
    let permissions_json: String = row.get(4)?;
    let permissions = serde_json::from_str::<BTreeSet<String>>(&permissions_json)
        .map_err(|err| conversion_error(4, permissions_json.len(), err))?;
    Ok(RoleBinding {
        tenant_id: id_from_row(row, 0)?,
        project_id,
        principal_id: row.get(2)?,
        role: row.get(3)?,
        permissions,
        created_at: parse_timestamp(row.get(5)?)?,
    })
}

fn id_from_row<T>(row: &rusqlite::Row<'_>, index: usize) -> rusqlite::Result<T>
where
    T: TryFrom<String>,
    T::Error: std::error::Error + Send + Sync + 'static,
{
    parse_id(row.get(index)?, index)
}

fn parse_id<T>(value: String, index: usize) -> rusqlite::Result<T>
where
    T: TryFrom<String>,
    T::Error: std::error::Error + Send + Sync + 'static,
{
    let len = value.len();
    value
        .try_into()
        .map_err(|err| conversion_error(index, len, err))
}

fn parse_timestamp(value: String) -> rusqlite::Result<Timestamp> {
    DateTime::parse_from_rfc3339(&value)
        .map(|time| time.with_timezone(&chrono::Utc))
        .map_err(|err| conversion_error(0, value.len(), err))
}

fn conversion_error(
    index: usize,
    _len: usize,
    err: impl std::error::Error + Send + Sync + 'static,
) -> rusqlite::Error {
    rusqlite::Error::FromSqlConversionFailure(index, rusqlite::types::Type::Text, Box::new(err))
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_core::{
        EnvironmentId, IdempotencyKey, OrganizationId, Sha256Hash, SpanId, TenantScope,
    };
    use beater_schema::{
        AgentSpanKind, ArtifactRef, AuthContext, RedactionClass, SourceDialect, SpanStatus,
        CANONICAL_SCHEMA_VERSION, RAW_SCHEMA_VERSION,
    };
    use beater_store::{InMemoryMetadataStore, InMemoryQuotaLimiter, InMemoryTraceStore};
    use chrono::{TimeZone, Utc};
    use serde_json::json;
    use std::collections::{BTreeMap, BTreeSet};

    #[tokio::test]
    async fn sqlite_trace_store_conforms() {
        trace_store_conformance(
            SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}")),
        )
        .await;
    }

    #[tokio::test]
    async fn in_memory_trace_store_conforms() {
        trace_store_conformance(InMemoryTraceStore::new()).await;
    }

    #[tokio::test]
    async fn sqlite_metadata_store_conforms() {
        metadata_store_conformance(
            SqliteMetadataStore::in_memory().unwrap_or_else(|err| panic!("{err}")),
        )
        .await;
    }

    #[tokio::test]
    async fn in_memory_metadata_store_conforms() {
        metadata_store_conformance(InMemoryMetadataStore::new()).await;
    }

    #[tokio::test]
    async fn sqlite_quota_limiter_conforms() {
        quota_limiter_conformance(
            SqliteQuotaLimiter::in_memory().unwrap_or_else(|err| panic!("{err}")),
        )
        .await;
    }

    #[tokio::test]
    async fn in_memory_quota_limiter_conforms() {
        quota_limiter_conformance(InMemoryQuotaLimiter::new()).await;
    }

    async fn trace_store_conformance<S>(store: S)
    where
        S: TraceStore,
    {
        let (batch, tenant, project, trace, idempotency_key) = fixture_batch();

        let first = store
            .write_batch(batch.clone())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let second = store
            .write_batch(batch)
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        assert_eq!(first.accepted_raw, 1);
        assert_eq!(first.accepted_spans, 2);
        assert_eq!(second.duplicate_raw, 1);
        assert_eq!(second.duplicate_spans, 2);

        let trace_view = store
            .get_trace(tenant.clone(), trace.clone())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(trace_view.spans.len(), 2);
        assert_eq!(trace_view.spans[0].span_id.as_str(), "root");
        assert_eq!(trace_view.spans[1].span_id.as_str(), "child");

        let raw = store
            .get_raw_envelope(tenant.clone(), project, idempotency_key)
            .await
            .unwrap_or_else(|err| panic!("{err}"))
            .unwrap_or_else(|| panic!("raw envelope should exist"));
        assert_eq!(raw.source, SourceDialect::Native);

        let spans = store
            .query_spans(
                tenant.clone(),
                SpanFilter {
                    project_id: None,
                    environment_id: None,
                    trace_id: Some(trace.clone()),
                    span_id: None,
                    kind: Some(AgentSpanKind::AgentStep),
                    status: Some(SpanStatus::Ok),
                },
                PageRequest {
                    limit: 10,
                    cursor: None,
                },
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(spans.items.len(), 1);
        assert_eq!(spans.items[0].span_id.as_str(), "child");

        let other_tenant = TenantId::new("other").unwrap_or_else(|err| panic!("{err}"));
        let empty = store
            .query_spans(other_tenant, SpanFilter::default(), PageRequest::default())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert!(empty.items.is_empty());

        let runs = store
            .query_runs(tenant, RunFilter::default(), PageRequest::default())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(runs.items.len(), 1);
        assert_eq!(runs.items[0].span_count, 2);
    }

    async fn metadata_store_conformance<S>(store: S)
    where
        S: MetadataStore,
    {
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let organization = OrganizationId::new("org").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));
        let environment = EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}"));
        let created_at = Utc
            .with_ymd_and_hms(2026, 1, 1, 0, 0, 0)
            .single()
            .unwrap_or_else(|| panic!("valid timestamp"));

        store
            .put_organization(OrganizationMetadata {
                tenant_id: tenant.clone(),
                organization_id: organization.clone(),
                display_name: "Org".to_string(),
                created_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        store
            .put_project(ProjectMetadata {
                tenant_id: tenant.clone(),
                organization_id: organization.clone(),
                project_id: project.clone(),
                display_name: "Project".to_string(),
                created_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        store
            .put_environment(EnvironmentMetadata {
                tenant_id: tenant.clone(),
                project_id: project.clone(),
                environment_id: environment.clone(),
                display_name: "Production".to_string(),
                created_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        store
            .put_role_binding(RoleBinding {
                tenant_id: tenant.clone(),
                project_id: Some(project.clone()),
                principal_id: "api-key:admin".to_string(),
                role: "project_admin".to_string(),
                permissions: BTreeSet::from(["admin".to_string()]),
                created_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        let loaded_environment = store
            .get_environment(tenant.clone(), project.clone(), environment)
            .await
            .unwrap_or_else(|err| panic!("{err}"))
            .unwrap_or_else(|| panic!("environment should exist"));
        assert_eq!(loaded_environment.display_name, "Production");

        let bindings = store
            .list_role_bindings(tenant, Some(project), "api-key:admin".to_string())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(bindings.len(), 1);
        assert!(bindings[0].permissions.contains("admin"));
    }

    async fn quota_limiter_conformance<L>(limiter: L)
    where
        L: QuotaLimiter,
    {
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));
        let window_start = Utc
            .with_ymd_and_hms(2026, 1, 1, 0, 0, 0)
            .single()
            .unwrap_or_else(|| panic!("valid timestamp"));
        let reset_at = Utc
            .with_ymd_and_hms(2026, 1, 1, 0, 1, 0)
            .single()
            .unwrap_or_else(|| panic!("valid timestamp"));

        let first = limiter
            .reserve_quota(QuotaReservationRequest {
                tenant_id: tenant.clone(),
                project_id: project.clone(),
                amount: 2,
                limit: 3,
                window_start,
                reset_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert!(first.accepted);
        assert_eq!(first.used, 2);

        let rejected = limiter
            .reserve_quota(QuotaReservationRequest {
                tenant_id: tenant.clone(),
                project_id: project.clone(),
                amount: 2,
                limit: 3,
                window_start,
                reset_at,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert!(!rejected.accepted);
        assert_eq!(rejected.used, 2);
        assert_eq!(rejected.reset_at, reset_at);

        let next_window = Utc
            .with_ymd_and_hms(2026, 1, 1, 0, 1, 0)
            .single()
            .unwrap_or_else(|| panic!("valid timestamp"));
        let next_reset = Utc
            .with_ymd_and_hms(2026, 1, 1, 0, 2, 0)
            .single()
            .unwrap_or_else(|| panic!("valid timestamp"));
        let after_reset = limiter
            .reserve_quota(QuotaReservationRequest {
                tenant_id: tenant,
                project_id: project,
                amount: 3,
                limit: 3,
                window_start: next_window,
                reset_at: next_reset,
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert!(after_reset.accepted);
        assert_eq!(after_reset.used, 3);
    }

    fn fixture_batch() -> (
        CanonicalTraceBatch,
        TenantId,
        ProjectId,
        TraceId,
        IdempotencyKey,
    ) {
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));
        let environment = EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}"));
        let _scope = TenantScope::new(tenant.clone(), project.clone(), environment.clone());
        let trace = TraceId::new("trace").unwrap_or_else(|err| panic!("{err}"));
        let idempotency_key =
            IdempotencyKey::new("tenant:project:trace:raw").unwrap_or_else(|err| panic!("{err}"));
        let body_ref = artifact_ref("raw");
        let raw = RawEnvelope {
            schema_version: RAW_SCHEMA_VERSION,
            tenant_id: tenant.clone(),
            project_id: project.clone(),
            environment_id: environment.clone(),
            source: SourceDialect::Native,
            source_schema_url: Some("beater://native/v1".to_string()),
            source_schema_version: Some("1".to_string()),
            received_at: Utc
                .with_ymd_and_hms(2026, 1, 1, 0, 0, 0)
                .single()
                .unwrap_or_else(|| panic!("valid timestamp")),
            idempotency_key: idempotency_key.clone(),
            payload_hash: body_ref.sha256.clone(),
            body_ref: body_ref.clone(),
            auth_context: AuthContext {
                api_key_id: None,
                scopes: BTreeSet::new(),
            },
        };
        let root = canonical_span(CanonicalSpanFixture {
            tenant: &tenant,
            project: &project,
            environment: &environment,
            trace: &trace,
            span: "root",
            seq: 1,
            kind: AgentSpanKind::AgentRun,
            name: "run",
            raw_ref: body_ref.clone(),
        });
        let child = canonical_span(CanonicalSpanFixture {
            tenant: &tenant,
            project: &project,
            environment: &environment,
            trace: &trace,
            span: "child",
            seq: 2,
            kind: AgentSpanKind::AgentStep,
            name: "step",
            raw_ref: body_ref,
        });
        (
            CanonicalTraceBatch {
                raw_envelopes: vec![raw],
                spans: vec![child, root],
            },
            tenant,
            project,
            trace,
            idempotency_key,
        )
    }

    struct CanonicalSpanFixture<'a> {
        tenant: &'a TenantId,
        project: &'a ProjectId,
        environment: &'a EnvironmentId,
        trace: &'a TraceId,
        span: &'a str,
        seq: u64,
        kind: AgentSpanKind,
        name: &'a str,
        raw_ref: ArtifactRef,
    }

    fn canonical_span(fixture: CanonicalSpanFixture<'_>) -> CanonicalSpan {
        CanonicalSpan {
            schema_version: CANONICAL_SCHEMA_VERSION,
            normalizer_version: "beater-native-v1".to_string(),
            tenant_id: fixture.tenant.clone(),
            project_id: fixture.project.clone(),
            environment_id: fixture.environment.clone(),
            trace_id: fixture.trace.clone(),
            span_id: SpanId::new(fixture.span).unwrap_or_else(|err| panic!("{err}")),
            parent_span_id: None,
            seq: fixture.seq,
            kind: fixture.kind,
            name: fixture.name.to_string(),
            status: SpanStatus::Ok,
            start_time: Utc
                .with_ymd_and_hms(2026, 1, 1, 0, 0, fixture.seq as u32)
                .single()
                .unwrap_or_else(|| panic!("valid timestamp")),
            end_time: None,
            model: None,
            cost: None,
            tokens: None,
            input_ref: None,
            output_ref: None,
            attributes: BTreeMap::new(),
            unmapped_attrs: json!({}),
            raw_ref: fixture.raw_ref,
        }
    }

    fn artifact_ref(name: &str) -> ArtifactRef {
        ArtifactRef {
            artifact_id: beater_core::ArtifactId::new(name).unwrap_or_else(|err| panic!("{err}")),
            uri: format!("artifact://tenant/project/{name}"),
            sha256: Sha256Hash::new("ab".repeat(32)).unwrap_or_else(|err| panic!("{err}")),
            size_bytes: 2,
            mime_type: "application/json".to_string(),
            redaction_class: RedactionClass::Internal,
        }
    }
}
