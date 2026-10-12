# AcWing 846 — Kotlin practice starter

Implement [Solution.kt](Solution.kt). The input reader, collection-based
adjacency lists, example input, and test runner are ready. The algorithm is
intentionally left as TODO so you can try the original problem yourself.

Read [Building the graph and understanding adjacency lists](GRAPH_GUIDE.md)
for the input-to-collection mapping, DFS traversal, and overall approach.

Open [the line-by-line DFS walkthrough](EXECUTION.html) in a browser to follow
the five-node discussion example. The graph appears beside the Kotlin code;
Previous, Next, and the step slider show recursive calls, local variables,
returned subtree sizes, and hypothetical removal components. This walkthrough
uses a snapshot of the learner's implementation with the missing closing
parenthesis on the `for` loop corrected; it does not edit `Solution.kt`.

Original reference: [846.cpp](../../../acwing/DFS/846.cpp).
This starter targets the original tree-removal objective, rather than the
related LeetCode 2049 product-score problem.

## Problem

Given an undirected tree with n nodes labeled 1 through n, remove one node
and all incident edges. Return the smallest possible size of the largest
remaining connected component. Return a component size, not a node label.
For a single-node tree, the result is 0.

Input: n, followed by n − 1 undirected edges, one pair of endpoints per edge.
Output: one integer. Inputs are assumed to form a valid tree. This contract
is reconstructed from the saved implementation and mathematical objective;
the original judge's numeric bounds have not been independently verified.

The local example is the one from our discussion, not a claimed official sample:

```text
        1
       / \
      2   3
     / \
    4   5
```

Removing node 2 leaves components of sizes 1, 1, and 2. The answer is 2.
The corresponding files are [sample.in](sample.in) and [sample.out](sample.out).

## Your function

```kotlin
fun minimumLargestComponent(n: Int, graph: List<List<Int>>): Int
```

`graph[u]` contains the neighbors of node u. Each edge is stored in both
directions. Index 0 is unused. The input reader constructs separate mutable
lists with `MutableList(n + 1) { mutableListOf<Int>() }`.

You may use Kotlin collections for additional state as needed. No forward-star
arrays (`h`, `e`, `ne`) or manual linked-array operations are needed.

## Run from the repository root

Compile the starter:

```sh
bash recap/dfs/acwing-846/run.sh build
```

Run the discussion example (expected output: 2):

```sh
bash recap/dfs/acwing-846/run.sh sample
```

Run the seven local cases:

```sh
bash recap/dfs/acwing-846/run.sh test
```

Run your own input:

```sh
bash recap/dfs/acwing-846/run.sh stdin < your-input.txt
```

Before you replace TODO, sample/test runs deliberately report that the solution
is not implemented and exit with status 1. The build command still succeeds.
After implementation, failed tests show the expected and actual results.
Compilation artifacts stay in the ignored .build directory.
