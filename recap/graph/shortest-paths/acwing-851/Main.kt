import java.util.Scanner

data class Edge(val to: Int, val weight: Int)

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val m = input.nextInt()
    val graph = MutableList(n + 1) { mutableListOf<Edge>() }
    repeat(m) {
        val a = input.nextInt()
        val b = input.nextInt()
        val w = input.nextInt()
        graph[a].add(Edge(b, w))
    }

    val dist = IntArray(n + 1) { Int.MAX_VALUE }
    val inQueue = BooleanArray(n + 1)
    val queue = ArrayDeque<Int>()
    dist[1] = 0
    inQueue[1] = true
    queue.add(1)

    while (queue.isNotEmpty()) {
        val currentNode = queue.removeFirst()
        inQueue[currentNode] = false
        for (edge in graph[currentNode]) {
            val next = edge.to
            val weight = edge.weight
            if (dist[next] > dist[currentNode] + weight) {
                dist[next] = dist[currentNode] + weight
                if (!inQueue[next]) {
                    queue.add(next)
                    inQueue[next] = true
                }
            }
        }
    }
    if (dist[n] == Int.MAX_VALUE) println("impossible") else println(dist[n])
}
