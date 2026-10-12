fun minimumLargestComponent(n: Int, graph: List<List<Int>>): Int {
    // Nodes are labeled 1 through n. graph[0] is unused.
    // Return the minimum possible largest-component size after removing one node.
    var res = Int.MAX_VALUE // Smallest maxPart found across all nodes
    fun dfs(u : Int, parent: Int): Int{
	// after processing node u, return the number of nodes in its subtree, including u.
        var sum = 1 // size of the current node's subtree, including itself
        var maxPart = 0 // Largest component remaining if the current node is removed
    	for (v in graph[u]): {
	    if (v == parent) continue
	    val subSum = dfs(v, u)
	    sum += subSum
	    maxPart = maxOf(maxPart, subSum)
   	 }

	 maxPart = maxOf(maxPart, n - sum)
	 res = minOf(res, maxPart)
	 return sum // return the size of u's subtree
    }

    dfs(1, 0)
    return res

}
