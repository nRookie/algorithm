class Solution {
    fun networkDelayTime(times: Array<IntArray>, n: Int, k: Int): Int {
        val graph = Array(n + 1) { IntArray(n + 1) { Int.MAX_VALUE } }
        for (time in times) {
            val u = time[0]
            val v = time[1]
            val w = time[2]
            graph[u][v] = w
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

            // Do not relax from an unreachable node: infinity + weight overflows.
            if (t == -1 || dist[t] == Int.MAX_VALUE) return -1
            visited[t] = true

            for (j in 1..n) {
                if (!visited[j] && graph[t][j] != Int.MAX_VALUE) {
                    dist[j] = minOf(dist[j], dist[t] + graph[t][j])
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
