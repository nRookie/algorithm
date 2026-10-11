# Source and submission target

Original idea: [acwing/basic/796.cpp](../../../acwing/basic/796.cpp).
The original C++ source remains unchanged. It reads a matrix and one-based,
inclusive rectangle queries from standard input.

Submission target: [LeetCode 304 — Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/description/)
(Medium). The saved [Solution.kt](Solution.kt) implements its Kotlin API:

```kotlin
class NumMatrix(matrix: Array<IntArray>)
fun sumRegion(row1: Int, col1: Int, row2: Int, col2: Int): Int
```

Coordinates are zero-based and inclusive. Paste only Solution.kt into the
judge; Test.kt and run.sh are local validation tools. No console input parser
or main function belongs in the submission.

The central idea remains two-dimensional prefix sums and inclusion-exclusion.
The adaptation changes the interface and coordinate offsets, and uses nested
Kotlin mutable lists internally while preserving the judge's array parameter.

Verified LeetCode constraints: 1–200 rows and columns, cell values between
−10,000 and 10,000, and valid ordered query corners. Int arithmetic suffices:
a rectangle's absolute sum is at most 400,000,000, and even the conservative
bound of four such prefix terms fits a signed Int.

The AcWing statement's original numeric constraints were not independently
verified. The recap and tests now use the verified LeetCode contract. Its
statement was publicly readable; this work does not claim a judge submission
or an Accepted result.
