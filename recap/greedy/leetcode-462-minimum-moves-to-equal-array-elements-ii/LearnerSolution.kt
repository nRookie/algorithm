import kotlin.math.abs

class Solution {
    fun minMoves2(nums: IntArray): Int {
        nums.sort()
        val n = nums.size
        val median = nums[n / 2]
        var distance = 0
        for (num in nums) {
            distance += abs(num - median)
        }
        return distance
    }
}
