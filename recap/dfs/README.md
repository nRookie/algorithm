# DFS recap

Start with child-before-parent aggregation, then revisit search with backtracking.

Current practice: [AcWing 846 Kotlin starter](acwing-846/README.md). Implement
the original problem first; the runnable scaffold uses adjacency collections
and leaves the algorithm for the learner.

| Order | Source | Focus | Recap / judge target |
| --- | --- | --- | --- |
| 1 | [846.cpp](../../acwing/DFS/846.cpp) | Subtree sizes and components after deleting a vertex | [Notes](leetcode-2049-count-nodes-with-the-highest-score/EXPLANATION.md), [Kotlin](leetcode-2049-count-nodes-with-the-highest-score/Solution.kt); LeetCode 2049 uses the same component decomposition but a different scoring rule |
| 2 | [IDDFS/187.cpp](../../acwing/DFS/IDDFS/187.cpp) | Iterative deepening and backtracking | Pending recap; judge match not yet verified |

The first source's centroid objective is recorded explicitly in its recap;
it is not presented as equivalent to LeetCode's highest-product objective.
