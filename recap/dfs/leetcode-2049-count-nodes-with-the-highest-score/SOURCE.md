# Source and LeetCode adaptation

Original source: [acwing/DFS/846.cpp](../../../acwing/DFS/846.cpp).
The code reads an undirected tree, explores from node 1, and returns the
smallest possible largest-component size after removing one vertex. This is
the tree-centroid objective. Original judge constraints were not verified.

Submission target: [LeetCode 2049 — Count Nodes With the Highest Score](https://leetcode.com/problems/count-nodes-with-the-highest-score/description/),
Medium. Match type: related component-size technique; **different scoring
objective**, not an equivalent problem.

| Aspect | Original AcWing code | LeetCode target |
| --- | --- | --- |
| Input | Undirected edges, one-based vertices | parents array, zero-based vertices, root 0 |
| Tree | No binary restriction expressed by the code | Valid binary tree, 2–100,000 nodes |
| After deleting u | Child subtrees and the parent-side component | Same component decomposition |
| Candidate value | Largest remaining component | Product of nonempty component sizes |
| Return | Minimum candidate value | Number of candidates tied for maximum score |

The shared idea is DFS subtree-size aggregation. We intentionally change the
scoring rule to solve the judge's actual problem. [Solution.kt](Solution.kt)
is ready to paste into LeetCode; Test.kt and run.sh are local tools.

The official LeetCode statement was publicly readable when checked. Local
tests do not constitute an online Accepted result.

The original file is preserved. Its `max_part = 1` would give 1 for a singleton
tree, whereas deleting the only node leaves largest-component size 0. If
singleton input is allowed, initialize that maximum to 0. LeetCode 2049 excludes
singleton input. No claim is made that this case occurs in AcWing's original
judge constraints.
