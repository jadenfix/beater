use chrono::{DateTime, Utc};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::fmt::{Display, Formatter};

pub type Timestamp = DateTime<Utc>;

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum IdError {
    #[error("identifier cannot be empty")]
    Empty,
    #[error("identifier contains whitespace: {0}")]
    Whitespace(String),
}

macro_rules! id_type {
    ($name:ident) => {
        #[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash, Serialize, Deserialize)]
        #[serde(transparent)]
        pub struct $name(String);

        impl $name {
            pub fn new(value: impl Into<String>) -> Result<Self, IdError> {
                let value = value.into();
                if value.is_empty() {
                    return Err(IdError::Empty);
                }
                if value.chars().any(char::is_whitespace) {
                    return Err(IdError::Whitespace(value));
                }
                Ok(Self(value))
            }

            pub fn as_str(&self) -> &str {
                &self.0
            }
        }

        impl Display for $name {
            fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
                f.write_str(&self.0)
            }
        }

        impl TryFrom<&str> for $name {
            type Error = IdError;

            fn try_from(value: &str) -> Result<Self, Self::Error> {
                Self::new(value)
            }
        }

        impl TryFrom<String> for $name {
            type Error = IdError;

            fn try_from(value: String) -> Result<Self, Self::Error> {
                Self::new(value)
            }
        }
    };
}

id_type!(TenantId);
id_type!(OrganizationId);
id_type!(ProjectId);
id_type!(EnvironmentId);
id_type!(AgentId);
id_type!(AgentReleaseId);
id_type!(RunId);
id_type!(TraceId);
id_type!(SpanId);
id_type!(ArtifactId);
id_type!(DatasetId);
id_type!(DatasetVersionId);
id_type!(DatasetCaseId);
id_type!(ExperimentId);
id_type!(ExperimentRunId);
id_type!(EvaluatorId);
id_type!(EvaluatorVersionId);
id_type!(EvalResultId);
id_type!(GateId);
id_type!(GateRunId);
id_type!(ReviewQueueId);
id_type!(ReviewTaskId);
id_type!(AnnotationId);
id_type!(CalibrationReportId);
id_type!(PromptId);
id_type!(PromptVersionId);
id_type!(ApiKeyId);
id_type!(ProviderSecretId);
id_type!(JudgeCallId);
id_type!(UsageRecordId);
id_type!(AuditEventId);
id_type!(WebhookEndpointId);
id_type!(IdempotencyKey);
id_type!(Sha256Hash);

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct TenantScope {
    pub tenant_id: TenantId,
    pub project_id: ProjectId,
    pub environment_id: EnvironmentId,
}

impl TenantScope {
    pub fn new(tenant_id: TenantId, project_id: ProjectId, environment_id: EnvironmentId) -> Self {
        Self {
            tenant_id,
            project_id,
            environment_id,
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Money {
    pub amount_micros: i64,
    pub currency: String,
}

impl Money {
    pub fn usd_micros(amount_micros: i64) -> Self {
        Self {
            amount_micros,
            currency: "USD".to_string(),
        }
    }
}

#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize, Deserialize)]
pub struct TokenCounts {
    pub input: u64,
    pub output: u64,
    pub reasoning: u64,
    pub cache_read: u64,
}

impl TokenCounts {
    pub fn total(&self) -> u64 {
        self.input + self.output + self.reasoning
    }
}

pub fn sha256_hex(bytes: &[u8]) -> String {
    let digest = Sha256::digest(bytes);
    digest.iter().map(|byte| format!("{byte:02x}")).collect()
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct PageRequest {
    pub limit: u32,
    pub cursor: Option<String>,
}

impl Default for PageRequest {
    fn default() -> Self {
        Self {
            limit: 100,
            cursor: None,
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Page<T> {
    pub items: Vec<T>,
    pub next_cursor: Option<String>,
}

impl<T> Page<T> {
    pub fn new(items: Vec<T>, next_cursor: Option<String>) -> Self {
        Self { items, next_cursor }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ids_reject_empty_and_whitespace() {
        assert_eq!(TenantId::new(""), Err(IdError::Empty));
        assert!(matches!(
            TenantId::new("tenant one"),
            Err(IdError::Whitespace(value)) if value == "tenant one"
        ));
        assert_eq!(
            TenantId::new("tenant-one").map(|id| id.to_string()),
            Ok("tenant-one".to_string())
        );
    }

    #[test]
    fn token_total_excludes_cache_read() {
        let counts = TokenCounts {
            input: 10,
            output: 20,
            reasoning: 5,
            cache_read: 100,
        };
        assert_eq!(counts.total(), 35);
    }
}
