import { NextResponse, type NextRequest } from "next/server";

export const GATE2_SESSION_COOKIE = "beater_gate2_session";

export function proxy(request: NextRequest) {
  const response = NextResponse.next();
  const existing = request.cookies.get(GATE2_SESSION_COOKIE)?.value;
  if (!existing || !/^[0-9a-f]{32}$/.test(existing)) {
    response.cookies.set({
      name: GATE2_SESSION_COOKIE,
      value: crypto.randomUUID().replaceAll("-", ""),
      httpOnly: true,
      sameSite: "lax",
      path: "/",
      maxAge: 60 * 60
    });
  }
  return response;
}

export const config = {
  matcher: ["/", "/api/gate2/:path*"]
};
