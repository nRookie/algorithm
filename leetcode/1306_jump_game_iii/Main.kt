fun main() {
    data class Case(val arr: IntArray, val start: Int, val expected: Boolean)
    val cases = listOf(
        Case(intArrayOf(4, 2, 3, 0, 3, 1, 2), 5, true),
        Case(intArrayOf(4, 2, 3, 0, 3, 1, 2), 0, true),
        Case(intArrayOf(3, 0, 2, 1, 2), 2, false),
        Case(intArrayOf(0), 0, true),
        Case(intArrayOf(1, 1), 0, false),
        Case(intArrayOf(0, 1), 1, true),
        Case(intArrayOf(2, 0, 2), 0, false),
        Case(IntArray(50_000) { if (it == 49_999) 0 else 1 }, 0, true),
    )
    for ((arr, start, expected) in cases) {
        val original = arr.copyOf()
        val actual = Solution().canReach(arr, start)
        check(actual == expected) {
            "length=${arr.size}, start=$start: expected $expected, got $actual"
        }
        check(arr.contentEquals(original)) { "Input was modified" }
    }
    println("${cases.size}/${cases.size} checks passed, including a 50,000-index path")
}
