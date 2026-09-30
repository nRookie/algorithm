// Alternative for the O(1)-extra-space follow-up.
// To submit this version, rename ReversalSolution to Solution.
class ReversalSolution {
    fun rotate(nums: IntArray, k: Int) {
        val shift = k % nums.size
        if (shift == 0) return

        reverseRange(nums, 0, nums.lastIndex)
        reverseRange(nums, 0, shift - 1)
        reverseRange(nums, shift, nums.lastIndex)
    }

    private fun reverseRange(nums: IntArray, start: Int, end: Int) {
        var left = start
        var right = end
        while (left < right) {
            val temp = nums[left]
            nums[left] = nums[right]
            nums[right] = temp
            left++
            right--
        }
    }
}
