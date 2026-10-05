class Solution {
    fun reverseWords(s: String): String {
        val result = StringBuilder()
        var right = s.lastIndex

        while (right >= 0) {
            // Skip separators before locating the next word.
            while (right >= 0 && s[right] == ' ') right--
            if (right < 0) break

            val endExclusive = right + 1
            while (right >= 0 && s[right] != ' ') right--
            val start = right + 1

            if (result.isNotEmpty()) result.append(' ')
            // Append the word in its original character order, without a substring.
            result.append(s, start, endExclusive)
        }

        return result.toString()
    }
}
