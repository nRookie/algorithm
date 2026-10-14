import java.util.Scanner

data class Edge(val to: Int, val weight: Int)

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val m = input.nextInt()
    val source = input.nextInt()
    val target = input.nextInt()
    val graph = MutableList(n + 1) { mutableListOf<Edge>() }

    fun addEdge(a: Int, b: Int, weight: Int) {
        graph[a].add(Edge(b, weight))
        graph[b].add(Edge(a, weight))
    }

    repeat(m) {
        val a = input.nextInt()
        val b = input.nextInt()
        val weight = input.nextInt()
        addEdge(a, b, weight)
    }

    val dist = MutableList(n + 1) { Long.MAX_VALUE }
    val inQueue = MutableList(n + 1) { false }
    val queue = ArrayDeque<Int>()
    dist[source] = 0L
    queue.addFirst(source)
    inQueue[source] = true

    while (queue.isNotEmpty()) {
        val u = queue.removeLast()
        inQueue[u] = false

        for (edge in graph[u]) {
            val v = edge.to
            val candidate = dist[u] + edge.weight
            if (candidate < dist[v]) {
                dist[v] = candidate
                if (!inQueue[v]) {
                    queue.addFirst(v)
                    inQueue[v] = true
                }
            }
        }
    }

    // Local convention for an unreachable target.
    println(if (dist[target] == Long.MAX_VALUE) -1L else dist[target])
}
