# Algorithm concepts cheatsheet

Transferable rules, organized by concept rather than by exercise. Each entry
states when a rule applies and why it works. Problem links are references for
the derivation, code, and detailed proof; the rule should make sense without them.

For the process of deriving a solution, use
[the solving workflow](algorithm-solving-workflow.md).

## Reuse exact matches through prefix–suffix overlaps

For contiguous exact string matching, after a mismatch, a candidate starting
inside the already matched region can survive only if its retained text suffix
equals a pattern prefix. Because the matched region equals a pattern prefix,
its proper borders (prefixes also equal to suffixes) identify these overlaps.
Try the longest border first; borders of that border give the shorter candidates.
This avoids rescanning text without skipping a possible occurrence.

Define whether the failure table stores a length or a last index. With a last
matched index `j` and `-1` for no match, the matched length is `j + 1`, the next
pattern character is at `j + 1`, and fallback is `j = failure[j]` while keeping
the mismatching text character fixed. For matched `sasas`, retained lengths
are `5 → 3 → 1 → 0`. An arbitrary substring is not a valid retained overlap.

**Cost:** KMP takes O(n + m) time and O(m) auxiliary space for text length n
and pattern length m. Fallbacks can retry one text character repeatedly;
linear time follows because total decreases of matched length are bounded by
total increases, each charged to an advancing scan step. Monotonic text scanning
alone is insufficient to establish this bound.

Reference: [String matching and failure tables](../leetcode/28_find_the_index_of_the_first_occurrence_in_a_string/EXPLANATION.md).

## Define aggregates by ranges, not by ambiguous index names

For n elements, boundaries 0 through n describe cuts between elements. A useful
convention is `prefix[k]` over `[0, k)` and `suffix[k]` over `[k, n)`.
State these ranges explicitly: an inclusive suffix and an exclusive suffix
require different formulas.

Use the operation's identity for an empty range: 0 for sums, 1 for products.
This makes boundary cases follow the same recurrence as other positions.
For products, the aggregate excluding index i is
`prefix[i] * suffix[i + 1]`, because those ranges omit exactly that element.
For `[1,2,3,4]`, excluding index 2 gives `2 * 4 = 8`.

**Limit:** Numeric overflow still matters. Removing an element by division
requires assumptions that fail at zero.

Reference: [Product Except Self](../leetcode/238_product_of_array_except_self/EXPLANATION.md).

## Replace stored aggregates with running values when access is sequential

If an aggregate is consumed only once in scan order, it may need only a running
value. Keep it equal to the range required by the current answer; extend it
only after using it if the current element must be excluded.

Reuse an output slot only after its old value's final use. This is a dependency
argument: compression is safe because no future computation needs the erased
information. Arbitrary later queries may still require the full aggregate array.

**Cost:** This can reduce auxiliary space without changing time complexity.
O(1) auxiliary space excluding an n-element output still means O(n) total
additional storage including that output.

Reference: [Product Except Self](../leetcode/238_product_of_array_except_self/EXPLANATION.md).

## Endpoint totals and intermediate feasibility are different conditions

For additive changes, define `pre[k] = sum(change[0 until k])`. The change over
`[a, b)` is `pre[b] - pre[a]`. Starting with resource R at boundary a leaves
`R + pre[b] - pre[a]` at boundary b.

If the resource must stay at least L, check this inequality at every visited
boundary, not just the destination. For changes `[2,-3,4]`, the final change is
positive, but starting with 0 violates a lower bound of 0 after the second step.

For a fixed sequence, let m be the minimum prefix sum, including the empty
prefix 0. The minimum initial resource is `L - m`: it raises the lowest point
to L, and any smaller initial amount fails there. This assumes additive changes,
no capacity limit that discards gains, and the same lower bound initially and
after every step.

Reference: [Minimum Value to Get Positive Step by Step Sum](../leetcode/1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md).

## A minimum prefix can select a feasible rotation

For a nonempty circular sequence of additive changes with total T >= 0,
choose a smallest prefix boundary s among `0 until n`.

- Before wrapping, each partial change is `pre[k] - pre[s] >= 0`.
- After wrapping, it is `T + pre[k] - pre[s] >= 0`.

Both inequalities follow from the minimum-prefix choice. Thus the rotation
starting at s keeps every partial sum nonnegative. Negative total makes every
rotation impossible when starting empty.

**Condition:** Gains must accumulate without being discarded; a capacity limit
can invalidate this reasoning. A nonnegative total alone does not make an
arbitrary starting boundary feasible.

Reference: [Gas Station](../leetcode/134_gas_station/EXPLANATION.md).

## Use dominance to eliminate candidates in groups

Suppose attempt A first fails after step i. At an earlier boundary k it had
nonnegative resource. Attempt B starts empty at k and faces the same future
additive changes, so it has no more resource than A at every later boundary.
It therefore also fails by i. One failure can rule out an entire interval of
candidate starts, instead of retrying each one.

**General rule:** Candidate B can be discarded when another candidate starts
at least as favorably, faces equivalent future choices, and still cannot succeed.
The comparison must persist through future transitions; an apparent advantage
is insufficient if the candidates have different options or resource behavior.

**Pitfall:** Eliminating earlier candidates proves they fail; it does not alone
prove the surviving candidate completes the whole task. Prove the remaining
portion separately, including any wraparound.

Reference: [Gas Station](../leetcode/134_gas_station/EXPLANATION.md).

## Combine data structures through an explicit shared invariant

A dense array and a value-to-index map complement each other: the array gives
indexed access, and the map gives location by value. For unique values, maintain
`indices[values[i]] == i` after every operation.

When order and stable indices are unnecessary, deletion can move the last
element into the deleted slot, repair its map entry, then remove the old key and
last slot. This avoids shifting. Updating the moved entry before deleting the
requested key also handles deletion of the last element correctly.

**Cost:** Indexed access is O(1), dynamic-array append is amortized O(1), and
hash lookup/update is expected O(1), not a per-operation worst-case guarantee.

Uniformly sampling an array index samples values uniformly only if each value
occupies exactly one slot. Duplicates weight values by multiplicity. Equal
probabilities do not guarantee equal observed counts in a small sample.

Reference: [RandomizedSet](../leetcode/380_insert_delete_getrandom_o1/EXPLANATION.md).

## Choose traversal order according to the objective

In a finite graph, complete DFS and BFS both answer reachability when repeated
states are handled correctly. Their order may change the first path found.

BFS also guarantees a path with the fewest edges: FIFO processing finishes
distance d before distance d + 1. This minimizes total cost when every edge
has the same positive cost. DFS's first success has no such guarantee;
ordinary BFS does not guarantee minimum cost with unequal edge costs.

| Order | Deque operations | Meaning |
| --- | --- | --- |
| Stack | `addLast`, `removeLast` | Last in, first out |
| Queue | `addLast`, `removeFirst` | First in, first out |

Two queues can represent current and next BFS layers. Finish one layer before
advancing distance; order within a layer does not affect equal-cost distances.
Layer organization alone does not reduce neighbor-generation work.
Store distances to return a count and parents to reconstruct a path.

References: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md),
[BFS distance layers](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).

## A visited key must identify equivalent future situations

Explore a state once only when revisiting it offers no new relevant choices.
A physical position alone is not a sufficient key if remaining resources,
move budgets, or history change what can happen next.

For basic reachability, permanent visited marks prevent cycles and repeated
expansion. A repeated visit being skipped does not mean that state's answer
has been proved false: visited marks and cached subproblem answers have
different meanings. Path enumeration may require different marking rules.

Marking before enqueueing prevents duplicate pending entries. In equal-cost
BFS, first discovery also fixes the shortest distance and its parent.
Marking when removing can still work if duplicates are skipped before expansion,
but pending duplicates must be counted in time and space analysis.

Reference: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Count total work, not just states or loop nesting

Time is the sum of work performed over all processed states. Visiting n states
once can still take O(n²) if each generates O(n) transitions. Adjacency-list
traversal is O(V + E) because both vertices and edges are counted.

Nested loops can be linear when their combined inner iterations visit globally
disjoint new items. Prove that a boundary only advances or that each item is
charged a bounded number of times. A visited set may prevent enqueueing without
preventing repeated checks of overlapping neighbors.

For an unobstructed m-by-n grid with right/down moves, complete corner-to-corner
paths number `C(m + n - 2, m - 1)`. Scanning every complete path separately costs
O((m + n) times that count). A DFS sharing prefixes requires counting its calls
instead. A DP with mn states and constant work per state takes Θ(mn), regardless
of the number of paths. Square-grid path counts grow exponentially in side
length, not in total cell count.

Include pending entries, recursion depth, copies, and library operations in
the analysis; qualify amortized costs. Reducing stored data does not automatically
reduce computation.

References: [Counting range scans](../leetcode/45_jump_game_ii/dp/EXPLANATION.md),
[Path enumeration versus DP](../leetcode/174_dungeon_game/LEARNING_SUMMARY.md).

## Execution style, search order, and DP describe different things

Iteration and recursion describe how code executes. DFS can use recursive calls
or an explicit stack; both may require memory proportional to search depth.

Dynamic programming stores and reuses subproblem results. It can be recursive
or iterative. Replacing recursion with loops does not by itself create DP.
BFS organizes work by distance; DP organizes it around subproblem dependencies.
These views can overlap, but neither is implied merely by a request to minimize.

**Pitfalls:** Memoization alone does not resolve cyclic dependencies. Recursive
short-circuiting, such as `search(a) || search(b)`, allows early success but does
not prevent cycles or replace visited-state handling.

Reference: [BFS and DP comparison](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).

## Compress state only when discarded distinctions cannot affect the answer

If a reachable set is guaranteed to be a continuous prefix, one endpoint can
represent it. Extend it only from a reachable source and never decrease it.
If exact moves leave holes, the farthest endpoint cannot describe which
intermediate positions are reachable.

The same structure can remove repeated scans: when discoveries are guaranteed
to form a prefix, examine only positions beyond the discovery boundary. Define
whether the boundary means discovered or processed; those are different states.

**Extra condition for optimization values:** Discovering a destination once
does not generally finalize its best value. Later sources must be unable to
improve it, for example because sources are processed in nondecreasing optimal
cost and all outgoing moves add the same cost. Prove that ordering property
before skipping updates.

Test any summary by asking: can two situations with the same summary have
different relevant futures? If yes, the compression loses necessary information.

References: [Reachable-prefix structure](../leetcode/55_jump_game/EXPLANATION.md),
[Finalizing new destinations](../leetcode/45_jump_game_ii/dp/EXPLANATION.md),
[Exact moves with holes](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Keep frequencies when individual identity and order are unnecessary

If only category counts affect the answer, use buckets instead of storing or
sorting individual items. Each item must enter exactly one category. For n
items and B buckets, counting and scanning cost O(n + B) time and O(B) space.
A huge category range can make direct indexing impractical.

Threshold queries can justify merging categories: if every query is `value >= h`
with h <= U, replacing values above U with U preserves those answers. It does
not preserve exact-value queries, sums, or distinctions among larger values.
For example, capping at 5 preserves `value >= 4`, but not `value == 100`.

Prefix counts answer “at most”; suffix counts answer “at least.” Add counts of
disjoint buckets to avoid double-counting. Scanning candidate thresholds from
largest to smallest makes the first passing candidate maximal, provided the
predicate is tested correctly and every larger candidate was considered.

Reference: [Capped buckets and threshold counts](../leetcode/274_h_index/EXPLANATION.md).

## Cancel unequal pairs when one value exceeds all others combined

A strict majority occurs m times among n items with `m > n - m`. Removing
two unequal values preserves that majority: removing one majority and one
other leaves the difference unchanged; removing two others increases it by 2.
The positive excess therefore cannot disappear, so the majority must survive.

Boyer–Moore compresses the uncanceled values into a candidate and a balance.
After every prefix, its items partition into unequal canceled pairs plus
`balance` copies of the candidate. A match adds a copy; a mismatch cancels
one; at zero balance the next item starts a new candidate. At the end, the
surviving candidate must be the guaranteed majority: O(n) time, O(1) space.

**Limits:** The balance is not the candidate's frequency. Zero balance describes
only the processed prefix. Without a strict-majority guarantee, count the final
candidate in a second pass and check `occurrences > n / 2`; a unique mode is
insufficient. For example, `[1,1,2,3]` has a unique mode but no majority.

Reference: [Majority Element](../leetcode/169_majority_element/EXPLANATION.md).

## Separate the identity of a DP subproblem from its stored answer

A state identifies a situation; its value stores that situation's answer
(a Boolean, count, minimum requirement, or best score). Include enough information
to distinguish histories with different relevant futures.

Adding a remaining-step dimension can turn cyclic position dependencies into
acyclic state dependencies: layer k reads only layer k - 1. This is a valid
formulation, not necessarily the most efficient one.

For finite, history-independent reachability, remove cycles from a successful
path to obtain a witness of at most V - 1 edges. This can bound a step-budget
dimension. The argument does not apply to counting walks, requiring exactly k
moves, or collecting resources through repeated visits. An “at most k” state
must allow immediate success using zero moves.

Reference: [Budget-layer DP](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Backward requirements can summarize an entire future

With additive resource changes, a fixed lower bound L, no capacity limit, and
acyclic dependencies, store the minimum resource required **before** the current
change to complete the remaining task. If any one successor is sufficient,
let q be the smallest successor requirement. For current change d:

```text
required = max(L, q - d)
```

Resource R must satisfy both `R >= L` and `R + d >= q`; the formula is the
smallest R satisfying both. Compute successors first. Reverse computation
does not reverse the task's legal movement.

Use L as the requirement after the final change when the same bound must still
hold. Invalid continuations must stay unavailable. The stored requirement is
not the actual resource remaining during a forward journey.

**Distinction:** `min` chooses a continuation; `max` enforces survival. Combining
them does not mean minimizing path length. Final totals alone cannot represent
intermediate resource shortages.

References: [Resource requirements on a path](../leetcode/1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md),
[Resource requirements with route choices](../leetcode/174_dungeon_game/EXPLANATION.md).

## Prove that later writes preserve earlier constraints

Suppose `x >= y + c` has been established, with fixed c. A sufficient condition
for preservation is that later writes only increase x and leave y unchanged:

```text
x' >= x >= y + c = y' + c
```

Check every write to both sides. A guard can prove an entry stays unchanged
when its condition contradicts the ordering assumed by the earlier constraint.
The contradiction must follow from the actual predicates, not from an absent
if statement. Preserving a relationship does not require freezing both values.

**Pitfall:** Increasing values with `max` alone is insufficient if the right
side can also increase: `2 >= 1 + 1` fails when the 1 becomes 2. The sufficient
condition above is one proof method, not a necessary condition for every algorithm.

**Transferable optimization:** Separate constraint families into dependency-ordered
passes when each pass establishes its constraints and preserves the others.
This can remove repeated correction or priority ordering. The gain still needs
a work count; it is not a universal rule for skipping DP iterations.
Constraint satisfaction and minimum total cost require separate arguments.

Reference: [Two directional scans: preservation proof](../leetcode/135_candy/EXPLANATION.md).

## Rolling arrays must preserve the meaning of a layer

If layer k reads only layer k - 1, two arrays suffice: keep the previous layer
unchanged until every new value is computed, then swap. In-place updates can
read new values and accidentally perform multiple transitions within one layer.

For a chain A → B → C, starting with only A reachable, an in-place scan might
mark B and then C in a layer intended to allow only one move. Using the old
layer reaches B but not C. The same immediate propagation might be appropriate
for eventual reachability, which is a different state definition.

**Cost:** Keeping two layers reduces space; it does not remove the work of
computing every layer. Rejustify correctness when changing update order.

Reference: [Layered reachability](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Process changed answers through their dependents

If a changed answer affects only known dependents, record those dependencies
and queue the affected work instead of repeatedly scanning every state.
For an edge `a → b`, record a in `predecessors[b]`: outgoing edges from b
generally cannot reveal who points to b.

For Boolean reachability, seed known-success states and propagate success to
their predecessors. Initially false means “not established yet”; after exhaustive
propagation, remaining false states cannot reach a seed. Each state changes
from false to true at most once, so processing its incoming edges costs O(V + E).

**Condition:** This bound depends on one-time changes and bounded dependency
processing. If values improve repeatedly, count every change and repeated edge
scan; using a queue alone does not guarantee linear time.

Reference: [Reverse dependency propagation](../leetcode/1306_jump_game_iii/dp_to_reverse_bfs/EXPLANATION.md).
