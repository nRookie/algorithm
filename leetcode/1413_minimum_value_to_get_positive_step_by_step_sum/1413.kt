class Solution {
    fun minStartValue(nums: IntArray): Int {
        val n = nums.size
        var sum = 0
        var min_x = 0
        for (i in 0 until n) {
            sum += nums[i]
            min_x = minOf(sum, min_x)
        }
        return 1 - min_x
    }
}
