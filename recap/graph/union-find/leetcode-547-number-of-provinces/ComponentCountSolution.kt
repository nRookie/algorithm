/*
 * Interview explanation
 * I begin with one group per city and merge cities that are directly connected.
 * I use path compression and union by size to keep root searches efficient.
 * Each group represents exactly one province after all connections are processed.
 * I start with n components and subtract one only when two different groups merge.
 * The matrix is symmetric, so I inspect each pair once using j > i.
 * Time: O(n² α(n)) as a standard upper bound; auxiliary space: O(n).
 * α is the inverse Ackermann function; union-find operations are amortized
 * almost constant time. Recursive find uses at most O(log n) stack depth
 * with union by size, within the O(n) total auxiliary-space bound.
 */
class Solution { // LeetCode's required solution container.
    class UnionFind(n: Int) { // Manage groups for nodes 0 through n - 1.
        private val parent = MutableList(n) { it } // Each node initially represents its own group.
        private val size = MutableList(n) { 1 } // Group sizes are meaningful only at roots.
        var components = n // Initially there are n separate groups.
            private set // Allow callers to read the count; only this class can change it.
        fun find(x: Int): Int { // Return the root representing the group containing x.
            if (parent[x] != x) parent[x] = find(parent[x]) // If x is not a root, compress its path by pointing directly to the root.
            return parent[x] // After compression this is the group representative.
        }
        fun merge(a: Int, b: Int) { // Merge entire groups by connecting their roots.
            var rootA = find(a) // Locate a’s group representative, not just its immediate parent.
            var rootB = find(b) // Locate b’s group representative.
            if (rootA == rootB) return // Already one group: do not change sizes or group counts.
            if (size[rootA] < size[rootB]) { // Ensure rootA represents the larger group before attaching rootB.
                val temp = rootA // Preserve the original rootA while swapping.
                rootA = rootB // Use the larger group’s root as rootA.
                rootB = temp // Use the smaller group’s root as rootB.
            }
            parent[rootB] = rootA // Attach the smaller tree under the larger root.
            size[rootA] += size[rootB] // Update the surviving root’s size; rootB’s old size is no longer used.
            components-- // Two different groups have become one: decrease exactly once.
        }
    }
    fun findCircleNum(isConnected: Array<IntArray>): Int { // Return the number of connected groups in the symmetric matrix.
        val n = isConnected.size // There is one city per matrix row.
        val uf = UnionFind(n) // Share one union-find instance across all connections.
        for (i in 0 until n) { // Visit each city; indices start at zero.
            for (j in i + 1 until n) { // Scan only the upper triangle: skip self-edges and symmetric duplicates.
                if (isConnected[i][j] == 1) uf.merge(i, j) // A direct connection joins the two cities’ groups.
            }
        }
        return uf.components // Successful merges have maintained the province count directly.
    }
}
