"use client";

import { useState } from "react";
import { useRouter } from "next/navigation";

type Mode = "login" | "register";

function humanize(status: number, code: unknown): string {
  if (code === "email_taken") return "That email is already registered — try signing in.";
  if (code === "invalid_credentials") return "Incorrect email or password.";
  if (status === 400) return "Enter a valid email and a password of at least 8 characters.";
  if (status === 502) return "Can't reach the API. Is the backend running?";
  return "Something went wrong. Please try again.";
}

export default function LoginPage() {
  const router = useRouter();
  const [mode, setMode] = useState<Mode>("login");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState<string | null>(null);
  const [busy, setBusy] = useState(false);

  async function submit(event: React.FormEvent) {
    event.preventDefault();
    setBusy(true);
    setError(null);
    try {
      const res = await fetch(`/api/auth/${mode}`, {
        method: "POST",
        headers: { "content-type": "application/json" },
        body: JSON.stringify({ email, password }),
      });
      if (!res.ok) {
        const data = (await res.json().catch(() => ({}))) as { error?: string };
        setError(humanize(res.status, data.error));
        return;
      }
      router.push("/");
      router.refresh();
    } catch {
      setError("Network error — please try again.");
    } finally {
      setBusy(false);
    }
  }

  const isRegister = mode === "register";

  return (
    <main
      style={{
        minHeight: "100vh",
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        padding: "2rem",
      }}
    >
      <form
        onSubmit={submit}
        style={{
          width: "100%",
          maxWidth: 360,
          display: "flex",
          flexDirection: "column",
          gap: "0.75rem",
          border: "1px solid #2a2a2a",
          borderRadius: 12,
          padding: "1.5rem",
        }}
      >
        <h1 style={{ margin: 0, fontSize: "1.25rem" }}>
          {isRegister ? "Create your Beater account" : "Sign in to Beater"}
        </h1>
        <label style={{ display: "flex", flexDirection: "column", gap: 4 }}>
          <span style={{ fontSize: "0.8rem", opacity: 0.8 }}>Email</span>
          <input
            type="email"
            name="email"
            autoComplete="email"
            required
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            style={{ padding: "0.5rem", borderRadius: 6, border: "1px solid #333" }}
          />
        </label>
        <label style={{ display: "flex", flexDirection: "column", gap: 4 }}>
          <span style={{ fontSize: "0.8rem", opacity: 0.8 }}>Password</span>
          <input
            type="password"
            name="password"
            autoComplete={isRegister ? "new-password" : "current-password"}
            required
            minLength={8}
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            style={{ padding: "0.5rem", borderRadius: 6, border: "1px solid #333" }}
          />
        </label>
        {error ? (
          <p role="alert" style={{ color: "#f87171", fontSize: "0.85rem", margin: 0 }}>
            {error}
          </p>
        ) : null}
        <button
          type="submit"
          disabled={busy}
          style={{
            padding: "0.6rem",
            borderRadius: 6,
            border: "none",
            background: "#3b82f6",
            color: "white",
            cursor: busy ? "default" : "pointer",
            opacity: busy ? 0.7 : 1,
          }}
        >
          {busy ? "Working…" : isRegister ? "Create account" : "Sign in"}
        </button>
        <button
          type="button"
          onClick={() => {
            setMode(isRegister ? "login" : "register");
            setError(null);
          }}
          style={{
            background: "none",
            border: "none",
            color: "#93c5fd",
            cursor: "pointer",
            fontSize: "0.85rem",
          }}
        >
          {isRegister ? "Already have an account? Sign in" : "Need an account? Create one"}
        </button>
      </form>
    </main>
  );
}
