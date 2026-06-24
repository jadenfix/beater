//! # Beater Rust SDK — ergonomic, OpenTelemetry-native agent observability
//!
//! This is the hand-written ergonomic (Layer 2) SDK, mirroring the Python
//! (`sdks/python`) and TypeScript (`sdks/typescript`) SDKs. It is a thin,
//! idiomatic wrapper over the OpenTelemetry API: `init()` wires up an OTLP/HTTP
//! exporter pointed at `beaterd`, and `observe` / `span` open Beater spans with
//! the right span-kind, sequence, and release attributes.
//!
//! ```no_run
//! use beater::{BeaterConfig, span_kind};
//!
//! beater::init(BeaterConfig::from_env());
//!
//! let answer = beater::observe("handle_refund", span_kind::AGENT_RUN, || {
//!     beater::set_input("late delivery refund");
//!     beater::set_output("escalate");
//!     "escalate"
//! });
//! assert_eq!(answer, "escalate");
//! beater::shutdown();
//! ```

mod config;
pub mod semconv;

pub use config::BeaterConfig;
// Re-export the semconv namespaces at the crate root for ergonomics, matching
// `beater.SpanKind` / `beater::span_kind` usage in the sibling SDKs.
pub use semconv::{attr, span_kind, SPAN_KINDS};

use std::sync::atomic::{AtomicU64, Ordering};
use std::sync::{Mutex, OnceLock};

use opentelemetry::trace::{SpanBuilder, Status, TraceContextExt, Tracer};
use opentelemetry::{global, Context, KeyValue, Value};
use opentelemetry_otlp::{WithExportConfig, WithHttpConfig};
use opentelemetry_sdk::trace::SdkTracerProvider;
use opentelemetry_sdk::Resource;

const TRACER_NAME: &str = "beater.sdk";

static CONFIG: OnceLock<BeaterConfig> = OnceLock::new();
static PROVIDER: Mutex<Option<SdkTracerProvider>> = Mutex::new(None);
static SEQ: AtomicU64 = AtomicU64::new(1);

/// Initialize the Beater tracer. Call once at process start.
///
/// Builds an OTLP/HTTP (protobuf) exporter pointed at
/// `{base_url}/v1/otlp/{tenant}/{project}/{environment}/v1/traces` and installs
/// it as the global OpenTelemetry tracer provider.
pub fn init(config: BeaterConfig) {
    let exporter = build_exporter(&config);

    let provider = SdkTracerProvider::builder()
        .with_batch_exporter(exporter)
        .with_resource(
            Resource::builder()
                .with_service_name(config.service_name.clone())
                .build(),
        )
        .build();

    global::set_tracer_provider(provider.clone());

    *PROVIDER.lock().unwrap() = Some(provider);
    let _ = CONFIG.set(config);
}

fn build_exporter(config: &BeaterConfig) -> opentelemetry_otlp::SpanExporter {
    let mut headers = std::collections::HashMap::new();
    if let Some(api_key) = &config.api_key {
        headers.insert("authorization".to_string(), format!("Bearer {api_key}"));
    }

    opentelemetry_otlp::SpanExporter::builder()
        .with_http()
        .with_endpoint(config.otlp_http_traces_url())
        .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
        .with_headers(headers)
        .build()
        .expect("failed to build Beater OTLP/HTTP span exporter")
}

/// The active config, if `init` has been called.
pub fn get_config() -> Option<&'static BeaterConfig> {
    CONFIG.get()
}

fn tracer() -> global::BoxedTracer {
    // Reads the global provider, so it works whether `init` ran here or the test
    // harness installed its own provider.
    global::tracer(TRACER_NAME)
}

fn common_attributes(kind: &str) -> Vec<KeyValue> {
    let mut attrs = vec![
        KeyValue::new(attr::SPAN_KIND, kind.to_string()),
        KeyValue::new(attr::SEQ, SEQ.fetch_add(1, Ordering::Relaxed) as i64),
    ];
    if let Some(release_id) = CONFIG.get().and_then(|c| c.release_id.clone()) {
        attrs.push(KeyValue::new(attr::RELEASE_ID, release_id));
    }
    attrs
}

/// An ergonomic Beater span: a thin RAII handle that activates an OpenTelemetry
/// span as the current context for its lifetime.
///
/// Use [`span`] to open one, then [`Span::set_input`] / [`Span::set_output`] (or
/// the free [`set_input`] / [`set_output`] functions that target the current
/// span). Dropping the guard ends the span and restores the previous context.
pub struct Span {
    // The owned context holding our span; we mutate the span through it.
    cx: Context,
    // Restores the previous current-context when dropped. Declared last so it
    // drops first, detaching this span before we end it.
    _context_guard: opentelemetry::ContextGuard,
}

impl Span {
    /// Attach an input payload to this span (`input.value`).
    pub fn set_input(&self, value: impl Into<Value>) {
        self.cx
            .span()
            .set_attribute(KeyValue::new(attr::INPUT_VALUE, value.into()));
    }

    /// Attach an output payload to this span (`output.value`).
    pub fn set_output(&self, value: impl Into<Value>) {
        self.cx
            .span()
            .set_attribute(KeyValue::new(attr::OUTPUT_VALUE, value.into()));
    }

    /// Set an arbitrary attribute on this span.
    pub fn set_attribute(&self, key: &'static str, value: impl Into<Value>) {
        self.cx.span().set_attribute(KeyValue::new(key, value.into()));
    }

    /// Mark the span OK. (Spans are otherwise unset/OK by default.)
    pub fn ok(&self) {
        self.cx.span().set_status(Status::Ok);
    }

    /// Mark the span as errored with a message.
    pub fn error(&self, message: impl Into<std::borrow::Cow<'static, str>>) {
        self.cx.span().set_status(Status::error(message));
    }
}

impl Drop for Span {
    fn drop(&mut self) {
        self.cx.span().end();
    }
}

/// Open a Beater span as the current span and return an RAII guard.
///
/// The span carries the given `kind` (one of [`span_kind`]), a monotonically
/// increasing `beater.seq`, and the configured `agent.release_id`. The span ends
/// when the returned [`Span`] is dropped.
///
/// ```no_run
/// use beater::span_kind;
/// let s = beater::span("retrieve", span_kind::RETRIEVAL_QUERY);
/// s.set_input("user question");
/// s.set_output("3 docs");
/// ```
pub fn span(name: &str, kind: &str) -> Span {
    let builder = SpanBuilder::from_name(name.to_string()).with_attributes(common_attributes(kind));
    let otel_span = tracer().build(builder);

    // Make this span the current context so nested spans become children and
    // the free `set_input`/`set_output` functions can find it.
    let cx = Context::current().with_span(otel_span);
    let _context_guard = cx.clone().attach();
    Span { cx, _context_guard }
}

/// Run `f` inside a Beater span, recording status. Returns `f`'s result.
///
/// This is the primary ergonomic entry point, analogous to Python's `@observe`.
///
/// ```no_run
/// use beater::span_kind;
/// let n = beater::observe("plan", span_kind::AGENT_PLAN, || 42);
/// assert_eq!(n, 42);
/// ```
pub fn observe<T>(name: &str, kind: &str, f: impl FnOnce() -> T) -> T {
    let otel_span = tracer().build(
        SpanBuilder::from_name(name.to_string()).with_attributes(common_attributes(kind)),
    );
    let cx = Context::current().with_span(otel_span);
    let _guard = cx.clone().attach();

    let result = f();

    // Mark OK and end. `cx` still owns the span; end it via the context's span.
    cx.span().set_status(Status::Ok);
    cx.span().end();
    result
}

/// Async variant of [`observe`]: run the future inside a Beater span.
pub async fn observe_async<T, Fut>(name: &str, kind: &str, fut: Fut) -> T
where
    Fut: std::future::Future<Output = T>,
{
    let otel_span = tracer().build(
        SpanBuilder::from_name(name.to_string()).with_attributes(common_attributes(kind)),
    );
    let cx = Context::current().with_span(otel_span);
    let _guard = cx.clone().attach();

    let result = fut.await;

    cx.span().set_status(Status::Ok);
    cx.span().end();
    result
}

/// Attach an input payload (`input.value`) to the current span.
pub fn set_input(value: impl Into<Value>) {
    let cx = Context::current();
    cx.span()
        .set_attribute(KeyValue::new(attr::INPUT_VALUE, value.into()));
}

/// Attach an output payload (`output.value`) to the current span.
pub fn set_output(value: impl Into<Value>) {
    let cx = Context::current();
    cx.span()
        .set_attribute(KeyValue::new(attr::OUTPUT_VALUE, value.into()));
}

/// Set an arbitrary attribute on the current span.
pub fn set_attribute(key: &'static str, value: impl Into<Value>) {
    let cx = Context::current();
    cx.span().set_attribute(KeyValue::new(key, value.into()));
}

/// Force-flush pending spans. Useful before a short-lived program exits.
pub fn flush() {
    if let Some(provider) = PROVIDER.lock().unwrap().as_ref() {
        let _ = provider.force_flush();
    }
}

/// Flush and shut down the tracer provider.
pub fn shutdown() {
    if let Some(provider) = PROVIDER.lock().unwrap().take() {
        let _ = provider.shutdown();
    }
}
