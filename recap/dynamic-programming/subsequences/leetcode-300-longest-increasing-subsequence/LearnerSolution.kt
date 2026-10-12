import kotlin.math.max

class Solution {
    fun lengthOfLIS(nums: IntArray): Int {
        val n = nums.size
        val dp = IntArray(n) { 1 }
        var res = 1
        // dp[i]: longest strictly increasing subsequence length ending at i.
        // Extend a subsequence ending at an earlier, smaller element.
        for (i in 0 until n) {
            for (j in 0 until i) {
                if (nums[i] > nums[j]) {
                    dp[i] = maxOf(dp[i], dp[j] + 1)
                    res = max(dp[i], res)
                }
            }
        }
        return res
    }
}
