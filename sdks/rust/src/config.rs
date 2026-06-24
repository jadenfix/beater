//! Configuration for the Beater SDK, resolved from explicit args then env vars.

use std::env;

/// Connection + scope settings shared by every span the SDK emits.
///
/// Defaults mirror the Python and TypeScript SDKs so the three behave
/// identically against a local `beaterd`.
#[derive(Debug, Clone)]
pub struct BeaterConfig {
    pub base_url: String,
    pub tenant_id: String,
    pub project_id: String,
    pub environment_id: String,
    pub api_key: Option<String>,
    pub service_name: String,
    pub release_id: Option<String>,
}

impl Default for BeaterConfig {
    fn default() -> Self {
        BeaterConfig {
            base_url: "http://127.0.0.1:8080".to_string(),
            tenant_id: "demo".to_string(),
            project_id: "demo".to_string(),
            environment_id: "local".to_string(),
            api_key: None,
            service_name: "beater-rust".to_string(),
            release_id: None,
        }
    }
}

fn env_or(name: &str, default: &str) -> String {
    match env::var(name) {
        Ok(v) if !v.is_empty() => v,
        _ => default.to_string(),
    }
}

fn env_opt(name: &str) -> Option<String> {
    match env::var(name) {
        Ok(v) if !v.is_empty() => Some(v),
        _ => None,
    }
}

impl BeaterConfig {
    /// Resolve config from `BEATER_*` environment variables, falling back to the
    /// same local defaults as the Python SDK (`http://127.0.0.1:8080`,
    /// `demo`/`demo`/`local`).
    pub fn from_env() -> Self {
        let defaults = BeaterConfig::default();
        BeaterConfig {
            base_url: env_or("BEATER_BASE_URL", &defaults.base_url),
            tenant_id: env_or("BEATER_TENANT_ID", &defaults.tenant_id),
            project_id: env_or("BEATER_PROJECT_ID", &defaults.project_id),
            environment_id: env_or("BEATER_ENVIRONMENT_ID", &defaults.environment_id),
            api_key: env_opt("BEATER_API_KEY"),
            service_name: env_or("BEATER_SERVICE_NAME", &defaults.service_name),
            release_id: env_opt("BEATER_RELEASE_ID"),
        }
    }

    /// The OTLP/HTTP traces endpoint: tenant/project/environment travel in the path.
    pub fn otlp_http_traces_url(&self) -> String {
        let base = self.base_url.trim_end_matches('/');
        format!(
            "{base}/v1/otlp/{}/{}/{}/v1/traces",
            self.tenant_id, self.project_id, self.environment_id
        )
    }
}
