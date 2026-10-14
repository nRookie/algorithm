import java.util.PriorityQueue

class Solution {
    data class Edge(val to: Int, val weight: Int)
    data class State(val node: Int, val distance: Int)

    fun networkDelayTime(times: Array<IntArray>, n: Int, k: Int): Int {
        val graph = MutableList(n + 1) { mutableListOf<Edge>() }
        for (time in times) {
            val u = time[0]
            val v = time[1]
            val w = time[2]
            graph[u].add(Edge(v, w))
        }
        val dist = IntArray(n + 1) { Int.MAX_VALUE }
        val pq = PriorityQueue<State>(compareBy { it.distance })
        dist[k] = 0
        pq.add(State(k, 0))
        while (pq.isNotEmpty()) {
            val state = pq.poll()
            if (dist[state.node] < state.distance) continue
            for (edge in graph[state.node]) {
                val v = edge.to
                val w = edge.weight
                if (dist[v] > dist[state.node] + w) {
                    dist[v] = dist[state.node] + w
                    pq.add(State(v, dist[v]))
                }
            }
        }
        val answer = dist.drop(1).max()
        return if (answer == Int.MAX_VALUE) -1 else answer
    }
}
