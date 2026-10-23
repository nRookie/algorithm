fun main() {
    fun verify(n: Int, roads: Array<IntArray>, expected: Int) {
        val actual = Solution().countPaths(n, roads)
        check(actual == expected) { "Expected $expected, got $actual" }
    }
    verify(7, arrayOf(
        intArrayOf(0,6,7), intArrayOf(0,1,2), intArrayOf(1,2,3),
        intArrayOf(1,3,3), intArrayOf(6,3,3), intArrayOf(3,5,1),
        intArrayOf(6,5,1), intArrayOf(2,5,1), intArrayOf(0,4,5),
        intArrayOf(4,6,2)
    ), 4)
    verify(2, arrayOf(intArrayOf(1,0,10)), 1)
    verify(1, emptyArray(), 1)
    verify(4, arrayOf(intArrayOf(0,3,10), intArrayOf(0,1,1),
        intArrayOf(0,2,1), intArrayOf(1,3,2), intArrayOf(2,3,2)), 2)
    verify(4, Array(3) { intArrayOf(it, it + 1, 1_000_000_000) }, 1)
    // 35 chained diamonds: each has two choices, giving 2^35 shortest routes.
    val roads = mutableListOf<IntArray>()
    var expected = 1L
    repeat(35) { i ->
        val start = 3 * i
        roads.add(intArrayOf(start, start + 1, 1))
        roads.add(intArrayOf(start, start + 2, 1))
        roads.add(intArrayOf(start + 1, start + 3, 1))
        roads.add(intArrayOf(start + 2, start + 3, 1))
        expected = expected * 2 % MOD
    }
    verify(106, roads.toTypedArray(), expected.toInt())
    println("6 checks passed")
}
