class Solution {
    fun validPath(n: Int, edges: Array<IntArray>, source: Int, destination: Int): Boolean {
        val graph = MutableList(n) { mutableListOf<Int>() }
        for (edge in edges) {
            val x = edge[0]
            val y = edge[1]
            graph[x].add(y)
            graph[y].add(x)
        }

        val queue = ArrayDeque<Int>()
        val visited = BooleanArray(n)
        queue.addFirst(source)
        visited[source] = true
        while (queue.isNotEmpty()) {
            val u = queue.removeLast()
            if (destination == u) return true
            for (v in graph[u]) {
                if (!visited[v]) {
                    visited[v] = true
                    queue.addFirst(v)
                }
            }
        }
        return false
    }
}
