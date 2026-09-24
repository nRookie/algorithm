class Solution {
    fun removeElement(nums: IntArray, `val`: Int): Int {
        var left = 0
        var right = 0
        while (right < nums.size) {
            if (nums[right] != `val`) {
                nums[left] = nums[right]
                left++
            }
            right++
        }
        return left
    }
}
