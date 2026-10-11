---
name: algorithm-recap
description: Reorganize old algorithm Markdown memos into readable study notes grouped by dynamic topics and subtopics, convert C++ or Go solutions to Kotlin collections, and find related LeetCode exercises when the original problem has no usable online judge. Use for revisiting previously studied material.
---

# Algorithm Recap

Help the learner revisit algorithm problems studied years ago, using their
supplied Markdown memos as the starting point. Support reconstruction of the
reasoning and independent practice, not just code translation.

Read the repository's AGENTS.md. Read the relevant repository-owned skill:
- [algorithm-practice](../algorithm-practice/SKILL.md) for explanations,
  implementation reviews, and study notes.
- [algorithm-step-by-step](../algorithm-step-by-step/SKILL.md) when the learner
  explicitly requests interactive derivation or dry runs during recap.

## Work topic by topic

Derive topics from the supplied material and existing recap directories.
Binary search, DFS, BFS, dynamic programming, number theory, and greedy
algorithms are examples, not a fixed taxonomy.

If a memo covers multiple topics, summarize the grouping and begin with the
user's selected topic, or the first topic in the memo if none is selected.
Complete the current topic or subtopic before introducing another. Do not
expand into unrelated algorithms or reveal solutions to future exercises.

Create subtopics when they meaningfully group related problems. Dynamic
programming might include knapsack, interval DP, tree DP, digit DP, or bitmask
DP. Create only categories represented in the supplied material, without
empty category folders.

Check existing categories before creating one. Use consistent lowercase,
hyphenated directory names and avoid synonymous categories. Classify by the
central reasoning technique rather than incidental storage: DFS using arrays
still belongs under DFS. Tree DP may belong under dynamic-programming/tree-dp,
with a cross-link from DFS when useful.

Give each problem one primary location; cross-link rather than duplicate it.

## Organize the files

Use this default structure unless the user specifies another location:

```text
recap/
  README.md
  <topic>/
    README.md
    [<subtopic>/]
      <problem-slug>/
        SOURCE.md
        EXPLANATION.md
        Solution.kt
        Main.kt       # When needed for local validation
        run.sh        # When useful with the existing Kotlin workflow
```

The subtopic level is optional. Add a subtopic README when that level exists.

- Root README: topics and links.
- Topic/subtopic README: a concise overview, problem links, and recap order.
- SOURCE.md: the supplied memo and original code relevant to this problem.
- EXPLANATION.md: cleaned explanations and references.
- Solution.kt: Kotlin implementation; keep test code separate.

Preserve original material. Do not move or overwrite existing solutions.
If a problem already exists in the repository, link to it and reuse relevant
notes or runners rather than creating unnecessary duplicates. For subsequent
recaps, refine matching notes and preserve source provenance. Update indexes
as topics evolve. Create only files needed for the supplied material.

## Rewrite the memo for understanding

Use clear English unless the learner requests another language. Preserve
useful reasoning, questions, failed attempts, and examples. Distinguish the
learner's supplied reasoning from explanations added now.

Correct substantive mistakes explicitly. Do not polish incorrect reasoning
into an apparently valid argument or invent the learner's past thinking.
If missing problem details could change correctness, retrieve the original
statement when available or ask for the missing contract; do not invent it.

Adapt explanation length to the problem. Include, where useful:

1. Problem contract and important constraints.
2. Original reasoning, polished.
3. Solution evolution: a correct baseline and meaningful improvements.
4. Exact meanings of variables or DP states.
5. Why transitions or candidate eliminations are valid.
6. One small execution trace matching the code.
7. Correctness, termination, and time/auxiliary-space complexity.
8. Kotlin implementation notes.
9. A short spoken interview explanation.
10. Optional self-study recall questions and a related practice exercise;
    these do not require answers before completing the recap.

Do not manufacture optimization stages. Keep examples fully specified and
consistent with the actual implementation.

Emphasize the learner's current practice goals:
- Define state at an exact moment, including ranges and endpoints.
- Derive transitions from the problem's requirements.
- Explain why discarded candidates cannot contain a required answer.
- Challenge assumptions with targeted counterexamples.
- Count actual implementation work, not merely possible outcomes.

Follow AGENTS.md when the learner requests reusable takeaways or asks to
remember a concept. Read and refine the existing concepts cheatsheet; keep
full traces and proofs in the problem folder.

## Convert C++ and Go to Kotlin collections

Translate the original algorithm into idiomatic Kotlin, preserving its
behavior and intended complexity. Use Kotlin collections by default,
including when arrays implement a data structure in the original code.
Translate the structure's purpose and operations rather than mechanically
reproducing its physical storage.

Typical mappings:
- Fixed indexed storage → MutableList(size) { initialValue }.
- Growable sequence → MutableList or ArrayList.
- Stack or queue → Kotlin ArrayDeque.
- Membership-only tracking → MutableSet when appropriate.
- Key-value lookup or frequency counts → MutableMap when appropriate.
- Array-based graph edge chains → adjacency lists of neighbors or edges.
- Priority queue → java.util.PriorityQueue on Kotlin/JVM, since Kotlin's
  standard collections have no priority queue.

Replace array-backed queue head/tail counters with ArrayDeque when they
serve only queue operations. Preserve indexes when positions matter,
duplicates when meaningful, ordering when correctness depends on it, and
explicit tree, graph, or DP relationships needed by the algorithm.

Allocate independent rows in a two-dimensional DP table:

```kotlin
val dp = MutableList(rows) { MutableList(cols) { 0 } }
```

Do not reuse one mutable row for every position.

Choose collections that retain intended complexity. Use ArrayDeque for
queue operations instead of removing index 0 from an ArrayList. Avoid
repeated copying, sorting, or collection pipelines in critical loops.
Account for boxing and allocation overhead in large numeric tables.

When a judge requires an array parameter or return type, preserve that
external signature. Use collections internally where suitable and explain
necessary boundary conversions. If collection overhead could prevent meeting
the constraints, explain the concrete tradeoff before proposing an array-based
exception; do not silently abandon the collection preference.

Keep recognizable variable names when they aid comparison. Explain important
language differences: Int versus Long and intermediate overflow, integer
division and remainder, bit operations and signedness, mutation and copying,
recursion depth, and input parsing. Verify relevant Kotlin APIs against the
available runtime or official documentation rather than assuming compatibility.

For recap implementations, target the matched LeetCode problem by default so
the learner can submit the saved Solution.kt directly. Verify and follow its
Kotlin class/method signature, parameter and return types, coordinate indexing,
and constraints. Preserve the original algorithmic idea; adapting the interface
is expected. Keep console parsers and local test entry points out of submission
code. Keep the original AcWing code as a reference and explain meaningful
contract changes. Align explanations and visualizations with the target's
indexing. Use the old standalone contract only when explicitly requested or
when no suitable judge problem exists, stating that limitation.

If original code is incorrect, preserve it in SOURCE.md, explain a small
counterexample and correction, and save corrected Kotlin with changes clearly
identified. Treat further optimizations as separate alternatives; do not
silently replace the original algorithm.

Use existing Kotlin tools and the terminal workflow. Compile and run meaningful
examples and boundary cases when available. Compare with a simple baseline
on small inputs when useful. State which checks actually ran and unresolved
limitations. In EXPLANATION.md, describe meaningful data-structure changes,
why behavior is preserved, and complexity or memory tradeoffs.

## Find a related LeetCode exercise

When the original problem has no usable online judge, search the web and
verify candidates against official LeetCode problem pages.

Prefer a close match in objective, constraints, and central technique.
Suggest one primary exercise, with an optional easier prerequisite or harder
follow-up when useful for the current topic. Prefer accessible exercises;
note a Premium restriction when verified. If access is unclear, say so.

For each recommendation, record:
- Problem number, title, and official link.
- Difficulty and access restriction, when verifiable.
- Match type: equivalent, requires adaptation, or same technique.
- What reasoning transfers and which constraints differ.

Do not claim equivalence merely because problems share a topic. Do not label
the original implementation as a solution to a related problem unless its
contract has been checked. The matched primary problem is the recap's default
implementation target; distinguish it from the preserved original source.

If no close match exists, say so and offer a clearly labeled technique-related
exercise. Do not invent numbers or links. The primary matched problem's Kotlin
solution is part of the recap. Keep solutions to additional practice exercises
hidden unless requested, so the learner can attempt them independently.

## Recap together

Default to a direct recap of previously studied material. Review the learner's
supplied reasoning and code, explain corrections, and produce readable notes.
Do not require them to repeat derivations, answer checkpoint questions, or
work through an interactive trace unless they explicitly request that mode.
Answer their questions directly without automatically adding a quiz afterward.

For document preparation, complete the supplied current-topic notes and Kotlin
conversions without asking for approval on routine choices.

When the learner explicitly requests interactive recap practice, use
algorithm-step-by-step: ask one small question at a time and wait, with
graduated hints. For a new problem, follow AGENTS.md's default step-by-step
coaching preference. A newly suggested exercise does not automatically start
an interactive session during recap.

Clarify genuinely missing problem details when needed for correctness; do
not use clarification as a checkpoint quiz.

At completion, link saved files, summarize corrections and Kotlin validation,
and identify the next exercise for independent practice. Do not create study
schedules or performance tracking unless requested.
