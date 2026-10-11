# 162. Find Peak Element

## Contract and assumptions

Return the index of any element strictly greater than its neighbors. The
array is nonempty, adjacent elements are unequal, and imaginary neighbors
outside the array have value negative infinity. The array need not be sorted
and may contain multiple peaks. Do not modify the input.

The imaginary values describe comparisons; do not actually access `nums[-1]`
or `nums[n]`, or substitute `Int.MIN_VALUE` for negative infinity: a real
element is allowed to equal `Int.MIN_VALUE`.

Source: [Official problem statement](https://leetcode.com/problems/find-peak-element/).

## Review of your explanation

Your implementation is correct. Your explanation correctly identifies a
linear baseline, the neighbor comparison, and the need to justify access
to `mid + 1`. Three details need refinement:

1. **The goal is to find any peak, not the first descending pair.** The
   predicate `nums[i] > nums[i + 1]` can alternate between true and false.
   This is not a lower-bound search over a monotone predicate.
2. **The midpoint is not always equal to `l`.** For example, `l = 0`,
   `r = 5` gives `mid = 2`. Safety follows from `l <= mid < r`, so
   `mid + 1 <= r < n`.
3. **The linear scan checks neighbors with index boundaries.** Its condition
   is `(i == 0 || nums[i] > nums[i - 1]) &&
   (i == n - 1 || nums[i] > nums[i + 1])`. Check values, not whether index
   `i` is greater than another index, and allow a left neighbor when `i > 0`.

## Solution evolution

### 1. Check each element's neighbors

A straightforward scan checks whether each element is greater than both
neighbors, treating a missing neighbor as negative infinity. Return the first
peak encountered. This takes `O(n)` time and `O(1)` extra space, but does
not meet the problem's logarithmic-time requirement.

For `[1, 3, 2, 4, 5, 1]`, index `1` is the first peak: `3 > 1` and `3 > 2`.

What to say:

> “I can check each element against its neighbors. That is correct, but
> scanning every position takes linear time.”

### 2. Use a local slope to retain a half containing a peak

Compare `nums[mid]` with `nums[mid + 1]`:

- If `nums[mid] > nums[mid + 1]`, keep `[l, mid]`.
- Otherwise, adjacent inequality implies `nums[mid] < nums[mid + 1]`;
  keep `[mid + 1, r]`.

Intuitively, follow the uphill direction. If values keep rising, they reach
a peak at the endpoint; if they start falling, the turning point is a peak.
The boundary invariant below makes this argument valid after every update.

This is an alternative to scanning for the first peak, not an algorithm
that preserves that first peak. Both approaches satisfy the request to
return any peak. Binary search discards about half the candidate interval
per step, giving `O(log n)` time and `O(1)` extra space.

What to say:

> “I do not need the first peak. A middle neighbor comparison lets me keep
> one half that is guaranteed to contain some peak.”

| Approach | Time | Extra space | Result |
| --- | --- | --- | --- |
| Left-to-right neighbor scan | `O(n)` | `O(1)` | First peak encountered |
| Your slope-based binary search | `O(log n)` | `O(1)` | Any peak |

## Your implementation with polished comments

The algorithm is unchanged.

```kotlin
class Solution {
    fun findPeakElement(nums: IntArray): Int {
        val n = nums.size
        var l = 0
        var r = n - 1

        // The inclusive interval [l, r] always contains a peak.
        while (l < r) {
            val mid = l + (r - l) / 2

            // mid < r, so mid + 1 is a valid index.
            if (nums[mid] > nums[mid + 1]) {
                // The left half, including mid, contains a peak.
                r = mid
            } else {
                // Adjacent values differ, so this slope rises.
                // The right half contains a peak.
                l = mid + 1
            }
        }
        return l
    }
}
```

## Why this is not a search for the first descending pair

Consider `[1, 3, 2, 4, 5, 1]`. Comparisons with the next value give:

```text
Index:                    0      1      2      3      4
nums[i] > nums[i + 1]:   false  true   false  false  true
```

There is no single false-to-true boundary. Your code returns index `4`,
although the first descending pair starts at index `1`. Index `4` is valid
because its value `5` is greater than both neighbors `4` and `1`.

A comparison does not prove the discarded half contains no peaks. It proves
the retained half contains at least one, which is enough for this objective.

## Correctness proof: preserve inward-facing boundaries

The inclusive interval `[l, r]` satisfies:

1. `0 <= l <= r < n`.
2. Its left endpoint is greater than its outside left neighbor:
   `l == 0` or `nums[l] > nums[l - 1]`.
3. Its right endpoint is greater than its outside right neighbor:
   `r == n - 1` or `nums[r] > nums[r + 1]`.

### Why these boundaries guarantee a peak

Choose an element with maximum value in `[l, r]`. If either neighbor is
inside the interval, that neighbor cannot be greater; because adjacent
values are unequal, it must be strictly smaller. If a neighbor is outside
the interval, the corresponding boundary condition makes it strictly
smaller as well. Thus, this maximum element is a peak of the original array.

This is an existence proof; the algorithm does not scan for that maximum.

### Initialization

Initially, `[l, r] = [0, n - 1]`. Both outside neighbors are imaginary
negative infinity, so the boundary conditions hold.

### Preservation

If `nums[mid] > nums[mid + 1]`, set `r = mid`. The left boundary is unchanged,
and the comparison establishes the new right boundary condition.

Otherwise, adjacent values are unequal, so `nums[mid + 1] > nums[mid]`.
Set `l = mid + 1`. The right boundary is unchanged, and the comparison
establishes the new left boundary condition.

Both updates therefore retain an interval containing a peak.

### Index safety and termination

When `l < r`, integer division gives:

```text
l <= mid < r
mid + 1 <= r < n
```

Thus `nums[mid + 1]` is safe to access. Updating `r = mid` strictly decreases
`r`; updating `l = mid + 1` strictly increases `l`. Neither update crosses
the pointers. The nonnegative integer `r - l` strictly decreases, so the
loop eventually ends with `l == r`.

### Final result

The remaining interval contains just one element. The preserved boundary
conditions say this element is strictly greater than both neighbors, using
negative infinity at an array endpoint. Therefore, returning `l` is correct.

## Complete execution trace

Input: `[1, 3, 2, 4, 5, 1]`.

| `l` before | `r` before | `mid` | Neighbor comparison | Update and interval afterward |
| --- | --- | --- | --- | --- |
| 0 | 5 | 2 | `2 < 4`: rising | `l = 3`; `[3, 5]` |
| 3 | 5 | 4 | `5 > 1`: falling | `r = 4`; `[3, 4]` |
| 3 | 4 | 3 | `4 < 5`: rising | `l = 4`; `[4, 4]` |
| 4 | 4 | — | — | Stop; return index `4`, value `5` |

The first step discards the earlier peak at index `1`. That is allowed:
the retained interval still contains another peak.

## Boundary cases and complexity

Expected examples illustrate the proof; they are not a substitute for it.

| Input | Result | Reason |
| --- | --- | --- |
| `[7]` | 0 | Loop is skipped; both neighbors are negative infinity |
| `[1, 2, 3]` | 2 | Every comparison rises; last element is a peak |
| `[3, 2, 1]` | 0 | Every comparison falls; first element is a peak |
| `[1, 3, 2, 4, 5, 1]` | 4 | Multiple peaks; the first need not be returned |

The adjacent-inequality assumption matters. With `[2, 2]`, your code would
return index `1`, but neither element is a strict peak. Such input is excluded
by the problem.

Each iteration keeps at most approximately half the interval. Time is
`O(log n)` and auxiliary space is `O(1)`; the input is unchanged.

## Polished interview wording

> “A linear scan could check each element against its neighbors, but I can
> find any peak in logarithmic time by following a local slope.
>
> I maintain an inclusive interval whose endpoints are higher than their
> outside neighbors. This guarantees the interval contains a peak. If the
> middle value is greater than the next value, I keep the left half including
> the middle. Otherwise, adjacent values differ, so the slope rises and I
> keep the right half. Each comparison establishes the new boundary condition.
>
> While the pointers differ, the midpoint is strictly below the right endpoint,
> so reading the next element is safe. The interval shrinks until one element
> remains. The boundary conditions prove that this element is a peak.”

Useful wording refinements:

- “An element strictly greater than its neighbors,” rather than “greater
  than it's neighbors.” `Its` is possessive; `it's` means `it is`.
- “A straightforward approach takes O(n) time,” rather than “O(n) times.”
- “Find a peak by retaining a half that contains one,” rather than “find
  the first index greater than the next element.”
- “The midpoint is strictly less than r, so mid + 1 is in bounds,” rather
  than claiming that the midpoint always equals l.

## Rehearsal questions

1. Why does the retained half contain a peak even if the discarded half does too?
2. Which boundary condition does each update establish?
3. Why is adjacent inequality needed for a strict peak?
4. Explain why this predicate cannot be used as a standard lower-bound predicate.
5. Derive `mid + 1 <= r` from `l < r` without assuming `mid == l`.
