import { cookies } from "next/headers";

import { dashboardApiBaseUrl } from "./api";

/** Session cookie set by the backend `/auth/*` endpoints (mirror of the Rust
 * `beater_oauth_server::SESSION_COOKIE`). */
export const SESSION_COOKIE = "beater_session";

export type Account = {
  user_id: string;
  email: string;
  /** The user's personal tenant (== their org id). */
  tenant_id: string;
};

/**
 * Resolve the logged-in account from the session cookie by asking the backend
 * `/auth/me`. Server-side only. Returns `null` when there is no valid session.
 */
export async function getSession(): Promise<Account | null> {
  const store = await cookies();
  const token = store.get(SESSION_COOKIE)?.value;
  if (!token) return null;
  try {
    const res = await fetch(`${dashboardApiBaseUrl()}/auth/me`, {
      headers: { cookie: `${SESSION_COOKIE}=${token}` },
      cache: "no-store",
    });
    if (!res.ok) return null;
    return (await res.json()) as Account;
  } catch {
    return null;
  }
}
