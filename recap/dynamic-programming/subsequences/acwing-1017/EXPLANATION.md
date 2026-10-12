# AcWing 1017 — two-direction subsequence DP

## Your completed implementation

[LearnerMain.kt](LearnerMain.kt) preserves your array-based implementation,
with formatting and the direction comment cleaned up. Your naming is
**f = backward (right-to-left), g = forward (left-to-right)**. The earlier
reference Solution.kt and its trace below use the opposite names; the
underlying recurrence is identical.

Your corrected final loop takes the maximum over every endpoint in both
directions. Checking only `g[n - 1]` and `f[0]` misses paths ending in the
middle: for `[9,8,1,10]`, your f is `[2,2,1,1]` and g is `[1,2,3,1]`.
The correct result is 3, from `9 → 8 → 1`; checking only the two boundary
states would return 2.

Compile and run your standalone version from the repository root:

```sh
kotlinc recap/dynamic-programming/subsequences/acwing-1017/LearnerMain.kt -include-runtime -d /tmp/acwing-1017-learner.jar
java -jar /tmp/acwing-1017-learner.jar < recap/dynamic-programming/subsequences/acwing-1017/sample.in
```

Run it without input redirection to type your own cases. The original run.sh
continues to run the separate reference implementation.

[Kotlin solution](Solution.kt) · [Console input/output](Main.kt) · [Source and confirmed contract](SOURCE.md)

## Problem confirmed by the supplied statement

Given heights in their original order, find the largest number of positions
you can visit while moving in one fixed horizontal direction and selecting
strictly decreasing heights. You may skip positions. Count the starting
position too. Take the better result from moving right or moving left.

The user-supplied statement confirms distinct building heights, 1–100 test
cases, and 1–100 buildings per case. It supplies no numeric height bound.
The two O(N²) passes are appropriate for these bounds. Our local equal-height
case is an extra robustness check, not an input required by the statement.

Starting anywhere is represented by initializing every state to 1. The fixed
direction rule is represented by computing the two directions separately.
The strict height comparison enforces downward movement. Trying all valid
predecessor positions permits skipping buildings. Taking the largest state
allows the path to end anywhere.

Do not sort: the original positions determine which moves are possible.
A subsequence may skip entries but preserves their relative order in the
chosen direction. A contiguous subarray cannot skip entries. Equal heights
cannot extend a strictly decreasing subsequence.

## Solution evolution

A baseline enumerates all subsets of positions and checks whether their
heights are strictly decreasing in either direction. There are 2^n subsets,
so a direct check costs O(n × 2^n) time. It repeatedly explores paths with
the same endpoint.

DP keeps only the longest path ending at each position. If two valid paths
end at the same i, they have the same endpoint height and the same available
future positions. The longer path is always at least as useful to extend.
This makes one length per endpoint sufficient.

## State meaning and transitions

`f[i]` is the longest descending subsequence **ending exactly at i**, moving
left-to-right. It is not the best answer anywhere in the prefix.

Start with f[i] = 1: the path containing only i is valid. Any predecessor j
must satisfy both `j < i` (correct direction) and `h[j] > h[i]` (strict descent).
For each such j, try `f[j] + 1` and keep the maximum.

```text
f[i] = max(1, all f[j] + 1 with j < i and h[j] > h[i])
```

`g[i]` has the same endpoint meaning, but moves right-to-left. Predecessors
now have `j > i`; the height condition stays `h[j] > h[i]`. Process i in
descending order so g[j] is ready.

Take the maximum of all f and g values. Do not add f[i] and g[i]: that would
combine paths from different directions, which the modeled problem does
not allow. A path can finish at any position, so the final array entry alone
is not sufficient.

## Example matching the code

```text
index: 0  1  2  3  4
h:     9  4  7  3  2
```

| i, forward order | Valid predecessor indexes | f[i] |
| --- | --- | --- |
| 0 | None | 1 |
| 1 | 0 | 2 |
| 2 | 0 | 2 |
| 3 | 0, 1, 2 | 3 |
| 4 | 0, 1, 2, 3 | 4 |

Forward final state: f = [1,2,2,3,4]. One optimal path is 9 → 7 → 3 → 2,
skipping height 4.

| i, backward order | Valid predecessor indexes to its right | g[i] |
| --- | --- | --- |
| 4 | None | 1 |
| 3 | None | 1 |
| 2 | None | 1 |
| 1 | 2 | 2 |
| 0 | None | 1 |

Backward final state: g = [1,2,1,1,1]. The answer is max(4,2) = 4.

## Why it is correct

Every path ending at i is either the singleton i or has a previous endpoint
j in the correct direction with a strictly greater height. The recurrence
considers every such predecessor, so no valid optimal path is missed.
Conversely, appending i to any path admitted by those conditions produces
a valid path; the recurrence cannot invent an invalid answer.

By induction on traversal order, each predecessor's DP value is already
correct when used. Taking the maximum therefore gives the correct value
at i. Every path has an endpoint and a direction, so the maximum over both
arrays covers every allowed path. Both nested loops range over finite indexes.

Multiple predecessors may yield equally long paths. That does not cause
overcounting: we take a maximum length, not a sum of path counts.

## Kotlin boundaries and cost

`h.indices` is 0 until n. `0 until i` excludes i. In the reverse pass,
`n - 1 downTo i + 1` includes only indexes greater than i. At i = n-1,
that range is empty. Each DP list starts with 1 for every position.

Each pass examines n(n-1)/2 candidate predecessor pairs. Total time is O(n²)
per case; storage is O(n). Both lists are recreated for each case, avoiding
state leaking from a previous input.

## Interview wording

“I preserve the original order and define the state as the longest descending
subsequence ending at a particular position. A position alone gives length
one. I consider each earlier, taller position as its possible predecessor and
extend that predecessor's best length by one. I repeat the calculation from
right to left for the other direction, then take the largest state across
both passes. This takes O(n²) time and O(n) space.”

## Run locally

From the repository root:

```sh
bash recap/dynamic-programming/subsequences/acwing-1017/run.sh sample
bash recap/dynamic-programming/subsequences/acwing-1017/run.sh stdin
bash recap/dynamic-programming/subsequences/acwing-1017/run.sh test
```

The illustrative sample outputs 4, 4, 1. Test mode compares small random
inputs with exhaustive enumeration. These are local tests, not online acceptance.
