class Solution {
    fun isValidSudoku(matrix: Array<CharArray>): Boolean {
        val n = 9
        val rows = Array(n) { BooleanArray(n) }
        val columns = Array(n) { BooleanArray(n) }
        val blocks = Array(n) { BooleanArray(n) }

        for (row in 0 until n) {
            for (col in 0 until n) {
                val char = matrix[row][col]
                if (char == '.') continue

                // Map '1'..'9' to array indexes 0..8.
                val digitIndex = char - '1'
                // Flatten the 3-by-3 grid of boxes into indexes 0..8.
                val block = (row / 3) * 3 + col / 3

                // Check previously visited cells before marking this cell.
                if (rows[row][digitIndex] ||
                    columns[col][digitIndex] ||
                    blocks[block][digitIndex]) {
                    return false
                }

                rows[row][digitIndex] = true
                columns[col][digitIndex] = true
                blocks[block][digitIndex] = true
            }
        }
        return true
    }
}
