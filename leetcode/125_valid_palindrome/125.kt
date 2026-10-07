class Solution {
    fun isPalindrome(s: String): Boolean {
        // Straightforward method: normalize, then compare left and right.
        val n = s.length
        val sb = StringBuilder(n)
        for (c in s) {
            if (c.isLetterOrDigit()) sb.append(c.lowercaseChar())
        }
        var left = 0
        var right = sb.length - 1
        while (left < right) {
            if (sb[left] != sb[right]) return false
            left++
            right--
        }
        return true
    }
}
