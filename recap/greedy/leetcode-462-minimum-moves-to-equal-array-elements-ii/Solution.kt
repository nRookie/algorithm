import kotlin.math.abs

class Solution {
    fun minMoves2(nums: IntArray): Int {
        val sorted = nums.sorted()
        val median = sorted[sorted.size / 2].toLong()
        var res = 0L
        for (value in sorted) {
            res += abs(value.toLong() - median)
        }
        // LeetCode 462 guarantees that the answer fits in Int.
        return res.toInt()
    }
}
