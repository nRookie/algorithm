fun main() {
    fun verify(n: Int, threshold: Int, expected: Int, vararg edges: IntArray) {
        check(Solution().findTheCity(n, arrayOf(*edges), threshold) == expected)
    }
    verify(4, 4, 3, intArrayOf(0,1,3), intArrayOf(1,2,1), intArrayOf(1,3,4), intArrayOf(2,3,1))
    verify(5, 2, 0, intArrayOf(0,1,2), intArrayOf(0,4,8), intArrayOf(1,2,3), intArrayOf(1,4,2), intArrayOf(2,3,1), intArrayOf(3,4,1))
    verify(2, 1, 1, intArrayOf(0,1,1))
    verify(2, 1, 1, intArrayOf(0,1,2))
    verify(4, 10, 3, intArrayOf(0,1,1))
    verify(4, 2, 2, intArrayOf(0,3,1), intArrayOf(3,1,1), intArrayOf(1,2,1))
    println("6 checks passed")
}
