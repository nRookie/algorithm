class Solution {
    fun fullJustify(words: Array<String>, maxWidth: Int): List<String> {
        val result = mutableListOf<String>()
        var i = 0

        while (i < words.size) {
            val lineWords = mutableListOf<String>()
            var wordWidth = 0

            // Choose the words before formatting the line.
            while (i < words.size) {
                // The candidate needs one separator per existing word.
                val candidateWidth =
                    wordWidth + words[i].length + lineWords.size

                if (candidateWidth > maxWidth) break

                lineWords.add(words[i])
                wordWidth += words[i].length
                i++
            }

            val isLastLine = i == words.size
            result.add(formatLine(lineWords, wordWidth, maxWidth, isLastLine))
        }

        return result
    }

    private fun formatLine(
        words: List<String>,
        wordWidth: Int,
        maxWidth: Int,
        isLastLine: Boolean
    ): String {
        if (isLastLine || words.size == 1) {
            return words.joinToString(" ").padEnd(maxWidth, ' ')
        }

        val gapCount = words.size - 1
        val totalSpaces = maxWidth - wordWidth
        val spacesPerGap = totalSpaces / gapCount
        val extraSpaces = totalSpaces % gapCount
        val line = StringBuilder(maxWidth)

        for (j in words.indices) {
            line.append(words[j])

            if (j < gapCount) {
                val gapWidth = spacesPerGap + if (j < extraSpaces) 1 else 0
                repeat(gapWidth) {
                    line.append(' ')
                }
            }
        }

        return line.toString()
    }
}
