import { readFile } from "node:fs/promises";
import path from "node:path";

// Serve the committed OpenAPI snapshot (the same file the drift check gates), so
// the rendered docs can never disagree with the generated SDKs / MCP tools.
export async function GET() {
  const specPath = path.join(process.cwd(), "openapi", "beater-read-api.json");
  try {
    const raw = await readFile(specPath, "utf8");
    return new Response(raw, {
      headers: { "content-type": "application/json", "cache-control": "no-store" },
    });
  } catch {
    return new Response(JSON.stringify({ error: "spec not found" }), {
      status: 500,
      headers: { "content-type": "application/json" },
    });
  }
}
