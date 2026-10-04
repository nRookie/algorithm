class Solution {
    fun calculateMinimumHP(dungeon: Array<IntArray>): Int {
        val m = dungeon.size
        val n = dungeon[0].size
        // Minimum health before applying this cell, to survive to the princess.
        val dp = Array(m + 1) {
            IntArray(n + 1) { Int.MAX_VALUE }
        }

        // Virtual successors of the princess require 1 health after her cell.
        dp[m - 1][n] = 1
        dp[m][n - 1] = 1

        for (i in m - 1 downTo 0) {
            for (j in n - 1 downTo 0) {
                dp[i][j] = maxOf(
                    minOf(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j],
                    1
                )
            }
        }

        return dp[0][0]
    }
}
