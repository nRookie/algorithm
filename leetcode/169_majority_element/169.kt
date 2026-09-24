class Solution {
    fun majorityElement(nums: IntArray): Int {
        var survivor = 0
        var count = 0
        for (x in nums) {
            if (count == 0) {
                survivor = x
            }
            count += if (x == survivor) 1 else -1
        }
        return survivor
    }
}
