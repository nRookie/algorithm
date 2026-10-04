class Solution {
    fun canCompleteCircuit(gas: IntArray, cost: IntArray): Int {
        val n = gas.size
        // dp[k][i]: minimum gas needed before collecting at station i
        // to complete exactly k clockwise trips.
        val dp = Array(n + 1) { IntArray(n) }

        // dp[0][i] = 0: no gas is needed to make zero trips.
        for (k in 1..n) {
            for (i in 0 until n) {
                val next = (i + 1) % n
                dp[k][i] = maxOf(
                    0,
                    cost[i] - gas[i] + dp[k - 1][next]
                )
            }
        }

        for (i in 0 until n) {
            if (dp[n][i] == 0) return i
        }
        return -1
    }
}
