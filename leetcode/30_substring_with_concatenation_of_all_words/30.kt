class Solution {
    fun findSubstring(s: String, words: Array<String>): List<Int> {
        val step = words[0].length
        val wordCount = words.size
        val n = s.length
        val answer = mutableListOf<Int>()

        if (wordCount * step > n) return answer

        // Required frequency of each word, including duplicate entries.
        val wordMap = HashMap<String, Int>()
        for (word in words) {
            wordMap[word] = wordMap.getOrDefault(word, 0) + 1
        }

        // Each pass visits one alignment of whole-word boundaries.
        for (start in 0 until step) {
            var currentWordMap = HashMap<String, Int>()
            var currentWordCount = 0
            var left = start
            var right = start

            // Window: [left, right). Read only complete words.
            while (right + step <= n) {
                val rightWord = s.substring(right, right + step)
                right += step

                val allowedCount = wordMap[rightWord]
                if (allowedCount == null) {
                    // No valid concatenation can cross an unknown word.
                    currentWordMap = HashMap()
                    currentWordCount = 0
                    left = right
                    continue
                }

                currentWordMap[rightWord] =
                    currentWordMap.getOrDefault(rightWord, 0) + 1
                currentWordCount++

                // Only the newly added word can exceed its required count.
                while (currentWordMap.getValue(rightWord) > allowedCount) {
                    val leftWord = s.substring(left, left + step)
                    currentWordMap[leftWord] = currentWordMap.getValue(leftWord) - 1
                    currentWordCount--
                    left += step
                }

                // Bounded frequencies + equal total count imply an exact match.
                if (currentWordCount == wordCount) {
                    answer.add(left)

                    // Retain the suffix to allow overlapping matches.
                    val leftWord = s.substring(left, left + step)
                    currentWordMap[leftWord] = currentWordMap.getValue(leftWord) - 1
                    currentWordCount--
                    left += step
                }
            }
        }

        return answer
    }
}
