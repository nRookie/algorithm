# 34. Find First and Last Position of Element in Sorted Array

## Contract

Given an integer array sorted in nondecreasing order, return the first and
last indexes of `target`. Return `[-1, -1]` if the target is absent. The
array may be empty and may contain duplicates. Do not modify the input.

Let `n = nums.size`. The required time is `O(log n)` for nonempty input.

## Solution evolution

### 1. Scan and record matching indexes

A straightforward scan records the first matching index and updates the
last matching index whenever another match appears. If there are no matches,
return `[-1, -1]`. This takes `O(n)` time and `O(1)` auxiliary space, but
does not meet the required logarithmic time.

For `[5,7,7,8,8,10]`, target `8`, the answer is `[3,4]`.

What to say:

> “I could scan for all matches and record their first and last indexes,
> but sorted order lets me find those boundaries without scanning.”

### 2. Binary search both boundaries

In sorted order, equal values occupy one consecutive block:

```text
[ values < target ][ values == target ][ values > target ]
                   ^                  ^
                  first              last
```

Search separately for the first value `>= target` and the last value
`<= target`. Check that the first candidate equals the target before
performing the second search. This takes `O(log n)` time and `O(1)` space.

What to say:

> “I search for the first value at least the target and verify equality.
> Once I know the target exists, the last value at most the target is its
> last occurrence.”

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Scan for matches | `O(n)` | `O(1)` |
| Two boundary searches | `O(log n)` | `O(1)` |

## Your explanation, polished

Your first partition was correct:

```text
[ values < target ][ values >= target ]
```

If `nums[mid] >= target`, all elements at or after mid also qualify. Keep
mid as a possible first index by setting `r = mid`. Otherwise, all elements
through mid are too small, so set `l = mid + 1`.

Your second partition needs a correction: the smaller values come first,
not the greater values.

```text
[ values <= target ][ values > target ]
```

If `nums[mid] <= target`, every element at or before mid also qualifies.
Keep mid as a possible last index by setting `l = mid`. Otherwise, all
elements from mid onward are too large, so set `r = mid - 1`.

Both searches use inclusive candidate bounds `[l, r]` and stop with one
candidate. A terminal candidate is not automatically a match; the first
search's equality check is essential.

## Your implementation

Your submitted logic is correct. Formatting and comments are polished below.

```kotlin
class Solution {
    fun searchRange(nums: IntArray, target: Int): IntArray {
        val n = nums.size
        if (n == 0) return intArrayOf(-1, -1)

        var l = 0
        var r = n - 1

        // Find the first value >= target, or stop at the last
        // index if no value qualifies.
        while (l < r) {
            val mid = l + (r - l) / 2
            if (nums[mid] >= target) {
                r = mid
            } else {
                l = mid + 1
            }
        }
        val left = l
        if (nums[left] != target) return intArrayOf(-1, -1)

        l = 0
        r = n - 1
        // The target exists. Find the last value <= target.
        while (l < r) {
            val mid = (l + r + 1) / 2
            if (nums[mid] <= target) {
                l = mid
            } else {
                r = mid - 1
            }
        }
        return intArrayOf(left, r)
    }
}
```

An arithmetic refinement, without changing the algorithm, is to replace
the second midpoint formula with:

```kotlin
val mid = l + (r - l + 1) / 2
```

Both choose the upper midpoint, but the latter avoids adding the endpoints.
Your original expression is safe for this exercise's array sizes.

## Step-by-step correctness proof

### 1. Find the first qualifying index

Maintain:

- Every value before l is smaller than the target.
- Every value strictly after r is greater than or equal to the target.
- If a first qualifying index exists, it remains in `[l, r]`.

Initially both outside regions are empty, and any qualifying index lies in
the whole array. A smaller midpoint value excludes every index through mid;
a qualifying midpoint value allows the first qualifying index to be at mid
or earlier. Sorted order therefore preserves the statements after either
update.

At convergence, if a first qualifying index exists, it is the sole candidate.
If none exists, every comparison moves l right while r stays at `n - 1`,
so the search instead stops at the last index.

### 2. Verify that the target exists

If the candidate equals the target, it must be the first occurrence: every
earlier value is smaller. If it is greater, no earlier index equals the
target, and no later value can equal it either. If it is smaller, all values
are smaller and no qualifying index exists. Thus the equality check correctly
rejects every absent target.

### 3. Find the last qualifying index

After the equality check passes, at least one value `<= target` exists.
Let q be the last such index. Maintain:

- Every value strictly before l is less than or equal to the target.
- Every value strictly after r is greater than the target.
- q remains in `[l, r]`.

If `nums[mid] <= target`, sorted order implies `q >= mid`, so `l = mid`
retains q. Otherwise, every value at or after mid is too large, so
`q < mid` and `r = mid - 1` retains q. At convergence, `l == r == q`.

Since the target exists and the array is sorted, this last qualifying value
equals the target. Any smaller qualifying value would occur before the
known target occurrence, not after it. Thus q is the last occurrence.

### 4. Termination and midpoint choice

The first loop uses the lower midpoint. While `l < r`, `l <= mid < r`, so
either `r = mid` or `l = mid + 1` strictly shrinks the interval.

The second loop uses the upper midpoint. While `l < r`, `l < mid <= r`, so
either `l = mid` or `r = mid - 1` strictly shrinks the interval.

Neither loop crosses its pointers, and both eventually stop with `l == r`.

Why the second loop cannot use the lower midpoint: for `[8,8]`, with
`l = 0`, `r = 1`, the lower midpoint is 0. The qualifying branch sets
`l = mid = 0`, making no progress and repeating forever. The upper midpoint
is 1 and correctly moves l to 1.

## Complete execution trace

Input: `[5,7,7,8,8,10]`, target `8`.

| Search | `l` before | `r` before | `mid` | Value | Update or result |
| --- | --- | --- | --- | --- | --- |
| First | 0 | 5 | 2 | 7 | `l = 3` |
| First | 3 | 5 | 4 | 8 | `r = 4` |
| First | 3 | 4 | 3 | 8 | `r = 3` |
| First | 3 | 3 | — | 8 | Stop; `left = 3`; equality passes |
| Last | 0 | 5 | 3 | 8 | `l = 3` |
| Last | 3 | 5 | 4 | 8 | `l = 4` |
| Last | 4 | 5 | 5 | 10 | `r = 4` |
| Last | 4 | 4 | — | 8 | Stop; return `[3,4]` |

## Boundary examples and complexity

| Input | Target | Expected result | What it checks |
| --- | --- | --- | --- |
| `[]` | 8 | `[-1,-1]` | Empty input guard |
| `[8]` | 8 | `[0,0]` | Both loops skipped |
| `[8,8]` | 8 | `[0,1]` | Upper midpoint in the second loop |
| `[5,7,7,8,8,10]` | 6 | `[-1,-1]` | First qualifying value is greater |
| `[5,7,7,8,8,10]` | 11 | `[-1,-1]` | No qualifying value; stop at last index |

These expected examples illustrate the proof rather than replace it.
Two sequential logarithmic searches take `O(log n)` time in total, with
`O(1)` auxiliary space and a constant-size result. Empty input returns in
constant time. No input mutation or copying occurs.

## Interview explanation

> “Since the array is sorted, all occurrences of the target are consecutive.
> I use two binary searches. The first finds the first value greater than or
> equal to the target, and I check equality there to establish that it exists.
> The second finds the last value less than or equal to the target, which
> must be its last occurrence. I use an upper midpoint in the second search
> because moving the left boundary retains the midpoint. Each search halves
> its interval, so total time is logarithmic and extra space is constant.”

For prepositions and reusable wording, see
[Algorithm interview phrases](../../study-notes/algorithm-interview-phrases.md#prepositions-for-positions-ranges-and-updates).

## Rehearsal questions

1. Why do equal values occupy a consecutive block in a sorted array?
2. Why does the second search use `<= target`, rather than `< target`?
3. Why is the existence check needed before the second search?
4. Explain the two-candidate infinite loop caused by using a lower midpoint
   with `l = mid`.
5. State both partitions and explain which endpoint each search retains.
