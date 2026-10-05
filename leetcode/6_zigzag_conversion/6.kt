class Solution {
    fun convert(s: String, numRows: Int): String {
        if (numRows == 1 || numRows >= s.length) return s

        val rows = Array(numRows) { StringBuilder() }
        var row = 0
        var step = 1

        for (c in s) {
            rows[row].append(c)

            when (row) {
                0 -> step = 1
                numRows - 1 -> step = -1
            }
            row += step
        }

        return rows.joinToString(separator = "")
    }
}
