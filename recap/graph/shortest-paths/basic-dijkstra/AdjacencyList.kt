import java.util.Scanner

const val INF = Long.MAX_VALUE

data class Edge(val to: Int, val weight: Long)

fun readGraph(input: Scanner, n: Int, m: Int): List<List<Edge>> {
    val graph = MutableList(n + 1) { mutableListOf<Edge>() }
    repeat(m) {
        val a = input.nextInt()
        val b = input.nextInt()
        val weight = input.nextLong()
        // Directed edge. Parallel edges can remain in the list.
        graph[a].add(Edge(b, weight))
    }
    return graph
}

fun dijkstra(graph: List<List<Edge>>, n: Int): Long {
    val dist = MutableList(n + 1) { INF }
    val visited = MutableList(n + 1) { false }
    dist[1] = 0L

    repeat(n) {
        var t = -1
        // Same linear selection as the adjacency-matrix version.
        for (j in 1..n) {
            if (!visited[j] && (t == -1 || dist[j] < dist[t])) {
                t = j
            }
        }
        if (t == -1 || dist[t] == INF) {
            return if (dist[n] == INF) -1L else dist[n]
        }
        visited[t] = true

        // Iterate only the outgoing edges that actually exist.
        for (edge in graph[t]) {
            val j = edge.to
            if (!visited[j]) {
                dist[j] = minOf(dist[j], dist[t] + edge.weight)
            }
        }
    }
    return if (dist[n] == INF) -1L else dist[n]
}

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val m = input.nextInt()
    val graph = readGraph(input, n, m)
    println(dijkstra(graph, n))
}
