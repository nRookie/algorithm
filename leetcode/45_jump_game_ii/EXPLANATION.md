# 45. Jump Game II

Given a nonempty array `nums`, start at index 0 and return the minimum number
of jumps to index `n - 1`. From index `i`, any forward destination through
`minOf(i + nums[i], n - 1)` is legal. The last index is guaranteed reachable.
The input is not modified. A one-element array needs zero jumps.

## My original reasoning, polished

This section preserves the reasoning supplied in the original code comments,
with grammar polished and technical corrections identified below. It is not
a verbatim transcript or an invented account of unspoken reasoning.

### What exactly must the output satisfy?

I need the minimum number of jumps from index 0 to index `n - 1`.
`nums[i]` is the maximum jump length, so I may choose any shorter forward
jump too. The problem guarantees that a solution exists.

When I reach an intermediate index, I want to retain the minimum jumps needed
to reach it. Arriving there by a longer path provides no new future choices.

### Solve one small example manually

For `[2,3,1,1,4]`, the route `0 → 2 → 3 → 4` takes three jumps.
The route `0 → 1 → 4` takes two. I must compare routes rather than accept
the first successful route.

Correction to my original example: I wrote `0 → 3 → 4`, but the first jump
is illegal because `nums[0] = 2`.

### What is a straightforward solution, and what can improve it?

I can use DFS to enumerate forward paths and retain the smallest successful
jump count. However, finding the minimum does not require enumerating every
path: paths can meet at the same index, where the future choices are identical.

I can instead use BFS to explore zero jumps, then one jump, then two jumps,
and so on. Since every transition costs one jump, the first discovery of an
index gives its minimum jump count. A visited set avoids enqueuing it again.

Corrections to my original complexity claims: exhaustive forward-path DFS
has an O(2ⁿ) bound rather than the loose O(nⁿ) estimate. Ordinary BFS here is
O(n²), not O(n), because it still scans overlapping destination ranges.
Guaranteed reachability does not remove that repeated work.

### What information do I need to decide the next action?

- `current_position`: the index being expanded.
- `jumps`: the minimum jumps to that particular index, carried in its queue entry.
- `nums[current_position]`: the maximum allowed forward jump length.
- `next_position`: a legal destination to consider.
- Initially, `visited`: which indices have already been enqueued.

`jumps` is not one global best-so-far answer and should not be incremented
once per queue iteration. Each newly discovered destination receives
`jumps + 1` from the current entry.

### Before every iteration, what can I rely on?

Every queued entry records a minimum jump count for its index. Entries are
processed in nondecreasing jump count, and discovered indices are not enqueued
twice. These are the concrete BFS invariants behind my original informal
statement that previously established results remain correct.

### Initialization, preservation, progress, and completion

**Initialization:** Enqueue `(0, 0)` and mark index 0 discovered.

**Preservation:** Remove the next FIFO entry, enumerate valid forward
destinations, and enqueue undiscovered ones with `jumps + 1`. Equal edge
costs and FIFO order preserve the minimum-distance guarantee.

**Progress:** Every index is enqueued at most once, and each iteration removes
one entry. Queue size need not decrease every iteration; the finite number
of unique entries is what guarantees termination.

**Completion:** When index `n - 1` is dequeued, its stored jump count is minimal.
Reachability guarantees that this happens.

The next sections explain how we improved this original BFS: first identify
the repeated scans, then use a discovery boundary to skip them. The final
space improvement is presented separately from the implementation we developed.

## Solution evolution

### 1. Enumerate paths with DFS

Try every strictly forward jump, recursively explore each resulting path,
and keep the smallest jump count that reaches the last index.

For `[2,3,1,1,4]`, `0 → 2 → 3 → 4` takes three jumps, while
`0 → 1 → 4` takes two. `0 → 3` is illegal because `nums[0] = 2`.

DFS enumeration is correct if all paths are considered, but many paths reach
the same index and repeat the same future exploration. In the dense case,
paths correspond to subsets of increasing intermediate indices, giving
O(2ⁿ) time and O(n) recursion space. Ignore zero-length jumps: they cannot
improve the answer and unguarded recursion on them would never terminate.

What to say: “Enumerating all forward paths works, but repeats work whenever
different paths reach the same position.”

### 2. BFS with a visited set

Treat each index as a graph state and each legal jump as an edge. Every edge
costs exactly one jump, regardless of its physical length. BFS therefore
discovers positions in minimum-jump order. Store `(jumps, current_position)`
in a FIFO queue and mark positions visited when enqueuing them.

An index alone identifies the state: arriving by a different path does not
change the jumps available from that index. Once first discovered, a position
does not need another queue entry.

For `[2,3,1,1,4]`, the discovery layers are `{0}`, `{1,2}`, `{3,4}`.
The first discovery of index 4 uses two jumps.

However, a visited set prevents repeated enqueueing, not repeated neighbor
checks. For `[4,3,2,1,0]`, processing indices 0, 1, 2, and 3 examines
4 + 3 + 2 + 1 destinations before index 4 is dequeued. BFS costs O(V + E),
and this implicit graph can have O(n²) edges. Time is O(n²), space O(n).
Guaranteed reachability does not make those checks linear.

What to say: “BFS gives the minimum jumps, but overlapping destination ranges
still cause quadratic scanning even though each position is enqueued once.”

Original implementation, with formatting polished and `minOf` used to avoid
an import; the visited-set algorithm is unchanged:

```kotlin
class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        val queue = ArrayDeque<Pair<Int, Int>>()
        val visited = HashSet<Int>()
        queue.addFirst(Pair(0, 0))
        visited.add(0)

        while (!queue.isEmpty()) {
            val (jumps, current_position) = queue.removeLast()
            if (current_position == n - 1) return jumps

            for (next_position in current_position + 1..
                minOf(current_position + nums[current_position], n - 1)) {
                if (next_position !in visited) {
                    visited.add(next_position)
                    queue.addFirst(Pair(jumps + 1, next_position))
                }
            }
        }
        return n
    }
}
```

### 3. Skip previously discovered destinations with a boundary

Every jump permits all shorter forward jumps. Consequently, after each
completed expansion, discovered indices form a continuous prefix `0..boundary`.
Initially that prefix is just `{0}`. Expanding a discovered position examines
an interval starting no later than `boundary + 1`, so any extension has no gap.

This lets one integer replace the visited set:

- `boundary`: farthest index already discovered (enqueued at some point).
  All indices from 0 through it are discovered, not just selected endpoints.
  Some have been processed; others are still waiting in the queue.
- `end`: farthest destination reachable from the current position alone.
- `start`: first legal destination that has not already been discovered.

```kotlin
val start = maxOf(current_position + 1, boundary + 1)
val end = minOf(current_position + nums[current_position], n - 1)
```

Enqueue every index in `start..end`, then extend the boundary:

```kotlin
boundary = maxOf(boundary, end)
```

The start is only a lower bound, not a promise that a destination exists.
For example, `6..4` is an empty Kotlin range: nothing is enqueued.

The `maxOf` update is essential because `end` describes only this position's
reach. A shorter jump must not erase earlier discoveries. If the boundary is
5 and `end` is 4, keep 5. Setting it to 4 could cause index 5 to be enqueued
again during a later expansion.

What to say: “Discovered indices always form a prefix. I store its endpoint
and scan only new destinations beyond it, so every index is examined once.”

| Approach | Time | Auxiliary space | Improvement |
| --- | --- | --- | --- |
| Enumerate forward paths | O(2ⁿ) | O(n) | Correct baseline |
| BFS with visited | O(n²) | O(n) | Merge paths reaching the same state |
| BFS with discovery boundary | O(n) | O(n) | Skip overlapping destination scans |
| BFS layers without a queue (extension below) | O(n) | O(1) | Store layer endpoints instead of entries |

### 4. Further improvement: represent BFS layers without a queue

This is an extension beyond the final implementation developed in the discussion.
The discovery-boundary BFS already achieves O(n) time, but stores O(n) entries.
To reach O(1) auxiliary space, retain the BFS layer boundaries instead of
individual queue entries and their distances.

Let `currentEnd` be the farthest index reachable with the current `jumps`
budget, and `farthest` be the farthest destination seen while scanning that
layer. When the scan reaches `currentEnd`, all positions in that layer have
contributed their reach. One more jump advances the layer to `farthest`.

This does not choose the farthest landing position at each step. It aggregates
the reach of every position in a layer, preserving BFS's minimum-jump order.
`currentEnd` is a layer endpoint, whereas the earlier `boundary` tracked all
discovered indices and could advance while a layer was still being processed.

```kotlin
fun jump(nums: IntArray): Int {
    var jumps = 0
    var currentEnd = 0
    var farthest = 0

    for (current_position in 0 until nums.lastIndex) {
        farthest = maxOf(
            farthest,
            minOf(current_position + nums[current_position], nums.lastIndex)
        )
        if (current_position == currentEnd) {
            jumps++
            currentEnd = farthest
            if (currentEnd == nums.lastIndex) return jumps
        }
    }
    return jumps
}
```

For the same `[2,2,3,1,1,0]` example:

| Index scanned | `farthest` afterward | Layer action |
| --- | --- | --- |
| 0 | 2 | Finish layer 0: `jumps = 1`, `currentEnd = 2` |
| 1 | 3 | Continue scanning the one-jump layer |
| 2 | 5 | Finish layer 1: `jumps = 2`, `currentEnd = 5`; return |

We do not scan the last index to start another jump: reaching it is the goal.
For a one-element array, the loop is empty and the result is 0. Guaranteed
reachability ensures that an unfinished layer can advance.

Each array position is scanned at most once, with only three scalar counters:
O(n) time and O(1) auxiliary space. The linear worst-case time is optimal:
on an all-ones array, changing any index before the penultimate index to 2
reduces the answer, so a correct algorithm must inspect linearly many values
in the worst case. Constant auxiliary space is also asymptotically optimal.

What to say: “The queue groups positions by jump count. Since each layer is
an interval, I can scan it directly, collect the next layer's farthest reach,
and increment the jump count once when the current layer ends.”

## Final implementation from our discussion

Saved separately in [45.kt](45.kt). This is the O(n)-space BFS we derived;
the further O(1)-space version above does not replace that saved implementation.

This preserves the final queue-based approach, using `maxOf` and `minOf`
consistently so no `kotlin.math` imports are needed.

```kotlin
class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        // Pair<jumps, current_index>
        val queue = ArrayDeque<Pair<Int, Int>>()
        queue.addFirst(Pair(0, 0))
        var boundary = 0

        while (!queue.isEmpty()) {
            val (jumps, current_position) = queue.removeLast()
            if (current_position == n - 1) return jumps

            val start = maxOf(current_position + 1, boundary + 1)
            val end = minOf(current_position + nums[current_position], n - 1)

            for (next_position in start..end) {
                queue.addFirst(Pair(jumps + 1, next_position))
            }
            boundary = maxOf(boundary, end)
        }
        return n
    }
}
```

`addFirst` and `removeLast` use opposite ends, giving FIFO order. The final
`return n` is unreachable under the problem's reachability guarantee.

## Full trace: one consistent example

```text
index:  0  1  2  3  4  5
nums:  [2, 2, 3, 1, 1, 0]
```

Queue entries below are `(jumps, index)`, shown in processing order:
the next entry to dequeue is on the left. This is logical FIFO order,
not the deque's physical first-to-last storage order.

| Action | Boundary before | New range | Queue afterward | Boundary after |
| --- | --- | --- | --- | --- |
| Initialize | — | Enqueue index 0 | `[(0,0)]` | 0 |
| Pop `(0,0)` | 0 | `1..2` | `[(1,1), (1,2)]` | 2 |
| Pop `(1,1)` | 2 | `3..3` | `[(1,2), (2,3)]` | 3 |
| Pop `(1,2)` | 3 | `4..5` | `[(2,3), (2,4), (2,5)]` | 5 |
| Pop `(2,3)` | 5 | `6..4` (empty) | `[(2,4), (2,5)]` | 5 |
| Pop `(2,4)` | 5 | `6..5` (empty) | `[(2,5)]` | 5 |
| Pop `(2,5)` | 5 | Return before expansion | `[]` | 5 |

The result is 2, witnessed by `0 → 2 → 5`.

At index 2, `nums[2] = 3`, so possible destinations are 3, 4, and 5.
Index 3 is already queued; only 4 and 5 are new. This example never permits
a jump from index 2 to index 7.

## Why it works

At the start of each while-loop iteration:

1. Exactly the indices `0..boundary` have been discovered, each once.
2. Each queued pair contains the minimum jumps needed to reach its index.
3. Queue processing order is nondecreasing in jump count.

**Initialization:** Only index 0 is enqueued, with its minimum distance 0.
The boundary is 0.

**Preservation:** The new range contains exactly the legal undiscovered
destinations. Skipping the discovered prefix loses no better path because
BFS first discovery already gives minimum distance with equal edge costs.
New entries get `jumps + 1` and join the back of the processing order.
Updating the boundary with the maximum preserves all old discoveries and
includes any new extension.

**Termination:** Each index is enqueued and dequeued at most once, so there
are at most n loop iterations. The guaranteed-reachable target is eventually
dequeued; its stored distance is the required minimum.

## Complexity and edge cases

The outer loop processes at most n entries. Across all executions of the
inner loop, each index beyond 0 appears at most once because the boundary
never retreats. Thus total time is O(n), despite the nested loops. Queue
operations are amortized O(1); the queue and pair allocations use O(n)
auxiliary space. This is still a queue-based BFS, not a constant-space solution.

- `[0]`: return 0 immediately.
- `[1,1,1,0]`: discover one new index per expansion; return 3.
- `[2,0,1,0]`: the zero at index 1 produces an empty range; index 2 can
  still reach the target, giving 2 jumps.
- `[4,3,2,1,0]`: discover all destinations from index 0; later expansions
  scan no new indices, and the answer is 1.

## Interview explanation and recall

“I model each index as a state and each jump as one edge. BFS finds the fewest
jumps because every edge has the same cost. A visited set alone still checks
overlapping ranges repeatedly. Since each jump allows every shorter distance,
discovered positions form a prefix. I keep its farthest index and enqueue
only destinations beyond it. The boundary never decreases, so every index
is scanned and enqueued once: O(n) time and O(n) queue space.”

To reconstruct the solution, explain:

1. Why is an index enough to identify a state?
2. Why does a visited set alone fail to guarantee O(n) time?
3. What input rule guarantees that discoveries have no holes?
4. How do `current_position`, `end`, and `boundary` differ?
5. Why is an empty new-destination range valid?
6. What goes wrong if the boundary is assigned `end` unconditionally?
