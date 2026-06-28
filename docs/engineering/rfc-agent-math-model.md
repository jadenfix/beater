# RFC: A First-Principles Mathematical Model of Agents in Beater

Status: Draft / thinking document
Scope: how to model every agent run as a measurable stochastic object, monitor
it with principled statistics, learn from it, and surface the result as a handful
of calibrated scalars — without the user ever seeing the math.

This RFC is grounded in the existing code, not a greenfield wish-list. Every
section names the crate/file it attaches to.

---

## 0. The one idea

> An agent run is **not** a log. It is a *sample path of a hierarchical, timed,
> marked stochastic process*. Beater already records that sample path losslessly
> (`crates/beater-schema` `CanonicalSpan`). So we are not instrumenting agents —
> we are doing **statistical inference on an already-observed stochastic process**.

Everything below is a projection of one object — the canonical span forest — onto
a different mathematical axis (topology, time, cost, quality, reliability,
causality, geometry). "Modeling in many dimensions" = choosing the projection.

The product principle that keeps UX easy:

> **Heavy inference runs server-side and is compressed to ≤1 low-dimensional,
> calibrated, uncertainty-bearing scalar per concern.** The dashboard shows the
> scalar; one click reveals the distribution; one more reveals the raw trace.
> Progressive disclosure of dimension, not of math.

---

## 1. The canonical object

A run `r` is a rooted, timed, labeled forest

```
T_r = (V, E, ℓ, t, x)
```

- `V` = spans; `E` = parent→child edges (`parent_span_id`), so `T_r` is a tree (forest across a trace).
- `ℓ : V → K`, the kind label, `K` = the 14 `AgentSpanKind`s
  (`AgentRun, AgentTurn, AgentPlan, AgentStep, LlmCall, ToolCall, McpRequest,
  RetrievalQuery, MemoryRead, MemoryWrite, GuardrailCheck, HumanReview,
  EvaluatorRun, ReplayRun`).
- `t : V → (start, end)` from `start_time/end_time` → duration `d_v = end−start`.
- `x : V → ℝ^D`, the per-span feature vector, **already present** on `CanonicalSpan`:
  `cost`, `tokens` (in/out), `d_v` (latency), `status∈{ok,error}`, `model`
  embedding, `seq`, depth.

Sibling spans ordered by `seq` are a **marked point process in time**; the
parent→children relation is a **branching process**. Those two views give us
almost everything.

The dimensions we model (each is a coordinate of this same object):
`time · cost · tokens · latency · quality · kind-topology · model · uncertainty ·
reliability · semantics(I/O embeddings) · causality`.

---

## 2. Generative model: Hierarchical Semi-Markov Branching Process

Fit, **per agent-release** (`AgentReleaseId`), three coupled estimators from spans:

### 2.1 Kind-transition chain `P ∈ ℝ^{14×14}`
Among ordered siblings (and parent→first-child), count `ℓ(v) → ℓ(next)`. MLE is
just normalized counts. `P` is the agent's "grammar." A candidate release whose
`P` differs from baseline is behaving differently *before any quality metric moves*.

### 2.2 Holding times (semi-Markov)
Per kind `k`, fit `d_v ~ LogNormal(μ_k, σ_k²)` (latency is heavy-tailed; log-normal
or Gamma fits LLM/tool latencies well). This yields **analytic tail latency**:
`P(d > SLO)` per kind in closed form — no histogram needed for the p99.

### 2.3 Offspring / branching `M`
Let `M[a,b]` = expected number of children of kind `b` produced by a span of kind
`a` (mean offspring matrix of a multitype Galton–Watson process). Estimated by
averaging child-kind counts over parents of each kind.

**The key invariant — termination safety via the spectral radius:**

```
ρ(M) = largest eigenvalue magnitude of M
ρ(M) < 1  ⇒  the run process is sub-critical ⇒ terminates a.s. (finite expected size)
ρ(M) ≥ 1  ⇒  super-critical ⇒ runaway / non-termination risk
```

A *single number* `ρ(M)` is a runaway-loop early-warning gauge. (The open
security PRs already worry about "warm-loop" / runaway evidence; this gives it a
rigorous, continuously-monitorable definition.) Expected subtree size under a
kind `k` is the corresponding row-sum of `(I − M)^{-1}` — i.e. "how much work does
one `agent.step` spawn on average," with a finite value iff sub-critical.

> UX surface: a **Termination-safety gauge** (green `ρ<0.8`, amber `0.8–1`,
> red `≥1`) on the release page. One scalar; the eigen-decomposition stays hidden.

### 2.4 Latent mode HMM (optional, higher-order)
Over the `agent.step` sequence, fit an HMM whose latent states are interpretable
modes (`explore / exploit / stuck / recover`). Forward–backward gives a per-step
posterior; `P(stuck) > τ` is an actionable alert, and the Viterbi path is a
human-readable "strategy decode" overlaid on the existing waterfall.

---

## 3. Evaluation & gating: from fixed-α z-test to anytime-valid inference

Today (`crates/beater-eval/src/lib.rs::compare_paired_scores`): paired
normal-approximation on score differences, Bonferroni `alpha/comparison_count`,
CI-band decision `Pass / FailRegression / Inconclusive`. This is sound for **one
look**. It is *not* valid for the way gates are actually used.

### 3.1 The peeking problem (the real bug, statistically)
A CI gate is evaluated on *every PR / every new batch of cases*. That is repeated
significance testing on accumulating data → type-I error inflation that Bonferroni
over `comparison_count` does not fix (Bonferroni handles **multiple metrics**, not
**multiple looks in time**).

**Fix — confidence sequences / e-processes (anytime-valid inference).** Replace the
fixed-`z` interval with a *time-uniform* confidence sequence (e.g. an
empirical-Bernstein or mixture-SPRT confidence sequence). Then:

- The interval is valid **at every look simultaneously** — peek as often as you like.
- You can **stop early** the moment the e-value crosses `1/α` (ship a clear win
  without waiting for `min_sample_size`), and the `Inconclusive` band shrinks
  honestly as data accrues.
- It composes cleanly with the existing `GateDecision` enum — only the interval
  math changes; `ci_low/ci_high` become sequence bounds.

### 3.2 Power & required-n (replace the binary `Underpowered` error)
`EvalError::Underpowered` is all-or-nothing. From the observed difference variance
`σ̂²` and a minimum detectable effect `δ` (the `max_regression` already in
`GatePolicy`), the required sample size is

```
n* ≈ 2 (z_{α} + z_{β})² σ̂² / δ²
```

> UX surface: instead of "underpowered," show **"Need ~24 more cases to detect a
> 1% regression at 95%/80%."** Deep math, one friendly sentence.

### 3.3 Multiplicity done right
When many evaluators/metrics are compared at once, **Benjamini–Hochberg FDR** has
strictly more power than Bonferroni at the same risk profile and is the correct
control when the goal is "few false regressions among many metrics."

### 3.4 Pairwise → distributional
Mean-of-differences hides *where* a release regressed. Add a **Wasserstein-1
distance** between baseline and candidate score distributions (and per-kind
latency/cost distributions): one principled scalar for "how different," robust to
shape changes a mean misses.

---

## 4. Judge reliability: a measurement-error model, not a threshold

Today (`crates/beater-calibration`): judge label vs human label, a scalar
`pass_threshold`. That is the **inter-rater reliability** problem; treat it as one.

1. **Agreement beyond chance:** Cohen's κ / Krippendorff's α (judge vs human),
   not raw accuracy.
2. **Latent-truth (Dawid–Skene + EM):** treat *both* human and judge as noisy
   raters of a latent true label; infer each rater's confusion matrix
   (sensitivity/specificity) and the latent labels jointly. Output: a per-judge,
   per-evaluator reliability profile — "this judge is 0.94 specific but 0.71
   sensitive on refusal cases."
3. **Calibration:** compute **ECE** (expected calibration error) and fit an
   **isotonic / Platt** recalibration map so a judge score `0.7` means an actual
   70% pass probability. `pass_threshold` then becomes a **Bayes-optimal decision
   boundary** under an explicit cost matrix (cost of a false-pass vs false-fail),
   not a guessed `0.5`.
4. **Propagate the uncertainty:** the gate (§3) should integrate over judge label
   uncertainty rather than treating judge scores as ground truth — calibrated
   judge variance flows into the confidence sequence.

> UX surface: a single **"Judge trust"** score (1−ECE, gated by κ) with a
> red flag when a judge is mis-calibrated; recalibration applied silently.

---

## 5. Cost, latency & routing: resource processes and optimization

### 5.1 Latency is a longest path, not a sum
Wall-clock latency of a run is the **critical path** = longest weighted path in the
*timed* span DAG, not `Σ d_v`. Compute it with a DAG longest-path pass over the
existing span tree. Output is directly actionable and fits the existing waterfall
UI: highlight the critical path, and report **"parallelizing `tool.call` X and Y
saves ≈Δt"** when two critical spans are independent (no data edge between them).

### 5.2 Cost/quality Pareto frontier
Each release is a point `(cost, quality)`. Maintain the **Pareto-optimal set**; a
*dominated* candidate (more cost, no more quality) should never ship and can be
auto-stamped as such. The frontier is a one-glance multi-objective view.

### 5.3 Model routing as off-policy bandit evaluation
Choosing a model per `llm.call` is a **contextual bandit**; reward = quality −
λ·cost. The win is **off-policy evaluation**: from *logged traces alone*, estimate
"what if we had routed the cheaper model here" via **inverse-propensity / doubly-
robust** estimators — no re-runs, no spend. Output: a recommended routing policy
with an estimated quality/cost delta and CI. (This is where `beater-replay`
becomes the *experimental* check on the *observational* estimate — see §7.)

---

## 6. Monitoring & active learning: watch everything, learn cheaply

### 6.1 Per-run outlier score (cheap, one number)
Maintain per-release feature mean `μ` and covariance `Σ`. Each run's
**Mahalanobis distance** `√((x−μ)ᵀ Σ⁻¹ (x−μ))` is a single novelty score. No
training loop, updates online.

### 6.2 Distribution drift
Between a rolling window and the release baseline, monitor **PSI / KL / MMD** on
per-kind `(cost, tokens, latency, error-rate)`. MMD with a characteristic kernel
catches multivariate shifts a per-metric check misses.

### 6.3 Changepoints
**Bayesian online changepoint detection** (or CUSUM) on the error-rate and quality
time series → "regression began at commit `X` / time `T`," posted as an alert
(`crates/beater-alerts`) with the offending release pinned.

### 6.4 Active learning closes the "promote failure to dataset" loop *automatically*
The product loop is "promote failure → dataset → eval." Make promotion **optimal**:
rank candidate traces by **expected information gain** — model uncertainty (entropy
of the calibrated judge), novelty (§6.1), and committee disagreement. Label the
top-k; you grow the dataset with the fewest human labels per unit of model
improvement. The "anomalous + uncertain" traces *are* the dataset Beater should ask
the human to label.

---

## 7. Causality: replay **is** the do-operator

`crates/beater-replay` re-executes a trace under a changed condition. That is
literally Pearl's **do(·) intervention**. So Beater can do both arms of causal
inference natively:

- **Observational (free, from logged traces):** estimate the average treatment
  effect of an intervention — e.g. "insert a `guardrail.check` before `tool.call`"
  — by backdoor adjustment / propensity weighting over the span DAG (the trace
  topology *is* the causal skeleton). Cheap, but confounded.
- **Experimental (replay):** `do()` the intervention on a sample and measure the
  outcome diff directly. Unconfounded, but costs a run.

Use the observational estimate to **prioritize which interventions are worth a
replay**, then confirm with replay. Output: ranked interventions, each with an ATE
estimate, a CI, and "confirmed by N replays."

---

## 8. Geometry: behavioral archetypes

Embed each trace (kind n-grams + I/O embeddings of `input_ref/output_ref`) and
cluster (mixture model / HDBSCAN). Clusters = **failure modes / task archetypes**.
A new run is soft-assigned: *"this run resembles cluster #7 (tool-retry-loop),
which fails 60% of the time"* — surfaced on the trace page, powered by
`crates/beater-search` for retrieval of nearest exemplars. Optimal transport
between release-level trace distributions gives the §3.4 distance for free.

---

## 9. The delivery vehicle: math as a contract surface (math-MCPs)

Per `CLAUDE.md`, every `/v1` endpoint auto-projects into **MCP tools + 7 SDKs +
CLI + docs** from one OpenAPI artifact. So the *cheapest* way to ship all of the
above as a product — usable by humans *and* by agents (RSI: agents improving
agents) — is as endpoints. Proposed analysis surface (each `→` an MCP tool for free):

| Endpoint / MCP tool            | Returns                                              | §  |
|--------------------------------|-----------------------------------------------------|----|
| `analyze.offspringSpectrum`    | `ρ(M)`, per-kind branching, runaway risk            | 2.3|
| `analyze.criticalPath`         | longest timed path + parallelization savings        | 5.1|
| `analyze.driftScore`           | PSI/MMD between two windows or releases              | 6.2|
| `analyze.changepoints`         | changepoint timestamps on a metric series           | 6.3|
| `eval.power`                   | required-n / minimum detectable effect              | 3.2|
| `eval.sequentialVerdict`       | anytime-valid confidence-sequence decision          | 3.1|
| `judge.calibration`            | κ, ECE, isotonic map, Dawid–Skene confusion         | 4  |
| `route.offPolicyEstimate`      | doubly-robust quality/cost delta of a routing policy| 5.3|
| `anomaly.rankTraces`           | Mahalanobis/novelty ranking for dataset promotion   | 6.1|
| `behavior.clusterAssign`       | archetype + historical failure rate                 | 8  |
| `causal.interventionEffect`    | ATE + CI of an intervention (obs + replay)          | 7  |

Implementation shape that fits Beater's conventions:

- A new **pure, deterministic crate `beater-mathkit`** holds the estimators
  (eigenvalues, EM, isotonic, confidence sequences, Mahalanobis, MMD, DAG
  longest-path). Deterministic + property-tested, exactly like the existing
  deterministic-lane crates and their conformance suites — so results are
  reproducible and offline (honoring R11 / offline-self-host).
- Thin handlers in `crates/beater-api` annotated with `#[utoipa::path]` →
  `cargo xtask regen-spec` + `scripts/regen-sdks.sh` propagate everything.
- Workers in `beaterd` (the bus, `crates/beater-bus`) recompute `ρ(M)`, drift,
  changepoints, Mahalanobis incrementally on `TraceIngested` events — the same
  hook `TraceIngestedSearchProcessor` already uses for indexing.

Native crate over an external math service is deliberate: it keeps the whole loop
**offline, deterministic, and self-hostable**, which is the product's core promise.

---

## 10. Reconciling rigor with "the user sees an easy experience"

The contract that makes this honest:

1. **One calibrated scalar per concern**, each with an uncertainty band, never a
   bare point estimate. (Termination safety, Judge trust, Ship verdict, Anomaly,
   Drift, Pareto position.)
2. **Progressive disclosure of dimension:** scalar → distribution → raw trace.
   The math is in the server; the screen has a gauge.
3. **Calibration is non-negotiable:** every probability shown is recalibrated
   (§4) so "0.7" is trustworthy. A platform that monitors itself must be
   *calibrated about itself*.
4. **Defaults are decisions:** `pass_threshold`, `alpha`, `max_regression`,
   `min_sample_size` become *derived* from cost matrices and power targets, with
   sensible defaults — the user accepts a recommendation, they don't tune knobs.
5. **No silent caps:** anything truncated/sampled is logged (mirrors the repo's
   existing "no silent wildcard" / loud-failure ethos in `beater-temporal`).

---

## 11. Suggested sequencing (low-risk → high-value)

1. `analyze.criticalPath` + `analyze.offspringSpectrum` — pure functions over a
   single trace, no statistics infra, immediately useful, great demos.
2. `eval.power` + Wasserstein in the existing comparison — small additions to
   `beater-eval`, directly improve the gate UX.
3. `judge.calibration` (κ/ECE/isotonic) — upgrades `beater-calibration` from a
   threshold to a reliability model.
4. `eval.sequentialVerdict` — the statistically-correct gate; swap the interval
   math, keep `GateDecision`.
5. Streaming monitors (Mahalanobis, drift, changepoints) on the bus →
   `anomaly.rankTraces` → automatic active-learning dataset promotion.
6. Off-policy routing + causal/replay — the highest-leverage, highest-effort tier.

---

### One-paragraph summary

Beater already stores each agent run as a lossless, timed, labeled span forest, so
the work is not instrumentation but **inference on an observed stochastic process**.
Model the forest three ways at once — a multitype branching process (whose
spectral radius `ρ(M)<1` is a rigorous runaway-safety gauge), a semi-Markov timed
process (whose critical path is the true latency and whose holding-times give
analytic tails), and a marked sequence (whose latent-mode HMM decodes strategy).
Make the gate **anytime-valid** (confidence sequences) so peeking on every PR is
honest, report **required-n** instead of a binary "underpowered," treat the judge
as a **calibrated noisy rater** (Dawid–Skene + isotonic + ECE), monitor everything
online (Mahalanobis, MMD/PSI drift, Bayesian changepoints) and let that ranking
**auto-select the most informative failures to label** (active learning), and use
**replay as the do-operator** for causal intervention estimates. Ship all of it as
`/v1` endpoints from a deterministic `beater-mathkit` crate so the contract turns
each estimator into an MCP tool + 7 SDKs + CLI for free — and compress every result
to **one calibrated, uncertainty-bearing scalar** behind progressive disclosure, so
the user sees a gauge, not a gradient.
