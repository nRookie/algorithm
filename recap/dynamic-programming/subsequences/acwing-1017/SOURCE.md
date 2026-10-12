# AcWing 1017 source

Preserved original: [1017.cpp](../../../../acwing/dp/line/lineup/1017.cpp).
The [original statement](https://www.acwing.com/problem/content/1019/) could
not be retrieved on 2026-10-12. The user subsequently supplied its text,
confirming the contract used by the conversion:

- Buildings stand in a line, with distinct heights in arrangement order.
- Kid may start on any building and choose either horizontal direction.
- He cannot change direction and can move only to a strictly lower building.
- Maximize the number of visited rooftops, including the starting building.
- Input has K test cases; each contains N followed by N distinct heights.
- Output one maximum count per case. Bounds: `1 <= K <= 100`, `1 <= N <= 100`.

The supplied statement gives no numeric height bound; the conversion retains
the original C++ Int height representation. The local sample is illustrative,
not a claimed official sample. Duplicate-height tests are extra robustness
checks outside the distinct-height contract.

The Kotlin conversion preserves f, g, res, strict comparisons, and scan order.
Indexes change from 1..n to 0 until n. Heights and DP states use Lists rather
than fixed-size C++ arrays; input uses the learner's preferred Java Scanner.

Related judge: [LeetCode 300 — Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/description/),
Medium, public statement verified. It requests a strictly increasing
subsequence in the original left-to-right order. Same DP technique, different
objective: do not submit the two-direction AcWing result to LeetCode 300.
