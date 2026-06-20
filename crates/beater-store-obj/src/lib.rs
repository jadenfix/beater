use async_trait::async_trait;
use beater_core::{sha256_hex, ArtifactId, ProjectId, Sha256Hash, TenantId};
use beater_schema::{ArtifactRef, RedactionClass};
use beater_store::{ArtifactStore, StoreError, StoreResult};
use std::fs;
use std::path::PathBuf;
use std::sync::Arc;
use uuid::Uuid;

#[derive(Clone, Debug)]
pub struct FsArtifactStore {
    root: Arc<PathBuf>,
}

impl FsArtifactStore {
    pub fn new(root: impl Into<PathBuf>) -> StoreResult<Self> {
        let root = root.into();
        fs::create_dir_all(&root).map_err(StoreError::backend)?;
        Ok(Self {
            root: Arc::new(root),
        })
    }

    fn path_for_uri(&self, uri: &str) -> StoreResult<PathBuf> {
        let prefix = "artifact://";
        let relative = uri
            .strip_prefix(prefix)
            .ok_or_else(|| StoreError::Integrity(format!("unsupported artifact uri: {uri}")))?;
        if relative.split('/').any(|segment| segment == "..") {
            return Err(StoreError::Integrity(format!(
                "artifact uri cannot contain '..': {uri}"
            )));
        }
        Ok(self.root.join(relative))
    }
}

#[async_trait]
impl ArtifactStore for FsArtifactStore {
    async fn put_bytes(
        &self,
        tenant_id: &TenantId,
        project_id: &ProjectId,
        mime_type: &str,
        redaction_class: RedactionClass,
        bytes: &[u8],
    ) -> StoreResult<ArtifactRef> {
        let artifact_id = ArtifactId::new(Uuid::new_v4().to_string())
            .map_err(|err| StoreError::Integrity(err.to_string()))?;
        let sha256 = Sha256Hash::new(sha256_hex(bytes))
            .map_err(|err| StoreError::Integrity(err.to_string()))?;
        let relative = format!(
            "{}/{}/{}",
            tenant_id.as_str(),
            project_id.as_str(),
            artifact_id.as_str()
        );
        let path = self.root.join(&relative);
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent).map_err(StoreError::backend)?;
        }
        fs::write(&path, bytes).map_err(StoreError::backend)?;

        Ok(ArtifactRef {
            artifact_id,
            uri: format!("artifact://{relative}"),
            sha256,
            size_bytes: bytes.len() as u64,
            mime_type: mime_type.to_string(),
            redaction_class,
        })
    }

    async fn get_bytes(&self, artifact_ref: &ArtifactRef) -> StoreResult<Vec<u8>> {
        let path = self.path_for_uri(&artifact_ref.uri)?;
        let bytes = fs::read(&path).map_err(StoreError::backend)?;
        let actual = sha256_hex(&bytes);
        if actual != artifact_ref.sha256.as_str() {
            return Err(StoreError::Integrity(format!(
                "artifact hash mismatch for {}: expected {}, got {}",
                artifact_ref.uri,
                artifact_ref.sha256.as_str(),
                actual
            )));
        }
        Ok(bytes)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[tokio::test]
    async fn fs_artifact_store_round_trips_and_checks_hash() {
        let tempdir = tempfile::tempdir().unwrap_or_else(|err| panic!("{err}"));
        let store = FsArtifactStore::new(tempdir.path()).unwrap_or_else(|err| panic!("{err}"));
        let tenant = TenantId::new("tenant").unwrap_or_else(|err| panic!("{err}"));
        let project = ProjectId::new("project").unwrap_or_else(|err| panic!("{err}"));

        let artifact = store
            .put_bytes(
                &tenant,
                &project,
                "application/json",
                RedactionClass::Sensitive,
                br#"{"ok":true}"#,
            )
            .await
            .unwrap_or_else(|err| panic!("{err}"));

        let bytes = store
            .get_bytes(&artifact)
            .await
            .unwrap_or_else(|err| panic!("{err}"));
        assert_eq!(bytes, br#"{"ok":true}"#);
    }
}
