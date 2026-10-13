# LeetCode 1971 — Find if Path Exists in Graph

[Official judge](https://leetcode.com/problems/find-if-path-exists-in-graph/description/)
· [Your implementation](Solution.kt)

Your supplied algorithm and variable names are preserved; only formatting
was adjusted. Build an undirected adjacency list, then use BFS to determine
whether destination is reachable from source. Node labels are 0..n-1.
The graph may be disconnected; the judge excludes self-loops and duplicate
edges. It allows no edges and source equal to destination.

## Representation and traversal

`graph[u]` contains u's neighbors. Each input edge is stored in both
directions. `MutableList(n) { mutableListOf<Int>() }` constructs independent
neighbor lists, one per node.

Mark source visited and enqueue it. Your `addFirst` and `removeLast` operations
use opposite ends, so they implement a FIFO queue. Remove a node, return true
if it is the destination, and discover each unvisited neighbor. Mark each
neighbor visited before enqueueing it to prevent duplicate entries.

Only reachability is needed: visited stores discovery, and neither distances
nor shortest-path counts are necessary. For source == destination, the
zero-edge path suffices and the first dequeued node returns true.

## Solution evolution and correctness

Enumerating possible routes repeats work and can cycle indefinitely without
cycle handling. For reachability, the history used to reach a node does not
change its outgoing options. Processing each node once is sufficient.

Every enqueued node is reachable: source is reachable, and each new node is
connected by an edge to a reachable processed node. Thus returning true on
dequeue cannot invent a path.

Conversely, along any path from source, processing each predecessor discovers
the next node if it has not already been discovered. If the queue empties,
all reachable nodes have therefore been processed. Failure to find destination
then proves that no path exists. Each node enters the queue at most once,
so traversal terminates even in graphs with cycles.

## Trace

```text
n = 4
edges = [[0,1], [1,2], [2,0]]
source = 0, destination = 3
```

Queue shown in processing order (next removal first):

| Action | Queue | Visited nodes |
| --- | --- | --- |
| Initialize | [0] | {0} |
| Process 0; discover 1 and 2 | [1,2] | {0,1,2} |
| Process 1; both neighbors already visited | [2] | {0,1,2} |
| Process 2; both neighbors already visited | [] | {0,1,2} |

Return false: node 3 is disconnected. The triangle does not cause revisits.

## Complexity

Let V = n and E = edges.size. Building adjacency lists takes O(V+E) time
and stores 2E neighbor entries. BFS processes each reachable node at most
once and each of its adjacency entries once. Total time is O(V+E); extra
space is O(V+E), including graph storage, visited, and the queue. The input
edges are not modified.

## Interview wording

“I build an adjacency list with both directions for every edge, then run BFS
from source. I mark each node visited when enqueueing it so cycles cannot
cause repeated processing. If I reach destination, I return true. Otherwise,
an empty queue means all reachable nodes have been exhausted, so I return
false. Time and space are O(V+E).”

## Local checks

Run `bash run.sh` in this folder. Tests cover both published examples,
no-edge graphs, source equal to destination, cycles, and a 200,000-node
chain. These are local checks, not an online-judge acceptance claim.
