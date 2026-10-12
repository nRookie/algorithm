# Building the graph and understanding adjacency lists

This guide explains the collection-based graph already built in [Main.kt](Main.kt).
The practice algorithm in [Solution.kt](Solution.kt) remains yours to implement.

## What the input describes

```text
5
1 2
1 3
2 4
2 5
```

The first number is the number of nodes. Each remaining pair is an undirected
edge: `1 2` means nodes 1 and 2 are directly connected. It does not say that
node 1 is inherently the parent of node 2.

```text
        1
       / \
      2   3
     / \
    4   5
```

The input is guaranteed to be a tree: connected and without cycles. Such a
structure has n − 1 edges. Merely having n − 1 edges does not prove that an
arbitrary graph is a tree; we also rely on the problem's tree guarantee.

## What an adjacency list stores

> `graph[u]` contains the labels of all nodes directly connected to u.

The outer collection is indexed by node label. Each inner collection stores
that node's neighbors. This representation is called an **adjacency list**;
it does not require using a linked-list data structure.

For the example:

| Node u | graph[u] | Meaning |
| --- | --- | --- |
| 0 | [] | Unused slot |
| 1 | [2, 3] | Node 1 connects directly to 2 and 3 |
| 2 | [1, 4, 5] | Node 2 connects directly to 1, 4, and 5 |
| 3 | [1] | Node 3 connects directly to 1 |
| 4 | [2] | Node 4 connects directly to 2 |
| 5 | [2] | Node 5 connects directly to 2 |

`graph[2][0]` is 1: the first stored neighbor's node label. The second index
is a position inside the neighbor list, not a node label or an edge weight.
A neighbor's position in the list has no special graph meaning.

## Build it with Kotlin collections

```kotlin
val graph = MutableList(n + 1) { mutableListOf<Int>() }
```

- `n + 1` allows node labels 1 through n to be used as indexes directly.
- The initializer runs separately for each position, creating independent lists.
- `graph[0]` is intentionally unused.
- `val` prevents reassigning the variable; it does not prevent mutating the lists.

Do not create one inner mutable list and reuse it for every node: adding a
neighbor would then change every node's apparent neighbors.

For each input edge `(a, b)`:

```kotlin
graph[a].add(b)
graph[b].add(a)
```

The edge is undirected. Both endpoints need to discover the other when DFS
examines their neighbors. These are two stored entries describing one edge.
For a directed edge a → b, only `graph[a].add(b)` would be needed.

Construction in input order:

| Edge read | First update | Second update |
| --- | --- | --- |
| 1 2 | graph[1] = [2] | graph[2] = [1] |
| 1 3 | graph[1] = [2, 3] | graph[3] = [1] |
| 2 4 | graph[2] = [1, 4] | graph[4] = [2] |
| 2 5 | graph[2] = [1, 4, 5] | graph[5] = [2] |

The input reader already implements:

```kotlin
val graph = MutableList(n + 1) { mutableListOf<Int>() }
repeat(n - 1) {
    val a = nextInt()
    val b = nextInt()
    graph[a].add(b)
    graph[b].add(a)
}
```

`nextInt()` is the local token-reading helper in Main.kt. The complete reader
also checks that node labels fall between 1 and n.

The solver accepts `List<List<Int>>`, a read-only interface to this graph.
That lets the solver inspect neighbors without needing mutation operations.
It does not make the underlying lists deeply immutable.

## How DFS uses the graph

To visit u's direct neighbors:

```kotlin
for (v in graph[u]) {
    // v is a neighboring node label.
}
```

If traversal enters node 2 from node 1, its neighbors are `[1, 4, 5]`.
Following 1 immediately would return to the previous node, and unrestricted
recursion would keep walking `1 → 2 → 1 → 2 ...`.

For a tree, remember the parent in the traversal and skip that neighbor.
This is a traversal-only sketch, placed inside a scope containing graph:

```kotlin
fun dfs(u: Int, parent: Int) {
    // Enter node u.
    for (v in graph[u]) {
        if (v == parent) continue
        dfs(v, u)
    }
    // All children of u have now been processed.
}

dfs(1, 0)
```

Zero is a convenient initial parent because there is no real node 0.
Rooting at 1 defines parent/child relationships for this traversal; it does
not change the undirected graph. For a general graph with cycles, skipping
only the parent is insufficient: track visited nodes instead. The original
C++ tree solution uses a visited collection, which is also valid here.

For this exact neighbor order, recursive entry order is `1, 2, 4, 5, 3`;
completion order is `4, 5, 2, 3, 1`. The completion of a child is the point at
which its result is available to the parent. Deep trees can exhaust the JVM
call stack; an explicit DFS stack can use the same adjacency lists.

## How this supports the original problem

The graph tells us who is connected to whom. The DFS state records what we
have learned about those connections.

1. Choose a root for traversal, such as 1.
2. Compute each node's subtree size, including the node itself, after processing
   its children.
3. If node u were removed, each child subtree would become a component. The
   nodes outside u's subtree form another component when nonempty.
4. Find the largest of those component sizes for this candidate u.
5. Minimize that largest size over all candidate nodes.

There is no need to physically remove a node or alter the adjacency lists.
The component sizes let us evaluate the hypothetical removal.

In the example, removing node 2 separates nodes 4 and 5 into singleton
components. The nodes outside node 2's subtree are 1 and 3, forming a component
of size 2. The largest remaining component therefore has size 2.

## Cost and interview wording

For n nodes and e undirected edges, the representation has n lists and 2e
neighbor entries: O(n + e) space. Building it takes O(n + e) amortized time
with these growable lists. Iterating over every adjacency list examines each
edge twice, so a traversal costs O(n + e), assuming each node is processed once.
For a tree, e = n − 1, giving O(n) time and space. An adjacency matrix would
allocate O(n²) entries, which is unnecessary for this sparse tree.

"I represent the tree with an adjacency list. The outer index is the node
label, and each inner list stores its neighbors. Since edges are undirected,
I add both endpoints to each other's list. During DFS I skip the parent edge
so I do not immediately walk backward. Once a node's children are processed,
I can combine their results to compute its subtree size."
