import kotlin.random.Random

// Independent baseline: actually omit each candidate and traverse its components.
private fun baseline(parents: IntArray): Int {
    val n = parents.size
    val graph = MutableList(n) { mutableListOf<Int>() }
    for (u in 1 until n) {
        graph[u].add(parents[u])
        graph[parents[u]].add(u)
    }
    val scores = mutableListOf<Long>()
    for (removed in 0 until n) {
        val visited = MutableList(n) { false }
        visited[removed] = true
        var score = 1L
        for (start in 0 until n) {
            if (visited[start]) continue
            val queue = ArrayDeque<Int>()
            queue.addLast(start)
            visited[start] = true
            var componentSize = 0
            while (queue.isNotEmpty()) {
                val u = queue.removeFirst()
                componentSize++
                for (v in graph[u]) if (!visited[v]) {
                    visited[v] = true
                    queue.addLast(v)
                }
            }
            score *= componentSize.toLong()
        }
        scores.add(score)
    }
    return scores.count { it == scores.maxOrNull() }
}

fun main() {
    val solution = Solution()
    check(solution.countHighestScoreNodes(intArrayOf(-1, 2, 0, 2, 0)) == 3)
    check(solution.countHighestScoreNodes(intArrayOf(-1, 2, 0)) == 2)
    check(solution.countHighestScoreNodes(intArrayOf(-1, 0)) == 2)
    check(solution.countHighestScoreNodes(intArrayOf(-1, 0, 0, 1, 1)) == 3)
    val random = Random(2049)
    repeat(200) {
        val n = random.nextInt(2, 26)
        val parents = IntArray(n) { -1 }
        val available = mutableListOf(0)
        val childCounts = MutableList(n) { 0 }
        for (u in 1 until n) {
            val parent = available[random.nextInt(available.size)]
            parents[u] = parent
            childCounts[parent]++
            if (childCounts[parent] == 2) available.remove(parent)
            available.add(u)
        }
        // A parent's label need not be smaller than a child's label.
        val labels = listOf(0) + (1 until n).shuffled(random)
        val relabeled = IntArray(n) { -1 }
        for (u in 1 until n) relabeled[labels[u]] = labels[parents[u]]
        val original = relabeled.copyOf()
        check(solution.countHighestScoreNodes(relabeled) == baseline(relabeled)) {
            "Mismatch for ${relabeled.contentToString()}"
        }
        check(relabeled.contentEquals(original)) { "Input was modified" }
    }
    val chain = IntArray(100_000) { it - 1 }
    check(solution.countHighestScoreNodes(chain) == 2)
    println("Passed 4 fixed cases, 200 random binary-tree comparisons, and a 100,000-node chain.")
}
