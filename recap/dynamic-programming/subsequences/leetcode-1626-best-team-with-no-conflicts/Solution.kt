import kotlin.math.max

class Solution {
    fun bestTeamScore(scores: IntArray, ages: IntArray): Int {
        val players = ages.zip(scores).sortedWith(compareBy({ it.first }, { it.second }))
        val n = players.size
        val dp = IntArray(n)
        var res = 0
        for (i in 0 until n) {
            dp[i] = players[i].second
            for (j in 0 until i) {
                if (players[j].second <= players[i].second) {
                    dp[i] = max(dp[i], dp[j] + players[i].second)
                }
            }
            res = max(dp[i], res)
        }
        return res
    }
}
