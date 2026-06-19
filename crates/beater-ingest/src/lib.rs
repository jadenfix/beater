use beater_bus::{BusMessage, DurableBus};
use beater_core::{
    EnvironmentId, IdempotencyKey, ProjectId, Sha256Hash, SpanId, TenantId, TenantScope, Timestamp,
    TokenCounts, TraceId,
};
use beater_schema::{
    make_idempotency_key, AgentSpanKind, ArtifactRef, AuthContext, CanonicalAttrs, CanonicalSpan,
    CanonicalTraceBatch, ModelRef, RawEnvelope, RedactionClass, SourceDialect, SpanStatus,
    TraceCompletionState, WriteAck, CANONICAL_SCHEMA_VERSION, RAW_SCHEMA_VERSION,
};
use beater_store::{sha256_hex, ArtifactStore, TraceStore};
use chrono::{Duration, Utc};
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use std::collections::{BTreeMap, BTreeSet, HashMap};
use std::sync::{Arc, Mutex};

#[derive(Debug, thiserror::Error)]
pub enum IngestError {
    #[error("quota exceeded for tenant={tenant_id} project={project_id}; limit={limit}")]
    QuotaExceeded {
        tenant_id: String,
        project_id: String,
        limit: u64,
    },
    #[error("too many attributes: {count} > {limit}")]
    TooManyAttributes { count: usize, limit: usize },
    #[error("payload too large: {size_bytes} > {limit_bytes}")]
    PayloadTooLarge {
        size_bytes: usize,
        limit_bytes: usize,
    },
    #[error(transparent)]
    Other(#[from] anyhow::Error),
}

#[derive(Clone)]
pub struct IngestService {
    artifacts: Arc<dyn ArtifactStore>,
    traces: Arc<dyn TraceStore>,
    bus: Arc<dyn DurableBus>,
    policy: IngestPolicy,
    quota: Arc<Mutex<HashMap<String, u64>>>,
}

impl IngestService {
    pub fn new(
        artifacts: Arc<dyn ArtifactStore>,
        traces: Arc<dyn TraceStore>,
        bus: Arc<dyn DurableBus>,
        policy: IngestPolicy,
    ) -> Self {
        Self {
            artifacts,
            traces,
            bus,
            policy,
            quota: Arc::new(Mutex::new(HashMap::new())),
        }
    }

    pub async fn ingest_native(
        &self,
        request: NativeIngestRequest,
    ) -> Result<IngestOutcome, IngestError> {
        self.enforce_quota_events(&request.scope, 1)?;
        let raw_bytes = serde_json::to_vec(&request).map_err(anyhow::Error::from)?;
        if raw_bytes.len() > self.policy.max_raw_payload_bytes {
            return Err(IngestError::PayloadTooLarge {
                size_bytes: raw_bytes.len(),
                limit_bytes: self.policy.max_raw_payload_bytes,
            });
        }

        let raw_ref = self
            .artifacts
            .put_bytes(
                &request.scope.tenant_id,
                &request.scope.project_id,
                "application/json",
                request.redaction_class.clone(),
                &raw_bytes,
            )
            .await
            .map_err(IngestError::Other)?;
        let payload_hash = Sha256Hash::new(sha256_hex(&raw_bytes)).map_err(anyhow::Error::from)?;
        let idempotency_key = request
            .idempotency_key
            .clone()
            .map(Ok)
            .unwrap_or_else(|| {
                make_idempotency_key(
                    &request.scope,
                    &request.trace_id,
                    &request.span_id,
                    request.seq,
                    &payload_hash,
                )
            })
            .map_err(anyhow::Error::from)?;

        let raw = RawEnvelope {
            schema_version: RAW_SCHEMA_VERSION,
            tenant_id: request.scope.tenant_id.clone(),
            project_id: request.scope.project_id.clone(),
            environment_id: request.scope.environment_id.clone(),
            source: SourceDialect::Native,
            source_schema_url: Some("beater://native/v1".to_string()),
            source_schema_version: Some("1".to_string()),
            received_at: Utc::now(),
            idempotency_key: idempotency_key.clone(),
            payload_hash,
            body_ref: raw_ref.clone(),
            auth_context: request
                .auth_context
                .clone()
                .unwrap_or_else(anonymous_auth_context),
        };

        let (attributes, unmapped_attrs) = self.govern_attributes(request.attributes)?;
        let input_ref = self
            .maybe_payload_artifact(
                &request.scope,
                request.input.as_ref(),
                &request.redaction_class,
                "application/json",
            )
            .await?;
        let output_ref = self
            .maybe_payload_artifact(
                &request.scope,
                request.output.as_ref(),
                &request.redaction_class,
                "application/json",
            )
            .await?;

        let mut canonical_attrs = attributes;
        if input_ref.is_none() {
            if let Some(input) = request.input.clone() {
                canonical_attrs.insert("input.value".to_string(), input);
            }
        }
        if output_ref.is_none() {
            if let Some(output) = request.output.clone() {
                canonical_attrs.insert("output.value".to_string(), output);
            }
        }

        let span = CanonicalSpan {
            schema_version: CANONICAL_SCHEMA_VERSION,
            normalizer_version: "beater-native-v1".to_string(),
            tenant_id: request.scope.tenant_id.clone(),
            project_id: request.scope.project_id.clone(),
            environment_id: request.scope.environment_id.clone(),
            trace_id: request.trace_id.clone(),
            span_id: request.span_id,
            parent_span_id: request.parent_span_id,
            seq: request.seq,
            kind: request.kind,
            name: request.name,
            status: request.status,
            start_time: request.start_time.unwrap_or_else(Utc::now),
            end_time: request.end_time,
            model: request.model,
            cost: request.cost,
            tokens: request.tokens,
            input_ref,
            output_ref,
            attributes: canonical_attrs,
            unmapped_attrs,
            raw_ref,
        };

        let trace_id = span.trace_id.clone();
        let batch = CanonicalTraceBatch::one(raw, span);
        let ack = self
            .traces
            .write_batch(batch)
            .await
            .map_err(IngestError::Other)?;

        let queue_payload = serde_json::to_vec(&QueuedTraceWork {
            tenant_id: request.scope.tenant_id.clone(),
            project_id: request.scope.project_id.clone(),
            trace_id,
        })
        .map_err(anyhow::Error::from)?;
        self.bus
            .publish(BusMessage::new(
                request.scope.tenant_id,
                request.scope.project_id,
                idempotency_key,
                "trace.ingested",
                queue_payload,
            ))
            .await
            .map_err(|err| IngestError::Other(anyhow::Error::new(err)))?;

        Ok(IngestOutcome {
            ack,
            downstream_queued: true,
        })
    }

    pub async fn ingest_raw_trace_batch(
        &self,
        request: RawTraceIngestRequest,
    ) -> Result<IngestOutcome, IngestError> {
        let scope = request.scope.clone();
        self.enforce_quota_events(&scope, request.spans.len() as u64)?;
        if request.raw_bytes.len() > self.policy.max_raw_payload_bytes {
            return Err(IngestError::PayloadTooLarge {
                size_bytes: request.raw_bytes.len(),
                limit_bytes: self.policy.max_raw_payload_bytes,
            });
        }

        let raw_ref = self
            .artifacts
            .put_bytes(
                &scope.tenant_id,
                &scope.project_id,
                &request.mime_type,
                request.redaction_class.clone(),
                &request.raw_bytes,
            )
            .await
            .map_err(IngestError::Other)?;
        let payload_hash =
            Sha256Hash::new(sha256_hex(&request.raw_bytes)).map_err(anyhow::Error::from)?;
        let raw_idempotency_key = request
            .raw_idempotency_key
            .clone()
            .map(Ok)
            .unwrap_or_else(|| {
                IdempotencyKey::new(format!(
                    "raw:{}:{}:{}:{}",
                    request.source.as_str(),
                    scope.tenant_id.as_str(),
                    scope.project_id.as_str(),
                    payload_hash.as_str()
                ))
            })
            .map_err(anyhow::Error::from)?;

        let raw = RawEnvelope {
            schema_version: RAW_SCHEMA_VERSION,
            tenant_id: scope.tenant_id.clone(),
            project_id: scope.project_id.clone(),
            environment_id: scope.environment_id.clone(),
            source: request.source,
            source_schema_url: request.source_schema_url,
            source_schema_version: request.source_schema_version,
            received_at: Utc::now(),
            idempotency_key: raw_idempotency_key.clone(),
            payload_hash,
            body_ref: raw_ref.clone(),
            auth_context: request.auth_context.unwrap_or_else(anonymous_auth_context),
        };

        let mut trace_ids = BTreeSet::new();
        let mut spans = Vec::with_capacity(request.spans.len());
        for draft in request.spans {
            let (attributes, unmapped_attrs) = self.govern_attributes(draft.attributes)?;
            let input_ref = self
                .maybe_payload_artifact(
                    &scope,
                    draft.input.as_ref(),
                    &request.redaction_class,
                    "application/json",
                )
                .await?;
            let output_ref = self
                .maybe_payload_artifact(
                    &scope,
                    draft.output.as_ref(),
                    &request.redaction_class,
                    "application/json",
                )
                .await?;
            let mut canonical_attrs = attributes;
            if input_ref.is_none() {
                if let Some(input) = draft.input.clone() {
                    canonical_attrs.insert("input.value".to_string(), input);
                }
            }
            if output_ref.is_none() {
                if let Some(output) = draft.output.clone() {
                    canonical_attrs.insert("output.value".to_string(), output);
                }
            }

            let span = CanonicalSpan {
                schema_version: CANONICAL_SCHEMA_VERSION,
                normalizer_version: request.normalizer_version.clone(),
                tenant_id: scope.tenant_id.clone(),
                project_id: scope.project_id.clone(),
                environment_id: scope.environment_id.clone(),
                trace_id: draft.trace_id,
                span_id: draft.span_id,
                parent_span_id: draft.parent_span_id,
                seq: draft.seq,
                kind: draft.kind,
                name: draft.name,
                status: draft.status,
                start_time: draft.start_time.unwrap_or_else(Utc::now),
                end_time: draft.end_time,
                model: draft.model,
                cost: draft.cost,
                tokens: draft.tokens,
                input_ref,
                output_ref,
                attributes: canonical_attrs,
                unmapped_attrs,
                raw_ref: raw_ref.clone(),
            };
            trace_ids.insert(span.trace_id.clone());
            spans.push(span);
        }

        let ack = self
            .traces
            .write_batch(CanonicalTraceBatch {
                raw_envelopes: vec![raw],
                spans,
            })
            .await
            .map_err(IngestError::Other)?;

        for trace_id in &trace_ids {
            let queue_payload = serde_json::to_vec(&QueuedTraceWork {
                tenant_id: scope.tenant_id.clone(),
                project_id: scope.project_id.clone(),
                trace_id: trace_id.clone(),
            })
            .map_err(anyhow::Error::from)?;
            let queue_key = IdempotencyKey::new(format!(
                "{}:{}",
                raw_idempotency_key.as_str(),
                trace_id.as_str()
            ))
            .map_err(anyhow::Error::from)?;
            self.bus
                .publish(BusMessage::new(
                    scope.tenant_id.clone(),
                    scope.project_id.clone(),
                    queue_key,
                    "trace.ingested",
                    queue_payload,
                ))
                .await
                .map_err(|err| IngestError::Other(anyhow::Error::new(err)))?;
        }

        Ok(IngestOutcome {
            ack,
            downstream_queued: !trace_ids.is_empty(),
        })
    }

    fn enforce_quota_events(
        &self,
        scope: &TenantScope,
        event_count: u64,
    ) -> Result<(), IngestError> {
        let Some(limit) = self.policy.per_project_event_quota else {
            return Ok(());
        };
        if event_count == 0 {
            return Ok(());
        }
        let key = format!("{}:{}", scope.tenant_id.as_str(), scope.project_id.as_str());
        let mut quota = self
            .quota
            .lock()
            .map_err(|err| IngestError::Other(anyhow::anyhow!("quota mutex poisoned: {err}")))?;
        let count = quota.entry(key).or_insert(0);
        if count.saturating_add(event_count) > limit {
            return Err(IngestError::QuotaExceeded {
                tenant_id: scope.tenant_id.to_string(),
                project_id: scope.project_id.to_string(),
                limit,
            });
        }
        *count += event_count;
        Ok(())
    }

    fn govern_attributes(
        &self,
        attributes: CanonicalAttrs,
    ) -> Result<(CanonicalAttrs, Value), IngestError> {
        if attributes.len() > self.policy.max_attributes {
            return Err(IngestError::TooManyAttributes {
                count: attributes.len(),
                limit: self.policy.max_attributes,
            });
        }
        let mut kept = BTreeMap::new();
        let mut dropped = BTreeMap::new();
        for (key, value) in attributes {
            if self.policy.denied_attributes.contains(&key) {
                dropped.insert(key, value);
                continue;
            }
            if let Some(allowed) = &self.policy.allowed_attributes {
                if !allowed.contains(&key) {
                    dropped.insert(key, value);
                    continue;
                }
            }
            kept.insert(key, value);
        }
        Ok((kept, json!({ "dropped_attributes": dropped })))
    }

    async fn maybe_payload_artifact(
        &self,
        scope: &TenantScope,
        value: Option<&Value>,
        redaction_class: &RedactionClass,
        mime_type: &str,
    ) -> Result<Option<ArtifactRef>, IngestError> {
        let Some(value) = value else {
            return Ok(None);
        };
        let bytes = serde_json::to_vec(value).map_err(anyhow::Error::from)?;
        if bytes.len() <= self.policy.inline_payload_bytes {
            return Ok(None);
        }
        self.artifacts
            .put_bytes(
                &scope.tenant_id,
                &scope.project_id,
                mime_type,
                redaction_class.clone(),
                &bytes,
            )
            .await
            .map(Some)
            .map_err(IngestError::Other)
    }
}

#[derive(Clone, Debug)]
pub struct IngestPolicy {
    pub max_raw_payload_bytes: usize,
    pub inline_payload_bytes: usize,
    pub max_attributes: usize,
    pub allowed_attributes: Option<BTreeSet<String>>,
    pub denied_attributes: BTreeSet<String>,
    pub per_project_event_quota: Option<u64>,
}

impl Default for IngestPolicy {
    fn default() -> Self {
        Self {
            max_raw_payload_bytes: 1024 * 1024,
            inline_payload_bytes: 16 * 1024,
            max_attributes: 128,
            allowed_attributes: None,
            denied_attributes: BTreeSet::new(),
            per_project_event_quota: None,
        }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct NativeIngestRequest {
    pub scope: TenantScope,
    pub trace_id: TraceId,
    pub span_id: SpanId,
    pub parent_span_id: Option<SpanId>,
    pub seq: u64,
    pub kind: AgentSpanKind,
    pub name: String,
    pub status: SpanStatus,
    pub start_time: Option<Timestamp>,
    pub end_time: Option<Timestamp>,
    pub model: Option<ModelRef>,
    pub cost: Option<beater_core::Money>,
    pub tokens: Option<TokenCounts>,
    pub input: Option<Value>,
    pub output: Option<Value>,
    pub attributes: CanonicalAttrs,
    pub redaction_class: RedactionClass,
    pub idempotency_key: Option<IdempotencyKey>,
    pub auth_context: Option<AuthContext>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RawTraceIngestRequest {
    pub scope: TenantScope,
    pub source: SourceDialect,
    pub source_schema_url: Option<String>,
    pub source_schema_version: Option<String>,
    pub normalizer_version: String,
    pub mime_type: String,
    pub redaction_class: RedactionClass,
    pub raw_bytes: Vec<u8>,
    pub raw_idempotency_key: Option<IdempotencyKey>,
    pub auth_context: Option<AuthContext>,
    pub spans: Vec<CanonicalSpanDraft>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct CanonicalSpanDraft {
    pub trace_id: TraceId,
    pub span_id: SpanId,
    pub parent_span_id: Option<SpanId>,
    pub seq: u64,
    pub kind: AgentSpanKind,
    pub name: String,
    pub status: SpanStatus,
    pub start_time: Option<Timestamp>,
    pub end_time: Option<Timestamp>,
    pub model: Option<ModelRef>,
    pub cost: Option<beater_core::Money>,
    pub tokens: Option<TokenCounts>,
    pub input: Option<Value>,
    pub output: Option<Value>,
    pub attributes: CanonicalAttrs,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct QueuedTraceWork {
    pub tenant_id: TenantId,
    pub project_id: ProjectId,
    pub trace_id: TraceId,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct IngestOutcome {
    pub ack: WriteAck,
    pub downstream_queued: bool,
}

pub fn anonymous_auth_context() -> AuthContext {
    AuthContext {
        api_key_id: None,
        scopes: BTreeSet::new(),
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct TraceCompletionInput {
    pub root_span_ended: bool,
    pub open_child_spans: usize,
    pub idle_for: Duration,
    pub idle_timeout: Duration,
    pub late_window_closed: bool,
}

pub fn trace_completion_state(input: TraceCompletionInput) -> TraceCompletionState {
    if input.root_span_ended && input.open_child_spans == 0 && input.late_window_closed {
        return TraceCompletionState::Complete;
    }
    if input.root_span_ended {
        return TraceCompletionState::RootEnded;
    }
    if input.idle_for >= input.idle_timeout && input.open_child_spans == 0 {
        return TraceCompletionState::IdleComplete;
    }
    if input.late_window_closed {
        return TraceCompletionState::LateWindowClosed;
    }
    TraceCompletionState::Open
}

pub async fn smoke_trace(service: &IngestService) -> Result<IngestOutcome, IngestError> {
    let scope = TenantScope::new(
        TenantId::new("demo").map_err(anyhow::Error::from)?,
        ProjectId::new("demo").map_err(anyhow::Error::from)?,
        EnvironmentId::new("local").map_err(anyhow::Error::from)?,
    );
    service
        .ingest_native(NativeIngestRequest {
            scope,
            trace_id: TraceId::new("smoke-trace").map_err(anyhow::Error::from)?,
            span_id: SpanId::new("smoke-root").map_err(anyhow::Error::from)?,
            parent_span_id: None,
            seq: 1,
            kind: AgentSpanKind::AgentRun,
            name: "smoke agent run".to_string(),
            status: SpanStatus::Ok,
            start_time: Some(Utc::now()),
            end_time: Some(Utc::now()),
            model: None,
            cost: None,
            tokens: None,
            input: Some(json!({ "prompt": "hello" })),
            output: Some(json!({ "answer": "world" })),
            attributes: BTreeMap::new(),
            redaction_class: RedactionClass::Internal,
            idempotency_key: None,
            auth_context: None,
        })
        .await
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_bus::InMemoryBus;
    use beater_store::{FsArtifactStore, SqliteTraceStore};

    #[tokio::test]
    async fn native_ingest_preserves_raw_and_canonical_span() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let artifacts = Arc::new(
            FsArtifactStore::new(tempdir.path().join("artifacts"))
                .unwrap_or_else(|err| panic!("{err}")),
        );
        let traces = Arc::new(SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}")));
        let bus = Arc::new(InMemoryBus::new(16));
        let service = IngestService::new(
            artifacts,
            traces.clone(),
            bus.clone(),
            IngestPolicy::default(),
        );
        let request = fixture_request();

        let outcome = service
            .ingest_native(request.clone())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(outcome.ack.accepted_raw, 1);
        assert_eq!(outcome.ack.accepted_spans, 1);
        assert_eq!(bus.depth().await, Ok(1));

        let trace = traces
            .get_trace(request.scope.tenant_id, request.trace_id)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(trace.spans.len(), 1);
        assert_eq!(trace.spans[0].normalizer_version, "beater-native-v1");
        assert_eq!(trace.spans[0].schema_version, CANONICAL_SCHEMA_VERSION);
        assert_eq!(
            trace.spans[0].unmapped_attrs["dropped_attributes"],
            json!({})
        );
    }

    #[tokio::test]
    async fn raw_trace_batch_preserves_external_source_bytes_and_envelope() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let artifacts = Arc::new(
            FsArtifactStore::new(tempdir.path().join("artifacts"))
                .unwrap_or_else(|err| panic!("{err}")),
        );
        let traces = Arc::new(SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}")));
        let bus = Arc::new(InMemoryBus::new(16));
        let service = IngestService::new(
            artifacts.clone(),
            traces.clone(),
            bus.clone(),
            IngestPolicy::default(),
        );
        let scope = TenantScope::new(
            TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}")),
            ProjectId::new("project").unwrap_or_else(|err| panic!("{err}")),
            EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}")),
        );
        let raw_idempotency_key =
            IdempotencyKey::new("otlp-raw-1").unwrap_or_else(|err| panic!("{err}"));
        let raw_bytes = b"\x0a\x05otlp".to_vec();

        let outcome = service
            .ingest_raw_trace_batch(RawTraceIngestRequest {
                scope: scope.clone(),
                source: SourceDialect::Otlp,
                source_schema_url: Some("https://opentelemetry.io/schemas/1.37.0".to_string()),
                source_schema_version: Some("1.37.0".to_string()),
                normalizer_version: "beater-otlp-v1".to_string(),
                mime_type: "application/x-protobuf".to_string(),
                redaction_class: RedactionClass::Internal,
                raw_bytes: raw_bytes.clone(),
                raw_idempotency_key: Some(raw_idempotency_key.clone()),
                auth_context: Some(AuthContext {
                    api_key_id: None,
                    scopes: BTreeSet::from(["trace:write".to_string()]),
                }),
                spans: vec![CanonicalSpanDraft {
                    trace_id: TraceId::new("trace").unwrap_or_else(|err| panic!("{err}")),
                    span_id: SpanId::new("span").unwrap_or_else(|err| panic!("{err}")),
                    parent_span_id: None,
                    seq: 1,
                    kind: AgentSpanKind::LlmCall,
                    name: "llm call".to_string(),
                    status: SpanStatus::Ok,
                    start_time: Some(Utc::now()),
                    end_time: Some(Utc::now()),
                    model: None,
                    cost: None,
                    tokens: None,
                    input: Some(json!("hello")),
                    output: Some(json!("world")),
                    attributes: BTreeMap::from([("otel.span.kind".to_string(), json!("CLIENT"))]),
                }],
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        assert_eq!(outcome.ack.accepted_raw, 1);
        assert_eq!(outcome.ack.accepted_spans, 1);
        assert_eq!(bus.depth().await, Ok(1));

        let raw = traces
            .get_raw_envelope(
                scope.tenant_id.clone(),
                scope.project_id.clone(),
                raw_idempotency_key,
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"))
            .unwrap_or_else(|| panic!("raw envelope should be present"));
        assert_eq!(raw.source, SourceDialect::Otlp);
        assert_eq!(raw.source_schema_version.as_deref(), Some("1.37.0"));
        assert_eq!(
            raw.auth_context.scopes,
            BTreeSet::from(["trace:write".to_string()])
        );

        let trace = traces
            .get_trace(
                scope.tenant_id,
                TraceId::new("trace").unwrap_or_else(|err| panic!("{err}")),
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(trace.spans[0].normalizer_version, "beater-otlp-v1");
        assert_eq!(trace.spans[0].raw_ref, raw.body_ref);
        let stored_bytes = artifacts
            .get_bytes(&trace.spans[0].raw_ref)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(stored_bytes, raw_bytes);
    }

    #[tokio::test]
    async fn ingest_governs_attributes_and_payload_refs() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let artifacts = Arc::new(
            FsArtifactStore::new(tempdir.path().join("artifacts"))
                .unwrap_or_else(|err| panic!("{err}")),
        );
        let traces = Arc::new(SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}")));
        let bus = Arc::new(InMemoryBus::new(16));
        let mut denied = BTreeSet::new();
        denied.insert("secret".to_string());
        let service = IngestService::new(
            artifacts,
            traces.clone(),
            bus,
            IngestPolicy {
                inline_payload_bytes: 4,
                denied_attributes: denied,
                ..IngestPolicy::default()
            },
        );
        let mut request = fixture_request();
        request.input = Some(json!({"large": "payload"}));
        request
            .attributes
            .insert("secret".to_string(), json!("drop"));

        service
            .ingest_native(request.clone())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let trace = traces
            .get_trace(request.scope.tenant_id, request.trace_id)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let span = &trace.spans[0];
        assert!(span.input_ref.is_some());
        assert!(!span.attributes.contains_key("secret"));
        assert_eq!(
            span.unmapped_attrs["dropped_attributes"]["secret"],
            json!("drop")
        );
    }

    #[tokio::test]
    async fn project_quota_returns_429_semantics_error() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let artifacts = Arc::new(
            FsArtifactStore::new(tempdir.path().join("artifacts"))
                .unwrap_or_else(|err| panic!("{err}")),
        );
        let traces = Arc::new(SqliteTraceStore::in_memory().unwrap_or_else(|err| panic!("{err}")));
        let bus = Arc::new(InMemoryBus::new(16));
        let service = IngestService::new(
            artifacts,
            traces,
            bus,
            IngestPolicy {
                per_project_event_quota: Some(1),
                ..IngestPolicy::default()
            },
        );

        service
            .ingest_native(fixture_request())
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let error = service
            .ingest_native(fixture_request_with_span("span-2"))
            .await
            .err()
            .unwrap_or_else(|| panic!("quota should fail"));

        assert!(matches!(error, IngestError::QuotaExceeded { limit: 1, .. }));
    }

    #[test]
    fn trace_completion_is_state_machine() {
        assert_eq!(
            trace_completion_state(TraceCompletionInput {
                root_span_ended: true,
                open_child_spans: 0,
                idle_for: Duration::seconds(1),
                idle_timeout: Duration::seconds(5),
                late_window_closed: true,
            }),
            TraceCompletionState::Complete
        );
        assert_eq!(
            trace_completion_state(TraceCompletionInput {
                root_span_ended: false,
                open_child_spans: 0,
                idle_for: Duration::seconds(10),
                idle_timeout: Duration::seconds(5),
                late_window_closed: false,
            }),
            TraceCompletionState::IdleComplete
        );
    }

    fn fixture_request() -> NativeIngestRequest {
        fixture_request_with_span("span")
    }

    fn fixture_request_with_span(span_id: &str) -> NativeIngestRequest {
        let scope = TenantScope::new(
            TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}")),
            ProjectId::new("project").unwrap_or_else(|err| panic!("{err}")),
            EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}")),
        );
        NativeIngestRequest {
            scope,
            trace_id: TraceId::new("trace").unwrap_or_else(|err| panic!("{err}")),
            span_id: SpanId::new(span_id).unwrap_or_else(|err| panic!("{err}")),
            parent_span_id: None,
            seq: 1,
            kind: AgentSpanKind::AgentRun,
            name: "agent run".to_string(),
            status: SpanStatus::Ok,
            start_time: Some(Utc::now()),
            end_time: Some(Utc::now()),
            model: Some(ModelRef {
                provider: "openai".to_string(),
                name: "gpt-test".to_string(),
            }),
            cost: None,
            tokens: Some(TokenCounts {
                input: 10,
                output: 5,
                reasoning: 0,
                cache_read: 0,
            }),
            input: Some(json!({ "question": "hi" })),
            output: Some(json!({ "answer": "hello" })),
            attributes: BTreeMap::from([("safe".to_string(), json!(true))]),
            redaction_class: RedactionClass::Sensitive,
            idempotency_key: None,
            auth_context: None,
        }
    }
}
