class Solution {
    fun minimumMountainRemovals(h: IntArray): Int {
        val n = h.size
        val f = IntArray(n) { 1 } // Increasing subsequence length ending at i.
        val g = IntArray(n) { 1 } // Decreasing subsequence length starting at i.

        for (i in 0 until n) {
            for (j in 0 until i) {
                if (h[i] > h[j]) f[i] = maxOf(f[i], f[j] + 1)
            }
        }

        for (i in n - 1 downTo 0) {
            for (j in n - 1 downTo i + 1) {
                if (h[i] > h[j]) g[i] = maxOf(g[i], g[j] + 1)
            }
        }

        var answer = 0
        for (i in 0 until n) {
            if (f[i] > 1 && g[i] > 1) {
                answer = maxOf(answer, f[i] + g[i] - 1)
            }
        }

        return n - answer
    }
}
