import kotlin.random.Random

private fun baseline(input: Array<IntArray>): Int {
    val sorted = input.sortedBy { it[0] }
    val dp = IntArray(sorted.size) { 1 }
    for (i in sorted.indices) for (j in 0 until i) {
        if (sorted[j][0] < sorted[i][0] && sorted[j][1] < sorted[i][1]) {
            dp[i] = maxOf(dp[i], dp[j] + 1)
        }
    }
    return dp.maxOrNull() ?: 0
}

fun main() {
    fun verify(input: Array<IntArray>, expected: Int) {
        check(Solution().maxEnvelopes(input) == expected)
    }
    verify(arrayOf(intArrayOf(5,4), intArrayOf(6,4), intArrayOf(6,7), intArrayOf(2,3)), 3)
    verify(Array(3) { intArrayOf(1,1) }, 1)
    verify(arrayOf(intArrayOf(2,3), intArrayOf(2,4)), 1)
    verify(arrayOf(intArrayOf(2,4), intArrayOf(3,4)), 1)
    verify(arrayOf(intArrayOf(9,9)), 1)
    verify(Array(100_000) { intArrayOf(it + 1, it + 1) }, 100_000)
    val random = Random(354)
    repeat(200) {
        val input = Array(random.nextInt(1, 30)) {
            intArrayOf(random.nextInt(1, 11), random.nextInt(1, 11))
        }
        val expected = baseline(input)
        verify(input, expected)
    }
    println("Passed 6 fixed cases and 200 comparisons with two-dimensional DP.")
}
