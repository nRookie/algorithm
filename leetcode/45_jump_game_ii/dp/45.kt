class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n) { Int.MAX_VALUE }
        dp[0] = 0
        var boundary = 0

        for (current in 0 until n) {
            val start = maxOf(current + 1, boundary + 1)
            val end = minOf(current + nums[current], n - 1)
            for (next in start..end) {
                if (dp[current] != Int.MAX_VALUE) {
                    dp[next] = minOf(dp[current] + 1, dp[next])
                }
            }
            boundary = maxOf(boundary, end)
        }
        return dp[n - 1]
    }
}
