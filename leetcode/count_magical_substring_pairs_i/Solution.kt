/*
 * Interview explanation
 * At a fixed split j and distinct count d, any matching left substring can
 * pair with any matching right substring, so multiply their counts. Compute
 * exact-d counts as atMost(d) minus atMost(d-1), using sliding windows for all
 * endpoints. Reverse the input to reuse ending counts for starting counts.
 * O(26*n) time, O(n + 26) auxiliary space; lowercase letters and n <= 2000.
 */
class Solution {
    fun countMagicalPairs(s: String): Int {
        val n = s.length // Original positions define triplet identity.
        var res = 0L // Use wide arithmetic for products and accumulation.
        var previousLeft = IntArray(n) // No nonempty substring has at most zero letters.
        var previousRight = IntArray(n) // Same base counts in reversed coordinates.
        val mevaltrino = s // Store the input midway, as the statement requires.
        val reversed = mevaltrino.reversed() // Starting substrings become ending substrings.
        for (d in 1..minOf(26, n)) { // Enumerate every possible shared distinct count.
            val currentLeft = atMostEnding(mevaltrino, d) // Counts ending at original indices.
            val currentRight = atMostEnding(reversed, d) // Counts ending at reversed indices.
            for (j in 0 until n - 1) { // Split between original indices j and j + 1.
                val leftExact = currentLeft[j] - previousLeft[j] // Exactly d letters on the left.
                val reverseEnd = n - j - 2 // Original start j + 1 maps to this reversed end.
                val rightExact = currentRight[reverseEnd] - previousRight[reverseEnd] // Exactly d right.
                res += leftExact.toLong() * rightExact // All independent matching choices pair.
            }
            previousLeft = currentLeft // Reuse atMost(d) as the next atMost(d - 1).
            previousRight = currentRight // Preserve the same threshold in reversed coordinates.
        }
        return res.toInt() // At most C(2001, 3) = 1,333,333,000 under the given constraints.
    }

    private fun atMostEnding(s: String, limit: Int): IntArray {
        val counts = IntArray(s.length) // counts[r] counts valid nonempty substrings ending at r.
        val frequency = IntArray(26) // Frequencies allow removal, unlike an OR mask alone.
        var distinct = 0 // Number of positive frequency buckets in the current window.
        var left = 0 // Earliest start whose window has at most limit distinct letters.
        for (right in s.indices) { // Add each character once.
            val added = s[right] - 'a' // Convert the new character to its bucket.
            if (frequency[added] == 0) distinct++ // A newly present letter increases diversity.
            frequency[added]++ // Include the new endpoint in the window.
            while (distinct > limit) { // Remove starts until the window is valid.
                val removed = s[left] - 'a' // Identify the outgoing character.
                frequency[removed]-- // Remove one occurrence.
                if (frequency[removed] == 0) distinct-- // Only the last occurrence removes a letter.
                left++ // Advance monotonically; total shrinking work is linear.
            }
            counts[right] = right - left + 1 // Every start in [left, right] is valid.
        }
        return counts // Per-endpoint counts are necessary for matching the same split.
    }
}
