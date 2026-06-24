use beater_core::Money;
use beater_schema::EvaluatorLane;
use regex::Regex;
use serde::{Deserialize, Serialize};
use serde_json::Value;

#[derive(Debug, thiserror::Error)]
pub enum EvalError {
    #[error("evaluator {0} requires judge broker lane")]
    RequiresJudgeBroker(String),
    #[error("evaluator {0} requires deterministic lane")]
    RequiresDeterministicLane(String),
    #[error(
        "evaluator {evaluator_id} kind {catalog_id} requires {expected:?} lane, got {actual:?}"
    )]
    EvaluatorLaneMismatch {
        evaluator_id: String,
        catalog_id: String,
        expected: EvaluatorLane,
        actual: EvaluatorLane,
    },
    #[error("invalid regex: {0}")]
    InvalidRegex(String),
    #[error(
        "underpowered comparison: sample_size={sample_size}, min_sample_size={min_sample_size}"
    )]
    Underpowered {
        sample_size: usize,
        min_sample_size: usize,
    },
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct EvaluationCase {
    #[schema(value_type = serde_json::Value)]
    pub input: Value,
    #[schema(value_type = serde_json::Value)]
    pub output: Value,
    #[schema(value_type = Option<serde_json::Value>)]
    pub reference: Option<Value>,
    #[schema(value_type = Option<serde_json::Value>)]
    pub trace: Option<Value>,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct ScoreResult {
    pub score: f64,
    pub label: Option<String>,
    #[schema(value_type = serde_json::Value)]
    pub evidence: Value,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct EvaluatorSpec {
    pub id: String,
    pub lane: EvaluatorLane,
    pub kind: EvaluatorKind,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
#[serde(tag = "type", rename_all = "snake_case")]
pub enum EvaluatorKind {
    ExactMatch,
    RegexMatch {
        pattern: String,
    },
    JsonObject,
    CostBudget {
        max_micros: i64,
    },
    LatencyBudgetMs {
        max_ms: u64,
    },
    LlmJudge {
        rubric: String,
        model: String,
    },
    /// Browser world-state success: asserts the final step's observed page
    /// (url and/or DOM) matches the configured target — NOT the agent's
    /// self-reported "done". Reads `trace.browser_steps`.
    BrowserTaskSuccess {
        url_contains: Option<String>,
        dom_contains: Option<String>,
    },
    /// Browser step efficiency: passes when the run used at most `max_steps`
    /// browser steps (catches looping/backtracking). Reads `trace.browser_steps`.
    BrowserStepEfficiency {
        max_steps: u64,
    },
    /// Browser grounding: fraction of element-targeted steps that resolved to
    /// their intended element; score is the ratio, passes at `min_ratio`.
    BrowserGrounding {
        min_ratio: f64,
    },
    /// Browser recovery: passes when the run either hit no errors or recovered
    /// to a successful final step (catches death spirals after a failed action).
    BrowserRecovery,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize)]
pub struct EvaluatorCatalogEntry {
    pub id: &'static str,
    pub lane: EvaluatorLane,
    pub display_name: &'static str,
    pub description: &'static str,
    pub requires_reference: bool,
    pub consumes_trace: bool,
    pub wasm_safe: bool,
}

pub const EVALUATOR_CATALOG: &[EvaluatorCatalogEntry] = &[
    EvaluatorCatalogEntry {
        id: "exact_match",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Exact match",
        description: "Scores output equality against a reference value.",
        requires_reference: true,
        consumes_trace: false,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "regex_match",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Regex match",
        description: "Scores a string output against a configured regular expression.",
        requires_reference: false,
        consumes_trace: false,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "json_object",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "JSON object",
        description: "Scores whether the output is a JSON object.",
        requires_reference: false,
        consumes_trace: false,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "cost_budget",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Cost budget",
        description: "Scores whether trace cost stays within a configured micro-unit budget.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "latency_budget_ms",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Latency budget",
        description: "Scores whether trace latency stays within a configured millisecond budget.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "llm_judge",
        lane: EvaluatorLane::JudgeBroker,
        display_name: "LLM judge",
        description: "Routes model-dependent scoring through the judge broker.",
        requires_reference: false,
        consumes_trace: false,
        wasm_safe: false,
    },
    EvaluatorCatalogEntry {
        id: "browser_task_success",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Browser task success",
        description: "Scores whether the final browser observation matches a world-state target.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "browser_step_efficiency",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Browser step efficiency",
        description: "Scores whether the browser run stayed within a step budget.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "browser_grounding",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Browser grounding",
        description: "Scores the fraction of element-targeted steps that resolved their element.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
    EvaluatorCatalogEntry {
        id: "browser_recovery",
        lane: EvaluatorLane::DeterministicWasi,
        display_name: "Browser recovery",
        description: "Scores whether the browser run avoided or recovered from action failures.",
        requires_reference: false,
        consumes_trace: true,
        wasm_safe: true,
    },
];

pub fn evaluator_catalog() -> &'static [EvaluatorCatalogEntry] {
    EVALUATOR_CATALOG
}

pub fn evaluator_catalog_entry(id: &str) -> Option<&'static EvaluatorCatalogEntry> {
    EVALUATOR_CATALOG.iter().find(|entry| entry.id == id)
}

impl EvaluatorKind {
    pub fn catalog_id(&self) -> &'static str {
        match self {
            Self::ExactMatch => "exact_match",
            Self::RegexMatch { .. } => "regex_match",
            Self::JsonObject => "json_object",
            Self::CostBudget { .. } => "cost_budget",
            Self::LatencyBudgetMs { .. } => "latency_budget_ms",
            Self::LlmJudge { .. } => "llm_judge",
            Self::BrowserTaskSuccess { .. } => "browser_task_success",
            Self::BrowserStepEfficiency { .. } => "browser_step_efficiency",
            Self::BrowserGrounding { .. } => "browser_grounding",
            Self::BrowserRecovery => "browser_recovery",
        }
    }

    pub fn catalog_entry(&self) -> &'static EvaluatorCatalogEntry {
        let id = self.catalog_id();
        evaluator_catalog_entry(id).unwrap_or_else(|| unreachable!("missing catalog entry: {id}"))
    }

    pub fn expected_lane(&self) -> EvaluatorLane {
        self.catalog_entry().lane
    }
}

impl EvaluatorSpec {
    pub fn validate_catalog_lane(&self) -> Result<(), EvalError> {
        let entry = self.kind.catalog_entry();
        if self.lane == entry.lane {
            return Ok(());
        }

        Err(EvalError::EvaluatorLaneMismatch {
            evaluator_id: self.id.clone(),
            catalog_id: entry.id.to_string(),
            expected: entry.lane,
            actual: self.lane,
        })
    }
}

pub fn evaluate_deterministic(
    spec: &EvaluatorSpec,
    case: &EvaluationCase,
) -> Result<ScoreResult, EvalError> {
    spec.validate_catalog_lane()?;
    if spec.lane != EvaluatorLane::DeterministicWasi {
        return Err(EvalError::RequiresDeterministicLane(spec.id.clone()));
    }

    match &spec.kind {
        EvaluatorKind::ExactMatch => {
            let pass = case.reference.as_ref() == Some(&case.output);
            Ok(binary_score(pass, "exact_match"))
        }
        EvaluatorKind::RegexMatch { pattern } => {
            let output = case.output.as_str().unwrap_or_default();
            let regex =
                Regex::new(pattern).map_err(|err| EvalError::InvalidRegex(err.to_string()))?;
            Ok(binary_score(regex.is_match(output), "regex_match"))
        }
        EvaluatorKind::JsonObject => Ok(binary_score(case.output.is_object(), "json_object")),
        EvaluatorKind::CostBudget { max_micros } => {
            let cost = case
                .trace
                .as_ref()
                .and_then(|trace| trace.get("cost_micros"))
                .and_then(Value::as_i64)
                .unwrap_or(0);
            Ok(binary_score(cost <= *max_micros, "cost_budget"))
        }
        EvaluatorKind::LatencyBudgetMs { max_ms } => {
            let latency = case
                .trace
                .as_ref()
                .and_then(|trace| trace.get("latency_ms"))
                .and_then(Value::as_u64)
                .unwrap_or(0);
            Ok(binary_score(latency <= *max_ms, "latency_budget"))
        }
        EvaluatorKind::LlmJudge { .. } => Err(EvalError::RequiresJudgeBroker(spec.id.clone())),
        EvaluatorKind::BrowserTaskSuccess {
            url_contains,
            dom_contains,
        } => {
            let steps = browser_steps(case);
            let observation = steps
                .last()
                .and_then(|step| step.get("outcome"))
                .and_then(|outcome| outcome.get("observation"));
            let url = observation
                .and_then(|obs| obs.get("url"))
                .and_then(Value::as_str)
                .unwrap_or_default();
            let dom = observation
                .and_then(|obs| obs.get("dom_html"))
                .and_then(Value::as_str)
                .unwrap_or_default();
            let url_ok = url_contains
                .as_ref()
                .map(|needle| url.contains(needle.as_str()))
                .unwrap_or(true);
            let dom_ok = dom_contains
                .as_ref()
                .map(|needle| dom.contains(needle.as_str()))
                .unwrap_or(true);
            let pass = !steps.is_empty() && url_ok && dom_ok;
            Ok(binary_score(pass, "browser_task_success"))
        }
        EvaluatorKind::BrowserStepEfficiency { max_steps } => {
            let count = browser_steps(case).len() as u64;
            Ok(binary_score(
                count > 0 && count <= *max_steps,
                "browser_step_efficiency",
            ))
        }
        EvaluatorKind::BrowserGrounding { min_ratio } => {
            let steps = browser_steps(case);
            let mut targeted = 0u64;
            let mut grounded = 0u64;
            for step in &steps {
                let grounding = step
                    .get("outcome")
                    .and_then(|outcome| outcome.get("grounding"));
                let has_selector = grounding
                    .and_then(|grounding| grounding.get("selector"))
                    .map(|selector| !selector.is_null())
                    .unwrap_or(false);
                if has_selector {
                    targeted += 1;
                    let matched = grounding
                        .and_then(|grounding| grounding.get("matched_element"))
                        .and_then(Value::as_bool)
                        .unwrap_or(false);
                    if matched {
                        grounded += 1;
                    }
                }
            }
            let ratio = if targeted == 0 {
                1.0
            } else {
                grounded as f64 / targeted as f64
            };
            let pass = ratio >= *min_ratio;
            Ok(ScoreResult {
                score: ratio,
                label: Some(if pass { "pass" } else { "fail" }.to_string()),
                evidence: serde_json::json!({
                    "metric": "browser_grounding",
                    "targeted": targeted,
                    "grounded": grounded,
                    "ratio": ratio,
                    "min_ratio": min_ratio,
                    "pass": pass,
                }),
            })
        }
        EvaluatorKind::BrowserRecovery => {
            let steps = browser_steps(case);
            let status_of = |step: &Value| -> String {
                step.get("outcome")
                    .and_then(|outcome| outcome.get("status"))
                    .and_then(Value::as_str)
                    .unwrap_or("ok")
                    .to_string()
            };
            let any_error = steps.iter().any(|step| status_of(step) == "error");
            let final_ok = steps
                .last()
                .map(|step| status_of(step) == "ok")
                .unwrap_or(false);
            let pass = !steps.is_empty() && (!any_error || final_ok);
            Ok(binary_score(pass, "browser_recovery"))
        }
    }
}

/// Extract the `browser_steps` array (serialized `StepTriple`s) from a case
/// trace. Returns an empty vec when absent — every browser evaluator degrades to
/// a deterministic "fail/neutral" rather than erroring on a non-browser trace.
fn browser_steps(case: &EvaluationCase) -> Vec<Value> {
    case.trace
        .as_ref()
        .and_then(|trace| trace.get("browser_steps"))
        .and_then(Value::as_array)
        .cloned()
        .unwrap_or_default()
}

fn binary_score(pass: bool, metric: &str) -> ScoreResult {
    ScoreResult {
        score: if pass { 1.0 } else { 0.0 },
        label: Some(if pass { "pass" } else { "fail" }.to_string()),
        evidence: serde_json::json!({ "metric": metric, "pass": pass }),
    }
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct JudgeRequest {
    pub rubric: String,
    pub model: String,
    #[schema(value_type = serde_json::Value)]
    pub input: Value,
    #[schema(value_type = serde_json::Value)]
    pub output: Value,
    #[schema(value_type = Option<serde_json::Value>)]
    pub reference: Option<Value>,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct JudgeResponse {
    pub score: f64,
    pub rationale: String,
    pub cost: Money,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct ExperimentComparison {
    pub sample_size: usize,
    pub baseline_mean: f64,
    pub candidate_mean: f64,
    pub delta: f64,
    pub ci_low: f64,
    pub ci_high: f64,
    pub decision: GateDecision,
    pub test: StatisticalTest,
    pub adjusted_alpha: f64,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize, utoipa::ToSchema)]
#[serde(rename_all = "snake_case")]
pub enum GateDecision {
    Pass,
    FailRegression,
    Inconclusive,
}

impl GateDecision {
    /// Stable snake_case name used in persisted reports.
    pub fn name(&self) -> &'static str {
        match self {
            GateDecision::Pass => "pass",
            GateDecision::FailRegression => "fail_regression",
            GateDecision::Inconclusive => "inconclusive",
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize, utoipa::ToSchema)]
#[serde(rename_all = "snake_case")]
pub enum StatisticalTest {
    PairedNormalApproximation,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize, utoipa::ToSchema)]
pub struct GatePolicy {
    pub min_sample_size: usize,
    pub max_regression: f64,
    pub alpha: f64,
    pub comparison_count: usize,
}

impl Default for GatePolicy {
    fn default() -> Self {
        Self {
            min_sample_size: 10,
            max_regression: 0.0,
            alpha: 0.05,
            comparison_count: 1,
        }
    }
}

pub fn compare_paired_scores(
    baseline: &[f64],
    candidate: &[f64],
    policy: &GatePolicy,
) -> Result<ExperimentComparison, EvalError> {
    let n = baseline.len().min(candidate.len());
    if n < policy.min_sample_size {
        return Err(EvalError::Underpowered {
            sample_size: n,
            min_sample_size: policy.min_sample_size,
        });
    }

    let mut differences = Vec::with_capacity(n);
    for index in 0..n {
        differences.push(candidate[index] - baseline[index]);
    }
    let delta = mean(&differences);
    let baseline_mean = mean(&baseline[..n]);
    let candidate_mean = mean(&candidate[..n]);
    let variance = sample_variance(&differences);
    let standard_error = (variance / n as f64).sqrt();
    let adjusted_alpha = (policy.alpha / policy.comparison_count.max(1) as f64).clamp(0.0001, 0.5);
    let z = if adjusted_alpha <= 0.01 { 2.576 } else { 1.96 };
    let ci_low = delta - z * standard_error;
    let ci_high = delta + z * standard_error;
    let decision = if ci_high < -policy.max_regression {
        GateDecision::FailRegression
    } else if ci_low >= -policy.max_regression {
        GateDecision::Pass
    } else {
        GateDecision::Inconclusive
    };

    Ok(ExperimentComparison {
        sample_size: n,
        baseline_mean,
        candidate_mean,
        delta,
        ci_low,
        ci_high,
        decision,
        test: StatisticalTest::PairedNormalApproximation,
        adjusted_alpha,
    })
}

fn mean(values: &[f64]) -> f64 {
    values.iter().sum::<f64>() / values.len() as f64
}

fn sample_variance(values: &[f64]) -> f64 {
    if values.len() < 2 {
        return 0.0;
    }
    let value_mean = mean(values);
    values
        .iter()
        .map(|value| {
            let diff = value - value_mean;
            diff * diff
        })
        .sum::<f64>()
        / (values.len() - 1) as f64
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn evaluator_catalog_classifies_execution_lanes() {
        let catalog = evaluator_catalog();
        assert_eq!(catalog.len(), 10);

        let exact = evaluator_catalog_entry("exact_match")
            .unwrap_or_else(|| panic!("exact_match catalog entry should exist"));
        assert_eq!(exact.lane, EvaluatorLane::DeterministicWasi);
        assert!(exact.requires_reference);
        assert!(exact.wasm_safe);

        let cost = EvaluatorKind::CostBudget { max_micros: 10 };
        assert_eq!(cost.catalog_id(), "cost_budget");
        assert_eq!(cost.expected_lane(), EvaluatorLane::DeterministicWasi);
        assert!(cost.catalog_entry().consumes_trace);

        let judge = EvaluatorKind::LlmJudge {
            rubric: "correctness".to_string(),
            model: "judge-model".to_string(),
        };
        assert_eq!(judge.catalog_id(), "llm_judge");
        assert_eq!(judge.expected_lane(), EvaluatorLane::JudgeBroker);
        assert!(!judge.catalog_entry().wasm_safe);

        let mismatch = EvaluatorSpec {
            id: "bad-exact".to_string(),
            lane: EvaluatorLane::JudgeBroker,
            kind: EvaluatorKind::ExactMatch,
        }
        .validate_catalog_lane();
        assert!(matches!(
            mismatch,
            Err(EvalError::EvaluatorLaneMismatch {
                expected: EvaluatorLane::DeterministicWasi,
                actual: EvaluatorLane::JudgeBroker,
                ..
            })
        ));
    }

    #[test]
    fn deterministic_and_judge_lanes_are_separate() {
        let case = EvaluationCase {
            input: serde_json::json!("question"),
            output: serde_json::json!("answer"),
            reference: Some(serde_json::json!("answer")),
            trace: None,
        };
        let exact = EvaluatorSpec {
            id: "exact".to_string(),
            lane: EvaluatorLane::DeterministicWasi,
            kind: EvaluatorKind::ExactMatch,
        };
        let judge = EvaluatorSpec {
            id: "judge".to_string(),
            lane: EvaluatorLane::JudgeBroker,
            kind: EvaluatorKind::LlmJudge {
                rubric: "correctness".to_string(),
                model: "judge-model".to_string(),
            },
        };

        assert_eq!(
            evaluate_deterministic(&exact, &case)
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            1.0
        );
        assert!(matches!(
            evaluate_deterministic(&judge, &case),
            Err(EvalError::RequiresDeterministicLane(_)) | Err(EvalError::RequiresJudgeBroker(_))
        ));
    }

    #[test]
    fn gates_fail_underpowered_and_use_confidence_bounds() {
        let underpowered = compare_paired_scores(
            &[0.9, 0.9],
            &[0.8, 0.8],
            &GatePolicy {
                min_sample_size: 3,
                ..GatePolicy::default()
            },
        );
        assert!(matches!(underpowered, Err(EvalError::Underpowered { .. })));

        let comparison = compare_paired_scores(
            &[1.0, 1.0, 1.0, 1.0, 1.0],
            &[0.0, 0.0, 0.0, 0.0, 0.0],
            &GatePolicy {
                min_sample_size: 5,
                max_regression: 0.05,
                comparison_count: 4,
                ..GatePolicy::default()
            },
        )
        .unwrap_or_else(|err| panic!("{err}"));

        assert_eq!(comparison.decision, GateDecision::FailRegression);
        assert!(comparison.adjusted_alpha < 0.05);
    }

    fn browser_step(action: &str, selector: Option<&str>, matched: bool, status: &str) -> Value {
        serde_json::json!({
            "action": { "action": action },
            "outcome": {
                "status": status,
                "grounding": {
                    "selector": selector,
                    "selector_existed": matched,
                    "matched_element": matched,
                },
                "observation": {
                    "url": "https://shop.example/checkout/confirmation",
                    "dom_html": "<div id=\"order-confirmed\">Thank you</div>",
                },
            },
        })
    }

    fn browser_case(steps: Vec<Value>) -> EvaluationCase {
        EvaluationCase {
            input: serde_json::json!("book a flight"),
            output: serde_json::json!(null),
            reference: None,
            trace: Some(serde_json::json!({ "browser_steps": steps })),
        }
    }

    fn deterministic_spec(kind: EvaluatorKind) -> EvaluatorSpec {
        EvaluatorSpec {
            id: kind.catalog_id().to_string(),
            lane: EvaluatorLane::DeterministicWasi,
            kind,
        }
    }

    #[test]
    fn browser_evaluator_catalog_ids_match_entries() {
        for kind in [
            EvaluatorKind::BrowserTaskSuccess {
                url_contains: None,
                dom_contains: None,
            },
            EvaluatorKind::BrowserStepEfficiency { max_steps: 1 },
            EvaluatorKind::BrowserGrounding { min_ratio: 1.0 },
            EvaluatorKind::BrowserRecovery,
        ] {
            assert_eq!(kind.catalog_entry().id, kind.catalog_id());
            assert_eq!(kind.expected_lane(), EvaluatorLane::DeterministicWasi);
            assert!(kind.catalog_entry().consumes_trace);
        }
    }

    #[test]
    fn browser_task_success_checks_world_state_not_self_report() {
        let case = browser_case(vec![browser_step("click", Some("#pay"), true, "ok")]);
        let pass = deterministic_spec(EvaluatorKind::BrowserTaskSuccess {
            url_contains: Some("confirmation".to_string()),
            dom_contains: Some("order-confirmed".to_string()),
        });
        assert_eq!(
            evaluate_deterministic(&pass, &case)
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            1.0
        );

        let fail = deterministic_spec(EvaluatorKind::BrowserTaskSuccess {
            url_contains: Some("error".to_string()),
            dom_contains: None,
        });
        assert_eq!(
            evaluate_deterministic(&fail, &case)
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            0.0
        );

        // No browser steps => cannot have succeeded.
        let empty = evaluate_deterministic(
            &deterministic_spec(EvaluatorKind::BrowserTaskSuccess {
                url_contains: None,
                dom_contains: None,
            }),
            &browser_case(vec![]),
        )
        .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(empty.score, 0.0);
    }

    #[test]
    fn browser_step_efficiency_enforces_budget() {
        let steps = vec![
            browser_step("click", Some("#a"), true, "ok"),
            browser_step("click", Some("#b"), true, "ok"),
        ];
        let within = deterministic_spec(EvaluatorKind::BrowserStepEfficiency { max_steps: 3 });
        assert_eq!(
            evaluate_deterministic(&within, &browser_case(steps.clone()))
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            1.0
        );
        let over = deterministic_spec(EvaluatorKind::BrowserStepEfficiency { max_steps: 1 });
        assert_eq!(
            evaluate_deterministic(&over, &browser_case(steps))
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            0.0
        );
    }

    #[test]
    fn browser_grounding_reports_resolution_ratio() {
        let steps = vec![
            browser_step("click", Some("#a"), true, "ok"),
            browser_step("click", Some("#b"), false, "error"),
            browser_step("scroll", None, true, "ok"), // not element-targeted, ignored
        ];
        let spec = deterministic_spec(EvaluatorKind::BrowserGrounding { min_ratio: 0.75 });
        let result = evaluate_deterministic(&spec, &browser_case(steps))
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(result.score, 0.5); // 1 of 2 targeted steps grounded
        assert_eq!(result.label.as_deref(), Some("fail"));
    }

    #[test]
    fn browser_recovery_distinguishes_spiral_from_recovery() {
        let recovered = vec![
            browser_step("click", Some("#a"), false, "error"),
            browser_step("click", Some("#a"), true, "ok"),
        ];
        let spec = deterministic_spec(EvaluatorKind::BrowserRecovery);
        assert_eq!(
            evaluate_deterministic(&spec, &browser_case(recovered))
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            1.0
        );

        let spiraled = vec![
            browser_step("click", Some("#a"), false, "error"),
            browser_step("click", Some("#b"), false, "error"),
        ];
        assert_eq!(
            evaluate_deterministic(&spec, &browser_case(spiraled))
                .unwrap_or_else(|err| panic!("{err}"))
                .score,
            0.0
        );
    }
}
