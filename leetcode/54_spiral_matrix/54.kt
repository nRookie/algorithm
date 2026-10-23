class Solution {
    fun spiralOrder(matrix: Array<IntArray>): List<Int> {
        val m = matrix.size
        val n = matrix[0].size
        var leftB = 0
        var rightB = n - 1
        var upB = 0
        var downB = m - 1
        val ans = mutableListOf<Int>()

        // Unvisited rectangle: rows [upB, downB], columns [leftB, rightB].
        while (leftB <= rightB && upB <= downB) {
            var row = upB
            var col = leftB

            // Consume the top row from left to right.
            while (col <= rightB) {
                ans.add(matrix[row][col])
                col++
            }
            upB++
            if (leftB > rightB || upB > downB) break

            // Consume the right column from top to bottom.
            row = upB
            col = rightB
            while (row <= downB) {
                ans.add(matrix[row][col])
                row++
            }
            rightB--
            if (leftB > rightB || upB > downB) break

            // Consume the bottom row from right to left.
            row = downB
            col = rightB
            while (col >= leftB) {
                ans.add(matrix[row][col])
                col--
            }
            downB--
            if (leftB > rightB || upB > downB) break

            // Consume the left column from bottom to top.
            row = downB
            col = leftB
            while (row >= upB) {
                ans.add(matrix[row][col])
                row--
            }
            leftB++
        }

        return ans
    }
}
