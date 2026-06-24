/** Configuration resolved from explicit options then `BEATER_*` env vars. */

export interface BeaterOptions {
  baseUrl?: string;
  tenantId?: string;
  projectId?: string;
  environmentId?: string;
  apiKey?: string;
  serviceName?: string;
  releaseId?: string;
}

export interface BeaterConfig {
  baseUrl: string;
  tenantId: string;
  projectId: string;
  environmentId: string;
  apiKey?: string;
  serviceName: string;
  releaseId?: string;
}

function env(name: string): string | undefined {
  return typeof process !== "undefined" && process.env ? process.env[name] : undefined;
}

export function resolveConfig(options: BeaterOptions = {}): BeaterConfig {
  return {
    baseUrl: options.baseUrl ?? env("BEATER_BASE_URL") ?? "http://127.0.0.1:8080",
    tenantId: options.tenantId ?? env("BEATER_TENANT_ID") ?? "demo",
    projectId: options.projectId ?? env("BEATER_PROJECT_ID") ?? "demo",
    environmentId: options.environmentId ?? env("BEATER_ENVIRONMENT_ID") ?? "local",
    apiKey: options.apiKey ?? env("BEATER_API_KEY"),
    serviceName: options.serviceName ?? env("BEATER_SERVICE_NAME") ?? "beater-node",
    releaseId: options.releaseId ?? env("BEATER_RELEASE_ID"),
  };
}

export function otlpHttpTracesUrl(config: BeaterConfig): string {
  const base = config.baseUrl.replace(/\/+$/, "");
  return `${base}/v1/otlp/${config.tenantId}/${config.projectId}/${config.environmentId}/v1/traces`;
}
