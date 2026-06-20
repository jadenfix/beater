export type Page<T> = {
  items: T[];
  next_cursor: string | null;
};

export type RunSummary = {
  tenant_id: string;
  trace_id: string;
  first_span_name: string;
  span_count: number;
  status: "ok" | "error" | "unset";
  started_at: string;
  ended_at: string | null;
};

export type Money = {
  currency: string;
  micros: number;
};

export type TokenCounts = {
  input: number;
  output: number;
  cache_read: number;
  cache_write: number;
};

export type ArtifactRef = {
  artifact_id: string;
  uri: string;
  sha256: string;
  size_bytes: number;
  mime_type: string;
  redaction_class: "public" | "internal" | "sensitive" | "secret";
};

export type CanonicalSpan = {
  schema_version: number;
  normalizer_version: string;
  tenant_id: string;
  project_id: string;
  environment_id: string;
  trace_id: string;
  span_id: string;
  parent_span_id: string | null;
  seq: number;
  kind: string;
  name: string;
  status: "ok" | "error" | "unset";
  start_time: string;
  end_time: string | null;
  model: { provider: string; name: string } | null;
  cost: Money | null;
  tokens: TokenCounts | null;
  input_ref: ArtifactRef | null;
  output_ref: ArtifactRef | null;
  attributes: Record<string, unknown>;
  unmapped_attrs: unknown;
  raw_ref: ArtifactRef;
};

export type TraceView = {
  tenant_id: string;
  trace_id: string;
  spans: CanonicalSpan[];
};

export type SpanIoValue =
  | { kind: "inline"; value: unknown }
  | { kind: "artifact"; artifact_ref: ArtifactRef }
  | { kind: "redacted"; reason: string }
  | { kind: "missing" };

export type SpanIoResponse = {
  tenant_id: string;
  trace_id: string;
  span_id: string;
  input: SpanIoValue;
  output: SpanIoValue;
};

export type DashboardQuery = {
  tenantId: string;
  projectId?: string;
  environmentId?: string;
  traceId?: string;
  selectedSpanId?: string;
};

export type DashboardData = {
  apiBaseUrl: string;
  query: DashboardQuery;
  runs: Page<RunSummary>;
  trace: TraceView | null;
  selectedSpan: CanonicalSpan | null;
  selectedIo: SpanIoResponse | null;
  error: string | null;
};

export function dashboardApiBaseUrl(): string {
  return (
    process.env.BEATER_API_BASE_URL ??
    process.env.NEXT_PUBLIC_BEATER_API_BASE_URL ??
    "http://127.0.0.1:8080"
  ).replace(/\/$/, "");
}

export function dashboardApiHeaders(query: DashboardQuery): HeadersInit {
  const headers: Record<string, string> = {};
  const bearerToken = process.env.BEATER_API_TOKEN ?? process.env.BEATER_API_BEARER_TOKEN;
  const apiKey = process.env.BEATER_API_KEY;
  if (bearerToken) {
    headers.authorization = bearerToken.startsWith("Bearer ")
      ? bearerToken
      : `Bearer ${bearerToken}`;
  } else if (apiKey) {
    headers["x-beater-api-key"] = apiKey;
  }
  if (query.projectId) headers["x-beater-project-id"] = query.projectId;
  if (query.environmentId) headers["x-beater-environment-id"] = query.environmentId;
  return headers;
}

export function searchParamsForTraceList(query: DashboardQuery): URLSearchParams {
  const params = new URLSearchParams();
  if (query.projectId) params.set("project_id", query.projectId);
  if (query.environmentId) params.set("environment_id", query.environmentId);
  if (query.traceId) params.set("trace_id", query.traceId);
  params.set("limit", "50");
  return params;
}

export function traceListPath(query: DashboardQuery): string {
  const params = searchParamsForTraceList(query);
  const suffix = params.toString();
  return `/v1/traces/${encodeURIComponent(query.tenantId)}${suffix ? `?${suffix}` : ""}`;
}

export function tracePath(query: DashboardQuery, traceId: string): string {
  return `/v1/traces/${encodeURIComponent(query.tenantId)}/${encodeURIComponent(traceId)}`;
}

export function spanIoPath(query: DashboardQuery, traceId: string, spanId: string): string {
  return `/v1/spans/${encodeURIComponent(query.tenantId)}/${encodeURIComponent(
    traceId
  )}/${encodeURIComponent(spanId)}/io`;
}

export async function loadDashboardData(query: DashboardQuery): Promise<DashboardData> {
  const apiBaseUrl = dashboardApiBaseUrl();
  const headers = dashboardApiHeaders(query);
  try {
    const runs = await fetchJson<Page<RunSummary>>(`${apiBaseUrl}${traceListPath(query)}`, headers);
    const activeTraceId = query.traceId || runs.items[0]?.trace_id;
    const trace = activeTraceId
      ? await fetchJson<TraceView>(`${apiBaseUrl}${tracePath(query, activeTraceId)}`, headers)
      : null;
    const selectedSpan =
      trace?.spans.find((span) => span.span_id === query.selectedSpanId) ??
      trace?.spans[0] ??
      null;
    const selectedIo =
      trace && selectedSpan
        ? await fetchJson<SpanIoResponse>(
            `${apiBaseUrl}${spanIoPath(query, trace.trace_id, selectedSpan.span_id)}`,
            headers
          )
        : null;
    return {
      apiBaseUrl,
      query: { ...query, traceId: activeTraceId },
      runs,
      trace,
      selectedSpan,
      selectedIo,
      error: null
    };
  } catch (error) {
    return {
      apiBaseUrl,
      query,
      runs: { items: [], next_cursor: null },
      trace: null,
      selectedSpan: null,
      selectedIo: null,
      error: error instanceof Error ? error.message : String(error)
    };
  }
}

async function fetchJson<T>(url: string, headers: HeadersInit): Promise<T> {
  const response = await fetch(url, { cache: "no-store", headers });
  if (!response.ok) {
    const text = await response.text();
    throw new Error(`${response.status} ${response.statusText}: ${text.slice(0, 240)}`);
  }
  return (await response.json()) as T;
}

export function durationMs(start: string, end: string | null): number | null {
  if (!end) return null;
  return Math.max(0, new Date(end).getTime() - new Date(start).getTime());
}

export function formatDuration(start: string, end: string | null): string {
  const ms = durationMs(start, end);
  if (ms === null) return "open";
  if (ms < 1000) return `${ms} ms`;
  return `${(ms / 1000).toFixed(2)} s`;
}

export function formatCost(cost: Money | null): string {
  if (!cost) return "none";
  return `${cost.currency} ${(cost.micros / 1_000_000).toFixed(6)}`;
}

export function spanDepth(span: CanonicalSpan, spans: CanonicalSpan[]): number {
  let depth = 0;
  let parent = span.parent_span_id;
  const byId = new Map(spans.map((candidate) => [candidate.span_id, candidate]));
  while (parent && byId.has(parent) && depth < 12) {
    depth += 1;
    parent = byId.get(parent)?.parent_span_id ?? null;
  }
  return depth;
}

export function statusLabel(status: string): string {
  if (status === "ok") return "OK";
  if (status === "error") return "Error";
  return "Unset";
}
