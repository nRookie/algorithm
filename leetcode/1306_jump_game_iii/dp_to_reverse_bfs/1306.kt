class Solution {
    fun canReach(arr: IntArray, start: Int): Boolean {
        val n = arr.size
        val predecessors = Array(n) { mutableListOf<Int>() }
        val queue = ArrayDeque<Int>(n)
        val dp = BooleanArray(n)
        for (i in 0 until n) {
            val right = i + arr[i]
            val left = i - arr[i]
            if (right < n) {
                predecessors[right].add(i)
            }
            if (left >= 0) {
                predecessors[left].add(i)
            }
        }

        for (i in 0 until n) {
            if (arr[i] == 0) {
                dp[i] = true
                queue.addFirst(i)
            }
        }
        while (!queue.isEmpty()) {
            val a = queue.removeLast()
            for (b in predecessors[a]) {
                if (dp[b] != true) {
                    dp[b] = true
                    queue.addFirst(b)
                }
            }
        }
        return dp[start]
    }
}
