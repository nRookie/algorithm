import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val m = input.nextInt()
    val graph = MutableList(n + 1) { mutableListOf<Int>() }
    repeat(m) {
        val x = input.nextInt()
        val y = input.nextInt()
        graph[x].add(y)
        graph[y].add(x)
    }

    val dist = MutableList(n + 1) { -1 }
    val count = MutableList(n + 1) { 0 }
    val queue = ArrayDeque<Int>()

    fun bfs() {
        dist[1] = 0
        count[1] = 1
        queue.addFirst(1)
        while (queue.isNotEmpty()) {
            val u = queue.removeLast()
            for (v in graph[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1
                    count[v] = count[u]
                    queue.addFirst(v)
                } else if (dist[v] == dist[u] + 1) {
                    count[v] = (count[v] + count[u]) % 100003
                }
            }
        }
    }

    bfs()
    val output = System.out.bufferedWriter()
    for (u in 1..n) output.write("${count[u]}\n")
    output.flush()
}
