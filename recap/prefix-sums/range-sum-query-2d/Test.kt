import kotlin.random.Random

fun main() {
    var checked = 0
    fun verify(a: List<List<Int>>) {
        val matrix = a.map { it.toIntArray() }.toTypedArray()
        val sums = NumMatrix(matrix)
        for (row1 in a.indices) for (row2 in row1 until a.size) {
            for (col1 in a[0].indices) for (col2 in col1 until a[0].size) {
                var expected = 0
                for (i in row1..row2) for (j in col1..col2) expected += a[i][j]
                val actual = sums.sumRegion(row1, col1, row2, col2)
                check(actual == expected) { "$a: ($row1,$col1)..($row2,$col2): $actual != $expected" }
                checked++
            }
        }
        check(matrix.map { it.toList() } == a) { "Input was modified" }
    }
    verify(listOf(listOf(1, 2, 3), listOf(4, 5, 6), listOf(7, 8, 9)))
    verify(listOf(listOf(-7)))
    verify(listOf(listOf(0, -2, 5)))
    verify(listOf(listOf(3), listOf(-4), listOf(0)))
    verify(listOf(listOf(10_000, 10_000)))
    val random = Random(796)
    repeat(100) {
        val rows = random.nextInt(1, 6)
        val cols = random.nextInt(1, 6)
        verify(List(rows) { List(cols) { random.nextInt(-20, 21) } })
    }
    val example = NumMatrix(arrayOf(
        intArrayOf(3, 0, 1, 4, 2), intArrayOf(5, 6, 3, 2, 1),
        intArrayOf(1, 2, 0, 1, 5), intArrayOf(4, 1, 0, 1, 7),
        intArrayOf(1, 0, 3, 0, 5)
    ))
    check(example.sumRegion(2, 1, 4, 3) == 8)
    check(example.sumRegion(1, 1, 2, 2) == 11)
    check(example.sumRegion(1, 2, 2, 4) == 12)
    val maximum = NumMatrix(Array(200) { IntArray(200) { 10_000 } })
    check(maximum.sumRegion(0, 0, 199, 199) == 400_000_000)
    val minimum = NumMatrix(Array(200) { IntArray(200) { -10_000 } })
    check(minimum.sumRegion(0, 0, 199, 199) == -400_000_000)
    println("Passed $checked rectangle comparisons, 3 official example queries, and 2 maximum-size cases.")
}
