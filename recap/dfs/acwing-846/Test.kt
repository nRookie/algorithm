import kotlin.system.exitProcess

fun main() {
    data class Case(val name: String, val input: String, val expected: Int)
    val cases = listOf(
        Case("Single node", "1", 0),
        Case("Two nodes", "2\n1 2", 1),
        Case("Discussion example", "5\n1 2\n1 3\n2 4\n2 5", 2),
        Case("Six-node chain", "6\n1 2\n2 3\n3 4\n4 5\n5 6", 3),
        Case("Six-node star", "6\n1 2\n1 3\n1 4\n1 5\n1 6", 1),
        Case("Balanced seven-node tree", "7\n1 2\n1 3\n2 4\n2 5\n3 6\n3 7", 3),
        Case("Star centered away from node 1", "5\n4 1\n4 2\n4 3\n4 5", 1)
    )
    var passed = 0
    for (case in cases) {
        val (n, graph) = readTree(case.input.reader().buffered())
        val actual = try {
            minimumLargestComponent(n, graph)
        } catch (e: NotImplementedError) {
            println("NOT IMPLEMENTED: fill in minimumLargestComponent in Solution.kt.")
            println("${cases.size} local cases are ready; no solution results checked yet.")
            exitProcess(1)
        }
        if (actual == case.expected) {
            passed++
            println("PASS: ${case.name}")
        } else {
            println("FAIL: ${case.name}: expected ${case.expected}, got $actual")
        }
    }
    println("$passed/${cases.size} cases passed.")
    if (passed != cases.size) exitProcess(1)
}
