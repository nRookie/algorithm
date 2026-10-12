# LeetCode 56 — Merge Intervals

Online judge: [LeetCode 56](https://leetcode.com/problems/merge-intervals/description/)
(Medium). Submission code: [Solution.kt](Solution.kt).
Original memo and Go code: [SOURCE.md](SOURCE.md).

## Contract

Given closed intervals `[left, right]`, merge all overlapping intervals and
return the resulting non-overlapping intervals covering the same points.
Touching endpoints count as overlap: `[1,4]` and `[4,5]` merge into `[1,5]`.
The verified LeetCode constraints are 1–10,000 intervals, two endpoints per
interval, and `0 <= left <= right <= 10,000`. The Kotlin code also handles
empty input defensively, although the judge does not require it.

## Your reasoning, polished

1. Sort intervals by their left endpoint in ascending order.
2. Initialize `start` and `end` from the first sorted interval. They represent
   the current merged interval, which has not yet been added to the answer.
3. Scan from the second interval. If its left endpoint is at most `end`, it
   overlaps the current interval. Keep `start` and set `end = maxOf(end, right)`.
4. Otherwise, there is a gap. Save `[start, end]` and begin a new current
   interval using the next interval's endpoints.
5. After the loop, save the last current interval. No later gap exists to
   trigger that final append automatically.

Your Go code already uses the correct maximum and final append. The verbal
description needed these details: assigning only `end = right` can shrink a
merged interval. For `[1,10]` followed by `[2,3]`, the end must remain 10.

## Solution evolution

A straightforward baseline repeatedly searches for any overlapping pair,
replaces it with its union, and repeats until no overlap remains. It is correct
because each merge preserves covered points, but repeated full pair searches
can cost O(n³) time in a naive implementation.

Sorting avoids repeatedly searching for the next relevant interval. Left
endpoints never decrease, so a single pending merged interval is enough.
If the next left endpoint exceeds `end`, every later interval starts beyond
`end` too. The pending interval is therefore final and safe to emit.

## Indexes and boundaries

- `i` is a position in the sorted list, not a coordinate on the number line.
- `sorted[i][0]` is its left endpoint; `sorted[i][1]` is its right endpoint.
- `start` and `end` are inclusive coordinates, not list indexes.
- `1 until sorted.size` visits indexes 1 through `sorted.size - 1`; index 0
  was already used for initialization.
- `left <= end` includes touching endpoints. There is no `+1` adjustment:
  `[1,2]` and `[3,4]` remain separate under this interval contract.

## Execution trace

```text
Input:  [[8,10], [2,3], [1,6], [6,8], [15,18]]
Sorted: [[1,6], [2,3], [6,8], [8,10], [15,18]]
```

| Step | Comparison / action | Current interval | Saved result |
| --- | --- | --- | --- |
| Initialize | Take first interval | [1,6] | [] |
| [2,3] | 2 <= 6; contained, keep end = 6 | [1,6] | [] |
| [6,8] | 6 <= 6; touching, extend end = 8 | [1,8] | [] |
| [8,10] | 8 <= 8; extend end = 10 | [1,10] | [] |
| [15,18] | 15 > 10; save current, restart | [15,18] | [[1,10]] |
| Finish | Save final current interval | — | [[1,10], [15,18]] |

## Correctness: complete coverage, exactly once, no duplicates

The key distinction is between finished groups in `res` and one pending
group in `[start, end]`. We prove correctness using a loop invariant.

### Loop invariant

Before processing the interval at sorted index i:

1. `res` contains finalized, non-overlapping merged intervals, in increasing
   order. No unprocessed interval can overlap any of them.
2. `[start, end]` represents the last merged group of processed intervals.
   It has **not yet been appended** and lies strictly after every group in `res`.
3. Together, `res` and the pending interval cover **exactly the same points**
   as the processed input at indexes `0 until i`.

### Initialization

The first interval initializes `[start, end]`, and `res` is empty. Exactly
one interval has been processed, and the pending interval covers exactly its
points. Thus the invariant holds before i = 1. Empty input returns immediately.

### Overlap: left <= end

Sorting guarantees `start <= left`. Together with `left <= end`, this means
the next interval overlaps or touches the pending interval. Their union is
exactly `[start, maxOf(end, right)]`.

Updating `end` preserves all existing coverage and adds precisely the next
interval's coverage, without filling an uncovered gap. The finalized groups
remain unchanged, so the invariant holds for the next iteration. Nothing is
appended yet because the pending group may still grow.

For example, merging `[1,10]` with `[2,3]` must keep `[1,10]`. Taking the
maximum prevents a contained interval from shrinking the group's coverage.

### Gap: left > end

The next interval does not overlap the pending group. Every later interval
has `laterLeft >= left > end`, so none can ever overlap that group either.
This proves the group is final and safe to append.

We then replace `[start, end]` with `[left, right]`. The old pending group
is now finalized, the new interval becomes the pending group, and their
combined coverage is exactly the processed input. The invariant is preserved.

### Termination and final append

The loop advances i once per iteration, so it terminates after every interval
has been processed. The invariant then says that `res` plus the pending group
covers exactly the entire input. Appending that last group completes the result.
For a single input interval, the loop is empty and this final append saves it.

### Why nothing is missed or duplicated

| Concern | Why it cannot happen |
| --- | --- |
| An input interval is skipped | Index 0 initializes the state; the loop visits every remaining index exactly once. |
| A merged group is appended twice | On a gap, the old group is appended and immediately replaced by a new pending group. After the loop, only the still-pending group is appended. |
| Duplicate input intervals create duplicate output | They satisfy `left <= end` and merge into the same pending group. |
| Two output intervals overlap | A new group starts only when its left endpoint is strictly greater than the previous group's end; sorting prevents any future interval from bridging that gap. |
| Output contains extra coverage | We combine intervals only when they overlap or touch, so their union contains no previously uncovered gap. |

“Exactly once” refers to processing each input entry once and emitting each
merged group once. Several overlapping input entries intentionally contribute
to the same output group.

```text
Sorted input: [1,3], [1,3], [2,6], [8,10]

Initialize:   current = [1,3]
Duplicate:    current = [1,3]       // append nothing
Overlap:      current = [1,6]       // append nothing
Gap:          append [1,6]
              current = [8,10]
Finish:       append [8,10]

Result:       [1,6], [8,10]
```

### Interview proof wording

“My invariant is that the result contains finalized disjoint intervals, while
the current interval represents the last unfinished merged group. Together,
they cover exactly the processed input. Sorting guarantees that once I
encounter a gap, no future interval can reach the current group, so I can
emit it exactly once. Appending the final pending group completes the coverage.”

## Complexity

Sorting costs O(n log n), scanning costs O(n), and total time is O(n log n).
The sorted list uses O(n) extra space. Results and return conversion use O(n)
space in the worst case, so total auxiliary space is O(n).

## Kotlin choices

The LeetCode API requires `Array<IntArray>` for both input and output. Inside
the function, `sortedBy` produces a sorted List and `mutableListOf` accumulates
results; each output interval uses `intArrayOf` to match the judge's row type.
`toTypedArray()` converts the result collection at the return boundary.

Unlike the original Go in-place sorting, this version does not reorder the
input array. The sorted list shares input rows, but never writes to them;
each output row is newly created. Sorting by the left endpoint is sufficient;
equal-left ordering does not matter because `maxOf` preserves the farthest end.

## Interview wording

“I sort the intervals by their left endpoints and keep one current merged
interval. For each next interval, if its left endpoint is at most the current
end, they overlap, so I keep the start and extend the end to the maximum of
the two right endpoints.

If there is a gap, I save the current interval and start a new one. This is
safe because all later intervals start at least as far right, so none can
overlap the interval I just saved. After the loop, I append the last interval.

These are closed intervals, so equal endpoints count as overlap. Sorting
dominates the runtime at O(n log n); my Kotlin implementation uses O(n)
additional space.”

## Local validation

From this folder, run `bash run.sh`. The checks cover the published examples,
containment, equal starts, duplicates, point intervals, disjoint intervals,
a single interval, the traced example, and the defensive empty-input case.
They also verify the input is unchanged. Local checks do not constitute an
online-judge acceptance claim.
