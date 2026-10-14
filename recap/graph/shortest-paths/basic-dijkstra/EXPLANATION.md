# Basic Dijkstra — adjacency matrix and adjacency list

Two standalone implementations use the same linear-scan Dijkstra algorithm:

- [Main.kt](Main.kt): adjacency matrix, preserving the original C++ structure.
- [AdjacencyList.kt](AdjacencyList.kt): adjacency list of Edge objects.

Compile them separately; each defines its own main, INF, readGraph and dijkstra.

## Comparing the representations

Matrix initialization:
```kotlin
val graph = MutableList(n + 1) { MutableList(n + 1) { INF } }
graph[a][b] = minOf(graph[a][b], weight)
```

List initialization:
```kotlin
data class Edge(val to: Int, val weight: Long)
val graph = MutableList(n + 1) { mutableListOf<Edge>() }
graph[a].add(Edge(b, weight))
```

Both allocate independent rows and leave index 0 unused. In the matrix, the
column identifies the destination and the stored value is its edge weight.
In the list, each Edge explicitly stores a destination and weight. Parallel
edges are collapsed to their minimum in the matrix; the list retains them,
and relaxation considers each one. Both produce the same shortest distances.

Selection of t is identical. The matrix scans all possible destinations and
skips missing edges; the list iterates only actual outgoing edges. Neither
version uses a queue. Both read directed edges and use nonnegative weights.

| Version | Time including input | Total space |
|---|---|---|
| Matrix | O(n² + m) | O(n²) |
| List with linear selection | O(n² + m) | O(n + m) |

The list saves storage on sparse graphs, but selecting nodes still costs O(n²).
It does not become O(m log n) without changing selection to a priority queue.

Based on the C++ implementation supplied in the conversation. The judge number
was not supplied, so this folder uses the algorithm name.

Read `n m`, followed by m directed edges `a b weight`. Find the minimum cost
from node 1 to node n, or print -1 if unreachable. We assume nonnegative weights
and path sums that fit in Long and are strictly below Long.MAX_VALUE.

This is Dijkstra without a queue: scan all unvisited nodes to select the smallest
tentative distance. A priority queue is a later optimization of this selection.
FIFO relaxation (SPFA) is a separate algorithm to recap afterward.

## Functions and storage

- readGraph builds an adjacency matrix using independently allocated MutableList
  rows. graph[a][b] is the cheapest direct edge from a to b, or INF if absent.
  Only a to b is added; parallel edges retain the minimum weight.
- dijkstra computes the answer. dist[j] is the best route cost found so far;
  visited[j] means its shortest distance is finalized. t is the selected node.
- main reads the dimensions, calls these functions, and prints the answer.

Each round selects the unvisited node with minimum distance, finalizes it, and
relaxes its outgoing edges. If the minimum is INF, all remaining nodes are
unreachable and processing stops. The Kotlin version avoids adding INF values
and uses Long instead of the original Int distances.

## Why finalization works

Suppose a shorter path to the selected node t existed. On that path, take the
first unvisited node x. Its predecessor was already finalized and its outgoing
edge relaxed, so dist[x] is at most the cost of the path prefix to x. Because
weights are nonnegative, that prefix costs no more than the proposed shorter
path to t. This contradicts selecting t as the smallest tentative distance.
The source is the initial case with distance zero. Thus every finalized distance
is correct. Unreachable nodes retain INF.

## Complexity and running

Time: O(n² + m), including matrix initialization and input. Space: O(n²).
The sample is custom: 1→3 costs 10, while 1→2→3 costs 2.

```sh
bash recap/graph/shortest-paths/basic-dijkstra/run.sh sample
bash recap/graph/shortest-paths/basic-dijkstra/run.sh stdin < input.txt
bash recap/graph/shortest-paths/basic-dijkstra/run.sh sample list
bash recap/graph/shortest-paths/basic-dijkstra/run.sh stdin list < input.txt
```

Sample output: 2.
