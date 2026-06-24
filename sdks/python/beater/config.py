"""Configuration for the Beater SDK, resolved from explicit args then env vars."""

from __future__ import annotations

import os
from dataclasses import dataclass
from typing import Optional


def _env(*names: str, default: Optional[str] = None) -> Optional[str]:
    for name in names:
        value = os.getenv(name)
        if value:
            return value
    return default


@dataclass
class BeaterConfig:
    """Connection + scope settings shared by every wrapper.

    Resolution order for each field: explicit argument, then environment
    variable, then a sensible local default.
    """

    base_url: str
    tenant_id: str
    project_id: str
    environment_id: str
    api_key: Optional[str] = None
    protocol: str = "http"  # "http" (OTLP/HTTP to base_url) or "grpc"
    grpc_endpoint: Optional[str] = None
    service_name: str = "beater-python"
    release_id: Optional[str] = None

    @classmethod
    def resolve(
        cls,
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
    ) -> "BeaterConfig":
        return cls(
            base_url=base_url or _env("BEATER_BASE_URL", default="http://127.0.0.1:8080"),
            tenant_id=tenant_id or _env("BEATER_TENANT_ID", default="demo"),
            project_id=project_id or _env("BEATER_PROJECT_ID", default="demo"),
            environment_id=environment_id or _env("BEATER_ENVIRONMENT_ID", default="local"),
            api_key=api_key or _env("BEATER_API_KEY"),
            protocol=(protocol or _env("BEATER_PROTOCOL", default="http")).lower(),
            grpc_endpoint=grpc_endpoint
            or _env("BEATER_GRPC_ENDPOINT", "OTEL_EXPORTER_OTLP_ENDPOINT", default="http://127.0.0.1:4317"),
            service_name=service_name or _env("BEATER_SERVICE_NAME", default="beater-python"),
            release_id=release_id or _env("BEATER_RELEASE_ID"),
        )

    def otlp_http_traces_url(self) -> str:
        base = self.base_url.rstrip("/")
        return f"{base}/v1/otlp/{self.tenant_id}/{self.project_id}/{self.environment_id}/v1/traces"
