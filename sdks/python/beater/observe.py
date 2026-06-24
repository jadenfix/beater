"""The ``@observe`` decorator and ``span`` context manager.

These are the ergonomic entry points for tracing arbitrary code as Beater spans.
"""

from __future__ import annotations

import functools
import inspect
import itertools
import json
from contextlib import contextmanager
from typing import Any, Callable, Iterator, Optional

from opentelemetry.trace import Status, StatusCode

from .semconv import Attr, SpanKind
from .tracing import get_config, get_tracer

_seq = itertools.count(1)


def _to_value(obj: Any) -> str:
    if isinstance(obj, str):
        return obj
    try:
        return json.dumps(obj, default=str)
    except (TypeError, ValueError):
        return str(obj)


def _apply_common(span, kind: str) -> None:
    span.set_attribute(Attr.SPAN_KIND, kind)
    span.set_attribute(Attr.SEQ, next(_seq))
    config = get_config()
    if config and config.release_id:
        span.set_attribute(Attr.RELEASE_ID, config.release_id)


def set_input(value: Any) -> None:
    """Attach an input payload to the current span."""
    from opentelemetry import trace as _trace

    span = _trace.get_current_span()
    if span is not None:
        span.set_attribute(Attr.INPUT_VALUE, _to_value(value))


def set_output(value: Any) -> None:
    """Attach an output payload to the current span."""
    from opentelemetry import trace as _trace

    span = _trace.get_current_span()
    if span is not None:
        span.set_attribute(Attr.OUTPUT_VALUE, _to_value(value))


@contextmanager
def span(
    name: str,
    *,
    kind: str = SpanKind.AGENT_STEP,
    input: Any = None,
    attributes: Optional[dict] = None,
) -> Iterator[Any]:
    """Open a Beater span as a context manager.

    >>> with beater.span("retrieve", kind=SpanKind.RETRIEVAL_QUERY) as s:
    ...     ...
    """
    tracer = get_tracer()
    with tracer.start_as_current_span(name) as current:
        _apply_common(current, kind)
        if input is not None:
            current.set_attribute(Attr.INPUT_VALUE, _to_value(input))
        for key, val in (attributes or {}).items():
            current.set_attribute(key, val)
        try:
            yield current
            current.set_status(Status(StatusCode.OK))
        except Exception as exc:  # noqa: BLE001 - re-raised below
            current.set_status(Status(StatusCode.ERROR, str(exc)))
            current.record_exception(exc)
            raise


def observe(
    _func: Optional[Callable] = None,
    *,
    name: Optional[str] = None,
    kind: str = SpanKind.AGENT_STEP,
    capture_input: bool = True,
    capture_output: bool = True,
) -> Callable:
    """Decorate a function so each call becomes a Beater span.

    Works on sync and async functions. Captures arguments and the return value
    as ``input.value`` / ``output.value`` unless disabled.

    >>> @beater.observe(kind=SpanKind.LLM_CALL)
    ... def call_model(prompt): ...
    """

    def decorate(func: Callable) -> Callable:
        span_name = name or func.__qualname__

        def _record_input(current, args, kwargs):
            if capture_input:
                payload = {"args": args, "kwargs": kwargs} if (args or kwargs) else None
                if payload is not None:
                    current.set_attribute(Attr.INPUT_VALUE, _to_value(payload))

        if inspect.iscoroutinefunction(func):

            @functools.wraps(func)
            async def async_wrapper(*args, **kwargs):
                tracer = get_tracer()
                with tracer.start_as_current_span(span_name) as current:
                    _apply_common(current, kind)
                    _record_input(current, args, kwargs)
                    try:
                        result = await func(*args, **kwargs)
                        if capture_output and result is not None:
                            current.set_attribute(Attr.OUTPUT_VALUE, _to_value(result))
                        current.set_status(Status(StatusCode.OK))
                        return result
                    except Exception as exc:  # noqa: BLE001
                        current.set_status(Status(StatusCode.ERROR, str(exc)))
                        current.record_exception(exc)
                        raise

            return async_wrapper

        @functools.wraps(func)
        def sync_wrapper(*args, **kwargs):
            tracer = get_tracer()
            with tracer.start_as_current_span(span_name) as current:
                _apply_common(current, kind)
                _record_input(current, args, kwargs)
                try:
                    result = func(*args, **kwargs)
                    if capture_output and result is not None:
                        current.set_attribute(Attr.OUTPUT_VALUE, _to_value(result))
                    current.set_status(Status(StatusCode.OK))
                    return result
                except Exception as exc:  # noqa: BLE001
                    current.set_status(Status(StatusCode.ERROR, str(exc)))
                    current.record_exception(exc)
                    raise

        return sync_wrapper

    if _func is not None:
        return decorate(_func)
    return decorate
