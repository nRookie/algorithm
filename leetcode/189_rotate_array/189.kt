class Solution {
    fun rotate(nums: IntArray, k: Int) {
        val n = nums.size
        val shift = k % n
        if (shift == 0) return

        val original = nums.copyOf()
        for (i in nums.indices) {
            nums[i] = original[(i + n - shift) % n]
        }
    }
}
