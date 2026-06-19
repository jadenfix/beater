use beater_eval::{EvaluationCase, ScoreResult};
use std::num::NonZeroUsize;
use wasmtime::{Config, Engine, Linker, Module, Store};

#[derive(Debug, thiserror::Error)]
pub enum SandboxError {
    #[error("evaluator input is too large: {size_bytes} > {limit_bytes}")]
    InputTooLarge {
        size_bytes: usize,
        limit_bytes: usize,
    },
    #[error("module imports are disabled in deterministic evaluator sandbox: {0}")]
    HostImportDenied(String),
    #[error("evaluator must export memory named `memory`")]
    MissingMemory,
    #[error("evaluator must export function `score(ptr: i32, len: i32) -> i32`")]
    MissingScoreFunction,
    #[error("evaluator returned invalid basis point score {0}; expected 0..=10000")]
    InvalidScore(i32),
    #[error("wasm execution failed: {0}")]
    Execution(String),
}

#[derive(Clone, Debug)]
pub struct WasmEvaluatorRuntime {
    engine: Engine,
    max_input_bytes: usize,
    fuel: u64,
}

impl WasmEvaluatorRuntime {
    pub fn new(config: SandboxConfig) -> Result<Self, SandboxError> {
        let mut wasmtime_config = Config::new();
        wasmtime_config.consume_fuel(true);
        wasmtime_config.wasm_backtrace_max_frames(NonZeroUsize::new(1));
        let engine = Engine::new(&wasmtime_config)
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        Ok(Self {
            engine,
            max_input_bytes: config.max_input_bytes,
            fuel: config.fuel,
        })
    }

    pub fn evaluate_case_json(
        &self,
        wasm_bytes: &[u8],
        case: &EvaluationCase,
    ) -> Result<ScoreResult, SandboxError> {
        let input =
            serde_json::to_vec(case).map_err(|err| SandboxError::Execution(err.to_string()))?;
        self.evaluate_bytes(wasm_bytes, &input)
    }

    pub fn evaluate_bytes(
        &self,
        wasm_bytes: &[u8],
        input: &[u8],
    ) -> Result<ScoreResult, SandboxError> {
        if input.len() > self.max_input_bytes {
            return Err(SandboxError::InputTooLarge {
                size_bytes: input.len(),
                limit_bytes: self.max_input_bytes,
            });
        }

        let module = Module::new(&self.engine, wasm_bytes)
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        if let Some(import) = module.imports().next() {
            let name = import.name();
            return Err(SandboxError::HostImportDenied(format!(
                "{}::{name}",
                import.module()
            )));
        }

        let linker = Linker::new(&self.engine);
        let mut store = Store::new(&self.engine, ());
        store
            .set_fuel(self.fuel)
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        let instance = linker
            .instantiate(&mut store, &module)
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        let memory = instance
            .get_memory(&mut store, "memory")
            .ok_or(SandboxError::MissingMemory)?;
        if input.len() > memory.data_size(&store) {
            let current_pages = memory.size(&store);
            let needed_pages = input.len().div_ceil(65_536) as u64;
            if needed_pages > current_pages {
                memory
                    .grow(&mut store, needed_pages - current_pages)
                    .map_err(|err| SandboxError::Execution(err.to_string()))?;
            }
        }
        memory
            .write(&mut store, 0, input)
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        let score_fn = instance
            .get_typed_func::<(i32, i32), i32>(&mut store, "score")
            .map_err(|_| SandboxError::MissingScoreFunction)?;
        let basis_points = score_fn
            .call(&mut store, (0, input.len() as i32))
            .map_err(|err| SandboxError::Execution(err.to_string()))?;
        if !(0..=10_000).contains(&basis_points) {
            return Err(SandboxError::InvalidScore(basis_points));
        }
        Ok(ScoreResult {
            score: basis_points as f64 / 10_000.0,
            label: Some(
                if basis_points >= 5_000 {
                    "pass"
                } else {
                    "fail"
                }
                .to_string(),
            ),
            evidence: serde_json::json!({
                "basis_points": basis_points,
                "runtime": "wasmtime",
                "host_imports": "disabled",
            }),
        })
    }
}

#[derive(Clone, Debug)]
pub struct SandboxConfig {
    pub max_input_bytes: usize,
    pub fuel: u64,
}

impl Default for SandboxConfig {
    fn default() -> Self {
        Self {
            max_input_bytes: 64 * 1024,
            fuel: 1_000_000,
        }
    }
}

impl Default for WasmEvaluatorRuntime {
    fn default() -> Self {
        Self::new(SandboxConfig::default())
            .unwrap_or_else(|err| panic!("default WasmEvaluatorRuntime must construct: {err}"))
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use beater_eval::EvaluationCase;
    use serde_json::json;

    #[test]
    fn wasmtime_evaluator_scores_case_json() {
        let wasm = wat::parse_str(
            r#"
            (module
              (memory (export "memory") 1)
              (func (export "score") (param $ptr i32) (param $len i32) (result i32)
                local.get $len
                i32.const 0
                i32.eq
                if (result i32)
                  i32.const 0
                else
                  local.get $ptr
                  i32.load8_u
                  i32.const 123
                  i32.eq
                  if (result i32)
                    i32.const 10000
                  else
                    i32.const 0
                  end
                end))
            "#,
        )
        .unwrap_or_else(|err| panic!("{err}"));
        let runtime = WasmEvaluatorRuntime::default();
        let score = runtime
            .evaluate_case_json(
                &wasm,
                &EvaluationCase {
                    input: json!("question"),
                    output: json!("answer"),
                    reference: Some(json!("answer")),
                    trace: None,
                },
            )
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(score.score, 1.0);
        assert_eq!(score.evidence["host_imports"], json!("disabled"));
    }

    #[test]
    fn sandbox_rejects_host_imports() {
        let wasm = wat::parse_str(
            r#"
            (module
              (import "wasi_snapshot_preview1" "fd_write" (func $fd_write))
              (memory (export "memory") 1)
              (func (export "score") (param i32 i32) (result i32)
                i32.const 10000))
            "#,
        )
        .unwrap_or_else(|err| panic!("{err}"));
        let runtime = WasmEvaluatorRuntime::default();
        assert!(matches!(
            runtime.evaluate_bytes(&wasm, br#"{}"#),
            Err(SandboxError::HostImportDenied(import)) if import == "wasi_snapshot_preview1::fd_write"
        ));
    }

    #[test]
    fn sandbox_fuel_bounds_infinite_loops() {
        let wasm = wat::parse_str(
            r#"
            (module
              (memory (export "memory") 1)
              (func (export "score") (param i32 i32) (result i32)
                (loop $again
                  br $again)
                i32.const 0))
            "#,
        )
        .unwrap_or_else(|err| panic!("{err}"));
        let runtime = WasmEvaluatorRuntime::new(SandboxConfig {
            max_input_bytes: 1024,
            fuel: 1_000,
        })
        .unwrap_or_else(|err| panic!("{err}"));
        let result = runtime.evaluate_bytes(&wasm, br#"{}"#);
        assert!(
            matches!(result, Err(SandboxError::Execution(_))),
            "{result:?}"
        );
    }
}
