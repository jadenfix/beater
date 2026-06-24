/**
 * Example: instrument a real Stagehand instance and drive a browser step.
 *
 * Run Beater locally (OTLP gRPC on :4317), then:
 *
 *   export BEATER_OTLP_ENDPOINT=http://localhost:4317
 *   npm run example
 *
 * Requires `@browserbasehq/stagehand` installed (it is an optional peer dep,
 * so this file is illustrative — `npm test` does not need it).
 */
import { instrumentStagehand } from "../src/index.js";

async function main() {
  // Dynamic import so the example runs only when the optional dep is present.
  const mod = (await import(
    // @ts-expect-error optional peer dep, not installed for `npm test`/build.
    "@browserbasehq/stagehand"
  )) as unknown as {
    Stagehand: new (cfg: Record<string, unknown>) => {
      init(): Promise<unknown>;
      page: {
        goto(url: string): Promise<unknown>;
        act(action: string): Promise<unknown>;
        observe(instruction: string): Promise<unknown>;
        extract(opts: Record<string, unknown>): Promise<unknown>;
      };
      close(): Promise<unknown>;
    };
  };
  const { Stagehand } = mod;

  const stagehand = new Stagehand({ env: "LOCAL" });
  await stagehand.init();

  // One call: every act/observe/extract now emits canonical browser.* spans.
  instrumentStagehand(stagehand, {
    endpoint: process.env.BEATER_OTLP_ENDPOINT ?? "http://localhost:4317",
    serviceName: "stagehand-example",
  });

  await stagehand.page.goto("https://news.ycombinator.com");
  await stagehand.page.observe("the top story link");
  await stagehand.page.act("click the first story");
  await stagehand.page.extract({
    instruction: "the article title",
    schema: { title: "string" },
  });

  await stagehand.close();
}

main().catch((err) => {
  console.error(err);
  process.exitCode = 1;
});
