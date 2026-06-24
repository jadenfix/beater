//! Offline tests: verify `observe`/`span` emit spans with the correct Beater
//! attributes, using the OTel in-memory exporter so no live beaterd is needed.
//! Analogous to the Python `tests/test_observe.py`.

use std::collections::HashSet;
use std::sync::{Mutex, MutexGuard, OnceLock};

use opentelemetry::global;
use opentelemetry::trace::TraceContextExt;
use opentelemetry::Context;
use opentelemetry_sdk::trace::{InMemorySpanExporter, InMemorySpanExporterBuilder, SdkTracerProvider};

use beater::{attr, span_kind, BeaterConfig, SPAN_KINDS};

/// Serializes tests: they all mutate the process-global tracer provider and the
/// SDK's global config, so they must not run concurrently.
fn test_lock() -> MutexGuard<'static, ()> {
    static LOCK: OnceLock<Mutex<()>> = OnceLock::new();
    LOCK.get_or_init(|| Mutex::new(()))
        .lock()
        .unwrap_or_else(|e| e.into_inner())
}

/// Install a fresh in-memory provider as the global tracer and configure the SDK
/// with a release id (matches the Python fixture). Returns a guard that holds
/// the serialization lock for the test's lifetime, plus the exporter.
fn setup() -> (MutexGuard<'static, ()>, InMemorySpanExporter) {
    let guard = test_lock();

    // beater::init builds an OTLP exporter and sets the global provider, and also
    // populates the one-time config (release_id). It's harmless to call once;
    // CONFIG is a OnceLock so later calls are no-ops, which is fine since every
    // test uses the same release id.
    beater::init(BeaterConfig {
        release_id: Some("rel-1".to_string()),
        ..BeaterConfig::default()
    });

    // Replace the OTLP global provider with an in-memory one so spans are
    // captured locally instead of shipped over the network.
    let exporter = InMemorySpanExporterBuilder::new().build();
    let provider = SdkTracerProvider::builder()
        .with_simple_exporter(exporter.clone())
        .build();
    global::set_tracer_provider(provider);

    (guard, exporter)
}

fn attr_str(span: &opentelemetry_sdk::trace::SpanData, key: &str) -> Option<String> {
    span.attributes
        .iter()
        .find(|kv| kv.key.as_str() == key)
        .map(|kv| kv.value.as_str().to_string())
}

#[test]
fn observe_records_kind_release_and_output() {
    let (_guard, exporter) = setup();

    let result = beater::observe("call", span_kind::LLM_CALL, || {
        beater::set_output("answer");
        "answer"
    });
    assert_eq!(result, "answer");

    let spans = exporter.get_finished_spans().unwrap();
    let span = spans.iter().find(|s| s.name == "call").expect("span emitted");

    assert_eq!(attr_str(span, attr::SPAN_KIND).as_deref(), Some(span_kind::LLM_CALL));
    assert_eq!(attr_str(span, attr::RELEASE_ID).as_deref(), Some("rel-1"));
    assert!(attr_str(span, attr::OUTPUT_VALUE)
        .map(|v| v.contains("answer"))
        .unwrap_or(false));
    // beater.seq is set (>= 1).
    let seq = span
        .attributes
        .iter()
        .find(|kv| kv.key.as_str() == attr::SEQ)
        .map(|kv| kv.value.clone());
    assert!(seq.is_some(), "beater.seq should be set");
}

#[test]
fn span_builder_sets_input_output() {
    let (_guard, exporter) = setup();

    {
        let s = beater::span("retrieve", span_kind::RETRIEVAL_QUERY);
        s.set_input("user question");
        s.set_output("3 docs");
    } // span ends on drop

    let spans = exporter.get_finished_spans().unwrap();
    let span = spans
        .iter()
        .find(|s| s.name == "retrieve")
        .expect("span emitted");
    assert_eq!(
        attr_str(span, attr::SPAN_KIND).as_deref(),
        Some(span_kind::RETRIEVAL_QUERY)
    );
    assert_eq!(attr_str(span, attr::INPUT_VALUE).as_deref(), Some("user question"));
    assert_eq!(attr_str(span, attr::OUTPUT_VALUE).as_deref(), Some("3 docs"));
}

#[test]
fn observe_creates_parent_child_hierarchy() {
    let (_guard, exporter) = setup();

    beater::observe("parent", span_kind::AGENT_RUN, || {
        // The free set_output targets the current (parent) span.
        let parent_cx = Context::current();
        let parent_span_id = parent_cx.span().span_context().span_id();

        beater::observe("child", span_kind::AGENT_PLAN, || {
            let child_parent = Context::current()
                .span()
                .span_context()
                .span_id();
            // Child's own span id differs from the parent's.
            assert_ne!(child_parent, parent_span_id);
        });
    });

    let spans = exporter.get_finished_spans().unwrap();
    let parent = spans.iter().find(|s| s.name == "parent").unwrap();
    let child = spans.iter().find(|s| s.name == "child").unwrap();
    // Same trace, child links to parent.
    assert_eq!(parent.span_context.trace_id(), child.span_context.trace_id());
    assert_eq!(child.parent_span_id, parent.span_context.span_id());
}

#[tokio::test]
async fn observe_async_records_kind() {
    let (_guard, exporter) = setup();

    let n = beater::observe_async("arun", span_kind::AGENT_RUN, async { 21 * 2 }).await;
    assert_eq!(n, 42);

    let spans = exporter.get_finished_spans().unwrap();
    let span = spans.iter().find(|s| s.name == "arun").expect("span emitted");
    assert_eq!(
        attr_str(span, attr::SPAN_KIND).as_deref(),
        Some(span_kind::AGENT_RUN)
    );
}

#[test]
fn semconv_kinds_match_normalizer() {
    // Guard: every kind the SDK can emit is one the server normalizer accepts.
    let expected: HashSet<&str> = [
        "agent.run",
        "agent.turn",
        "agent.plan",
        "agent.step",
        "llm.call",
        "tool.call",
        "mcp.request",
        "retrieval.query",
        "memory.read",
        "memory.write",
        "guardrail.check",
    ]
    .into_iter()
    .collect();

    let actual: HashSet<&str> = SPAN_KINDS.into_iter().collect();
    assert_eq!(actual, expected);
}
