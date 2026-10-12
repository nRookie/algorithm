import kotlin.math.max

// Learner's recursive implementation. Compile separately from Solution.kt.
class Solution {
    fun countHighestScoreNodes(parents: IntArray): Int {
        val n = parents.size
        var highestScore = 0L
        var res = 0 // Number of nodes whose score equals the highest score.
        val graph = MutableList(n + 1) { mutableListOf<Int>() }
        val scores = LongArray(n + 1) { 0 }

        // Node labels are 0 until n. Index n is unused in these collections.
        // Store each parent-child edge in both directions.
        for (i in parents.indices) {
            val a = i
            val b = parents[i]
            if (b >= 0) {
                graph[a].add(b)
                graph[b].add(a)
            }
        }

        // Return the size of u's subtree, including u; also compute its score.
        fun dfs(u: Int, parent: Int): Int {
            var score = 1L // Identity for multiplying component sizes.
            var sum = 1 // Count u itself.
            for (v in graph[u]) {
                if (v == parent) continue
                val subNodeNumber = dfs(v, u)
                sum += subNodeNumber
                score *= subNodeNumber
            }
            // All children are finished. The parent-side component contains
            // every node outside u's subtree. An empty component is omitted.
            if (n - sum > 0) {
                score *= (n - sum)
            }
            scores[u] = score
            highestScore = max(score, highestScore)
            return sum
        }

        dfs(0, -1)
        // Count ties after the global maximum is known.
        for (score in scores) {
            if (score == highestScore) res++
        }
        return res
    }
}
