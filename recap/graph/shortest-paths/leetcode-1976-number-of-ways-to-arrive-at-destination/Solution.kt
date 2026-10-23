import java.util.PriorityQueue

const val MOD = 1_000_000_007

class Solution {
    data class Edge(val to: Int, val weight: Int)
    data class State(val node: Int, val distance: Long)

    fun countPaths(n: Int, roads: Array<IntArray>): Int {
        val graph = MutableList(n) { mutableListOf<Edge>() }
        for (road in roads) {
            val u = road[0]
            val v = road[1]
            val w = road[2]
            graph[u].add(Edge(v, w))
            graph[v].add(Edge(u, w))
        }
        val pq = PriorityQueue<State>(compareBy { it.distance })
        val dist = LongArray(n) { Long.MAX_VALUE }
        val cnt = IntArray(n) { 0 }
        dist[0] = 0L
        cnt[0] = 1
        pq.add(State(0, 0L))

        while (pq.isNotEmpty()) {
            val curState = pq.poll()
            val (node, distance) = curState
            if (distance > dist[node]) continue

            for (edge in graph[node]) {
                val v = edge.to
                val w = edge.weight
                val candidate = dist[node] + w

                if (candidate < dist[v]) {
                    dist[v] = candidate
                    cnt[v] = cnt[node]
                    pq.add(State(v, candidate))
                } else if (candidate == dist[v]) {
                    cnt[v] = (cnt[v] + cnt[node]) % MOD
                }
            }
        }
        return cnt[n - 1] % MOD
    }
}
