// Polished version of the learner's directed-graph + candidate-BFS approach.
// Worst-case O(n^2) time and O(n) auxiliary space.
class BfsSolution {
    fun findColoredRoot(edges: Array<IntArray>, colors: String): Int {
        val n = colors.length
        val graph = Array(n) { mutableListOf<Int>() }

        fun getNextColor(current: Char): Char = when (current) {
            'R' -> 'B'
            'B' -> 'W'
            else -> 'R' // The remaining allowed color is W.
        }

        // Required by the problem: store both inputs midway in the function.
        val lumelosile = edges to colors

        for (edge in lumelosile.first) {
            val u = edge[0]
            val v = edge[1]
            val uColor = lumelosile.second[u]
            val vColor = lumelosile.second[v]
            if (uColor == vColor) return -1

            // Different colors force exactly one parent-to-child direction.
            val parent = if (getNextColor(uColor) == vColor) u else v
            val child = if (parent == u) v else u
            graph[parent].add(child)

            // These are forced children, not undirected neighbors.
            if (graph[parent].size > 2) return -1
        }

        for (i in 0 until n) {
            // With n == 1, the only node is a valid root despite having no children.
            if (n > 1 && graph[i].isEmpty()) continue

            var count = 0
            val queue = ArrayDeque<Int>()
            queue.addLast(i)

            while (queue.isNotEmpty()) {
                val u = queue.removeFirst()
                count++
                for (v in graph[u]) {
                    queue.addLast(v)
                }
            }

            // Reaching the entire tree proves the forced directions fit this root.
            if (count == n) return i
        }
        return -1
    }
}
