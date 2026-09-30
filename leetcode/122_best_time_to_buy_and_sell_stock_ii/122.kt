import kotlin.math.max

class Solution {
    fun maxProfit(prices: IntArray): Int {
        val n = prices.size
        val nonhold_max_profit = IntArray(n + 1) { 0 }
        val hold_max_profit = IntArray(n + 1) { 0 }
        // Before processing any days, holding a stock is impossible.
        hold_max_profit[0] = -10000000
        for (i in 1..n) {
            nonhold_max_profit[i] = max(nonhold_max_profit[i - 1], hold_max_profit[i - 1] + prices[i - 1])
            hold_max_profit[i] = max(hold_max_profit[i - 1], nonhold_max_profit[i - 1] - prices[i - 1])
        }
        return nonhold_max_profit[n]
    }
}
