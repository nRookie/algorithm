class Solution {
    fun merge(intervals: Array<IntArray>): Array<IntArray> {
        if (intervals.isEmpty()) return emptyArray()

        val sorted = intervals.sortedBy { it[0] }
        val res = mutableListOf<IntArray>()
        var start = sorted[0][0]
        var end = sorted[0][1]

        for (i in 1 until sorted.size) {
            val left = sorted[i][0]
            val right = sorted[i][1]
            if (left <= end) {
                end = maxOf(end, right)
            } else {
                res.add(intArrayOf(start, end))
                start = left
                end = right
            }
        }

        res.add(intArrayOf(start, end))
        return res.toTypedArray()
    }
}
