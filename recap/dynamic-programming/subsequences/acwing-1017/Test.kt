import kotlin.random.Random

private fun baseline(h: List<Int>): Int {
    var best = 0
    for (mask in 1 until (1 shl h.size)) {
        val selected = h.indices.filter { mask and (1 shl it) != 0 }.map { h[it] }
        if (selected.zipWithNext().all { (a, b) -> a > b } ||
            selected.zipWithNext().all { (a, b) -> a < b }) {
            best = maxOf(best, selected.size)
        }
    }
    return best
}

fun main() {
    val cases = listOf(
        listOf(9, 4, 7, 3, 2) to 4,
        listOf(1, 2, 3, 4) to 4,
        listOf(5, 5, 5) to 1,
        listOf(8) to 1,
        listOf(1, 3, 2) to 2
    )
    for ((h, expected) in cases) check(longestGlide(h) == expected)
    val random = Random(1017)
    repeat(200) {
        val h = List(random.nextInt(1, 11)) { random.nextInt(1, 11) }
        check(longestGlide(h) == baseline(h)) { h.toString() }
    }
    println("Passed 5 fixed cases and 200 exhaustive-subsequence comparisons.")
}
