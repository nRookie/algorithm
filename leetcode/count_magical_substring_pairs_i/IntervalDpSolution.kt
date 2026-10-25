/*
 * Interview explanation
 * Precompute each interval's letter set as a 26-bit mask. For a fixed left
 * endpoint, equal-count splits form a contiguous block. Track its first >=
 * and first > boundaries as the right endpoint grows; neither moves backward.
 * Count the block's length, not just whether it exists. O(n^2) time and space.
 */
class Solution {
    fun countMagicalPairs(s: String): Int {
        val n = s.length // The supplied constraints are 2 <= n <= 2000.
        var res = 0 // The maximum answer is 1,333,333,000, which fits Int.
        val dp = Array(n) { IntArray(n) } // dp[l][r] stores letters, not their count.
        for (i in s.indices) { // Initialize all single-character intervals.
            dp[i][i] = 1 shl (s[i] - 'a') // Set this character's bit.
        }
        for (len in 2..n) { // Dependencies have smaller lengths.
            for (l in 0..(n - len)) { // Keep the entire interval in bounds.
                val r = l + len - 1 // Inclusive right endpoint.
                val newLetter = 1 shl (s[r] - 'a') // Encode the appended letter.
                dp[l][r] = dp[l][r - 1] or newLetter // Union preserves duplicates once.
            }
        }
        val mevaltrino = s // Store the input midway, as the statement requires.
        for (l in 0 until mevaltrino.length - 1) { // Leave room for a right substring.
            var lower = l // First split with left count >= right count.
            var upper = l // First split with left count > right count.
            for (r in l + 1 until n) { // Reuse both boundaries as r grows.
                while (lower < r && // r is an exclusive sentinel, not a legal split.
                    Integer.bitCount(dp[l][lower]) < Integer.bitCount(dp[lower + 1][r])
                ) {
                    lower++ // Skip strictly smaller left counts.
                }
                while (upper < r && // Short-circuiting prevents invalid array access.
                    Integer.bitCount(dp[l][upper]) <= Integer.bitCount(dp[upper + 1][r])
                ) {
                    upper++ // Skip smaller AND equal left counts.
                }
                res += upper - lower // Every split in [lower, upper) is one triplet.
            }
        }
        return res // Count index triplets, including equal text at different positions.
    }
}
