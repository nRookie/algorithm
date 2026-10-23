// Original executable logic, with formatting normalized and class renamed
// so it can compile alongside Solution.kt. See EXPLANATION.md for limitations.
class OriginalSolution {
    fun findColoredRoot(edges: Array<IntArray>, colors: String): Int {
        var n = 0
        for (edge in edges) {
            val u = edge[0]
            val v = edge[1]
            n = maxOf(n, u)
            n = maxOf(n, v)
        }
        val graph = Array<MutableList<Int>>(n + 1) { mutableListOf<Int>() }

        fun getNextColor(current: Char): Char {
            return when (current) {
                'B' -> 'W'
                'W' -> 'R'
                else -> 'B'
            }
        }

        for (edge in edges) {
            val u = edge[0]
            val v = edge[1]
            if (colors[u] == colors[v]) return -1
            if (getNextColor(colors[u]) == colors[v]) graph[u].add(v)
            if (graph[u].size > 3) return -1
            if (getNextColor(colors[v]) == colors[u]) graph[v].add(u)
            if (graph[v].size > 3) return -1
        }

        for (i in 0..n) {
            if (graph[i].size == 0) continue
            var count = 0
            val queue = ArrayDeque<Pair<Int, Int>>()
            queue.addFirst(i to -1)
            var result = true
            while (!queue.isEmpty()) {
                val (u, parent) = queue.removeLast()
                count++
                var childCount = 0
                val nextColor = getNextColor(colors[u])
                for (v in graph[u]) {
                    if (v == parent) continue
                    if (nextColor != colors[v]) {
                        result = false
                        break
                    }
                    if (childCount == 2) {
                        result = false
                        break
                    }
                    childCount++
                    queue.addFirst(v to u)
                }
            }
            if (result == true && count == n + 1) return i
        }
        return -1
    }
}
