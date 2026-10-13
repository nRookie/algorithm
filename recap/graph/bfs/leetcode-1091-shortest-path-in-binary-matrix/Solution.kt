class Solution {
    fun shortestPathBinaryMatrix(dist: Array<IntArray>): Int {
        if (dist[0][0] == 1) return -1
        val directions = listOf(
            -1 to -1, // Top left
            -1 to 0,  // Up
            -1 to 1,  // Top right
            0 to -1,  // Left
            0 to 1,   // Right
            1 to -1,  // Bottom left
            1 to 0,   // Down
            1 to 1    // Bottom right
        )

        val queue = ArrayDeque<Pair<Int, Int>>()
        val n = dist.size
        queue.addFirst(0 to 0)
        dist[0][0] = 1

        while (queue.isNotEmpty()) {
            val (x, y) = queue.removeLast()
            if (x == n - 1 && y == n - 1) return dist[x][y]
            for ((dx, dy) in directions) {
                val nx = x + dx
                val ny = y + dy
                if (nx !in 0 until n || ny !in 0 until n) {
                    continue
                } else if (dist[nx][ny] == 0) {
                    queue.addFirst(nx to ny)
                    dist[nx][ny] = 1 + dist[x][y]
                }
            }
        }
        return -1
    }
}
