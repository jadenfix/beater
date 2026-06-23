import re


UNRESOLVED_REQUIRED_VALUES = {
    "...",
    "\u2026",
    "unknown",
    "not requested",
    "not reported",
    "tbd",
    "todo",
}
EMBEDDED_PLACEHOLDER = re.compile(
    "(^|[\\s:;,/()_-])(\\.\\.\\.|\\u2026|tbd|todo)($|[\\s:;,/()_-])", re.I
)

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


def clean_value(value):
    return value.strip().strip("`").strip()


def markdown_field_values(source_text, name):
    return [
        clean_value(match)
        for match in re.findall(
            r"^- " + re.escape(name) + r":[ \t]*(.*)$",
            source_text,
            re.MULTILINE,
        )
    ]


def contains_placeholder_fragment(value):
    return bool(EMBEDDED_PLACEHOLDER.search(value))


def is_unresolved_marker(value):
    cleaned = clean_value(value)
    return not cleaned or cleaned.lower() in UNRESOLVED_REQUIRED_VALUES


def is_unresolved_argument(value, *, allow_none=False):
    cleaned = clean_value(value)
    return (
        is_unresolved_marker(cleaned)
        or (cleaned.lower() == "none" and not allow_none)
        or contains_placeholder_fragment(cleaned)
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
