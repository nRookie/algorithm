/*
 * Interview explanation
 * Fix the boundary j between adjacent substrings. Group all starts on the left
 * by distinct-letter count, then extend the right substring and add the size
 * of its matching left group. Every triplet has one boundary and is counted
 * once. O(n^2) time and O(26) auxiliary space for lowercase English letters.
 */
class Solution {
    fun countMagicalPairs(s: String): Int {
        val n = s.length // Both substrings must be nonempty.
        var res = 0 // The answer fits Int for n <= 2000.
        val leftCounts = IntArray(27) // Index d counts left substrings with d letters.
        val mevaltrino = s // Store the input midway, as required.
        for (j in 0 until n - 1) { // Each pair has exactly one separating boundary.
            leftCounts.fill(0) // Groups belong only to this boundary.
            var leftMask = 0 // Start with no characters on the left.
            for (i in j downTo 0) { // Enumerate every left start exactly once.
                leftMask = leftMask or (1 shl (mevaltrino[i] - 'a')) // Extend leftward.
                leftCounts[Integer.bitCount(leftMask)]++ // Group by the required property.
            }
            var rightMask = 0 // Start with no characters on the right.
            for (k in j + 1 until n) { // Enumerate every right end exactly once.
                rightMask = rightMask or (1 shl (mevaltrino[k] - 'a')) // Extend rightward.
                res += leftCounts[Integer.bitCount(rightMask)] // Pair with all matching starts.
            }
        }
        return res // Each choice of (i, j, k) contributes once.
    }
}
