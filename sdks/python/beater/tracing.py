"""Tracer setup: configure an OpenTelemetry pipeline that exports to Beater.

``init()`` is the one call a user makes. After it, ``@observe`` and the provider
wrappers emit spans that land in the Beater dashboard waterfall.
"""

from __future__ import annotations

import threading
from typing import Optional

from opentelemetry import trace
from opentelemetry.sdk.resources import Resource
from opentelemetry.sdk.trace import TracerProvider
from opentelemetry.sdk.trace.export import BatchSpanProcessor

from .config import BeaterConfig
from .semconv import HEADER_ENVIRONMENT, HEADER_PROJECT, HEADER_TENANT

_TRACER_NAME = "beater.sdk"
_lock = threading.Lock()
_config: Optional[BeaterConfig] = None
_provider: Optional[TracerProvider] = None


def _build_exporter(config: BeaterConfig):
    auth_headers = {}
    if config.api_key:
        auth_headers["authorization"] = f"Bearer {config.api_key}"

    if config.protocol == "grpc":
        from opentelemetry.exporter.otlp.proto.grpc.trace_exporter import OTLPSpanExporter

        headers = {
            HEADER_TENANT: config.tenant_id,
            HEADER_PROJECT: config.project_id,
            HEADER_ENVIRONMENT: config.environment_id,
            **auth_headers,
        }
        insecure = config.grpc_endpoint is not None and config.grpc_endpoint.startswith("http://")
        return OTLPSpanExporter(
            endpoint=config.grpc_endpoint,
            insecure=insecure,
            headers=tuple(headers.items()),
        )

    # Default: OTLP/HTTP. Tenant/project/environment travel in the URL path.
    from opentelemetry.exporter.otlp.proto.http.trace_exporter import OTLPSpanExporter

    return OTLPSpanExporter(endpoint=config.otlp_http_traces_url(), headers=auth_headers or None)


def init(
    *,
    base_url: Optional[str] = None,
    tenant_id: Optional[str] = None,
    project_id: Optional[str] = None,
    environment_id: Optional[str] = None,
    api_key: Optional[str] = None,
    protocol: Optional[str] = None,
    grpc_endpoint: Optional[str] = None,
    service_name: Optional[str] = None,
    release_id: Optional[str] = None,
) -> BeaterConfig:
    """Initialize the Beater tracer. Call once at process start.

    All arguments fall back to ``BEATER_*`` environment variables, so the
    zero-argument ``beater.init()`` works when the env is configured.
    """

    global _config, _provider
    config = BeaterConfig.resolve(
        base_url=base_url,
        tenant_id=tenant_id,
        project_id=project_id,
        environment_id=environment_id,
        api_key=api_key,
        protocol=protocol,
        grpc_endpoint=grpc_endpoint,
        service_name=service_name,
        release_id=release_id,
    )

    with _lock:
        provider = TracerProvider(resource=Resource.create({"service.name": config.service_name}))
        provider.add_span_processor(BatchSpanProcessor(_build_exporter(config)))
        _provider = provider
        _config = config

    trace.set_tracer_provider(provider)
    return config


def get_config() -> Optional[BeaterConfig]:
    return _config


def get_tracer():
    """Return the Beater tracer, auto-initializing from env if ``init`` was skipped."""
    if _config is None:
        init()
    return trace.get_tracer(_TRACER_NAME)


def flush(timeout_millis: int = 30_000) -> bool:
    """Force-flush pending spans. Useful before a short-lived script exits."""
    if _provider is None:
        return True
    return _provider.force_flush(timeout_millis)


def shutdown() -> None:
    if _provider is not None:
        _provider.shutdown()
