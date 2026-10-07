// Local checks; submit only 68.kt to the judge.
fun main() {
    data class Case(val words: List<String>, val width: Int, val expected: List<String>)

    val cases = listOf(
        Case(
            listOf("This", "is", "an", "example", "of", "text", "justification."),
            16,
            listOf("This    is    an", "example  of text", "justification.  ")
        ),
        Case(listOf("ab", "cd"), 5, listOf("ab cd")),
        Case(listOf("abcd", "ef"), 4, listOf("abcd", "ef  ")),
        Case(listOf("a", "b", "c", "dddd"), 6, listOf("a  b c", "dddd  ")),
        Case(listOf("a", "b", "cccc"), 4, listOf("a  b", "cccc")),
        Case(listOf("a"), 4, listOf("a   ")),
        Case(listOf("a", "b"), 1, listOf("a", "b"))
    )

    for ((index, case) in cases.withIndex()) {
        val actual = Solution().fullJustify(case.words.toTypedArray(), case.width)
        check(actual == case.expected) { "Case ${index + 1}: $actual != ${case.expected}" }
        check(actual.all { it.length == case.width })
        val original = OriginalSolution().fullJustify(case.words.toTypedArray(), case.width)
        check(original == case.expected) { "Original case ${index + 1} failed: $original" }
    }

    println("Passed ${cases.size} cases for both implementations.")
}
