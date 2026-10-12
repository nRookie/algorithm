fun main() {
    fun rows(vararg pairs: Pair<Int, Int>) = pairs.map { intArrayOf(it.first, it.second) }.toTypedArray()
    val cases = listOf(
        rows(1 to 3, 2 to 6, 8 to 10, 15 to 18) to rows(1 to 6, 8 to 10, 15 to 18),
        rows(1 to 4, 4 to 5) to rows(1 to 5),
        rows(4 to 7, 1 to 4) to rows(1 to 7),
        rows(1 to 10, 2 to 3) to rows(1 to 10),
        rows(1 to 2, 1 to 8, 1 to 4) to rows(1 to 8),
        rows(2 to 5, 2 to 5) to rows(2 to 5),
        rows(1 to 1, 1 to 2, 3 to 3) to rows(1 to 2, 3 to 3),
        rows(3 to 4, 1 to 2) to rows(1 to 2, 3 to 4),
        rows(0 to 10000) to rows(0 to 10000),
        rows(8 to 10, 2 to 3, 1 to 6, 6 to 8, 15 to 18) to rows(1 to 10, 15 to 18),
        rows() to rows()
    )
    for ((input, expected) in cases) {
        val original = input.map { it.copyOf() }.toTypedArray()
        val actual = Solution().merge(input)
        check(actual.contentDeepEquals(expected)) {
            "Input ${input.contentDeepToString()}: expected ${expected.contentDeepToString()}, got ${actual.contentDeepToString()}"
        }
        check(input.contentDeepEquals(original)) { "Input was modified" }
    }
    println("Passed ${cases.size} cases and input-preservation checks.")
}
