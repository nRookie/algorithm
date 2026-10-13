# AcWing 1134 — Counting shortest paths with BFS

[Your corrected Kotlin implementation](Main.kt)
· [Original C++](../../../../acwing/graph/single-source-shortest-path/1134.cpp)

## Contract

The user supplied the statement: an undirected, unweighted graph with nodes
1..N, possibly self-loops and parallel edges. Print N lines: the number of
shortest paths from 1 to each node modulo 100003. Unreachable nodes have
count zero. N <= 100000 and M <= 200000. Input starts with N M and then M
pairs of endpoints. The local sample is illustrative, not an official sample.

## Your reasoning and corrections

Build an adjacency list, initialize dist[1] = 0 and count[1] = 1, then traverse
with BFS. The saved code retains your nested bfs function, collection-based
storage, and addFirst/removeLast queue operations. Both operations together
give FIFO behavior. No manual edge arrays or linked-list indexes are needed.

The supplied attempt was corrected by reading m, reducing the whole count
sum modulo 100003, fixing braces and variable names, and outputting one count
per node rather than summing all counts. On discovery, assignment replaces
`+=` for clarity; the count at that point is zero.

## Graph and state

`graph[u]` lists neighbors; index 0 is unused. Each undirected input edge is
stored in both directions. Keep parallel edges: separate edges represent
separate route choices. A set would incorrectly discard them.

Self-loops may remain, even though the two-direction construction stores them
twice. A self-loop can never satisfy dist[u] == dist[u] + 1, so neither copy
contributes. A loop adds an edge without reaching a different vertex and
therefore cannot improve or tie the shortest distance to that vertex.

- dist[u] = -1 means undiscovered; otherwise it is the shortest edge count.
- count[u] is the number of shortest paths found, always reduced modulo 100003.
- queue holds discovered nodes whose outgoing adjacency lists await processing.
- count[1] = 1 counts the empty path from 1 to itself.

## Solution evolution

Enumerating simple paths and keeping the shortest ones is a direct but
potentially exponential approach. Positive unit edge lengths mean shortest
paths never need a cycle. BFS shares the work across all routes: it discovers
nodes in non-decreasing distance order and aggregates counts instead of
enumerating individual paths.

For each edge u to v:

1. If v is undiscovered, set its distance to dist[u]+1, copy count[u], and
   enqueue it. Record discovery before enqueueing to prevent duplicate work.
2. If dist[v] == dist[u]+1, add count[u] to count[v] modulo 100003. Do not
   enqueue it again: this is another route to an already discovered node.
3. Otherwise ignore the edge; it does not belong to a shortest path to v.

Do not use count[v] == 0 as the visited check: a reachable node's path count
can equal zero modulo 100003. dist is the discovery marker.

## Trace

Edges: 1–2, 1–3, 2–4, 3–4, 4–5. Queue below is shown in processing order
(next node first), regardless of the physical deque end used.

| Processed node | Queue afterward | Newly determined / updated counts |
| --- | --- | --- |
| Initialize | [1] | count[1]=1, dist[1]=0 |
| 1 | [2,3] | distances to 2 and 3 are 1, both counts are 1 |
| 2 | [3,4] | dist[4]=2, count[4]=1 |
| 3 | [4] | another shortest route: count[4]=2 |
| 4 | [5] | dist[5]=3, count[5]=2 |
| 5 | [] | no changes |

Output counts: 1, 1, 1, 2, 2, each on its own line.

## Correctness and cost

FIFO processing handles all distance-d nodes before distance-(d+1) nodes.
First discovery therefore assigns the minimum possible distance. Every
shortest path to v ends with an edge from a node u at distance dist[v]-1.
All such nodes are processed before v is removed from the queue, so its count
is complete before it propagates to the next layer. Copying the first
contribution and adding the rest counts exactly those shortest paths,
distinguished by their final edge and preceding path. Parallel edges give
separate contributions. Longer routes and self-loops are excluded by distance.

Each node is enqueued at most once and each stored edge is examined once.
Time is O(N+M), space O(N+M). Every count stays below 100003, so adding two
counts is safe in Int. Scanner is convenient for practice but may be slow
under tight judge limits at these sizes. Local tests do not imply online
acceptance or certify the judge's time/memory limits.

## Run locally

```sh
bash recap/graph/bfs/acwing-1134/run.sh sample
bash recap/graph/bfs/acwing-1134/run.sh stdin
bash recap/graph/bfs/acwing-1134/run.sh test
```

## LeetCode practice

- [1091 — Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/):
  Medium, a suitable immediate BFS exercise. It asks for a shortest path
  length rather than counts. The graph is implicit in the grid, uses eight
  directions, and measures path length in visited cells rather than edges.
- [1976 — Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/):
  Medium, closer counting objective but a later exercise. Roads have positive
  weights, requiring a weighted shortest-path method such as Dijkstra instead
  of plain BFS. Nodes are 0..n-1, the output is only for the final node, and
  the modulus is 1,000,000,007. Distances require Long. Unlike the AcWing
  contract, roads have no parallel edges or self-loops and the graph is connected.

Both public statements were checked during this recap. These are related
exercises, not identical contracts. Their solutions remain for independent practice.
