package beater

import (
	"context"
	"errors"
	"testing"

	"go.opentelemetry.io/otel"
	"go.opentelemetry.io/otel/attribute"
	"go.opentelemetry.io/otel/codes"
	sdktrace "go.opentelemetry.io/otel/sdk/trace"
	"go.opentelemetry.io/otel/sdk/trace/tracetest"
)

// setup installs a TracerProvider backed by an in-memory exporter and returns
// it. It also sets a release id so the release attribute is exercised.
func setup(t *testing.T) *tracetest.InMemoryExporter {
	t.Helper()
	exp := tracetest.NewInMemoryExporter()
	tp := sdktrace.NewTracerProvider(sdktrace.WithSyncer(exp))
	otel.SetTracerProvider(tp)
	provider.Store(tp)
	c := Config{ReleaseID: "rel-123"}
	cfg.Store(&c)
	t.Cleanup(func() { _ = tp.Shutdown(context.Background()) })
	return exp
}

func attrs(span sdktrace.ReadOnlySpan) map[string]attribute.Value {
	m := map[string]attribute.Value{}
	for _, kv := range span.Attributes() {
		m[string(kv.Key)] = kv.Value
	}
	return m
}

func TestObserveSetsKindReleaseAndOutput(t *testing.T) {
	exp := setup(t)

	err := Observe(context.Background(), "call-model", KindLLMCall, func(ctx context.Context) error {
		SetInput(ctx, map[string]string{"prompt": "hi"})
		SetOutput(ctx, "escalate")
		return nil
	})
	if err != nil {
		t.Fatalf("Observe returned error: %v", err)
	}

	spans := exp.GetSpans()
	if len(spans) != 1 {
		t.Fatalf("expected 1 span, got %d", len(spans))
	}
	s := spans.Snapshots()[0]
	if s.Name() != "call-model" {
		t.Errorf("name = %q, want call-model", s.Name())
	}
	a := attrs(s)

	if got := a[AttrSpanKind].AsString(); got != KindLLMCall {
		t.Errorf("%s = %q, want %q", AttrSpanKind, got, KindLLMCall)
	}
	if got := a[AttrReleaseID].AsString(); got != "rel-123" {
		t.Errorf("%s = %q, want rel-123", AttrReleaseID, got)
	}
	if got := a[AttrOutputValue].AsString(); got != "escalate" {
		t.Errorf("%s = %q, want escalate", AttrOutputValue, got)
	}
	if got := a[AttrInputValue].AsString(); got != `{"prompt":"hi"}` {
		t.Errorf("%s = %q, want JSON object", AttrInputValue, got)
	}
	if _, ok := a[AttrSeq]; !ok {
		t.Errorf("missing %s attribute", AttrSeq)
	}
	if s.Status().Code != codes.Ok {
		t.Errorf("status = %v, want Ok", s.Status().Code)
	}
}

func TestObservePropagatesAndRecordsError(t *testing.T) {
	exp := setup(t)

	wantErr := errors.New("boom")
	err := Observe(context.Background(), "failing", KindToolCall, func(ctx context.Context) error {
		return wantErr
	})
	if !errors.Is(err, wantErr) {
		t.Fatalf("Observe err = %v, want %v", err, wantErr)
	}

	s := exp.GetSpans().Snapshots()[0]
	if s.Status().Code != codes.Error {
		t.Errorf("status = %v, want Error", s.Status().Code)
	}
	if len(s.Events()) == 0 {
		t.Errorf("expected a recorded exception event")
	}
}

func TestSemconvKindSet(t *testing.T) {
	want := []string{
		KindAgentRun, KindAgentTurn, KindAgentPlan, KindAgentStep,
		KindLLMCall, KindToolCall, KindMCPRequest, KindRetrievalQuery,
		KindMemoryRead, KindMemoryWrite, KindGuardrailCheck,
	}
	if len(SpanKinds) != 11 {
		t.Fatalf("SpanKinds has %d entries, want 11", len(SpanKinds))
	}
	for _, k := range want {
		if _, ok := SpanKinds[k]; !ok {
			t.Errorf("SpanKinds missing %q", k)
		}
	}
}

func TestConfigOTLPURLAndDefaults(t *testing.T) {
	c := ConfigFromEnv()
	if c.BaseURL != "http://127.0.0.1:8080" || c.TenantID != "demo" ||
		c.ProjectID != "demo" || c.EnvironmentID != "local" {
		t.Fatalf("unexpected defaults: %+v", c)
	}
	want := "http://127.0.0.1:8080/v1/otlp/demo/demo/local/v1/traces"
	if got := c.otlpTracesURL(); got != want {
		t.Errorf("otlpTracesURL = %q, want %q", got, want)
	}
}
