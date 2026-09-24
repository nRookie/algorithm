private data class TestCase(val name: String, val nums: IntArray, val expected: Int)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(3, 2, 3), 3),
        TestCase("example 2", intArrayOf(2, 2, 1, 1, 1, 2, 2), 2),
        TestCase("single value", intArrayOf(7), 7),
        TestCase("all equal", intArrayOf(4, 4, 4, 4), 4),
        TestCase("first value is minority", intArrayOf(9, 1, 1), 1),
        TestCase("do not double-count a new candidate", intArrayOf(1, 2, 2), 2),
        TestCase("candidate changes", intArrayOf(1, 2, 3, 2, 2), 2),
        TestCase("zero majority", intArrayOf(0, -1, 0, 2, 0), 0),
        TestCase("negative majority", intArrayOf(-2, 1, -2, 3, -2), -2),
        TestCase("boundary values", intArrayOf(-1000000000, 1000000000, 1000000000), 1000000000),
        TestCase("maximum length", IntArray(50000) { if (it < 24999) 1 else 2 }, 2),
    )
    var failures = 0
    for (case in cases) {
        val actual = Solution().majorityElement(case.nums.copyOf())
        if (actual == case.expected) {
            println("PASS: ${case.name}")
        } else {
            failures++
            println("FAIL: ${case.name}; expected ${case.expected}, got $actual")
        }
    }

    // Independent frequency-count oracle for all arrays of lengths 1..8
    // over {-1, 0, 1}. Only arrays satisfying the majority guarantee are tested.
    var exhaustiveCases = 0
    for (size in 1..8) {
        var combinations = 1
        repeat(size) { combinations *= 3 }
        for (encoding in 0 until combinations) {
            var digits = encoding
            val nums = IntArray(size) {
                val value = digits % 3 - 1
                digits /= 3
                value
            }
            val expected = nums.toList().groupingBy { it }.eachCount()
                .entries.firstOrNull { it.value > size / 2 }?.key ?: continue
            val actual = Solution().majorityElement(nums.copyOf())
            check(actual == expected) {
                "Exhaustive failure: ${nums.contentToString()}, expected $expected, got $actual"
            }
            exhaustiveCases++
        }
    }
    println("${cases.size - failures}/${cases.size} named tests passed")
    println("$exhaustiveCases exhaustive majority cases passed")
    if (failures > 0) kotlin.system.exitProcess(1)
}
