//! Tonic (gRPC) + Beater example (R11.3).
//!
//! A tonic gRPC service whose RPC handler emits a Beater agent trace per call
//! using the ergonomic Rust SDK. Demonstrates the first-class Rust gRPC adoption
//! path. The `.proto` and generated stubs are elided for brevity; the load-
//! bearing part is bracketing the RPC body in `beater::observe`.
//!
//! Cargo.toml:
//!
//! ```toml
//! [dependencies]
//! beater = { path = "../../sdks/rust" }
//! tonic = "0.12"
//! tokio = { version = "1", features = ["full"] }
//! ```
//!
//! Run a local beaterd (`docker compose up`) then `cargo run`.

use beater::{span_kind, BeaterConfig};

// In a real service these come from `tonic::include_proto!`. We model the RPC
// body so the Beater instrumentation pattern is clear and self-contained.
struct AgentRequest {
    prompt: String,
}

struct AgentReply {
    decision: String,
}

fn handle_rpc(req: AgentRequest) -> AgentReply {
    let decision = beater::observe("RunAgent", span_kind::AGENT_RUN, || {
        beater::set_input(req.prompt.clone());
        let answer = beater::observe("call_model", span_kind::LLM_CALL, || {
            beater::set_output("ok");
            "escalate"
        });
        beater::set_output(answer);
        answer.to_string()
    });
    AgentReply { decision }
}

#[tokio::main]
async fn main() {
    beater::init(BeaterConfig {
        service_name: "beater-rust-tonic-example".to_string(),
        release_id: Some("tonic-example".to_string()),
        ..BeaterConfig::from_env()
    });

    // Wire `handle_rpc` into your generated tonic service impl, e.g.
    //   async fn run_agent(&self, request: Request<AgentRequest>) -> ...
    //       { Ok(Response::new(handle_rpc(request.into_inner()))) }
    let reply = handle_rpc(AgentRequest {
        prompt: "refund please".to_string(),
    });
    println!("rpc decision: {}", reply.decision);
    beater::shutdown();
}
