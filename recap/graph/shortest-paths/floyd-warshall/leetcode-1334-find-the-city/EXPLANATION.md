# LeetCode 1334 — Find the City With the Smallest Number of Neighbors at a Threshold Distance

[Problem](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)
· Medium. Undirected positive-weight graph, cities 0..n-1, n <= 100,
weights and threshold <= 10000. Return the city with the fewest other cities
reachable within the threshold; ties choose the greatest city index.

## Learner's explanation, polished

“I use Floyd–Warshall to compute shortest distances between every pair of cities.
For each city, I count other cities whose shortest distance is at most the
threshold. I find the minimum count, then scan city indices in increasing order.
Whenever a city's count equals the minimum, I replace the answer. The last match
is therefore the greatest qualifying city index.”

The implementation is preserved, with formatting and explicit braces added.
No algorithmic corrections were necessary.

## Solution evolution and state

Repeated single-source shortest paths can compute all pairs. Here the small
number of cities permits a matrix DP with O(n³) time and O(n²) space.
Initialize the diagonal to zero, direct edges in both directions to their
weights, and missing routes to Int.MAX_VALUE. Edge pairs are unique in this
problem, so assignment rather than min on input is valid.

Before processing k, dist[i][j] is the best route allowing intermediate nodes
0..k-1. After processing k, intermediate nodes 0..k are allowed. Endpoints i
and j are unrestricted. This is not Dijkstra finalization: later stages may
improve entries involving earlier nodes.

## Correctness

An optimal route either avoids k, retaining the old answer, or passes through
k and splits into i→k and k→j. With no negative cycles, a shortest route can be
chosen without repeated vertices, so those subroutes need only earlier
intermediates. Taking their minimum establishes the next DP stage. The zero
diagonal keeps row k and column k unchanged during that stage, making in-place
updates safe. Put k outermost. After every stage, all intermediates are allowed.

Guard both subroutes before adding: infinity is not a real distance. Int is
sufficient here; a simple shortest path costs at most 99*10000, and finite
candidate sums remain safely within Int. Never rely on that bound to permit
adding Int.MAX_VALUE itself.

ans[city] counts exactly the other cities meeting the inclusive threshold.
minimum is the smallest count. The increasing final scan overwrites res for
every match, proving the required greatest-index tie break.

Example: edges 0–1 (3), 1–2 (1), 1–3 (4), 2–3 (1), threshold 4.
Floyd discovers 1→2→3 costs 2, improving the direct cost 4. Counts are
[2,3,3,2], so the final scan matches city 0, then city 3, and returns 3.

## Complexity and practice

Time O(n³ + m), conventionally O(n³) for this simple graph. Counting takes
O(n²) additional time. Total space O(n²).
See the [interactive stage visualization](../VISUALIZATION.html).

Recall: Why must k be outermost? Why can an earlier distance improve later?
Why exclude city itself and use <= rather than <?

Run `bash recap/graph/shortest-paths/floyd-warshall/leetcode-1334-find-the-city/run.sh`.
