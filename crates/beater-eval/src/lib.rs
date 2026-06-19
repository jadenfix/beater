use async_trait::async_trait;
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
    #[error("judge budget exceeded: attempted {attempted_micros} micros, remaining {remaining_micros} micros")]
    JudgeBudgetExceeded {
        attempted_micros: i64,
        remaining_micros: i64,
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

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct EvaluationCase {
    pub input: Value,
    pub output: Value,
    pub reference: Option<Value>,
    pub trace: Option<Value>,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct ScoreResult {
    pub score: f64,
    pub label: Option<String>,
    pub evidence: Value,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct EvaluatorSpec {
    pub id: String,
    pub lane: EvaluatorLane,
    pub kind: EvaluatorKind,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum EvaluatorKind {
    ExactMatch,
    RegexMatch { pattern: String },
    JsonObject,
    CostBudget { max_micros: i64 },
    LatencyBudgetMs { max_ms: u64 },
    LlmJudge { rubric: String, model: String },
}

pub fn evaluate_deterministic(
    spec: &EvaluatorSpec,
    case: &EvaluationCase,
) -> Result<ScoreResult, EvalError> {
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
    }
}

fn binary_score(pass: bool, metric: &str) -> ScoreResult {
    ScoreResult {
        score: if pass { 1.0 } else { 0.0 },
        label: Some(if pass { "pass" } else { "fail" }.to_string()),
        evidence: serde_json::json!({ "metric": metric, "pass": pass }),
    }
}

#[async_trait]
pub trait JudgeProvider: Send + Sync {
    async fn judge(&self, request: JudgeRequest) -> anyhow::Result<JudgeResponse>;
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct JudgeRequest {
    pub rubric: String,
    pub model: String,
    pub input: Value,
    pub output: Value,
    pub reference: Option<Value>,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
pub struct JudgeResponse {
    pub score: f64,
    pub rationale: String,
    pub cost: Money,
}

pub struct JudgeBroker<P> {
    provider: P,
    remaining_budget_micros: std::sync::Mutex<i64>,
}

impl<P> JudgeBroker<P>
where
    P: JudgeProvider,
{
    pub fn new(provider: P, budget: Money) -> Self {
        Self {
            provider,
            remaining_budget_micros: std::sync::Mutex::new(budget.amount_micros),
        }
    }

    pub async fn evaluate(
        &self,
        spec: &EvaluatorSpec,
        case: &EvaluationCase,
    ) -> Result<ScoreResult, EvalError> {
        let EvaluatorKind::LlmJudge { rubric, model } = &spec.kind else {
            return Err(EvalError::RequiresDeterministicLane(spec.id.clone()));
        };
        if spec.lane != EvaluatorLane::JudgeBroker {
            return Err(EvalError::RequiresJudgeBroker(spec.id.clone()));
        }

        let response = self
            .provider
            .judge(JudgeRequest {
                rubric: rubric.clone(),
                model: model.clone(),
                input: case.input.clone(),
                output: case.output.clone(),
                reference: case.reference.clone(),
            })
            .await
            .map_err(EvalError::from_anyhow)?;

        let mut remaining = self.remaining_budget_micros.lock().map_err(|err| {
            EvalError::RequiresJudgeBroker(format!("budget mutex poisoned: {err}"))
        })?;
        if response.cost.amount_micros > *remaining {
            return Err(EvalError::JudgeBudgetExceeded {
                attempted_micros: response.cost.amount_micros,
                remaining_micros: *remaining,
            });
        }
        *remaining -= response.cost.amount_micros;

        Ok(ScoreResult {
            score: response.score,
            label: None,
            evidence: serde_json::json!({
                "rationale": response.rationale,
                "cost_micros": response.cost.amount_micros,
                "currency": response.cost.currency
            }),
        })
    }
}

impl EvalError {
    fn from_anyhow(error: anyhow::Error) -> Self {
        Self::RequiresJudgeBroker(error.to_string())
    }
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
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

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum GateDecision {
    Pass,
    FailRegression,
    Inconclusive,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum StatisticalTest {
    PairedNormalApproximation,
}

#[derive(Clone, Debug, PartialEq, Serialize, Deserialize)]
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
    use beater_core::Money;

    #[tokio::test]
    async fn deterministic_and_judge_lanes_are_separate() {
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

    #[tokio::test]
    async fn judge_broker_meters_budget() {
        let broker = JudgeBroker::new(
            FixedJudgeProvider {
                score: 0.75,
                cost_micros: 20,
            },
            Money::usd_micros(30),
        );
        let spec = EvaluatorSpec {
            id: "judge".to_string(),
            lane: EvaluatorLane::JudgeBroker,
            kind: EvaluatorKind::LlmJudge {
                rubric: "correctness".to_string(),
                model: "judge-model".to_string(),
            },
        };
        let case = EvaluationCase {
            input: serde_json::json!("question"),
            output: serde_json::json!("answer"),
            reference: None,
            trace: None,
        };

        let first = broker
            .evaluate(&spec, &case)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(first.score, 0.75);
        assert!(matches!(
            broker.evaluate(&spec, &case).await,
            Err(EvalError::JudgeBudgetExceeded {
                attempted_micros: 20,
                remaining_micros: 10
            })
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

    struct FixedJudgeProvider {
        score: f64,
        cost_micros: i64,
    }

    #[async_trait]
    impl JudgeProvider for FixedJudgeProvider {
        async fn judge(&self, _request: JudgeRequest) -> anyhow::Result<JudgeResponse> {
            Ok(JudgeResponse {
                score: self.score,
                rationale: "fixed".to_string(),
                cost: Money::usd_micros(self.cost_micros),
            })
        }
    }
}
