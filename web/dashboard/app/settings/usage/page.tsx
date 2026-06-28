import Link from "next/link";
import { Gauge, Activity, Database, FlaskConical, HardDrive, Layers } from "lucide-react";

import { getSession } from "../../../lib/auth";
import { fetchUsageSummary, humanizeMetric, formatQuantity } from "../../../lib/usage";

export const dynamic = "force-dynamic";

function iconFor(key: string) {
  if (/span/i.test(key)) return Layers;
  if (/trace/i.test(key)) return Activity;
  if (/dataset/i.test(key)) return Database;
  if (/eval|judge|experiment/i.test(key)) return FlaskConical;
  if (/byte|storage|disk/i.test(key)) return HardDrive;
  return Gauge;
}

export default async function UsagePage() {
  const account = await getSession();

  if (!account) {
    return (
      <main className="settings">
        <div className="page-head">
          <div className="page-titles">
            <h1>Usage</h1>
            <p>Volume recorded by your beaterd, by metric.</p>
          </div>
        </div>
        <div className="panel">
          <div className="empty-state">
            <span className="empty-glyph" aria-hidden="true">
              <Gauge />
            </span>
            <strong>Sign in to see usage</strong>
            <p>Usage is scoped to your tenant and project.</p>
            <Link href="/login" className="btn btn-primary" style={{ marginTop: 6 }}>
              Sign in
            </Link>
          </div>
        </div>
      </main>
    );
  }

  const project = "default";
  const { summary, error } = await fetchUsageSummary(account.tenant_id, project);
  const totals = summary ? Object.entries(summary.totals) : [];
  const maxQty = totals.reduce((max, [, t]) => Math.max(max, t.quantity), 0);

  return (
    <main className="settings">
      <div className="page-head">
        <div className="page-titles">
          <h1>Usage</h1>
          <p>
            Volume recorded by your beaterd for the current period. Self-hosted —
            you keep every byte.
          </p>
        </div>
        <div className="page-actions">
          <span className="tag tag-accent mono">project {project}</span>
        </div>
      </div>

      {totals.length === 0 ? (
        <div className="panel">
          <div className="empty-state">
            <span className="empty-glyph" aria-hidden="true">
              <Gauge />
            </span>
            <strong>{error ? "Usage isn't available yet" : "No usage recorded yet"}</strong>
            <p>
              {error
                ? "Couldn't reach the usage endpoint. Start beaterd and send a trace to see numbers here."
                : "Send your first trace and metrics will appear here within seconds."}
            </p>
            <Link href="/docs/quickstarts" className="btn btn-primary" style={{ marginTop: 6 }}>
              View quickstart
            </Link>
          </div>
        </div>
      ) : (
        <div className="stack">
          <div className="statgrid">
            {totals.map(([key, total]) => {
              const Icon = iconFor(key);
              return (
                <div className="stat" key={key}>
                  <span className="stat-label">
                    <Icon aria-hidden="true" /> {humanizeMetric(key)}
                  </span>
                  <span className="stat-value">{formatQuantity(total.quantity, total.unit)}</span>
                  <span className="stat-sub">{total.unit}</span>
                </div>
              );
            })}
          </div>

          <section className="panel">
            <div className="panel-head">
              <div className="panel-titles">
                <h2>By metric</h2>
                <p>Relative volume across recorded usage metrics.</p>
              </div>
            </div>
            <div className="panel-body">
              {totals.map(([key, total]) => {
                const pct = maxQty > 0 ? Math.max(2, Math.round((total.quantity / maxQty) * 100)) : 0;
                return (
                  <div className="meter-row" key={key}>
                    <div className="meter-head">
                      <span className="meter-name">{humanizeMetric(key)}</span>
                      <span className="meter-value">
                        {formatQuantity(total.quantity, total.unit)}{" "}
                        <small>{total.unit}</small>
                      </span>
                    </div>
                    <div
                      className="meter-track"
                      role="img"
                      aria-label={`${humanizeMetric(key)}: ${total.quantity} ${total.unit}`}
                    >
                      <div className="meter-fill" style={{ width: `${pct}%` }} />
                    </div>
                  </div>
                );
              })}
            </div>
            <div className="panel-foot">
              <span>
                Source: <code>GET /v1/usage/{account.tenant_id}/{project}</code>
              </span>
              <Link href="/settings/billing" className="btn-link">
                View billing
              </Link>
            </div>
          </section>
        </div>
      )}
    </main>
  );
}
