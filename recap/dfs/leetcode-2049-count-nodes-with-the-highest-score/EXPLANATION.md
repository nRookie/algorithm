# DFS recap: subtree sizes and removing a node

The learner's own recursive implementation is saved separately in
[LearnerSolution.kt](LearnerSolution.kt), with its polished reasoning,
example trace, and interview wording in
[LEARNER_EXPLANATION.md](LEARNER_EXPLANATION.md).

Source: [AcWing 846.cpp](../../../acwing/DFS/846.cpp).
Submission: [LeetCode 2049](https://leetcode.com/problems/count-nodes-with-the-highest-score/description/),
using [Solution.kt](Solution.kt). See [SOURCE.md](SOURCE.md) for the contract
comparison. This explanation reconstructs the algorithm from the old code;
it does not claim to reproduce the learner's past reasoning.

## What this DFS computes

DFS explores a branch before moving to the next branch. For subtree sizes,
the important moment is after the children have been processed: their results
are then available to the parent.

Define `size[u]` as the number of nodes in the subtree rooted at u, **including
u itself**. A leaf has size 1. In general:

```text
size[u] = 1 + sum(size[child])
```

In the original recursive code, `Size[u] = 1` counts u, `dfs(j)` computes a
child's result, and `Size[u] += Size[j]` accumulates it after the call returns.
`st` prevents revisiting a vertex through undirected edges. The root used for
this computation is just an orientation for describing the components.

## Why subtree sizes answer a removal question

Removing node u breaks a tree into:

- One component of size `size[child]` for each child.
- A component of size `n - size[u]` on the parent side, if that quantity is positive.

A tree has a unique path between two nodes. Different child branches cannot
reconnect without passing through u, which has been removed. The nodes outside
u's subtree remain connected through its parent side. These components contain
all n − 1 remaining nodes without overlap.

The quantity `n - size[u]` excludes u and all its descendants. It is not just
the parent node, and it is not `n - size[child]`.

AcWing takes the maximum of these sizes and minimizes that value across u.
LeetCode 2049 multiplies the sizes and counts how many nodes attain the highest
product. These objectives differ; the reusable part is finding the components.

## Solution evolution

### Baseline: try each removal explicitly

For each candidate, mark it unavailable, traverse all remaining connected
components, and count their nodes. Apply the required scoring rule and compare
with the best value seen. This directly implements the removal definition.

A tree traversal costs O(n); doing it for all n candidates costs O(n²) time
and O(n) reusable auxiliary space. It repeatedly recounts many identical branches.

What to say: "I could remove each node conceptually and traverse the remaining
components, but that repeats a whole-tree traversal for every candidate."

### Reuse subtree sizes

Root the tree once and compute every subtree size. Then each candidate's
component sizes are already available from its children and its outside count.
Every child edge contributes once to the computation, giving O(n) total time
and O(n) auxiliary space.

What to say: "Removing a node separates each child subtree and the part outside
its own subtree. One traversal computes the sizes I need for every candidate."

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Traverse after every removal | O(n²) | O(n) |
| DFS subtree aggregation | O(n) | O(n) |

## Kotlin collections and DFS order

LeetCode gives the parent of every node, so build directed child lists:

```kotlin
val children = MutableList(n) { mutableListOf<Int>() }
for (u in 1 until n) children[parents[u]].add(u)
```

The outer index is a node label; each inner list contains that node's children.
It replaces the original `h`, `e`, and `ne` arrays. Node 0 has parent −1, so
construction skips it. Labels are identifiers, not a guaranteed traversal order:
a parent can have a larger label than its child.

The original code is recursive. The Kotlin submission uses an explicit
`ArrayDeque<Int>` stack because a valid tree can be a chain of 100,000 nodes.
A recursive Kotlin DFS would risk exhausting the JVM call stack.

First record a DFS discovery order. Every parent is recorded before its
children. Process that list in reverse so every child result is ready before
its parent's result. This preserves the dependency that recursive DFS achieves
when a call returns. The exact sibling order is irrelevant to the sums.

No visited set is needed here because the input is a valid rooted tree and
we follow only parent-to-child edges. That simplification does not apply to
an arbitrary graph with cycles or repeated incoming paths.

## Example and complete execution trace

```text
parents = [-1, 0, 0, 1, 1]

        0
       / \
      1   2
     / \
    3   4
```

Adjacency lists: `0: [1,2]`, `1: [3,4]`; all other lists are empty.
The stack's right end is its top. Children are pushed in their list order:

| Action | Stack afterward | order afterward |
| --- | --- | --- |
| Initialize | [0] | [] |
| Pop 0; push 1, 2 | [1,2] | [0] |
| Pop 2 | [1] | [0,2] |
| Pop 1; push 3, 4 | [3,4] | [0,2,1] |
| Pop 4 | [3] | [0,2,1,4] |
| Pop 3; finish discovery | [] | [0,2,1,4,3] |

Initially all sizes are 1, `highestScore = 0L`, and `count = 0`.
Reverse processing order is 3, 4, 1, 2, 0:

| u | Child sizes | Final size[u] | n − size[u] | Score | highestScore, count afterward |
| --- | --- | --- | --- | --- | --- |
| 3 | None | 1 | 4 | 4 | 4, 1 |
| 4 | None | 1 | 4 | 4 | 4, 2 |
| 1 | 1, 1 | 3 | 2 | 1 × 1 × 2 = 2 | 4, 2 |
| 2 | None | 1 | 4 | 4 | 4, 3 |
| 0 | 3, 1 | 5 | 0 (absent) | 3 × 1 = 3 | 4, 3 |

Return 3: nodes 2, 3, and 4 tie for the highest score.
For comparison, AcWing's largest-component objective on this tree would favor
node 1 with largest component 2. This illustrates why the objectives must not
be conflated.

## Scoring and correctness details

Start each score at `1L`, the identity for multiplication. Multiply each
child component and multiply `remaining` only when it is positive. For the
root there is no parent-side component; multiplying by zero would incorrectly
make its score zero.

Use Long before multiplying. For a 100,000-node chain, a middle node's score
can exceed Int range. Because this is a binary tree, removal creates at most
three components. Each size is at most n, so even the loose bound n³ ≤ 10¹⁵
fits Long. This bound depends on the binary-tree guarantee.

When a score exceeds the previous maximum, reset count to 1. When it equals
the maximum, increment count. Lower scores leave both variables unchanged.

Before processing u in reversed discovery order, all its child sizes are final.
Their disjoint subtrees plus u give the correct size[u]; the component argument
then gives the correct score. After each processed node, highestScore is the
largest processed score and count is exactly its number of occurrences.
After all nodes, that statement covers the whole tree.

DFS discovery processes each vertex once and each child edge once; the reverse
pass also processes each child edge once. Total time is O(n). Adjacency lists,
order, explicit stack, and sizes together use O(n) auxiliary space. The input
is not modified.

## Original-code boundary note

The AcWing code initializes `max_part` to 1. If a singleton tree is permitted,
this should be 0: removing its only node leaves no nonempty components.
LeetCode 2049 requires at least two nodes, so this is a source-review caveat,
not a failing LeetCode case. Original AcWing constraints remain unverified.

## Interview wording

"I need the component sizes produced by removing each node. I define size[u]
as the number of nodes in u's subtree, including u. Removing u separates each
child subtree, plus the nodes outside u's subtree, whose count is n − size[u].

I build child lists from the parents array and record a DFS order with an
explicit stack. I process that order backward so each child's size is ready
before its parent. This avoids deep recursion on a long chain.

For each node, I multiply the nonempty component sizes using Long. I track
the maximum product and how many nodes tie for it. Both passes visit each
node and edge only a constant number of times, so time and auxiliary space
are O(n)."

## Run and submit

```sh
bash recap/dfs/leetcode-2049-count-nodes-with-the-highest-score/run.sh
```

The harness checks official examples, a two-node tree, the traced example,
random binary trees against explicit removal and component traversal, and a
100,000-node chain. Paste only Solution.kt into LeetCode 2049. These are local
checks, not a claim of online judge acceptance.
