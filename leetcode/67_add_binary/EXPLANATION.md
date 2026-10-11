# 67. Add Binary

## Contract and constraints

Return the sum of two binary strings as a binary string. Each input has length
1 through 10,000, contains only `0` and `1`, and has no leading zeros except
for `"0"`. The inputs are immutable; construct a separate result.

Examples: `"11" + "1" = "100"`, `"1010" + "1011" = "10101"`.
In an interview, establish the base, maximum length, valid digits, and rules
for leading zeros before choosing a representation.

## Solution evolution

### 1. Your original implementation: reverse both inputs

Reversing each input puts its least significant digit at index 0. Scan up to
the longer length, use zero for a missing digit, and add the incoming carry.
Append each output bit and reverse the result after handling a final carry.

```kotlin
class Solution {
    fun addBinary(a: String, b: String): String {
        val ra = a.reversed()
        val rb = b.reversed()
        val sbr = StringBuilder()

        val length = maxOf(ra.length, rb.length)
        var carry = 0
        for (i in 0 until length) {
            val ca = if (i < ra.length) ra[i] - '0' else 0
            val cb = if (i < rb.length) rb[i] - '0' else 0
            val sum = ca + cb + carry

            carry = sum / 2
            val bit = sum % 2
            sbr.append(bit)
        }
        if (carry == 1) {
            sbr.append(carry)
        }

        return sbr.reverse().toString()
    }
}
```

This is correct column addition. Let n be the longer input length. Reversing
the inputs, scanning, and constructing the answer together take O(n) time and
O(n) extra space. The two reversed strings are avoidable allocations.

What to say:

> “I can reverse the inputs to align their least significant bits at index zero
> and simulate addition with a carry. This is linear, but the reversed inputs
> copy data just to change traversal order.”

### 2. Your final implementation: traverse the original strings backward

Descending pointers provide the same digit order without reversed copies.
Including `carry != 0` in the loop also handles the final carry through the
same logic. This reduces allocations while retaining O(n) time and O(n) space
for the output construction.

```kotlin
class Solution {
    fun addBinary(a: String, b: String): String {
        var i = a.lastIndex
        var j = b.lastIndex
        val sbr = StringBuilder()
        var carry = 0

        while (i >= 0 || j >= 0 || carry != 0) {
            val ca = if (i >= 0) a[i] - '0' else 0
            val cb = if (j >= 0) b[j] - '0' else 0
            val sum = ca + cb + carry

            carry = sum / 2
            val bit = sum % 2
            sbr.append(bit)
            i--
            j--
        }

        return sbr.reverse().toString()
    }
}
```

The final code preserves your arithmetic implementation. An optional capacity
hint, `StringBuilder(maxOf(a.length, b.length) + 1)`, can avoid buffer growth;
it does not change the algorithm's complexity.

What to say:

> “I can read each original string from its last index instead of reversing it.
> I continue while either string has digits or carry remains, appending the
> least significant bits first and reversing the result once.”

| Approach | Time | Space including result construction | Difference |
| --- | --- | --- | --- |
| Reversed input copies | O(n) | O(n) | Stores two extra input copies |
| Descending input pointers | O(n) | O(n) | Avoids those copies; keeps output buffer |

Converting entire inputs to `Int` or `Long` cannot satisfy the constraints:
the 65-bit string `"1" + "0".repeat(64)` represents 2⁶⁴, already beyond either
type. Column arithmetic never needs to represent the entire number.

## Variables and column arithmetic

- `i`, `j`: indexes of the next unprocessed input digits, or negative when exhausted.
- `ca`, `cb`: digit values, with missing digits treated as zero.
- `carry`: overflow from the lower columns into the current column.
- `sum`: `ca + cb + carry`, in the range 0 through 3.
- `bit`: the current result digit, `sum % 2`.
- `sbr`: completed result digits in least-significant-first order.

For every nonnegative column total, `sum = 2 * (sum / 2) + sum % 2`.
Thus division produces the carry and remainder produces the current bit.
The incoming carry starts at 0. Since both digits are at most 1, a carry at
most 1 gives a total at most 3, so the outgoing carry also stays at most 1.

## Complete dry run of your final implementation

Input: `a = "11"`, `b = "1"`. Initial state:
`i = 1`, `j = 0`, `carry = 0`, `sbr = ""`.

| Step | Before `(i, j, carry)` | Input branches: `ca`, `cb` | `sum` | Appended `bit` | After `(i, j, carry)` | `sbr` after |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | `(1, 0, 0)` | Both present: 1, 1 | 2 | 0 | `(0, -1, 1)` | `"0"` |
| 2 | `(0, -1, 1)` | Only a present: 1, 0 | 2 | 0 | `(-1, -2, 1)` | `"00"` |
| 3 | `(-1, -2, 1)` | Neither present: 0, 0 | 1 | 1 | `(-2, -3, 0)` | `"001"` |

At the next condition, both pointers are negative and carry is zero, so the
loop stops. Reversing `"001"` returns `"100"`. Notice that negative indexes
are never dereferenced: their conditional branches supply zero instead.

## Correctness, termination, and optimality

**Invariant:** Before each iteration, `sbr` contains the correct result bits
for all processed lower columns, in reverse order, and `carry` is exactly
their overflow into the next unprocessed column.

Initially no columns have been processed and carry is zero. Each iteration
reads the next digits (or zero), adds the incoming carry, and splits that total
into its correct output bit and outgoing carry. Appending the bit and moving
the pointers preserves the invariant. On termination all input digits and
carry have been processed; reversing the stored bits gives the complete sum.

Both pointers decrease once per iteration. After at most n iterations, both
inputs are exhausted. A remaining carry is at most 1, so one additional
iteration appends it and clears it. There are at most n + 1 iterations.

The scan, amortized builder appends, final reversal, and conversion to a string
take O(n) time. The builder and returned string take O(n) storage; the arithmetic
state alone is O(1). Even excluding the returned immutable string, the separate
builder is O(n) auxiliary space. Avoid calling the entire implementation O(1)
space just because it uses only a few numeric variables.

Time is asymptotically optimal: a valid sum has n or n + 1 digits, so producing
the requested output already requires Ω(n) work. The O(n) output-size lower
bound does not prove a separate O(n) auxiliary buffer is unavoidable.

## Arithmetic and bitwise variants in Kotlin

For this nonnegative `sum`, these two replacements are equivalent:

```kotlin
val bit = sum and 1  // instead of sum % 2
carry = sum shr 1    // instead of sum / 2
```

`shr 1` shifts right by one position, preserving the sign. Masking with 1
keeps only the rightmost bit. For `sum = 3 = 11₂`, that rightmost bit is 1
and shifting gives the carry 1. For totals 0, 1, 2, 3, `(bit, carry)` is
respectively `(0,0)`, `(1,0)`, `(0,1)`, `(1,1)`.

Neither replacement improves asymptotic complexity. Keep the arithmetic version
when it communicates column addition more clearly. The nonnegative condition
matters: `-3 shr 1` is -2, whereas Kotlin's integer `-3 / 2` is -1.

See the [Kotlin/C++ bitwise comparison and masking patterns](../../study-notes/algorithm-concepts-cheatsheet.md#bitwise-operations-act-on-integer-bits-not-boolean-conditions).

## Edge cases and interview rehearsal

| Inputs | Expected | What it checks |
| --- | --- | --- |
| `"0"`, `"0"` | `"0"` | Zero result is still one digit |
| `"1"`, `"1"` | `"10"` | Final carry |
| `"111"`, `"1"` | `"1000"` | Carry propagation through several columns |
| `"1"`, `"1000"` | `"1001"` | Unequal lengths and exhausted-input branches |
| `"1010"`, `"1011"` | `"10101"` | Supplied example with mixed digits |

> “I simulate binary addition from right to left because the lower column
> determines the carry into the higher one. Missing digits contribute zero.
> Each total splits into a bit and a carry using remainder and division by two.
> I continue until both inputs and carry are exhausted, then reverse the result.
> This takes optimal linear time and linear space for result construction.”

Practice answering:

1. What allocations did descending pointers eliminate from your first version?
2. Why can the carry never be 2 when adding two binary strings?
3. Why would `&&` stop too early? Use `"11" + "1"` as a counterexample.
4. State the invariant and explain why the loop needs at most one extra iteration.
5. Why does the final reversal preserve O(n) time, and why is the builder still O(n) space?
6. Why are `sum and 1` and `sum shr 1` equivalent to your arithmetic here?
7. For positional base k >= 2, how would remainder and carry change?

Rebuild the loop from the invariant, then dry-run `"111" + "1"` before rereading the code.
