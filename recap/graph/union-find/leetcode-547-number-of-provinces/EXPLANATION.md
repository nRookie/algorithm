# LeetCode 547 — Number of Provinces

[Problem](https://leetcode.com/problems/number-of-provinces/): count connected
components in a symmetric n×n adjacency matrix (n <= 200). Cities are 0..n-1.

## Solution evolution

The learner built union-find with path compression and union by size, then
counted distinct representatives. [Solution.kt](Solution.kt) preserves this
seen-array counting approach with corrections. Scanning only j>i avoids self
connections and duplicate symmetric edges. This scan simplification is optional.
[ComponentCountSolution.kt](ComponentCountSolution.kt) instead starts with n
components and decrements only on a successful merge. Submit one file at a time;
both contain LeetCode's class Solution.

## Review: three mistakes in the supplied draft

1. The original swap was `temp=rootA; rootB=rootA; rootA=temp`. With roots 0
   and 3, this makes both roots 0 and fails to join the groups. Correct order:
   `temp=rootA; rootA=rootB; rootB=temp`.
2. The original size update used `size[rootA] += size[b]`. Use size[rootB];
   b may not be a root and its size entry may be stale.
3. The final scan used `uf.parent[i]`. Use `uf.find(i)` to identify the group.
   For 0→1→2, immediate parents are [1,2,2], but every node's root is 2.

The parent list is private in the saved versions to keep its internal structure
behind find and merge. Replacing seen with a component counter is not necessary
to fix the learner's approach.

## Parent pointers and size

Initially parent[x]=x and size[x]=1. A root points to itself. find follows
parents to the root and makes the visited nodes point directly to that root:
0→1→2 becomes 0→2 and 1→2 after find(0). Membership does not change.

merge first finds both roots. Equal roots mean no change. Otherwise attach the
smaller group's root below the larger root and add their sizes. size[x] is
meaningful only for roots; the old root's size can remain stale. Setting it to
1 does not describe a new singleton group. Group size is size[find(x)].

Use a regular class because this is mutable state with operations, rather than
a value requiring generated equality, destructuring, and shallow copying.

## Correctness

Initially each node is its own component. Every processed matrix edge merges
exactly its endpoints' components, preserving the invariant that union-find
groups equal connectivity under processed edges. Root-to-root attachment merges
whole groups without splitting one. Path compression preserves the root and
therefore preserves membership. After all edges are processed, groups are
exactly provinces. Counting distinct roots counts each once. Alternatively,
each merge of two different roots reduces the component count by exactly one.

Example: connections 0–1 and 1–2, with isolated node 3. Start with four groups;
merge 0,1 gives three; merge 1,2 gives two. Repeatedly merging 0,2 changes
nothing. The distinct-root scan and component counter both return 2.

## Complexity and interview wording

Matrix scan O(n²); a standard total bound is O(n² α(n)) with O(n) auxiliary
space. Union by size and path compression give O(α(n)) amortized operations;
α is the inverse Ackermann function, effectively constant for practical sizes.
It is not a guarantee that each individual find takes a fixed number of steps.

“I begin with one group per city and merge directly connected cities. Root
equality identifies group membership; path compression and union by size keep
root searches efficient. At the end I count distinct roots, or maintain a
counter that decreases only when two different groups merge.”

Recall: Why merge roots? Why read size only at roots? Why can parent[i] differ
from find(i)?

Run `bash recap/graph/union-find/leetcode-547-number-of-provinces/run.sh` or add
`components` to test the alternative. Next recap: Kruskal minimum spanning trees.
