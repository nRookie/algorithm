private data class TestCase(val name: String, val nums: IntArray, val expected: IntArray)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(1, 1, 1, 2, 2, 3), intArrayOf(1, 1, 2, 2, 3)),
        TestCase("example 2", intArrayOf(0, 0, 1, 1, 1, 1, 2, 3, 3), intArrayOf(0, 0, 1, 1, 2, 3, 3)),
        TestCase("empty input: defensive guard", intArrayOf(), intArrayOf()),
        TestCase("single element", intArrayOf(5), intArrayOf(5)),
        TestCase("two equal elements", intArrayOf(1, 1), intArrayOf(1, 1)),
        TestCase("two distinct elements", intArrayOf(1, 2), intArrayOf(1, 2)),
        TestCase("all equal", intArrayOf(2, 2, 2, 2, 2), intArrayOf(2, 2)),
        TestCase("all unique", intArrayOf(-2, 0, 3, 5), intArrayOf(-2, 0, 3, 5)),
        TestCase("already valid pairs", intArrayOf(1, 1, 2, 2, 3, 3), intArrayOf(1, 1, 2, 2, 3, 3)),
        TestCase("negative values and zero", intArrayOf(-3, -3, -3, -1, 0, 0, 0), intArrayOf(-3, -3, -1, 0, 0)),
        TestCase("long runs", intArrayOf(1, 1, 1, 1, 2, 2, 2, 2), intArrayOf(1, 1, 2, 2)),
    )
    var failures = 0
    for (case in cases) {
        val actual = case.nums.copyOf()
        val k = Solution().removeDuplicates(actual)
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
