import { NextRequest, NextResponse } from "next/server";

import { dashboardApiBaseUrl } from "../../../../lib/api";

export const dynamic = "force-dynamic";

const ALLOWED = new Set(["login", "register", "logout"]);

/**
 * Proxy the dashboard's `/api/auth/{login,register,logout}` to the backend's
 * root `/auth/*` endpoints, relaying the `Set-Cookie` so the `beater_session`
 * cookie is set on the dashboard origin. Keeps the backend URL server-side.
 */
export async function POST(
  req: NextRequest,
  ctx: { params: Promise<{ action: string }> },
): Promise<NextResponse> {
  const { action } = await ctx.params;
  if (!ALLOWED.has(action)) {
    return NextResponse.json({ error: "not_found" }, { status: 404 });
  }
  const cookie = req.headers.get("cookie") ?? "";
  const body = action === "logout" ? "{}" : await req.text();

  let upstream: Response;
  try {
    upstream = await fetch(`${dashboardApiBaseUrl()}/auth/${action}`, {
      method: "POST",
      headers: { "content-type": "application/json", cookie },
      body,
      cache: "no-store",
    });
  } catch {
    return NextResponse.json({ error: "upstream_unreachable" }, { status: 502 });
  }

  const text = await upstream.text();
  const res = new NextResponse(text.length > 0 ? text : null, {
    status: upstream.status,
    headers: {
      "content-type": upstream.headers.get("content-type") ?? "application/json",
    },
  });
  const setCookie = upstream.headers.get("set-cookie");
  if (setCookie) res.headers.set("set-cookie", setCookie);
  return res;
}
