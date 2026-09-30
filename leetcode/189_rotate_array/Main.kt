private data class TestCase(val name: String, val nums: IntArray, val k: Int, val expected: IntArray)

fun main() {
    val cases = listOf(
        TestCase("example 1", intArrayOf(1, 2, 3, 4, 5, 6, 7), 3, intArrayOf(5, 6, 7, 1, 2, 3, 4)),
        TestCase("example 2", intArrayOf(-1, -100, 3, 99), 2, intArrayOf(3, 99, -1, -100)),
        TestCase("zero steps", intArrayOf(1, 2, 3), 0, intArrayOf(1, 2, 3)),
        TestCase("full rotation", intArrayOf(1, 2, 3), 3, intArrayOf(1, 2, 3)),
        TestCase("k exceeds length", intArrayOf(1, 2, 3), 5, intArrayOf(2, 3, 1)),
        TestCase("one value", intArrayOf(9), 100000, intArrayOf(9)),
        TestCase("one step", intArrayOf(1, 2, 3, 4), 1, intArrayOf(4, 1, 2, 3)),
        TestCase("length minus one", intArrayOf(1, 2, 3, 4), 3, intArrayOf(2, 3, 4, 1)),
        TestCase("duplicates", intArrayOf(1, 1, 2, 2), 1, intArrayOf(2, 1, 1, 2)),
        TestCase("three separate cycles", intArrayOf(1, 2, 3, 4, 5, 6), 3, intArrayOf(4, 5, 6, 1, 2, 3)),
        TestCase("all equal: stop by index, not value", intArrayOf(7, 7, 7, 7, 7, 7), 2, intArrayOf(7, 7, 7, 7, 7, 7)),
        TestCase("integer boundaries", intArrayOf(Int.MIN_VALUE, 0, Int.MAX_VALUE), 1, intArrayOf(Int.MAX_VALUE, Int.MIN_VALUE, 0)),
    )
    val implementations: List<Pair<String, (IntArray, Int) -> Unit>> = listOf(
        "copy" to { nums, k -> Solution().rotate(nums, k) },
        "reversal" to { nums, k -> ReversalSolution().rotate(nums, k) },
        "cyclic" to { nums, k -> CyclicSolution().rotate(nums, k) },
    )
    for ((name, rotate) in implementations) {
        for (case in cases) {
            val actual = case.nums.copyOf()
            rotate(actual, case.k)
            check(actual.contentEquals(case.expected)) {
                "$name / ${case.name}: expected ${case.expected.contentToString()}, got ${actual.contentToString()}"
            }
        }
        // Independent oracle: physically move the last value to the front k times.
        var checked = 0
        for (size in 1..20) {
            for (k in 0..(2 * size + 1)) {
                val original = IntArray(size) { it - size / 2 }
                val expected = original.toMutableList()
                repeat(k) { expected.add(0, expected.removeAt(expected.lastIndex)) }
                val actual = original.copyOf()
                rotate(actual, k)
                check(actual.toList() == expected) { "$name: failed size=$size, k=$k" }
                checked++
            }
        }
        val large = IntArray(100000) { it }
        rotate(large, 99999)
        check(large.indices.all { large[it] == if (it == large.lastIndex) 0 else it + 1 })
        println("PASS: $name — ${cases.size} named cases, $checked generated cases, maximum-size case")
    }
}
