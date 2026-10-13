class Solution {
    fun lengthOfLIS(nums: IntArray): Int {
        // tails[p]: smallest ending value found for a subsequence of length p + 1.
        val tails = mutableListOf<Int>()
        // Process the original order and find the first tail >= x.
        for (x in nums) {
            var l = 0
            var r = tails.size
            while (l < r) {
                val mid = l + (r - l) / 2
                if (tails[mid] < x) {
                    l = mid + 1
                } else {
                    r = mid
                }
            }

            if (l == tails.size) {
                tails.add(x)
            } else {
                tails[l] = x
            }
        }

        return tails.size
    }
}
