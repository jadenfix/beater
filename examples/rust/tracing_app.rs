//! Rust `tracing` -> Beater example (R11.3).
//!
//! Bridges the idiomatic Rust `tracing` crate to Beater. The Beater Rust SDK
//! (`sdks/rust`, crate `beater`) is OpenTelemetry-native, so you can use either:
//!
//! 1. the SDK's ergonomic `beater::observe(...)` helper directly (shown here), or
//! 2. `tracing` + `tracing-opentelemetry` with an OTLP exporter pointed at
//!    beaterd, in which case `tracing` spans become Beater spans automatically.
//!
//! Cargo.toml:
//!
//! ```toml
//! [dependencies]
//! beater = { path = "../../sdks/rust" }
//! tracing = "0.1"
//! ```
//!
//! Run a local beaterd (`docker compose up`) then `cargo run`.

use beater::{span_kind, BeaterConfig};

fn main() {
    beater::init(BeaterConfig {
        service_name: "beater-rust-tracing-example".to_string(),
        release_id: Some("tracing-example".to_string()),
        ..BeaterConfig::from_env()
    });

    // `observe` opens a Beater span with the right kind/sequence/release attrs.
    let decision = beater::observe("handle_refund", span_kind::AGENT_RUN, || {
        beater::set_input("late delivery refund after 31 days");
        let answer = beater::observe("call_model", span_kind::LLM_CALL, || {
            beater::set_output("Escalate: outside the refund window.");
            "escalate"
        });
        beater::set_output(answer);
        answer
    });

    println!("agent result: {decision}");
    beater::shutdown();
}
