# Jump Game III: deriving DP, then improving it to reverse BFS

This records the reasoning from our DP discussion through your final O(n)
implementation. The earlier [DFS/BFS notes](../EXPLANATION.md) explain forward
exploration. Your final reverse-search code is saved in [1306.kt](1306.kt),
with formatting normalized and the algorithm unchanged.

The goal is to determine whether a zero-valued index is reachable from `start`.
From index i, legal destinations are `i - arr[i]` and `i + arr[i]` within the
array. Jump lengths are exact, values are nonnegative, and the input is unchanged.

## Solution evolution

### 1. Derive a state from the remaining problem

Begin with: “If I pause a sequence of moves here, what must I know to continue?”
With no jump limit, the current index is enough. Different paths reaching the
same index have identical future choices. A natural state definition is:

```text
canReachZero[i] = whether a zero is reachable starting at index i
```

Distinguish the state (the current situation, i) from its value (the Boolean
answer to the remaining problem). Do not choose array dimensions before
deciding what question each entry answers.

Its natural recurrence depends on the two destinations. However, `[1,1]`
produces dependencies `0 → 1 → 0`. The state captures sufficient information,
but ordinary memoization or a single table pass has no acyclic evaluation order.
Memoizing after recursive calls return does not by itself stop this cycle.

**What to say:** “The index describes the remaining reachability question,
but cyclic dependencies prevent a straightforward bottom-up evaluation.”

### 2. Create easier questions with a jump budget

Ask: “Can I answer the question with no jumps, then with one jump, then two?”
This derives a second dimension instead of guessing one:

```text
dp[k][i] = starting at index i, can I reach any zero-valued index
           using at most k jumps?
```

Here k is the remaining budget, not a position or a jump length. We introduce
it to order the subproblems. If the original problem imposed a jump limit,
remaining budget would also be necessary information: at index 0 of `[1,1,0]`,
two remaining jumps succeed but one does not. Those situations cannot share
the same state under a limited-budget contract.

This gives two reasons for adding a state dimension:

- Future choices or answers differ depending on that information.
- A restricted version gives a sequence of easier subproblems to compute first.

**State test:** Can two situations with the same proposed state have different
future possibilities or answers? If so, identify the missing distinction.

### 3. Derive the base case and transition

With zero jumps, you cannot leave the current index:

```text
dp[0][i] = (arr[i] == 0)
```

For k >= 1, either you are already at zero or one legal move leaves a problem
with one fewer jump available:

```text
left  = i - arr[i]
right = i + arr[i]

dp[k][i] =
    (arr[i] == 0)
    OR (left >= 0 AND dp[k - 1][left])
    OR (right < n AND dp[k - 1][right])
```

Nonnegative jump lengths make those one-sided bounds sufficient here. Index 0
is valid: the left check is `>= 0`, not `> 0`. `[0,1]`, start 1, exposes that bug.

“At most k” permits using zero jumps. Therefore a zero-valued starting index
is true for every budget. In this particular problem, the explicit zero test
is computationally redundant after initialization: both moves from a zero
point back to itself, carrying its true value forward. Keeping the test makes
the meaning of the state clear.

**What to say:** “One jump spends one unit of budget, so every transition uses
the previous budget row. Either legal move succeeding is enough.”

### 4. Choose an evaluation order and a finite budget bound

Initialize the whole row for k = 0 separately. Then compute budgets in increasing
order, with k outside and i inside. The transition reads row k - 1, so using it
at k = 0 would incorrectly access row -1.

For `[1,1,0]`:

| Budget | Index 0 | Index 1 | Index 2 |
| --- | --- | --- | --- |
| 0 | false | false | true |
| 1 | false | true | true |
| 2 | true | true | true |

The original question has no explicit budget. Why is n - 1 sufficient?
If a successful path repeats an index, remove the section between those visits:

```text
Original: start → a → b → c → a → d → zero
Shorter:  start → a → d → zero
```

The available moves at a are identical on both visits. Repeatedly removing
cycles leaves at most n distinct indices, hence at most n - 1 jumps. The
starting index costs no jump. This is an existence bound: a successful path
may loop, but a successful path without loops also exists.

The bound is not n / 2. `[1,1,1,0]`, start 0, needs three jumps with no repeats.
More jumps reaching new indices can help; returning to an old index adds no
new options in this problem.

Use an n-by-n Boolean table and return `dp[n - 1][start]`. For n = 1, the base
row already answers the question. Time and space are O(n²), making this an
educational formulation rather than a practical choice for the largest inputs.

**What to say:** “Removing cycles bounds a necessary successful path by n - 1
jumps. I compute each budget from the preceding row, then read the start state.”

### 5. Reduce space by keeping only the previous row

Row k reads only row k - 1, so keep `previous` and `current` arrays. Compute
every current entry from the unchanged previous array, then swap the arrays.
Overwrite every entry before reusing an old array as the next output row.

Space becomes O(n), but time is still O(n²). Reducing the number of stored
rows does not reduce the number of state updates.

Updating a single array in place breaks the precise budget interpretation.
For `[0,1,1]`, initially `[true,false,false]`, scan left to right:

1. Index 1 becomes true by reading index 0.
2. Index 2 reads the newly updated index 1 and also becomes true.

One scan has discovered a two-jump path. This is not an infinite loop; it is
mixing budget layers. Separate arrays prevent that mixing.

**What to say:** “Only the previous row is needed, so I can save space. I must
keep that row unchanged if I want each iteration to represent exactly one
additional unit of allowed budget.”

### 6. Reinterpret the in-place array as reachability propagation

Your in-place implementation still computed eventual reachability correctly,
but its state meaning changed:

```text
dp[i] = we have established that a zero is reachable from i
```

Initialize only zero-valued indices to true. A zero remains true through its
self-edge. Other entries turn true when a legal destination is true. These
truths never revert: each has a chain of supporting moves to a zero. Updates
can propagate through several edges in one scan, depending on scan order.
After n - 1 full scans, every successful simple path has been covered.

Before propagation finishes, false means “not yet established,” not “proved
impossible.” Cycles with no path to a zero never gain a true seed and stay false.

This is repeated Boolean propagation, also called fixed-point iteration. It
uses O(n) space but still O(n²) worst-case time. Stopping when `dp[start]` becomes
true, or when a whole scan changes nothing, can help but does not remove that
worst case. The unresolved cost is repeatedly scanning unaffected indices.

**What to say:** “A scan spreads known reachability, but most checks may find
no new information. I want to process only states affected by a new true value.”

### 7. Find exactly who depends on a changed result

If there is a legal move `a → b` and dp[b] becomes true, dp[a] can become true:

```text
a → b → ... → zero
```

We need the indices that can jump TO b, not the places b can jump TO.
`b - arr[b]` and `b + arr[b]` describe outgoing moves. They do not find incoming
moves because a jump's length comes from its starting index.

For `[2,1,0]`, both `0 + arr[0]` and `1 + arr[1]` equal 2. But the formulas
using arr[2] only produce 2. Record each legal edge in reverse:

```text
Original move i → destination
Record: predecessors[destination].add(i)
```

Thus `predecessors[2]` includes 0 and 1. Your implementation also includes
index 2 twice because its zero-length left and right moves both reach itself.
That duplication is harmless.

`predecessors[b]` means “indices that can jump directly to b,” or informally
`canJumpHereFrom[b]`. An array of mutable lists is sufficient:

```kotlin
val predecessors = Array(n) { mutableListOf<Int>() }
```

It is not an n-by-n table. One destination can have many predecessors, but
across all lists there are at most 2n entries because each source contributes
at most two legal edges.

### 8. Queue only newly established truths

After building the reverse lists:

1. Set dp[i] true for every zero-valued index and enqueue its index i.
2. Remove a known-true index a from the queue.
3. For each b in predecessors[a], if dp[b] is false, set it true and enqueue b.
4. Continue until the queue empties; return dp[start].

The queue holds indices, not Boolean values. We do not skip a false predecessor:
the edge to a just gave us evidence to make it true. We skip an already-true
predecessor because it has already been scheduled or processed.

Enqueuing b allows the discovery to spread to its own predecessors. Each index
changes from false to true once, so it is enqueued at most once. Your code's
`addFirst` with `removeLast` is FIFO, just like `addLast` with `removeFirst`.

This is multi-source BFS on the reversed graph. We reached it by optimizing
the propagation schedule of the recurrence. The name matters less than the
reason: process only dependents affected by changed information.

**What to say:** “I record incoming edges, seed a queue with all zeros, and
propagate true backward. Every index changes once and every edge is examined
at most once, so the total work is linear.”

| Method | Time | Auxiliary space | What improved |
| --- | --- | --- | --- |
| Budget DP, full table | O(n²) | O(n²) | Makes cyclic position dependencies acyclic in the budget |
| Budget DP, two rows | O(n²) | O(n) | Removes unused rows |
| In-place repeated propagation | O(n²) | O(n) | Changes semantics; does not fix repeated scans |
| Predecessor queue | O(n) | O(n) | Processes only newly affected states |
| Earlier forward DFS/BFS | O(n) | O(n) | Directly explores from start without reverse lists |

The reverse method answers reachability for every starting index in one run.
For just one start, forward DFS/BFS remains simpler and can visit fewer states.

## Trace of your exact final code

Input `[4,2,3,0,3,1,2]`, start 5. Construction scans i in increasing order,
adding right before left. The resulting predecessor lists are:

```text
0: []
1: [4]
2: []
3: [1,3,3]
4: [0,5,6]
5: [2]
6: [2,5]
```

The queue below is shown first to last: add on the left, remove on the right.
Initially only dp[3] is true and the queue is `[3]`.

| Iteration | a removed | Newly true and enqueued, in order | Queue afterward | True indices afterward |
| --- | --- | --- | --- | --- |
| 1 | 3 | 1; skip the two already-true self-edges | `[1]` | `{1,3}` |
| 2 | 1 | 4 | `[4]` | `{1,3,4}` |
| 3 | 4 | 0, 5, 6 | `[6,5,0]` | `{0,1,3,4,5,6}` |
| 4 | 0 | None | `[6,5]` | `{0,1,3,4,5,6}` |
| 5 | 5 | 2 | `[2,6]` | `{0,1,2,3,4,5,6}` |
| 6 | 6 | None; 2 and 5 are already true | `[2]` | `{0,1,2,3,4,5,6}` |
| 7 | 2 | None | `[]` | `{0,1,2,3,4,5,6}` |

The queue is empty and dp[start] = dp[5] = true. The saved code deliberately
finishes all propagation, even though success for start was known earlier.

## Correctness, termination, and costs

Invariant: every true dp entry has a valid original-direction path to a zero.
Every true index has been enqueued exactly once, and each dequeued index has
had all its predecessors considered.

Initially zero-valued indices satisfy the invariant without making a jump.
If b is a predecessor of true index a, the original edge `b → a` followed by
a's known path proves b true. Therefore propagation never creates a false positive.

For completeness, take a successful path to zero and work backward along it.
The final zero is seeded. Processing each discovered vertex marks its predecessor
on that path. Eventually the starting vertex is marked. If the queue empties
with dp[start] false, no successful path exists.

Every false-to-true transition schedules one index; there are at most n of
these. Thus the queue terminates. Constructing lists examines 2n candidate
moves, and processing all lists examines at most 2n stored entries. With
amortized O(1) list append and deque operations, time is O(n). The lists,
Boolean array, and queue together use O(n) auxiliary space. No recursion is used.

## Interview explanation and recall practice

“I first defined reachability with at most k jumps to make dependencies acyclic.
Cycle removal bounds the budget by n - 1, giving a quadratic DP. Keeping only
the previous row saves memory but not time. To remove repeated scans, I noticed
that a newly true state only affects indices that can jump to it. I build those
predecessor lists, seed all zero-valued indices, and propagate true through a
queue. Each index is queued once and there are at most two edges per index,
so time and space are O(n).”

Try answering without looking:

1. How can two histories expose information missing from a proposed state?
2. Why was i sufficient for unlimited reachability, yet k useful for this DP?
3. Why does “at most k” allow immediate success without spending all k jumps?
4. Why does removing cycles imply n - 1, rather than n / 2, jumps suffice?
5. Why does in-place updating break budget semantics without necessarily
   breaking eventual reachability?
6. For an edge `i → j`, which predecessor list receives which index?
7. Why is a false entry not a reason to skip it when new evidence arrives?
8. What justifies one enqueue per index here? Would a repeatedly improving
   numeric score necessarily have the same bound?

Next, rebuild the queue implementation from “who depends on this changed
answer?” and trace `[2,0,2]` to verify that unreachable zeros do not make every
index true. Reusable lessons are in the
[concepts cheatsheet](../../../study-notes/algorithm-concepts-cheatsheet.md).

## Local verification

Run `bash leetcode/1306_jump_game_iii/dp_to_reverse_bfs/run.sh` from the repository
root. The runner checks examples, cycles, unreachable targets, and a long path,
then compares this implementation against the full budget DP on all arrays of
lengths 1 through 5 with legal values 0 through n - 1, for every starting index.
Passing these checks supports, but does not replace, the correctness proof.
