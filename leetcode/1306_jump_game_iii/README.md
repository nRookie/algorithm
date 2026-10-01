# 1306. Jump Game III — Kotlin

Your iterative DFS implementation is in [1306.kt](1306.kt). Copy only that file
into LeetCode. See [EXPLANATION.md](EXPLANATION.md) for solution evolution,
the exact stack trace, correctness, complexity, and rehearsal questions.

For the later DP exploration, read
[From DP to reverse BFS](dp_to_reverse_bfs/EXPLANATION.md). It records state
derivation, budget DP, space compression, in-place propagation, and the O(n)
predecessor-queue method. Your final alternative implementation is saved in
[dp_to_reverse_bfs/1306.kt](dp_to_reverse_bfs/1306.kt); compile it separately
because both submissions define `Solution`.

Run the reverse-BFS checks with:

```sh
bash leetcode/1306_jump_game_iii/dp_to_reverse_bfs/run.sh
```

Run from the repository root:

```sh
bash leetcode/1306_jump_game_iii/run.sh
```

The separate `Main.kt` runner checks the three examples, starting at zero,
a cycle with no zero, moving left, an unreachable zero, input preservation,
and a 50,000-index path. Build artifacts stay in the ignored `.build/` folder.
