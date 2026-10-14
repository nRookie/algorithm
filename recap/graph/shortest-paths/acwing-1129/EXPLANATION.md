# AcWing 1129 — queue-based weighted shortest paths (SPFA)

## Current recap order: Dijkstra first, then SPFA

[Dijkstra.kt](Dijkstra.kt) contains the basic priority-queue version, separated
into addEdge, readGraph, dijkstra, and main functions. Run it with
`bash recap/graph/shortest-paths/acwing-1129/run-dijkstra.sh sample` (or `stdin`).
Compile this file separately from Main.kt: both are standalone programs with
their own Edge declaration. Main.kt remains the SPFA version for later study.

Dijkstra's queue stores immutable (node, distance) entries, ordered by distance.
When a distance improves, insert a new entry. Skip a removed entry if its saved
distance differs from dist[node]; it is outdated. No inQueue flag is needed.
With nonnegative weights, a current minimum-distance entry can be finalized:
any hypothetical shorter path would have crossed from a finalized node to an
unfinalized node with a smaller tentative distance, contradicting the minimum
selection. Remaining edges cannot lower the path cost because they are nonnegative.

For this lazy heap implementation, time is O(V + E log(E + 1)) and total space
is O(V + E), including potentially O(E) heap entries. In a simple graph this is
commonly written O((V + E) log V) time. Input uses the same source/target format
and local unreachable convention described below.

## Contract and source

Based on the repository's [original C++ code](../../../../acwing/graph/single-source-shortest-path/1129.cpp).
Read `n m source target`, followed by `m` lines of `a b weight`.
Nodes are numbered 1 through n; each edge is undirected. Output the shortest
distance from source to target. This recap assumes nonnegative integer weights.
The local runner prints -1 for an unreachable target; this is a local convention,
not a verified original-judge requirement. Examples below are custom examples.

The learner's draft started at node 1. This version reads source and target to
match the saved AcWing input format. It also reads n and m, declares inQueue,
moves addEdge inside main so it can access graph, stores Edge objects rather
than integers, and prints the answer. The learner's relaxation loop and
addFirst/removeLast FIFO convention are preserved.

## Graph representation

`graph[u]` is a list of Edge(to, weight). An undirected edge is stored in both
directions. These are Kotlin collections, replacing the original h/e/ne/w
array-linked adjacency representation. Each row is independently allocated.
Distances use Long so sums can exceed the Int range.

## Why this is SPFA, not Dijkstra

Both algorithms use relaxation: if dist[u] + weight is smaller than dist[v],
update dist[v]. Relaxation alone does not identify the algorithm.

This implementation processes nodes in FIFO order. A node can leave the queue,
improve later, and enter again. This is SPFA, a queue-based Bellman–Ford variant.
inQueue means currently waiting, not permanently visited or finalized.

Dijkstra selects the unfinalized node with the smallest tentative distance.
With nonnegative weights, that selection allows its distance to be finalized.
A priority queue efficiently supports this selection; scanning all nodes is
also possible. Dijkstra is not defined merely by using a particular container.

Ordinary BFS can finalize distances on discovery when every edge has the same
positive cost. With different weights, first discovery need not be shortest.

## Execution example

Edges: 1–2 costs 10, 1–3 costs 1, 3–2 costs 1. Source 1, target 2.
Queue below is shown next-to-process first.

| Process | Distance changes | Queue afterward |
|---|---|---|
| Initialize | dist[1] = 0 | [1] |
| 1 | dist[2] = 10, dist[3] = 1 | [2, 3] |
| 2 | None | [3] |
| 3 | dist[2] = 2 | [2] |
| 2 again | None | [] |

The answer is 2. Do not return when the target is first removed: it may improve.
If a node improves while already queued, update its distance without adding a
duplicate. Its pending turn reads the latest distance.

## Correctness and termination

Every finite distance is the cost of an actual route: source starts at zero,
and each update extends a known route by one edge. Thus it cannot underestimate
the true shortest distance.

Every improvement schedules processing, or the node is already scheduled.
Once the queue is empty, every reachable edge satisfies
`dist[v] <= dist[u] + weight(u, v)` because u's latest improvement has propagated.
Applying these inequalities along a shortest path shows the final distance is
at most that path's cost. Combined with the first observation, it is exactly
the shortest distance. Unreachable nodes retain Long.MAX_VALUE.

With nonnegative integer weights, every successful update strictly decreases
a finite nonnegative integer. After first discovery there can only be finitely
many such decreases. Thus only finitely many queue entries are added.
Only reachable nodes enter the queue, so relaxation never adds to Long.MAX_VALUE.

A stack can also schedule these repeated relaxations correctly under these
assumptions. Processing order affects work, not this correctness argument.
SPFA can support negative edges when no reachable negative cycle exists, but
this implementation has no negative-cycle detection. That is outside this recap.

## Complexity

Worst-case SPFA time is O(VE), not BFS's O(V + E): nodes and their outgoing edges
may be processed repeatedly. Graph storage is O(V + E); distances, membership,
and queue need O(V) additional space. inQueue prevents duplicate pending entries.

## Interview wording

“I store the weighted graph as adjacency lists and track tentative distances.
When an edge gives a cheaper route, I update the neighbor and schedule it to
propagate that improvement. I track queue membership to avoid duplicate pending
entries, while allowing a node to return after a later improvement. This is SPFA;
unlike Dijkstra, I do not always select the smallest tentative distance.”

## Run locally

```sh
bash recap/graph/shortest-paths/acwing-1129/run.sh sample
bash recap/graph/shortest-paths/acwing-1129/run.sh stdin < input.txt
```

The custom sample prints 2. Priority-queue Dijkstra is the next recap;
LeetCode 1976 remains deferred until then.
