# Sort Array: quick sort and merge sort

This note develops the first-element-pivot quick sort and the merge sort we
worked through together. It preserves your algorithms and explains the choices
needed to reconstruct them in an interview. Sections 1–13 cover quick sort;
section 14 develops merge sort with commented code and a full trace.

The function sorts an `IntArray` in ascending order, mutates that array, and
returns it. Duplicates and negative values are allowed. All index ranges below
are **inclusive**; a range whose start exceeds its end is empty.

## 1. Solution evolution

### Your starting reasoning

Your original explanation was:

> Choose a pivot, move smaller values to its left and larger values to its
> right, and recursively sort both sides. Use two pointers to scan inward,
> exchanging values when they do not belong on their current sides.

The central idea was correct. The questions we needed to resolve were:

- Does a pointer identify a verified position or the next unchecked position?
- When the pointers meet, which side owns that value?
- How do equal values allow the loop to make progress?
- Where does the pivot end up?
- Which recursive ranges exclude the finished pivot?

These were actual uncertainties in the supplied reasoning, rather than facts
the initial implementation already established.

### A straightforward partition baseline

One easy way to express the idea is to select a pivot and collect the other
values into two temporary lists: values `<= x` and values `> x`. Recursively
sort those lists and concatenate the left result, pivot, and right result.

For `[3, 5, 3, 1, 4]`, this could produce:

```text
left list: [3, 1]     pivot: 3     right list: [5, 4]
```

This makes membership explicit, but each partition allocates storage
proportional to its input size. A partition costs O(n) time and O(n) extra
storage. With balanced splits, the whole sort takes O(n log n) time and can
use O(n) peak auxiliary storage with careful allocation lifetimes. Skewed
splits take O(n²) time; retaining all ancestor lists can also make peak
storage O(n²).

What to say:

> “I can first partition into temporary lists. To avoid allocating those lists,
> I can exchange values inside the original array.”

### Move the partition into the array

Your two-pointer implementation represents those groups as regions of the
original array. Each partition uses O(1) extra space. Recursion still uses
stack space.

The improvement is in storage and copying; the quality of the pivot still
determines whether recursion is balanced.

For duplicates, the final partition conditions are non-strict:

```text
values <= x | pivot x | values >= x
```

Equal values may belong on either side.

This version keeps the pivot at `left` while scanning, then explicitly moves
it into its final position. Its recursive boundaries must be derived from
that behavior; boundaries from a different partition implementation are not
automatically interchangeable.

## 2. Final Kotlin implementation

Each code line has an explanation immediately above it. “Move past a value”
means move the pointer beyond that value's position; the value itself stays
in place until a swap occurs.

```kotlin
// Group the sorting entry point and its helper functions.
class Solution {
    // Accept an integer array and return that same array after sorting it.
    fun sortArray(nums: IntArray): IntArray {
        // Sort the entire inclusive range; an empty array has lastIndex == -1.
        quickSort(nums, 0, nums.lastIndex)
        // The helper mutated nums, so return the now-sorted array.
        return nums
    // End the public sorting function.
    }

    // Sort only the inclusive subarray from left to right.
    private fun quickSort(nums: IntArray, left: Int, right: Int) {
        // Stop before reading a pivot if the range has zero or one element.
        if (left >= right) return

        // Save the first value as the pivot; its array position stays protected.
        val x = nums[left]
        // Start checking immediately after the pivot; the verified left region is empty.
        var i = left + 1
        // Start checking at the last element; the verified right region is empty.
        var j = right

        // Continue while at least one unchecked position remains, including i == j.
        // Invariant: nums[left] == x; [left + 1, i - 1] <= x; [j + 1, right] >= x.
        while (i <= j) {
            // Check bounds first; move right while the value already fits on the left.
            // Stop at a value >= x, or at right + 1 without reading that invalid index.
            while (i <= right && nums[i] < x) i++
            // Check bounds first; move left while the value already fits on the right.
            // The protected pivot equals x, so this scan cannot move below left.
            while (j >= left && nums[j] > x) j--

            // Swap only if the scans still identify unchecked positions.
            if (i <= j) {
                // Exchange nums[i] >= x with nums[j] <= x; each now fits its side.
                swap(nums, i, j)
                // Include the handled position in the verified left region.
                i++
                // Include the handled position in the verified right region.
                j--
            // If the pointers crossed during scanning, skip the swap and updates.
            }
        // The unchecked region is now empty: i > j.
        }

        // Move the pivot to j; the displaced value fits on the left because it is <= x.
        // If j == left, this is a harmless self-swap.
        swap(nums, left, j)

        // Sort everything before the finished pivot, including the displaced value at left.
        quickSort(nums, left, j - 1)
        // Sort everything after the finished pivot; exclude j so the range shrinks.
        quickSort(nums, j + 1, right)
    // Both sides are sorted, so the entire current subarray is sorted.
    }

    // Exchange the values at indices a and b without losing either value.
    private fun swap(nums: IntArray, a: Int, b: Int) {
        // Save the original value at a before overwriting that position.
        val temp = nums[a]
        // Copy the original value at b into position a.
        nums[a] = nums[b]
        // Put the saved original value at a into position b, completing the exchange.
        nums[b] = temp
    // End the swap helper; a == b is also safe.
    }
// End the Solution class.
}
```

This is the implementation derived together. The fixed first-element pivot
is useful for understanding the proof, but its worst-case performance remains
O(n²); see the performance section before using it for large inputs.

## 3. State definition

| State | Meaning | Changes during one partition? |
|---|---|---|
| `nums` | The current arrangement of values | Yes, through swaps |
| `left`, `right` | Bounds of the current recursive subarray | No |
| `x` | Saved pivot **value**, initially `nums[left]` | No |
| `i` | Left end of the remaining unchecked region | Moves right |
| `j` | Right end of the remaining unchecked region | Moves left |

`x` is a value, not an index. The pivot need not be the median or come from
the middle of the array.

During scanning, `j` is a pointer. Only after partitioning and the final swap
does `j` become the pivot's final index.

The state is divided into four regions:

```text
index:  left     left+1 ... i-1       i ... j       j+1 ... right
        ┌─────┐ ┌────────────────┐ ┌───────────┐ ┌────────────────┐
        │  x  │ │ values <= x    │ │ unchecked │ │ values >= x    │
        └─────┘ └────────────────┘ └───────────┘ └────────────────┘
```

“Unchecked” means we have not yet incorporated a position into a verified
region. It does not mean its value is necessarily misplaced.

## 4. The invariant and initialization

At each outer-loop entry:

1. `nums[left] == x`: the pivot remains protected.
2. Every value in `[left + 1, i - 1]` is `<= x`.
3. Every value in `[j + 1, right]` is `>= x`.
4. All rearrangements so far are swaps, so no values are lost or created.

The pointers stay within:

```text
left + 1 <= i <= right + 1
left <= j <= right
```

When `i <= j`, `[i, j]` remains to be processed. When `i > j`, it is empty.
After crossing, the verified regions can overlap; any overlapping value must
satisfy both conditions and therefore equal `x`.

Initialize:

```kotlin
val x = nums[left]
var i = left + 1
var j = right
```

Both verified regions are empty:

```text
left verified:  [left + 1, left]
right verified: [right + 1, right]
```

Every statement about all values in an empty region is satisfied. The
unchecked region contains all non-pivot positions.

We start at `left + 1` because this version reserves the pivot at `left`.
An implementation that starts at `left - 1` and increments before reading
uses a different scanning convention; its initialization cannot be copied
independently of its other rules.

## 5. State transitions

### Transition A: extend the verified left region

```kotlin
while (i <= right && nums[i] < x) i++
```

Before moving, the current value is `< x`, hence also `<= x`. Moving `i`
one position right includes that value in `[left + 1, i - 1]`.
The left invariant is preserved.

The scan stops because:

- `i == right + 1`, so there is no valid array position left to read; or
- `nums[i] >= x`, so we stop and consider exchanging this value.

`i == right + 1` is a valid pointer state, but `nums[i]` is not a valid access
there. Kotlin evaluates `&&` left to right and short-circuits, so the bounds
check must appear before the access.

Do not add `i < j` to this scan: that would stop at a meeting position before
its value is classified.

### Transition B: extend the verified right region

```kotlin
while (j >= left && nums[j] > x) j--
```

Every passed value is `> x`, hence also `>= x`. Decreasing `j` adds it to
`[j + 1, right]`, preserving the right invariant.

The pivot is still at `left`, with value `x`. Therefore this scan must stop
at or before reaching that position: `nums[left] > x` is false.
In this implementation, `j` never scans below `left`.

### Transition C: decide whether a pair remains

After both scans, check:

```kotlin
if (i <= j)
```

If true, both pointer positions are valid and the stopped scans imply:

```text
nums[i] >= x
nums[j] <= x
```

Swapping produces:

```text
nums[i] <= x
nums[j] >= x
```

Then:

```kotlin
i++
j--
```

These updates include the handled positions in their verified regions.
Their movement records progress; the pointers do not need to stay attached
to particular values.

Because `i >= left + 1` and `j >= i` when swapping, this swap cannot touch the
protected pivot. After `j--`, we still have `j >= left`.

### Equality case: `i == j`

If both scans stop on the same position, then:

```text
nums[i] >= x and nums[i] <= x
```

Therefore the value equals `x`. A self-swap is harmless. Advancing both
pointers consumes that remaining position and ends the loop.

Using `if (i < j)` could work with separate equality handling, but in this
implementation it would skip the only pointer updates when `i == j`, causing
an infinite loop on an equal value.

### Crossing case: `i > j`

The unchecked interval is empty. Do not swap.

For example, with `[1, 5, 2, 3]` and `x = 1`, the scans produce `i = 1`,
`j = 0`. Swapping those positions would move `5` into the left region even
though it is greater than the pivot.

### Why strict scans work with non-strict partitions

These are different responsibilities:

| Rule | Purpose |
|---|---|
| Left region contains `<= x` | Describes acceptable final membership |
| Right region contains `>= x` | Describes acceptable final membership |
| Left scan passes `< x` | Skips values definitely suitable on the left |
| Right scan passes `> x` | Skips values definitely suitable on the right |
| Swap, then advance both pointers | Handles stopped values, including equals |

An equal value does not need to be passed by the scan to be processed.
The swap-and-advance transition processes it.

## 6. Termination and pivot placement

Each entered outer iteration does one of two things:

- The scans cross, leaving no unchecked positions; the loop then exits.
- The pointers do not cross, so we swap and advance both, reducing the
  unchecked interval.

Pointers never move backward toward the unchecked region. Thus partitioning
terminates, including for all-equal arrays.

At exit, `i > j`. The invariant gives:

```text
nums[left + 1 .. j] <= x
nums[j + 1 .. right] >= x
```

The first fact follows because `j <= i - 1`, so the range through `j` lies
inside the verified left region.

Now perform:

```kotlin
swap(nums, left, j)
```

If `j > left`, the displaced value `nums[j]` is `<= x`, so it fits at `left`.
If `j == left`, the swap changes nothing.

Afterward:

```text
nums[left .. j - 1] <= x
nums[j] == x
nums[j + 1 .. right] >= x
```

The pivot is in a valid final sorted position. With duplicates, there may be
several equally valid positions for that value.

Important proof detail: the final `nums[j] <= x` follows from the invariant.
It cannot always be attributed only to the last right scan, because `j`
also decreases after swaps.

## 7. Recursion and whole-array correctness

Exclude the finished pivot:

```kotlin
quickSort(nums, left, j - 1)
quickSort(nums, j + 1, right)
```

Do not skip `left`: it now contains a displaced value, not necessarily the
original pivot.

Do not include `j`: it is already finished. Including it can create a
recursive call as large as the original range when the pivot is extreme.

The stopping condition is checked before reading the pivot:

```kotlin
if (left >= right) return
```

It covers both:

```text
left == right: one element
left > right:  zero elements
```

For a correctness argument by induction:

1. Arrays of length zero or one are sorted.
2. Partitioning preserves all values and places the pivot between two
   correctly classified regions.
3. Both recursive ranges are smaller, so assume recursion sorts them.
4. A sorted left region, pivot, and sorted right region form a sorted whole
   because every left value is `<= x` and every right value is `>= x`.

## 8. Full trace with duplicates

Initial input:

```text
index:  0  1  2  3  4
nums:  [3, 5, 3, 1, 4]
left = 0, right = 4, x = 3
```

| Phase | `i` | `j` | Array | Reason |
|---|---:|---:|---|---|
| Initialize | 1 | 4 | `[3, 5, 3, 1, 4]` | Both verified regions empty |
| Left scan stops | 1 | 4 | `[3, 5, 3, 1, 4]` | `5 < 3` is false |
| Right scan moves | 1 | 3 | `[3, 5, 3, 1, 4]` | Pass `4 > 3`; stop at `1` |
| Swap indices 1 and 3 | 1 | 3 | `[3, 1, 3, 5, 4]` | `1` fits left, `5` fits right |
| Advance pointers | 2 | 2 | `[3, 1, 3, 5, 4]` | Only index 2 remains unchecked |
| Both scans stop | 2 | 2 | `[3, 1, 3, 5, 4]` | Value equals `x` |
| Swap index 2 with itself | 2 | 2 | `[3, 1, 3, 5, 4]` | Equality is allowed |
| Advance pointers | 3 | 1 | `[3, 1, 3, 5, 4]` | Pointers cross |
| Outer loop exits | 3 | 1 | `[3, 1, 3, 5, 4]` | `3 <= 1` is false |
| Swap pivot indices 0 and 1 | 3 | 1 | `[1, 3, 3, 5, 4]` | Pivot finishes at index 1 |

Notice the overlap after the self-swap:

```text
left verified:  indices 1..2 → [1, 3]
right verified: indices 2..4 → [3, 5, 4]
```

Index 2 belongs to both verified descriptions and contains exactly `x`.
This is consistent with both inequalities.

### Recursive calls and returns

The code executes the left call before the right call:

```text
quickSort(0, 4): pivot 3 finishes at 1
  quickSort(0, 0): base case, return
  quickSort(2, 4): pivot 3
    i = 3 stops at 5
    j moves 4 → 3 → 2, stopping at pivot 3
    pointers cross; pivot self-swap at 2
    quickSort(2, 1): empty, return
    quickSort(3, 4): pivot 5
      i moves 4 → 5, passing value 4
      j = 4 stops at value 4
      pointers cross; swap pivot 5 with 4
      array becomes [1, 3, 3, 4, 5]
      quickSort(3, 3): base case, return
      quickSort(5, 4): empty, return
    return from quickSort(3, 4)
  return from quickSort(2, 4)
return from quickSort(0, 4)
```

## 9. Edge cases that explain the design

### Pivot is largest: `[5, 2, 3, 1]`

```text
x = 5, left = 0, right = 3
initial: i = 1, j = 3
left scan: i = 1 → 2 → 3 → 4
right scan: j stays 3 because 1 > 5 is false
crossed: skip inner swap
pivot swap: indices 0 and 3
result: [1, 2, 3, 5]
recursive ranges: [0, 2], [4, 3]
```

`i = 4` is safe as a pointer state because the bounds check prevents reading
`nums[4]`.

In your earlier scan, the `i < j` restriction stopped `i` at index 3.
The final code passes that value and reaches index 4.

### Pivot is smallest: `[1, 5, 2, 3]`

```text
x = 1, left = 0, right = 3
initial: i = 1, j = 3
left scan: i stays 1
right scan: j = 3 → 2 → 1 → 0
crossed: skip inner swap
pivot swap: index 0 with itself
result: [1, 5, 2, 3]
recursive ranges: [0, -1], [1, 3]
```

The pivot needs no movement, but the right region still needs sorting.

### All equal: `[3, 3, 3]`

```text
x = 3, left = 0, right = 2
initial: i = 1, j = 2
both scans stop
swap indices 1 and 2: array unchanged
advance: i = 2, j = 1
exit; swap pivot with index 1: array unchanged
recursive ranges: [0, 0], [2, 2]
```

The array need not change for the algorithm to make progress. Shrinking the
unchecked region is the progress measure.

### Two elements: `[1, 2]` and `[2, 1]`

Both start with `i == j == 1`, so the outer condition must allow equality.

| Input | Scan result | Pivot swap | Result |
|---|---|---|---|
| `[1, 2]` | `i = 1`, `j = 0` | Self-swap at 0 | `[1, 2]` |
| `[2, 1]` | `i = 2`, `j = 1` | Swap 0 and 1 | `[1, 2]` |

With the old `while (i < j)`, `[1, 2]` would skip scanning and then incorrectly
swap the pivot with index 1.

### Empty and single-element arrays

For an empty array, `nums.lastIndex == -1`, so the initial call is `(0, -1)`.
For a single element, it is `(0, 0)`. Both return before reading `nums[left]`.

## 10. Corrections to the original attempt

The initial partition fragment was:

```kotlin
val x = nums[left]
var i = left + 1
var j = right
while (i < j) {
    do {
        if (nums[i] < x) i++
        else break
    } while (i < j)
    do {
        if (nums[j] > x) j--
        else break
    } while (i < j)
    val t = nums[i]
    nums[i] = nums[j]
    nums[j] = t
}
```

| Original idea or code | Correction | Why |
|---|---|---|
| All left values `< x`, all right values `> x` | Allow `<= x` and `>= x` | Duplicates must fit somewhere |
| Assign the meeting index to a fixed side | Classify by value; let scans cross | The meeting value can be smaller or larger |
| Stop scans at `i == j` | Use array bounds for scan safety | The meeting value may still need processing |
| Outer loop uses `i < j` | Use `i <= j` | One unchecked element is still work |
| Swap but leave pointers unchanged | Advance both after swapping | Equal values otherwise cause an infinite loop |
| Swap unconditionally after scans | Swap only if `i <= j` | Crossed pointers no longer identify a pair to fix |
| Recurse before moving the pivot | Swap `left` and `j` first | Establish the final pivot position |
| Recurse on `[left + 1, j]` | Use `[left, j - 1]` | The pivot moved away from `left` |
| Recurse on `[j, right]` | Use `[j + 1, right]` | Exclude the finished pivot and shrink the range |

## 11. Complexity and practical limits

For a subarray of length n, both pointers move in only one direction and each
moves O(n) times. A partition therefore takes O(n) time and O(1) auxiliary
space.

| Partition shape | Total time | Recursion stack |
|---|---|---|
| Balanced | O(n log n) | O(log n) |
| Worst case: sizes 0 and n−1 repeatedly | O(n²) | O(n) |

For sorted distinct input, selecting the first element repeatedly selects the
smallest pivot. Reverse-sorted distinct input also produces extreme splits.
Large inputs of this kind can cause excessive runtime or stack overflow.

All-equal input behaves differently in this implementation: the swaps advance
both pointers, producing roughly balanced partitions.

A further improvement, separate from the version derived here, is to choose
a uniformly random pivot index in `[left, right]` and swap that value into
`left` before initializing `x`. The partition proof stays the same. Random
pivot selection gives expected O(n log n) time, but worst-case O(n²) time
remains possible.

The implementation is not stable: swaps can change the relative order of
equal-key items. Its partition is in-place, but the recursive algorithm does
not use O(1) total auxiliary space because the call stack must be counted.

## 12. Interview explanation

> “I use quick sort with an in-place two-pointer partition. For each subarray,
> I reserve its first element as the pivot.
>
> My invariant is that values before the left pointer, excluding the reserved
> pivot, are at most the pivot, and values after the right pointer are at least
> the pivot. The interval between the pointers is still unchecked.
>
> I scan past smaller values on the left and larger values on the right. If
> the pointers have not crossed, I exchange the stopped values and advance
> both pointers. This preserves the invariant and guarantees progress even
> with duplicates.
>
> When the pointers cross, I exchange the reserved pivot with the value at
> the right pointer. That places the pivot between the partitions. I then
> recursively sort both sides, excluding the pivot.
>
> Each partition is linear. Balanced recursion takes O(n log n) time and
> O(log n) stack space. A fixed first-element pivot can give O(n²) time and
> O(n) stack space; randomizing pivot selection improves expected behavior.”

## 13. Reconstruct it without memorizing

1. Draw the reserved pivot, verified left region, unchecked interval, and
   verified right region.
2. Initialize empty verified regions.
3. Derive the scans from which values can safely join each verified region.
4. Derive the swap from the two stopped inequalities.
5. Advance past the handled positions, including the equality case.
6. Use crossing plus the invariant to prove the final pivot swap.
7. Exclude the pivot from both recursive calls.

Questions to rehearse:

- Why are partition membership conditions non-strict but scan conditions strict?
- Why can `i` safely become `right + 1`?
- Why does the pivot stay protected during the inner swaps?
- Why does the right scan never pass `left`?
- Why is the final `nums[j] <= x` still justified if `j` last moved after a swap?
- Why does including the pivot in recursion risk failing to shrink the problem?
- Which input demonstrates the fixed-pivot worst case?

## 14. Merge sort: sort the halves, then merge

### Solution evolution

Our starting point was the merge operation: given two already-sorted arrays,
repeatedly select the smaller of their first unconsumed values. For example:

```text
Left:  [2, 5, 8]
Right: [1, 3, 7]
```

Each first unconsumed value is the minimum of its own remaining array. Therefore
the smaller of the two is the minimum remaining value overall. Append it and
advance only the pointer belonging to that value. Once one side is exhausted,
append the other side's remaining values in their existing order.

Your explanation correctly identified that this keeps the result sorted. More
precisely, the result contains the smallest values selected so far, in sorted
order; each pointer identifies its side's smallest **remaining** value.

The missing prerequisite for an arbitrary input is that its halves might not
be sorted. We satisfy that prerequisite recursively:

```text
                  [5, 2, 8, 3]
                  /          \
               [5, 2]       [8, 3]
               /    \       /    \
             [5]    [2]   [8]    [3]    already sorted
               \    /       \    /
               [2, 5]       [3, 8]      merge sorted pieces
                  \          /
                  [2, 3, 5, 8]
```

A straightforward implementation could create separate arrays for each half.
We instead represent the halves using inclusive index ranges in `nums`, avoiding
copies during splitting. We still use a temporary list during merging so that
writing output cannot overwrite values we have not yet read.

This is the implementation we derived together; allocating one reusable merge
buffer is a possible later optimization, not a prerequisite for understanding
this version.

What to say:

> “I know how to merge two sorted sequences in linear time. To sort an arbitrary
> sequence, I recursively sort its two halves first, then apply that merge.”

### Polished Kotlin code with comments above each line

This is an alternative `Solution` to the quick-sort implementation above; use
one `Solution` class at a time for submission.

```kotlin
// Group the sorting entry point and recursive helper.
class Solution {
    // Sort the input array in ascending order and return the same array.
    fun sortArray(nums: IntArray): IntArray {
        // Sort the full inclusive range; lastIndex is -1 for an empty array.
        mergeSort(nums, 0, nums.lastIndex)
        // All merges have copied their sorted results back into nums.
        return nums
    // End the public entry point.
    }

    // Sort the inclusive range [left, right], leaving other positions unchanged.
    private fun mergeSort(nums: IntArray, left: Int, right: Int) {
        // An empty range or a single element is already sorted.
        if (left >= right) return

        // Find the midpoint without risking overflow from adding left and right.
        val mid = left + (right - left) / 2
        // Finish sorting the left half before starting the merge.
        mergeSort(nums, left, mid)
        // Finish sorting the right half before starting the merge.
        mergeSort(nums, mid + 1, right)

        // Point to the first unconsumed value in the now-sorted left half.
        var i = left
        // Point to the first unconsumed value in the now-sorted right half.
        var j = mid + 1
        // Store merged output separately so unread input values remain intact.
        val temp = mutableListOf<Int>()

        // Compare only while both halves have an unconsumed value.
        while (i <= mid && j <= right) {
            // Choose the smaller value; prefer the left on ties to preserve stability.
            if (nums[i] <= nums[j]) {
                // Append the smallest remaining value overall from the left half.
                temp.add(nums[i])
                // Mark that left value consumed by advancing only i.
                i++
            // Otherwise the right value is strictly smaller.
            } else {
                // Append the smallest remaining value overall from the right half.
                temp.add(nums[j])
                // Mark that right value consumed by advancing only j.
                j++
            // End the choice of which half supplies the next value.
            }
        // At least one half is now exhausted.
        }

        // Copy any remaining left values; their order is already correct.
        while (i <= mid) {
            // Append the next unconsumed left value.
            temp.add(nums[i])
            // Move to the following left value.
            i++
        // The left half is now fully consumed.
        }

        // The right half ends at right, so use right rather than mid here.
        while (j <= right) {
            // Append the next unconsumed right value.
            temp.add(nums[j])
            // Move to the following right value.
            j++
        // Both halves are now fully consumed.
        }

        // Visit every merged value using its zero-based index in temp.
        for (k in temp.indices) {
            // Offset by left to write into this call's original subarray.
            nums[left + k] = temp[k]
        // The inclusive range [left, right] is now sorted.
        }
    // Return to the parent call, which can now safely merge this sorted half.
    }
// End the Solution class.
}
```

### State definitions

All boundaries are inclusive. Unlike quick sort, merge sort has no pivot to
exclude from recursion.

| State | Meaning |
|---|---|
| `left`, `right` | Fixed bounds of this call's subarray |
| `mid` | Last index in the left half |
| `[left, mid]` | Left half, sorted by the first recursive call |
| `[mid + 1, right]` | Right half, sorted by the second recursive call |
| `i` | Index of the next unconsumed left value |
| `j` | Index of the next unconsumed right value |
| `temp` | Sorted output built from consumed values |
| `k` | Index in `temp` during copying back; its destination is `left + k` |

During merging, `nums` is not changed. “Consumed” is a logical state recorded
by the pointers; it does not mean values were deleted from the original array.

```text
Left half:   [ consumed values | remaining values ]
              left ... i-1      i ... mid

Right half:  [ consumed values | remaining values ]
              mid+1 ... j-1      j ... right

Output:      temp = sorted merge of the two consumed prefixes
```

### Invariant: what remains true while merging?

At the beginning of each comparison-loop iteration:

1. Both original halves are sorted and remain unchanged during merging.
2. `temp` contains exactly the values consumed from both halves, with the same
   multiplicities; it is sorted in nondecreasing order.
3. Every value in `temp` is at most every remaining value in either half.
4. The pointer offsets count the consumed values:

```text
temp.size == (i - left) + (j - (mid + 1))
```

Initially, `i = left`, `j = mid + 1`, and `temp` is empty. No values have been
consumed, so all four properties hold.

### Transition 1: compare the two remaining minima

The guard is:

```kotlin
while (i <= mid && j <= right)
```

Sortedness tells us **why the selection is correct**. These bounds tell us
**whether both values are available to compare**. They are separate arguments.

Since each half is sorted, `nums[i]` and `nums[j]` are their respective remaining
minima. If `nums[i] <= nums[j]`, then `nums[i]` is no greater than any remaining
value on either side. Append it and increment `i`. Otherwise append `nums[j]`
and increment `j`.

The previous output is no greater than the selected value, so appending preserves
sortedness. Advancing exactly one pointer records exactly one consumed value,
so the count and content invariants remain true.

Every iteration consumes one value. The loop therefore terminates when one of
the finite halves is exhausted.

### Transition 2: append the remaining values

After the comparison loop, either `i == mid + 1` or `j == right + 1`.
We must not read the exhausted side.

The other side is already sorted. The invariant also tells us that its remaining
values are at least as large as the last appended value, if there is one.
Therefore we can append them without further cross-half comparisons:

```kotlin
while (i <= mid) { /* append nums[i], then increment i */ }
while (j <= right) { /* append nums[j], then increment j */ }
```

An exhausted side's loop executes zero times. After both loops:

```text
i == mid + 1
j == right + 1
temp.size == right - left + 1
```

`temp` now contains every value in this call's range, in sorted order.

### Transition 3: copy the sorted result back

The temporary list starts at index zero, but the destination range may start
elsewhere:

```text
left = 2, right = 5

temp index k:        0  1  2  3
destination left+k:  2  3  4  5
```

Therefore the assignment is:

```kotlin
nums[left + k] = temp[k]
```

This is a destination formula, not an update `k = left + k`.
The loop ends at `k = right - left`, whose destination is exactly `right`.
No positions outside the current subarray are modified.

### Why the recursive order is essential

The order is:

```text
sort left half → sort right half → merge → copy back → return
```

Our selection rule depends on each half already being sorted. Before recursion,
its first value need not be its minimum. For example, merging `[5, 2]` and
`[8, 3]` directly would select `5` before seeing `2`, breaking output order.

The base case is `left >= right`. For larger ranges, the midpoint creates two
nonempty, strictly smaller ranges. Both recursive calls terminate; once they
return sorted halves, the merge proof establishes a sorted whole. This is an
inductive correctness proof, not merely an observation from one example.

### Full execution trace

Start with:

```text
index:  0  1  2  3
nums:  [5, 2, 8, 3]
```

Call and return order:

```text
mergeSort(0, 3), mid = 1
  mergeSort(0, 1), mid = 0
    mergeSort(0, 0): return immediately
    mergeSort(1, 1): return immediately
    merge [5] and [2] into [2, 5]
    copy back: nums = [2, 5, 8, 3]
    return
  mergeSort(2, 3), mid = 2
    mergeSort(2, 2): return immediately
    mergeSort(3, 3): return immediately
    merge [8] and [3] into [3, 8]
    copy back: nums = [2, 5, 3, 8]
    return
  merge [2, 5] and [3, 8] into [2, 3, 5, 8]
  copy back: nums = [2, 3, 5, 8]
  return
```

Every step of the final merge uses `left = 0`, `mid = 1`, `right = 3`:

| Step | `i` after step | `j` after step | `temp` after step | Reason |
|---|---:|---:|---|---|
| Initialize | 0 | 2 | `[]` | No values consumed |
| Append `2` | 1 | 2 | `[2]` | `2 <= 3`; advance only `i` |
| Append `3` | 1 | 3 | `[2, 3]` | `5 > 3`; advance only `j` |
| Append `5` | 2 | 3 | `[2, 3, 5]` | `5 <= 8`; advance only `i` |
| Exit comparison loop | 2 | 3 | `[2, 3, 5]` | `i > mid`; left exhausted |
| Skip left remainder | 2 | 3 | `[2, 3, 5]` | No left values remain |
| Append right remainder `8` | 2 | 4 | `[2, 3, 5, 8]` | `j <= right`, then advance `j` |

The source array remains `[2, 5, 3, 8]` throughout these steps. Only then do we
copy back:

| `k` | Assignment | `nums` after assignment |
|---:|---|---|
| 0 | `nums[0] = 2` | `[2, 5, 3, 8]` |
| 1 | `nums[1] = 3` | `[2, 3, 3, 8]` |
| 2 | `nums[2] = 5` | `[2, 3, 5, 8]` |
| 3 | `nums[3] = 8` | `[2, 3, 5, 8]` |

The temporary duplicate `3` during copying is harmless: the complete result,
including `5`, is already preserved in `temp`.

### Review of your implementation

Your implementation already had the correct base case, recursive ranges,
recursive order, pointer initialization, comparison, left remainder, and
copy-back offset.

The right-remainder loop used:

```kotlin
// Original boundary from your attempt:
while (j <= mid) {
    temp.add(nums[j])
    j++
}
```

Since `j` starts at `mid + 1` and only increases, this loop never executes.
The intended full-output version uses `j <= right`.

A qualification matters here: the original code can still sort correctly,
because remaining right-hand values are already at their final positions.
This was an inconsistency with our intended full-merge invariant, not a
counterexample proving the original output was wrong.

Why can that shorter copy work? If the left half is exhausted and the right
pointer is `j`, the number of values in `temp` is:

```text
left half size + consumed right values
= (mid - left + 1) + (j - mid - 1)
= j - left
```

Copying this prefix back fills `[left, j - 1]`, leaving `[j, right] untouched.
That untouched suffix is precisely the sorted right remainder. If the right
half is exhausted instead, the left-remainder loop completes all of `temp`.

We use the full-output version in the polished code because it makes the
contract explicit and symmetric: `temp.size == right - left + 1` before copying.

The other cleanup was the midpoint:

```kotlin
// Avoid adding two potentially large indices.
val mid = left + (right - left) / 2
```

### Boundary cases and stability

| Case | Why it works |
|---|---|
| Empty input | Initial bounds `(0, -1)` immediately return |
| One element | `left == right` immediately returns |
| Two elements | Two singleton calls return, then one merge orders them |
| Odd length | The halves differ in size by one; neither requires equal lengths |
| Left half exhausted first | Append the right remainder through `right` |
| Right half exhausted first | Append the left remainder through `mid` |
| Duplicates | Each comparison still appends one value and advances one pointer |
| Negative values | The same integer comparisons apply |
| Subarray starts after index zero | Copy to `left + k`, not just `k` |

Choosing the left value on equality makes this merge **stable**. Conceptually,
if equal keys are labeled by their original positions:

```text
Left: [2A]   Right: [2B]
```

`<=` selects `2A` first. Recursive halves also preserve equal-key order, so the
whole sort preserves it. For plain integers the labels are invisible, but the
property matters when sorting records by a key.

### Complexity and an optional next improvement

For a range of length n, merging consumes n values and copying back writes n
values, so the work is O(n). Appending to the list costs amortized O(1) per value.

The halves are balanced by index regardless of input order. There are O(log n)
levels, each doing O(n) total work:

- Time: O(n log n) in the best, average, and worst cases for this implementation.
- Recursion stack: O(log n).
- Temporary storage: O(n) peak live auxiliary storage, plus the stack.

The parent creates `temp` only after its child calls return. Their completed
lists are no longer needed, so all levels' lists need not remain live together.
Total allocation across the execution is O(n log n), even though peak live
auxiliary storage is O(n). Actual memory use also depends on garbage collection
and list capacity. On Kotlin/JVM, `MutableList<Int>` additionally stores boxed
integer values rather than a primitive integer array.

A later optimization is to allocate one `IntArray(nums.size)` at the entry
point and reuse it for every merge. This avoids repeated list allocations and
boxing while keeping the same asymptotic time and space bounds. It does not
change the merge invariant or selection rule.

### Interview explanation

> “I split the array into two inclusive ranges and recursively sort each one.
> A range with at most one element is already sorted.
>
> After both calls return, I merge their sorted results using two pointers.
> Each pointer identifies the smallest remaining value in its half, so I append
> the smaller value to a temporary list and advance only that pointer. The list
> remains sorted and contains exactly the consumed values.
>
> Once one half is exhausted, I append the other half's remaining values, then
> copy the merged result back starting at the current range's left boundary.
>
> Each level does linear work and there are logarithmically many levels, giving
> O(n log n) time. Temporary storage is O(n), and recursion uses O(log n) stack
> space. Choosing the left value on ties preserves stability.”

### Quick sort versus this merge sort

| Property | First-element-pivot quick sort above | Merge sort above |
|---|---|---|
| Work before recursive calls | Partition around the pivot | Compute midpoint |
| Work after recursive calls | No merge needed | Merge sorted halves and copy back |
| Recursive ranges | Exclude the finished pivot | Cover both complete halves |
| Split balance | Depends on pivot and values | Determined by indices |
| Worst-case time | O(n²) | O(n log n) |
| Peak auxiliary space | O(log n) balanced, O(n) worst-case stack | O(n) buffer/list plus O(log n) stack |
| Stable | No | Yes, because ties choose the left |

### Rehearsal questions

- What prerequisite does comparing only `nums[i]` and `nums[j]` depend on?
- How do the index bounds differ from the argument that the selection is correct?
- Why does only one pointer advance after each comparison?
- Why are remaining values safe to append without further comparisons?
- Why must merging happen after both recursive calls return?
- Why do we need temporary storage before overwriting the source range?
- Why is the destination `left + k` instead of `k`?
- Why can omitting the right remainder still work with a prefix-only copy?
