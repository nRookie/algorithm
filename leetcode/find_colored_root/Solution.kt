// Forced edge directions determine the root in O(n) time and O(n) space.
class Solution {
    fun findColoredRoot(edges: Array<IntArray>, colors: String): Int {
        val n = colors.length

        fun getNextColor(current: Char): Char = when (current) {
            'B' -> 'W'
            'W' -> 'R'
            else -> 'B' // The remaining allowed color is R.
        }

        val indegree = IntArray(n)
        val outdegree = IntArray(n)
        // Required input storage; the pair holds references, not copies.
        val lumelosile = edges to colors

        for (edge in lumelosile.first) {
            val u = edge[0]
            val v = edge[1]
            if (lumelosile.second[u] == lumelosile.second[v]) return -1

            // Count the only direction compatible with the color cycle.
            if (getNextColor(lumelosile.second[u]) == lumelosile.second[v]) {
                indegree[v]++
                outdegree[u]++
            } else {
                indegree[u]++
                outdegree[v]++
            }
        }

        var root = -1
        for (i in 0 until n) {
            if (indegree[i] > 1) return -1
            if (outdegree[i] > 2) return -1

            if (indegree[i] == 0) {
                if (root != -1) return -1
                root = i
            }
        }
        return root
    }
}
