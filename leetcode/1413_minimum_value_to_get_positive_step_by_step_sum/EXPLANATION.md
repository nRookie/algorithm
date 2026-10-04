# 1413. Minimum Value to Get Positive Step by Step Sum

## Problem and saved implementations

Given a nonempty integer array `nums`, choose the smallest positive initial
value. Add the elements in order, keeping the result at least 1 after every
addition. The input does not change. For `[-3,2,-3,4,2]`, the answer is 5.

- [1413.kt](1413.kt): your prefix-sum solution, preserving `n`, `sum`, and `min_x`.
- [dp/1413.kt](dp/1413.kt): the backward minimum-required-value DP we discussed.

Each file independently uses LeetCode's `class Solution` and method signature.
Submit one file at a time. Your supplied active code was correct; formatting
and unused exploratory comments were cleaned up. The DP was introduced during
our discussion, not part of your original solution.

## Solution evolution

### 1. Conceptual baseline: try initial values

Try initial values 1, 2, 3, and so on. For each, scan the array and reject it
as soon as the running value drops below 1. The first successful value is the
minimum because candidates are tested in increasing order. This is a baseline
for comparison, not a claim that you used it.

If the answer is S, this can take O(nS) time and O(1) auxiliary space. It repeats
the same additions for each candidate; increasing the initial value shifts
every running result by the same amount.

What to say: “Trying each initial value works, but repeats the same sequence.
I can calculate its largest cumulative deficit once instead.”

### 2. Your solution: find the smallest cumulative sum

You recorded the prefix sums for `[-3,2,-3,4,2]` as `-3,-1,-4,0,2`. Your code
keeps only their minimum rather than allocating an array of all prefixes:

```kotlin
class Solution {
    fun minStartValue(nums: IntArray): Int {
        val n = nums.size
        var sum = 0
        var min_x = 0
        for (i in 0 until n) {
            sum += nums[i]
            min_x = minOf(sum, min_x)
        }
        return 1 - min_x
    }
}
```

`sum` is the combined change after the elements processed so far. `min_x` is
the smallest such change, including zero before processing any elements.
Including zero ensures that the initial value itself is at least 1, even if
every nonempty prefix is positive.

For any prefix, the actual running result is:

```text
initial value + prefix sum
```

The smallest result is therefore `initial value + min_x`. Requiring that result
to be at least 1 gives `initial value >= 1 - min_x`. Returning exactly that
bound is both sufficient and minimal. An intermediate deficit still matters
even if the final sum is positive.

Complete trace:

```text
index:  0  1  2  3  4
nums:  -3  2 -3  4  2
```

Initially `sum = 0`, `min_x = 0`.

| i | nums[i] | sum before | sum after addition | min_x after comparison |
| --- | --- | --- | --- | --- |
| 0 | -3 | 0 | -3 | -3 |
| 1 | 2 | -3 | -1 | -3 |
| 2 | -3 | -1 | -4 | -4 |
| 3 | 4 | -4 | 0 | -4 |
| 4 | 2 | 0 | 2 | -4 |

The loop ends and returns `1 - (-4) = 5`. With initial value 5, the results
are `2,4,1,5,7`. Initial value 4 would produce 0 at index 2 and fail.

The invariant is that `sum` describes all processed elements and `min_x`
describes their smallest prefix, including the empty one. Adding the next
element and taking the smaller minimum preserves those meanings. The finite
scan visits each element once: O(n) time and O(1) auxiliary space.

What to say: “The initial value shifts every prefix by the same amount. I find
the smallest prefix sum, including zero, and return enough to shift it to 1.”

### 3. Alternative DP: calculate what the remaining suffix requires

This is an alternative explanation, not an improvement over your solution's
complexity. Define:

```text
dp[i] = minimum value needed before adding nums[i], so that processing
        nums[i] through nums[n - 1] keeps the value at least 1.
```

The value immediately before processing must also be at least 1: it is either
the positive initial value or the result of the preceding addition.
At boundary n, no elements remain, but the value must still be at least 1:
`dp[n] = 1`.

To process the current element and then the remaining suffix:

```text
value before nums[i] + nums[i] >= dp[i + 1]
value before nums[i] >= dp[i + 1] - nums[i]
```

Combining that requirement with the lower bound 1 gives:

```kotlin
dp[i] = maxOf(1, dp[i + 1] - nums[i])
```

Implementation:

```kotlin
class Solution {
    fun minStartValue(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n + 1)

        // After processing everything, the value must still be at least 1.
        dp[n] = 1

        for (i in n - 1 downTo 0) {
            dp[i] = maxOf(1, dp[i + 1] - nums[i])
        }

        return dp[0]
    }
}
```

For the same input `[-3,2,-3,4,2]`, initialize `dp[5] = 1`:

| i | nums[i] | dp[i + 1], required after addition | Calculation | dp[i] |
| --- | --- | --- | --- | --- |
| 4 | 2 | 1 | max(1, 1 - 2) | 1 |
| 3 | 4 | 1 | max(1, 1 - 4) | 1 |
| 2 | -3 | 1 | max(1, 1 - (-3)) | 4 |
| 1 | 2 | 4 | max(1, 4 - 2) | 2 |
| 0 | -3 | 2 | max(1, 2 - (-3)) | 5 |

The final table is `[5,2,4,1,1,1]`; return `dp[0] = 5`. These entries are
minimum values required before each suffix, not the actual running values
of a forward simulation starting at 5.

**Correctness:** The base requirement at n is 1. Assuming `dp[i + 1]` is the
exact minimum for the remaining suffix, the recurrence selects the smallest
value that is at least 1 before the current addition and leaves enough after
it. A smaller value violates one of those requirements. Thus each entry is
correct by backward induction, including the returned initial requirement.

Iterate right to left because `dp[i + 1]` must be ready before calculating
`dp[i]`. The loop visits n elements and terminates: O(n) time and O(n) auxiliary
space for the stored table. Since only the next entry is needed, the table
could be compressed to one running requirement; this is a further storage
improvement, not another saved implementation.

What to say: “I work backward, asking how much value is needed before this
element to leave enough for the suffix. I subtract the element from the next
requirement and enforce the minimum value of 1.”

## How this relates to Gas Station DP

Both use the same requirement calculation:

```text
required now = max(minimum allowed, required afterward - current change)
```

| Part | 1413 | Gas Station DP |
| --- | --- | --- |
| Current change | `nums[i]` | `gas[i] - cost[i]` |
| Required afterward | `dp[i + 1]` | `dp[k - 1][next]` |
| Minimum allowed | 1 | 0 |
| State meaning | Requirement before the suffix at i | Requirement before k trips starting at i |

In 1413, i determines the entire remaining suffix, so one index identifies
the subproblem. On a circular route, a station alone does not specify how
many trips remain; the Gas Station DP also stores k.

The prefix solution answers “how far did the cumulative change drop?” The DP
answers “how much do the remaining elements require?” They compute the same
minimum initial value from opposite directions. The
[Gas Station DP](../134_gas_station/dp/EXPLANATION.md) uses the latter view;
the linear Gas Station solution instead eliminates candidates greedily.

| Saved approach | Time | Auxiliary space |
| --- | --- | --- |
| Your running prefix minimum | O(n) | O(1) |
| Backward DP table | O(n) | O(n) |

## Verification

Both Kotlin files compiled independently and each passed 9 example/boundary
cases plus 3,905 exhaustive small cases: all arrays of lengths 1–5 with values
from -2 through 2. An independent baseline tried initial values in increasing
order and simulated every addition until it found the first valid candidate.
The fixed cases include the standard examples, one-element inputs, zeros,
all-positive and all-negative inputs, and an early deficit followed by a
positive final sum. These are observed checks; the proofs above justify the
methods for every valid input.

## Recall

Recall questions: Why include zero in `min_x`? Why is the DP's lower bound 1
rather than 0? Why must we fill it right to left? How is `dp[i]` different
from the actual value after processing index i?
