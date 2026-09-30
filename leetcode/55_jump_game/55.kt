import kotlin.math.max

class Solution {
    fun canJump(nums: IntArray): Boolean {
        var farthest: Int = 0
        val n = nums.size
        for (current in 0..n - 1) {
            if (farthest >= current) {
                farthest = max(farthest, current + nums[current])
            }
        }
        return n - 1 <= farthest
    }
}
