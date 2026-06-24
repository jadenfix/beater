//! Five-line Beater quickstart: instrument an agent and emit a trace.
//!
//! Run a local beaterd (e.g. `docker compose up`), then:
//!
//! ```sh
//! BEATER_TENANT_ID=demo BEATER_PROJECT_ID=demo BEATER_ENVIRONMENT_ID=local \
//!     cargo run --example quickstart
//! ```
//!
//! It emits an agent.run -> agent.plan -> llm.call trace. Open the dashboard and
//! click the trace.

use beater::{span_kind, BeaterConfig};

fn main() {
    beater::init(BeaterConfig {
        service_name: "beater-rust-quickstart".to_string(),
        release_id: Some("quickstart".to_string()),
        ..BeaterConfig::from_env()
    });

    let result = beater::observe("handle_refund", span_kind::AGENT_RUN, || {
        beater::set_input("late delivery refund after 31 days");

        let plan = beater::observe("make_plan", span_kind::AGENT_PLAN, || {
            "look up refund policy".to_string()
        });

        let decision = beater::observe("call_model", span_kind::LLM_CALL, || {
            beater::set_input(plan.clone());
            beater::set_output("Escalate: order is outside the standard refund window.");
            "escalate"
        });

        beater::set_output(decision);
        decision
    });

    println!("agent result: {result}");
    beater::shutdown();
    println!("trace flushed -- open the dashboard to inspect it");
}
