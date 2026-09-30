# Why cyclic replacement correctly rotates an array

Executable code: [CyclicSolution.kt](CyclicSolution.kt).
Run `bash run.sh` in this folder to test it alongside the copy and reversal methods.

## 1. The goal fixes every destination

Let `n` be the nonempty array length and `s = k % n`. If s is zero, return:
every value already occupies its required position. Assume `0 < s < n` below.

The original value at index i must move to:

```text
f(i) = (i + s) % n
```

A **cycle** is a chain of these destination arrows returning to its starting
index. It does not mean a `for` loop, a scan in index order, or an arbitrary
choice of processing order.

For n = 6 and s = 3, label the original values A through F:

```text
Index:      0  1  2  3  4  5
Original:  [A, B, C, D, E, F]
Required:  [D, E, F, A, B, C]

Destination cycles:
    0 ──→ 3       1 ──→ 4       2 ──→ 5
    ↑     │       ↑     │       ↑     │
    └─────┘       └─────┘       └─────┘
```

## 2. Why we follow a displaced value immediately

Your proposed order `0 → 3`, then `1 → 4`, then `2 → 5` is a valid order if
we preserve D, E, and F for later. Otherwise those three values are overwritten.
The copy-based method preserves all original values in another array.

Cyclic replacement instead keeps a single value in transit:

```text
Pick up A from index 0.
    │
    ▼
Write A at index 3, but first SAVE D.
Array: [A, B, C, A, E, F]      carrying D
    │
    ▼
D belongs at index 0: write it there.
Array: [D, B, C, A, E, F]      cycle 0 → 3 → 0 complete
```

Now repeat from index 1, carrying B then E, and from index 2, carrying C then F.
We never need to keep a growing collection of displaced values.

## 3. Connect each statement to that movement

```kotlin
val next = (current + shift) % n // Where the carried value belongs.
val displaced = nums[next]      // Preserve the value about to be overwritten.
nums[next] = carried            // Place the carried value permanently.
carried = displaced             // Continue with the displaced original value.
current = next                  // Its original index becomes our current index.
moved++                         // One more destination has been filled.
```

Saving `displaced` must happen before the write. Otherwise its original value
would be lost. The algorithm uses a constant number of temporary variables;
“one value in transit” does not mean there is literally only one local variable.

The `do ... while` runs once before checking `current != start`, because at
initialization `current` already equals `start`. Comparing values instead of
indexes would fail to identify cycle boundaries reliably when values repeat.

## 4. Trace every write for n = 6, s = 3

Initial array: `[A,B,C,D,E,F]`; `moved = 0`.

| start | current → next | carried before | displaced | Array after write | moved |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 → 3 | A | D | `[A,B,C,A,E,F]` | 1 |
| 0 | 3 → 0 | D | A | `[D,B,C,A,E,F]` | 2 |
| 1 | 1 → 4 | B | E | `[D,B,C,A,B,F]` | 3 |
| 1 | 4 → 1 | E | B | `[D,E,C,A,B,F]` | 4 |
| 2 | 2 → 5 | C | F | `[D,E,C,A,B,C]` | 5 |
| 2 | 5 → 2 | F | C | `[D,E,F,A,B,C]` | 6 |

On the closing write of each cycle, the displaced value is the old starting
value. It has already been placed at its destination, so it does not need
another move. The loop stops that cycle immediately when `current == start`.

## 5. Why the destination arrows form disjoint cycles

The map f has an inverse:

```text
previous(j) = (j - s + n) % n
```

Each index therefore has exactly one outgoing arrow and exactly one incoming
arrow. Following arrows in a finite set must eventually repeat an index.
The first repeat must be the starting index: entering any earlier visited
non-start index from a new predecessor would give that index two different
incoming arrows, which is impossible.

Thus every index belongs to a closed cycle. Two cycles cannot partly overlap:
once they share an index, its unique successor forces them to follow the same
cycle. Consequently the cycles partition the array indexes.

This property is called a **permutation** of the indexes: a rearrangement where
each index has one unique destination and one unique source.

## 6. Prove that processing one cycle is correct

Let `original[i]` denote the value before the algorithm began. This is notation
for the proof, not an array the implementation allocates.

At the beginning of each inner-loop iteration:

1. `carried` equals `original[current]`.
2. Every destination already written in this cycle contains its required final value.
3. Positions not yet written retain their original values.

**Initialization:** the outer loop chooses an untouched cycle, sets `current`
to `start`, and picks up `nums[start]`. No destination in that cycle has yet
been written, so all three statements hold.

**Maintenance:** compute `next = f(current)`. Writing `original[current]`
there is correct by the rotation definition. Until the closing step, `next`
has not been visited, so its original value is safely captured in `displaced`.
Assigning it to `carried` and moving `current` to `next` establishes the
invariant for the next iteration. Earlier finished destinations are untouched.

**Closing step:** when `next == start`, the same write correctly fills the
last destination. The saved starting value has already been placed earlier,
and the loop exits rather than processing it again.

Therefore, after the cycle closes, every index in that cycle holds its correct
rotated value. This is an invariant proof: initialization plus maintenance
establish the property through all iterations, and the exit condition yields
the required result for the cycle.

## 7. Why increasing start by one finds all cycles without revisiting them

The specific code uses `start++`, not a visited array. We must justify that
choice; merely knowing cycles exist is not enough.

Let `g = gcd(n, s)`, and write `n = g × a`, `s = g × b`, where a and b share
no common factor greater than 1. Returning to a starting index after t jumps
requires `t × s` to be divisible by n. Equivalently, a must divide `t × b`.
Since a and b are coprime, a must divide t. The smallest positive such t is a,
so every cycle has exactly `a = n / g` indexes.

Every jump preserves the index's remainder modulo g: both adding s and wrapping
by subtracting n change it by a multiple of g. Each remainder group contains
exactly `n / g` indexes, the same as one cycle's length. Thus a cycle visits the
entire group with its starting remainder.

```text
n = 6, s = 2, g = 2:
start 0: remainder 0 group  {0,2,4}   cycle 0 → 2 → 4 → 0
start 1: remainder 1 group  {1,3,5}   cycle 1 → 3 → 5 → 1

n = 6, s = 3, g = 3:
start 0: remainder 0 group  {0,3}     cycle 0 → 3 → 0
start 1: remainder 1 group  {1,4}     cycle 1 → 4 → 1
start 2: remainder 2 group  {2,5}     cycle 2 → 5 → 2
```

Starting at `0,1,...,g-1` therefore processes distinct cycles. After those g
cycles, `moved = g × (n/g) = n`, and the outer loop exits before revisiting
any cycle. Computing the gcd is unnecessary in the code because `moved`
detects when all positions are finished.

## 8. Termination and complexity

Each inner loop returns to its start after exactly `n/g` writes. Each outer
iteration processes a new cycle, and there are g cycles. Thus the algorithm
terminates after exactly n writes when s is nonzero.

Every destination has been written once, and the single-cycle proof says each
write is correct. Therefore the final array is the requested right rotation.

Nested loops do not imply quadratic time here: the total inner iterations across
all cycles are n, not n for every starting index. Time is O(n), and the fixed
number of scalar variables uses O(1) auxiliary space. When s is zero, the code
returns immediately. Nonempty input and nonnegative k match the problem contract.

## Interview explanation

> “Each original value at i belongs at (i + shift) modulo n. I carry a value
> to its destination, saving the displaced value first, then continue with that
> value. Returning to the starting index finishes a cycle. Rotation is a
> permutation, so its destination arrows form disjoint cycles. I process new
> cycles until n values have moved. Each write places one value correctly and
> preserves the next, giving linear time and constant extra space.”

Practice tracing `[1,2,3,4,5,6]` with k = 2 and explaining exactly where the
displaced value lives after each write. Then contrast that with visiting source
indexes `0,1,2,...` while reading from an unchanged snapshot.
