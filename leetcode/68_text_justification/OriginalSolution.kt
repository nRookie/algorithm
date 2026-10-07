// Your latest implementation, with formatting polished for comparison.
class OriginalSolution {
    fun fullJustify(words: Array<String>, maxWidth: Int): List<String> {
        var candidateWidth = 0
        var wordWidth = 0
        var i = 0
        val n = words.size
        val positions = mutableListOf<MutableList<String>>()
        var row = 0
        positions.add(mutableListOf())

        while (i < n) {
            candidateWidth = candidateWidth + words[i].length +
                if (positions[row].isEmpty()) 0 else 1

            if (candidateWidth <= maxWidth) {
                positions[row].add(words[i])
                wordWidth += words[i].length
                i++
            } else {
                val slotNumber = positions[row].size - 1
                var extraSpace = maxWidth - wordWidth
                var slotIndex = 0

                if (slotNumber == 0) {
                    positions[row][slotIndex] += " ".repeat(extraSpace)
                } else {
                    while (extraSpace > 0) {
                        if (slotIndex < slotNumber) {
                            positions[row][slotIndex] += " "
                            extraSpace--
                            slotIndex++
                        } else {
                            slotIndex = 0
                        }
                    }
                }

                positions.add(mutableListOf())
                candidateWidth = 0
                wordWidth = 0
                row++
            }
        }

        if (maxWidth - wordWidth > 0) {
            var spaceLeft = maxWidth - wordWidth
            val slotNumber = positions[row].size - 1

            for (j in 0 until slotNumber) {
                positions[row][j] += " "
                spaceLeft--
            }
            if (spaceLeft > 0) {
                positions[row][positions[row].lastIndex] += " ".repeat(spaceLeft)
            }
        }

        return positions.map { it.joinToString("") }.toMutableList()
    }
}
