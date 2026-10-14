fun main() {
    fun checkCase(n: Int, k: Int, expected: Int, vararg edges: IntArray) {
        val actual = Solution().networkDelayTime(arrayOf(*edges), n, k)
        check(actual == expected) { "Expected $expected, got $actual" }
    }
    checkCase(4, 2, 2, intArrayOf(2, 1, 1), intArrayOf(2, 3, 1), intArrayOf(3, 4, 1))
    checkCase(2, 1, 1, intArrayOf(1, 2, 1))
    checkCase(2, 2, -1, intArrayOf(1, 2, 1))
    checkCase(3, 1, -1, intArrayOf(2, 3, 1))
    checkCase(3, 1, 2, intArrayOf(1, 2, 10), intArrayOf(1, 3, 1), intArrayOf(3, 2, 1))
    checkCase(3, 1, 0, intArrayOf(1, 2, 0), intArrayOf(2, 3, 0))
    val chain = Array(99) { intArrayOf(it + 1, it + 2, 100) }
    checkCase(100, 1, 9900, *chain)
    // Additional function-level boundary case outside times.length >= 1.
    checkCase(1, 1, 0)
    println("8 checks passed")
}
