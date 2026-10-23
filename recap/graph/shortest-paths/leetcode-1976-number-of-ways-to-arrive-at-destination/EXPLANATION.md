# LeetCode 1976 — Number of Ways to Arrive at Destination

[Problem](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
· Medium. Connected undirected graph with n <= 200, nodes 0..n-1, unique
endpoint pairs, and strictly positive road times up to 10^9. Count shortest
routes from 0 to n-1 modulo 1,000,000,007.

## Solution evolution

The learner's [743 heap Dijkstra](../leetcode-743-network-delay-time/EXPLANATION.md)
finds shortest distances. This exercise adds shortest-route counts, extending
the counting idea from [AcWing 1134](../../bfs/acwing-1134/EXPLANATION.md).
The supplied final implementation is preserved in Solution.kt, with formatting
and the missing java.util.PriorityQueue import added.

dist[v] is the smallest route cost found so far. cnt[v] counts routes achieving
that distance, modulo MOD. Initialize dist[0] = 0 and cnt[0] = 1: one empty route
starts at the source. Edge stores a single road; State stores a node and a
snapshot of its distance from the source. Add every road in both directions.

## Replace versus add

For candidate = dist[node] + weight:

| Comparison | Distance update | Count update | Heap update |
|---|---|---|---|
| candidate < dist[v] | Replace distance | cnt[v] = cnt[node] | Insert new State |
| candidate == dist[v] | None | Add cnt[node], modulo MOD | None |
| candidate > dist[v] | None | None | None |

The initial attempt added counts even for a shorter route, omitted equal-distance
contributions, used Int distances, and returned the distance. The final version
corrects all four. Old counts belong to the old distance and must be discarded
when a shorter route is found. The answer is cnt[n-1], not dist[n-1].

## Small trace

Take undirected roads 0–3 (10), 0–1 (1), 0–2 (1), 1–3 (2), 2–3 (2).

| Process | Effect on destination 3 |
|---|---|
| 0 | dist[3] = 10, cnt[3] = 1 |
| 1 | Cheaper route: dist[3] = 3, cnt[3] = 1 |
| 2 | Equal route: dist[3] = 3, cnt[3] = 2 |
| 3 at distance 3 | Count is complete; no improving outgoing route |
| Old entry for 3 at distance 10 | Skip outdated entry |

Nodes 1 and 2 may be processed in either order; the result remains 2.

## Why the counts are correct

Dijkstra finalizes distances in increasing order because road weights are
nonnegative. Here weights are strictly positive: every predecessor on a
shortest route to v has a strictly smaller shortest distance than v. Therefore
all shortest-route contributions reach v before its current heap entry is
processed. An equal-distance update needs no new heap entry.

Every shortest route to v has one final predecessor. Counting routes through
each predecessor adds disjoint groups; extending each shortest route to that
predecessor by its road to v supplies exactly that group's routes. A better
distance discards all routes to the previous distance; an equal distance adds
another group. Starting with the source's one empty route proves the count
invariant in processing order. Modulo arithmetic preserves these sums.

This simple counting argument relies on strictly positive weights. Although
Dijkstra distances support zero weights, the same counting update order cannot
be assumed correct for arbitrary graphs with zero-weight edges.

Stale heap entries have distance > dist[node] and are skipped. Strict improvement
is the only case that inserts a new entry. No separate visited list is needed.

## Types and complexity

Use Long for dist and State.distance: path sums can exceed Int. Edge.weight can
stay Int because adding it to Long produces Long. Only finite distances enter
the heap. cnt stays Int: two reduced counts sum to at most 2,000,000,012, within
Int range. The final modulo is redundant but harmless and preserved.

For this simple graph, time is O((n + m) log n), space O(n + m). More explicitly,
the lazy heap can hold O(m) entries and takes O(n + m log(m + 1)) time.

## Interview wording

“I run Dijkstra from node zero and track the number of routes achieving each
tentative distance. A shorter route replaces both distance and count; an equal
route adds to the count. Positive road times ensure every shortest predecessor
is processed before its destination, so the count is complete when that node
is processed. I use Long distances and reduce counts modulo 1,000,000,007.”

## Local checks

Run `bash recap/graph/shortest-paths/leetcode-1976-number-of-ways-to-arrive-at-destination/run.sh`.
Checks include official examples, one node, equal shortest routes with stale
entries, large distances, and repeated branching that exercises modulo reduction.
