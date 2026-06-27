//! Axum + Beater example (R11.3).
//!
//! A minimal axum HTTP service whose handler emits a Beater agent trace per
//! request using the ergonomic Rust SDK (`beater::observe`). Demonstrates the
//! first-class Rust server adoption path.
//!
//! Cargo.toml:
//!
//! ```toml
//! [dependencies]
//! beater = { path = "../../sdks/rust" }
//! axum = "0.7"
//! tokio = { version = "1", features = ["full"] }
//! serde = { version = "1", features = ["derive"] }
//! ```
//!
//! Run a local beaterd (`docker compose up`) then `cargo run`, and:
//!   curl -X POST localhost:8000/agent -H 'content-type: application/json' \
//!     -d '{"prompt":"refund please"}'

use axum::{routing::post, Json, Router};
use beater::{span_kind, BeaterConfig};
use serde::{Deserialize, Serialize};

#[derive(Deserialize)]
struct AgentRequest {
    prompt: String,
}

#[derive(Serialize)]
struct AgentResponse {
    decision: String,
}

async fn run_agent(Json(req): Json<AgentRequest>) -> Json<AgentResponse> {
    let decision = beater::observe("handle_request", span_kind::AGENT_RUN, || {
        beater::set_input(req.prompt.clone());
        let answer = beater::observe("call_model", span_kind::LLM_CALL, || {
            beater::set_input(req.prompt.clone());
            beater::set_output("ok");
            "escalate"
        });
        beater::set_output(answer);
        answer.to_string()
    });
    Json(AgentResponse { decision })
}

#[tokio::main]
async fn main() {
    beater::init(BeaterConfig {
        service_name: "beater-rust-axum-example".to_string(),
        release_id: Some("axum-example".to_string()),
        ..BeaterConfig::from_env()
    });

    let app = Router::new().route("/agent", post(run_agent));
    let listener = tokio::net::TcpListener::bind("127.0.0.1:8000")
        .await
        .expect("bind");
    println!("beater axum example on :8000");
    axum::serve(listener, app).await.expect("serve");
    beater::shutdown();
}
