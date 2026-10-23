class Solution {
    fun findTheCity(n: Int, edges: Array<IntArray>, distanceThreshold: Int): Int {
        val dist = Array(n) { IntArray(n) { Int.MAX_VALUE } }
        for (edge in edges) {
            val from = edge[0]
            val to = edge[1]
            val weight = edge[2]
            dist[from][to] = weight
            dist[to][from] = weight
        }
        for (i in 0 until n) dist[i][i] = 0
        for (k in 0 until n) {
            for (i in 0 until n) {
                for (j in 0 until n) {
                    if (dist[i][k] != Int.MAX_VALUE && dist[k][j] != Int.MAX_VALUE) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j]
                        }
                    }
                }
            }
        }
        val ans = IntArray(n)
        var minimum = Int.MAX_VALUE
        var res = 0
        for (city in 0 until n) {
            for (next in 0 until n) {
                if (next != city && dist[city][next] <= distanceThreshold) {
                    ans[city]++
                }
            }
            minimum = minOf(ans[city], minimum)
        }
        for (city in 0 until n) {
            if (ans[city] == minimum) res = city
        }
        return res
    }
}
