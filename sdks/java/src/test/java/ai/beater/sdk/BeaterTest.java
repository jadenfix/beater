package ai.beater.sdk;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

import io.opentelemetry.sdk.testing.exporter.InMemorySpanExporter;
import io.opentelemetry.sdk.trace.data.SpanData;
import io.opentelemetry.sdk.trace.export.SimpleSpanProcessor;
import java.util.List;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class BeaterTest {

    private InMemorySpanExporter exporter;

    @BeforeEach
    void setUp() {
        exporter = InMemorySpanExporter.create();
        BeaterConfig cfg = new BeaterConfig();
        cfg.releaseId = "rel-42";
        Beater.init(cfg, SimpleSpanProcessor.create(exporter));
    }

    @AfterEach
    void tearDown() {
        Beater.shutdown();
    }

    @Test
    void observeSetsKindReleaseAndOutput() {
        String result = Beater.observe("answer", SemConv.LLM_CALL, () -> {
            Beater.setInput("hello");
            Beater.setOutput("world");
            return "world";
        });
        assertEquals("world", result);

        List<SpanData> spans = exporter.getFinishedSpanItems();
        assertEquals(1, spans.size());
        SpanData span = spans.get(0);

        assertEquals("answer", span.getName());
        assertEquals(
                SemConv.LLM_CALL,
                span.getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.stringKey(SemConv.SPAN_KIND)));
        assertEquals(
                "rel-42",
                span.getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.stringKey(SemConv.RELEASE_ID)));
        assertEquals(
                "hello",
                span.getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.stringKey(SemConv.INPUT_VALUE)));
        assertEquals(
                "world",
                span.getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.stringKey(SemConv.OUTPUT_VALUE)));
        assertNotNull(
                span.getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.longKey(SemConv.SEQ)));
    }

    @Test
    void runnableOverloadProducesSpan() {
        Beater.observe("plan", SemConv.AGENT_PLAN, () -> Beater.setOutput("ok"));
        List<SpanData> spans = exporter.getFinishedSpanItems();
        assertEquals(1, spans.size());
        assertEquals(
                SemConv.AGENT_PLAN,
                spans.get(0).getAttributes().get(
                        io.opentelemetry.api.common.AttributeKey.stringKey(SemConv.SPAN_KIND)));
    }

    @Test
    void semconvHasElevenSpanKinds() {
        assertEquals(11, SemConv.SPAN_KINDS.size());
    }
}
