class Solution {
    fun removeDuplicates(nums: IntArray): Int {
        if (nums.size < 2) {
            return nums.size
        }
        var right = 2
        var left = 2
        while (right < nums.size) {
            if (nums[right] != nums[left - 2]) {
                nums[left] = nums[right]
                left++
            }
            right++
        }
        return left
    }
}
