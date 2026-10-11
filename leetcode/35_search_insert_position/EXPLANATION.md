# 35. Search Insert Position

## Problem and key idea

Given an array of distinct integers sorted in ascending order, return the
target's index if it exists. Otherwise, return the index where it should be
inserted to preserve the order. The input array is not modified.

Both outcomes can be described by one rule:

> Find the first index whose value is greater than or equal to `target`.
> If no such element exists, return `nums.size`.

This position is called the **lower bound**. For `[1, 3, 5, 6]`, both target
`4` and target `5` have lower bound `2`: insert `4` before `5`, or return the
existing index of `5`.

## Solution evolution

### 1. Scan for the first qualifying element

A straightforward solution checks each element from left to right. Return
the first index where `nums[i] >= target`; if none qualifies, return `n`,
where `n = nums.size`.

This works because sorted order ensures every earlier element is smaller
than the target. It takes `O(n)` time and `O(1)` extra space.

What to say:

> “I can scan for the first element greater than or equal to the target.
> That gives either its existing index or its insertion position.”

### 2. Use sorted order to discard half the remaining elements

The scan checks elements individually, but sorted order lets one comparison
classify an entire portion of the array:

```text
nums[i] < target:    true true true | false false false
                                  ^
                            lower bound
```

If `nums[mid] < target`, all elements through `mid` are too small. Otherwise,
all elements from `mid` onward qualify, and the first qualifying element is
at `mid` or earlier. Binary search finds this boundary in `O(log n)` time
with `O(1)` extra space.

What to say:

> “Because the array is sorted, each comparison lets me discard half of the
> undecided elements while preserving the boundary I want to find.”

## Your reasoning, polished

You identified three useful ideas:

1. Sorted order makes binary search applicable.
2. Updating `left = mid` can get stuck when the midpoint equals `left`.
3. There are `n + 1` insertion positions for `n` elements, so the answer can
   be `n` even though the last element's index is `n - 1`.

Your “holes” intuition can be written as:

```text
Values:       1     3     5     6
Positions:  ^   ^     ^     ^     ^
            0   1     2     3     4
```

The important refinement is to define what each pointer means. We are
searching for a boundary, and `right` may represent the insertion position
after the last element.

Corrections to the intermediate explanation:

- When `nums[mid] < target`, move `left` to `mid + 1`, because `mid` itself
  cannot be the answer. This also guarantees progress.
- When `nums[mid] >= target`, move `right` to `mid`, because `mid` may be
  the answer. Equality can safely use this same branch.
- Your final implementation starts with `right = nums.size`, so its first
  midpoint for a four-element array is `2`, not `1`.
- The loop ends with `left == right`. The updates never let the pointers
  cross.
- Distinctness makes an existing target's index unique, but this algorithm
  also works with duplicates: it returns the first occurrence.

## Implementation

Your algorithm is unchanged; the comments now describe the invariant.

```kotlin
class Solution {
    fun searchInsert(nums: IntArray, target: Int): Int {
        var left = 0
        var right = nums.size

        // Before left: values < target.
        // At or after right: values >= target.
        while (left < right) {
            val mid = left + (right - left) / 2
            if (nums[mid] < target) {
                left = mid + 1
            } else {
                right = mid
            }
        }
        return left
    }
}
```

## Pointer meanings and loop invariant

At the start of every iteration:

- `0 <= left <= right <= n`.
- Every element before `left` is smaller than `target`.
- Every element at or after `right` is greater than or equal to `target`.

```text
[ values < target ][ undecided elements ][ values >= target ]
                   left                right
```

The **undecided elements** occupy `[left, right)`: `left` is included,
`right` is excluded. The **possible answer positions** occupy `[left, right]`:
both endpoints are included. The boundary could be immediately after all
the undecided elements.

This distinction explains why `right = n` is valid without accessing `nums[n]`.
While `left < right`, the midpoint always satisfies `left <= mid < right <= n`,
so `mid` is a valid element index.

## Correctness proof

### Initialization

Initially, `left = 0` and `right = n`. There are no elements before index
`0`, and no elements at or after index `n`. Therefore, both classification
statements hold, and the answer is somewhere from `0` through `n`.

### Preservation: `nums[mid] < target`

Because the array is sorted, every element at or before `mid` is also
smaller than `target`. None can be the first element greater than or equal
to the target. Setting `left = mid + 1` correctly classifies these elements
as too small. The statement about elements at or after `right` is unchanged.

### Preservation: `nums[mid] >= target`

Because the array is sorted, every element at or after `mid` is also
greater than or equal to `target`. Setting `right = mid` correctly
classifies these elements as qualifying. The statement about elements
before `left` is unchanged.

We keep `mid` as a possible answer because it could be the first qualifying
index. This is why equality does not require an immediate return.

### Termination

Whenever the loop runs, `left <= mid < right`:

- `left = mid + 1` strictly increases `left` without moving past `right`.
- `right = mid` strictly decreases `right` without moving before `left`.

Thus, the nonnegative integer `right - left` strictly decreases on every
iteration. Eventually, the pointers meet and the loop stops.

### Result

At termination, `left == right`. By the invariant:

- Every element before `left` is smaller than the target.
- Every element at or after `left` is greater than or equal to the target.

Therefore, `left` is exactly the lower bound. If the target exists, this is
its index. Otherwise, inserting there preserves sorted order. If every
element is smaller than the target, `left = n`, correctly indicating an
insertion after the last element.

## Complete execution trace

Input: `nums = [1, 3, 5, 6]`, `target = 4`, `n = 4`.

| State before step | `left` | `right` | `mid` | `nums[mid]` | Decision and state afterward |
| --- | --- | --- | --- | --- | --- |
| Initial | 0 | 4 | 2 | 5 | `5 >= 4`: set `right = 2`; state `(0, 2)` |
| Next iteration | 0 | 2 | 1 | 3 | `3 < 4`: set `left = 2`; state `(2, 2)` |
| Terminal | 2 | 2 | — | — | Loop stops; return `2` |

For target `5`, exactly the same pointer updates occur. The first comparison
uses the equality branch, preserving index `2` as a possible answer.

## Boundary cases

These expected results illustrate the proof; examples alone are not a proof.

| Array | Target | Expected result | Reason |
| --- | --- | --- | --- |
| `[1, 3, 5, 6]` | 0 | 0 | Insert before every element |
| `[1, 3, 5, 6]` | 7 | 4 | Insert after every element |
| `[1]` | 1 | 0 | Existing target in a one-element array |
| `[1]` | 2 | 1 | Insertion after a one-element array |
| `[]` | 4 | 0 | Also handled by the code, if empty input is permitted |
| `[1, 3, 3, 6]` | 3 | 1 | With duplicates, returns the first occurrence |

The last two rows show behavior beyond the supplied problem's nonempty,
distinct-element constraints.

## Complexity

Each iteration reduces the undecided interval to at most half its previous
length. For `n` elements, time is `O(log n)` and auxiliary space is `O(1)`.
The array is not modified.

## Interview explanation

> “I search for the first index whose value is greater than or equal to the
> target. That index is either the target's position or where it should be
> inserted. The answer can range from zero through the array length.
>
> I maintain that all elements before `left` are smaller than the target,
> and all elements at or after `right` are greater than or equal to it.
> If the middle value is smaller, I discard everything through `mid` by
> setting `left = mid + 1`. Otherwise, I keep `mid` as a possible answer by
> setting `right = mid`.
>
> Each iteration shrinks the undecided interval. When the pointers meet,
> the invariant proves that their position is the answer. This takes
> logarithmic time and constant extra space.”

## Rehearsal questions

1. What repeated work does binary search remove from the linear scan?
2. Why can `right` equal `n`, but `mid` never equal `n` inside the loop?
3. Why does equality use `right = mid`?
4. Explain why `left = mid` can get stuck when `right = left + 1`.
5. Trace `[1, 3]`, target `2`, to show why replacing `right = mid` with
   `right = mid - 1` would break this implementation.
