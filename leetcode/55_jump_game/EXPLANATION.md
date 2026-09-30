# 55. Jump Game

Starting at index 0, determine whether the last index is reachable. Each
`nums[i]` is a maximum forward jump length: shorter jumps are allowed.
The input is nonempty and does not need to change. For a one-element array,
the answer is true because the starting index is already the last index.

## Final implementation

[55.kt](55.kt) preserves your final algorithm, adding the `kotlin.math.max`
import, braces, and consistent formatting. It skips unreachable positions
and checks the final boundary after scanning the array.

Time: O(n). Auxiliary space: O(1). There is no recursion or input mutation.
Under the supplied constraints, `current + nums[current]` fits in Kotlin Int.

## Solution evolution

### 1. Explore forward paths

Try every legal next jump recursively. For `[2,3,1,1,4]`, one successful path
is `0 → 1 → 4`. Different paths can reach the same index and repeat the same
future exploration. An uncached exhaustive search has O(2^n) worst-case time
and O(n) recursion space; it is not factorial because indices only increase.

**What to say:** “The straightforward search tries all forward paths, but paths
reaching the same index have identical future options.”

### 2. Track reachable indices

Initialize `reachable[0] = true`. For each reachable index, mark every legal
destination as reachable. This avoids repeating entire histories, but marking
overlapping ranges still takes O(n²) worst-case time and O(n) space.

These costs describe this explicit range-marking DP, not your earlier DFS's
special descending traversal with an early return on a visited destination.

**What to say:** “I only need to remember whether an index is reachable, not
which path reached it. However, many transitions mark the same positions.”

### 3. Compress the reachable prefix

The key guarantee is that every jump length up to the maximum is allowed.
From a reachable index, all destinations in a continuous interval are reachable.
These intervals extend the existing reachable prefix without creating holes.

For `[2,3,1,1,4]`, processing index 0 gives `T T T F F`; processing index 1
gives `T T T T T`. Store the boundary instead of every Boolean.

| Variable | Meaning |
| --- | --- |
| `n` | Number of indices; the target index is `n - 1` |
| `current` | Index being considered in the left-to-right scan |
| `farthest` | Farthest boundary offered by reachable positions processed so far, initially 0 |

Only when `current <= farthest` may we use its jump length:

```text
farthest = max(farthest, current + nums[current])
```

The boundary may exceed the last index. Every in-bounds index up to it is
reachable; exceeding the last index also proves the last index is reachable
because shorter jumps are allowed.

This represents all available options, rather than committing to the longest
jump. In `[2,2,0,1]`, committing to `0 → 2` fails, while `0 → 1 → 3` succeeds.
The boundary method retains index 1 as a reachable option.

**What to say:** “Reachable positions form a prefix, so I track its farthest
boundary. Only reachable positions may extend it. This uses O(n) time and
O(1) space.”

## Trace of your final code

Input: `[2,3,1,1,4]`. Initially `farthest = 0`; target index = 4.

| current | nums[current] | farthest before | Reachable? | farthest after |
| --- | --- | --- | --- | --- |
| 0 | 2 | 0 | Yes | 2 |
| 1 | 3 | 2 | Yes | 4 |
| 2 | 1 | 4 | Yes | 4 |
| 3 | 1 | 4 | Yes | 4 |
| 4 | 4 | 4 | Yes | 8 |

The loop ends; `4 <= 8` returns true. Your implementation continues scanning
after success becomes known, which is correct and still O(n).

For `[3,2,1,0,4]`, the boundary after each iteration is `3,3,3,3,3`.
Index 4 is skipped because it is unreachable; the final answer is false.

## Correctness and termination

Initially index 0 is reachable without moving, so the boundary is valid.
Before each iteration, all in-bounds indices through `farthest` are reachable
using jumps from already processed positions.

If `current <= farthest`, it is reachable. Its jumps add a continuous interval
that overlaps the existing prefix. Taking the larger endpoint preserves the
invariant and includes every destination offered by this position.

If `current > farthest`, no processed position can reach it. Forward movement
means no unprocessed position can be reached first and then help us cross this
gap. Your code skips this index and every later index because the boundary
can no longer grow. Returning false immediately would be an optional shortcut.

The loop processes exactly n indices and terminates. The final boundary covers
the target exactly when it is reachable, so the final comparison is correct.

## Reconstruct the idea yourself

Use the prompts in [the general workflow](../../study-notes/algorithm-solving-workflow.md):

1. **History:** Why do paths reaching the same index have identical futures?
2. **Structure:** Why do reachable indices form a prefix without holes?
3. **Sufficiency:** Why does one boundary preserve everything needed next?
4. **Dependency:** Which word in the statement makes that compression valid?

With exact jumps, reachable positions can have holes. In `[2,3,0,0,0]`, exact
forward jumps reach index 2 but never index 1. Treating every index below the
boundary as reachable would incorrectly allow index 1 to reach index 4.

Rehearse why `[0]` returns true, `[0,2,0]` returns false, and `[2,0,0]`
returns true. Explain why the reachability check must precede the update.

## Next practice: exact jumps

[LeetCode 1306: Jump Game III](https://leetcode.com/problems/jump-game-iii/)
uses exact jump lengths. It differs from the hypothetical forward-only variant:
you start at a supplied index, may move to `i + arr[i]` or `i - arr[i]` within
the array, and seek any index whose value is zero. Try deriving its state and
transitions yourself before looking at a solution.
