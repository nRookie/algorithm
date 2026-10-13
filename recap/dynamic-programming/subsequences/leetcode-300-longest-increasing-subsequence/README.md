# LeetCode 300 — Longest Increasing Subsequence

[Official judge](https://leetcode.com/problems/longest-increasing-subsequence/description/).
Related practice for [AcWing 1017](../acwing-1017/EXPLANATION.md).

Return the longest strictly increasing subsequence length in the original
array order. The O(n²) DP state is the best length ending exactly at i;
extend j < i only when nums[j] < nums[i]. This differs from taking the better
of both descending directions in the AcWing conversion. The statement also
offers an O(n log n) follow-up, now implemented in your
[TailsSolution.kt](TailsSolution.kt).

Submit [Solution.kt](Solution.kt). Input is nonempty under the judge contract.

Your implementation is preserved in [LearnerSolution.kt](LearnerSolution.kt),
with the required `kotlin.math.max` import and polished comments. It uses
IntArray and updates res inside the successful predecessor condition. This
is correct because both the initial states and res start at 1 and the input
is nonempty. Time is O(n²), extra space O(n). Both files declare Solution;
compile or submit only one at a time. TailsSolution.kt also declares Solution;
select that file alone when practicing the optimized version.

## Your O(n log n) implementation

TailsSolution.kt preserves your corrected implementation, with comments
polished to describe the new state rather than endpoint-based DP.
`tails[p]` stores the smallest ending value found for an increasing subsequence
of length p + 1 among the input processed so far. Start with an empty list:
`mutableListOf(n)` would create a list containing the value n, not reserve space.

For each x in original input order, binary-search for the first tail >= x.
The search keeps values before l below x and values at or beyond r at least x.
Replace the tail at l, or append if l equals tails.size. Equal values replace
rather than append because the subsequence must be strictly increasing.

Each length's tail is an independent record, not necessarily part of one
shared subsequence. For input `[2,8,3,5,1]`, tails becomes `[1,3,5]`, but the
actual length-3 subsequence remains `[2,3,5]`. The final 1 improves only the
length-1 record.

A smaller tail is at least as useful for extending a subsequence of the same
length. At replacement position p > 0, tails[p-1] < x, so a real earlier
length-p subsequence can be extended with x. At p = 0, x alone suffices.
No longer subsequence can end at x: if tails[p] exists, even the smallest
length-(p+1) tail is >= x. The updates preserve attainable minimum tails,
so their count is exactly the LIS length. This reasoning does not directly
apply to maximum-sum subsequences: a smaller tail can have a worse total sum.

Time is O(n log n), with O(n) extra space. The original input is unchanged.
