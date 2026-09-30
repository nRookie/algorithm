import kotlin.math.max

class Solution {
    fun maxProfit(prices: IntArray): Int {
        var buy_day = 0
        var sell_day = 1
        var max_profit = 0
        while (sell_day < prices.size) {
            if (prices[sell_day] > prices[buy_day]) {
                max_profit = max(max_profit, prices[sell_day] - prices[buy_day])
            } else {
                buy_day = sell_day
            }
            sell_day++
        }
        return max_profit
    }
}
