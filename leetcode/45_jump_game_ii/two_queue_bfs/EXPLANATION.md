# Jump Game II: two-queue BFS and the DP alternative

Return the minimum jumps from index 0 to the last index. Each jump may use any
length up to `nums[current_position]`; the target is guaranteed reachable.

Implementation: [45.kt](45.kt). Earlier derivation:
[DFS to boundary BFS](../EXPLANATION.md).

## Our reasoning, polished

We wanted to make BFS layers explicit using two queues. This is reasonably
called **two-queue BFS**, or level-order BFS implemented with two queues.
The queues represent the current and next distance layers, not weight versus
distance. Each edge still costs one jump.

The learner's observation was that we no longer need `(jumps, index)` pairs:
all positions in a layer share the same minimum jump count. The tutor supplied
the boundary-based destination loop; the learner assembled the two-queue code.

- `current` contains the remaining positions at minimum distance `jumps`.
- `next` collects newly discovered positions at distance `jumps + 1`.
- `boundary` records all discoveries so far: every index from 0 through it has
  been enqueued at some point. It persists across layers.

Initialize `current` with 0, `jumps = 0`, and `boundary = 0`. Process the whole
current layer before transferring the next layer and incrementing `jumps`.

## Solution evolution

The original visited-set BFS merged paths reaching the same index, but scanned
overlapping destination ranges in O(n²) time. Our boundary optimization reduced
that to O(n) by examining each new destination once.

The one-queue version stored a distance in every pair. The two-queue version
groups equal-distance positions explicitly, allowing one shared distance counter.
It changes how we represent layers; it does not improve the asymptotic bounds.

| Version | How distance is stored | Time | Auxiliary space |
| --- | --- | --- | --- |
| Visited-set BFS | Per-entry distance | O(n²) | O(n) |
| Boundary BFS, one queue | Per-entry distance | O(n) | O(n) |
| Boundary BFS, two queues | Shared layer counter | O(n) | O(n) |

What to say: “Each jump has equal cost, so I process one BFS layer at a time.
The current queue contains positions at the same distance; the next queue
collects their undiscovered destinations. A discovery boundary skips all
positions already enqueued.”

## The destination loop

```kotlin
val start = maxOf(current_position + 1, boundary + 1)
val end = minOf(current_position + nums[current_position], nums.lastIndex)
for (next_position in start..end) {
    next.addLast(next_position)
}
boundary = maxOf(boundary, end)
```

`end` is the current position's reach, whereas `boundary` summarizes all
discoveries. The maximum keeps that summary from retreating. When `start > end`,
the Kotlin range is empty and nothing is added. This compression works because
all shorter jumps are legal, so the discovered set has no holes.

## Queue transfer: preserving the submitted behavior

The saved implementation preserves the learner's transfer loop:

```kotlin
while (next.isNotEmpty()) {
    val next_position = next.removeFirst()
    current.addFirst(next_position)
}
jumps++
```

This reverses the order within a layer: `[1,2]` becomes `[2,1]`. It remains
correct because every position in that layer has the same minimum distance.
It also preserves the boundary invariant: expanding any discovered index adds
every undiscovered destination through its reach, without leaving holes.

Using `current.addLast(next_position)` would preserve the order and simplify
some traces, but is not required for correctness. Both queues can remain `val`:
their contents change, but the queue references are never reassigned.

## Trace of the exact submitted implementation

```text
index:  0  1  2  3  4  5
nums:  [2, 2, 3, 1, 1, 0]
```

Queues are shown from first to last; removal is from the first end.

| Action | `jumps` | `current` afterward | `next` afterward | `boundary` |
| --- | --- | --- | --- | --- |
| Initialize | 0 | `[0]` | `[]` | 0 |
| Pop 0; discover 1, 2 | 0 | `[]` | `[1,2]` | 2 |
| Transfer layer; increment | 1 | `[2,1]` | `[]` | 2 |
| Pop 2; discover 3, 4, 5 | 1 | `[1]` | `[3,4,5]` | 5 |
| Pop 1; range `6..3` is empty | 1 | `[]` | `[3,4,5]` | 5 |
| Transfer layer; increment | 2 | `[5,4,3]` | `[]` | 5 |
| Pop 5; return 2 | 2 | `[4,3]` | `[]` | 5 |

Because the layer order is reversed, index 2 discovers index 3 before index 1
is processed. That is fine: either parent reaches index 3 in two jumps.

## Correctness and complexity

At the beginning of each outer iteration, `current` is exactly the unprocessed
layer at distance `jumps`, and `next` is empty. During the inner loop, all newly
discovered destinations have distance `jumps + 1`: every shorter-distance
layer was already fully expanded. Duplicate discovery is excluded by the
boundary. After transfer, incrementing `jumps` establishes the next layer's
meaning. Reordering entries within a layer does not change these facts.

There are at most n discoveries. Every index is processed once, and each index
other than 0 is transferred once. The destination loops examine each new
index only once globally. Total time is O(n), including the transfer loops;
the two queues together use O(n) auxiliary space.

For `[0]`, the initial dequeue returns 0. A zero-length jump creates an empty
destination range. The fallback `return n` is unreachable under the contract.

## Can we solve it with DP?

Yes. Instead of discovering minimum distances by BFS layers, compute them in
increasing index order. Every useful jump is strictly forward, so all incoming
dependencies of index j come from smaller indices.

Define `dp[j]` as the minimum jumps needed to reach index j.

```text
dp[0] = 0
dp[j] = infinity initially, for j > 0

dp[j] = min(dp[i] + 1)
        over reachable i satisfying 0 <= i < j and i + nums[i] >= j
```

The minimum of no candidates stays infinity. Under this problem's guarantee,
every index is reachable because reachability forms a prefix containing the
last index; infinity still expresses the initial, not-yet-computed state.

For the same `[2,2,3,1,1,0]` example:

| Destination j | Earlier indices that can jump directly to j | `dp[j]` |
| --- | --- | --- |
| 0 | Start | 0 |
| 1 | 0 | 1 |
| 2 | 0, 1 | 1 |
| 3 | 1, 2 | 2 |
| 4 | 2, 3 | 2 |
| 5 | 2, 4 | 2 |

Why it works: every path to j has a final jump from some earlier index i.
The recurrence considers all legal final jumps and chooses the cheapest prefix
plus that one jump. Increasing index order ensures `dp[i]` is already correct.

This direct DP takes O(n²) time and O(n) space: for each destination, check all
earlier sources. Memoized forward DFS is another DP formulation with the same
bounds; it caches repeated subproblems instead of enumerating every path.

The DP is a valid alternative, but our boundary BFS is faster. This section
provides the state and recurrence for practice rather than a completed DP
implementation. The earlier explanation separately develops the O(n)-time,
O(1)-space BFS-layer compression.

## Recall questions

1. Why can the queues store indices without storing distances?
2. Why must `jumps` increase after a whole layer rather than after one position?
3. Why does reversing one layer preserve minimum distances?
4. Why must `boundary` persist when we switch layers?
5. For DP, why are smaller-index states ready before a larger-index state?
