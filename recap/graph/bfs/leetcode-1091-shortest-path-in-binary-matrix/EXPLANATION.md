# LeetCode 1091 — Shortest Path in Binary Matrix

[Official problem](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/)
· [Your in-place Kotlin solution](Solution.kt)

Your implementation is preserved with formatting and direction comments
cleaned up; Pair(a,b) and a to b were made consistent. The parameter name
dist is intentional: the supplied grid is reused to store distances.

## Contract and graph representation

Find a shortest path from (0,0) to (n-1,n-1) through zero-valued cells,
moving in any of eight directions, including diagonals. Return the number
of visited cells in the path, or -1 if no path exists. The grid is square,
nonempty, and has n <= 100. No explicit adjacency list is needed: each
traversable cell is a node and legal neighboring moves are its edges.

## Solution evolution: reuse the grid

Your earlier version used a separate distance matrix initialized to -1.
This version stores distances in the input itself:

- 0: open and undiscovered.
- 1: originally blocked, or the visited starting cell.
- 2 or more: a discovered open cell with that path length.

The shared value 1 is safe: both walls and the visited start should be
excluded from future discovery. Only cells with value 0 are enqueued.
Originally blocked cells are never queued, so a dequeued cell's value is
always a valid distance. Check the starting cell before overwriting it.

This changes the input matrix. Calling the function again on the same
matrix is not equivalent to solving the original grid again; use a fresh
copy if needed. It removes the separate distance-matrix allocation, but
does not reduce the overall worst-case space bound because the queue remains.

## BFS process and correctness

Set the starting distance to 1 because path length counts cells, not edges.
Your addFirst/removeLast combination is FIFO. For each removed cell,
generate the eight neighbors, reject out-of-bounds positions, and enqueue
only zeros. Record distance as the current distance plus one.

The enqueue and distance assignment execute consecutively, before another
neighbor or queue item is processed, so your code marks discovery in time
to prevent duplicate enqueues. Assigning the distance first is also valid.

Every move costs one step. FIFO processing explores all cells at one distance
before cells at the next distance, so first discovery establishes a shortest
path. Each cell is discovered at most once. The first dequeue of the goal
therefore returns the shortest path length. If the queue empties, no reachable
unprocessed cells remain, so the goal is unreachable and -1 is correct.

A blocked goal need not be separately checked: it never passes the zero
test and cannot enter the queue. An initial endpoint check could reject it
earlier as an optional optimization. A one-cell open grid returns 1; a
one-cell blocked grid returns -1.

## Small trace

```text
Input:       After start:  After discovering diagonal goal:
0 1          1 1          1 1
1 0          1 0          1 2
```

Process (0,0), discover (1,1), then dequeue (1,1) and return 2. The two
blocked neighboring cells do not prevent this diagonal move under the
problem's eight-direction movement rule.

## Complexity and running locally

Time is O(n²): each of at most n² cells checks eight neighbors once.
Extra space is O(n²) in the worst case for the queue. Directions use O(1)
space, and no separate visited or distance matrix is allocated.

Run `bash run.sh` from this folder. Tests include the official examples,
single cells, blocked endpoints, a disconnected grid, and random comparisons
against a separate-distance BFS. Local tests do not claim online acceptance.
