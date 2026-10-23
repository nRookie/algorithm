# Reverse Pairs: counting while merge-sorting

Count index pairs `(i, j)` satisfying both:

```text
i < j
nums[i] > 2 * nums[j]
```

The comparison is strict. For example, `6` and a later `3` do not count because
`6 == 2 * 3`. A later `2` does count because `6 > 2 * 2`.

This implementation returns the count and also sorts the input array. It uses
the supplied `reversePairs(nums: IntArray): Int` API. The return type assumes the
problem's total pair count fits in an `Int`; for a more general API with larger
inputs, use `Long` for the counts and return type too.

## 1. Solution evolution

### Baseline: check every pair

For each index `i`, try each index `j` starting at `i + 1`:

```kotlin
var count = 0
for (i in nums.indices) {
    for (j in i + 1 until nums.size) {
        if (nums[i].toLong() > 2L * nums[j]) {
            count++
        }
    }
}
```

There are `n * (n - 1) / 2` candidate pairs: O(n²) time and O(1) extra space.
Starting `j` at `i` would incorrectly allow an element to pair with itself.

What to say:

> “The baseline checks every ordered-by-index pair. It is quadratic because
> each left element independently scans all later elements.”

### Divide pairs into three disjoint groups

Split a range into two contiguous halves:

```text
index:  0  1 | 2  3
nums:  [6, 3 | 2, 1]
```

Every candidate pair belongs to exactly one group:

| Group | Example | Who counts it? |
|---|---|---|
| Both indices in the left half | `(6, 3)` | Left recursive call |
| Both indices in the right half | `(2, 1)` | Right recursive call |
| First index in left, second in right | `(6, 2)` | Current call |

“Cross-half pair” describes where the two elements come from. It does not yet
mean the numeric condition is true. For example, `(3, 2)` crosses the halves but
fails `3 > 2 * 2`.

We combine the counts by addition, since the groups are disjoint and exhaustive.

### Use sorted halves to avoid repeated comparisons

Each recursive call both counts its internal pairs and sorts its range. After
those calls, the example becomes:

```text
Left: [3, 6]    Right: [1, 2]
```

Every value in the left group originally occurred before every value in the
right group. Sorting within each group does not change that membership, so all
cross-group combinations satisfy the original index ordering.

For a fixed left value, matching right values form a **prefix** of the sorted
right half. If a right value fails `leftValue > 2 * rightValue`, every larger
right value fails too.

As left values increase, previously matching right values still match. We can
reuse one right pointer rather than restarting its scan for every left value.
Each pointer moves forward at most the length of its half, giving O(n) work per
counting phase.

What to say:

> “I let merge sort give me sorted halves. For each left value, I find the end
> of the matching prefix on the right. Since left values increase, that boundary
> never moves backward. This makes counting cross-half pairs linear.”

## 2. Polished implementation with line-by-line comments

The algorithm is your supplied implementation, with the right-remainder bound
corrected, a safer midpoint formula, and separate names for counting and merging.

```kotlin
// Group the entry point and recursive sorting/counting helper.
class Solution {
    // Return the number of reverse pairs; the helper also sorts nums.
    fun reversePairs(nums: IntArray): Int {
        // Start with the full inclusive range; an empty input has lastIndex == -1.
        return mergeSort(nums, 0, nums.lastIndex)
    // End the public entry point.
    }

    // Count original pairs within [left, right], then leave that range sorted.
    private fun mergeSort(nums: IntArray, left: Int, right: Int): Int {
        // Zero or one element forms zero pairs with distinct indices i < j.
        if (left >= right) return 0

        // Split without adding two potentially large indices.
        val mid = left + (right - left) / 2
        // Count left-internal pairs and finish sorting the left half.
        var count = mergeSort(nums, left, mid)
        // Add right-internal pairs and finish sorting the right half.
        count += mergeSort(nums, mid + 1, right)

        // Initialize the matching-prefix boundary once, before visiting left values.
        var j = mid + 1
        // Visit left values in nondecreasing order; p is a counting index.
        for (p in left..mid) {
            // Check bounds first; use Long arithmetic before doubling to avoid overflow.
            while (j <= right && nums[p].toLong() > 2L * nums[j]) {
                // This right value matches; extend the matching prefix by one position.
                j++
            // j is now the first nonmatching right index, or right + 1.
            }
            // Count every match for this left value, including matches found earlier.
            count += j - (mid + 1)
        // Cross-half counting is complete; the two groups have not yet been mixed.
        }

        // Start merging from the first value in the left half.
        var i = left
        // Reset j: merging must read all right values, not just those after counting.
        j = mid + 1
        // Keep merged output separate so unread source values are not overwritten.
        val temp = mutableListOf<Int>()

        // Compare only while both halves still have an unconsumed value.
        while (i <= mid && j <= right) {
            // Choose the smaller value; prefer the left on equality.
            if (nums[i] <= nums[j]) {
                // Append the smallest remaining value from the left half.
                temp.add(nums[i])
                // Mark that left value consumed.
                i++
            // Otherwise the right value is smaller.
            } else {
                // Append the smallest remaining value from the right half.
                temp.add(nums[j])
                // Mark that right value consumed.
                j++
            // End the selection of the next merged value.
            }
        // At least one half is now exhausted.
        }

        // Append any left remainder, which is already sorted.
        while (i <= mid) {
            // Copy the next remaining left value into temp.
            temp.add(nums[i])
            // Advance the left pointer.
            i++
        // The left half is fully consumed.
        }

        // The right half ends at right, not mid.
        while (j <= right) {
            // Copy the next remaining right value into temp.
            temp.add(nums[j])
            // Advance the right pointer.
            j++
        // Both halves are fully consumed; temp has right - left + 1 values.
        }

        // Copy the sorted output back into this call's original range.
        for (k in temp.indices) {
            // temp starts at zero, while this subarray starts at left.
            nums[left + k] = temp[k]
        // The parent call can now rely on this range being sorted.
        }
        // Return all three groups: left-internal, right-internal, and cross-half.
        return count
    // End the recursive helper.
    }
// End the Solution class.
}
```

## 3. Function contract and state definitions

`mergeSort(nums, left, right)` has two outputs:

1. Its return value counts reverse pairs whose original indices belong to this
   range.
2. Its mutation leaves `nums[left..right]` sorted for the parent call.

All ranges here are inclusive unless explicitly described as excluding an end.

| State | Meaning |
|---|---|
| `left`, `right` | Fixed bounds of the current recursive range |
| `mid` | Last index of its left half |
| `count` | Internal counts from children plus cross-half counts accumulated so far |
| `p` | Current left index during pair counting |
| `j` during counting | Boundary between matching and not-yet-confirmed right values |
| `i`, `j` during merging | Next unconsumed indices in the two sorted halves |
| `temp` | Sorted merge of the values consumed so far |
| `k` | Temporary-list index; destination is `left + k` |

A value's current sorted position is not necessarily its original index. We do
not claim that sorting preserves individual indices. What matters is that no
value crosses the current midpoint until cross-half counting is finished.

## 4. Counting invariant and transitions

### Initialization

Both halves are sorted by the recursive calls. Set `j = mid + 1` once.
Before the first left value, the confirmed matching prefix is empty.

### Invariant before scanning for a left value

For the current left value `nums[p]`, every right value in
`[mid + 1, j - 1]` is already known to match it.

For the first left value, this is an empty range. For later left values, this
follows from monotonicity: if `a > 2 * b` and `aNext >= a`, then
`aNext > 2 * b` too.

At this point `j` is not necessarily a nonmatching value for the new left value.
It is the first right value whose match has not yet been confirmed for that value.

### Transition: extend the matching prefix

```kotlin
while (j <= right && nums[p].toLong() > 2L * nums[j]) {
    j++
}
```

Each successful comparison proves that the value at `j` also matches. Moving
`j` forward includes that position in the matching prefix.

At loop exit:

```text
Matching right indices:    [mid + 1, j - 1]
Nonmatching right indices: [j, right]
```

Either interval can be empty. If `j == right + 1`, every right value matches.
Sortedness guarantees all values after the first failure also fail.

### Transition: add the prefix length

A range starting at `start` and ending just before `j` contains `j - start`
positions. Here `start = mid + 1`:

```kotlin
count += j - (mid + 1)
```

For `mid = 1`, the right half begins at index 2:

| `j` | Matching indices | Count for this left value |
|---:|---|---:|
| 2 | None | `2 - 2 = 0` |
| 3 | `[2]` | `3 - 2 = 1` |
| 4 | `[2, 3]` | `4 - 2 = 2` |

`j` is an index, not a count. Subtracting `mid` instead would incorrectly include
one extra position.

Do not add only the number of new pointer movements. The same right element
can form different pairs with different left elements: `(3, 1)` and `(6, 1)`
are distinct pairs.

### Transition: advance the left index

The next left value is at least as large as the current one. All confirmed
matches remain valid, so keep `j` where it is and extend it if possible.

This reuse is what makes counting linear rather than quadratic.

## 5. Why counting precedes merging

The correct order is:

```text
count/sort left → count/sort right → count cross-half pairs → merge → return
```

Counting needs sorted halves, but it also needs their original membership to
remain separate. Merging mixes those groups. Therefore it must happen after
cross-half counting and before the parent call uses this range.

Counting and merging use different comparisons:

```text
Counting: nums[p] > 2 * nums[j]
Merging:  nums[i] <= nums[j]
```

Do not treat a merge decision as automatically deciding the reverse-pair count.
The factor of two makes these different boundaries.

Before merging, reset `i = left` and `j = mid + 1`. Counting did not consume or
remove array elements; it only inspected them.

The merge invariant is the one derived in our
[Sort Array explanation](../912_sort_an_array/EXPLANATION.md#14-merge-sort-sort-the-halves-then-merge):
`temp` is sorted, contains exactly the consumed values, and every remaining
value is at least as large as every appended value. Append remaining values,
then copy back with `nums[left + k] = temp[k]`.

## 6. Complete trace: `[6, 3, 2, 1]`

### Left recursive call: original `[6, 3]`

Its singleton calls return zero. Comparing `6` against `3` gives
`6 > 2 * 3`, which is false. Cross count is zero. Merge to `[3, 6]` and return 0.

### Right recursive call: original `[2, 1]`

Its singleton calls return zero. Comparing `2` against `1` gives
`2 > 2 * 1`, which is false. Cross count is zero. Merge to `[1, 2]` and return 0.

### Parent's cross-half phase

```text
index:  0  1 | 2  3
nums:  [3, 6 | 1, 2]
left = 0, mid = 1, right = 3
count = 0 + 0 = 0
j = 2
```

| Step | `p` | `j` after step | Action | `count` |
|---|---:|---:|---|---:|
| Test `3 > 2 * 1` | 0 | 3 | True: extend matching prefix | 0 |
| Test `3 > 2 * 2` | 0 | 3 | False: stop scanning | 0 |
| Add prefix length | 0 | 3 | Add `3 - 2 = 1`: pair `(3, 1)` | 1 |
| Test `6 > 2 * 2` | 1 | 4 | True: extend matching prefix | 1 |
| Check bounds | 1 | 4 | `j > right`: stop without reading `nums[4]` | 1 |
| Add prefix length | 1 | 4 | Add `4 - 2 = 2`: pairs `(6, 1)`, `(6, 2)` | 3 |

We did not recheck `1` for `6`, but we still counted its distinct pair with `6`.
The total is `0 + 0 + 3 = 3`.

### Parent's merge phase

Reset `i = 0`, `j = 2`, `temp = []`:

| Action | `i` after | `j` after | `temp` |
|---|---:|---:|---|
| Take right value `1` | 0 | 3 | `[1]` |
| Take right value `2` | 0 | 4 | `[1, 2]` |
| Comparison loop ends | 0 | 4 | `[1, 2]` |
| Append remaining left `3` | 1 | 4 | `[1, 2, 3]` |
| Append remaining left `6` | 2 | 4 | `[1, 2, 3, 6]` |
| Right-remainder loop is skipped | 2 | 4 | `[1, 2, 3, 6]` |

Copying back produces these array states:

```text
k = 0: [1, 6, 1, 2]
k = 1: [1, 2, 1, 2]
k = 2: [1, 2, 3, 2]
k = 3: [1, 2, 3, 6]
```

The temporary intermediate duplicates are harmless because all merged output
is preserved in `temp`. Return the count 3.

Original valid index pairs were `(0, 2)`, `(0, 3)`, and `(1, 3)`.

## 7. Review of your submitted code

Your cross-half counting logic was correct: initialize `j` once, scan with
`Long` multiplication, add `j - (mid + 1)` for every left value, and reset the
pointers before merging.

The supplied code had these details worth polishing:

| Supplied detail | Polished version | Reason |
|---|---|---|
| Comment says zero/one element “would be one” | Say zero pairs | Your actual `return 0` was already correct |
| `(right + left) / 2` | `left + (right - left) / 2` | Avoid overflow in the sum |
| Outer `var i`, then `for (i in ...)` | Use `p` for counting, declare `i` for merging | Avoid shadowing and distinguish pointer roles |
| `while (j <= mid)` for right remainder | `while (j <= right)` | The right half ends at `right` |

Your original right-remainder fragment was:

```kotlin
while (j <= mid) {
    temp.add(nums[j])
    j++
}
```

That loop never runs because `j` starts at `mid + 1` and only increases.
However, this does **not** make the supplied algorithm's final output incorrect:
with your prefix-only copy-back loop, any remaining right suffix stays in its
already-correct position.

If the left half is exhausted while `j` remains on the right, the temporary list
has length:

```text
(mid - left + 1) + (j - (mid + 1)) = j - left
```

Copying that list fills `[left, j - 1]`, leaving the right remainder `[j, right]`
untouched. If the right half is exhausted instead, the left-remainder loop
finishes the complete output.

Thus the original code can still sort the halves correctly and count pairs
correctly. We changed the boundary to match the clearer full-output invariant:
`temp` contains every element in `[left, right]` before copying back.

## 8. Edge cases and pitfalls

- **No elements or one element:** return 0 before reading the array.
- **Strict equality:** `[6, 3]` contributes zero, since `6 > 6` is false.
- **Negative values:** `[-3, -2]` contributes one, since `-3 > -4`. An additional
  requirement `nums[i] > nums[j]` would wrongly reject this pair.
- **Equal negative values:** `[-1, -1]` contributes one. Equal values are not
  automatically nonmatching when doubling is involved.
- **Zero:** `[0, 0]` contributes zero.
- **Overflow:** perform multiplication in `Long`, as in `2L * nums[j]`.
  `(2 * nums[j]).toLong()` is too late: the `Int` multiplication may already
  have overflowed.
- **All right values match:** `j` reaches `right + 1`; the bounds guard prevents
  an invalid read and the prefix length equals the right half's size.
- **No right values match:** `j == mid + 1`, so the added count is zero.
- **Do not globally sort first:** that would erase the original index grouping
  before its pair counts have been recorded.

## 9. Correctness and complexity

For correctness, use induction on the range length:

1. Ranges of length zero or one have zero pairs and are sorted.
2. Child calls correctly count internal pairs and sort their halves.
3. The monotone-prefix argument counts every cross-half pair exactly once.
4. These three pair categories are disjoint and cover all possibilities.
5. Merging preserves the elements and sorts the range for its parent.

For a range of length n, the cross-half counting pass is O(n): the left index
visits each left value once and `j` advances at most the right half's length.
Merging and copying back also take O(n).

Balanced recursion has O(log n) levels, with O(n) work per level:

- Time: **O(n log n)**.
- Peak live auxiliary storage: **O(n)** for temporary merge output, plus
  **O(log n)** recursion stack.
- Cumulative list allocation: O(n log n); child lists are no longer needed when
  a parent creates its list, so cumulative allocation is not peak live storage.

A reusable `IntArray` buffer can reduce allocation and boxing overhead without
changing the counting algorithm or asymptotic bounds. The code above preserves
the mutable-list merge we derived together.

## 10. Interview explanation and rehearsal

> “I use merge sort so each recursive call returns the reverse-pair count and
> leaves its range sorted. The total is the left count, right count, and count
> of pairs crossing between the two halves.
>
> For each sorted left value, matching right values form a prefix. I advance a
> right pointer while the left value is greater than twice the right value.
> The prefix length is the pointer minus the right half's starting index.
> Since left values increase, I never reset that pointer during counting.
>
> After counting, I reset the merge pointers and merge the halves. Counting must
> happen before merging so their original group membership is still available.
> I use Long arithmetic for doubling. Each recursion level takes linear work,
> giving O(n log n) time and O(n) auxiliary space.”

Practice explaining:

1. Why does sorting within the halves preserve the cross-half index condition?
2. Why do matches form a prefix, including when values are negative?
3. Why does `j` move only forward, yet the full prefix gets counted for every left value?
4. Why is the prefix length `j - (mid + 1)` rather than `j - mid`?
5. Why do counting and merging require separate pointer passes?
6. Why does conversion to `Long` need to happen before multiplication?
