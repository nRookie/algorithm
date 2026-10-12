fun main() {
    val cases = listOf(
        intArrayOf(1, 3, 1) to 0,
        intArrayOf(2, 1, 1, 5, 6, 2, 3, 1) to 3,
        intArrayOf(1, 2, 3, 2, 1) to 0,
        intArrayOf(1, 2, 2, 1) to 1,
        intArrayOf(1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 9) to 8,
        intArrayOf(9, 8, 7, 6, 5, 4, 3, 2, 1, 5, 4, 3, 2, 1) to 8
    )
    for ((input, expected) in cases) {
        val original = input.copyOf()
        val actual = Solution().minimumMountainRemovals(input)
        check(actual == expected) { "${input.contentToString()}: expected $expected, got $actual" }
        check(input.contentEquals(original)) { "Input changed" }
    }
    println("Passed ${cases.size} cases and input-preservation checks.")
}
