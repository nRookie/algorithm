private data class TestCase(val input: String, val expected: Boolean)

fun main() {
    val cases = listOf(
        TestCase("A man, a plan, a canal: Panama", true),
        TestCase("race a car", false),
        TestCase(" ", true),
        TestCase(".,!?", true),
        TestCase("a", true),
        TestCase("a.", true),
        TestCase("Aa", true),
        TestCase("ab", false),
        TestCase("0P", false),
        TestCase("1aA1", true),
        TestCase(".,a,,A!?", true),
        TestCase("a".repeat(200_000), true),
        TestCase("a".repeat(199_999) + "b", false),
    )
    val baseline = Solution()
    val optimized = ConstantSpaceSolution()
    for ((input, expected) in cases) {
        check(baseline.isPalindrome(input) == expected) { "Baseline failed, length=${input.length}" }
        check(optimized.isPalindrome(input) == expected) { "Optimized failed, length=${input.length}" }
    }
    var checked = 0
    fun verify(input: String, remaining: Int) {
        if (input.isNotEmpty()) {
            val normalized = input.filter { it in 'a'..'z' || it in 'A'..'Z' || it in '0'..'9' }.lowercase()
            val expected = normalized == normalized.reversed()
            check(baseline.isPalindrome(input) == expected) { "Baseline failed: <$input>" }
            check(optimized.isPalindrome(input) == expected) { "Optimized failed: <$input>" }
            checked++
        }
        if (remaining == 0) return
        for (c in charArrayOf('a', 'A', 'b', '0', ' ', '.')) verify(input + c, remaining - 1)
    }
    verify("", 5)
    println("Both implementations passed ${cases.size} targeted cases and $checked exhaustive short cases.")
}
