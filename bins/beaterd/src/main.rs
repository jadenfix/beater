use anyhow::Context;
use beater_api::{router, ApiState};
use beater_archive::ParquetTraceArchive;
use beater_audit::SqliteAuditStore;
use beater_auth::SqliteApiKeyStore;
use beater_bus::{DurableBus, InMemoryBus, SqliteDurableBus};
use beater_calibration::SqliteCalibrationStore;
use beater_core::Money;
use beater_datasets::SqliteDatasetStore;
use beater_experiments::SqliteExperimentStore;
use beater_gates::SqliteGateStore;
use beater_human::SqliteHumanReviewStore;
use beater_ingest::{IngestPolicy, IngestService};
use beater_judge::{
    HttpRoutingJudgeProvider, JudgeBrokerService, JudgeProvider, KeywordJudgeProvider,
    SqliteJudgeLedger,
};
use beater_search::TantivySearchIndex;
use beater_secrets::{EncryptedSqliteProviderSecretStore, SecretKeyring};
use beater_store::{FsArtifactStore, SqliteTraceStore};
use beater_usage::SqliteUsageLedger;
use clap::{Parser, ValueEnum};
use std::net::SocketAddr;
use std::path::PathBuf;
use std::sync::Arc;

#[derive(Debug, Parser)]
#[command(
    name = "beaterd",
    about = "All-in-one Beater agent observability server"
)]
struct Args {
    #[arg(long, default_value = "127.0.0.1:8080")]
    addr: SocketAddr,
    #[arg(long, default_value = ".beater")]
    data_dir: PathBuf,
    #[arg(long, default_value_t = 1024)]
    bus_capacity: usize,
    #[arg(long, value_enum, default_value_t = BusBackendArg::Sqlite)]
    bus_backend: BusBackendArg,
    #[arg(long, value_enum, default_value_t = AuthModeArg::Local)]
    auth_mode: AuthModeArg,
    #[arg(long, env = "BEATER_PROVIDER_SECRET_KEY")]
    provider_secret_key: Option<String>,
    #[arg(long, value_enum, default_value_t = JudgeProviderArg::Keyword)]
    judge_provider: JudgeProviderArg,
    #[arg(long, env = "BEATER_JUDGE_BUDGET_MICROS", default_value_t = 1_000_000)]
    judge_budget_micros: i64,
}

#[derive(Clone, Copy, Debug, ValueEnum)]
enum AuthModeArg {
    Local,
    Required,
}

#[derive(Clone, Copy, Debug, ValueEnum)]
enum BusBackendArg {
    Sqlite,
    Memory,
}

#[derive(Clone, Copy, Debug, ValueEnum)]
enum JudgeProviderArg {
    Keyword,
    HttpRouting,
}

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let args = Args::parse();
    let artifacts = Arc::new(FsArtifactStore::new(args.data_dir.join("artifacts"))?);
    let traces = Arc::new(SqliteTraceStore::open(args.data_dir.join("traces.sqlite"))?);
    let search = Arc::new(TantivySearchIndex::open_or_create(
        args.data_dir.join("search"),
    )?);
    let archive = ParquetTraceArchive::new(args.data_dir.join("archive"))?;
    let datasets = Arc::new(SqliteDatasetStore::open(
        args.data_dir.join("datasets.sqlite"),
    )?);
    let experiments = Arc::new(SqliteExperimentStore::open(
        args.data_dir.join("experiments.sqlite"),
    )?);
    let gates = Arc::new(SqliteGateStore::open(args.data_dir.join("gates.sqlite"))?);
    let human_reviews = Arc::new(SqliteHumanReviewStore::open(
        args.data_dir.join("reviews.sqlite"),
    )?);
    let calibrations = Arc::new(SqliteCalibrationStore::open(
        args.data_dir.join("calibrations.sqlite"),
    )?);
    let usage = Arc::new(SqliteUsageLedger::open(args.data_dir.join("usage.sqlite"))?);
    let audit = Arc::new(SqliteAuditStore::open(args.data_dir.join("audit.sqlite"))?);
    let provider_secret_keyring = match args.provider_secret_key.as_deref() {
        Some(encoded) => SecretKeyring::from_base64("env-v1", encoded)?,
        None => SecretKeyring::load_or_create_local_file(
            args.data_dir.join("provider-secrets.key"),
            "local-v1",
        )?,
    };
    let provider_secrets = Arc::new(EncryptedSqliteProviderSecretStore::open(
        args.data_dir.join("provider-secrets.sqlite"),
        provider_secret_keyring,
    )?);
    let judge_ledger = Arc::new(SqliteJudgeLedger::open(args.data_dir.join("judge.sqlite"))?);
    let judge_provider: Arc<dyn JudgeProvider> = match args.judge_provider {
        JudgeProviderArg::Keyword => Arc::new(KeywordJudgeProvider::default()),
        JudgeProviderArg::HttpRouting => Arc::new(HttpRoutingJudgeProvider::default()),
    };
    let judge_broker = Arc::new(JudgeBrokerService::new(
        provider_secrets.clone(),
        judge_ledger.clone(),
        judge_provider,
        Money::usd_micros(args.judge_budget_micros),
    ));
    let bus: Arc<dyn DurableBus> = match args.bus_backend {
        BusBackendArg::Sqlite => Arc::new(
            SqliteDurableBus::open(args.data_dir.join("bus.sqlite"), args.bus_capacity)
                .map_err(anyhow::Error::from)?,
        ),
        BusBackendArg::Memory => Arc::new(InMemoryBus::new(args.bus_capacity)),
    };
    let ingest = IngestService::new(artifacts, traces.clone(), bus, IngestPolicy::default());
    let mut state =
        ApiState::with_integrations(ingest, traces, search, archive, datasets, experiments)
            .with_gates(gates)
            .with_human_reviews(human_reviews)
            .with_calibrations(calibrations)
            .with_usage(usage)
            .with_audit(audit)
            .with_judge(provider_secrets, judge_broker, judge_ledger);
    if matches!(args.auth_mode, AuthModeArg::Required) {
        let api_keys = Arc::new(SqliteApiKeyStore::open(
            args.data_dir.join("security.sqlite"),
        )?);
        state = state.require_auth(api_keys);
    }
    let app = router(state);
    let listener = tokio::net::TcpListener::bind(args.addr)
        .await
        .with_context(|| format!("bind {}", args.addr))?;
    axum::serve(listener, app).await.context("serve beaterd")?;
    Ok(())
}
