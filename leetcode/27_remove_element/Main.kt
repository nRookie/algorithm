private data class TestCase(
    val name: String,
    val nums: IntArray,
    val value: Int,
    val expected: IntArray,
)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(3, 2, 2, 3), 3, intArrayOf(2, 2)),
        TestCase("example 2", intArrayOf(0, 1, 2, 2, 3, 0, 4, 2), 2, intArrayOf(0, 1, 3, 0, 4)),
        TestCase("empty array", intArrayOf(), 0, intArrayOf()),
        TestCase("remove all", intArrayOf(5, 5, 5), 5, intArrayOf()),
        TestCase("remove none", intArrayOf(1, 2, 3), 4, intArrayOf(1, 2, 3)),
        TestCase("single removed", intArrayOf(1), 1, intArrayOf()),
        TestCase("single kept", intArrayOf(1), 2, intArrayOf(1)),
        TestCase("remove zeros", intArrayOf(0, 1, 0, 2, 0), 0, intArrayOf(1, 2)),
    )

    var failures = 0
    for (case in cases) {
        val actual = case.nums.copyOf()
        val k = try {
            Solution().removeElement(actual, case.value)
        } catch (e: NotImplementedError) {
            println("Starter compiled and ran successfully. Implement removeElement in 27.kt, then run again.")
            kotlin.system.exitProcess(1)
        }
        // Order is unrestricted. Only the first k values matter, including duplicates.
        val validCount = k in 0..actual.size && k == case.expected.size
        val passed = validCount && actual.take(k).sorted() == case.expected.sorted()
        if (passed) {
            println("PASS: ${case.name}")
        } else {
            failures++
            println("FAIL: ${case.name}")
            println("  expected k: ${case.expected.size}, values (any order): ${case.expected.contentToString()}")
            println("  actual k: $k, full array: ${actual.contentToString()}")
        }
    }
    println("${cases.size - failures}/${cases.size} tests passed")
    if (failures > 0) kotlin.system.exitProcess(1)
}
