# Algorithm concepts cheatsheet

Reusable facts collected from solved problems. For how to derive a solution,
use [the solving workflow](algorithm-solving-workflow.md). Full implementations
and traces belong in each problem's `EXPLANATION.md`.

To add future lessons, ask: **“What can we learn from this? Update the cheatsheet.”**
Keep the condition behind each rule, not just the rule itself.

## Graph traversal: DFS and BFS

### BFS finds the fewest edges; DFS does not guarantee that

- **Rule:** In an unweighted graph, BFS explores states in increasing distance
  from the start, measured in number of edges. The first target reached has the
  minimum number of edges among all reachable targets. Equal positive edge
  costs also make this a minimum-cost path.
- **Why:** A FIFO queue processes all states at distance d before states at
  distance d + 1. DFS follows a branch deeply before trying alternatives.
- **Example:** In Jump Game III, each legal jump is one edge. BFS can find the
  minimum number of jumps to any zero. A jump spanning ten array positions
  still costs one jump. A Boolean-only implementation must add distance
  tracking to return the count; parent tracking is needed to reconstruct a path.
- **Limit:** Ordinary BFS does not guarantee minimum total cost when edge
  costs differ. DFS may find a shortest path by chance, but its first success
  is not guaranteed to be shortest.

### Reachability allows either traversal order

For a finite graph, both DFS and BFS correctly answer whether a target is
reachable when they explore all relevant moves and handle repeated states.
Changing the order can change which path is found first, but not whether a
path exists.

| Traversal | Kotlin deque operations | Order |
| --- | --- | --- |
| DFS with a stack | `addLast`, `removeLast` | Last in, first out |
| BFS with a queue | `addLast`, `removeFirst` | First in, first out |

`addFirst` with `removeLast` also implements FIFO; use opposite ends for a queue.

Two-queue BFS makes distance layers explicit: finish `current`, collecting new
states in `next`, then transfer and increment the distance once. Entries need
no individual distance because a layer shares one value. Reordering within a
layer is safe for equal-cost shortest distances; mixing layers is not. This
alone does not reduce neighbor-scanning work. See
[Jump Game II: two-queue BFS and DP](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).

With a stack, push right then left to explore left first. With a queue, adding
right then left processes right first among those newly added neighbors.

### Visited prevents cycles and repeated expansion

If reaching a state again offers the same future choices, explore it once.
For example, `[1,1]` in Jump Game III permits `0 → 1 → 0 → ...`; visited stops
this cycle. Recursive DFS must mark before exploring neighbors.

For basic reachability, keep marks permanently instead of unmarking on return.
Returning false for a repeated visit means “skip this exploration,” not “this
state has been proved unable to reach the target.” A visited array is not a
cache of per-state answers.

**Condition:** The visited key must represent the full state. If future options
depend on remaining resources or another part of the history, an index alone
may be insufficient. Path-enumeration tasks may also need different rules.

### Marking when adding versus when removing

Marking valid states before adding them to a stack or queue prevents duplicate
pending entries. In BFS, first discovery gives the shortest distance, so record
the distance and parent then, without overwriting them on later encounters.

Marking when removing is also correct for the reachability code in Jump Game
III, provided repeated entries are skipped before expansion. Duplicates can
be pending simultaneously. Its O(n) bound still holds because each index
expands once and adds at most two entries.

Source example: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Complexity: count transitions as well as states

“Each state is visited once” is only part of the time analysis. Also count the
work performed at that state, including neighbor generation.

- Graph traversal with adjacency lists takes O(V + E): V vertices and E edges.
- In Jump Game III, there are n indices and at most 2n edges, so time is O(n).
  For the saved iterative implementation, at most `1 + 2n` entries are pushed,
  including invalid and duplicate entries. Deque operations are amortized O(1).
- In range-marking Jump Game I DP, one index may examine O(n) destinations;
  processing each index once can therefore still take O(n²) time.
- In Jump Game II BFS, a visited set prevents duplicate enqueueing but still
  checks overlapping destination ranges: O(n²) time. Scanning only destinations
  beyond a monotone discovery boundary makes the total inner-loop work O(n).
  Nested loops can be linear when each index participates only once globally.

Include the visited array and pending stack/queue in space complexity. Include
the runtime call stack for recursion: a depth-n path can require O(n) space.

## Iteration, recursion, and DP are different concepts

**Iterative** describes execution with loops; **recursive** describes functions
calling themselves. DFS can use either recursive calls or an explicit stack.
Both versions can have O(n) space even though the iterative version avoids
deep JVM call-stack usage. An explicit stack still needs memory.

**Dynamic programming** stores and reuses subproblem results. It can be
recursive or iterative. Replacing recursive DFS with a loop does not by itself
turn the solution into DP.

BFS and DP can both describe states and transitions, but organize work for
different reasons. BFS processes states by increasing number of moves; DP
combines and reuses subproblem answers in a valid dependency order. They are
not mutually exclusive labels: some problems admit both views. For example,
Jump Game II can use BFS distance layers or DP minimum-jump values; see its
[BFS and DP comparison](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).
“Minimum” alone does not imply DP or BFS: ordinary BFS needs equal move costs
for its minimum-cost guarantee, and a DP recurrence needs justified
dependencies. Memoization alone does not resolve cyclic dependencies.

For recursive existence searches, `dfs(left) || dfs(right)` short-circuits:
a true left result skips the right call and success propagates through callers.
This improves early stopping but does not replace visited or prevent cycles.

## State compression requires a structural guarantee

If all reachable positions form a prefix, store its endpoint instead of a
Boolean for every position. Before extending the boundary, check that the
position providing the extension is itself reachable.

In Jump Game I, “maximum jump length” allows every shorter jump, making
reachability a continuous prefix. Its update is:

```text
if current <= farthest:
    farthest = max(farthest, current + nums[current])
```

Exact jumps can leave holes: for `[2,0,2]` starting at 0, Jump Game III reaches
index 2 but not index 1. A farthest boundary cannot represent that distinction.

In Jump Game II BFS, discoveries also form a prefix. Here `boundary` means
all indices `0..boundary` have already been enqueued, not necessarily processed.
For each current index, enqueue only
`maxOf(current + 1, boundary + 1)..end`, where
`end = minOf(current + nums[current], n - 1)`. An empty range adds nothing.
Then set `boundary = maxOf(boundary, end)`: a shorter current reach must not
erase earlier discoveries and allow duplicate enqueueing. Equal-cost BFS
preserves minimum jump counts while this compression skips redundant checks.
The queue still requires O(n) space.

For Jump Game II's left-to-right DP, the same boundary can finalize each
destination once. The extra justification is that minimum jump counts are
nondecreasing with index: shorten the first jump that passes an earlier target
to land on it. Thus the first source reaching a new destination is no worse
than later sources. This is specific to these jump rules, not a general
first-update rule for DP. Disjoint new-destination ranges give at most n − 1
inner iterations in total; source processing is counted separately. See
[quadratic to linear DP](../leetcode/45_jump_game_ii/dp/EXPLANATION.md).

Before compressing state, ask: **Could two situations with the same summary
require different future decisions? Which input guarantee rules that out?**

Source examples: [Jump Game I](../leetcode/55_jump_game/EXPLANATION.md),
[Jump Game II](../leetcode/45_jump_game_ii/EXPLANATION.md), and
[Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Buckets: preserve frequencies when individual order is unnecessary

When the answer depends on how many items fall into each category, count items
in buckets instead of preserving their individual order. Define exactly what
each bucket means, and place each item into one category. This loses original
positions and order, so it is unsuitable when those details affect the answer.

For n items and B buckets, building a frequency array and scanning it costs
O(n + B) time and O(B) extra space. A small or provably bounded range makes
this useful; a huge maximum input value can make direct indexing impractical.
H-Index avoids that problem by bounding the relevant thresholds, not the input
values.

### Cap values when all relevant thresholds are bounded

If every query asks whether a value is at least h, with h <= B, replacing values
above B with B preserves the answers. In H-Index, n papers imply h <= n,
so bucket n can combine all papers with at least n citations. Buckets below n
count exact citation values, including zero. Each paper enters one bucket.
This is safe because the answer needs threshold counts, not citation sums or
the exact ordering of values above n. Capping does not preserve exact-value
queries: a paper with 100 citations is not a paper with exactly n citations.

### Combine exact counts to answer threshold queries

With exact-value buckets, a prefix sum counts values at most a threshold;
a suffix sum counts values at least a threshold. Disjoint categories allow
these counts to be added without double-counting. For H-Index's capped final
bucket, suffix counts remain exact for thresholds 0 through n.

Scan buckets downward and add `count[h]` to a running total. After the update,
the total counts papers with at least h citations; comparing one bucket alone
would miss papers with higher counts. The first passing h is maximal because
every larger candidate was checked first. This replaces sorting with O(n)
counting time and O(n) extra space. It is time-optimal for arbitrary unsorted
input, not a claim of optimal space.

Recognition question: **Do I need the items' order, or only their frequencies?
Can I bound the useful categories, and which distinctions can I safely merge?**

Worked derivation, state definitions, Kotlin code, and trace:
[H-Index: sorting to capped buckets](../leetcode/274_h_index/EXPLANATION.md).

## Deriving DP states instead of guessing dimensions

Ask: “If I pause here, what must I know to solve the remaining problem?” Then
define what answer is stored for that situation. The state identifies a
subproblem; its value is the Boolean, count, best score, or other result.

**Sufficiency test:** Find two histories your state treats as identical. Could
they have different future choices or answers? If yes, add the missing
information. For example, under a jump limit, the same index with one remaining
jump can fail while two remaining jumps succeed.

Dimensions can also organize easier questions. In unlimited Jump Game III,
the index alone describes reachability, but its dependencies can cycle. Defining
`dp[k][i]` as “can reach zero from i with at most k jumps” creates dependencies
only on k - 1. A position cycle is no longer a cycle among these DP states.

Before coding, write: **state meaning → transitions → base cases → dependency
order → final answer → number of states and cost per state**. A valid DP
formulation is not automatically the most efficient algorithm.

## Prove a bound before introducing a budget dimension

When revisiting a state offers identical future choices, remove cycles from
any successful path. In a graph with n vertices, reachability then has a
witness using at most n - 1 edges. This bounds a jump-budget DP even when the
original task has no explicit limit.

This applies to reachability with history-independent moves. Do not assume
cycles are removable when the goal or rules require counting walks, spending
an exact number of moves, or changing resources through repeated visits.

“At most k” permits immediate success with zero moves. In Jump Game III,
`dp[0][i] = (arr[i] == 0)`. Initialize that row before transitions using k - 1.

## Rolling arrays: preserve the layer meaning

If layer k reads only layer k - 1, two arrays suffice. Finish all writes using
the unchanged previous layer before swapping. This saves space, not necessarily
time: n layers with n updates each still cost O(n²).

In-place updates may mix old and new layers. For `[0,1,1]`, starting from
`[true,false,false]`, a left-to-right scan can mark both indices 1 and 2 true.
It has propagated two jumps in a supposedly one-jump layer.

That breaks the jump-budget meaning, but can still be valid for a different
goal: repeatedly propagate eventual reachability until no new truths appear.
Recheck the state definition and correctness whenever the update order changes.

## Replace repeated scans with a queue of changed results

Ask: **“When this answer changes, which other states could be affected?”**
Store those dependencies so they can be found without rescanning everything.

For a legal move `i → j`, record `predecessors[j].add(i)`. A predecessor list
stores who can jump TO an index. `j ± arr[j]` only describes where j can jump
FROM; it cannot recover incoming moves whose lengths depend on other indices.

For Boolean reachability:

1. Seed true states whose success is already known (all zero-valued indices).
2. Pop a known-true state and mark its still-false predecessors true.
3. Enqueue each newly true index once; skip already-true predecessors.

False initially means “not established yet.” After exhaustive propagation,
remaining false states are unreachable. This is multi-source BFS on reversed
edges and computes which original states can reach any seeded target.

**Why linear here:** Each Boolean changes once, and Jump Game III has at most
2n edges. Processing each changed state and its dependents therefore costs
O(n) time and space. A queue alone does not guarantee linear time: if values
can improve repeatedly, count all changes and repeated edge processing.

Worked derivation, exact trace, and implementation:
[Jump Game III: DP to reverse BFS](../leetcode/1306_jump_game_iii/dp_to_reverse_bfs/EXPLANATION.md).
