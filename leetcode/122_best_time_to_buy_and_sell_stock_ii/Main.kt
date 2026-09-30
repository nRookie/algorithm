// Enumerate legal daily decisions; unfinished holdings cannot be the answer.
private fun bruteForce(prices: IntArray): Int {
    var best = 0
    fun visit(day: Int, holding: Boolean, balance: Int) {
        if (day == prices.size) {
            if (!holding) best = maxOf(best, balance)
            return
        }
        visit(day + 1, holding, balance)
        if (holding) {
            visit(day + 1, false, balance + prices[day])
        } else {
            visit(day + 1, true, balance - prices[day])
        }
    }
    visit(0, false, 0)
    return best
}

fun main() {
    val cases = listOf(
        intArrayOf(7, 1, 5, 3, 6, 4) to 7,
        intArrayOf(1, 2, 3, 4, 5) to 4,
        intArrayOf(7, 6, 4, 3, 1) to 0,
        intArrayOf(5) to 0,
        intArrayOf(2, 2, 2) to 0,
        intArrayOf(0, 5) to 5,
        intArrayOf(2, 10, 1, 3) to 10,
        intArrayOf(0, 10000, 0, 10000) to 20000,
    )
    for ((prices, expected) in cases) {
        val actual = Solution().maxProfit(prices)
        check(actual == expected) {
            "${prices.contentToString()}: expected $expected, got $actual"
        }
    }
    println("${cases.size}/${cases.size} example and edge-case tests passed")

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
