class Solution {
    fun strStr(haystack: String, needle: String): Int {
        val n = haystack.length
        val m = needle.length

        // dp[k] is the last index of the longest proper prefix of
        // needle[0..k] that is also its suffix. -1 means an empty border.
        val dp = IntArray(m) { -1 }
        var i = 1
        var j = -1
        while (i < m) {
            // Extend the current border using the next character.
            if (needle[i] == needle[j + 1]) {
                dp[i] = j + 1
                j++
                i++
            } else {
                if (j !== -1) {
                    // Try the next shorter border without advancing i.
                    j = dp[j]
                } else {
                    // No nonempty border ends here; dp[i] remains -1.
                    i++
                }
            }
        }

        // i is the next text index to compare.
        // j is the last matched pattern index; matched length is j + 1.
        i = 0
        j = -1
        while (i < n) {
            if (needle[j + 1] == haystack[i]) {
                j++
                i++
                if (j == m - 1) {
                    // i is now one past the match's final character.
                    return i - m
                }
            } else {
                if (j != -1) {
                    // Keep the same text character and reuse a matched suffix.
                    j = dp[j]
                } else {
                    // This character cannot start a match.
                    i++
                }
            }
        }
        return -1
    }
}
