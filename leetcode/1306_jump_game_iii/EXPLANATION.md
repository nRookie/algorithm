# 1306. Jump Game III

Starting at `start`, determine whether any reachable index has value zero.
From index `i`, the only possible destinations are `i - arr[i]` and
`i + arr[i]`, provided they are inside the array. Jump lengths are exact.
The array is nonempty, values are nonnegative, and `start` is a valid index.
The input need not change, and the output does not need to include a path.

Your final iterative DFS is saved in [1306.kt](1306.kt), with only whitespace
normalized. It preserves your variable names, marking on removal, and push order.

## Solution evolution

### 1. Model the legal moves

Each index is a graph vertex with at most two outgoing edges. For the example:

```text
index:  0  1  2  3  4  5  6
value:  4  2  3  0  3  1  2
start: 5
successful path: 5 → 4 → 1 → 3
```

Be careful to separate indices from values: `arr[5] = 1`, `arr[6] = 2`, and
index 7 is out of bounds. Never read `arr[7]`.

Naively trying both moves forever is not a correct baseline: cycles can prevent
termination. For `[1,1]`, moves can repeat `0 → 1 → 0 → ...`. A straightforward
correct search must remember which indices it has already explored.

### 2. Recursive DFS with visited and a shared result

Your first correct version used `visited` and a shared Boolean `res`. Check
bounds, skip visited indices, mark the index, then either set `res = true` at
a zero or recursively explore both destinations. Mark before recursion so a
cycle cannot re-enter an unmarked active index.

Different histories reaching the same index have the same future choices.
Exploring that index once suffices. Keep it marked permanently: this task asks
whether a target is reachable, not for enumeration of distinct paths.

The search takes O(n) time and O(n) auxiliary space, including recursion.
Setting `res = true` and returning only exits the current call; ancestors
still execute their remaining recursive calls unless explicitly stopped.

**What to say:** “I explore the two legal moves from each index. A visited array
prevents cycles and repeated exploration. If I encounter zero, the answer is true.”

### 3. Return success directly from recursive DFS

Your next version removed the need for shared result state:

```kotlin
fun dfs(current: Int): Boolean {
    if (current < 0 || current >= n) return false
    if (visited[current]) return false
    visited[current] = true
    if (arr[current] == 0) return true
    val left = current - arr[current]
    val right = current + arr[current]
    return dfs(left) || dfs(right)
}
// canReach returns dfs(start).
```

Kotlin's `||` short-circuits: a successful left branch skips the right branch.
Success propagates through the callers to the original call. The worst-case
costs remain O(n) time and O(n) space; this improves control flow and can stop
earlier, but does not improve the asymptotic bounds.

Returning false for a visited index means “skip this repeated exploration.”
It is not a cached proof that the index cannot reach zero. Its exploration is
already in progress or completed elsewhere in this traversal. `visited` is a
discovery record, not a table of per-index reachability answers.

**What to say:** “Either branch finding zero is enough, so I return their logical
OR. I still need visited because returning a Boolean does not prevent cycles.”

### 4. Your final iterative DFS

Recursive DFS uses the runtime call stack. A long path can overflow the JVM
call stack, so replace recursive calls with an explicit stack and a loop.

| Recursive DFS | Your iterative DFS |
| --- | --- |
| Call DFS on an index | Push the index with `addLast` |
| Enter a call | Pop an index with `removeLast` |
| Return from an invalid or repeated call | Skip that popped entry |
| Propagate success through callers | Return true directly from `canReach` |
| Finish every unsuccessful branch | Empty the stack and return false |

You push right first and left second, so left is popped first. This matches
the exploration order of your recursive version. An `ArrayDeque` used with
`addLast` and `removeLast` is a last-in, first-out stack.

| Variable | Meaning |
| --- | --- |
| `n` | Array length; valid indices are 0 through n - 1 |
| `current` | Candidate index just removed from the stack |
| `visited[i]` | Index i has been processed; do not expand it again |
| `stack` | Pending candidate indices, including possible invalid or duplicate entries |

Your code marks on removal. Marking valid neighbors before pushing is an
optional alternative that avoids duplicate pending entries. Your current
version is correct and linear because each expanded index pushes only two entries.

**What to say:** “I keep pending indices on an explicit stack, skip invalid or
visited entries, and expand each valid index once. This avoids deep recursion.”

| Version | Time | Auxiliary space | Main change |
| --- | --- | --- | --- |
| Recursive DFS with shared result | O(n) | O(n) | Prevent cycles with visited |
| Boolean-returning recursive DFS | O(n) | O(n) | Short-circuit and propagate success |
| Your iterative DFS | O(n) | O(n) | Use an explicit stack instead of recursive calls |

Iterative means using a loop rather than recursion. It does not mean dynamic
programming. This algorithm remains a graph traversal; DP is a separate idea
about storing and reusing subproblem results and can itself be iterative or recursive.

## Full trace of your final implementation

Use `[4,2,3,0,3,1,2]`, start 5. The stack is shown bottom to top, so the
rightmost item is removed next. Initially `stack = [5]`, visited is empty.

| Iteration | current popped | Action | stack afterward | Visited indices |
| --- | --- | --- | --- | --- |
| 1 | 5 | Mark 5; push 6, then 4 | `[6,4]` | `{5}` |
| 2 | 4 | Mark 4; push 7, then 1 | `[6,7,1]` | `{4,5}` |
| 3 | 1 | Mark 1; push 3, then -1 | `[6,7,3,-1]` | `{1,4,5}` |
| 4 | -1 | Out of bounds; continue | `[6,7,3]` | `{1,4,5}` |
| 5 | 3 | Mark 3; value is zero; return true | `[6,7]` | `{1,3,4,5}` |

The remaining stack is discarded when the function returns. There is no need
to inspect every reachable index after success has been established.

## Correctness, termination, and complexity

At the start of each loop iteration, every valid pending index is reachable
from `start`. Each visited index has already been checked for zero and, if the
search continued, its two destinations were pushed. No index is expanded twice.

Initially the stack contains only the reachable starting index. Pushing the
two destinations from a reachable index preserves reachability for valid entries.
Out-of-bounds entries are checked before any array access. Duplicate entries
can be skipped because their destinations were already scheduled. Thus a true
return always witnesses a reachable zero.

If the stack becomes empty, every reachable index has been explored. Otherwise,
take a path to an unexplored reachable index and consider its first unexplored
vertex: its explored predecessor would have pushed it, so it could not remain
unexplored after the stack was exhausted. With no zero found, false is correct.

Each index is expanded at most once and produces at most two pushes. Including
the initial start entry, there are at most `1 + 2n` pushes and therefore at most
that many pops. This both proves termination and bounds the loop work, even
though the same index may be popped repeatedly. Deque operations are amortized
O(1), giving O(n) total time. The visited array and explicit stack use O(n) space.

## Why Jump Game I's boundary no longer works

In Jump Game I, all shorter forward jumps are allowed, so reachable indices form
a prefix. Here exact jumps can leave holes. With `[2,0,2]`, start 0, only indices
0 and 2 are reachable; the zero at index 1 is not. Knowing the farthest reachable
index does not tell you that index 1 can be used.

Use [the general workflow](../../study-notes/algorithm-solving-workflow.md):
histories at the same index can still be merged, but reachable positions lack
the prefix structure needed to compress the visited array to one boundary.

## Interview rehearsal

“I model each index as a vertex with up to two outgoing moves. I explore from
start with a stack and a visited array. I skip invalid and repeated entries,
return true at a zero, and otherwise push both destinations. Every reachable
index is eventually explored unless I find success earlier. Each index expands
once with two moves, so time and auxiliary space are O(n).”

Try answering without looking at the code:

1. Why is it safe to merge different paths reaching the same index?
2. Why must recursive DFS mark an index before exploring its neighbors?
3. Why keep visited marks instead of unmarking them during backtracking?
4. Why does a Boolean return not replace visited?
5. Why is time O(n) even though an index can be pushed more than once?
6. Which destination is explored first, and what causes that order?
7. Why can an existing zero still be unreachable?
8. What resource limitation does the explicit stack address?

Next, reconstruct the iterative version from the invariant, then trace `[1,1]`
to demonstrate exactly where its cycle stops.

Problem reference: [LeetCode 1306](https://leetcode.com/problems/jump-game-iii/).
