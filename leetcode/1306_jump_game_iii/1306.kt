class Solution {
    fun canReach(arr: IntArray, start: Int): Boolean {
        val n = arr.size
        val visited = BooleanArray(n)
        val stack = ArrayDeque<Int>()
        stack.addLast(start)
        while (!stack.isEmpty()) {
            val current = stack.removeLast()
            if (current >= n || current < 0) continue
            if (!visited[current]) {
                visited[current] = true
                if (arr[current] == 0) {
                    return true
                }
                stack.addLast(current + arr[current])
                stack.addLast(current - arr[current])
            }
        }
        return false
    }
}
