"""Drop-in Anthropic instrumentation: ``client = wrap_anthropic(Anthropic())``."""

from __future__ import annotations

from typing import Any

from opentelemetry.trace import Status, StatusCode

from ..observe import _apply_common, _to_value
from ..semconv import Attr, SpanKind
from ..tracing import get_tracer


def _record_usage(span, response: Any) -> None:
    usage = getattr(response, "usage", None)
    if usage is None:
        return
    input_tokens = getattr(usage, "input_tokens", None)
    output_tokens = getattr(usage, "output_tokens", None)
    cache_read = getattr(usage, "cache_read_input_tokens", None)
    if input_tokens is not None:
        span.set_attribute(Attr.LLM_TOKEN_PROMPT, int(input_tokens))
    if output_tokens is not None:
        span.set_attribute(Attr.LLM_TOKEN_COMPLETION, int(output_tokens))
    if cache_read is not None:
        span.set_attribute(Attr.LLM_TOKEN_CACHE_READ, int(cache_read))


def _output_text(response: Any) -> str:
    try:
        blocks = getattr(response, "content", None) or []
        parts = [getattr(block, "text", "") for block in blocks if getattr(block, "text", None)]
        return "".join(parts)
    except (AttributeError, TypeError):
        return ""


def wrap_anthropic(client: Any) -> Any:
    """Instrument an Anthropic client in place and return it.

    Wraps ``client.messages.create`` so each call emits an ``llm.call`` span with
    model and token counts. Safe to call once per client.
    """

    if getattr(client, "_beater_wrapped", False):
        return client

    messages_api = client.messages
    original = messages_api.create

    def create(*args: Any, **kwargs: Any) -> Any:
        tracer = get_tracer()
        model = kwargs.get("model", "unknown")
        with tracer.start_as_current_span("anthropic.messages.create") as span:
            _apply_common(span, SpanKind.LLM_CALL)
            span.set_attribute(Attr.LLM_PROVIDER, "anthropic")
            span.set_attribute(Attr.LLM_MODEL_NAME, str(model))
            messages = kwargs.get("messages")
            if messages is not None:
                span.set_attribute(Attr.INPUT_VALUE, _to_value(messages))
            try:
                response = original(*args, **kwargs)
                response_model = getattr(response, "model", None)
                if response_model:
                    span.set_attribute(Attr.LLM_MODEL_NAME, str(response_model))
                _record_usage(span, response)
                span.set_attribute(Attr.OUTPUT_VALUE, _output_text(response))
                span.set_status(Status(StatusCode.OK))
                return response
            except Exception as exc:  # noqa: BLE001
                span.set_status(Status(StatusCode.ERROR, str(exc)))
                span.record_exception(exc)
                raise

    messages_api.create = create  # type: ignore[method-assign]
    client._beater_wrapped = True
    return client
