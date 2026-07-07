"use client";

import { useEffect, useMemo, useState } from "react";
import {
  Bot,
  Braces,
  CheckCircle2,
  KeyRound,
  Link2,
  LockKeyhole,
  MonitorCog,
  ShieldCheck,
  TerminalSquare,
} from "lucide-react";

import { CopyButton, CopyField } from "../../components/CopyButton";

type ClientTarget = {
  id: string;
  name: string;
  icon: typeof Bot;
  note: string;
};

const CLIENTS: ClientTarget[] = [
  {
    id: "claude",
    name: "Claude / Claude Code",
    icon: Bot,
    note: "Use the remote MCP server URL. OAuth starts automatically when the client connects.",
  },
  {
    id: "cursor",
    name: "Cursor",
    icon: MonitorCog,
    note: "Add Beater as a remote HTTP MCP server. Cursor should discover OAuth from the endpoint.",
  },
  {
    id: "chatgpt",
    name: "ChatGPT",
    icon: Braces,
    note: "Use the hosted MCP URL in connector setup. Tool scopes are advertised per operation.",
  },
  {
    id: "openai",
    name: "OpenAI API / Agents",
    icon: TerminalSquare,
    note: "Attach Beater as a hosted MCP tool with server_url and per-call approvals.",
  },
];

const PERMISSION_SETS = [
  {
    name: "Trace reader",
    scopes: ["mcp:invoke", "trace:read"],
    use: "Inspect traces, spans, and span I/O.",
  },
  {
    name: "Reviewer",
    scopes: ["mcp:invoke", "trace:read", "dataset:write"],
    use: "Promote failures to datasets and submit review annotations.",
  },
  {
    name: "Evaluator",
    scopes: ["mcp:invoke", "trace:read", "dataset:write", "eval:run"],
    use: "Run evals and calibration flows from an agent client.",
  },
  {
    name: "Admin",
    scopes: ["mcp:invoke", "admin"],
    use: "Manage provider secrets, usage, queues, and administrative MCP tools.",
  },
];

function currentOrigin() {
  if (typeof window === "undefined") return "https://app.palette.dev";
  return window.location.origin;
}

function claudeConfig(mcpUrl: string) {
  return JSON.stringify(
    {
      mcpServers: {
        beater: {
          type: "http",
          url: mcpUrl,
        },
      },
    },
    null,
    2,
  );
}

function cursorConfig(mcpUrl: string) {
  return JSON.stringify(
    {
      mcpServers: {
        beater: {
          url: mcpUrl,
          transport: "http",
        },
      },
    },
    null,
    2,
  );
}

function openAiToolConfig(mcpUrl: string) {
  return JSON.stringify(
    {
      type: "mcp",
      server_label: "beater",
      server_url: mcpUrl,
      require_approval: "always",
    },
    null,
    2,
  );
}

function apiKeyFallback(origin: string) {
  return [
    `export BEATER_API_BASE_URL="${origin}"`,
    `export BEATER_API_KEY="bt_..."`,
    `export BEATER_TENANT="your-tenant-id"`,
    `export BEATER_PROJECT="default"`,
    `export BEATER_ENVIRONMENT="default"`,
    ``,
    `curl -X POST "$BEATER_API_BASE_URL/mcp" \\`,
    `  -H "content-type: application/json" \\`,
    `  -H "x-beater-api-key: $BEATER_API_KEY" \\`,
    `  -H "x-beater-project-id: $BEATER_PROJECT" \\`,
    `  -H "x-beater-environment-id: $BEATER_ENVIRONMENT" \\`,
    `  --data "{\\"jsonrpc\\":\\"2.0\\",\\"id\\":1,\\"method\\":\\"tools/call\\",\\"params\\":{\\"name\\":\\"listTraces\\",\\"arguments\\":{\\"tenant_id\\":\\"$BEATER_TENANT\\"}}}"`,
  ].join("\n");
}

export function ConnectClient({ signedIn }: { signedIn: boolean }) {
  const [origin, setOrigin] = useState("https://app.palette.dev");

  useEffect(() => {
    setOrigin(currentOrigin());
  }, []);

  const mcpUrl = `${origin}/mcp`;
  const protectedResourceUrl = `${origin}/.well-known/oauth-protected-resource`;
  const authServerUrl = `${origin}/.well-known/oauth-authorization-server`;
  const configs = useMemo(
    () => ({
      claude: claudeConfig(mcpUrl),
      cursor: cursorConfig(mcpUrl),
      openai: openAiToolConfig(mcpUrl),
      chatgpt: mcpUrl,
      fallback: apiKeyFallback(origin),
    }),
    [mcpUrl, origin],
  );

  return (
    <div className="connect-grid">
      <section className="panel connect-primary" aria-labelledby="connect-title">
        <div className="panel-head">
          <div className="panel-titles">
            <h2 id="connect-title">Hosted MCP endpoint</h2>
            <p>OAuth is the default path. API keys remain available when a client cannot launch OAuth.</p>
          </div>
          <span className="tag tag-success">
            <CheckCircle2 aria-hidden="true" width={13} height={13} /> OAuth ready
          </span>
        </div>
        <div className="panel-body">
          <div className="field">
            <span className="field-label">Remote MCP URL</span>
            <CopyField value={mcpUrl} />
          </div>
          <div className="connect-endpoints" aria-label="OAuth discovery endpoints">
            <div>
              <span>Protected resource</span>
              <code>{protectedResourceUrl}</code>
            </div>
            <div>
              <span>Authorization server</span>
              <code>{authServerUrl}</code>
            </div>
          </div>
          <div className="alert alert-info">
            <LockKeyhole aria-hidden="true" />
            <span>
              Clients discover login from <code>/mcp</code>, request scoped consent, and send a bearer
              token on protected tool calls.
            </span>
          </div>
        </div>
      </section>

      <section className="panel" aria-labelledby="client-configs-title">
        <div className="panel-head">
          <div className="panel-titles">
            <h2 id="client-configs-title">Client configs</h2>
            <p>Use the hosted URL directly; the endpoint advertises OAuth and per-tool scopes.</p>
          </div>
        </div>
        <div className="panel-body connect-clients">
          {CLIENTS.map(({ id, name, icon: Icon, note }) => {
            const value =
              id === "cursor"
                ? configs.cursor
                : id === "chatgpt"
                  ? configs.chatgpt
                  : id === "openai"
                    ? configs.openai
                    : configs.claude;
            return (
              <article className="connect-client" key={id}>
                <div className="connect-client-head">
                  <span className="connect-client-icon" aria-hidden="true">
                    <Icon />
                  </span>
                  <div>
                    <h3>{name}</h3>
                    <p>{note}</p>
                  </div>
                </div>
                {id === "chatgpt" ? (
                  <CopyField value={value} />
                ) : (
                  <pre className="codeblock">{value}</pre>
                )}
                <CopyButton value={value} label="Copy config" className="btn btn-sm" />
              </article>
            );
          })}
          <div className="alert alert-warn">
            <TerminalSquare aria-hidden="true" />
            <span>
              Codex compatibility depends on the surface you use: hosted OpenAI model calls use the
              MCP tool object above; local clients that cannot run remote HTTP OAuth should use the
              scoped API-key fallback.
            </span>
          </div>
        </div>
      </section>

      <section className="panel" aria-labelledby="permissions-title">
        <div className="panel-head">
          <div className="panel-titles">
            <h2 id="permissions-title">Delegated permissions</h2>
            <p>Start narrow. The client asks for scopes, and Beater enforces them on every MCP call.</p>
          </div>
          <span className="tag tag-accent">
            <ShieldCheck aria-hidden="true" width={13} height={13} /> Least privilege
          </span>
        </div>
        <div className="panel-body permission-list">
          {PERMISSION_SETS.map((preset) => (
            <article className="permission-row" key={preset.name}>
              <div>
                <h3>{preset.name}</h3>
                <p>{preset.use}</p>
              </div>
              <div className="permission-scopes" aria-label={`${preset.name} scopes`}>
                {preset.scopes.map((scope) => (
                  <code key={scope}>{scope}</code>
                ))}
              </div>
            </article>
          ))}
        </div>
      </section>

      <section className="panel" aria-labelledby="fallback-title">
        <div className="panel-head">
          <div className="panel-titles">
            <h2 id="fallback-title">API-key fallback</h2>
            <p>Use this only for clients or automation that cannot complete OAuth.</p>
          </div>
          <span className="tag">
            <KeyRound aria-hidden="true" width={13} height={13} /> Scoped key
          </span>
        </div>
        <div className="panel-body">
          {signedIn ? (
            <a className="btn btn-primary" href="/settings/api-keys">
              <KeyRound aria-hidden="true" />
              Create scoped key
            </a>
          ) : (
            <a className="btn btn-primary" href="/login?return_to=/settings/api-keys">
              <KeyRound aria-hidden="true" />
              Sign in for keys
            </a>
          )}
          <pre className="codeblock">{configs.fallback}</pre>
        </div>
        <div className="panel-foot">
          <span>Fallback calls must include project and environment headers.</span>
          <CopyButton value={configs.fallback} label="Copy fallback" className="btn btn-sm" />
        </div>
      </section>

      <section className="connect-checklist" aria-label="Connection checks">
        <div>
          <Link2 aria-hidden="true" />
          <span>/mcp returns an OAuth challenge before protected calls run.</span>
        </div>
        <div>
          <LockKeyhole aria-hidden="true" />
          <span>Bearer tokens bind tenant, project, environment, and scopes.</span>
        </div>
        <div>
          <TerminalSquare aria-hidden="true" />
          <span>API-key fallback is scoped and explicit when OAuth is unavailable.</span>
        </div>
      </section>
    </div>
  );
}
