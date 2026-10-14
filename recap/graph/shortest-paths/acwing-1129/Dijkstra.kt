import java.util.PriorityQueue
import java.util.Scanner

data class Edge(val to: Int, val weight: Int)
data class State(val node: Int, val distance: Long)

fun addEdge(graph: MutableList<MutableList<Edge>>, a: Int, b: Int, weight: Int) {
    graph[a].add(Edge(b, weight))
    graph[b].add(Edge(a, weight))
}

fun readGraph(input: Scanner, n: Int, m: Int): MutableList<MutableList<Edge>> {
    val graph = MutableList(n + 1) { mutableListOf<Edge>() }
    repeat(m) {
        val a = input.nextInt()
        val b = input.nextInt()
        val weight = input.nextInt()
        require(weight >= 0) { "Dijkstra requires nonnegative edge weights" }
        addEdge(graph, a, b, weight)
    }
    return graph
}

// Assumes nonnegative edge weights. Returns distances from source to every node.
fun dijkstra(graph: List<List<Edge>>, source: Int): List<Long> {
    val dist = MutableList(graph.size) { Long.MAX_VALUE }
    val queue = PriorityQueue<State>(compareBy { it.distance })
    dist[source] = 0L
    queue.add(State(source, 0L))

    while (queue.isNotEmpty()) {
        val current = queue.poll()
        val u = current.node

        // A cheaper entry was inserted after this one: skip the outdated entry.
        if (current.distance != dist[u]) continue

        for (edge in graph[u]) {
            val v = edge.to
            val candidate = dist[u] + edge.weight
            if (candidate < dist[v]) {
                dist[v] = candidate
                queue.add(State(v, candidate))
            }
        }
    }
    return dist
}

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val m = input.nextInt()
    val source = input.nextInt()
    val target = input.nextInt()
    val graph = readGraph(input, n, m)
    val dist = dijkstra(graph, source)
    // Local convention for an unreachable target.
    println(if (dist[target] == Long.MAX_VALUE) -1L else dist[target])
}
