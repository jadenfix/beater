"use client";

import { useEffect } from "react";

// Renders the API reference from the single committed OpenAPI snapshot via Scalar.
// The same spec drives the SDKs and MCP tools, so this reference cannot drift.
export default function DocsPage() {
  useEffect(() => {
    const script = document.createElement("script");
    script.id = "api-reference";
    script.setAttribute("data-url", "/api/openapi");
    document.body.appendChild(script);

    const loader = document.createElement("script");
    loader.src = "https://cdn.jsdelivr.net/npm/@scalar/api-reference";
    document.body.appendChild(loader);

    return () => {
      script.remove();
      loader.remove();
    };
  }, []);

  return null;
}
