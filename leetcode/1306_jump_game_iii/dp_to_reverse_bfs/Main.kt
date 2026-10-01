private fun budgetDp(arr: IntArray, start: Int): Boolean {
    val n = arr.size
    val table = Array(n) { BooleanArray(n) }
    for (i in arr.indices) table[0][i] = arr[i] == 0
    for (k in 1 until n) {
        for (i in arr.indices) {
            val left = i - arr[i]
            val right = i + arr[i]
            table[k][i] = arr[i] == 0 ||
                (left >= 0 && table[k - 1][left]) ||
                (right < n && table[k - 1][right])
        }
    }
    return table[n - 1][start]
}

fun main() {
    data class Case(val arr: IntArray, val start: Int, val expected: Boolean)
    val cases = listOf(
        Case(intArrayOf(4, 2, 3, 0, 3, 1, 2), 5, true),
        Case(intArrayOf(4, 2, 3, 0, 3, 1, 2), 0, true),
        Case(intArrayOf(3, 0, 2, 1, 2), 2, false),
        Case(intArrayOf(0), 0, true),
        Case(intArrayOf(1, 1), 0, false),
        Case(intArrayOf(0, 1), 1, true),
        Case(intArrayOf(2, 0, 2), 0, false),
        Case(IntArray(50_000) { if (it == 49_999) 0 else 1 }, 0, true),
    )
    for ((arr, start, expected) in cases) {
        val original = arr.copyOf()
        check(Solution().canReach(arr, start) == expected)
        check(arr.contentEquals(original))
    }
    println("${cases.size}/${cases.size} example, edge, and long-path checks passed")

    var checked = 0
    for (n in 1..5) {
        var combinations = 1
        repeat(n) { combinations *= n }
        for (encoding in 0 until combinations) {
            var digits = encoding
            val arr = IntArray(n) {
                val value = digits % n
                digits /= n
                value
            }
            for (start in arr.indices) {
                val expected = budgetDp(arr, start)
                check(Solution().canReach(arr, start) == expected) {
                    "${arr.contentToString()}, start=$start, expected=$expected"
                }
                checked++
            }
        }
    }
    println("$checked exhaustive array/start cases matched budget DP")
}
