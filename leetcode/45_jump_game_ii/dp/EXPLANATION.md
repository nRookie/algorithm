# Jump Game II: from quadratic DP to linear boundary DP

Return the minimum jumps from index 0 to index `n - 1`. A jump from index i
may land at any later index through `minOf(i + nums[i], n - 1)`. The array
is nonempty and the last index is guaranteed reachable. We do not modify it.

Final implementation: [45.kt](45.kt). Related approaches:
[one-queue BFS](../EXPLANATION.md) and
[two-queue BFS](../two_queue_bfs/EXPLANATION.md).

## Our reasoning, polished

We first derived a DP state: `dp[j]` stores the minimum jumps to reach index j.
The learner proposed initializing unknown answers to `Int.MAX_VALUE`, starting
with `dp[0] = 0`, and considering each earlier source i for destination j.
The tutor corrected the reachability comparison from `<` to `<=`: a jump
may use exactly its maximum length. The learner then assembled the quadratic DP.

To improve it, we discussed grouping positions by minimum jump count. The
learner proposed reusing the discovery boundary from BFS to skip destinations
already updated, and assembled the final array-based implementation. This
follows the discovery-boundary route rather than removing the DP array with
explicit layer endpoints.

The important clarifications were:

- `current` is a source index; `next` is a destination index.
- `boundary` is the last discovered index, not the first undiscovered index.
  Therefore update it with `maxOf(boundary, end)`, not `end + 1`.
- “At or behind the boundary” means an index is less than or equal to it.
  Such an index may still be processed as an outer-loop source, but it will
  not be examined again as an inner-loop destination.
- There are at most n − 1 destination updates across **all inner-loop
  executions combined**, not n − 1 per outer iteration.

## Solution evolution

### 1. Define a DP state and recurrence

During computation, `dp[j]` is the best known jump count; once finalized, it
is the true minimum. Initialize:

```kotlin
val dp = IntArray(n) { Int.MAX_VALUE }
dp[0] = 0
```

Zero jumps reach the starting index. Infinity means “no route established
yet,” not a proof of unreachability. Never add one to `Int.MAX_VALUE`, which
would overflow; guard that addition.

Every path to j ends with a jump from some earlier i. Consequently:

```text
dp[j] = min(dp[i] + 1)
        over reachable i with 0 <= i < j and j <= i + nums[i]
```

All useful jumps are forward, so smaller-index dependencies can be computed
before larger-index states. Zero-length jumps cannot improve the minimum.

What to say: “For each destination, I consider its possible final jump. The
best route is the cheapest route to a legal predecessor plus one jump.”

### 2. Original O(n²) implementation

This is the learner's first DP implementation, with formatting polished:

```kotlin
class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n) { Int.MAX_VALUE }
        dp[0] = 0
        for (j in 1 until n) {
            for (i in 0 until j) {
                if (j <= i + nums[i] && dp[i] != Int.MAX_VALUE) {
                    dp[j] = minOf(dp[i] + 1, dp[j])
                }
            }
        }
        return dp[n - 1]
    }
}
```

**Outer-loop invariant:** Before destination j is processed, all entries
`dp[0]` through `dp[j - 1]` are final minimum distances.

**Inner-loop invariant:** Before examining source i, `dp[j]` is the minimum
candidate from the legal sources already examined, indices `0 until i`.
It is infinity if none has contributed. Processing i adds exactly its candidate
when legal; after the inner loop, every possible predecessor has been checked.

Initialization holds because `dp[0] = 0`. The recurrence preserves the inner
invariant and finalizes j, establishing the next outer iteration's invariant.
Both finite loops advance their indices. On completion, `dp[n - 1]` is final.

There are `1 + 2 + ... + (n - 1)` predecessor checks: O(n²) time, O(n) space.

### 3. Change from collecting predecessors to updating destinations

The same transition can be applied in the other direction: scan each source
`current`, then send `dp[current] + 1` to its reachable destinations.

```text
for each current in increasing index order:
    for each legal next destination:
        dp[next] = min(dp[next], dp[current] + 1)
```

This alone is still O(n²). Different sources have overlapping destination
ranges, so they repeatedly update the same entries. We need a reason that
the first update is already optimal before skipping subsequent updates.

### 4. Prove that first discovery is enough here

Two structural properties make this possible:

**Discovered destinations form a prefix.** All shorter jumps are allowed.
Starting from `{0}`, an expansion from a discovered source fills any new
positions through its reach without leaving holes. Store that prefix's last
index as `boundary`.

**Minimum jump counts are nondecreasing with index.** For indices a < b,
take a minimum-jump path to b. If it passes through a, stop there. Otherwise,
at the first jump that passes a, shorten that jump to land on a. This reaches
a using no more jumps than reaching b. Therefore `distance[a] <= distance[b]`.

When scanning sources in increasing index order, their finalized distances
are consequently nondecreasing. The first source reaching a new destination
has no worse distance than any later source. Its candidate is already optimal.

This is a problem-specific guarantee, not a rule that arbitrary DP states can
be finalized on first update. Prefix reachability alone would not prove the
minimum-distance claim for arbitrary edge costs or different movement rules.

What to say: “Here, earlier indices require no more jumps than later indices.
Scanning sources left to right therefore discovers each destination with its
minimum distance the first time.”

### 5. Skip the finalized prefix

```kotlin
val start = maxOf(current + 1, boundary + 1)
val end = minOf(current + nums[current], n - 1)
```

The range must satisfy both requirements: the destination is ahead of the
source, and it is beyond all previous discoveries. `end` is the current
source's farthest legal destination. If `start > end`, the range is empty.

After updating new destinations:

```kotlin
boundary = maxOf(boundary, end)
```

For example, if the old boundary is 5 but the source reaches only 4, retain 5.
Earlier discoveries do not disappear. Using `end + 1` would instead mark a
position that we have not actually discovered and could skip its update.

| Approach | Time | Auxiliary space | Removed work |
| --- | --- | --- | --- |
| Destination-based DP | O(n²) | O(n) | Baseline |
| Source-based DP without boundary | O(n²) | O(n) | Same transitions, different organization |
| Source-based DP with boundary | O(n) | O(n) | Repeated destination updates |

## Final implementation

This preserves the learner's algorithm. Formatting and braces are polished;
`min` is changed to `minOf` so no `kotlin.math.min` import is needed.

```kotlin
class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n) { Int.MAX_VALUE }
        dp[0] = 0
        var boundary = 0

        for (current in 0 until n) {
            val start = maxOf(current + 1, boundary + 1)
            val end = minOf(current + nums[current], n - 1)
            for (next in start..end) {
                if (dp[current] != Int.MAX_VALUE) {
                    dp[next] = minOf(dp[current] + 1, dp[next])
                }
            }
            boundary = maxOf(boundary, end)
        }
        return dp[n - 1]
    }
}
```

Every `next` in the inner loop is new, so its old value is infinity. A direct
assignment `dp[next] = dp[current] + 1` would suffice under the invariant;
we keep the submitted minimum update to preserve the implementation.

## Final loop invariants

At the beginning of each outer iteration for `current`:

1. All sources with index less than `current` have been expanded.
2. Exactly the indices `0..boundary` have been discovered, and their DP
   entries are final minimum distances. Entries beyond it remain infinity.
3. `current <= boundary`, so the current source has a final, finite distance.
   This uses the problem's reachability guarantee.

**Initialization:** At `current = 0`, only index 0 is discovered and its
distance is correctly zero. No sources have been expanded yet.

**Inner-loop invariant:** Holding the old boundary fixed, before each `next`,
all earlier indices in `start until next` have received their final distance
`dp[current] + 1`; the remaining new destinations have not yet been updated.
The boundary variable itself is updated only after the range is complete.

**Preservation:** The range contains precisely the undiscovered destinations
reachable from this source. The nondecreasing-distance argument makes every
first update optimal. Updating the boundary incorporates the completed new
range and retains earlier discoveries. The next source must be discovered:
otherwise no processed source crosses that gap, contradicting reachability
of the last index.

**Termination and completion:** The outer loop advances through n indices.
Every inner range is finite. On completion, the guaranteed-reachable last
index has a finalized DP value, which is returned.

The unconditional boundary update relies on the stated contract. If supporting
unreachable inputs, skip an unreachable source before extending the boundary
and define an unreachable return value. The inner guard alone does not make
the discovered-prefix invariant valid outside the contract.

## Full trace

```text
index:  0  1  2  3  4  5
nums:  [2, 2, 3, 1, 1, 0]
```

`∞` below means `Int.MAX_VALUE`.

| Step | Boundary before | New range | DP after expansion | Boundary after |
| --- | --- | --- | --- | --- |
| Initialize | — | — | `[0,∞,∞,∞,∞,∞]` | 0 |
| `current = 0` | 0 | `1..2` | `[0,1,1,∞,∞,∞]` | 2 |
| `current = 1` | 2 | `3..3` | `[0,1,1,2,∞,∞]` | 3 |
| `current = 2` | 3 | `4..5` | `[0,1,1,2,2,2]` | 5 |
| `current = 3` | 5 | `6..4`, empty | `[0,1,1,2,2,2]` | 5 |
| `current = 4` | 5 | `6..5`, empty | `[0,1,1,2,2,2]` | 5 |
| `current = 5` | 5 | `6..5`, empty | `[0,1,1,2,2,2]` | 5 |

Return `dp[5] = 2`. Index 2 was updated as a destination during source 0's
expansion. It later acts as a source, but never becomes a new destination again.

## Why nested loops are O(n) here

Count the outer and inner work separately:

- n outer iterations, each doing O(1) work outside its inner loop.
- At most n − 1 inner iterations **in total**: every destination from 1 to
  n − 1 appears in at most one new range. The boundary never retreats.
- Initializing the DP array takes O(n).

Thus total time is O(n + (n − 1) + n) = O(n), and auxiliary space is O(n).
We do not multiply n by n because an inner loop cannot repeatedly scan the
same n destinations. Its ranges are disjoint across expansions.

This final implementation retains the DP array. The separate
[BFS-layer compression](../EXPLANATION.md) can reduce space to O(1); that is
a further change, not the implementation derived here.

Edge cases: `[0]` returns 0; `[1,1,1,0]` returns 3; `[2,0,1,0]` returns 2.
An empty destination range is normal and does not by itself mean failure.

## Interview explanation and recall

“I first define the minimum jumps to each index and consider every legal
predecessor, giving quadratic DP. I then scan sources left to right. Because
shorter jumps are legal, discoveries form a prefix and minimum distances are
nondecreasing with index. The first source reaching a new destination already
gives its minimum. A boundary lets me update only new destinations. Each index
is updated once and expanded once, so the result is O(n) time and O(n) space.”

Practice explaining why first discovery is optimal, why the boundary uses
`end` rather than `end + 1`, and why an index can be processed later as a source
without violating the one-update-per-destination count.
