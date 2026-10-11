# 33. Search in Rotated Sorted Array

## Contract

Given a nonempty array of distinct integers that was originally sorted in
ascending order and may have been rotated, return the target's index or `-1`
if it is absent. The required time is `O(log n)`, where `n = nums.size`.
The input is not modified.

Source: [Official problem statement](https://leetcode.com/problems/search-in-rotated-sorted-array/).

## Solution evolution

### 1. Linear scan

Check each element for equality with the target. This takes `O(n)` time and
`O(1)` extra space. It works regardless of rotation, but does not meet the
required time bound.

For `[4,5,6,7,0,1,2]`, target `1`, the scan eventually returns index `5`.

What to say:

> “A linear scan is straightforward, but it ignores the sorted structure
> that remains after rotation.”

### 2. Locate a split, then search the sorted portions

Your approach identifies where values change from being at least `nums[0]`
to being smaller than it. Then it binary searches the sorted portions.

```text
Indexes:             0  1  2  3 | 4  5  6
Values:              4  5  6  7 | 0  1  2
nums[i] >= nums[0]:   T  T  T  T | F  F  F
                                 ^
                                turn
```

Each portion is ascending, although the whole array is not. The classification
has a single boundary, so binary search can locate it without scanning.

What to say:

> “Rotation divides the array into two sorted portions. Comparing values
> with the first element identifies which portion they belong to, so I can
> locate the split and then search the portions.”

| Approach | Time | Extra space |
| --- | --- | --- |
| Linear scan | `O(n)` | `O(1)` |
| Your split search plus two target searches | `O(log n)` | `O(1)` |

The second approach improves time without allocating or sorting anything.

## Your reasoning, polished and corrected

Your useful starting ideas were to find the drop caused by rotation and to
binary search the two ascending portions. Your implementation is correct,
but its explanation needs these qualifications:

- The first portion's values are **greater than or equal to** `nums[0]`,
  not all strictly greater. Index `0` equals itself, even with distinct values.
- A midpoint in the second portion does not imply that every value between
  `l` and `mid` is smaller than `nums[0]`: that interval may cross the split.
  Instead, all values **at or after** that midpoint belong to the smaller
  second portion.
- For an unrotated array, no value is smaller than `nums[0]`. Your first
  search returns `n - 1`, which is a useful split for this implementation,
  but is not the minimum element's index or a genuine rotation point.
- Your first target search inspects the sorted prefix `[0, turn)`. It does
  not binary search the generally unsorted inclusive range `[0, turn]`.
  Index `turn` is a possible terminal boundary, checked only afterward.

## Your implementation with polished comments

The submitted logic is preserved; formatting and comments are refined.

```kotlin
class Solution {
    fun search(nums: IntArray, target: Int): Int {
        val n = nums.size
        var l = 0
        var r = n - 1

        // Find the first index with value < nums[0],
        // or stop at the last index if no such value exists.
        while (l < r) {
            val mid = l + (r - l) / 2
            if (nums[mid] >= nums[0]) {
                l = mid + 1
            } else {
                r = mid
            }
        }
        val turn = l

        // Lower bound in the sorted prefix [0, turn).
        // The result may be the boundary turn.
        l = 0
        r = turn
        while (l < r) {
            val mid = l + (r - l) / 2
            if (nums[mid] >= target) {
                r = mid
            } else {
                l = mid + 1
            }
        }
        if (nums[l] == target) return l

        // Search the sorted suffix [turn, n - 1].
        // If no element qualifies, stop at the last index.
        l = turn
        r = n - 1
        while (l < r) {
            val mid = l + (r - l) / 2
            if (nums[mid] >= target) {
                r = mid
            } else {
                l = mid + 1
            }
        }
        if (nums[l] == target) return l
        return -1
    }
}
```

## Step 1: Prove the split search

### Why comparison with the first value gives one boundary

A genuine rotation moves a suffix of the original ascending array to the
front. Every value in that moved suffix is at least its first value,
`nums[0]`. Every value in the original prefix, now placed at the back, is
smaller than `nums[0]`. This establishes the `true ... true, false ... false`
classification shown above.

The invariants are:

- `0 <= l <= r < n`.
- Every element before `l` is at least `nums[0]`.
- Every element strictly after `r` is smaller than `nums[0]`.

Initially both outside regions are empty. If `nums[mid] >= nums[0]`, the
classification tells us every earlier index has that property too. Setting
`l = mid + 1` preserves the left invariant. Otherwise, every later index
is also in the smaller portion, so `r = mid` preserves the right invariant.

If a first smaller index `p` exists, it remains in `[l, r]`: the first
branch implies `p > mid`, and the second implies `p <= mid`. When the
pointers meet, they must therefore equal `p`.

If no smaller index exists, every iteration increases `l`; `r` never moves
from `n - 1`. The pointers meet there. For a one-element array, they already
meet at `0` and the loop is skipped.

### What `turn` means

```text
Genuine rotation: turn = minimum element's index.
No rotation:      turn = last element's index.
```

Both cases give an ascending prefix `[0, turn)` and ascending suffix
`[turn, n)`. This is the property the subsequent searches need.

## Step 2: Prove the prefix search

The prefix contains element indexes `0` through `turn - 1`. Its lower bound
can be any position from `0` through `turn`, inclusive.

During this loop:

- All prefix elements before `l` are smaller than the target.
- All prefix elements at or after `r` are at least the target.
- The undecided prefix elements occupy `[l, r)`.

Sorted order preserves these statements with the usual lower-bound updates.
At convergence, `l` is the first qualifying prefix index, or `turn` if
no prefix element qualifies.

The midpoint always satisfies `mid < r <= turn`, so the loop never compares
`nums[turn]`. This is essential: for `[4,5,6,7,0,1,2]`, the inclusive segment
`[4,5,6,7,0]` is not sorted, but the prefix `[4,5,6,7]` is.

After convergence, your equality check may read `nums[turn]`. This is safe
because `turn < n`; it may even find the target there. It is an extra
membership check outside the prefix, not an assumption that the prefix
continues in sorted order through `turn`.

## Step 3: Prove the suffix search

The suffix `[turn, n - 1]` is sorted and nonempty. Maintain that values
before `l` within this suffix are smaller than the target, and values
strictly after `r` are at least the target.

If a first qualifying suffix index exists, both updates retain it, so the
final index is that lower bound. If none exists, every update moves `l`
right while `r` remains `n - 1`; the search stops at the last element.

In either case, equality at the final index correctly decides whether the
suffix contains the target. The prefix and suffix cover the whole array,
so failure in both means the target is absent.

## Step 4: Safety, termination, and complexity

In every loop, `l < r` implies `l <= mid < r`:

- `r = mid` strictly decreases `r`.
- `l = mid + 1` strictly increases `l` without passing `r`.

Therefore, the nonnegative width strictly decreases until the pointers meet.
All accessed indexes lie between `0` and `n - 1`, including final equality
checks. Each loop halves its undecided range, taking `O(log n)` time.

The three loops execute sequentially, so their costs add rather than multiply:

```text
O(log n) + O(log n) + O(log n) = O(log n)
```

Auxiliary space is `O(1)`; the array is not modified.

## Complete trace: rotated array, target in the suffix

Input: `nums = [4,5,6,7,0,1,2]`, `target = 1`.

### Split search

Compare each midpoint with `nums[0] = 4`.

| `l` before | `r` before | `mid` | Value | Branch and state afterward |
| --- | --- | --- | --- | --- |
| 0 | 6 | 3 | 7 | `7 >= 4`: `l = 4`; `(4, 6)` |
| 4 | 6 | 5 | 1 | `1 < 4`: `r = 5`; `(4, 5)` |
| 4 | 5 | 4 | 0 | `0 < 4`: `r = 4`; `(4, 4)` |
| 4 | 4 | — | — | Stop; `turn = 4` |

### Prefix search

Search `[0, 4)`, whose values are `[4,5,6,7]`.

| `l` before | `r` before | `mid` | Value | Branch and state afterward |
| --- | --- | --- | --- | --- |
| 0 | 4 | 2 | 6 | `6 >= 1`: `r = 2`; `(0, 2)` |
| 0 | 2 | 1 | 5 | `5 >= 1`: `r = 1`; `(0, 1)` |
| 0 | 1 | 0 | 4 | `4 >= 1`: `r = 0`; `(0, 0)` |
| 0 | 0 | — | 4 | Stop; `nums[0] != 1`; continue |

### Suffix search

Search `[4, 6]`, whose values are `[0,1,2]`.

| `l` before | `r` before | `mid` | Value | Branch and state afterward |
| --- | --- | --- | --- | --- |
| 4 | 6 | 5 | 1 | `1 >= 1`: `r = 5`; `(4, 5)` |
| 4 | 5 | 4 | 0 | `0 < 1`: `l = 5`; `(5, 5)` |
| 5 | 5 | — | 1 | Stop; equality succeeds; return `5` |

## Complete trace: unrotated array

Input: `nums = [1,2,3,4]`, `target = 4`.

| Phase | `l` before | `r` before | `mid` | Comparison | Update |
| --- | --- | --- | --- | --- | --- |
| Split | 0 | 3 | 1 | `2 >= nums[0]` | `l = 2` |
| Split | 2 | 3 | 2 | `3 >= nums[0]` | `l = 3` |
| Split | 3 | 3 | — | — | Stop; `turn = 3` |
| Prefix | 0 | 3 | 1 | `2 < 4` | `l = 2` |
| Prefix | 2 | 3 | 2 | `3 < 4` | `l = 3` |
| Prefix | 3 | 3 | — | `nums[3] == 4` | Return `3` |

The suffix loop does not run because the boundary equality check already
found the target. Notice that `turn = 3` is not the minimum's index `0`.

## Missing-target example

For `[4,5,6,7,0,1,2]`, target `8`, the split search again gives `turn = 4`.

| Phase | `l` before | `r` before | `mid` | Value | Update or result |
| --- | --- | --- | --- | --- | --- |
| Prefix | 0 | 4 | 2 | 6 | `l = 3` |
| Prefix | 3 | 4 | 3 | 7 | `l = 4` |
| Prefix | 4 | 4 | — | 0 | Boundary check fails; continue |
| Suffix | 4 | 6 | 5 | 1 | `l = 6` |
| Suffix | 6 | 6 | — | 2 | Equality fails; return `-1` |

The prefix search reaches its boundary, while the inclusive suffix search
stops at its last element. Neither terminal position guarantees a match.

## Validation and assumptions

An exact Python translation of the submitted loops passed 4,032 cases:
every nonempty subset of the integers `-3` through `3`, sorted and rotated
at every possible offset, with every target from `-4` through `4`. This
checked singletons, no rotation, all rotations, and missing targets. It was
not a Kotlin compilation check, and finite examples do not replace the proof.

Distinctness matters for the single classification boundary. With duplicates,
`[2,2,0,1,2]` gives `true,true,false,false,true` for `nums[i] >= nums[0]`;
the same boundary-search argument no longer applies. Empty arrays are outside
this problem's constraints and would require separate handling.

## Polished interview explanation

> “A rotated ascending array has two sorted portions. Relative to the first
> value, the first portion contains values at least that value, and the
> second contains smaller values. That classification has one boundary,
> which I locate using binary search. If no smaller value exists, my search
> stops at the last index, which still gives a valid split.
>
> Next, I find the lower bound in the sorted prefix before the split. Its
> terminal position may be the split itself, so I check equality there too.
> If that fails, I search the sorted suffix starting at the split and check
> equality again. Together, these searches cover every element. The total
> time is logarithmic and the extra space is constant.”

## Rehearsal questions

1. Why must the first classification use `>= nums[0]`, not `> nums[0]`?
2. Why is `turn` the last index for an unrotated array?
3. Why does the first target loop never compare `nums[turn]`?
4. What would be wrong with claiming `[0, turn]` is sorted?
5. Which terminal positions mean “no qualifying value,” and why must equality
   still be checked?
6. Why do three logarithmic searches remain logarithmic overall?
