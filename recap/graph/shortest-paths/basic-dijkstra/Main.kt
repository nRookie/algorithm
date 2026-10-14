import java.util.Scanner

const val INF = Long.MAX_VALUE

fun readGraph(input: Scanner, n: Int, m: Int): List<List<Long>> {
    val graph = MutableList(n + 1) { MutableList(n + 1) { INF } }
    repeat(m) {
        val a = input.nextInt()
        val b = input.nextInt()
        val weight = input.nextLong()
        graph[a][b] = minOf(graph[a][b], weight)
    }
    return graph
}

fun dijkstra(graph: List<List<Long>>, n: Int): Long {
    val dist = MutableList(n + 1) { INF }
    val visited = MutableList(n + 1) { false }
    dist[1] = 0L

    repeat(n) {
        var t = -1
        // Select the unvisited node with the smallest tentative distance.
        for (j in 1..n) {
            if (!visited[j] && (t == -1 || dist[j] < dist[t])) {
                t = j
            }
        }
        if (t == -1 || dist[t] == INF) {
            return if (dist[n] == INF) -1L else dist[n]
        }
        visited[t] = true

        for (j in 1..n) {
            if (!visited[j] && graph[t][j] != INF) {
                dist[j] = minOf(dist[j], dist[t] + graph[t][j])
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
