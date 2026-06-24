// Quickstart: emit an agent.run -> agent.plan -> llm.call trace to Beater.
//
//	BEATER_TENANT_ID=demo BEATER_PROJECT_ID=demo BEATER_ENVIRONMENT_ID=local \
//	    go run ./example
package main

import (
	"context"
	"log"

	beater "github.com/jadenfix/beater/sdks/go"
	"go.opentelemetry.io/otel/trace"
)

func main() {
	ctx := context.Background()

	cfg := beater.ConfigFromEnv()
	cfg.ServiceName = "beater-go-quickstart"
	cfg.ReleaseID = "quickstart"

	shutdown, err := beater.Init(ctx, cfg)
	if err != nil {
		log.Fatalf("beater init: %v", err)
	}
	defer func() { _ = shutdown(ctx) }()

	err = beater.Observe(ctx, "handle_refund", beater.KindAgentRun, func(ctx context.Context) error {
		log.Printf("trace_id=%s", trace.SpanContextFromContext(ctx).TraceID())
		beater.SetInput(ctx, "late delivery refund after 31 days")

		var plan string
		if err := beater.Observe(ctx, "make_plan", beater.KindAgentPlan, func(ctx context.Context) error {
			plan = "look up refund policy"
			beater.SetOutput(ctx, plan)
			return nil
		}); err != nil {
			return err
		}

		return beater.Observe(ctx, "call_model", beater.KindLLMCall, func(ctx context.Context) error {
			beater.SetInput(ctx, plan)
			beater.SetOutput(ctx, "Escalate: order is outside the standard refund window.")
			return nil
		})
	})
	if err != nil {
		log.Fatalf("agent run: %v", err)
	}

	if err := beater.Flush(ctx); err != nil {
		log.Printf("flush: %v", err)
	}
	log.Println("trace flushed -- open the dashboard to inspect it")
}
