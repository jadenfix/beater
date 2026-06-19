use anyhow::{anyhow, Context};
use async_trait::async_trait;
use beater_core::{ProjectId, SpanId, TenantId, TraceId};
use beater_schema::{CanonicalSpan, SpanStatus};
use serde::{Deserialize, Serialize};
use serde_json::Value as JsonValue;
use std::path::Path;
use std::sync::{Arc, Mutex};
use tantivy::collector::TopDocs;
use tantivy::query::{AllQuery, Query, QueryParser};
use tantivy::schema::{Schema, TantivyDocument, Value, STORED, STRING, TEXT};
use tantivy::{doc, Index, IndexWriter, Term};

#[async_trait]
pub trait SearchIndex: Send + Sync {
    async fn index_spans(&self, spans: &[CanonicalSpan]) -> anyhow::Result<()>;
    async fn search(&self, query: SearchRequest) -> anyhow::Result<SearchResponse>;
}

#[derive(Clone, Default)]
pub struct NoopSearchIndex;

#[async_trait]
impl SearchIndex for NoopSearchIndex {
    async fn index_spans(&self, _spans: &[CanonicalSpan]) -> anyhow::Result<()> {
        Ok(())
    }

    async fn search(&self, _query: SearchRequest) -> anyhow::Result<SearchResponse> {
        Ok(SearchResponse { hits: Vec::new() })
    }
}

#[derive(Clone)]
pub struct TantivySearchIndex {
    index: Index,
    fields: SearchFields,
    writer: Arc<Mutex<IndexWriter>>,
}

impl TantivySearchIndex {
    pub fn in_memory() -> anyhow::Result<Self> {
        let (schema, fields) = build_schema();
        let index = Index::create_in_ram(schema);
        Self::from_index(index, fields)
    }

    pub fn open_or_create(path: impl AsRef<Path>) -> anyhow::Result<Self> {
        let path = path.as_ref();
        std::fs::create_dir_all(path)
            .with_context(|| format!("create search index dir {}", path.display()))?;
        let (schema, fields) = build_schema();
        let index = match Index::open_in_dir(path) {
            Ok(index) => index,
            Err(_) => Index::create_in_dir(path, schema)
                .with_context(|| format!("create tantivy search index in {}", path.display()))?,
        };
        Self::from_index(index, fields)
    }

    fn from_index(index: Index, fields: SearchFields) -> anyhow::Result<Self> {
        let writer = index.writer(50_000_000).context("create tantivy writer")?;
        Ok(Self {
            index,
            fields,
            writer: Arc::new(Mutex::new(writer)),
        })
    }
}

#[async_trait]
impl SearchIndex for TantivySearchIndex {
    async fn index_spans(&self, spans: &[CanonicalSpan]) -> anyhow::Result<()> {
        let mut writer = self
            .writer
            .lock()
            .map_err(|err| anyhow!("search writer mutex poisoned: {err}"))?;
        for span in spans {
            let doc_key = doc_key(span);
            writer.delete_term(Term::from_field_text(self.fields.doc_key, &doc_key));
            writer.add_document(doc!(
                self.fields.doc_key => doc_key,
                self.fields.tenant_id => span.tenant_id.as_str(),
                self.fields.project_id => span.project_id.as_str(),
                self.fields.environment_id => span.environment_id.as_str(),
                self.fields.trace_id => span.trace_id.as_str(),
                self.fields.span_id => span.span_id.as_str(),
                self.fields.kind => span.kind.as_str(),
                self.fields.status => status_name(&span.status),
                self.fields.name => span.name.as_str(),
                self.fields.model => model_text(span),
                self.fields.tool => tool_text(span).unwrap_or_default(),
                self.fields.text => searchable_text(span),
            ))?;
        }
        writer.commit().context("commit search index")?;
        Ok(())
    }

    async fn search(&self, query: SearchRequest) -> anyhow::Result<SearchResponse> {
        let reader = self.index.reader().context("open search reader")?;
        let searcher = reader.searcher();
        let parser = QueryParser::for_index(
            &self.index,
            vec![
                self.fields.text,
                self.fields.name,
                self.fields.model,
                self.fields.tool,
            ],
        );
        let parsed: Box<dyn Query> = if query.text.trim().is_empty() {
            Box::new(AllQuery)
        } else {
            parser
                .parse_query(&query.text)
                .with_context(|| format!("parse search query {:?}", query.text))?
        };
        let limit = query.limit.unwrap_or(50).clamp(1, 200);
        let top_docs = searcher
            .search(
                &parsed,
                &TopDocs::with_limit((limit * 5) as usize).order_by_score(),
            )
            .context("search tantivy index")?;

        let mut hits = Vec::new();
        for (score, address) in top_docs {
            let doc = searcher
                .doc::<TantivyDocument>(address)
                .context("load search hit document")?;
            let hit = SearchHit {
                score,
                tenant_id: text_field(&doc, self.fields.tenant_id)?,
                project_id: text_field(&doc, self.fields.project_id)?,
                environment_id: text_field(&doc, self.fields.environment_id)?,
                trace_id: text_field(&doc, self.fields.trace_id)?,
                span_id: text_field(&doc, self.fields.span_id)?,
                kind: text_field(&doc, self.fields.kind)?,
                status: text_field(&doc, self.fields.status)?,
                name: text_field(&doc, self.fields.name)?,
                model: text_field(&doc, self.fields.model)?,
                tool: text_field(&doc, self.fields.tool)?,
            };
            if query.matches(&hit) {
                hits.push(hit);
            }
            if hits.len() >= limit as usize {
                break;
            }
        }
        Ok(SearchResponse { hits })
    }
}

#[derive(Clone, Copy)]
struct SearchFields {
    doc_key: tantivy::schema::Field,
    tenant_id: tantivy::schema::Field,
    project_id: tantivy::schema::Field,
    environment_id: tantivy::schema::Field,
    trace_id: tantivy::schema::Field,
    span_id: tantivy::schema::Field,
    kind: tantivy::schema::Field,
    status: tantivy::schema::Field,
    name: tantivy::schema::Field,
    model: tantivy::schema::Field,
    tool: tantivy::schema::Field,
    text: tantivy::schema::Field,
}

fn build_schema() -> (Schema, SearchFields) {
    let mut builder = Schema::builder();
    let doc_key = builder.add_text_field("doc_key", STRING | STORED);
    let tenant_id = builder.add_text_field("tenant_id", STRING | STORED);
    let project_id = builder.add_text_field("project_id", STRING | STORED);
    let environment_id = builder.add_text_field("environment_id", STRING | STORED);
    let trace_id = builder.add_text_field("trace_id", STRING | STORED);
    let span_id = builder.add_text_field("span_id", STRING | STORED);
    let kind = builder.add_text_field("kind", STRING | STORED);
    let status = builder.add_text_field("status", STRING | STORED);
    let name = builder.add_text_field("name", TEXT | STORED);
    let model = builder.add_text_field("model", TEXT | STORED);
    let tool = builder.add_text_field("tool", TEXT | STORED);
    let text = builder.add_text_field("text", TEXT | STORED);
    (
        builder.build(),
        SearchFields {
            doc_key,
            tenant_id,
            project_id,
            environment_id,
            trace_id,
            span_id,
            kind,
            status,
            name,
            model,
            tool,
            text,
        },
    )
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct SearchRequest {
    pub tenant_id: TenantId,
    pub text: String,
    pub project_id: Option<ProjectId>,
    pub environment_id: Option<String>,
    pub trace_id: Option<TraceId>,
    pub span_id: Option<SpanId>,
    pub kind: Option<String>,
    pub status: Option<String>,
    pub model: Option<String>,
    pub tool: Option<String>,
    pub limit: Option<u32>,
}

impl SearchRequest {
    fn matches(&self, hit: &SearchHit) -> bool {
        if hit.tenant_id != self.tenant_id.as_str() {
            return false;
        }
        if let Some(project_id) = &self.project_id {
            if hit.project_id != project_id.as_str() {
                return false;
            }
        }
        if let Some(environment_id) = &self.environment_id {
            if &hit.environment_id != environment_id {
                return false;
            }
        }
        if let Some(trace_id) = &self.trace_id {
            if hit.trace_id != trace_id.as_str() {
                return false;
            }
        }
        if let Some(span_id) = &self.span_id {
            if hit.span_id != span_id.as_str() {
                return false;
            }
        }
        if let Some(kind) = &self.kind {
            if &hit.kind != kind {
                return false;
            }
        }
        if let Some(status) = &self.status {
            if &hit.status != status {
                return false;
            }
        }
        if let Some(model) = &self.model {
            if !hit.model.contains(model) && !model.is_empty() {
                return false;
            }
        }
        if let Some(tool) = &self.tool {
            if !hit.tool.contains(tool) && !tool.is_empty() {
                return false;
            }
        }
        true
    }
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct SearchResponse {
    pub hits: Vec<SearchHit>,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct SearchHit {
    pub score: f32,
    pub tenant_id: String,
    pub project_id: String,
    pub environment_id: String,
    pub trace_id: String,
    pub span_id: String,
    pub kind: String,
    pub status: String,
    pub name: String,
    pub model: String,
    pub tool: String,
}

fn text_field(doc: &TantivyDocument, field: tantivy::schema::Field) -> anyhow::Result<String> {
    doc.get_first(field)
        .and_then(|value| value.as_str().map(ToString::to_string))
        .ok_or_else(|| anyhow!("search hit missing stored text field {:?}", field))
}

fn doc_key(span: &CanonicalSpan) -> String {
    format!(
        "{}:{}:{}:{}:{}",
        span.tenant_id.as_str(),
        span.project_id.as_str(),
        span.trace_id.as_str(),
        span.span_id.as_str(),
        span.seq
    )
}

fn status_name(status: &SpanStatus) -> &'static str {
    match status {
        SpanStatus::Ok => "ok",
        SpanStatus::Error => "error",
        SpanStatus::Unset => "unset",
    }
}

fn model_text(span: &CanonicalSpan) -> String {
    span.model
        .as_ref()
        .map(|model| format!("{} {}", model.provider, model.name))
        .unwrap_or_default()
}

fn tool_text(span: &CanonicalSpan) -> Option<String> {
    span.attributes
        .get("tool.name")
        .and_then(JsonValue::as_str)
        .map(ToString::to_string)
}

fn searchable_text(span: &CanonicalSpan) -> String {
    let mut pieces = vec![
        span.name.clone(),
        span.kind.as_str().to_string(),
        status_name(&span.status).to_string(),
        model_text(span),
        tool_text(span).unwrap_or_default(),
    ];
    for (key, value) in &span.attributes {
        pieces.push(key.clone());
        pieces.push(value_to_text(value));
    }
    pieces.push(value_to_text(&span.unmapped_attrs));
    pieces.join(" ")
}

fn value_to_text(value: &JsonValue) -> String {
    match value {
        JsonValue::Null => String::new(),
        JsonValue::Bool(value) => value.to_string(),
        JsonValue::Number(value) => value.to_string(),
        JsonValue::String(value) => value.clone(),
        JsonValue::Array(values) => values
            .iter()
            .map(value_to_text)
            .collect::<Vec<_>>()
            .join(" "),
        JsonValue::Object(values) => values
            .iter()
            .flat_map(|(key, value)| [key.clone(), value_to_text(value)])
            .collect::<Vec<_>>()
            .join(" "),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_core::{EnvironmentId, ProjectId, TenantId};
    use beater_schema::{AgentSpanKind, ModelRef, CANONICAL_SCHEMA_VERSION};
    use chrono::Utc;
    use serde_json::json;
    use std::collections::BTreeMap;

    #[tokio::test]
    async fn tantivy_search_indexes_text_and_enforces_tenant_filters() {
        let index = TantivySearchIndex::in_memory().unwrap_or_else(|err| panic!("{err}"));
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let other_tenant = TenantId::new("other").unwrap_or_else(|err| panic!("{err}"));
        index
            .index_spans(&[
                fixture_span(
                    &tenant,
                    "trace-a",
                    "span-a",
                    "refund tool failed",
                    SpanStatus::Error,
                ),
                fixture_span(
                    &other_tenant,
                    "trace-b",
                    "span-b",
                    "refund tool failed",
                    SpanStatus::Error,
                ),
            ])
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        let response = index
            .search(SearchRequest {
                tenant_id: tenant.clone(),
                text: "refund".to_string(),
                status: Some("error".to_string()),
                kind: Some("tool.call".to_string()),
                limit: Some(10),
                ..SearchRequest::default_for_tenant(tenant)
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        assert_eq!(response.hits.len(), 1);
        assert_eq!(response.hits[0].trace_id, "trace-a");
    }

    #[tokio::test]
    async fn reindex_replaces_existing_span_document() {
        let index = TantivySearchIndex::in_memory().unwrap_or_else(|err| panic!("{err}"));
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let mut span = fixture_span(&tenant, "trace", "span", "first message", SpanStatus::Ok);
        index
            .index_spans(&[span.clone()])
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        span.name = "second message".to_string();
        index
            .index_spans(&[span])
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        let old = index
            .search(SearchRequest {
                tenant_id: tenant.clone(),
                text: "first".to_string(),
                limit: Some(10),
                ..SearchRequest::default_for_tenant(tenant.clone())
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        let new = index
            .search(SearchRequest {
                tenant_id: tenant.clone(),
                text: "second".to_string(),
                limit: Some(10),
                ..SearchRequest::default_for_tenant(tenant)
            })
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        assert!(old.hits.is_empty());
        assert_eq!(new.hits.len(), 1);
    }

    impl SearchRequest {
        fn default_for_tenant(tenant_id: TenantId) -> Self {
            Self {
                tenant_id,
                text: String::new(),
                project_id: None,
                environment_id: None,
                trace_id: None,
                span_id: None,
                kind: None,
                status: None,
                model: None,
                tool: None,
                limit: None,
            }
        }
    }

    fn fixture_span(
        tenant_id: &TenantId,
        trace_id: &str,
        span_id: &str,
        name: &str,
        status: SpanStatus,
    ) -> CanonicalSpan {
        CanonicalSpan {
            schema_version: CANONICAL_SCHEMA_VERSION,
            normalizer_version: "test".to_string(),
            tenant_id: tenant_id.clone(),
            project_id: ProjectId::new("project").unwrap_or_else(|err| panic!("{err}")),
            environment_id: EnvironmentId::new("prod").unwrap_or_else(|err| panic!("{err}")),
            trace_id: TraceId::new(trace_id).unwrap_or_else(|err| panic!("{err}")),
            span_id: SpanId::new(span_id).unwrap_or_else(|err| panic!("{err}")),
            parent_span_id: None,
            seq: 1,
            kind: AgentSpanKind::ToolCall,
            name: name.to_string(),
            status,
            start_time: Utc::now(),
            end_time: None,
            model: Some(ModelRef {
                provider: "openai".to_string(),
                name: "gpt-test".to_string(),
            }),
            cost: None,
            tokens: None,
            input_ref: None,
            output_ref: None,
            attributes: BTreeMap::from([
                ("tool.name".to_string(), json!("refund_lookup")),
                ("input.value".to_string(), json!("customer asks for refund")),
                ("output.value".to_string(), json!("refund denied")),
            ]),
            unmapped_attrs: json!({ "error": "timeout talking to billing" }),
            raw_ref: beater_schema::ArtifactRef {
                artifact_id: beater_core::ArtifactId::new("artifact")
                    .unwrap_or_else(|err| panic!("{err}")),
                uri: "artifact://tenant/project/artifact".to_string(),
                sha256: beater_core::Sha256Hash::new("hash").unwrap_or_else(|err| panic!("{err}")),
                size_bytes: 0,
                mime_type: "application/json".to_string(),
                redaction_class: beater_schema::RedactionClass::Internal,
            },
        }
    }
}
