"use client";

import { useEffect, useState } from "react";

// MCP tool catalog, derived from the SAME OpenAPI spec the /mcp server uses
// (tool name == operationId), so this page can never drift from the live tools.

type Tool = { name: string; method: string; path: string; tag: string; summary: string };

export default function McpCatalog() {
  const [tools, setTools] = useState<Tool[]>([]);
  const [err, setErr] = useState<string>("");

  useEffect(() => {
    fetch("/api/openapi")
      .then((r) => r.json())
      .then((spec) => {
        const out: Tool[] = [];
        for (const [path, methods] of Object.entries<any>(spec.paths ?? {})) {
          for (const [method, op] of Object.entries<any>(methods)) {
            if (!op?.operationId) continue;
            out.push({
              name: op.operationId,
              method: method.toUpperCase(),
              path,
              tag: (op.tags ?? ["_"])[0],
              summary: op.summary ?? op.description ?? "",
            });
          }
        }
        out.sort((a, b) => a.tag.localeCompare(b.tag) || a.name.localeCompare(b.name));
        setTools(out);
      })
      .catch((e) => setErr(String(e)));
  }, []);

  return (
    <main style={{ maxWidth: 900, margin: "0 auto", padding: 32, fontFamily: "system-ui, sans-serif" }}>
      <h1 style={{ fontSize: 26 }}>MCP tool catalog</h1>
      <p style={{ color: "#57606a" }}>
        Every API operation is exposed as an MCP tool at <code>/mcp</code> on beaterd
        (tool name = operationId). Point any MCP client at it. {tools.length} tools.
      </p>
      {err && <p style={{ color: "#cf222e" }}>Failed to load spec: {err}</p>}
      <table style={{ borderCollapse: "collapse", width: "100%", fontSize: 13 }}>
        <thead>
          <tr style={{ textAlign: "left", borderBottom: "2px solid #d0d7de" }}>
            <th style={{ padding: 6 }}>tool</th>
            <th style={{ padding: 6 }}>tag</th>
            <th style={{ padding: 6 }}>method</th>
            <th style={{ padding: 6 }}>path</th>
          </tr>
        </thead>
        <tbody>
          {tools.map((t) => (
            <tr key={t.name} style={{ borderBottom: "1px solid #eaeef2" }}>
              <td style={{ padding: 6, fontFamily: "monospace" }}>{t.name}</td>
              <td style={{ padding: 6 }}>{t.tag}</td>
              <td style={{ padding: 6 }}>{t.method}</td>
              <td style={{ padding: 6, fontFamily: "monospace", color: "#57606a" }}>{t.path}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </main>
  );
}
