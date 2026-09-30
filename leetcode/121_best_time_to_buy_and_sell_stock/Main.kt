private fun bruteForce(prices: IntArray): Int {
    var best = 0
    for (buy in prices.indices) {
        for (sell in buy + 1 until prices.size) {
            best = maxOf(best, prices[sell] - prices[buy])
        }
    }
    return best
}

fun main() {
    val cases = listOf(
        intArrayOf(7, 1, 5, 3, 6, 4) to 5,
        intArrayOf(7, 6, 4, 3, 1) to 0,
        intArrayOf(5) to 0,
        intArrayOf(2, 2, 2) to 0,
        intArrayOf(1, 2, 3, 4) to 3,
        intArrayOf(2, 10, 1, 3) to 8,
        intArrayOf(3, 3, 5) to 2,
        intArrayOf(5, 4, 1, 6) to 5,
        intArrayOf(0, 5) to 5,
    )
    for ((prices, expected) in cases) {
        val actual = Solution().maxProfit(prices)
        check(actual == expected) {
            "${prices.contentToString()}: expected $expected, got $actual"
        }
    }
    println("${cases.size}/${cases.size} example and edge-case tests passed")

    // Compare against all valid buy/sell pairs, independently of the greedy rule.
    var checked = 0
    for (size in 1..7) {
        var combinations = 1
        repeat(size) { combinations *= 4 }
        for (encoding in 0 until combinations) {
            var digits = encoding
            val prices = IntArray(size) {
                val price = digits % 4
                digits /= 4
                price
            }
            val expected = bruteForce(prices)
            val actual = Solution().maxProfit(prices)
            check(actual == expected) {
                "${prices.contentToString()}: expected $expected, got $actual"
            }
            checked++
        }
    }
    println("$checked exhaustive cases passed (lengths 1..7, prices 0..3)")
}
