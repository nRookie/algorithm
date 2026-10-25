import kotlin.random.Random

private fun bruteForce(s: String): Int {
    var count = 0
    for (i in s.indices) {
        for (j in i until s.lastIndex) {
            val left = s.substring(i, j + 1).toSet().size
            for (k in j + 1 until s.length) {
                if (left == s.substring(j + 1, k + 1).toSet().size) count++
            }
        }
    }
    return count
}

fun main() {
    val solution = Solution()
    var checked = 0
    fun verify(s: String, expected: Int = bruteForce(s)) {
        val actual = solution.countMagicalPairs(s)
        check(actual == expected) { "Input=$s expected=$expected actual=$actual" }
        checked++
    }
    verify("aba", 2)
    verify("kkk", 4)
    verify("abcac", 7)
    verify("aa", 1)
    verify("ab", 1)
    verify("kkkk", 10)
    verify("abcdefghijklmnopqrstuvwxyz")
    for (length in 2..7) {
        var combinations = 1
        repeat(length) { combinations *= 3 }
        for (encoded in 0 until combinations) {
            var value = encoded
            val chars = CharArray(length) {
                val c = ('a'.code + value % 3).toChar()
                value /= 3
                c
            }
            verify(String(chars))
        }
    }
    val random = Random(42)
    repeat(200) {
        verify(String(CharArray(random.nextInt(2, 31)) { ('a'.code + random.nextInt(26)).toChar() }))
    }
    val n = 2000
    verify("k".repeat(n), ((n + 1L) * n * (n - 1) / 6).toInt())
    println("PASS: $checked cases (examples, exhaustive short strings, random inputs, n=2000 maximum answer)")
}
