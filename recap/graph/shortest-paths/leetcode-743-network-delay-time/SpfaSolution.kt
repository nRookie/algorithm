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
        val queue = ArrayDeque<Int>()
        val inQueue = BooleanArray(n + 1)
        dist[k] = 0
        queue.add(k)
        inQueue[k] = true

        while (queue.isNotEmpty()) {
            val current = queue.removeFirst()
            inQueue[current] = false
            for (edge in graph[current]) {
                val v = edge.to
                val w = edge.weight
                if (dist[v] > dist[current] + w) {
                    dist[v] = dist[current] + w
                    if (!inQueue[v]) {
                        inQueue[v] = true
                        queue.add(v)
                    }
                }
            }
        }
        val answer = dist.drop(1).max()
        return if (answer == Int.MAX_VALUE) -1 else answer
    }
}
