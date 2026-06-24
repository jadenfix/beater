"""Drop-in OpenAI instrumentation: ``client = wrap_openai(OpenAI())``."""

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
    prompt = getattr(usage, "prompt_tokens", None)
    completion = getattr(usage, "completion_tokens", None)
    reasoning = None
    details = getattr(usage, "completion_tokens_details", None)
    if details is not None:
        reasoning = getattr(details, "reasoning_tokens", None)
    if prompt is not None:
        span.set_attribute(Attr.LLM_TOKEN_PROMPT, int(prompt))
    if completion is not None:
        span.set_attribute(Attr.LLM_TOKEN_COMPLETION, int(completion))
    if reasoning is not None:
        span.set_attribute(Attr.LLM_TOKEN_REASONING, int(reasoning))


def _output_text(response: Any) -> str:
    try:
        choice = response.choices[0]
        message = getattr(choice, "message", None)
        if message is not None and getattr(message, "content", None) is not None:
            return message.content
        return getattr(choice, "text", "") or ""
    except (AttributeError, IndexError, TypeError):
        return ""


def wrap_openai(client: Any) -> Any:
    """Instrument an OpenAI client in place and return it.

    Wraps ``client.chat.completions.create`` so each call emits an ``llm.call``
    span with model and token counts. Safe to call once per client.
    """

    if getattr(client, "_beater_wrapped", False):
        return client

    completions = client.chat.completions
    original = completions.create

    def create(*args: Any, **kwargs: Any) -> Any:
        tracer = get_tracer()
        model = kwargs.get("model", "unknown")
        with tracer.start_as_current_span("openai.chat.completions.create") as span:
            _apply_common(span, SpanKind.LLM_CALL)
            span.set_attribute(Attr.LLM_PROVIDER, "openai")
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

    completions.create = create  # type: ignore[method-assign]
    client._beater_wrapped = True
    return client
