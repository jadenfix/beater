package ai.beater.sdk;

/**
 * Connection + scope settings for the Beater SDK.
 *
 * <p>{@link #fromEnv()} reads {@code BEATER_*} environment variables with local
 * defaults so a zero-config {@code Beater.init(BeaterConfig.fromEnv())} works
 * when the environment is configured.
 */
public final class BeaterConfig {

    public String baseUrl;
    public String tenantId;
    public String projectId;
    public String environmentId;
    public String apiKey;
    public String serviceName;
    public String releaseId;

    public BeaterConfig() {
        this.baseUrl = "http://127.0.0.1:8080";
        this.tenantId = "demo";
        this.projectId = "demo";
        this.environmentId = "local";
        this.serviceName = "beater-java";
    }

    private static String env(String name, String fallback) {
        String value = System.getenv(name);
        return (value != null && !value.isEmpty()) ? value : fallback;
    }

    /** Resolve config from {@code BEATER_*} env vars with sensible local defaults. */
    public static BeaterConfig fromEnv() {
        BeaterConfig c = new BeaterConfig();
        c.baseUrl = env("BEATER_BASE_URL", "http://127.0.0.1:8080");
        c.tenantId = env("BEATER_TENANT_ID", "demo");
        c.projectId = env("BEATER_PROJECT_ID", "demo");
        c.environmentId = env("BEATER_ENVIRONMENT_ID", "local");
        c.apiKey = env("BEATER_API_KEY", null);
        c.serviceName = env("BEATER_SERVICE_NAME", "beater-java");
        c.releaseId = env("BEATER_RELEASE_ID", null);
        return c;
    }

    /** The OTLP/HTTP traces endpoint, with tenant/project/environment in the path. */
    public String otlpHttpTracesUrl() {
        String base = baseUrl;
        while (base.endsWith("/")) {
            base = base.substring(0, base.length() - 1);
        }
        return base + "/v1/otlp/" + tenantId + "/" + projectId + "/" + environmentId + "/v1/traces";
    }
}
