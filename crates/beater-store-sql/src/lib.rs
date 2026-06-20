use async_trait::async_trait;
use beater_core::{IdempotencyKey, Page, PageRequest, ProjectId, TenantId, TraceId};
use beater_schema::{
    CanonicalSpan, CanonicalTraceBatch, RawEnvelope, RunFilter, RunSummary, SpanFilter, SpanStatus,
    SpanSummary, TraceView, WriteAck,
};
use beater_store::{page_vec, roll_up_runs, span_matches, StoreError, StoreResult, TraceStore};
use rusqlite::{params, Connection, OptionalExtension};
use std::fs;
use std::path::Path;
use std::sync::{Arc, Mutex};

#[derive(Clone)]
pub struct SqliteTraceStore {
    connection: Arc<Mutex<Connection>>,
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
                        status_name(&span.status),
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
        let connection = self.lock()?;
        let mut statement = connection
            .prepare(
                r#"
                SELECT span_json
                FROM spans
                WHERE tenant_id = ?1
                ORDER BY start_time DESC, seq ASC
                "#,
            )
            .map_err(StoreError::backend)?;
        let rows = statement
            .query_map(params![tenant.as_str()], |row| row.get::<_, String>(0))
            .map_err(StoreError::backend)?;

        let mut spans = Vec::new();
        for row in rows {
            let json = row.map_err(StoreError::backend)?;
            let span = serde_json::from_str::<CanonicalSpan>(&json).map_err(StoreError::backend)?;
            if !span_matches(&span, &filter) {
                continue;
            }
            spans.push(SpanSummary {
                tenant_id: span.tenant_id,
                trace_id: span.trace_id,
                span_id: span.span_id,
                kind: span.kind,
                name: span.name,
                status: span.status,
                started_at: span.start_time,
                ended_at: span.end_time,
            });
        }

        Ok(page_vec(spans, page))
    }
}

fn status_name(status: &SpanStatus) -> &'static str {
    match status {
        SpanStatus::Ok => "ok",
        SpanStatus::Error => "error",
        SpanStatus::Unset => "unset",
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_core::{EnvironmentId, IdempotencyKey, Sha256Hash, SpanId, TenantScope};
    use beater_schema::{
        AgentSpanKind, ArtifactRef, AuthContext, RedactionClass, SourceDialect,
        CANONICAL_SCHEMA_VERSION, RAW_SCHEMA_VERSION,
    };
    use beater_store::InMemoryTraceStore;
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
