//! MCP + Beater example (R11.3).
//!
//! Instruments an agent's MCP tool calls with Beater. Each MCP request the agent
//! makes is wrapped in an `mcp.request` span, so the tool name, arguments
//! (input), and result (output) show up in the trace waterfall alongside the
//! agent's reasoning. Beater itself also exposes its API as MCP tools at `/mcp`,
//! so this same shape is what you get when an agent drives Beater over MCP.
//!
//! Cargo.toml:
//!
//! ```toml
//! [dependencies]
//! beater = { path = "../../sdks/rust" }
//! tokio = { version = "1", features = ["full"] }
//! serde_json = "1"
//! ```
//!
//! Run a local beaterd (`docker compose up`) then `cargo run`.

use beater::{span_kind, BeaterConfig};
use serde_json::json;

// Stand-in for your MCP client's `call_tool(name, args) -> result`.
async fn call_mcp_tool(name: &str, args: serde_json::Value) -> serde_json::Value {
    // Wrap the MCP request in an mcp.request span and record args/result.
    beater::observe_async("mcp.request", span_kind::MCP_REQUEST, async move {
        beater::set_input(json!({ "tool": name, "arguments": args }).to_string());
        // Replace with a real MCP transport call (stdio / HTTP) to a tool server.
        let result = json!({ "ok": true, "tool": name });
        beater::set_output(result.to_string());
        result
    })
    .await
}

#[tokio::main]
async fn main() {
    beater::init(BeaterConfig {
        service_name: "beater-rust-mcp-example".to_string(),
        release_id: Some("mcp-example".to_string()),
        ..BeaterConfig::from_env()
    });

    let answer = beater::observe_async("handle_request", span_kind::AGENT_RUN, async {
        beater::set_input("look up the refund policy via MCP");
        let lookup = call_mcp_tool("search_traces", json!({ "kind": "llm.call" })).await;
        beater::set_output(lookup.to_string());
        lookup
    })
    .await;

    println!("mcp result: {answer}");
    beater::shutdown();
}
