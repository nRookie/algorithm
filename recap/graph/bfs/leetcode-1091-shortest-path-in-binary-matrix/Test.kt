import kotlin.random.Random

private fun baseline(grid: Array<IntArray>): Int {
    val n = grid.size
    if (grid[0][0] == 1) return -1
    val distance = Array(n) { IntArray(n) { -1 } }
    val queue = ArrayDeque<Pair<Int, Int>>()
    distance[0][0] = 1
    queue.addLast(0 to 0)
    while (queue.isNotEmpty()) {
        val (r, c) = queue.removeFirst()
        if (r == n - 1 && c == n - 1) return distance[r][c]
        for (dr in -1..1) for (dc in -1..1) {
            if (dr == 0 && dc == 0) continue
            val nr = r + dr
            val nc = c + dc
            if (nr in 0 until n && nc in 0 until n &&
                grid[nr][nc] == 0 && distance[nr][nc] == -1) {
                distance[nr][nc] = distance[r][c] + 1
                queue.addLast(nr to nc)
            }
        }
    }
    return -1
}

fun main() {
    fun grid(vararg rows: String) = rows.map { row -> row.map { it - '0' }.toIntArray() }.toTypedArray()
    val cases = listOf(
        grid("01", "10") to 2,
        grid("000", "110", "110") to 4,
        grid("100", "110", "110") to -1,
        grid("0") to 1,
        grid("1") to -1,
        grid("00", "01") to -1,
        grid("000", "111", "000") to -1,
        Array(100) { IntArray(100) } to 100
    )
    fun verify(original: Array<IntArray>, expected: Int) {
        val input = original.map { it.copyOf() }.toTypedArray()
        check(Solution().shortestPathBinaryMatrix(input) == expected)
        for (r in original.indices) for (c in original.indices) {
            if (original[r][c] == 1) check(input[r][c] == 1) { "Wall changed" }
        }
    }
    for ((input, expected) in cases) verify(input, expected)
    val random = Random(1091)
    repeat(200) {
        val n = random.nextInt(1, 9)
        val input = Array(n) { IntArray(n) { random.nextInt(2) } }
        verify(input, baseline(input))
    }
    println("Passed 8 fixed cases and 200 random comparisons; walls preserved.")
}
