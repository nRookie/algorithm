# Algorithm concepts cheatsheet

Reusable facts collected from solved problems. For how to derive a solution,
use [the solving workflow](algorithm-solving-workflow.md). Full implementations
and traces belong in each problem's `EXPLANATION.md`.

To add future lessons, ask: **“What can we learn from this? Update the cheatsheet.”**
Keep the condition behind each rule, not just the rule itself.

## Graph traversal: DFS and BFS

### BFS finds the fewest edges; DFS does not guarantee that

- **Rule:** In an unweighted graph, BFS explores states in increasing distance
  from the start, measured in number of edges. The first target reached has the
  minimum number of edges among all reachable targets. Equal positive edge
  costs also make this a minimum-cost path.
- **Why:** A FIFO queue processes all states at distance d before states at
  distance d + 1. DFS follows a branch deeply before trying alternatives.
- **Example:** In Jump Game III, each legal jump is one edge. BFS can find the
  minimum number of jumps to any zero. A jump spanning ten array positions
  still costs one jump. A Boolean-only implementation must add distance
  tracking to return the count; parent tracking is needed to reconstruct a path.
- **Limit:** Ordinary BFS does not guarantee minimum total cost when edge
  costs differ. DFS may find a shortest path by chance, but its first success
  is not guaranteed to be shortest.

### Reachability allows either traversal order

For a finite graph, both DFS and BFS correctly answer whether a target is
reachable when they explore all relevant moves and handle repeated states.
Changing the order can change which path is found first, but not whether a
path exists.

| Traversal | Kotlin deque operations | Order |
| --- | --- | --- |
| DFS with a stack | `addLast`, `removeLast` | Last in, first out |
| BFS with a queue | `addLast`, `removeFirst` | First in, first out |

With a stack, push right then left to explore left first. With a queue, adding
right then left processes right first among those newly added neighbors.

### Visited prevents cycles and repeated expansion

If reaching a state again offers the same future choices, explore it once.
For example, `[1,1]` in Jump Game III permits `0 → 1 → 0 → ...`; visited stops
this cycle. Recursive DFS must mark before exploring neighbors.

For basic reachability, keep marks permanently instead of unmarking on return.
Returning false for a repeated visit means “skip this exploration,” not “this
state has been proved unable to reach the target.” A visited array is not a
cache of per-state answers.

**Condition:** The visited key must represent the full state. If future options
depend on remaining resources or another part of the history, an index alone
may be insufficient. Path-enumeration tasks may also need different rules.

### Marking when adding versus when removing

Marking valid states before adding them to a stack or queue prevents duplicate
pending entries. In BFS, first discovery gives the shortest distance, so record
the distance and parent then, without overwriting them on later encounters.

Marking when removing is also correct for the reachability code in Jump Game
III, provided repeated entries are skipped before expansion. Duplicates can
be pending simultaneously. Its O(n) bound still holds because each index
expands once and adds at most two entries.

Source example: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Complexity: count transitions as well as states

“Each state is visited once” is only part of the time analysis. Also count the
work performed at that state, including neighbor generation.

- Graph traversal with adjacency lists takes O(V + E): V vertices and E edges.
- In Jump Game III, there are n indices and at most 2n edges, so time is O(n).
  For the saved iterative implementation, at most `1 + 2n` entries are pushed,
  including invalid and duplicate entries. Deque operations are amortized O(1).
- In range-marking Jump Game I DP, one index may examine O(n) destinations;
  processing each index once can therefore still take O(n²) time.

Include the visited array and pending stack/queue in space complexity. Include
the runtime call stack for recursion: a depth-n path can require O(n) space.

## Iteration, recursion, and DP are different concepts

**Iterative** describes execution with loops; **recursive** describes functions
calling themselves. DFS can use either recursive calls or an explicit stack.
Both versions can have O(n) space even though the iterative version avoids
deep JVM call-stack usage. An explicit stack still needs memory.

**Dynamic programming** stores and reuses subproblem results. It can be
recursive or iterative. Replacing recursive DFS with a loop does not by itself
turn the solution into DP.

For recursive existence searches, `dfs(left) || dfs(right)` short-circuits:
a true left result skips the right call and success propagates through callers.
This improves early stopping but does not replace visited or prevent cycles.

## State compression requires a structural guarantee

If all reachable positions form a prefix, store its endpoint instead of a
Boolean for every position. Before extending the boundary, check that the
position providing the extension is itself reachable.

In Jump Game I, “maximum jump length” allows every shorter jump, making
reachability a continuous prefix. Its update is:

```text
if current <= farthest:
    farthest = max(farthest, current + nums[current])
```

Exact jumps can leave holes: for `[2,0,2]` starting at 0, Jump Game III reaches
index 2 but not index 1. A farthest boundary cannot represent that distinction.

Before compressing state, ask: **Could two situations with the same summary
require different future decisions? Which input guarantee rules that out?**

Source examples: [Jump Game I](../leetcode/55_jump_game/EXPLANATION.md) and
[Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).
