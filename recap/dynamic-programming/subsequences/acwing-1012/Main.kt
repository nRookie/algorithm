import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)
    val n = input.nextInt()
    val pairs = MutableList(n) {
        val south = input.nextInt()
        val north = input.nextInt()
        Pair(south, north)
    }
    pairs.sortBy { it.first }

    var res = 0
    val dp = IntArray(n)
    for (i in 0 until n) {
        dp[i] = 1
        for (j in 0 until i) {
            if (pairs[i].second > pairs[j].second) {
                dp[i] = maxOf(dp[i], dp[j] + 1)
            }
        }
        res = maxOf(res, dp[i])
    }
    println(res)
}
