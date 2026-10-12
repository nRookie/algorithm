# My recursive solution — LeetCode 2049

Implementation: [LearnerSolution.kt](LearnerSolution.kt). This is a polished
account of the learner's supplied reasoning, preserving the undirected graph,
recursive DFS, variable names, stored scores, and final counting pass. Formatting
and comments were cleaned up, braces were added around the outside-component
condition, and `kotlin.math.max` was imported for standalone compilation.

## What I need to calculate

For each node, imagine removing it and its incident edges. Its score is the
product of the sizes of the remaining nonempty connected components. Return
the number of nodes that achieve the highest score, not the score itself.

## Solution evolution

A direct approach tries each removal and traverses the remaining components
to count their sizes. That takes O(n²) time because it repeats a traversal
for every node. A tree lets me reuse subtree sizes: removing a node separates
its child subtrees and, when present, the part outside its own subtree.
One DFS can therefore calculate all scores in O(n) time.

## 1. Build the adjacency lists

`n = parents.size` is the total number of nodes. Node labels are `0 until n`.
`parents[i]` gives the parent label of node i; `parents[0] = -1` means node 0
has no parent. For each real parent, I add the edge in both directions.

`graph[u]` is the list of u's neighbors. An index inside that list selects a
neighbor; it is not itself a node label. Because the graph is undirected,
DFS receives the node it came from as `parent` and skips that neighbor.
Skipping only the parent is sufficient for a tree, but not a general cyclic graph.

My allocation uses `n + 1`, although `n` entries are enough for zero-based
labels. The extra entry at index n is unused. In `scores` it stays zero and
does not affect the result because valid problem scores are positive.

## 2. Give DFS one clear return meaning

`dfs(u, parent)` returns the size of u's subtree, **including u itself**.

- `sum = 1` counts u before visiting children.
- `score = 1L` starts the product at its multiplicative identity, using Long.
- `subNodeNumber = dfs(v, u)` is the size of the entire child subtree rooted
  at v, not just v's direct children.
- `sum += subNodeNumber` accumulates the size to return to u's parent.
- `score *= subNodeNumber` accounts for one component left after removing u.

Each recursive call has its own `sum` and `score`. The parent's call waits
until the child returns before using its result.

## 3. Account for the parent-side component

After processing all children, `sum` contains u plus all its descendants.
The number of nodes outside that subtree is `n - sum`. These nodes form
one connected component when the quantity is positive.

Multiply by `n - sum` only if it is greater than zero. For the root, `sum = n`:
there is no outside component. Multiplying by zero would incorrectly erase
the product of the child component sizes.

## 4. Save the score, then return the size

`scores[u] = score` records the candidate's score, and `highestScore` keeps
the largest score seen so far. DFS returns `sum`, because its parent needs
the child's subtree size to compute its own score.

The traversal starts with `dfs(0, -1)`. Once it finishes, every node's score
is available. A final pass counts the values equal to `highestScore`.

Storing all scores is one valid way to count ties; it is not required. An
alternative updates the count during DFS: reset it to 1 on a new maximum,
increment it on an equal score, and leave it unchanged on a lower score.
My implementation deliberately keeps the two-pass approach.

## Example using my input

```text
parents = [-1, 2, 0, 2, 0]

        0
       / \
      2   4
     / \
    1   3

graph[0] = [2, 4]
graph[1] = [2]
graph[2] = [1, 0, 3]
graph[3] = [2]
graph[4] = [0]
```

Calls enter in order 0, 2, 1, 3, 4 and return in order 1, 3, 2, 4, 0.

| Finished node u | Child subtree sizes | sum returned | Outside size | score | highestScore afterward |
| --- | --- | --- | --- | --- | --- |
| 1 | None | 1 | 4 | 4 | 4 |
| 3 | None | 1 | 4 | 4 | 4 |
| 2 | 1, 1 | 3 | 2 | 1 × 1 × 2 = 2 | 4 |
| 4 | None | 1 | 4 | 4 | 4 |
| 0 | 3, 1 | 5 | 0, omitted | 3 × 1 = 3 | 4 |

The real nodes' scores are `[3, 4, 2, 4, 4]`. Nodes 1, 3, and 4 tie,
so the answer is 3. The extra allocated score entry stays zero.

## Why it works and what it costs

A leaf returns 1. If each child returns its correct subtree size, adding
those disjoint sizes plus 1 gives the correct size for u. Removing u
separates exactly those child subtrees and the outside component, so their
nonempty sizes produce the correct score. The final pass counts precisely
the nodes whose score equals the maximum.

Time is O(n): graph construction, DFS, and score counting each take linear
time. Space is O(n) for adjacency lists and scores, plus O(h) recursive stack
space for tree height h; in the worst case h = n.

Long is necessary because the product can exceed Int range. The recursive
approach can overflow the JVM stack on a deep chain. The existing
[Solution.kt](Solution.kt) uses an explicit stack to handle that case; it
also uses directed child lists and counts ties without storing all scores.
Those are separate implementation choices, not changes to this saved version.

If adapting the score storage to Kotlin collections, `MutableList(n) { 0L }`
can replace `LongArray(n + 1) { 0 }`; `graph` can also have exactly n entries.
The saved implementation retains the learner's chosen storage for comparison.

## Local review results

The saved recursive implementation passed all 4 fixed cases and 200 random
binary-tree comparisons against the independent removal-and-traversal baseline.
The random cases also checked that the input was not modified. It raised
`StackOverflowError` on the 100,000-node chain under the local JVM's default
stack settings. This confirms the recursion limitation; no online-judge
acceptance is claimed.

Both implementation files declare `class Solution`, so compile only one at
a time. To run the original harness against this version from this folder:

```sh
mkdir -p .build
kotlinc LearnerSolution.kt Test.kt -include-runtime -d .build/learner.jar
java -cp .build/learner.jar TestKt
```

The harness includes the deep chain, so a stack-overflow failure is expected
with the current recursive implementation and local default stack settings.
The existing `run.sh` continues to test the separate iterative solution.

## Interview wording

“I need to count how many nodes achieve the highest removal score. Rather
than traversing the tree again for every removal, I use subtree sizes.

I build an undirected adjacency list from the parents array. Nodes are indexed
from 0 to n minus 1, and I skip the root's parent value of minus 1. My DFS
starts at node 0 and skips the parent edge to avoid going backward.

DFS returns the size of the current node's subtree, including itself. Each
child returns a subtree size, which I add to sum and multiply into score.
After all children finish, n minus sum gives the size of the outside component;
I multiply that in only if it is nonempty.

I save each node's score, track the maximum, and finally count how many scores
equal that maximum. I use Long for the product. The algorithm takes O(n) time
and O(n) space. For a very deep tree, I would use an explicit stack to avoid
overflowing Kotlin's recursive call stack.”
