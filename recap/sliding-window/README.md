# Sliding-window recap

When minimizing a valid window, one right endpoint may allow several left
boundaries. Record each valid length and keep shrinking when the invariant
justifies it; a single `if` can miss the best boundary for that endpoint.

For sum thresholds, ordinary shrinking relies on nonnegative elements.
Negative elements break that monotonicity. A prefix-sum monotonic deque instead
keeps selected candidate starts, which need not be consecutive indices.

| Problem | Recap focus |
| --- | --- |
| [862. Shortest Subarray with Sum at Least K](leetcode-862-shortest-subarray-with-sum-at-least-k/EXPLANATION.md) | Why front removal uses `while`, safe removal, and the learner's implementation corrections |
