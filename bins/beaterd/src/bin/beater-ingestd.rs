//! Optional thin "ingest" role binary (R1.2).
//!
//! Beater ships as a single all-in-one `beaterd` by default. The future service
//! split is *logical, not operational*: this thin bin exists only behind the
//! `thin-bins` cargo feature so an operator who wants to scale the ingest path
//! independently can, but nobody is forced into a multi-service deployment.
//!
//! It is intentionally a stub: it documents the role and points back at the
//! all-in-one binary rather than duplicating the wiring, so the supported path
//! stays the one tested by `bins/beaterd/tests/*`.
//!
//! ```sh
//! cargo run -p beaterd --features thin-bins --bin beater-ingestd
//! ```

fn main() {
    eprintln!(
        "beater-ingestd is an optional thin ingest-role binary (R1.2). The \
         supported, fully tested deployment is the all-in-one `beaterd`. Run \
         `beaterd` for the single-process server; this thin role is opt-in for \
         operators who explicitly want to scale ingest separately."
    );
}
