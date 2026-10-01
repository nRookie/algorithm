class Solution {
    fun jump(nums: IntArray): Int {
        val n = nums.size
        // Pair<jumps, current_index>
        val queue = ArrayDeque<Pair<Int, Int>>()
        queue.addFirst(Pair(0, 0))
        var boundary = 0

        while (!queue.isEmpty()) {
            val (jumps, current_position) = queue.removeLast()
            if (current_position == n - 1) return jumps

            val start = maxOf(current_position + 1, boundary + 1)
            val end = minOf(current_position + nums[current_position], n - 1)

            for (next_position in start..end) {
                queue.addFirst(Pair(jumps + 1, next_position))
            }
            boundary = maxOf(boundary, end)
        }
        return n
    }
}
