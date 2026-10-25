fun main() {
    fun verify(n: Int, expected: Int, vararg edges: Pair<Int, Int>) {
        val matrix = Array(n) { i -> IntArray(n) { j -> if (i == j) 1 else 0 } }
        for ((a, b) in edges) { matrix[a][b] = 1; matrix[b][a] = 1 }
        check(Solution().findCircleNum(matrix) == expected)
    }
    verify(3, 2, 0 to 1)
    verify(3, 3)
    verify(1, 1)
    verify(5, 1, 0 to 4, 1 to 2, 1 to 3, 3 to 4)
    verify(5, 2, 0 to 1, 1 to 2, 2 to 0, 3 to 4)
    // Exercise merging a smaller first group into a larger second group.
    val uf = Solution.UnionFind(5)
    uf.merge(1, 2)
    uf.merge(1, 3)
    uf.merge(0, 1)
    check(uf.find(0) == uf.find(3))
    check(uf.find(4) != uf.find(0))
    println("6 checks passed")
}
