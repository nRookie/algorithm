# 128. Longest Consecutive Sequence

## Contract and review

[Official problem](https://leetcode.com/problems/longest-consecutive-sequence/):
given an unsorted integer array, return the length of its longest run of
consecutive values. Input order does not matter, and duplicates do not extend a
run. Return `0` for an empty array. The required time complexity is O(n).

Constraints: `0 <= nums.size <= 100_000` and
`-1_000_000_000 <= nums[i] <= 1_000_000_000`.

**Your implementation is correct under these constraints.** It does not mutate
`nums`. Its two important choices are iterating over distinct values and
expanding only from the first value of a run.

Your code below preserves the algorithm and variable names, with spacing
normalized and an explicit import for `max`. Alternatively, `maxOf(cnt, ans)`
does not require that import.

```kotlin
import kotlin.math.max

class Solution {
    fun longestConsecutive(nums: IntArray): Int {
        val set = nums.toHashSet()
        var ans = 0
        for (num in set) {
            if (num - 1 in set) continue
            var cnt = 0
            var current = num
            while (current in set) {
                cnt++
                current++
            }
            ans = max(cnt, ans)
        }
        return ans
    }
}
```

## Solution evolution

Let `n` be the input length and `u` the number of distinct values.

### 1. Sort, then scan

Sort a copy of the input. For `[100, 4, 200, 1, 3, 2]`, this produces
`[1, 2, 3, 4, 100, 200]`. Equal neighbors are skipped; a difference of one
extends the current run; a larger gap starts a new run.

Sorting groups consecutive values together, so scanning finds every maximal
run. This costs O(n log n) time and O(n) auxiliary space for the copied array.
It is a useful baseline, but does not meet the linear-time requirement.

**What to say:** “Sorting makes consecutive values adjacent, but sorting costs
more than the required linear time. I can use a set to ask whether the next
value exists without sorting.”

### 2. Hash set, but expand from every distinct value

Build a set and, for every value, repeatedly check its successor. This is
correct because starting at the beginning of the longest run will count it.
However, the same run is counted repeatedly: for `[1, 2, 3, 4]`, expansion
lengths are `4, 3, 2, 1`. A run of length `u` produces
`u + (u - 1) + ... + 1` successful checks.

With expected O(1) hash operations, worst-case total work is O(n + u²),
or O(n²), with O(n) auxiliary space for the Kotlin set allocation.

**What to say:** “Fast membership checks remove sorting, but scanning from
every value repeats suffixes of the same run. I need to recognize its start.”

### 3. Your solution: expand only from run starts

If `num - 1` exists, `num` belongs to a run that starts earlier. Skip it.
Otherwise, `num` is the unique smallest value in its run, so count forward.
For the shared example, only `1`, `100`, and `200` start scans.

Different maximal runs are disjoint. Starting exactly once per run means the
inner loops collectively count exactly `u` values, regardless of set order.
This removes repeated suffix scans and gives expected O(n) total time.

**What to say:** “I put the values in a set and scan forward only when the
predecessor is absent. Each distinct value belongs to exactly one scan, so the
total work is linear in expectation, with linear extra space.”

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Sort a copy, then scan | O(n log n) | O(n) |
| Set, expand from every distinct value | Expected O(n + u²) | O(n) |
| Set, expand only from starts | Expected O(n) | O(n) |

## Variables and invariant

| Variable | Meaning |
| --- | --- |
| `set` | All distinct input values; membership is independent of input order |
| `num` | Candidate start of a consecutive run |
| `current` | Next value to check, not an array index |
| `cnt` | Number of values counted in this scan |
| `ans` | Longest completed run so far |

At the top of the inner loop, all values in `[num, current)` have been
counted and exist in the set, and `cnt == current - num`.
If `current` exists, counting it and incrementing `current` preserves this
invariant. The first missing value ends the run.

## Execution trace

Input: `[100, 4, 200, 1, 3, 2]`. Initially `ans = 0`.
Hash-set iteration order is unspecified; use the following possible order for
illustration. The result does not depend on that order.

| `num` | Predecessor present? | Inner scan: `(current, cnt)` before → after each successful iteration | Stop / update |
| --- | --- | --- | --- |
| 100 | No | `(100, 0) → (101, 1)` | 101 missing; `ans = 1` |
| 4 | Yes: 3 | Skip | `ans = 1` |
| 200 | No | `(200, 0) → (201, 1)` | 201 missing; `ans = 1` |
| 1 | No | `(1, 0) → (2, 1) → (3, 2) → (4, 3) → (5, 4)` | 5 missing; `ans = 4` |
| 3 | Yes: 2 | Skip | `ans = 4` |
| 2 | Yes: 1 | Skip | `ans = 4` |
| End | — | Outer loop exhausted | Return `4` |

## Correctness and termination

Partition the distinct input values into maximal consecutive runs. Each run has
exactly one smallest value whose predecessor is absent. The outer loop visits
that value and starts a scan; every other value in the run is skipped.

By the inner-loop invariant, the scan counts exactly the run's values and
stops at the first missing successor. Taking the maximum across all runs
therefore returns the longest run length. If the set is empty, no scan runs
and the initial answer `0` is correct.

The outer loop visits a finite set. Each inner iteration increases `current`,
eventually reaching a missing value beyond its finite run. The problem's
value bounds keep both `num - 1` and the final `current++` within Kotlin's
`Int` range. Supporting arbitrary `Int` values would require overflow guards
or `Long` arithmetic; that is outside this problem's constraints.

## Why the nested loops are linear

- Building the set processes `n` input values.
- The outer loop performs `u` predecessor checks.
- All inner loops together perform `u` successful membership checks.
- Each run contributes one final failed membership check, at most `u` total.

Hash operations take expected O(1), so total time is expected O(n + u) = O(n).
Auxiliary space is O(n): there are `u` stored values, and Kotlin's
`toHashSet()` may reserve capacity based on the original input size. The
remaining variables use O(1) space. Reading the input already requires Ω(n)
work in the worst case, so the expected linear time is asymptotically optimal.

## Edge cases and pitfalls

These are expected results from code review, not executed tests.

| Input | Expected | What it checks |
| --- | --- | --- |
| `[]` | 0 | No iterations |
| `[7]` | 1 | A singleton is a run |
| `[2, 2, 2]` | 1 | Duplicates do not increase length |
| `[1, 0, 1, 2]` | 3 | Duplicate start and unordered values |
| `[-2, 0, -1, 5]` | 3 | Negative values and crossing zero |
| `[1, 2, 4, 5]` | 2 | Gaps separate runs |
| `[-1000000000, 1000000000]` | 1 | Allowed numeric boundaries |

**Keep `for (num in set)`.** Iterating over `nums` instead still produces the
right answer, but can lose the linear-time guarantee. With `k` copies of `1`
followed by `2, 3, ..., k`, every copy of `1` starts the same length-`k` scan:
Θ(k²) work on an input of length `2k - 1`.

**Keep the predecessor check.** Without it, even distinct values in one long
run cause repeated suffix scans. The set and the start check solve different
sources of repeated work.

## Interview explanation and recall

“I need consecutive values regardless of their input positions. Sorting would
work but costs O(n log n), so I build a hash set. A value starts a run exactly
when its predecessor is missing. I scan forward only from those starts and
keep the maximum length. Every distinct value is counted in one run, giving
expected O(n) time and O(n) extra space.”

For later practice:

- Explain the repeated work that remains after adding a hash set alone.
- Explain why skipping a value with a predecessor cannot lose the answer.
- Defend the total inner-loop bound without multiplying the loop lengths.
- Explain why each scan terminates and why duplicate starts must be removed.

Next review: rebuild the solution from “scan each maximal run exactly once,”
then use `[1, 1, 2, 3]` to explain both safeguards against repeated work.
