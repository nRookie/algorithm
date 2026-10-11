# 190. Reverse Bits

## Contract

Reverse all positions of a 32-bit signed Kotlin `Int`, returning the resulting
32-bit pattern as an `Int`. Input bit i, counted from zero at the right, moves
to position `31 - i`. Leading zeros and the sign bit are part of the input.
A negative result is valid when the reversed pattern's highest bit is 1.

```text
43261596:  00000010100101000001111010011100
964176192: 00111001011110000010100101000000
```

The entire decimal number is converted to binary. Its last decimal digit does
not determine a binary suffix: 6 alone is `110₂`, not `101₂` (which is 5).

## Saved interactive diagram

Open [the interactive five-stage diagram](VISUALIZATION.html) in a browser.
Use Previous and Next to inspect the group swaps; choose an original bit to
follow its movement. Tile labels `b0` through `b31` identify original positions,
while the selected-bit detail reports its current source and destination.
Brackets mark the blocks within which a swap occurs. At narrow widths a larger
block can span multiple displayed rows; the bit sequence is still continuous.

The [editable diagram source](../../output/visualizations/reverse-bits-swaps.html)
is retained separately. `VISUALIZATION.html` is a standalone browser export,
so viewing the saved diagram does not depend on the chat's inline preview.

## Solution evolution

### 1. Your first attempt: extract into a string, then reverse it again

```kotlin
class Solution {
    fun reverseBits(n: Int): Int {
        val sb = StringBuilder()
        var current = n
        while (current > 0) {
            val bit = current and 1
            current = current shr 1
            sb.append(bit)
        }
        var sum = 0
        for (c in sb.reversed()) {
            if (c == '1')
                sum = sum * 2 + 1
            else
                sum = sum * 2
        }
        return sum
    }
}
```

This draft is incorrect. With `n = 6`, extraction appends `0, 1, 1`, producing
`sb = "011"`. Reading `sb.reversed()` parses `"110"` and reconstructs 6 instead
of reversing it. Also, stopping when `current` becomes zero omits leading zeros,
and `current > 0` skips negative inputs entirely.

Even parsing `"011"` directly would produce 3, while reversing all 32 positions
of 6 produces `01100000000000000000000000000000`, or 1610612736.

### 2. Your corrected string implementation

```kotlin
class Solution {
    fun reverseBits(n: Int): Int {
        val sb = StringBuilder()
        var i = 32
        var current = n
        while (i > 0) {
            val bit = current and 1
            current = current ushr 1
            i--
            sb.append(bit)
        }
        var sum = 0
        for (c in sb) {
            if (c == '1')
                sum = sum * 2 + 1
            else
                sum = sum * 2
        }
        return sum
    }
}
```

Exactly 32 extractions preserve the full width. Reading `sb` directly preserves
the reversed order. Parsing uses `sum = sum * 2 + bit`: shift the constructed
prefix left, then append its next digit. Kotlin `Int` arithmetic wraps to the
32-bit pattern; a negative signed result is allowed.

What to say:

> “Extracting low bits already gives the reversed order. I need all 32 positions,
> and I must parse the collected bits without reversing them a second time.”

### 3. Further improvement: accumulate directly without a string

```kotlin
class Solution {
    fun reverseBits(n: Int): Int {
        var current = n
        var result = 0
        repeat(32) {
            val bit = current and 1
            result = (result shl 1) or bit
            current = current ushr 1
        }
        return result
    }
}
```

The extraction and parsing loops can be combined: append each extracted bit
directly to `result`. This performs 32 extract-and-append iterations and removes
the builder allocation. After k iterations, `result` contains the original
lowest k bits in reverse order, with unused higher positions zero.

What to say:

> “I can consume each bit once and append it directly to the integer result.
> Left shift makes room; OR writes the extracted bit into that empty position.”

### 4. Your final implementation: swap growing groups in parallel

```kotlin
class Solution {
    fun reverseBits(n: Int): Int {
        var x = n
        val mask1 = 0x55555555
        val mask2 = 0x33333333
        val mask3 = 0x0f0f0f0f
        val mask4 = 0x00ff00ff
        val mask5 = 0x0000ffff

        x = ((x and mask1) shl 1) or ((x and mask1.inv()) ushr 1)
        x = ((x and mask2) shl 2) or ((x and mask2.inv()) ushr 2)
        x = ((x and mask3) shl 4) or ((x and mask3.inv()) ushr 4)
        x = ((x and mask4) shl 8) or ((x and mask4.inv()) ushr 8)
        x = ((x and mask5) shl 16) or ((x and mask5.inv()) ushr 16)
        return x
    }
}
```

This preserves the final implementation you supplied, with formatting cleanup.
We derived the group movements and masks together using an 8-bit example before
extending them to all 32 positions. Each line reads the current `x` on both
sides and assigns the combined result only afterward.

An optional simplification of only the final line is:

```kotlin
x = (x shl 16) or (x ushr 16)
```

At that stage, the shifts themselves discard the opposite 16-bit halves, so
the masks are unnecessary. Your saved five-mask version is already correct.

What to say:

> “Instead of handling one bit per iteration, I swap all adjacent 1-bit groups,
> then 2-, 4-, 8-, and 16-bit groups. Each stage doubles the block size whose
> contents are fully reversed, ending with the entire 32-bit word.”

| Correct approach | Work for a 32-bit input | Storage | Improvement |
| --- | --- | --- | --- |
| Fixed-width string | 32 extractions and 32 parsing steps | Builder plus integer state | Corrects width and order |
| Direct accumulation | 32 extract-and-append iterations | Integer state | Removes the string and second pass |
| Growing-group swaps | Five stages of masks, shifts, and OR | Integer state and masks | Moves many groups per stage |

All three have O(1) time and O(1) space for fixed 32-bit inputs. The string still
allocates storage for 32 characters. Fewer stages do not establish measured
speed: each group-swap stage contains multiple operations, and runtime depends
on the implementation and hardware. No benchmark was performed.
For a generalized width W that is a power of two, the bit loop has W iterations
and the group method has log₂ W stages. Word operations on arbitrary-size
integers must be costed separately; they are not automatically constant-time.

## Why hexadecimal masks are easier to read

Each hex digit represents four bits. A 32-bit mask can be displayed using
eight hex digits. Leading zero digits can be omitted without changing its value.

| Swap size | Lower-group mask | Repeating binary selection | Reversed block size afterward |
| --- | --- | --- | --- |
| 1 bit | `0x55555555` | `01` | 2 bits |
| 2 bits | `0x33333333` | `0011` | 4 bits |
| 4 bits | `0x0f0f0f0f` | `00001111` | 8 bits |
| 8 bits | `0x00ff00ff` | `0000000011111111` | 16 bits |
| 16 bits | `0x0000ffff` | 16 zeros followed by 16 ones | 32 bits |

The complementary mask selects the higher group in each block. Using `.inv()`
gives an `Int` complement without a large positive literal such as `0xAAAAAAAA`,
which does not fit a positive signed `Int` and can be inferred as `Long`.

## Our complete 8-bit derivation

Original input: `10110010`. The 8-bit masks here are for this demonstration;
the real implementation repeats their patterns across all 32 bits.

| Swap size | Before | Selected lower groups | Shift left | Selected higher groups | Unsigned shift right | OR result |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | `10110010` | `00010000` with `01010101` | `00100000` | `10100010` with `10101010` | `01010001` | `01110001` |
| 2 | `01110001` | `00110001` with `00110011` | `11000100` | `01000000` with `11001100` | `00010000` | `11010100` |
| 4 | `11010100` | `00000100` with `00001111` | `01000000` | `11010000` with `11110000` | `00001101` | `01001101` |

The terminal state `01001101` is the full reversal of `10110010`.
The distinction clarified during practice was moving whole groups: a 2-bit
stage changes `[01 | 11]` into `[11 | 01]`; it does not turn `01` into `10` again.

Your own commented example used `|11|00|01|10|`. Its polished, corrected account is:

```text
Lower bits moved left:  |10|00|10|00|
Higher bits moved right:|01|00|00|01|
Combined:              |11|00|10|01|
```

The last pair in your original OR comment was `11`; it should be `01`.

## Every stage on the supplied 32-bit example

| State | Binary pattern | Signed decimal value |
| --- | --- | --- |
| Initial | `00000010100101000001111010011100` | 43261596 |
| After 1-bit swaps | `00000001011010000010110101101100` | 23604588 |
| After 2-bit swaps | `00000100100100101000011110010011` | 76711827 |
| After 4-bit swaps | `01000000001010010111100000111001` | 1076459577 |
| After 8-bit swaps | `00101001010000000011100101111000` | 692074872 |
| After 16-bit swaps | `00111001011110000010100101000000` | 964176192 |

## Correctness proof

First prove one stage performs its intended group swap. Inside a 2s-bit block,
write the two s-bit groups as `[A | B]`. The mask keeps B and clears A; shifting
left by s produces `[B | zeros]`. Its complement keeps A and clears B; unsigned
right shift by s produces `[zeros | A]`. OR gives `[B | A]` because the destination
fields do not overlap. Repeating the mask across the entire word performs this
swap independently within every block, without moving bits across its boundary.

**Invariant:** After the stage swapping s-bit groups, every 2s-bit block is
reversed relative to its contents in the original input.

- **Initialization:** One-bit groups are trivially reversed. Swapping adjacent
  one-bit groups therefore reverses every two-bit block.
- **Preservation:** Suppose both s-bit halves of an original block `[A | B]`
  are already internally reversed. The current block is
  `[reverse(A) | reverse(B)]`. Swapping its halves yields
  `[reverse(B) | reverse(A)]`, exactly `reverse(A + B)`.
- **Completion:** Stages 1, 2, 4, 8, and 16 establish reversed blocks of sizes
  2, 4, 8, 16, and finally 32. The entire input pattern is therefore reversed.

Labels make this visible without relying on particular zero/one values:

```text
Original:   a b c d e f g h
Swap 1-bit: b a d c f e h g
Swap 2-bit: d c b a h g f e
Swap 4-bit: h g f e d c b a
```

Termination is immediate: the implementation executes five fixed assignments.

## `shr` and `ushr`: the important qualification

`shr` copies the sign bit; `ushr` fills with zeros. For example:

```text
-8 shr 1  = -4
-8 ushr 1 = 2147483644
-1 shr 1  = -1 forever under repeated shifts
```

For the 32-iteration loop extracting the lowest bit before shifting, either
operator reads the same 32 original bits. Inserted bits would only be extracted
starting with iteration 33. `while (current > 0)` would still skip negative
inputs regardless of which operator is used, and a loop waiting for zero with
`shr` can get stuck at -1.

For the group-swap implementation, use `ushr`: a masked higher-group value can
be negative, and sign extension would insert ones into fields intended to stay
zero before OR. With `n = Int.MIN_VALUE`, using `shr` in the first group stage
already inserts an unwanted 1 at position 31. Thus the fixed-count loop's shift
equivalence does not justify changing these grouped shifts.

## Mistakes to recognize next time

- Extracting low bits already reverses their order; reversing the string again
  undoes that movement.
- A value becoming zero does not mean every fixed-width position was processed.
- A full-width mask must include every relevant group. With `n = 256`, using
  only `0x55` and `0xAA` clears bit 8 during the first stage, giving zero forever.
- Group size grows, but word width stays 32 at every stage. Hexadecimal avoids
  accidentally writing short masks or miscounting a long sequence of ones.
- OR safely combines these fields because their destination positions are
  disjoint; that requires masks, shift distances, and zero filling to agree.

## Validation and interview rehearsal

The final five-mask Kotlin implementation compiled and passed 8 edge cases,
all 32 single-bit-position cases, and 10,000 generated `Int` inputs against
JVM `Integer.reverse`. These are observed checks; the block invariant above
is the correctness proof.

Useful boundaries: `0 → 0`, `1 → Int.MIN_VALUE`, `Int.MIN_VALUE → 1`,
`-1 → -1`, `6 → 1610612736`, and the supplied example.
Reversing twice should restore the original value, but that check alone is
insufficient: an implementation that returns its input also passes it.

> “I swap neighboring groups of sizes 1, 2, 4, 8, and 16. Each mask selects
> the lower group in every block, and its inverse selects the higher group.
> Opposite shifts exchange their positions, and OR combines disjoint fields.
> After each stage, every block twice that group size is reversed, because
> exchanging two already-reversed halves reverses their entire concatenation.
> The final stage covers all 32 bits, using fixed time and constant storage.”

Practice rebuilding the masks from group sizes, explaining why they must cover
all 32 positions, and proving the reversed-block invariant before memorizing code.
