fun longestGlide(h: List<Int>): Int {
    val n = h.size
    val f = MutableList(n) { 1 }
    val g = MutableList(n) { 1 }
    var res = 0

    // f[i]: longest descending subsequence ending at i, moving right.
    for (i in h.indices) {
        for (j in 0 until i) {
            if (h[j] > h[i]) {
                f[i] = maxOf(f[i], f[j] + 1)
            }
        }
        res = maxOf(res, f[i])
    }

    // g[i]: longest descending subsequence ending at i, moving left.
    for (i in h.indices.reversed()) {
        for (j in n - 1 downTo i + 1) {
            if (h[j] > h[i]) {
                g[i] = maxOf(g[i], g[j] + 1)
            }
        }
        res = maxOf(res, g[i])
    }
    return res
}
