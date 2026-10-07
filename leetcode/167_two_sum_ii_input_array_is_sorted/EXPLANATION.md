# Two Sum II — Input Array Is Sorted

## Contract and implementation review

Find two distinct elements in a non-decreasing array whose sum equals `target`.
Return their **1-based indexes**, in increasing order. Exactly one solution is
guaranteed, and the solution must use constant extra space.
Source: [LeetCode 167](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/).

Your pointer movement and `left < right` condition are correct. The condition
prevents using the same element twice. The implementation needs one correction:
`intArrayOf(left, right)` returns zero-based indexes. For `[2, 7, 11, 15]` and
target `9`, your code finds indexes `[0, 1]`, but the required answer is `[1, 2]`.

The fallback return after the loop is unreachable under the problem's guarantee.
An explicit error makes that assumption clear instead of returning an invalid pair.

## Your reasoning, polished

“A hash map can solve Two Sum in expected O(n) time, but it uses O(n) extra space
and does not take advantage of the sorted input. Since this array is sorted,
I can start one pointer at each end and compare their sum with the target.
If the sum is too small, I move the left pointer right. If it is too large,
I move the right pointer left. If it matches, I return both indexes plus one.”

This captures your original reasoning. To make it sufficient for an interview,
add **why those moves cannot discard the solution**. Moving a pointer may leave
the sum unchanged when values repeat; non-decreasing does not mean strictly increasing.

## Solution evolution

Let n be the array length.

| Approach | Method | Time | Extra space |
| --- | --- | --- | --- |
| Brute force | Check every pair of distinct indexes | O(n²) | O(1) |
| Hash map | Look for the current value's complement among previously seen values | O(n) expected | O(n) |
| Two pointers | Use sorted order to eliminate one endpoint per step | O(n) | O(1) |

Brute force works because it examines every possible pair, but repeats many
comparisons. A hash map avoids that repeated search by storing seen values and
their indexes. Looking up the complement before inserting the current element
prevents reusing the same element. This is a useful baseline, but its space use
violates this problem's constant-space requirement.

Sorted order lets us eliminate an entire group of pairs with one comparison,
so we can replace the map with two pointers.

**What to say:** “Checking every pair takes quadratic time. A hash map improves
that to expected linear time with linear space. The sorted input lets me reach
linear time with constant space by ruling out one endpoint after each comparison.”

## Why each pointer move is safe

`left` and `right` are zero-based indexes bounding the remaining candidates.
The invariant is: **the solution's two indexes remain inside `[left, right]`.**

- If `numbers[left] + numbers[right] < target`, every possible partner for
  `left` inside the interval is at most `numbers[right]`. Thus every pair using
  `left` is too small. We can safely discard `left` with `left++`.
- If `numbers[left] + numbers[right] > target`, every possible partner for
  `right` inside the interval is at least `numbers[left]`. Thus every pair using
  `right` is too large. We can safely discard `right` with `right--`.
- If the sum equals `target`, we have found the pair. Convert the indexes to
  the required 1-based form.

Initially, all indexes are candidates. Each unsuccessful iteration preserves
the invariant and decreases `right - left` by one. Since a solution exists,
we find it before the pointers meet.

## Kotlin implementation

This keeps your algorithm and variable names, corrects the returned indexes,
and replaces the unreachable fallback with an explicit error.

```kotlin
class Solution {
    fun twoSum(numbers: IntArray, target: Int): IntArray {
        var left = 0
        var right = numbers.size - 1

        while (left < right) {
            val sum = numbers[left] + numbers[right]
            if (sum < target) {
                left++
            } else if (sum > target) {
                right--
            } else {
                return intArrayOf(left + 1, right + 1)
            }
        }

        error("The problem guarantees exactly one solution")
    }
}
```

The original implementation returned `intArrayOf(left, right)` both when it
found a match and after the loop. Its search logic is otherwise unchanged.

## Dry run

For `numbers = [1, 2, 4, 7, 11]`, `target = 9`:

| State before comparison: left | right | Values | Sum | Action / next state |
| --- | --- | --- | --- | --- |
| 0 | 4 | 1 + 11 | 12 | Too large: right becomes 3 |
| 0 | 3 | 1 + 7 | 8 | Too small: left becomes 1 |
| 1 | 3 | 2 + 7 | 9 | Return `[2, 4]`; pointers stay at 1 and 3 |

## Complexity and spoken explanation

Each unsuccessful iteration moves one pointer inward, so there are at most
n − 1 comparisons: O(n) time. The pointers and sum use O(1) auxiliary space;
the returned array also has a fixed size. The input is not modified.

“I place a pointer at each end. If the sum is too small, even the largest
remaining partner cannot make the left value work, so I discard it. If the sum
is too large, even the smallest remaining partner cannot make the right value
work, so I discard it. Otherwise I return the two indexes plus one. Each pointer
only moves inward, giving O(n) time and O(1) extra space.”

## Review later

- Why does a sum that is too small rule out every pair using `left`?
- Why must the loop use `left < right`?
- Predict the answers for `[3, 3]`, target `6`, and `[-3, -1, 2, 5]`, target `2`.
  They are `[1, 2]` and `[1, 4]`; duplicates and negative values do not break the proof.
- Would the elimination argument still hold for an unsorted array? Explain which
  ordering assumption would be lost.

The official value bounds keep the sum within Kotlin's `Int` range. For a version
accepting arbitrary `Int` values, widen the addition to `Long` before comparing.
The review above is based on the code and correctness argument; no Kotlin runner
was executed when saving these notes.
