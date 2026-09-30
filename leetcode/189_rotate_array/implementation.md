# Rotate Array: following the cyclic implementation

Read this beside [CyclicSolution.kt](CyclicSolution.kt). This guide describes
that implementation; it does not change the solution.

The task is to rotate a nonempty array to the right by `k` positions.

## 1. Source and destination come first

- **Source**: the index where a value was in the original array.
- **Destination**: the index where that value belongs after rotation.

For `n = 7`, `k = 3`:

```text
index:     0 1 2 3 4 5 6
original: [a,b,c,d,e,f,g]
result:   [e,f,g,a,b,c,d]

original index 0 -- a moves right by 3 --> destination index 3
```

Two formulas describe the SAME movement from opposite ends:

```kotlin
// Given a source, find its destination:
val destination = (source + shift) % n

// Given a destination, find its source:
val source = (destination - shift + n) % n
```

Here `shift = k % n`, so `0 <= shift < n`. Adding `n` in the second
formula avoids a negative remainder in Kotlin.

Your copy-based formula is correct:

```kotlin
result[current] = original[(n + current - shift) % n]
```

In THAT formula, `current` means **destination**. A clearer spelling is:

```kotlin
val source = (n + destination - shift) % n
result[destination] = original[source]
```

In the cyclic code below, `current` instead tracks the **source of the carried
value**. Do not transfer its meaning from one implementation to the other.

## 2. Solution evolution: from a copy to a carried value

With an unchanged copy, we can fill each destination from its original source.
That takes O(n) time and O(n) extra space. We can also express this as pushing
each original value forward: `result[(source + shift) % n] = original[source]`.

To do that directly in `nums`, we must protect the value we are about to
overwrite. Save it, write the carried value, then carry the saved value to its
own destination. This leads to the cycle-following implementation: O(n) time
and O(1) extra space.

## 3. Variable definitions

| Variable | Meaning in `CyclicSolution.kt` |
|---|---|
| `nums` | The array we modify. During execution, it mixes original and already-placed values. |
| `n` | Number of elements. |
| `k` | Requested number of right-rotation steps. |
| `shift` | Effective rotation, `k % n`. If zero, nothing needs to move. |
| `start` | Index where the current cycle began. Returning here completes the cycle. |
| `current` | At the beginning of an active iteration, the original source index of the value in `carried`. |
| `carried` | The value held outside the array, ready to be placed at its final destination. |
| `next` | Destination index for `carried`: `(current + shift) % n`. |
| `displaced` | Value read from `nums[next]` before that position is overwritten. |
| `moved` | Total values placed into their final positions across all cycles. |

```text
carried = value originally from current
                    |
                    v
          write it at next = (current + shift) % n
```

Important: `carried` does NOT have to equal `nums[current]`.
We may have overwritten that array slot while preserving its old value in
`carried`.

## 4. Read one iteration line by line

Initial state: `nums = [a,b,c,d,e,f,g]`, `start = 0`, `current = 0`,
`carried = a`, `moved = 0`, `shift = 3`.
Letters represent distinct values for tracing; the actual function uses integers.

```kotlin
val next = (current + shift) % n
```

`next = 3`. The `a` we are holding belongs at index 3.

```kotlin
val displaced = nums[next]
```

Save `d` before overwriting index 3. Now `displaced = d`.

```kotlin
nums[next] = carried
```

Put `a` in its final position:

```text
index:     0 1 2 3 4 5 6
nums:     [a,b,c,a,e,f,g]
                 ^
               wrote a

displaced = d  <-- d is safe outside the array
```

```kotlin
carried = displaced
current = next
moved++
```

Now we hold `d`, which originally came from index 3:

```text
current = 3
carried = d
moved   = 1
```

`nums[current]` is now `a`, but `carried` is `d`. This is intentional.
The next iteration sends `d` from its original index 3 to destination 6.

The two temporary copies of `a` do not mean a value was lost. Its old slot will
be overwritten later, and `d` is preserved in `carried`.

## 5. Complete dry run

Index path for `n = 7`, `shift = 3`:

```text
0 --> 3 --> 6 --> 2 --> 5 --> 1 --> 4 --> 0
```

Initial array: `[a,b,c,d,e,f,g]`. Initial `moved = 0`.

In each row, `current` and `carried` are measured BEFORE the iteration;
the array is measured AFTER the write.

| Step | `current` before | `carried` before | `next` | `displaced` saved | Array after write |
|---|---|---|---|---|---|
| 1 | 0 | a | 3 | d | `[a,b,c,a,e,f,g]` |
| 2 | 3 | d | 6 | g | `[a,b,c,a,e,f,d]` |
| 3 | 6 | g | 2 | c | `[a,b,g,a,e,f,d]` |
| 4 | 2 | c | 5 | f | `[a,b,g,a,e,c,d]` |
| 5 | 5 | f | 1 | b | `[a,f,g,a,e,c,d]` |
| 6 | 1 | b | 4 | e | `[a,f,g,a,b,c,d]` |
| 7 | 4 | e | 0 | a | `[e,f,g,a,b,c,d]` |

After every row:

- `current` becomes that row's `next`.
- `carried` becomes that row's `displaced`.
- `moved` increases by one.

After step 7, `current == start == 0`, so the inner loop stops. The saved `a`
is an old duplicate from the starting slot; `a` is already correctly placed at
index 3. We must NOT start another iteration of this cycle.

The code increments `start`, then checks `moved < n`. Since `moved == 7`,
the outer loop also stops. The rotation is complete.

## 6. Why this works and when another cycle is needed

At the start of each active iteration, `carried` holds the original value from
index `current`. Adding `shift` gives its final destination. Saving that
destination's old value before writing prevents losing the next value we need.

Returning to `start` closes the cycle. Some inputs have more than one cycle:

```text
n = 6, shift = 3

start 0: 0 --> 3 --> 0    moved = 2
start 1: 1 --> 4 --> 1    moved = 4
start 2: 2 --> 5 --> 2    moved = 6, finished
```

In general, there are `gcd(n, shift)` cycles. Each contains exactly the indexes
with one particular remainder modulo that gcd, so starts `0` through
`gcd(n, shift) - 1` cover distinct cycles. This is why `start++` works here.
See [CYCLIC_PROOF.md](CYCLIC_PROOF.md) for the full justification.

Each of the `n` values is placed once: O(n) time. Only a fixed number of
variables is used: O(1) extra space. If `shift == 0`, the early return avoids
unnecessary work. The problem guarantees `n >= 1`.

## 7. A sentence to say while tracing

> I am holding the value originally from `current`. Its destination is `next`.
> I save the value at `next`, write the carried value there, and carry the saved
> value forward. I stop this cycle when I return to `start`.

Practice: hide rows 2 through 7 and reconstruct them. Before each write, ask:

1. Which value am I holding, and where did it originally come from?
2. Where does it belong?
3. Which value must I save before overwriting that slot?
