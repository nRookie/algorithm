# Prefix sums

Start with repeated range queries on an unchanged sequence.

| Problem | Recap | Original source |
| --- | --- | --- |
| One-dimensional range sums / LeetCode 303 | [Explanation and interview wording](range-sum-query-immutable/EXPLANATION.md) | [AcWing 795.cpp](../../acwing/basic/795.cpp) and the learner's Kotlin implementation in the explanation |
| Two-dimensional range sums / LeetCode 304 | [Explanation and interview wording](range-sum-query-2d/EXPLANATION.md), [Kotlin](range-sum-query-2d/Solution.kt) | [AcWing 796.cpp](../../acwing/basic/796.cpp) |

Read the one-dimensional recap first, then extend its boundary model to rows
and columns. The Kotlin implementation targets LeetCode directly, using zero-based query
coordinates and its required class interface.
