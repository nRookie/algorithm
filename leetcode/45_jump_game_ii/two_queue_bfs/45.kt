class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        val current = ArrayDeque<Int>()
        val next = ArrayDeque<Int>()
        current.addFirst(0)
        var jumps = 0
        var boundary = 0

        while (current.isNotEmpty()) {
            while (current.isNotEmpty()) {
                val current_position = current.removeFirst()
                if (current_position == nums.lastIndex) return jumps

                val start = maxOf(current_position + 1, boundary + 1)
                val end = minOf(current_position + nums[current_position], nums.lastIndex)
                for (next_position in start..end) {
                    next.addLast(next_position)
                }
                boundary = maxOf(boundary, end)
            }

            while (next.isNotEmpty()) {
                val next_position = next.removeFirst()
                current.addFirst(next_position)
            }
            jumps++
        }
        return n
    }
}
