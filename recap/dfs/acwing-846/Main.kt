import java.io.BufferedReader
import java.util.StringTokenizer
import kotlin.system.exitProcess

data class TreeInput(val n: Int, val graph: List<List<Int>>)

fun readTree(reader: BufferedReader): TreeInput {
    var tokens = StringTokenizer("")
    fun nextInt(): Int {
        while (!tokens.hasMoreTokens()) {
            tokens = StringTokenizer(reader.readLine() ?: error("Unexpected end of input"))
        }
        return tokens.nextToken().toInt()
    }

    val n = nextInt()
    require(n >= 1) { "A tree must have at least one node" }
    val graph = MutableList(n + 1) { mutableListOf<Int>() }
    repeat(n - 1) {
        val a = nextInt()
        val b = nextInt()
        require(a in 1..n && b in 1..n) { "Node labels must be between 1 and n" }
        graph[a].add(b)
        graph[b].add(a)
    }
    return TreeInput(n, graph)
}

fun main() {
    val (n, graph) = readTree(System.`in`.bufferedReader())
    try {
        println(minimumLargestComponent(n, graph))
    } catch (e: NotImplementedError) {
        System.err.println("Starter is ready. Fill in minimumLargestComponent in Solution.kt, then run again.")
        exitProcess(1)
    }
}
