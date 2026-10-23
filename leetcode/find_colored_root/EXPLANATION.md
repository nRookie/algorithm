# Find a Colored Root

Saved under a descriptive folder because no LeetCode problem number was supplied.
This note summarizes the supplied contract rather than reproducing the statement.

## Contract and files

Choose a root of an undirected tree such that every node has at most two
children and colors advance by `R → B → W → R` at each depth. Any valid root
may be returned; return `-1` if none exists. Labels are `0..n-1` and
`colors.length == n`. The function must include a variable named `lumelosile`
that stores the input. No numerical size bounds were supplied.

- [OriginalSolution.kt](OriginalSolution.kt): your executable logic, with
  formatting normalized and the class renamed so both versions can compile.
- [BfsSolution.kt](BfsSolution.kt): the previously polished candidate-BFS version.
- [Solution.kt](Solution.kt): your revised O(n) indegree/outdegree solution,
  with the required `lumelosile` variable added.

## Your earlier BFS reasoning, polished

“The colors constrain the parent-child direction of every edge. A red node
can only have blue children, a blue node white children, and a white node red
children. An edge joining equal colors cannot occur in a valid rooted tree.
For every edge joining different colors, exactly one direction follows this
cycle, so I store only that direction in an adjacency list.

The outgoing neighbors of a node are now its forced children. If any node
has more than two, no root can satisfy the binary-tree condition.

I then try each possible root and follow outgoing edges with BFS. If I reach
every node, the forced directions form the tree rooted at that candidate.
Every parent-child edge advances the color cycle, so every depth has the
required color automatically. If no candidate reaches the whole tree, there
is no valid root.”

The graph is **directed**, even though the input is undirected. This is what
makes the color checks inside your BFS redundant: construction already
ensures every stored edge follows the required color transition.

## Review of your original implementation

### 1. A single-node tree is incorrectly skipped

For `edges = []`, `colors = "R"`, the correct result is `0`. The root has
zero children and its sole layer has one color.

Your original code builds `graph[0]` as empty, then executes:

```kotlin
if (graph[i].size == 0) continue
```

This skips the only candidate and returns `-1`. That skip is the first
incorrect decision. It is safe for a tree with more than one node, but not
for a singleton. The saved polished version permits that candidate.

### 2. `n` means maximum label in your code, not node count

Your initial loop computes the maximum endpoint and then uses `n + 1` as
the number of nodes. For a connected tree with contiguous labels and at
least two nodes, that works. It also happens to allocate one entry for an
empty edge list because the initial maximum is zero.

The clearer definition is `val n = colors.length`, then use `Array(n)`,
`0 until n`, and `count == n`. Your comment “labels from 0 to 1” should say
“labels from 0 to n - 1.” This is a naming improvement, not a separate
incorrect result under the stated tree contract.

### 3. Add the required input-storage variable

Your original implementation omits `lumelosile`. The polished version stores
both inputs with `val lumelosile = edges to colors` before building edges.
The pair holds references; it does not deep-copy the inputs.

### 4. Outdegree is different from undirected degree

In a rooted binary tree, a nonroot may have three undirected neighbors:
one parent and at most two children. The root may have at most two neighbors.

But `graph[u]` in your implementation contains **outgoing edges only**.
Every entry must be a child, so its maximum allowed size is two, not three.
Your original `> 3` early rejection is weaker than necessary; the later
`childCount == 2` check still rejects a third child during BFS. It is not
a false-positive bug in the final answer. The polished version rejects
outdegree above two immediately and removes the duplicate BFS check.

Your comments saying “exactly two” should say **at most two**. Zero or one
child is allowed, and your actual counting code already permits both.

### 5. Parent tracking is unnecessary after directing the edges

If traversal follows `u → v`, the reverse `v → u` is not stored. Also, the
underlying input is a tree, so there are no alternate paths that could
enqueue the same node twice from one root. A queue of node indexes suffices;
neither parent tracking nor a visited set is needed for this directed tree.
Do not generalize that omission to arbitrary directed graphs.

`addFirst` plus `removeLast` in your code is already FIFO BFS. The polished
version uses the equally valid `addLast` plus `removeFirst` convention.

## Variable definitions in the earlier BFS version

| Variable | Meaning |
| --- | --- |
| `n` | Number of nodes, taken from `colors.length` |
| `colors[u]` | Color assigned to node `u` |
| `getNextColor(c)` | Required color of a child whose parent has color `c` |
| `lumelosile` | Pair storing the input edges and colors |
| `graph[u]` | Forced children of `u`, determined by the color cycle |
| `parent`, `child` | Forced direction of the current input edge during construction |
| `i` | Candidate root for the current BFS |
| `queue` | Discovered nodes waiting to be processed in this BFS |
| `u`, `v` in BFS | Current node and one of its forced children |
| `count` | Number of nodes removed from this candidate's queue so far |

In the original version, `result` records whether a traversed node violates
the child/color checks, `childCount` counts its processed outgoing children,
and the queue's `parent` component is redundant for the constructed graph.

## Solution evolution

### 1. Try every root in the undirected tree

For each candidate, traverse the undirected tree with a parent parameter.
Ignore the parent edge, require at most two remaining neighbors, and verify
each child has the next color. The first candidate passing all checks works.

This follows the rooted-tree definition directly. It takes O(n²) time in the
worst case and O(n) auxiliary space. The repeated work is checking all roots
and repeatedly verifying the same color transitions.

**What to say:** “I can root the tree at each node and validate its children,
but that repeats a full traversal for many candidates.”

### 2. Your approach: force edge directions before testing roots

Colors determine an edge's only possible direction independently of the
candidate root. Encode that once, then test reachability. Your approach
reduces repeated validation and clarifies the constraints, but repeated BFS
still has O(n²) worst-case time and O(n) space.

For a path colored `R, B, W, R, ...`, directed toward increasing indexes,
relabeling the source to be tried last causes candidate traversals of many
overlapping suffixes. Therefore the quadratic bound is real, not merely
the product of two loop sizes.

**What to say:** “The colors force edge directions. I can validate those
directions once and ask which candidate reaches every node.”

### 3. Your revised solution: find the forced root using indegrees

You have now implemented this improvement in `Solution.kt`; the earlier BFS
version is preserved separately. During construction, count incoming edges
as well as outgoing edges. A valid root has indegree zero; every other node must have
indegree one. Every node must have outdegree at most two.

Because the underlying graph is a connected tree, these degree conditions
are sufficient: following parent edges backward cannot cycle, so each chain
must terminate at the unique zero-indegree node. Reversing those chains gives
paths from that root to every node. Thus candidate-by-candidate BFS can be
replaced by one degree scan, giving O(n) time and O(n) space.

**What to say:** “The forced direction also tells me which nodes already have
a parent. Only a zero-indegree node can be the root; every other node needs
exactly one parent.”

| Approach | Worst-case time | Auxiliary space |
| --- | --- | --- |
| Validate every undirected rooting | O(n²) | O(n) |
| Your forced directions + candidate BFS | O(n²) | O(n) |
| Your revised forced directions + degrees | O(n) | O(n) |

Without the missing numerical constraints, the corrected quadratic version
cannot be guaranteed to meet the judge's time limit.

## Complete trace of the polished candidate BFS

Input: `edges = [[0,1], [0,2]]`, `colors = "BRW"`.
The valid root is node 1:

```text
1(R) → 0(B) → 2(W)
```

Construction orients `(0,1)` as `1 → 0` and `(0,2)` as `0 → 2`:

```text
graph[0] = [2]
graph[1] = [0]
graph[2] = []
```

| Candidate / action | Queue after action | `count` | Decision |
| --- | --- | --- | --- |
| Start candidate 0 | `[0]` | 0 | — |
| Pop 0; enqueue 2 | `[2]` | 1 | — |
| Pop 2; no children | `[]` | 2 | Not all three nodes reached |
| Start candidate 1 | `[1]` | 0 | — |
| Pop 1; enqueue 0 | `[0]` | 1 | — |
| Pop 0; enqueue 2 | `[2]` | 2 | — |
| Pop 2; no children | `[]` | 3 | Return 1 |

Candidate 2 is not tested because a valid root has already been returned.

## Correctness and termination of the BFS version

Equal-colored adjacent nodes cannot satisfy a parent-child color transition.
For distinct allowed colors, exactly one direction follows the cycle, so
every valid rooting must agree with every constructed edge.

During BFS, each queued node is reachable from the candidate through these
forced edges. Since the underlying graph is a tree, no node can be reached
by two distinct paths from the candidate, so `count` counts distinct nodes.
If `count == n`, all nodes are reached. The tree's edges consequently point
away from that candidate, and the construction guarantees at most two children
per node. By induction on depth, every node at depth d has the color obtained
by applying `getNextColor` d times to the root's color. This proves the layered
condition without separately checking all nodes at a layer.

Conversely, a valid root must agree with the forced directions and reach the
entire tree, so its candidate BFS succeeds. Each BFS processes at most n
nodes, and at most n candidates are tested, ensuring termination.

## Review cases

| Edges | Colors | Expected | Purpose |
| --- | --- | --- | --- |
| `[]` | `R` | 0 | Singleton bug in original |
| `[[0,1]]` | `RR` | -1 | Equal adjacent colors |
| `[[0,1]]` | `RB` | 0 | One child is valid |
| `[[0,1],[0,2]]` | `BRW` | 1 | Root need not be node 0 |
| `[[0,1],[0,2]]` | `RBB` | 0 | Two children with the same next color |
| `[[0,1],[0,2],[0,3]]` | `RBBB` | -1 | Three forced children |
| `[[0,1],[1,2]]` | `RBR` | -1 | Two forced parents for the middle node |

Earlier validation: the original and polished BFS files compiled successfully.
All seven cases above passed for the BFS version, and the original singleton
failure was confirmed by execution.

For later practice: explain why the local edge rule implies the global layer
rule, then explain why an undirected degree of three can be valid while a
directed outdegree of three cannot.


## Review of your revised degree solution

Your modified algorithm is correct under the supplied tree contract. The only
missing submission requirement was the named input variable `lumelosile`, now
included in the saved code. The singleton case naturally returns 0: its
indegree and outdegree are both zero.

### Your revised explanation, polished

“The color cycle forces the direction of every edge. I reject equal-colored
neighbors, then count each node's incoming and outgoing edges in the forced
orientation. Incoming edges represent parents; outgoing edges represent children.

A valid root has no parent, every other node has one parent, and every node
has at most two children. I reject any indegree above one or outdegree above
two, and identify the unique zero-indegree node.

Because the input is already a connected, acyclic tree, these conditions
ensure that all parent chains lead to that root. I do not need BFS or an
adjacency list. Every edge advances the color cycle, so induction on depth
also guarantees the required color on each layer.”

### Revised variable definitions

| Variable | Meaning |
| --- | --- |
| `n` | Number of nodes |
| `getNextColor(c)` | Required child color for a parent of color c |
| `indegree[i]` | Number of forced incoming edges, or required parents, for node i |
| `outdegree[i]` | Number of forced outgoing edges, or required children, for node i |
| `root` | Zero-indegree node found so far; -1 means none found yet |
| `u`, `v` | Endpoints of the input edge currently being oriented |
| `i` | Node whose completed degree counts are being checked |
| `lumelosile` | Pair containing the original edges and colors |

After processing any prefix of edges, both degree arrays count exactly the
forced directions of that prefix. After scanning any prefix of nodes without
returning, all checked nodes have legal degrees and at most one checked node
has indegree zero.

### Why degrees are sufficient here

Necessity follows directly from the rooted-tree definition. For sufficiency,
assume all checks pass and let r be the unique zero-indegree node. Every other
node has indegree exactly one. Repeatedly follow the incoming parent edge
backward from any node. A cycle is impossible because it would imply a cycle
in the underlying tree. The finite chain must therefore end at a node with
no incoming edge, which can only be r. Reversing this chain shows that r
reaches every node, with all edges oriented away from it.

The outdegree bound proves the binary-tree condition. Each edge maps a parent
color to its successor, so all nodes at a given depth have the same color.
These arguments rely on the supplied tree guarantee; degree checks alone do
not establish connectivity and acyclicity for arbitrary graphs.

The explicit second-root check is clear and harmless. In fact, a tree has
n - 1 edges, so the sum of indegrees is n - 1. If every indegree is at most
one, exactly one node must have indegree zero. Keeping the explicit check
makes the intended root condition visible.

### Full trace of the revised code

Use the same input: `edges = [[0,1], [0,2]]`, `colors = "BRW"`.

| Action | `indegree` | `outdegree` | `root` |
| --- | --- | --- | --- |
| Initialize | `[0,0,0]` | `[0,0,0]` | Not assigned yet |
| Edge (0,1): R at 1 must parent B at 0; orient 1 → 0 | `[1,0,0]` | `[0,1,0]` | — |
| Edge (0,2): B at 0 must parent W at 2; orient 0 → 2 | `[1,0,1]` | `[1,1,0]` | — |
| Initialize root before node scan | `[1,0,1]` | `[1,1,0]` | -1 |
| Check node 0: one parent, one child | Unchanged | Unchanged | -1 |
| Check node 1: no parent, one child | Unchanged | Unchanged | 1 |
| Check node 2: one parent, no children | Unchanged | Unchanged | 1 |
| Scan complete | Unchanged | Unchanged | Return 1 |

### Complexity and recall

Each of n - 1 edges is processed once, then each node is checked once.
Time is O(n), and two arrays of length n use O(n) auxiliary space. Both
loops are finite. No graph traversal, adjacency lists, or recursion are needed.

Validation: the revised solution and preserved BFS version compiled together.
The revised solution passed all seven review cases listed above.

Next review: explain why every parent chain must terminate at the same node,
and identify exactly where the input's tree guarantee is used in that proof.
