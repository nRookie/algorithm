class NumMatrix(matrix: Array<IntArray>) {
    private val n = matrix.size
    private val m = matrix[0].size
    // pre[r][c] covers the first r rows and first c columns.
    private val pre = MutableList(n + 1) { MutableList(m + 1) { 0 } }

    init {
        for (i in 1..n) {
            for (j in 1..m) {
                pre[i][j] = pre[i - 1][j] + pre[i][j - 1] -
                    pre[i - 1][j - 1] + matrix[i - 1][j - 1]
            }
        }
    }

    // LeetCode coordinates are zero-based and include both endpoints.
    fun sumRegion(row1: Int, col1: Int, row2: Int, col2: Int): Int {
        return pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] -
            pre[row2 + 1][col1] + pre[row1][col1]
    }
}
