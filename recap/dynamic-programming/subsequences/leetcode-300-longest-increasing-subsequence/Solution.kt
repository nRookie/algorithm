class Solution {
    fun lengthOfLIS(nums: IntArray): Int {
        val dp = MutableList(nums.size) { 1 }
        var res = 0
        for (i in nums.indices) {
            for (j in 0 until i) {
                if (nums[j] < nums[i]) {
                    dp[i] = maxOf(dp[i], dp[j] + 1)
                }
            }
            res = maxOf(res, dp[i])
        }
        return res
    }
}
