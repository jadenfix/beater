use anyhow::{anyhow, Context};
use async_trait::async_trait;
use beater_core::{
    ArtifactId, IdempotencyKey, Page, PageRequest, ProjectId, Sha256Hash, TenantId, TraceId,
};
use beater_schema::{
    ArtifactRef, CanonicalSpan, CanonicalTraceBatch, RawEnvelope, RedactionClass, RunFilter,
    RunSummary, SpanFilter, SpanStatus, SpanSummary, TraceView, WriteAck,
};
use rusqlite::{params, Connection, OptionalExtension};
use sha2::{Digest, Sha256};
use std::fs;
use std::path::{Path, PathBuf};
use std::sync::{Arc, Mutex};
use uuid::Uuid;

#[async_trait]
pub trait ArtifactStore: Send + Sync {
    async fn put_bytes(
        &self,
        tenant_id: &TenantId,
        project_id: &ProjectId,
        mime_type: &str,
        redaction_class: RedactionClass,
        bytes: &[u8],
    ) -> anyhow::Result<ArtifactRef>;

    async fn get_bytes(&self, artifact_ref: &ArtifactRef) -> anyhow::Result<Vec<u8>>;
}

#[async_trait]
pub trait TraceStore: Send + Sync {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> anyhow::Result<WriteAck>;

    async fn get_trace(&self, tenant: TenantId, trace: TraceId) -> anyhow::Result<TraceView>;

    async fn get_raw_envelope(
        &self,
        tenant: TenantId,
        project: ProjectId,
        idempotency_key: IdempotencyKey,
    ) -> anyhow::Result<Option<RawEnvelope>>;

    async fn query_runs(
        &self,
        tenant: TenantId,
        filter: RunFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<RunSummary>>;

    async fn query_spans(
        &self,
        tenant: TenantId,
        filter: SpanFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<SpanSummary>>;
}

#[derive(Clone, Debug)]
pub struct FsArtifactStore {
    root: Arc<PathBuf>,
}

impl FsArtifactStore {
    pub fn new(root: impl Into<PathBuf>) -> anyhow::Result<Self> {
        let root = root.into();
        fs::create_dir_all(&root)
            .with_context(|| format!("create artifact root {}", root.display()))?;
        Ok(Self {
            root: Arc::new(root),
        })
    }

    fn path_for_uri(&self, uri: &str) -> anyhow::Result<PathBuf> {
        let prefix = "artifact://";
        let relative = uri
            .strip_prefix(prefix)
            .ok_or_else(|| anyhow!("unsupported artifact uri: {uri}"))?;
        if relative.split('/').any(|segment| segment == "..") {
            return Err(anyhow!("artifact uri cannot contain '..': {uri}"));
        }
        Ok(self.root.join(relative))
    }
}

#[async_trait]
impl ArtifactStore for FsArtifactStore {
    async fn put_bytes(
        &self,
        tenant_id: &TenantId,
        project_id: &ProjectId,
        mime_type: &str,
        redaction_class: RedactionClass,
        bytes: &[u8],
    ) -> anyhow::Result<ArtifactRef> {
        let artifact_id = ArtifactId::new(Uuid::new_v4().to_string())?;
        let hash = sha256_hex(bytes);
        let sha256 = Sha256Hash::new(hash)?;
        let relative = format!(
            "{}/{}/{}",
            tenant_id.as_str(),
            project_id.as_str(),
            artifact_id.as_str()
        );
        let path = self.root.join(&relative);
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent)
                .with_context(|| format!("create artifact dir {}", parent.display()))?;
        }
        fs::write(&path, bytes).with_context(|| format!("write artifact {}", path.display()))?;

        Ok(ArtifactRef {
            artifact_id,
            uri: format!("artifact://{relative}"),
            sha256,
            size_bytes: bytes.len() as u64,
            mime_type: mime_type.to_string(),
            redaction_class,
        })
    }

    async fn get_bytes(&self, artifact_ref: &ArtifactRef) -> anyhow::Result<Vec<u8>> {
        let path = self.path_for_uri(&artifact_ref.uri)?;
        let bytes = fs::read(&path).with_context(|| format!("read artifact {}", path.display()))?;
        let actual = sha256_hex(&bytes);
        if actual != artifact_ref.sha256.as_str() {
            return Err(anyhow!(
                "artifact hash mismatch for {}: expected {}, got {}",
                artifact_ref.uri,
                artifact_ref.sha256.as_str(),
                actual
            ));
        }
        Ok(bytes)
    }
}

#[derive(Clone)]
pub struct SqliteTraceStore {
    connection: Arc<Mutex<Connection>>,
}

impl SqliteTraceStore {
    pub fn in_memory() -> anyhow::Result<Self> {
        let connection = Connection::open_in_memory().context("open in-memory sqlite")?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    pub fn open(path: impl AsRef<Path>) -> anyhow::Result<Self> {
        let path = path.as_ref();
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent)
                .with_context(|| format!("create sqlite dir {}", parent.display()))?;
        }
        let connection = Connection::open(path)
            .with_context(|| format!("open sqlite trace store {}", path.display()))?;
        let store = Self {
            connection: Arc::new(Mutex::new(connection)),
        };
        store.init()?;
        Ok(store)
    }

    fn init(&self) -> anyhow::Result<()> {
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
            .context("initialize sqlite trace store")?;
        Ok(())
    }

    fn lock(&self) -> anyhow::Result<std::sync::MutexGuard<'_, Connection>> {
        self.connection
            .lock()
            .map_err(|err| anyhow!("sqlite connection mutex poisoned: {err}"))
    }
}

#[async_trait]
impl TraceStore for SqliteTraceStore {
    async fn write_batch(&self, batch: CanonicalTraceBatch) -> anyhow::Result<WriteAck> {
        let mut connection = self.lock()?;
        let tx = connection
            .transaction()
            .context("begin trace write transaction")?;

        let mut accepted_raw = 0;
        let mut duplicate_raw = 0;
        for raw in &batch.raw_envelopes {
            let raw_json = serde_json::to_string(raw).context("serialize raw envelope")?;
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
                .context("insert raw envelope")?;
            if changed == 0 {
                duplicate_raw += 1;
            } else {
                accepted_raw += 1;
            }
        }

        let mut accepted_spans = 0;
        let mut duplicate_spans = 0;
        for span in &batch.spans {
            let span_json = serde_json::to_string(span).context("serialize canonical span")?;
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
                .context("insert canonical span")?;
            if changed == 0 {
                duplicate_spans += 1;
            } else {
                accepted_spans += 1;
            }
        }

        tx.commit().context("commit trace write transaction")?;
        Ok(WriteAck {
            accepted_raw,
            accepted_spans,
            duplicate_raw,
            duplicate_spans,
        })
    }

    async fn get_trace(&self, tenant: TenantId, trace: TraceId) -> anyhow::Result<TraceView> {
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
            .context("prepare get_trace")?;
        let rows = statement
            .query_map(params![tenant.as_str(), trace.as_str()], |row| {
                row.get::<_, String>(0)
            })
            .context("query trace spans")?;

        let mut spans = Vec::new();
        for row in rows {
            let json = row.context("read span row")?;
            spans.push(serde_json::from_str::<CanonicalSpan>(&json).context("decode span row")?);
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
    ) -> anyhow::Result<Option<RawEnvelope>> {
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
            .context("get raw envelope")?;
        raw_json
            .map(|json| serde_json::from_str::<RawEnvelope>(&json).context("decode raw envelope"))
            .transpose()
    }

    async fn query_runs(
        &self,
        tenant: TenantId,
        filter: RunFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<RunSummary>> {
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

        let mut runs = Vec::<RunSummary>::new();
        for span in spans {
            if let Some(run) = runs
                .iter_mut()
                .find(|run| run.trace_id.as_str() == span.trace_id.as_str())
            {
                run.span_count += 1;
                if run.status != SpanStatus::Error && span.status == SpanStatus::Error {
                    run.status = SpanStatus::Error;
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
        Ok(page_vec(runs, page))
    }

    async fn query_spans(
        &self,
        tenant: TenantId,
        filter: SpanFilter,
        page: PageRequest,
    ) -> anyhow::Result<Page<SpanSummary>> {
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
            .context("prepare query_spans")?;
        let rows = statement
            .query_map(params![tenant.as_str()], |row| row.get::<_, String>(0))
            .context("query spans")?;

        let mut spans = Vec::new();
        for row in rows {
            let json = row.context("read span row")?;
            let span = serde_json::from_str::<CanonicalSpan>(&json).context("decode span row")?;
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

fn span_matches(span: &CanonicalSpan, filter: &SpanFilter) -> bool {
    if let Some(trace_id) = &filter.trace_id {
        if span.trace_id.as_str() != trace_id.as_str() {
            return false;
        }
    }
    if let Some(span_id) = &filter.span_id {
        if span.span_id.as_str() != span_id.as_str() {
            return false;
        }
    }
    if let Some(kind) = &filter.kind {
        if &span.kind != kind {
            return false;
        }
    }
    if let Some(status) = &filter.status {
        if &span.status != status {
            return false;
        }
    }
    true
}

fn page_vec<T>(mut items: Vec<T>, page: PageRequest) -> Page<T> {
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

fn status_name(status: &SpanStatus) -> &'static str {
    match status {
        SpanStatus::Ok => "ok",
        SpanStatus::Error => "error",
        SpanStatus::Unset => "unset",
    }
}

pub fn sha256_hex(bytes: &[u8]) -> String {
    let digest = Sha256::digest(bytes);
    digest.iter().map(|byte| format!("{byte:02x}")).collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_core::{EnvironmentId, IdempotencyKey, SpanId, TenantScope};
    use beater_schema::{
        AgentSpanKind, AuthContext, RawEnvelope, SourceDialect, CANONICAL_SCHEMA_VERSION,
        RAW_SCHEMA_VERSION,
    };
    use chrono::Utc;
    use serde_json::json;
    use std::collections::{BTreeMap, BTreeSet};

    #[tokio::test]
    async fn fs_artifact_store_round_trips_and_checks_hash() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let store = FsArtifactStore::new(tempdir.path()).unwrap_or_else(|err| panic!("{err}"));
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));

        let artifact = store
            .put_bytes(
                &tenant,
                &project,
                "application/json",
                RedactionClass::Sensitive,
                br#"{"ok":true}"#,
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        let bytes = store
            .get_bytes(&artifact)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(bytes, br#"{"ok":true}"#);
    }

    #[tokio::test]
    async fn sqlite_trace_store_is_idempotent_and_tenant_scoped() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let artifact_store = FsArtifactStore::new(tempdir.path().join("artifacts"))
            .unwrap_or_else(|err| panic!("{err}"));
        let trace_store = SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}"));
        let (batch, tenant, trace) = fixture_batch(&artifact_store).await;

        let first = trace_store
            .write_batch(batch.clone())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let second = trace_store
            .write_batch(batch)
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        assert_eq!(first.accepted_raw, 1);
        assert_eq!(first.accepted_spans, 1);
        assert_eq!(second.duplicate_raw, 1);
        assert_eq!(second.duplicate_spans, 1);

        let trace_view = trace_store
            .get_trace(tenant.clone(), trace)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(trace_view.spans.len(), 1);

        let other_tenant = TenantId::new("other").unwrap_or_else(|err| panic!("{err}"));
        let empty = trace_store
            .query_spans(other_tenant, SpanFilter::default(), PageRequest::default())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert!(empty.items.is_empty());

        let runs = trace_store
            .query_runs(tenant, RunFilter::default(), PageRequest::default())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(runs.items.len(), 1);
        assert_eq!(runs.items[0].span_count, 1);
    }

    async fn fixture_batch(
        artifact_store: &FsArtifactStore,
    ) -> (CanonicalTraceBatch, TenantId, TraceId) {
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));
        let environment = EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}"));
        let scope = TenantScope::new(tenant.clone(), project.clone(), environment.clone());
        let trace = TraceId::new("trace").unwrap_or_else(|err| panic!("{err}"));
        let span = SpanId::new("span").unwrap_or_else(|err| panic!("{err}"));
        let body = br#"{"trace_id":"trace"}"#;
        let body_ref = artifact_store
            .put_bytes(
                &tenant,
                &project,
                "application/json",
                RedactionClass::Internal,
                body,
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let idempotency_key = IdempotencyKey::new("tenant:project:trace:span:1:hash")
            .unwrap_or_else(|err| panic!("{err}"));
        let raw = RawEnvelope {
            schema_version: RAW_SCHEMA_VERSION,
            tenant_id: tenant.clone(),
            project_id: project.clone(),
            environment_id: environment.clone(),
            source: SourceDialect::Native,
            source_schema_url: Some("beater://native/v1".to_string()),
            source_schema_version: Some("1".to_string()),
            received_at: Utc::now(),
            idempotency_key,
            payload_hash: body_ref.sha256.clone(),
            body_ref: body_ref.clone(),
            auth_context: AuthContext {
                api_key_id: None,
                scopes: BTreeSet::new(),
            },
        };
        let canonical = CanonicalSpan {
            schema_version: CANONICAL_SCHEMA_VERSION,
            normalizer_version: "beater-native-v1".to_string(),
            tenant_id: tenant.clone(),
            project_id: project.clone(),
            environment_id: environment,
            trace_id: trace.clone(),
            span_id: span,
            parent_span_id: None,
            seq: 1,
            kind: AgentSpanKind::AgentRun,
            name: "run".to_string(),
            status: SpanStatus::Ok,
            start_time: Utc::now(),
            end_time: None,
            model: None,
            cost: None,
            tokens: None,
            input_ref: None,
            output_ref: None,
            attributes: BTreeMap::new(),
            unmapped_attrs: json!({}),
            raw_ref: body_ref,
        };
        let _ = scope;
        (CanonicalTraceBatch::one(raw, canonical), tenant, trace)
    }
}
