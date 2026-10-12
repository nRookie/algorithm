# LeetCode 300 — Longest Increasing Subsequence

[Official judge](https://leetcode.com/problems/longest-increasing-subsequence/description/).
Related practice for [AcWing 1017](../acwing-1017/EXPLANATION.md).

Return the longest strictly increasing subsequence length in the original
array order. The O(n²) DP state is the best length ending exactly at i;
extend j < i only when nums[j] < nums[i]. This differs from taking the better
of both descending directions in the AcWing conversion. The statement also
offers an O(n log n) follow-up, left for a later recap.

Submit [Solution.kt](Solution.kt). Input is nonempty under the judge contract.

Your implementation is preserved in [LearnerSolution.kt](LearnerSolution.kt),
with the required `kotlin.math.max` import and polished comments. It uses
IntArray and updates res inside the successful predecessor condition. This
is correct because both the initial states and res start at 1 and the input
is nonempty. Time is O(n²), extra space O(n). Both files declare Solution;
compile or submit only one at a time.
