import { NextResponse, type NextRequest } from "next/server";

import {
  GATE2_SESSION_COOKIE,
  GATE2_SESSION_MAX_AGE_SECONDS,
  isGate2SessionId
} from "./lib/gate2-session";

export function proxy(request: NextRequest) {
  const response = NextResponse.next();
  const existing = request.cookies.get(GATE2_SESSION_COOKIE)?.value;
  if (!isGate2SessionId(existing)) {
    response.cookies.set({
      name: GATE2_SESSION_COOKIE,
      value: crypto.randomUUID().replaceAll("-", ""),
      httpOnly: true,
      sameSite: "lax",
      path: "/",
      maxAge: GATE2_SESSION_MAX_AGE_SECONDS
    });
  }
  return response;
}

export const config = {
  matcher: ["/", "/api/gate2/:path*"]
};
