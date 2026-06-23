import { isBrowserClickProof, type BrowserClickProof } from "./gate2-click-proof";

export const GATE2_TRACE_ID = /^[0-9a-f]{32}$/;
export const GATE2_SPAN_ID = /^[0-9a-f]{16}$/;

export type Gate2ConfirmationRequest = {
  traceId: string;
  spanId: string;
  click: BrowserClickProof;
};

export function isGate2TraceId(value: unknown): value is string {
  return typeof value === "string" && GATE2_TRACE_ID.test(value);
}

export function isGate2SpanId(value: unknown): value is string {
  return typeof value === "string" && GATE2_SPAN_ID.test(value);
}

export function isGate2ConfirmationRequest(
  value: unknown
): value is Gate2ConfirmationRequest {
  if (!value || typeof value !== "object" || Array.isArray(value)) return false;
  const record = value as Record<string, unknown>;
  return (
    isGate2TraceId(record.traceId) &&
    isGate2SpanId(record.spanId) &&
    isBrowserClickProof(record.click)
  );
}
