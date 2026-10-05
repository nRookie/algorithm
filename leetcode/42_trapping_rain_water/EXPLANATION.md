# 42. Trapping Rain Water

Given an array of non-negative bar heights, where each bar has width 1, return
the total amount of trapped rainwater. The implementation below does not modify
the input. In an interview, clarify the height and length bounds so you know
whether the total fits in `Int`; also clarify whether an empty input is possible.

## Your implementation

This preserves your algorithm and variable names, with shorter explanatory
comments. The two different comparisons are intentional.

```kotlin
class Solution {
    fun trap(height: IntArray): Int {
        val n = height.size
        var hi = 0
        var sum = 0
        var ss = 0

        // Count segments closed by an equally tall or taller right boundary.
        for (i in 1 until n) {
            if (height[i] < height[hi]) {
                ss += height[hi] - height[i]
            } else {
                sum += ss
                ss = 0
                hi = i
            }
        }

        // Discard unconfirmed water and start from the right boundary.
        ss = 0
        hi = n - 1
        for (i in n - 2 downTo 0) {
            if (height[i] <= height[hi]) {
                ss += height[hi] - height[i]
            } else {
                // Require a strictly taller boundary to avoid double counting.
                sum += ss
                ss = 0
                hi = i
            }
        }

        return sum
    }
}
```

| Variable | Meaning |
|---|---|
| `hi` | Index of the tallest boundary encountered so far in the current scan |
| `ss` | Pending water volume measured against that boundary's height |
| `sum` | Total water volume confirmed by completed segments |
| `i` | Index currently being examined |

`hi` is an index; `height[hi]` is a height. `ss` is a volume, not a height.
Because every bar has width 1, a height difference contributes the same numerical
amount to the volume.

## Your reasoning, polished

This is a polished account of the reasoning you supplied.

> I first work through an example. During a left-to-right scan, I keep track of
> the tallest boundary seen so far. If the current bar is lower than that
> boundary, the difference in height is potential water above this bar. I add
> that difference to a temporary total.
>
> This water is not confirmed yet: I still need a right boundary that is at
> least as tall as the current left boundary. When I find one, I add the
> temporary total to the answer, reset it, and use the current bar as the new
> boundary.
>
> At the end of this scan, some potential water may remain unconfirmed because
> there was no sufficiently tall right boundary. I discard that temporary
> total and scan from right to left to count the remaining water using a right
> boundary instead.
>
> If both scans accepted equal-height closing boundaries, they could count the
> same water twice. Therefore, the forward scan accepts an equally tall or
> taller boundary, while the reverse scan accepts only a strictly taller one.
>
> Each bar is visited at most twice, so the time complexity is O(n). I use a
> constant number of variables, so the auxiliary space complexity is O(1).

Two corrections to the original comments:

- The forward update should read `lhi = i`, not `lss = i`. Your code already
  updates the correct variable, `hi`.
- In the reverse scan of your example, index 8 has the same height as the
  boundary at index 10. Your final code keeps the pending water and commits it
  only when it reaches the taller bar at index 7.

## Solution evolution

The underlying rule is that the water above a bar is limited by the shorter of
the tallest boundaries on its two sides:

```text
water[i] = min(leftMax[i], rightMax[i]) - height[i]
```

Here, both maxima include index `i`, so the expression is non-negative.

### 1. Compute both maxima separately for every bar

For each index, search its left and right sides for the tallest bars, then apply
the formula. This is correct, but repeatedly searches overlapping ranges.
It takes O(n²) time and O(1) auxiliary space.

What to say: “For each bar, I find the tallest boundary on each side. The
shorter boundary determines the water level.”

### 2. Precompute prefix and suffix maxima

The searches overlap, so compute all left maxima in one forward pass and all
right maxima in one backward pass. Then apply the formula to every index.
This takes O(n) time and O(n) auxiliary space for the arrays.

What to say: “I can avoid repeating the searches by precomputing the maximum
height from each direction.”

### 3. Your approach: confirm entire segments

When a closing boundary is at least as tall as the current boundary, every bar
between them can be evaluated using the current boundary's height. Instead of
storing maxima for every position, accumulate these differences in `ss` and
commit them when the segment closes.

For `[2, 0, 2]`, the forward scan accumulates `2 - 0 = 2`, then confirms it when
the second height-2 boundary is reached. For `[3, 0, 2]`, the forward scan cannot
confirm a water level of 3; the reverse scan correctly confirms a water level
of 2 instead.

This preserves O(n) time and reduces auxiliary space to O(1).

What to say: “I can accumulate water for a whole segment and confirm it once
a sufficiently tall closing boundary appears. A reverse scan handles the
remaining side.”

| Approach | Time | Auxiliary space |
|---|---|---|
| Search both sides for every bar | O(n²) | O(1) |
| Prefix and suffix maximum arrays | O(n) | O(n) |
| Your two directional scans | O(n) | O(1) |

## Why the implementation works

### Pending water becomes valid when the segment closes

During the forward scan, `hi` identifies a tallest bar seen so far. Every bar
accumulated into `ss` is lower than `height[hi]`. Therefore, `ss` is exactly the
volume needed to fill the current segment to that boundary's height.

When a bar with height at least `height[hi]` appears, the right boundary is tall
enough to support that water level. The tallest boundary to the left is still
`height[hi]`, so that height is also the limit. Adding `ss` is therefore exact.

The reverse scan follows the same argument with left and right exchanged.
Equal-height bars contribute zero to `ss` and do not reset it in this scan.

### The scans cover all water without overlap

Let `m` be the index of the **rightmost global maximum**.

The forward scan commits every segment up to `m`. Because it accepts equality,
it also commits water between equal global maxima. After `m`, no bar can close
another segment, so the forward scan counts no water to its right.

The reverse scan commits every segment from the right end back to `m`. All
bars to the right of `m` are strictly shorter than the global maximum, so `m`
closes its remaining segment. After reaching `m`, no strictly taller bar exists,
so the reverse scan commits nothing further.

Thus, the forward scan counts water to the left of `m`, and the reverse scan
counts water to its right. The bar at `m` holds no water. Every contribution is
counted exactly once.

### Why equality must be handled differently

For `[2, 0, 2]`, the forward scan commits 2 units. The reverse scan accumulates
2 units but never finds a strictly taller closing boundary, so it leaves them
uncommitted. The answer remains 2.

If both scans committed on equality, the answer would be 4. If neither did,
the answer would be 0. In this implementation, one direction owns equality.

## Trace of your example

```text
height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
```

All variable values in the tables are **after** the listed action. “Commit”
means add `ss` to `sum`, reset `ss`, and set `hi = i`.

### Left to right

| `i` | `height[i]` | Action | `hi` | `ss` | `sum` |
|---|---|---|---|---|---|
| — | — | Initialize | 0 | 0 | 0 |
| 1 | 1 | Commit 0 | 1 | 0 | 0 |
| 2 | 0 | Accumulate 1 | 1 | 1 | 0 |
| 3 | 2 | Commit 1 | 3 | 0 | 1 |
| 4 | 1 | Accumulate 1 | 3 | 1 | 1 |
| 5 | 0 | Accumulate 2 | 3 | 3 | 1 |
| 6 | 1 | Accumulate 1 | 3 | 4 | 1 |
| 7 | 3 | Commit 4 | 7 | 0 | 5 |
| 8 | 2 | Accumulate 1 | 7 | 1 | 5 |
| 9 | 1 | Accumulate 2 | 7 | 3 | 5 |
| 10 | 2 | Accumulate 1 | 7 | 4 | 5 |
| 11 | 1 | Accumulate 2 | 7 | 6 | 5 |
| — | — | Discard pending 6; initialize reverse scan | 11 | 0 | 5 |

### Right to left

| `i` | `height[i]` | Action | `hi` | `ss` | `sum` |
|---|---|---|---|---|---|
| — | — | Start reverse scan | 11 | 0 | 5 |
| 10 | 2 | Commit 0 | 10 | 0 | 5 |
| 9 | 1 | Accumulate 1 | 10 | 1 | 5 |
| 8 | 2 | Equal height: accumulate 0 | 10 | 1 | 5 |
| 7 | 3 | Commit 1 | 7 | 0 | 6 |
| 6 | 1 | Accumulate 2 | 7 | 2 | 6 |
| 5 | 0 | Accumulate 3 | 7 | 5 | 6 |
| 4 | 1 | Accumulate 2 | 7 | 7 | 6 |
| 3 | 2 | Accumulate 1 | 7 | 8 | 6 |
| 2 | 0 | Accumulate 3 | 7 | 11 | 6 |
| 1 | 1 | Accumulate 2 | 7 | 13 | 6 |
| 0 | 0 | Accumulate 3 | 7 | 16 | 6 |
| — | — | Return `sum`; pending 16 is never committed | 7 | 16 | 6 |

Pending water can include positions already counted by the other scan. This is
safe because it contributes to the answer only when committed.

## Interview explanation: about one minute

> I use two directional scans and a temporary total for potential water.
>
> In the forward scan, I track the tallest boundary seen so far. For each lower
> bar, I add the height difference to the temporary total. When I find an
> equally tall or taller bar, it closes the segment, so I add that temporary
> total to the answer and start a new segment.
>
> Any unfinished segment may lack a tall enough right boundary, so I discard
> its temporary total and scan from right to left. In this direction, I commit
> only when I find a strictly taller bar. That prevents equal-height boundaries
> from causing double counting.
>
> The forward scan counts water to the left of the rightmost global maximum,
> and the reverse scan counts water to its right. Each bar is visited at most
> twice, so the algorithm takes O(n) time and O(1) auxiliary space.

## Useful wording

| Original wording or idea | Natural interview wording |
|---|---|
| “left side highest wall” | “the tallest boundary seen so far” |
| “there is a possibility we could trap one water” | “this bar could hold one unit of water if a sufficiently tall right boundary appears” |
| “we can stop consider the previous wall” | “the current bar becomes the new boundary” |
| “add the sub sum to sum” | “add the temporary total to the answer” or “commit the pending water” |
| “there is a duplication” | “we could count the same water twice” |
| “the two wall is not equal” | “the closing boundary must be strictly taller” |
| “each element is traversed twice” | “each bar is visited at most twice” |

Use “bar” for an array element and “boundary” for a bar that limits the water
level. Say “units of water” when discussing volume.

## Complexity and validation

Each loop advances through the array once and does constant work per iteration.
Both terminate after at most `n - 1` iterations. Total time is O(n), and auxiliary
space is O(1); there are no extra arrays or recursive calls.

The Kotlin code block above was extracted, compiled, and checked against the
per-position formula on 87,381 arrays of lengths 0–8 with heights 0–3; all
matched. The supplied example returned 6. The validation harness was kept in a
temporary directory, separate from the submission code. These checks support
the implementation, while the argument above establishes why it works.

Useful boundary cases include `[2, 0, 2]` (2), `[3, 0, 2]` (2), `[2, 0, 3]` (2),
and `[3, 0, 3, 0, 3]` (6), plus increasing, decreasing, and flat arrays (0).
The loops also return 0 for empty, one-bar, and two-bar inputs without accessing
an invalid index.

## Rehearsal questions

1. Why is `ss` only potential water until a closing boundary appears?
2. Why can the prefix/suffix maxima approach avoid repeated searches, and how
   does your approach avoid storing those arrays?
3. Why does the forward scan use `>=` to commit, while the reverse uses `>`?
4. Why does resetting `ss` between scans preserve the final answer?
5. Explain how the rightmost global maximum separates the scans' contributions.

Try explaining `[3, 0, 2]` aloud using “pending water,” “closing boundary,” and
“confirmed water,” then reconstruct the two comparisons from `[2, 0, 2]`.
