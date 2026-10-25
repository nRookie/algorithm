# LeetCode 1584 — Min Cost to Connect All Points

## Interview explanation

“I treat each point's index as a graph node and create an edge for every pair,
weighted by Manhattan distance. I sort the edges from cheapest to most expensive.
Using union-find, I select an edge only when its endpoints belong to different
components. This avoids cycles and connects all points with minimum total cost
by Kruskal's algorithm. Path compression and union by size keep component checks
efficient. There are O(n²) candidate edges, so time is O(n² log n) and space is
O(n²).”

[Problem](https://leetcode.com/problems/min-cost-to-connect-all-points/) · Medium.
Every pair of points may be connected. The connection cost is
`abs(xi - xj) + abs(yi - yj)`. Return the minimum total cost to connect every point.

## Reviewed learner implementation

The algorithm is correct. The code below preserves the learner's explicit root
check before merge, Boolean-returning merge, and complete scan of sorted edges.
The only compilation addition is `import kotlin.math.abs`; formatting and
comments were added. The caller does not use merge's Boolean result, which is
harmless. Because the caller already checks the roots, merge could instead
return Unit. Alternatively, the caller could use `if (uf.merge(a, b))`.

```kotlin
/*
 * Interview explanation
 * I build all pairwise Manhattan-distance edges, sort them by cost, and select
 * only edges that connect different union-find groups. Kruskal's safe-edge
 * property makes these choices compatible with a minimum spanning tree.
 * Path compression and union by size keep connectivity checks efficient.
 * Time: O(n² log n). Auxiliary space: O(n²) for edges and the sorted copy.
 */
import kotlin.math.abs // Compute absolute coordinate differences.

class Solution { // LeetCode's required solution container.
    class UnionFind(val n: Int) { // Manage groups of point indices 0..n-1.
        private val parent = MutableList(n) { it } // Each node starts as its own root.
        private val size = MutableList(n) { 1 } // Only root entries hold valid group sizes.

        fun find(x: Int): Int { // Return the representative of x's group.
            if (parent[x] != x) { // A non-root must follow its parent chain.
                parent[x] = find(parent[x]) // Compress the path directly to its root.
            }
            return parent[x] // The root identifies the component.
        }

        fun merge(a: Int, b: Int): Boolean { // Report whether two groups were joined.
            var rootA = find(a) // Find the first group's representative.
            var rootB = find(b) // Find the second group's representative.
            if (rootA == rootB) { // Already one component: no merge is needed.
                return false // No group or size changes occurred.
            }
            if (size[rootA] < size[rootB]) { // Keep the larger group under rootA.
                val temp = rootA // Preserve the old first root for the swap.
                rootA = rootB // Move the larger group's root into rootA.
                rootB = temp // Move the smaller group's root into rootB.
            }
            size[rootA] += size[rootB] // Add both sizes at the surviving root.
            parent[rootB] = rootA // Attach the smaller group's root to the larger one.
            return true // Exactly two components became one.
        }
    }

    data class Edge(val a: Int, val b: Int, val weight: Int) // One undirected candidate edge.

    fun kruskal(n: Int, edges: List<Edge>): Int { // Find the minimum spanning-tree cost.
        val sortedEdges = edges.sortedBy { it.weight } // Sort a copy; List is read-only.
        val uf = UnionFind(n) // Initially, no edges have been selected.
        var cost = 0 // Sum only weights of selected edges.
        var connectCount = 0 // Count successful component-connecting edges.
        for (edge in sortedEdges) { // Consider candidates in nondecreasing weight order.
            val rootA = uf.find(edge.a) // Locate the first endpoint's component.
            val rootB = uf.find(edge.b) // Locate the second endpoint's component.
            if (rootA == rootB) continue // This edge would create a cycle: skip it.
            cost += edge.weight // Select the edge and include its cost.
            uf.merge(rootA, rootB) // Join the components; the prior check guarantees success.
            connectCount += 1 // One more edge belongs to the spanning forest.
        }
        if (connectCount != n - 1) return -1 // General safeguard for a disconnected graph.
        return cost // n-1 acyclic selected edges connect all n nodes.
    }

    fun minCostConnectPoints(points: Array<IntArray>): Int { // LeetCode entry point.
        val n = points.size // Every point becomes one graph node.
        val edges = mutableListOf<Edge>() // Store all candidate edges together for sorting.
        for (i in 0 until n) { // Choose the first point's index.
            for (j in i + 1 until n) { // Include each pair once, excluding self-pairs.
                val weight = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]) // Manhattan cost.
                edges.add(Edge(i, j, weight)) // Store indices as endpoints, not coordinates.
            }
        }
        return kruskal(n, edges) // Choose the cheapest set that connects all points.
    }
}
```

## Solution evolution and optional cleanup

The learner first wrote union-find and a generic Kruskal routine. For this
problem, build a complete undirected graph with n(n-1)/2 edges, then reuse that
routine. Adjacency lists are unnecessary: Kruskal needs global edge order.

The explicit root comparison is valid. Passing roots to merge is also valid,
though merge checks them again. Returning Boolean is optional for this caller.
Stopping once connectCount reaches n-1 avoids scanning remaining candidates;
the saved implementation deliberately preserves the learner's full scan.

## Why it works

Union-find groups are the connected components of the selected edges. Accepting
only edges between different groups preserves an acyclic forest, and each
accepted edge reduces the number of components by one. Thus n-1 accepted edges
connect all n nodes. For n=1, zero edges correctly give cost zero. The complete
graph guarantees connectivity for this problem.

For minimality, maintain that some MST contains all edges already selected.
When accepting edge e, consider the cut separating one endpoint's current
component from the rest. e is a minimum-weight edge across that cut: any cheaper
crossing edge would already have joined these components when considered.
If an MST containing previous choices does not contain e, adding e forms a cycle.
That cycle includes another edge crossing the cut, of weight at least e's.
Replace that edge with e. Connectivity and minimal cost are preserved, and no
previously selected edge crosses this component cut. Therefore the invariant
continues to hold; the final tree is minimum.

## Trace

Points: 0=(0,0), 1=(2,2), 2=(5,2).

| Candidate in sorted order | Decision | Selected cost | Groups |
|---|---|---|---|
| Initial | None | 0 | {0}, {1}, {2} |
| 1—2, weight 3 | Different roots: select | 3 | {0}, {1,2} |
| 0—1, weight 4 | Different roots: select | 7 | {0,1,2} |
| 0—2, weight 7 | Same root: skip | 7 | {0,1,2} |

## Complexity and numeric bounds

With E=n(n-1)/2, generation is O(n²), sorting O(E log E), and union-find work
O(E α(n)) amortized. Total O(n² log n) time and O(n²) auxiliary space, including
the sorted copy. Recursive find adds O(log n) stack depth with union by size.

Coordinates are between -10^6 and 10^6, so each Manhattan edge weight fits Int.
The MST total also fits Int for n<=1000: sort points by x and connect consecutive
points into a spanning path. Its horizontal cost telescopes to at most 2,000,000;
its vertical cost is at most (n-1)*2,000,000. Thus an MST costs at most
2,000,000*n <= 2,000,000,000. Selected costs are nonnegative and never exceed
the final MST cost. Use Long for a generic problem with larger bounds.

Recall: Why are edges stored once? Why does a successful merge avoid a cycle?
Why is avoiding cycles alone insufficient to prove minimum total weight?

Validation: the exact Kotlin block above was extracted and compiled locally.
Four checks passed: both official examples, a single point, and opposite
coordinate extremes. No online-judge submission was performed.
