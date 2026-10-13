fun main() {
    val solution = Solution()
    fun edges(vararg pairs: Pair<Int, Int>) = pairs.map { intArrayOf(it.first, it.second) }.toTypedArray()
    check(solution.validPath(3, edges(0 to 1, 1 to 2, 2 to 0), 0, 2))
    check(!solution.validPath(6, edges(0 to 1, 0 to 2, 3 to 5, 5 to 4, 4 to 3), 0, 5))
    check(solution.validPath(1, emptyArray(), 0, 0))
    check(!solution.validPath(2, emptyArray(), 0, 1))
    check(solution.validPath(3, edges(0 to 1), 2, 2))
    check(!solution.validPath(4, edges(0 to 1, 1 to 2, 2 to 0), 0, 3))
    val chain = Array(199_999) { intArrayOf(it, it + 1) }
    check(solution.validPath(200_000, chain, 0, 199_999))
    println("Passed 7 cases, including a 200,000-node chain.")
}
