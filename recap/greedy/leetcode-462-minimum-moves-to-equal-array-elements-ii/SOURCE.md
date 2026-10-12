# Source and judge mapping

Original code, preserved unchanged: [acwing/greedy/104.cpp](../../../acwing/greedy/104.cpp).

Verified on 2026-10-12:

- [AcWing 104 — 货仓选址 (Warehouse Location)](https://www.acwing.com/problem/content/106/):
  choose a warehouse coordinate minimizing total distance to the stores;
  output the minimum distance sum. There are 1–100,000 stores, with coordinates
  from 0 to 40,000. Input is n followed by n coordinates. Sample coordinates
  `6 2 9 1` give output 12.
- [LeetCode 462 — Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/):
  Medium; public statement accessible. A move increments or decrements one
  element by 1. Return the minimum moves to make every element equal.
  There are 1–100,000 elements, each from -10⁹ to 10⁹; the answer fits Int.

These objectives are mathematically equivalent: moving value a to target x
costs exactly |a - x|. The story, coordinate limits, and input/output interfaces
differ. The saved Kotlin implementation targets LeetCode's `minMoves2` API.

The original C++ sorts the input, chooses `a[n / 2]`, and sums distances.
Its `printf("%d", res)` uses the wrong format for a `long long` argument;
`%lld` or `cout << res` would be appropriate. The original file is not edited.
Kotlin uses a sorted List without changing the input, performs arithmetic in
Long, and converts the final answer to Int under LeetCode's guarantee.
