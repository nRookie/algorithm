# Algorithm concepts cheatsheet

Reusable facts collected from solved problems. For how to derive a solution,
use [the solving workflow](algorithm-solving-workflow.md). Full implementations
and traces belong in each problem's `EXPLANATION.md`.

To add future lessons, ask: **“What can we learn from this? Update the cheatsheet.”**
Keep the condition behind each rule, not just the rule itself.

## Prefix and suffix arrays: indexes can represent boundaries

For n elements, use n + 1 boundaries numbered 0 through n. Boundary k is
after the first k elements. Define `prefix[k]` over `[0, k)` and `suffix[k]`
over `[k, n)`: both use the same cut, looking left and right respectively.
This is a common convention, not a requirement; always state the ranges.

For products, empty ranges have value 1: `prefix[0] = suffix[n] = 1`.
For sums, the empty value is 0. These identity values allow the first real
element to be combined without a special branch.

- Left to right: `prefix[i + 1] = prefix[i] * nums[i]`.
- Right to left: `suffix[i] = nums[i] * suffix[i + 1]`.
- Exclude index i: `prefix[i] * suffix[i + 1]`; the two ranges cover every
  element except i. For `[1,2,3,4]`, excluding index 2 gives `2 * 4 = 8`.

**Pitfall:** This `suffix[i]` includes `nums[i]`. A suffix defined as strictly
after i instead uses different recurrence and answer indexes. Adding a slot
does not justify shifting formulas without redefining the stored ranges.
Products require suitable numeric bounds; division-based removal fails at zero.

### Reuse output and keep only the running aggregate when possible

If each suffix is needed only once in right-to-left order, keep a single
running product instead of the full suffix array. For Product Except Self,
store exclusive prefixes in `answers`; at index i, multiply by the current
suffix **before** extending it with `nums[i]`. Before use, the suffix must
represent exactly the elements strictly to the right of i. The update order
preserves that meaning for the next index.

This reduces storage, not the asymptotic time: O(n) time and O(1) auxiliary
space **excluding output**, but O(n) total additional space including the
returned array. Reuse is valid only when overwriting a value cannot destroy
data needed later; storing all aggregates remains useful when later queries
need arbitrary entries.

Full derivation, original and improved Kotlin implementations, and boundary
walkthrough: [Product Except Self](../leetcode/238_product_of_array_except_self/EXPLANATION.md).

### Prefix sums answer totals; path feasibility needs intermediate sums

For additive changes, define `pre[k] = sum(change[0 until k])`. Then the
combined change over `[a, b)` is `pre[b] - pre[a]`. Starting with resource R,
the remaining amount at boundary b is `R + pre[b] - pre[a]`. When resource
must never be negative, this must hold at **every intermediate boundary**,
not only the endpoint. For changes `[2,-3,4]`, the total is 3 but starting
empty at index 0 fails after the second change. Zero remaining is allowed.

For a circular additive sequence with nonnegative total, starting at a
smallest prefix boundary among indices `0 until n` makes all rotated partial
sums nonnegative: before wrapping, subtract that minimum from later prefixes;
after wrapping, additionally add the nonnegative total. This models Gas
Station with an empty initial car and unlimited capacity. It does not account
for capacity limits that discard collected gas.

For a fixed additive sequence whose value must stay at least L, including the
initial value, let m be the smallest prefix sum including the empty prefix 0.
The minimum initial value is `L - m`: adding it raises even the lowest prefix
to L. An equivalent backward requirement is
`required[i] = max(L, required[i + 1] - change[i])`, with terminal requirement
L. For 1413, L = 1; Gas Station allows remaining gas 0. Requirements before a
suffix are different from actual values during a forward simulation.

Both implementations and their connection to Gas Station DP:
[Minimum Value to Get Positive Step by Step Sum](../leetcode/1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md).

### A first failed attempt can eliminate a whole interval of starts

With the same additive changes, starting empty at s and first failing after
processing i rules out every start in `[s, i]`. The original attempt reached
each such station with nonnegative resources; starting there empty provides
no more, and identical future changes cannot remove that disadvantage.
Reset the candidate to `i + 1` and its local sum to 0. Keep a separate total
without resetting. For Gas Station, the total check also establishes that
the final candidate completes the wrapped portion; the surviving local sum
alone establishes only the portion through the array's end.

Full proof and retrospective on the incorrect prefix/suffix predicate:
[Gas Station](../leetcode/134_gas_station/EXPLANATION.md).

## Combine indexed storage with a value-to-index map

For unique values, a dense ArrayList plus a HashMap from value to index supports
average O(1) membership and location, with O(1) indexed access. Keep
`indices[values[i]] == i` between operations. Append and record the old size as
the new index; after appending, the index is `size - 1`. Appending is amortized
O(1), because occasional capacity growth copies elements; hash operations have
average/expected O(1) cost. These are not per-operation worst-case guarantees.

When order is irrelevant, remove a value by replacing its slot with the last
value, updating the moved value's index, deleting the requested map key, and
removing the last slot. This avoids shifting. Update the moved value's map
entry before deleting the requested key so removal of the last element does
not recreate that key. This technique does not preserve order or stable indices.

Uniform random indices give uniform random values **when each value occupies
exactly one slot**: each of n members has probability 1/n. Moving members
between slots preserves this; duplicates would weight values by multiplicity.
Equal probability does not guarantee equal counts in a small sample.

Derivation, Kotlin collection details, and removal trace:
[RandomizedSet](../leetcode/380_insert_delete_getrandom_o1/EXPLANATION.md).

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

For an unobstructed m × n grid with only right/down moves, the number of
complete corner-to-corner paths is `C(m + n - 2, m - 1)`: choose where the
downward moves occur. Separately scanning each complete path costs
`O((m + n) × number of paths)`. This does not describe every DFS implementation;
if it shares prefix work, count its recursive calls instead. Dungeon Game's
backward DP processes mn states with constant work each, giving Θ(mn) time
regardless of the dungeon values or number of routes. Path count grows
exponentially in a square grid's side length, not its total cell count.

Worked comparison: [Dungeon Game learning summary](../leetcode/174_dungeon_game/LEARNING_SUMMARY.md).

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

### Backward resource requirements with a choice of continuations

For additive resource changes, no upper capacity limit, and acyclic movement,
store the minimum resource needed before applying the current state's change
to complete the task. If any one continuation suffices, choose the smallest
successor requirement, then use
`required = max(lower bound, smallest next requirement - current change)`.
Compute successors first; reverse computation does not reverse legal movement.

Dungeon Game requires health at least 1 and chooses between right/down
successors. Initialize the terminal continuation to 1; invalid outside moves
must remain unavailable. Its padded implementation sets only the two virtual
successors of the destination to 1, leaving other outside entries infinite.
The stored requirement is not health remaining during a forward journey.

Here `min` chooses one sufficient continuation, while `max(lower bound, ...)`
enforces resource feasibility. This is path optimization by initial resource,
not shortest path by number of moves: every complete right/down route has
`m + n - 2` moves. A route's final resource or total change alone does not
capture its intermediate shortages.

State definition, corrected comments, full table illustration, and proof:
[Dungeon Game](../leetcode/174_dungeon_game/EXPLANATION.md).

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

## Prove that later updates preserve earlier inequalities

**Rule:** An established inequality `x >= y + c`, with fixed c, survives if
later updates never decrease x and never change y. This is a sufficient
condition; check every write that could affect either side. Preserve the
relationship, not necessarily the exact stored values.

**Candy example:** Let A be dp after the left-to-right scan and B be dp after
the right-to-left scan. Choose any adjacent pair with
`ratings[i] > ratings[i - 1]`. The first scan establishes
`A[i] >= A[i - 1] + 1`. In the second scan:

- `B[i] >= A[i]`, because updates use `maxOf(existing, requirement)`.
- Index `i - 1` could update only if `ratings[i - 1] > ratings[i]`, which
  contradicts this pair's ordering. Only its own iteration writes that entry,
  so `B[i - 1] = A[i - 1]`.

Combining these facts proves preservation for every such pair:

```text
B[i] >= A[i] >= A[i - 1] + 1 = B[i - 1] + 1
```

The guard is false because the two strict comparisons are mutually exclusive,
not because an if statement is missing. `maxOf` alone is insufficient if the
right-hand side can also increase: `2 >= 1 + 1` would fail if 1 became 2.

**Optimization:** Complementary guarded constraints can sometimes be handled
in separate directional scans without revisiting previously satisfied ones.
For Candy, two linear scans replace increasing-rating heap order, reducing
O(n log n) time to O(n), with O(n) auxiliary space. The proof justifies this
processing order; it is not a universal rule for skipping DP iterations.
Preservation establishes feasibility of the earlier constraints. Minimum
total candies still requires a separate minimality argument.

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
