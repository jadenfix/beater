export const GATE2_SESSION_COOKIE = "beater_gate2_session";
export const GATE2_SESSION_MAX_AGE_SECONDS = 60 * 60;

const GATE2_SESSION_ID = /^[0-9a-f]{32}$/;

export function isGate2SessionId(value: string | undefined): value is string {
  return typeof value === "string" && GATE2_SESSION_ID.test(value);
}
