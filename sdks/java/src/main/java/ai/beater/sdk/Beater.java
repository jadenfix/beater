package ai.beater.sdk;

import io.opentelemetry.api.OpenTelemetry;
import io.opentelemetry.api.trace.Span;
import io.opentelemetry.api.trace.StatusCode;
import io.opentelemetry.api.trace.Tracer;
import io.opentelemetry.context.Scope;
import io.opentelemetry.exporter.otlp.http.trace.OtlpHttpSpanExporter;
import io.opentelemetry.sdk.OpenTelemetrySdk;
import io.opentelemetry.sdk.resources.Resource;
import io.opentelemetry.sdk.trace.SdkTracerProvider;
import io.opentelemetry.sdk.trace.SpanProcessor;
import io.opentelemetry.sdk.trace.export.BatchSpanProcessor;
import java.util.concurrent.atomic.AtomicLong;
import java.util.function.Supplier;

/**
 * Ergonomic entry point for tracing arbitrary code as Beater spans.
 *
 * <p>Call {@link #init(BeaterConfig)} once at process start, then wrap work in
 * {@link #observe(String, String, Supplier)}.
 */
public final class Beater {

    private static final String TRACER_NAME = "beater.sdk";

    private static volatile OpenTelemetrySdk sdk;
    private static volatile SdkTracerProvider provider;
    private static volatile BeaterConfig config;
    private static volatile Tracer tracer;
    private static final AtomicLong SEQ = new AtomicLong(0);

    private Beater() {}

    /** Initialize the Beater tracer with an OTLP/HTTP exporter. Call once at startup. */
    public static synchronized void init(BeaterConfig cfg) {
        var exporterBuilder = OtlpHttpSpanExporter.builder().setEndpoint(cfg.otlpHttpTracesUrl());
        if (cfg.apiKey != null && !cfg.apiKey.isEmpty()) {
            exporterBuilder.addHeader("authorization", "Bearer " + cfg.apiKey);
        }
        SpanProcessor processor = BatchSpanProcessor.builder(exporterBuilder.build()).build();
        configure(cfg, processor);
    }

    /**
     * Initialize with a caller-supplied {@link SpanProcessor}. Useful for tests
     * (e.g. wiring an in-memory exporter) and custom export pipelines.
     */
    public static synchronized void init(BeaterConfig cfg, SpanProcessor processor) {
        configure(cfg, processor);
    }

    private static void configure(BeaterConfig cfg, SpanProcessor processor) {
        Resource resource = Resource.getDefault().toBuilder()
                .put("service.name", cfg.serviceName)
                .build();
        SdkTracerProvider tracerProvider = SdkTracerProvider.builder()
                .setResource(resource)
                .addSpanProcessor(processor)
                .build();
        OpenTelemetrySdk built = OpenTelemetrySdk.builder()
                .setTracerProvider(tracerProvider)
                .build();
        provider = tracerProvider;
        sdk = built;
        config = cfg;
        tracer = built.getTracer(TRACER_NAME);
    }

    private static Tracer tracer() {
        if (tracer == null) {
            init(BeaterConfig.fromEnv());
        }
        return tracer;
    }

    private static void applyCommon(Span span, String kind) {
        span.setAttribute(SemConv.SPAN_KIND, kind);
        span.setAttribute(SemConv.SEQ, SEQ.incrementAndGet());
        BeaterConfig cfg = config;
        if (cfg != null && cfg.releaseId != null && !cfg.releaseId.isEmpty()) {
            span.setAttribute(SemConv.RELEASE_ID, cfg.releaseId);
        }
    }

    /** Open a span, run {@code body}, record status, and end the span; returns the result. */
    public static <T> T observe(String name, String kind, Supplier<T> body) {
        Span span = tracer().spanBuilder(name).startSpan();
        applyCommon(span, kind);
        try (Scope ignored = span.makeCurrent()) {
            T result = body.get();
            span.setStatus(StatusCode.OK);
            return result;
        } catch (RuntimeException e) {
            span.setStatus(StatusCode.ERROR, String.valueOf(e.getMessage()));
            span.recordException(e);
            throw e;
        } finally {
            span.end();
        }
    }

    /** {@link Runnable} overload of {@link #observe(String, String, Supplier)}. */
    public static void observe(String name, String kind, Runnable body) {
        observe(name, kind, () -> {
            body.run();
            return null;
        });
    }

    /** Attach an input payload to the current span (JSON-encoded if not a String). */
    public static void setInput(Object value) {
        Span.current().setAttribute(SemConv.INPUT_VALUE, toValue(value));
    }

    /** Attach an output payload to the current span (JSON-encoded if not a String). */
    public static void setOutput(Object value) {
        Span.current().setAttribute(SemConv.OUTPUT_VALUE, toValue(value));
    }

    /** Force-flush pending spans. Useful before a short-lived process exits. */
    public static void flush() {
        SdkTracerProvider p = provider;
        if (p != null) {
            p.forceFlush().join(30, java.util.concurrent.TimeUnit.SECONDS);
        }
    }

    /** Shut down the tracer pipeline, flushing any pending spans. */
    public static synchronized void shutdown() {
        OpenTelemetrySdk s = sdk;
        if (s != null) {
            s.close();
        }
        sdk = null;
        provider = null;
        tracer = null;
        config = null;
    }

    /** String values pass through; everything else is encoded as a small JSON value. */
    static String toValue(Object obj) {
        if (obj == null) {
            return "null";
        }
        if (obj instanceof String s) {
            return s;
        }
        if (obj instanceof Number || obj instanceof Boolean) {
            return obj.toString();
        }
        return jsonString(String.valueOf(obj));
    }

    private static String jsonString(String s) {
        StringBuilder sb = new StringBuilder(s.length() + 2);
        sb.append('"');
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '"' -> sb.append("\\\"");
                case '\\' -> sb.append("\\\\");
                case '\n' -> sb.append("\\n");
                case '\r' -> sb.append("\\r");
                case '\t' -> sb.append("\\t");
                default -> {
                    if (c < 0x20) {
                        sb.append(String.format("\\u%04x", (int) c));
                    } else {
                        sb.append(c);
                    }
                }
            }
        }
        sb.append('"');
        return sb.toString();
    }
}
