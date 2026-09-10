private data class TestCase(
    val name: String,
    val nums1: IntArray,
    val m: Int,
    val nums2: IntArray,
    val n: Int,
    val expected: IntArray,
)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(1, 2, 3, 0, 0, 0), 3, intArrayOf(2, 5, 6), 3, intArrayOf(1, 2, 2, 3, 5, 6)),
        TestCase("example 2: empty nums2", intArrayOf(1), 1, intArrayOf(), 0, intArrayOf(1)),
        TestCase("example 3: empty nums1", intArrayOf(0), 0, intArrayOf(1), 1, intArrayOf(1)),
        TestCase("nums2 comes first", intArrayOf(4, 5, 6, 0, 0, 0), 3, intArrayOf(1, 2, 3), 3, intArrayOf(1, 2, 3, 4, 5, 6)),
        TestCase("duplicates", intArrayOf(2, 2, 0, 0), 2, intArrayOf(2, 2), 2, intArrayOf(2, 2, 2, 2)),
        TestCase("negative numbers and real zeros", intArrayOf(-3, 0, 0, 0, 0), 3, intArrayOf(-2, 0), 2, intArrayOf(-3, -2, 0, 0, 0)),
    )

    var failures = 0
    for (case in cases) {
        val actual = case.nums1.copyOf()
        try {
            Solution().merge(actual, case.m, case.nums2.copyOf(), case.n)
        } catch (e: NotImplementedError) {
            println("Starter compiled and ran successfully. Implement merge in 88.kt, then run again.")
            kotlin.system.exitProcess(1)
        }
        if (actual.contentEquals(case.expected)) {
            println("PASS: ${case.name}")
        } else {
            failures++
            println("FAIL: ${case.name}")
            println("  expected: ${case.expected.contentToString()}")
            println("  actual:   ${actual.contentToString()}")
        }
    }
    println("${cases.size - failures}/${cases.size} tests passed")
    if (failures > 0) kotlin.system.exitProcess(1)
}
