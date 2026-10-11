# Mistake I made: checking the partition, not just the array shape

Problem: find the minimum in a nonempty rotated ascending array with distinct
values. A non-rotated array is also valid input.

## My original reasoning, polished

I recognized that a rotated array has two ascending portions. Comparing each
value with `nums[0]` should let me locate the boundary between them using binary
search. I used `l` and `r` to separate the already classified elements from the
undecided elements, and expected the search to finish at `l = r`.

This was the right structure. The gap was how I assigned equality to the two
portions: I described the first as `>= nums[0]` and the second as `<= nums[0]`.
Those conditions overlap at `nums[0]` itself. Distinct values mean equality
occurs only at index `0`; they do not mean equality never occurs.

## The actual bug: my predicate was not monotone

For a first-true binary search, the predicate must have the pattern
`false ... false, true ... true`, allowing either portion to be empty.

My original condition did not guarantee that:

```text
nums                       [3,     4,     5,     1,    2]
nums[i] <= nums[0]          [true, false, false, true, true]
nums[i] <  nums[0]          [false, false, false, true, true]
```

In particular, my claim that a qualifying midpoint makes every later element
qualify fails at `mid = 0`: `3 <= 3`, but `4 <= 3` is false.

The correction is to assign equality to the first portion only:

- First portion: values `>= nums[0]`.
- Second portion: values `< nums[0]`.

For a genuinely rotated distinct array, the first element of the second portion
is the minimum. Handling non-rotated input separately would not repair the
original predicate: it also fails on rotated input.

## A small counterexample to my original code

Input: `[3, 1, 2]`, with `n = 3`.

| State before iteration | `mid` | Original condition | State after iteration |
| --- | --- | --- | --- |
| `l = 0, r = 3` | 1 | `1 <= 3` is true | `l = 0, r = 1` |
| `l = 0, r = 1` | 0 | `3 <= 3` is true | `l = 0, r = 0` |

The loop ends and returns `nums[0] = 3`; the expected minimum is `1`.
The first incorrect update is the second iteration: index `0` is treated as
belonging to the second portion.

## Solution evolution

A linear scan finds the minimum in O(n) time and O(1) extra space. The two
portions give us more structure: with distinct values, `nums[i] < nums[0]`
changes from false to true at most once. Searching for that transition avoids
examining every element and takes O(log n) time with O(1) extra space.

My original implementation was:

```kotlin
class Solution {
    fun findMin(nums: IntArray): Int {
        val n = nums.size
        var l = 0
        var r = n

        while (l < r) {
            val mid = (l + r) / 2
            if (nums[mid] <= nums[0]) {
                r = mid
            } else {
                l = mid + 1
            }
        }

        return nums[l % n]
    }
}
```

The correction we reached is one condition change:

```kotlin
if (nums[mid] < nums[0]) {
    r = mid
} else {
    l = mid + 1
}
```

With `[3, 1, 2]`, the corrected loop first moves `r` to `1`, then moves `l`
to `1` because `3 < 3` is false. It terminates at `l = r = 1` and returns `1`.

## Why my actual `r = n` initialization was already right

The corrected invariant is:

- Every valid index before `l` has a value `>= nums[0]`.
- Every valid index at or after `r` has a value `< nums[0]`.
- The undecided elements occupy `[l, r)`.

Initially `l = 0` and `r = n`, so both classified regions are empty. My original
comment said `r = n - 1`, but the actual code correctly used `r = n`.

If `nums[mid] < nums[0]`, monotonicity classifies `mid` and every later element
as true, so `r = mid` preserves the invariant. Otherwise, `mid` and every earlier
element are false, so `l = mid + 1` preserves it. Each update strictly shrinks
the undecided interval.

At termination, `l = r` is the first qualifying index, or `n` if none exists.
The midpoint is safe: while `l < r <= n`, the lower midpoint satisfies `mid < n`.

For `[1, 2, 3, 4, 5]`, every predicate result is false:

| State before iteration | `mid` | Update | State after iteration |
| --- | --- | --- | --- |
| `l = 0, r = 5` | 2 | `l = mid + 1` | `l = 3, r = 5` |
| `l = 3, r = 5` | 4 | `l = mid + 1` | `l = 5, r = 5` |

Here the result is the boundary `n`, not an element index. Since no value is
smaller than `nums[0]`, the minimum is at index `0`. My return expression
`nums[l % n]` maps that boundary to index `0`; when `l < n`, it returns `nums[l]`.
This mapping is justified by this problem's structure, not by binary search in
general. It also requires `n > 0`.

Starting with `r = n - 1` would assert that the last element already belongs to
the second portion. That is false for non-rotated input and prevents returning
the no-match boundary `n`.

## What I should remember

Before writing the loop, check the predicate at the anchor itself, and write
out its truth values on a small input. A useful array shape does not automatically
make my chosen comparison monotone. Make the two classifications disjoint,
then align the invariant, initialization, updates, and possible return values.

Interview wording: “I search for the first value strictly smaller than the first
element. For distinct rotated ascending input, that predicate is false and then
true. If it is false everywhere, the array is non-rotated and the minimum is
the first element.”

Recall questions: Why does uniqueness still allow equality at index `0`? Why
does `n` need to be a possible boundary? What justifies mapping that boundary
back to index `0` here?
