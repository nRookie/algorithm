// To submit this alternative to LeetCode, rename CyclicSolution to Solution.
class CyclicSolution {
    fun rotate(nums: IntArray, k: Int) {
        val n = nums.size
        val shift = k % n
        if (shift == 0) return

        var moved = 0
        var start = 0
        while (moved < n) {
            var current = start
            var carried = nums[current]
            do {
                val next = (current + shift) % n
                val displaced = nums[next]
                nums[next] = carried
                carried = displaced
                current = next
                moved++
            } while (current != start)
            start++
        }
    }
}
