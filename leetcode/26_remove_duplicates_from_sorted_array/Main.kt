private data class TestCase(val name: String, val nums: IntArray, val expected: IntArray)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(1, 1, 2), intArrayOf(1, 2)),
        TestCase("example 2", intArrayOf(0, 0, 1, 1, 1, 2, 2, 3, 3, 4), intArrayOf(0, 1, 2, 3, 4)),
        TestCase("single element", intArrayOf(5), intArrayOf(5)),
        TestCase("all equal", intArrayOf(2, 2, 2, 2), intArrayOf(2)),
        TestCase("all unique", intArrayOf(-2, 0, 3, 5), intArrayOf(-2, 0, 3, 5)),
        TestCase("negative values and zero", intArrayOf(-3, -3, -1, 0, 0), intArrayOf(-3, -1, 0)),
        TestCase("duplicate at end", intArrayOf(1, 2, 3, 3), intArrayOf(1, 2, 3)),
        TestCase("two equal values", intArrayOf(1, 1), intArrayOf(1)),
    )
    var failures = 0
    for (case in cases) {
        val actual = case.nums.copyOf()
        val k = Solution().removeDuplicates(actual)
        // Unlike problem 27, the retained prefix must have the expected order.
        val passed = k in 0..actual.size && k == case.expected.size &&
            actual.take(k) == case.expected.toList()
        if (passed) {
            println("PASS: ${case.name}")
        } else {
            failures++
            println("FAIL: ${case.name}")
            println("  expected k: ${case.expected.size}, prefix: ${case.expected.contentToString()}")
            println("  actual k: $k, full array: ${actual.contentToString()}")
        }
    }
    println("${cases.size - failures}/${cases.size} tests passed")
    if (failures > 0) kotlin.system.exitProcess(1)
}
