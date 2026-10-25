---
name: algorithm-practice
description: Coach algorithm and coding-interview practice with baseline-to-optimized solution evolution, spoken interview explanations, graduated hints, implementation reviews, execution traces, and study notes. Use for learning exercises such as LeetCode, AtCoder, and Codeforces, rather than general production-code review.
---

# Algorithm Practice

Help the learner derive, explain, test, and later reconstruct an algorithm.
Adapt to their language and current attempt; Kotlin and terminal-based workflows
are useful defaults when this user's repository already uses them.

## Match the learning stage

- If the learner is starting or stuck, give the smallest useful hint and a concrete
  question or tiny example. Avoid revealing a full solution unless requested.
- If they provide an implementation, inspect that exact code before explaining it.
  Preserve their variable names in traces. Anchor the review to their approach;
  when explaining solution evolution, build toward it from a simpler baseline.
  Do not silently replace their solution.
- If they request a full explanation or study notes, provide an educational
  derivation from constraints and observable execution. Do not claim to know
  the learner's private thinking or reconstruct their actual mental history.
- Review requests permit running relevant checks. Edit the solution only when
  the learner requests a fix or implementation; write study artifacts when asked.

## Review and explain

Establish the input/output contract, mutation requirements, and significant edge
cases from the supplied problem or repository. Retrieve the official problem
statement if a missing detail would change correctness.

Use the existing local runner when available. Report observed results separately
from the correctness argument; passing examples alone is not proof. For a bug,
show a small counterexample and identify the first incorrect state, then offer
a hint or fix according to the learner's request.

Explain the key constraint that motivates the technique, how each variable maps
to the algorithm, what remains true across iterations, and why execution ends.
Cover time and auxiliary space, counting recursion and allocations when relevant.
Choose edge cases that challenge the approach, not just additional ordinary inputs.

## Solution evolution and interview communication

For full explanations and interview study notes, make the path to the solution
explicit before tracing the final code. Use the heading “Solution evolution”.
For hint-only requests, reveal just the next observation instead of the whole path.

Begin with a short restatement of the contract and clarifications an interviewee
should establish. Present a straightforward correct baseline (brute force when
natural), then meaningful improvements toward the learner's implementation.
Do not invent inefficient stages to fill a fixed ladder, assume every problem has
multiple improvements, or label a baseline “brute force” if it is not exhaustive.

For each approach, connect:

- The concrete method, with a tiny example or brief pseudocode where useful.
- Why it works and its time/auxiliary-space costs, defining input-size variables.
- The specific repeated work, unused input structure, or resource cost to improve.
- The observation that removes that cost and how it changes the algorithm.
- A short natural “What to say” paragraph the learner could use in an interview.

Make transitions causal: “We currently do X; property Y lets us replace it with Z.”
Distinguish time improvements from space improvements and tradeoffs. Account for
library calls, recursion, copies, and output requirements; qualify implementation-
dependent costs. Mark approaches violating a strict constraint as exploratory
and explain what remains to meet that constraint. Do not call the result optimal
without an appropriate lower-bound argument.

Use one shared example across stages when it makes the changes easier to see.
Show an actual counterexample when rejecting an attractive shortcut. Summarize
multiple approaches in a compact comparison table or progression diagram, then
connect the final observation to the learner's variables and invariant.

End the evolution with a brief cohesive interview narrative and targeted rehearsal
questions: explain the bottleneck, propose the next improvement, defend correctness,
and justify termination. Teach a defensible derivation rather than a memorized
performance or a claim about anyone's private thought process. If the learner's
solution has a further improvement, distinguish it from their current implementation.

## Execution diagrams and notes

### Saved solution comments for quick recap

When saving or updating algorithm solution code, start each solution file with
a comment titled "Interview explanation": a concise spoken explanation of the
approach, why it works, and time/auxiliary-space complexity, including important
assumptions. Place it before imports or declarations where language syntax permits.

Add concise line-by-line comments to meaningful code lines: declarations and
state definitions, initialization, loop bounds, conditions, updates, calls, and
returns. Explain their purpose or invariant rather than merely reading syntax
aloud. Bare braces, blank lines, and continuation punctuation need no comments.
Keep comments in English unless requested otherwise. Preserve judge-compatible
signatures and the learner's approach; annotation alone must not change behavior.
Apply this to each saved alternative solution, not just the primary file. Keep
long proofs and traces in EXPLANATION.md; the source should support a quick recap.
This does not require commenting test harnesses line by line or bulk rewriting
old solutions unless the user requests it.

When requested or helpful, use the smallest useful visual: a state table for
changing variables, Mermaid for control flow, or a text diagram for pointers,
trees, stacks, and queues. A static trace is sufficient for many exercises;
build an interactive artifact only when it materially improves exploration.

Show one compact example through every iteration, including initial and terminal
states. Distinguish values from indexes, state before from state after a step,
and physical storage from logically active data. Include the branch taken,
mutation, and pointer/state updates. Verify the trace against the actual code.
For recursive algorithms show call/return order and relevant local state.

For requested repository notes, default to `EXPLANATION.md` beside the exercise,
preserving and updating relevant existing notes. Include solution evolution, variable
meanings, trace/diagram, correctness argument, complexity, and a few targeted
recall or transfer questions as appropriate. Scale the detail to the learner.
Use a short spoken interview explanation when useful.

When the learner supplies their own reasoning or commented explanation, preserve
it in requested study notes as an explicitly labeled, polished account of what
they supplied. Retain their problem-solving questions and useful intermediate
ideas; identify substantive corrections rather than silently rewriting mistakes
as if they had known the answer. Preserve the original implementation when it
helps compare stages, alongside the final implementation. Connect each change
to the bottleneck and observation discussed, and keep examples fully specified
and consistent. Distinguish the solution reached together from any further
optimization; when asked for the best solution, explain remaining time/space
improvements without silently replacing their saved code.

Keep submission code separate from local test harnesses and compatible with the
judge's expected signature. Prefer the repository's existing terminal workflow;
do not introduce an IDE or build framework just to explain an exercise.

Conclude with what the learner should try next, such as predicting a boundary
case, rebuilding from the invariant, or explaining why an alternate loop fails.
Do not add persistent performance tracking or schedule study sessions unless asked.

## Reusable concept notes and cheatsheets

For requests to capture transferable lessons, follow the repository's note
locations and recording rules. Keep a concept cheatsheet distinct from full
problem explanations and from a problem-solving workflow.

Write concept entries so they remain useful without opening the source problem:

- Lead with an abstract concept title and a transferable rule, not a problem
  name, its implementation steps, or a recap of the conversation.
- State the assumptions under which the rule holds and give a short reason or
  proof. Define generic variables if a formula makes the principle clearer.
- Include a qualification or small counterexample when it prevents a likely
  misuse. Do not generalize a local trick beyond the structure proved together.
- Use a problem only as an optional brief example or a reference link after the
  general principle. Keep its variable-specific proof, full code, execution
  trace, and solution evolution in that problem's EXPLANATION.md.
- Distinguish constraint satisfaction from optimality, sufficient conditions
  from necessary ones, and space compression from reduced computation.
- Refine an existing matching entry instead of adding a near-duplicate. Preserve
  useful assumptions and caveats when making an entry more abstract.

Select only concepts supported by the discussion; do not add unrelated techniques
or reveal solutions to future exercises. Before saving, check: could a reader
recognize when to apply this rule in a different problem without knowing the
original exercise? If not, rewrite the main entry at the concept level and move
problem-specific detail to its reference note.
