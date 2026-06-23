import re


LLM_OBSERVATION_FRAGMENTS = [
    "llm.call",
    "prompt",
    "completion",
    "model",
    "token breakdown",
    "cost",
    "latency",
    "confirmation code",
]
WATERFALL_OBSERVATION_FRAGMENTS = ["run", "turn", "step", "tool", "MCP"]

NEGATED_OBSERVATION = re.compile(
    r"\b(?:did\s+not|didn't|could\s+not|couldn't|cannot|can't|failed\s+to\s+see|"
    r"not\s+visible|not\s+shown|not\s+showing|missing|without)\b"
)
VISIBLE_OBSERVATION = re.compile(
    r"\b(?:saw|seen|visible|read|confirmed|verified|opened|clicked|showed|displayed|inspected)\b"
)


def observation_errors(field_name, value, required_fragments):
    normalized = value.lower()
    errors = []
    if NEGATED_OBSERVATION.search(normalized):
        errors.append(f"{field_name} must be a positive observation, not negated evidence")
    if not VISIBLE_OBSERVATION.search(normalized):
        errors.append(f"{field_name} must describe a positive visible observation")
    missing = [
        fragment for fragment in required_fragments if fragment.lower() not in normalized
    ]
    if missing:
        errors.append(f"{field_name} must mention: " + ", ".join(missing))
    return errors
