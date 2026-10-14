# LeetCode 743 — Network Delay Time

[Problem](https://leetcode.com/problems/network-delay-time/) · Medium.
Directed weighted edges; nodes 1..n; signal starts at k. Return the time when
every node has received the signal, or -1 if any node is unreachable.
Constraints include n <= 100 and edge weights from 0 to 100.

## Learner's approach

The learner chose an adjacency list of Edge(to, weight) with basic Dijkstra's
linear selection. This is valid even though matrix practice was initially
suggested. Keep the supplied IntArray distances and collection-based graph.

“I compute the shortest distance from k to every node. Each distance is the
earliest time that node receives the signal. The last node to receive it
determines the total delay, so I take the maximum distance. If any node is
unreachable, I return -1. Node 0 is unused, so I scan only 1..n.”

This maximum is over shortest distances, not over all possible paths.

## Review correction: unreachable selection

The original draft immediately marked t visited and relaxed its edges after
selection. It needed this guard before doing either:

```kotlin
if (t == -1 || dist[t] == Int.MAX_VALUE) return -1
```

Without the guard, an unreachable node can be selected with infinite distance.
Adding a positive weight to Int.MAX_VALUE overflows. For example, with n=3,
k=1, and only edge 2→3 of weight 1, processing node 2 would incorrectly assign
node 3 a negative distance. The original final scan still catches unreachable
node 2 in this example and returns -1, but the distance calculation is invalid.
The guard ensures every relaxation starts from a finite distance.

All other algorithmic choices are preserved. The final unreachable check is
now redundant but retained to match the learner's reasoning. Int is sufficient
for finite distances under this problem's constraints.

## States, correctness, and complexity

dist[u] is the best route cost found so far. visited[u] means its shortest
distance is finalized. Each iteration selects the unvisited node t with the
smallest distance and relaxes only its unvisited outgoing neighbors.

Nonnegative weights make finalization safe: a hypothetical shorter route to t
would contain a first unvisited node whose tentative distance, after relaxation
from its visited predecessor, is smaller than dist[t]. This contradicts the
minimum selection. The source is the initial case with distance zero.
See the [basic Dijkstra proof](../basic-dijkstra/EXPLANATION.md).

If the selected minimum is infinity, every remaining node is unreachable. If
all nodes are finalized, their shortest distances are their earliest signal
arrival times, and the maximum is exactly when all nodes have received it.

Time O(n² + m): n scans of up to n nodes plus at most m edge relaxations.
Space O(n + m) for the adjacency lists, distances, and visited flags.

## Local validation

Run `bash recap/graph/shortest-paths/leetcode-743-network-delay-time/run.sh`.
Checks cover the three official examples, an unreachable component with an
outgoing edge, later improvement of a tentative distance, zero-weight edges,
a maximum-weight 100-node chain, and source-only reachability.

## Learner's adjacency-matrix implementation

[MatrixSolution.kt](MatrixSolution.kt) preserves the learner's Array<IntArray>
matrix, IntArray distances, and MutableList visited flags. The unused Edge
declaration was removed. The same unreachable-selection guard was added before
finalizing t to prevent adding a weight to Int.MAX_VALUE.

Checking graph[t][j] != Int.MAX_VALUE only checks that an edge exists; it does
not establish that t is reachable from k. Both conditions are needed before
relaxation. Direct assignment graph[u][v] = w is valid here because LeetCode 743
guarantees unique directed endpoint pairs. A general multigraph matrix would
retain the minimum of parallel edge weights.

The list iterates actual edges; the matrix scans all possible destinations.
Selection, finalization, correctness, and the final maximum are unchanged.
Matrix time is O(n² + m), and total space is O(n²).

Both files define class Solution and can be submitted separately. Compile only
one at a time with the shared tests:

```sh
bash recap/graph/shortest-paths/leetcode-743-network-delay-time/run.sh list
bash recap/graph/shortest-paths/leetcode-743-network-delay-time/run.sh matrix
```

LeetCode 1334 is deferred until the Floyd–Warshall recap. The learner chose to
practice both representations on 743 to focus on graph storage changes.

## Learner's heap implementation

[HeapSolution.kt](HeapSolution.kt) preserves the learner's implementation, adding
the java.util.PriorityQueue import. Compile it separately from the other Solution
classes. Run the shared checks with `bash recap/graph/shortest-paths/leetcode-743-network-delay-time/run.sh heap`.

### Solution evolution

Basic Dijkstra scans every unvisited node to select the smallest tentative
distance. The heap version retrieves the smallest recorded distance using a
priority queue. The adjacency list and relaxation formula remain the same.

Edge(to, weight) describes one outgoing edge in the graph. State(node, distance)
records a candidate distance from the source to a node, not an individual edge
weight. Queue entries are immutable snapshots; changing dist does not change
an existing entry. A successful relaxation adds a new snapshot.

### Why skip outdated entries?

Suppose edges are 1→2 (10), 1→3 (1), and 3→2 (2). Processing 1 inserts (2,10)
and (3,1). Processing 3 improves dist[2] to 3 and inserts (2,3). Both entries
for node 2 remain in the heap. The entry (2,3) is processed first. Later (2,10)
is skipped because its distance is larger than the current dist[2].

```kotlin
if (dist[state.node] < state.distance) continue
```

Equivalently: state.distance > dist[state.node], or !=. Distances only decrease,
so a saved entry cannot be smaller than the current best distance. Testing
state.distance < dist[state.node] would not detect stale entries.

### Why no visited list?

When a removed entry matches dist[node], it is the smallest current tentative
distance. With nonnegative weights, Dijkstra's finalization proof applies: its
distance cannot improve later. Older, larger entries are skipped. Equal-distance
routes do not create duplicate matching entries because relaxation uses strict
improvement (`>`), not `>=`. Thus each reachable node's outgoing edges are
processed once even without recording finalization in a Boolean list.

This argument relies on nonnegative weights and inserting only on strict
improvement. It does not mean visited flags are unnecessary in arbitrary graph
algorithms. SPFA's inQueue tracks pending work instead and allows a processed
node's distance to improve later.

Only finite distances enter the heap, so this implementation never relaxes
from Int.MAX_VALUE. Unreachable nodes remain infinite and the final scan returns
-1. Otherwise, the maximum shortest distance is the final arrival time.

Lazy heap time is O(n + m log(m + 1)), with O(n + m) total space; old entries
can occupy O(m) heap space. For this simple graph, the usual bound is
O((n + m) log n). The drop(1) result also uses O(n) temporary space.

## Next practice

[LeetCode 1976 — Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
is the exercise previously deferred until Dijkstra. It combines weighted
shortest paths with the counting idea from AcWing 1134. This is an extension,
not an identical distance-only problem. Use an undirected adjacency list,
source 0, destination n-1, and Long distances. Return the number of shortest
routes modulo 1,000,000,007. Keep its implementation for independent practice.
