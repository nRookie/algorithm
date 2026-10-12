class Solution {
    fun countHighestScoreNodes(parents: IntArray): Int {
        val n = parents.size
        val children = MutableList(n) { mutableListOf<Int>() }
        for (u in 1 until n) children[parents[u]].add(u)

        // DFS discovery order: every parent appears before its descendants.
        val order = mutableListOf<Int>()
        val stack = ArrayDeque<Int>()
        stack.addLast(0)
        while (stack.isNotEmpty()) {
            val u = stack.removeLast()
            order.add(u)
            for (child in children[u]) stack.addLast(child)
        }

        val size = MutableList(n) { 1 }
        var highestScore = 0L
        var count = 0
        // Reverse order ensures each child's subtree size is ready.
        for (index in order.lastIndex downTo 0) {
            val u = order[index]
            var score = 1L
            for (child in children[u]) {
                size[u] += size[child]
                score *= size[child].toLong()
            }
            val remaining = n - size[u]
            if (remaining > 0) score *= remaining.toLong()

            if (score > highestScore) {
                highestScore = score
                count = 1
            } else if (score == highestScore) {
                count++
            }
        }
        return count
    }
}
