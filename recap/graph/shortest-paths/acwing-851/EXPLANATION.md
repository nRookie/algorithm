# AcWing 851 — SPFA shortest path

## Problem contract

Source: the problem statement and Kotlin attempt supplied by the learner.
Read n m, then m directed edges a b weight. Nodes are numbered 1..n.
Find the shortest distance from 1 to n; print `impossible` if unreachable.
Parallel edges and self-loops are allowed; weights may be negative.
The statement guarantees no negative cycles. n,m <= 100000 and |weight| <= 10000.

## Solution evolution

Repeated full-edge relaxation (Bellman–Ford) can scan all m edges over n-1
passes, even if few distances changed. SPFA schedules only vertices whose
improvements need propagating, using a FIFO queue and adjacency lists.
It can save work but retains the O(nm) worst-case bound. It is not Dijkstra:
removing a vertex does not finalize its distance, and it may be queued again.

## Learner's implementation and corrections

Main.kt preserves the learner's names, IntArray distances, BooleanArray queue
membership, Java Scanner, and collection adjacency lists. Each directed edge
is stored once; parallel edges remain in the list. add plus removeFirst is FIFO.

Two corrections were required:

1. Replace `inQueue[1] = false` after removal with
   `inQueue[currentNode] = false`. Otherwise removed nodes other than 1 remain
   marked as waiting and cannot re-enter after a later improvement.
2. Replace `return dist[n]` from main with printing either the distance or
   `impossible`. Kotlin main returns Unit.

The condition `inQueue[next] != true` was simplified to `!inQueue[next]`.
No other algorithm change was needed.

dist[u] is the best route cost found so far. inQueue[u] means currently waiting,
not ever visited. On removal, clear the flag. On a strict improvement, always
update dist; enqueue only if the node is not already waiting. Its pending turn
will read the latest distance. Only reachable nodes enter the queue, so infinity
is never used in addition. Int is suitable for these bounds; a shortest simple
path has at most n-1 edges. Long is preferable for larger general constraints.

## Trace and bug counterexample

Use directed edges in this input order: 1→2 (10), 1→3 (1), 2→4 (1), 3→2 (1).
The queue below is shown next-to-process first.

| Removed | Change | Queue afterward |
|---|---|---|
| Initialize | dist[1]=0 | [1] |
| 1 | dist[2]=10, dist[3]=1 | [2,3] |
| 2 | dist[4]=11 | [3,4] |
| 3 | dist[2]=2; enqueue 2 again | [4,2] |
| 4 | No outgoing edges | [2] |
| 2 | dist[4]=3; enqueue 4 again | [4] |
| 4 | No outgoing edges | [] |

The original flag bug prevents the second processing of 2 and incorrectly
leaves dist[4]=11. The corrected answer is 3.

## Correctness and termination

Every finite distance is the cost of an actual route: zero is the empty route,
and relaxation extends a known route by one edge. It cannot underestimate the
true shortest distance.

Every improvement is propagated: either its node is newly enqueued or an
existing pending entry will use its updated distance. When the queue is empty,
every reachable edge satisfies dist[v] <= dist[u] + weight(u,v). Applying these
inequalities along a shortest path proves dist[v] is at most that path's cost.
Together with the first observation this proves equality. Unreachable vertices
retain infinity and yield `impossible`.

With no negative cycles, reachable shortest distances have finite lower bounds.
After first discovery, each successful update strictly decreases an integer
distance. Only finitely many decreases are possible, so processing terminates.
No negative-cycle detection is needed for this problem's guaranteed input.

## Why worst-case time is O(nm)

Processing u scans its outgoing edges. Processing each vertex once would scan
m edges, but a vertex can re-enter after its distance improves.

For this FIFO implementation, conceptually divide processing into rounds. At
the start of a round, record the number of pending entries and process exactly
those entries. Newly appended entries belong to the next round. inQueue ensures
that a vertex appears at most once in a round. Thus a round scans at most m
edges, plus O(n) bookkeeping for the reachable vertices.

A shortest path can be chosen with at most n-1 edges: removing any repeated-node
cycle cannot increase cost because there are no negative cycles. Along such a
path, a correct distance advances by at least one edge per round. Once a
predecessor is correct, it either already propagated that value or is pending
for processing by the next round. The next vertex is updated then, possibly
earlier. After O(n) rounds all shortest distances have propagated, and one
final round can drain pending work without further changes.

If r vertices are reachable, each round processes at most r entries. For r>1,
at least r-1 edges are needed to reach them, so per-round bookkeeping is also
O(m) (m>=1 in the statement). Thus O(n) rounds times O(m) work gives O(nm).
This argument is for FIFO scheduling, not an arbitrary stack discipline.
inQueue prevents duplicate simultaneous entries, not repeated processing over
time. Queue/dist/flags use O(n) space; graph uses O(n+m), total O(n+m).

At the largest constraints this worst-case bound is large; these local tests
check correctness, not a guarantee of judge runtime with Scanner on all inputs.

## Interview wording

“I keep nodes with improved distances in a FIFO queue. When a node is removed,
I relax its outgoing edges and schedule each improved neighbor unless it is
already waiting. Queue membership is temporary, so nodes can return later.
When no work remains, no reachable edge can improve a distance. Without negative
cycles the process terminates; worst-case time is O(nm), space O(n+m).”

Recall: Why clear the removed node's flag? Why update a neighbor that is already
queued? Why does processing a node once not suffice?

## Related LeetCode practice

[743 — Network Delay Time](https://leetcode.com/problems/network-delay-time/)
(Medium, public statement) is the closest direct practice: redo your existing
solution using SPFA and a FIFO queue. It has a directed weighted graph and
nodes 1..n, but starts at k and returns the maximum distance, or -1 if any node
is unreachable. Its nonnegative weights do not exercise negative-edge support.
This is an adaptation, not an identical contract. Existing solutions are in
[the 743 folder](../leetcode-743-network-delay-time/EXPLANATION.md); leave the
new SPFA implementation for independent practice.

Practice completed: the learner's [743 SPFA implementation](../leetcode-743-network-delay-time/SpfaSolution.kt)
is now saved with its queue-membership corrections in the judge-specific folder.

## Run

`bash recap/graph/shortest-paths/acwing-851/run.sh` runs the custom trace above.
Use `run.sh stdin < input.txt` for your own input, or `run.sh test` for checks.
