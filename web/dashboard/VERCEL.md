# Vercel deployment notes (dashboard)

This directory's [`vercel.json`](vercel.json) deploys the **stateless Next.js
dashboard** to Vercel. This note covers requirement **R1.4** (Vercel is used
only for stateless / control-plane work) and the status of Rust function config.

## What runs on Vercel

- The Next.js UI (`framework: nextjs`, `buildCommand: npm run build`). It is
  stateless: it renders the committed OpenAPI spec and proxies read/control
  requests to a `beaterd` it points at via `BEATER_API_BASE_URL` /
  `NEXT_PUBLIC_BEATER_API_BASE_URL`.

## What does NOT run on Vercel

- Stateful workers (ingest drain, trace-write/queue workers, search indexing,
  archive) run inside `beaterd`, never as Vercel functions. The all-in-one
  `beaterd` is the only mandatory deployment (R1.2).

## Rust function config — deferral note

The evidence for R1.4 calls for "Rust function config still required for hosted
control plane." Today the dashboard is a pure Next.js app and ships **no Vercel
Rust serverless functions**, so there is intentionally no `functions` /
`vercel-rust` runtime block in `vercel.json` yet.

This is a deliberate deferral: a Rust control-plane function (e.g. via the
`vercel-rust` runtime, `api/*.rs` with `runtime: vercel-rust`) will be added to
`vercel.json` only when the **hosted** control plane introduces a Rust serverless
endpoint that must run on Vercel. Until then, control-plane logic lives in
`beaterd`, keeping the Vercel deployment strictly stateless and avoiding an empty
or speculative function config that could not be deployed or tested.

When that endpoint lands, the config block will look like:

```jsonc
{
  "framework": "nextjs",
  "buildCommand": "npm run build",
  "functions": {
    "api/*.rs": { "runtime": "vercel-rust@4" }
  }
}
```

Tracked as a follow-up so the hosted control plane (not the self-host path) owns
the Rust-on-Vercel surface.
