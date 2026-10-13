class Solution {
    fun maxEnvelopes(envelopes: Array<IntArray>): Int {
        // Width ascending; height descending for equal widths.
        envelopes.sortWith(compareBy<IntArray> { it[0] }.thenByDescending { it[1] })
        val tails = mutableListOf<Int>()
        for (envelope in envelopes) {
            var l = 0
            var r = tails.size
            val x = envelope[1]
            // Find the first tails[p] >= x for a strictly increasing height LIS.
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
