class Solution {
    fun canCompleteCircuit(gas: IntArray, cost: IntArray): Int {
        var total = 0
        val n = gas.size
        var leftOver = 0
        val change = IntArray(n) { 0 }
        for (i in cost.indices) {
            change[i] = gas[i] - cost[i]
        }

        var start = 0
        for (i in 0 until n) {
            total += change[i]
            leftOver += change[i]
            if (leftOver < 0) {
                start = i + 1
                leftOver = 0
            }
        }

        if (total < 0) {
            return -1
        } else {
            return start
        }
    }
}
