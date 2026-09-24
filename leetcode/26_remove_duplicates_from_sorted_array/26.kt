class Solution {
    fun removeDuplicates(nums: IntArray): Int {
        var left = 0
        var right = 0
        while (right < nums.size) {
            if (nums[right] != nums[left]) {
                left++
                nums[left] = nums[right]
            }
            right++
        }
        return left + 1
    }
}
