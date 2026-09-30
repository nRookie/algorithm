# Why three reversals rotate an array to the right

The key idea is that **reversing the whole array puts the two blocks in the
correct order, but reverses the values inside each block. Two smaller reversals
repair those internal orders.**

This proof follows the implementation in [ReversalSolution.kt](ReversalSolution.kt).
All indexes are zero-based, and range endpoints are inclusive.

## 1. Establish what rotation must produce

Let `n` be the nonempty array length and `s = k % n`. Moving right n times
restores every element to its starting position, so only s matters.

If s is zero, the answer is the original array and the implementation returns.
For the rest of the proof, assume `0 < s < n`.

Split the original array into two blocks:

- **A:** the first `n - s` elements.
- **B:** the last s elements.

A right rotation by s moves B to the front and A behind it, preserving the
order within each block. Our goal is therefore:

```text
Original:  A B
Target:    B A
```

For `[1,2,3,4,5,6,7]` with s = 3:

```text
A = [1,2,3,4]       B = [5,6,7]
Target = [5,6,7 | 1,2,3,4]
```

This is the problem we need to solve: exchange the blocks without losing their
internal order or allocating another array.

## 2. Understand the effect of one whole-array reversal

Write `R(X)` for block X in reverse order. Reversing concatenated blocks obeys:

```text
R(A B) = R(B) R(A)
```

Why? When we read the original array from its end to its beginning, we first
encounter B backward, then A backward.

```text
Before:  [1,2,3,4 | 5,6,7]       A, B
After:   [7,6,5 | 4,3,2,1]       R(B), R(A)
```

The blocks have reached their desired positions: B's values occupy the first
s positions and A's values occupy the rest. Only their internal orders are wrong.

## 3. Repair the first block

Reverse indexes `0..s-1`. This region contains exactly R(B).
Reversing a sequence twice restores it: `R(R(B)) = B`.

```text
[7,6,5 | 4,3,2,1]  →  [5,6,7 | 4,3,2,1]
 R(B)      R(A)           B        R(A)
```

The prefix is now correct. The operation does not touch the suffix.

## 4. Repair the second block

Reverse indexes `s..n-1`. This region contains exactly R(A), so it becomes A.

```text
[5,6,7 | 4,3,2,1]  →  [5,6,7 | 1,2,3,4]
   B       R(A)           B        A
```

The result is B A, exactly the target established in step 1.

The complete proof can be written as three transformations:

```text
       reverse all       reverse first s       reverse remaining n-s
A B  ─────────────→  R(B) R(A)  ───────────→  B R(A)  ───────────────→  B A
```

This reasoning works for any values, including duplicates and negative numbers.
It depends only on positions and block lengths, not on the values themselves.

## 5. Confirm by following an arbitrary original index

The block argument is already a correctness proof. We can independently check
the destination formula: an element originally at index i must finish at
`(i + s) % n`.

Reversing an inclusive interval `[L, H]` maps a position p to `L + H - p`.
In particular, the whole-array reversal maps i to `p = n - 1 - i`.

### Case A: the element originally belongs to A

Here `0 <= i < n - s`. After the whole reversal, p is in `[s, n-1]`.
The prefix reversal leaves it alone; the suffix reversal maps it to:

```text
s + (n - 1) - p
= s + (n - 1) - (n - 1 - i)
= i + s
```

Since `i + s < n`, this is exactly `(i + s) % n`.

### Case B: the element originally belongs to B

Here `n - s <= i < n`. After the whole reversal, p is in `[0, s-1]`.
The prefix reversal maps it to:

```text
0 + (s - 1) - p
= s - 1 - (n - 1 - i)
= i + s - n
```

The suffix reversal leaves it alone. Since `n <= i + s < 2n`, this is exactly
`(i + s) % n`.

These two cases cover every original position. Each element reaches precisely
its required destination, proving the result is a right rotation by s.

## 6. Why the reversal helper is correct

The helper reverses an interval by swapping its two ends, then moving inward:

```kotlin
private fun reverseRange(nums: IntArray, start: Int, end: Int) {
    var left = start
    var right = end
    while (left < right) {
        val temp = nums[left]
        nums[left] = nums[right]
        nums[right] = temp
        left++
        right--
    }
}
```

Its loop invariant is: within the requested interval, every position outside
`left..right` already holds its final reversed value; the remaining inner
positions have not yet been processed.

Initially there are no processed positions, so this holds. Swapping the two
current ends puts both into their final reversed positions. Moving the pointers
inward preserves the invariant and shrinks the unfinished region by two.

Eventually the pointers meet or cross. If they meet, the middle element already
belongs in that position. Nothing remains to process, so the interval is reversed.
The temporary variable preserves one endpoint while the other is overwritten.

## 7. Connect the proof to the actual calls

```kotlin
val shift = k % nums.size
if (shift == 0) return

reverseRange(nums, 0, nums.lastIndex)       // A B → R(B) R(A)
reverseRange(nums, 0, shift - 1)           // R(B) → B
reverseRange(nums, shift, nums.lastIndex)  // R(A) → A
```

After the whole reversal, the split is at **s**, because the front block is B
and its length is s. In the original array, the split was at **n - s**.
Confusing these two boundaries is a common source of errors.

Reversing the original two blocks first is another valid ordering:

```text
A B → R(A) B → R(A) R(B) → B A
```

That ordering must use the original ranges `0..n-s-1` and `n-s..n-1`, then
reverse the whole array. After the whole-array-first step, the two disjoint
repair reversals can also be performed in either order.

## 8. Complexity and edge cases

The reversal lengths are n, s, and n-s. The exact number of swaps is:

```text
floor(n / 2) + floor(s / 2) + floor((n - s) / 2) <= n
```

Thus worst-case time is O(n). The helper is iterative and uses only a temporary
value and scalar indexes, so auxiliary space is O(1). Three sequential calls
do not create recursion or an additional array.

- `k = 0` or a multiple of n: s is zero, so return without modifying anything.
- `n = 1`: s is always zero, so return.
- `k > n`: normalization handles all full rotations before choosing the split.
- `s = 1` or `s = n - 1`: a one-element block requires no swaps to reverse.
- Empty arrays are outside the supplied contract; a general-purpose function
  accepting them would need a guard before computing `k % nums.size`.

## Interview explanation

> “I split the array into A, the first n minus s values, and B, the last s,
> where s is k modulo n. A right rotation should produce B followed by A.
> Reversing the whole array gives reversed B followed by reversed A, so the
> blocks are already in the right positions. Reversing each block restores
> its internal order. Each reversal uses two pointers and swaps, giving linear
> time and constant extra space.”

To check your understanding, derive the ranges for n = 5 and k = 2 without
looking at the code, then explain why reversing only the entire array is not enough.
