class Solution {
    data class Edge(val to: Int, val weight: Int)

    fun networkDelayTime(times: Array<IntArray>, n: Int, k: Int): Int {
        val graph = MutableList(n + 1) { mutableListOf<Edge>() }
        for (time in times) {
            val u = time[0]
            val v = time[1]
            val w = time[2]
            graph[u].add(Edge(v, w))
        }
        val dist = IntArray(n + 1) { Int.MAX_VALUE }
        val visited = MutableList(n + 1) { false }
        dist[k] = 0

        repeat(n) {
            var t = -1
            for (j in 1..n) {
                if (!visited[j] && (t == -1 || dist[j] < dist[t])) {
                    t = j
                }
            }

            // All remaining nodes are unreachable. Never relax from infinity.
            if (t == -1 || dist[t] == Int.MAX_VALUE) return -1
            visited[t] = true
            for (edge in graph[t]) {
                val j = edge.to
                if (!visited[j]) {
                    dist[j] = minOf(dist[j], dist[t] + edge.weight)
                }
            }
        }

        var res = 0
        for (i in 1..n) {
            if (dist[i] == Int.MAX_VALUE) return -1
            res = maxOf(res, dist[i])
        }
        return res
    }
}
