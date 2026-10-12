import kotlin.math.abs
import kotlin.random.Random

fun main() {
    val cases = listOf(
        intArrayOf(1, 2, 3) to 2,
        intArrayOf(1, 10, 2, 9) to 16,
        intArrayOf(6, 2, 9, 1) to 12,
        intArrayOf(7) to 0,
        intArrayOf(3, 3, 3) to 0,
        intArrayOf(-5, -1, 2) to 7,
        intArrayOf(-1_000_000_000, 1_000_000_000) to 2_000_000_000
    )
    fun verify(input: IntArray, expected: Int) {
        val original = input.copyOf()
        check(Solution().minMoves2(input) == expected) { input.contentToString() }
        check(input.contentEquals(original)) { "Input changed" }
    }
    cases.forEach { (input, expected) -> verify(input, expected) }
    val random = Random(462)
    repeat(200) {
        val input = IntArray(random.nextInt(1, 15)) { random.nextInt(-15, 16) }
        val expected = (input.minOrNull()!!..input.maxOrNull()!!).minOf { target ->
            input.sumOf { abs(it - target) }
        }
        verify(input, expected)
    }
    println("Passed 7 fixed cases and 200 exhaustive-baseline comparisons; input preserved.")
}
