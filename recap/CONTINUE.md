# Recap continuation — 2026-10-13

## Current focus

DP is paused at the user's request. Continue BFS, DFS, and graph theory.
Latest completed work: [AcWing 1134](graph/bfs/acwing-1134/EXPLANATION.md),
counting shortest paths in an undirected unweighted multigraph from node 1,
modulo 100003. User understands adjacency lists, dist=-1 as discovery state,
source count 1, FIFO deque, parallel edges, and why self-loops do not contribute.
Their attempt needed m input, whole-sum modulo, and per-node output fixes.
Saved corrected code preserves addFirst/removeLast and collection storage.

## Next exercise

Current next practice: LeetCode 1971 — Find if Path Exists in Graph. The user
specifically wants explicit adjacency-list traversal, so use this edge-list
reachability problem next. Nodes are 0..n-1; return Boolean for source to
destination. No solution supplied yet. User explicitly deferred LeetCode
1976 until after learning Dijkstra.

LeetCode 1091 is now completed: the learner implemented eight-direction BFS,
then reused the input grid as the distance/visited storage. Saved in
graph/bfs/leetcode-1091-shortest-path-in-binary-matrix with explanation and
208 passing local checks. Keep their addFirst/removeLast FIFO convention.
Grid zeros mean undiscovered; positive values are blocked or discovered.
This mutates the input and removes a separate matrix, but worst-case queue
space remains O(n²). The AcWing folder has grid/state BFS in 1131 but no
simple grid BFS starter; 1131's keys and doors were deferred until later.
LeetCode 1976 has the closer shortest-path-counting objective but weighted
roads, so defer it until Dijkstra. Neither is an identical AcWing match.

## Preferences

- Explain in English, in small focused pieces; avoid information overload.
- Recaps are direct explanations, not compulsory Socratic checkpoints.
- Preserve the user's variable names and implementation when reviewing.
- User prefers Java Scanner for console practice and Kotlin collections for
  adjacency lists; no manual array-linked adjacency implementation.
- User also uses IntArray for DP and judge APIs; preserve their chosen code.
- Use judge-number-and-title folders. Save requested code, reasoning,
  correctness, time/space complexity, and runnable tests in the problem folder.
- Commit only when requested. Read AGENTS.md and relevant local skills.

## Recent completed background

AcWing 104 / LeetCode 462 median; 1017 / LeetCode 300 quadratic LIS;
1014 / LeetCode 1671 mountains; 1016 discussion / LeetCode 1626 maximum score;
1012 / LeetCode 354 pair ordering. User completed O(n log n) LIS using tails
and Russian Doll Envelopes with width ascending, equal-width height descending.
Those implementations and explanations are saved. Last known commit before
this turn was 6f687a3; tails/envelope changes were still uncommitted when this
turn began. Inspect git status rather than assuming a clean tree.

Resume prompt: “Read recap/CONTINUE.md and continue BFS practice with me.”
