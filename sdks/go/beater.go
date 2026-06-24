package beater

import (
	"context"
	"encoding/json"
	"strings"
	"sync/atomic"

	"go.opentelemetry.io/otel"
	"go.opentelemetry.io/otel/attribute"
	"go.opentelemetry.io/otel/codes"
	"go.opentelemetry.io/otel/exporters/otlp/otlptrace/otlptracehttp"
	"go.opentelemetry.io/otel/sdk/resource"
	sdktrace "go.opentelemetry.io/otel/sdk/trace"
	semconv "go.opentelemetry.io/otel/semconv/v1.26.0"
	"go.opentelemetry.io/otel/trace"
)

const tracerName = "beater.sdk"

// Package-level state set by Init. The provider is also stashed so Flush can
// force-flush without the caller holding the shutdown closure.
var (
	cfg      atomic.Pointer[Config]
	provider atomic.Pointer[sdktrace.TracerProvider]
	seq      atomic.Int64
)

// Init configures a global OpenTelemetry TracerProvider that exports spans to
// Beater over OTLP/HTTP. It returns a shutdown function that flushes and stops
// the provider; call it (e.g. with defer) before the process exits.
func Init(ctx context.Context, c Config) (func(context.Context) error, error) {
	opts := []otlptracehttp.Option{
		otlptracehttp.WithEndpointURL(c.otlpTracesURL()),
	}
	if strings.HasPrefix(c.BaseURL, "http://") {
		opts = append(opts, otlptracehttp.WithInsecure())
	}
	if c.APIKey != "" {
		opts = append(opts, otlptracehttp.WithHeaders(map[string]string{
			"authorization": "Bearer " + c.APIKey,
		}))
	}

	exporter, err := otlptracehttp.New(ctx, opts...)
	if err != nil {
		return nil, err
	}

	res, err := resource.New(ctx, resource.WithAttributes(
		semconv.ServiceName(c.ServiceName),
	))
	if err != nil {
		return nil, err
	}

	tp := sdktrace.NewTracerProvider(
		sdktrace.WithBatcher(exporter),
		sdktrace.WithResource(res),
	)
	otel.SetTracerProvider(tp)

	conf := c
	cfg.Store(&conf)
	provider.Store(tp)

	return func(ctx context.Context) error {
		return tp.Shutdown(ctx)
	}, nil
}

func tracer() trace.Tracer {
	return otel.GetTracerProvider().Tracer(tracerName)
}

func applyCommon(span trace.Span, kind string) {
	span.SetAttributes(
		attribute.String(AttrSpanKind, kind),
		attribute.Int64(AttrSeq, seq.Add(1)),
	)
	if c := cfg.Load(); c != nil && c.ReleaseID != "" {
		span.SetAttributes(attribute.String(AttrReleaseID, c.ReleaseID))
	}
}

func toValue(v any) string {
	if s, ok := v.(string); ok {
		return s
	}
	b, err := json.Marshal(v)
	if err != nil {
		return ""
	}
	return string(b)
}

// Observe runs fn inside a new span named name with the given span kind. It sets
// the kind/seq/release attributes, records the error and span status, and ends
// the span. The error returned by fn is propagated.
func Observe(ctx context.Context, name, kind string, fn func(ctx context.Context) error) error {
	ctx, span := tracer().Start(ctx, name)
	defer span.End()
	applyCommon(span, kind)

	if err := fn(ctx); err != nil {
		span.RecordError(err)
		span.SetStatus(codes.Error, err.Error())
		return err
	}
	span.SetStatus(codes.Ok, "")
	return nil
}

// SetInput attaches an input payload to the span in ctx. Non-string values are
// JSON-encoded.
func SetInput(ctx context.Context, v any) {
	trace.SpanFromContext(ctx).SetAttributes(attribute.String(AttrInputValue, toValue(v)))
}

// SetOutput attaches an output payload to the span in ctx. Non-string values are
// JSON-encoded.
func SetOutput(ctx context.Context, v any) {
	trace.SpanFromContext(ctx).SetAttributes(attribute.String(AttrOutputValue, toValue(v)))
}

// Flush force-flushes any buffered spans to the exporter. Useful before a
// short-lived program exits.
func Flush(ctx context.Context) error {
	if tp := provider.Load(); tp != nil {
		return tp.ForceFlush(ctx)
	}
	return nil
}
