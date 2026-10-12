import kotlin.random.Random

private fun brute(scores: IntArray, ages: IntArray): Int {
    var best = 0
    for (mask in 1 until (1 shl scores.size)) {
        var sum = 0
        var valid = true
        for (i in scores.indices) if (mask and (1 shl i) != 0) {
            sum += scores[i]
            for (j in 0 until i) if (mask and (1 shl j) != 0) {
                if ((ages[i] < ages[j] && scores[i] > scores[j]) ||
                    (ages[j] < ages[i] && scores[j] > scores[i])) valid = false
            }
        }
        if (valid) best = maxOf(best, sum)
    }
    return best
}

fun main() {
    fun verify(scores: IntArray, ages: IntArray, expected: Int) {
        val savedScores = scores.copyOf()
        val savedAges = ages.copyOf()
        val actual = Solution().bestTeamScore(scores, ages)
        check(actual == expected) { "Expected $expected, got $actual" }
        check(scores.contentEquals(savedScores) && ages.contentEquals(savedAges))
    }
    verify(intArrayOf(1,3,5,10,15), intArrayOf(1,2,3,4,5), 34)
    verify(intArrayOf(4,5,6,5), intArrayOf(2,1,2,1), 16)
    verify(intArrayOf(1,2,3,5), intArrayOf(8,9,10,1), 6)
    verify(intArrayOf(5,2), intArrayOf(1,1), 7)
    verify(intArrayOf(5,5), intArrayOf(1,2), 10)
    verify(intArrayOf(8), intArrayOf(2), 8)
    verify(IntArray(1000) { 1_000_000 }, IntArray(1000) { 1 }, 1_000_000_000)
    val random = Random(1626)
    repeat(200) {
        val n = random.nextInt(1, 10)
        val scores = IntArray(n) { random.nextInt(1, 15) }
        val ages = IntArray(n) { random.nextInt(1, 6) }
        verify(scores, ages, brute(scores, ages))
    }
    println("Passed 7 fixed cases and 200 exhaustive comparisons; inputs preserved.")
}
