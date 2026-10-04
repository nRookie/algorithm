# Algorithm-solving workflow

Build the habit of deriving a solution, not merely remembering its code.

**Understand → try → observe → derive → justify → implement → verify.**

Use the same opening questions across problems, not the same algorithm. First
clarify the output and constraints, work a tiny example, and describe a correct
baseline. You need not implement brute force when its behavior and cost are
already clear. Technique recognition suggests a candidate; the problem's
properties must justify it.

After that common start, adapt the questions: BFS needs a full state, legal
moves, and a reason distance layers match the objective; DP needs a precise
subproblem answer, a recurrence, base cases, and a valid dependency order.
Greedy needs a reason committing to a local choice cannot spoil the result.
If stuck, identify the missing piece—state, transition, processing order, or
correctness argument—and investigate it with a small example.

## Quick rehearsal checklist

Before coding, explain these points in your own words. Leave unknown answers
open and work on the next small question rather than guessing.

1. **Goal:** The required result is…
2. **Baseline:** A straightforward correct method is…
3. **Cost:** Its main time or space cost is…
4. **Observation:** The useful property that could reduce this cost is…
5. **State:** I need to track… Each variable means…
6. **Invariant:** Before each iteration, it is true that…
7. **Transition:** One iteration reads…, saves…, changes…, and advances…
8. **Completion:** We finish when… This implies the required result because…
9. **Verification:** I will trace… and test…

Use this as a guide, not a rigid sequence. Variable meanings, formulas, and
invariants can develop together. Return to an earlier step when an example
reveals a flaw. Not every problem needs multiple optimizations.

## 1. Understand the goal

Ask: **What exactly must the output satisfy?**

Identify the input, output, guarantees, constraints, and allowed modifications.
For example, distinguish returning a new array from modifying the existing one.

Say:

> Given ___, I need to produce ___, while preserving ___.

Do not choose an algorithm before understanding the contract.

## 2. Solve one small example manually

Ask: **If I had no programming language, how would I solve this example?**

Draw the data and perform one action at a time. Notice what you inspect,
remember, change, or repeat. Choose an example small enough to follow but rich
enough to expose the difficulty.

First describe the action in ordinary language. Code comes later.

## 3. Establish a straightforward solution

Ask: **What is the simplest method I can explain and justify?**

Extra arrays, repeated scans, or checking all possibilities can be useful
starting points. Explain why the method works and estimate its time and space.

If it violates a requirement, say so. It is then an exploratory baseline, not
the final answer. A correct baseline also provides a reference for later tests.

## 4. Find the specific inefficiency

Ask:

> What work am I repeating, or what information am I storing unnecessarily?

Then:

> Which property of this problem could eliminate that cost?

When repeated simulations fail, also ask: **What did this first failure prove
about other candidates?** Compare a fresh candidate with the resources or
state the old attempt had at the same point. Discard an interval only after
proving that its candidates cannot do better. In Gas Station, every station
reached during a failed attempt would start with no more gas if tried fresh.

Useful properties might include sorted input, repeated subproblems, a limited
value range, or a quantity that changes predictably.

Explain each improvement causally:

> Currently I do ___ repeatedly. Because ___, I can instead ___.

Do not replace this reasoning with a technique name such as “two pointers.”
Do not force an improvement when the straightforward solution is sufficient.

### When the useful observation is hard to find

Start with the information your correct baseline stores and the work it repeats.
Use these smaller questions to investigate possible improvements:

| Question | What to look for |
|---|---|
| **History:** If different paths reach the same state, do their future possibilities differ? | If not, merge those histories and avoid solving the same future problem repeatedly. Include any history that still affects valid choices in the state. |
| **Structure:** What shape do the possible states have? | Look for a prefix, interval, ordering, or another pattern. Draw the actual states before choosing a representation. |
| **Sufficiency:** Can a smaller representation preserve everything future decisions need? | Consider a boundary, count, best value, or another summary. Check whether two situations with the same summary could require different decisions. |
| **Dependency:** Which input guarantee makes this simplification valid? | Name the exact guarantee, then imagine removing it. Find an example where the proposed summary would lose necessary information. |

For example, in Jump Game:

```text
Explore jump paths.
    → Paths reaching the same index have the same future options.
Track which indices are reachable.
    → Every shorter jump is allowed, so reachable indices form a prefix.
Track the prefix's boundary, farthest.
    → Only reachable indices may extend that boundary.
```

A reachability array such as `T T T T F F` can be represented by `farthest = 3`.
The invariant is that every index from `0` through `farthest` is reachable using
the positions processed so far. An index `i` may extend the boundary only when
`i <= farthest`; its contribution is `i + nums[i]`.

The word **maximum** is essential here: any shorter jump is also allowed. If
jumps had to be exactly the given length, reachable positions could have holes.
For example, with exact jumps in `[2, 3, 0, 0, 0]`, index `2` is reachable but
index `1` is not. A boundary alone would incorrectly treat index `1` as usable.

This is one route to an optimization, not a requirement for every problem.
Other improvements may come from reusing calculations, faster lookups, sorting,
or changing processing order. Keep a smaller state only when you can explain
why the information removed cannot affect future decisions.

## 5. Derive the rule and define the state

Ask: **What information do I need to decide the next action?**

For each variable, establish:

- What it represents: an index, value, count, boundary, or other state.
- What data or processed region it refers to.
- When its meaning is valid, such as at the start of an iteration.

Prefer “the next position to write” over “the left pointer.”
For movement, distinguish source from destination. For modified data,
distinguish original contents from current contents.

For aggregates, write the exact range and reference point: one element's
change, a sum measured from index 0, and resources measured from the current
candidate are different quantities. Keep names and meanings stable. Before
using an aggregate to accept a candidate, identify whether the task requires
an endpoint condition or a condition at every intermediate step.

Derive formulas from the desired behavior in the example, then explain why
the same relationship applies generally. Do not memorize a formula whose
variables you cannot define.

## 6. Identify what must remain true

Ask: **Before every iteration, what can I rely on?**

This is the loop invariant. Start with plain language:

- Everything before this boundary is already correct.
- This variable contains the best result among the elements examined so far.
- This temporary variable preserves the value needed for the next move.

An invariant is a claim you must justify, not just a description of your intent.
Use mathematical notation only when it makes that claim clearer.

## 7. Design the control flow

Work through one question at a time:

| Question | Purpose |
|---|---|
| How do I make the invariant true initially? | Initialization |
| What is one valid next action? | Transition |
| Why is the invariant still true afterward? | Preservation |
| What changes so that we eventually finish? | Progress and termination |
| Why does the stopping condition imply the required result? | Completion |

For nested loops, distinguish finishing one local traversal from finishing the
whole task. Establish complete coverage without accidentally repeating work.

Decide how often each initialization should run:

```text
Once for the entire function?
Once per outer-loop iteration?
Once per inner-loop iteration?
```

Statements inside a loop body execute again whenever that body repeats.
Do not reset a variable whose updated state must carry into the next iteration.

Choose the loop construct to match the behavior:

- `while`: check whether to enter before executing the body.
- `do … while`: execute the body before checking whether to repeat.
- `for`: iterate over a suitable range or collection.

When recursion is appropriate, apply the same reasoning to the function's
contract, base cases, recursive calls, and progress toward a base case.

## 8. Implement one transition, then assemble

Ask: **What must I read or save before changing anything?**

Write the statements in that order. Then add initialization and the surrounding
control flow. Keep the code close to your explanation.

If a line has no clear role, stop and examine it. If language syntax, scope,
or evaluation order is unclear, resolve that separately from the algorithm.

## 9. Trace, test, and explain

Trace a small example using **before → action → after** states.
For arrays, show the index row, array contents, pointers, and temporary values.
Record the exact point at which each variable changes.

Then choose tests that challenge your assumptions, where valid for the problem:

- Smallest input.
- Repeated values or all-equal values.
- No work required or an answer at a boundary.
- A transition that wraps, changes direction, or changes branches.
- Multiple groups, components, or passes when relevant.
- A case that breaks the convenient pattern of your first example.

Check which special properties your first example has. Gas Station's familiar
zero-total example hid an incorrect candidate test that failed with a positive
total. For a rule claiming that every step is feasible, try an early shortage
followed by a large surplus. Test the proposed acceptance rule against the
correct baseline before adding another technique or state dimension.

Compare an optimized implementation against your simple baseline on small
inputs when practical. Recheck time and auxiliary space, including temporary
collections and recursion depth.

Finally say:

> It starts correctly because ___. Each step preserves ___ and makes progress
> by ___. When it stops, ___ guarantees the answer.

A trace verifies an example. The argument above explains why the method works
for every valid input. Passing tests alone is not a general proof.

## How to practice this repeatedly

1. **Guided practice:** answer one small question at a time with a coach.
2. **Checklist practice:** solve a related problem with only the checklist above.
3. **Independent reconstruction:** later, derive the approach again without
   looking at the solution. If stuck, revisit the smallest missing idea.
4. **Transfer:** use the same questions on a different problem. Do not assume
   the same algorithm applies merely because the examples look similar.

Before a session, read the quick checklist. During a session, focus only on the
current unanswered question. Afterward, explain the approach aloud and note
the one idea that required help, if you want a personal reminder.

In an interview, communicate the goal, baseline, useful observation, variable
roles, correctness argument, and complexity. Use a small example to make an
unclear transition concrete; you need not narrate every checklist item mechanically.

Measure progress by whether you can explain **why the next step is valid**,
not only by how quickly you remember code.

## Ask for this coaching style

```text
Use $algorithm-step-by-step to practice [problem].
My current understanding is: [...].
Ask one small question at a time and wait for my answer.
```

Without a skill invocation, use:

> Coach me through deriving and dry-running this algorithm. Ask one small
> question at a time and wait for my answer. Help me derive the formulas,
> variable definitions, invariant, and control flow before writing the complete
> solution. Show the array and relevant variables during tracing. Correct one
> misconception at a time; do not reveal future steps unless I ask.

## Where related material belongs

- This folder: reusable reasoning and study guidance.
- [Algorithm concepts cheatsheet](algorithm-concepts-cheatsheet.md): reusable
  facts, their conditions, and common pitfalls. Ask “What can we learn from
  this?” to record relevant takeaways there after an exercise.
- Individual problem folders: problem-specific code, traces, and proofs.
- Skills: instructions for how the assistant should coach.

For a worked array example, see
[Rotate Array implementation guide](../leetcode/189_rotate_array/implementation.md).
For a worked derivation from repeated pair comparisons to a single scan, see
[Best Time to Buy and Sell Stock](../leetcode/121_best_time_to_buy_and_sell_stock/EXPLANATION.md).
