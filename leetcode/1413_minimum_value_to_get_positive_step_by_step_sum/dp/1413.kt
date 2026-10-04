class Solution {
    fun minStartValue(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n + 1)

        // After processing everything, the value must still be at least 1.
        dp[n] = 1

        for (i in n - 1 downTo 0) {
            dp[i] = maxOf(1, dp[i + 1] - nums[i])
        }

        return dp[0]
    }
}
