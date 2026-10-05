private data class TestCase(val name: String, val input: String, val expected: String)

fun main() {
    val cases = listOf(
        TestCase("ordinary sentence", "the sky is blue", "blue is sky the"),
        TestCase("outer spaces", "  hello world  ", "world hello"),
        TestCase("repeated separators", "a good   example", "example good a"),
        TestCase("single character", "x", "x"),
        TestCase("single padded word", "   Kotlin   ", "Kotlin"),
        TestCase("two words", "ab cd", "cd ab"),
        TestCase("digits and case", "  A1   b22 C3  ", "C3 b22 A1"),
        TestCase("maximum length word", "a".repeat(10_000), "a".repeat(10_000)),
        TestCase("many words", "a ".repeat(4_999) + "b ", "b" + " a".repeat(4_999)),
    )
    val solution = Solution()
    for (case in cases) {
        val actual = solution.reverseWords(case.input)
        check(actual == case.expected) { "FAIL: ${case.name}: expected <${case.expected}>, got <$actual>" }
        println("PASS: ${case.name}")
    }

    // Exhaustively compare short valid inputs against a separate split/reverse oracle.
    var exhaustiveCases = 0
    fun verify(prefix: String, remaining: Int) {
        if (prefix.any { it != ' ' }) {
            val expected = prefix.split(' ').filter { it.isNotEmpty() }.reversed().joinToString(" ")
            check(solution.reverseWords(prefix) == expected) { "FAIL: exhaustive input <$prefix>" }
            exhaustiveCases++
        }
        if (remaining == 0) return
        for (character in charArrayOf('a', 'b', ' ')) verify(prefix + character, remaining - 1)
    }
    verify("", 7)
    println("${cases.size} targeted tests and $exhaustiveCases exhaustive cases passed")
}
