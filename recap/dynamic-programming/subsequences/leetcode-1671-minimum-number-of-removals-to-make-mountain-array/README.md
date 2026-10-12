# LeetCode 1671 — Minimum Number of Removals to Make Mountain Array

[Online judge](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/description/)
· [Your implementation](Solution.kt)
· [Related AcWing 1014 recap](../acwing-1014/EXPLANATION.md)

Your supplied algorithm and variable names are preserved. Formatting and
comments were polished, and braces added around the valid-peak condition.

## State and answer

- f[i]: longest strictly increasing subsequence length ending exactly at i.
- g[i]: longest strictly decreasing subsequence length starting exactly at i.
- Both states start at 1, counting i itself.
- Calculate f left-to-right and g right-to-left, so dependencies are ready.

A valid peak must satisfy `f[i] > 1 && g[i] > 1`: at least one selected
element lies on each slope. Merely checking that i is an internal array
index is not enough. Scanning all indexes is safe, since f[0] and g[n-1]
are 1 and fail this condition automatically.

For each valid peak, `f[i] + g[i] - 1` counts the most elements we can keep,
subtracting the shared peak once. The two sides occupy disjoint index ranges
apart from that peak, so they can be combined. Every mountain has such a peak;
maximizing the kept length and returning `n - answer` minimizes removals.

Unlike AcWing 1014, a purely increasing or decreasing subsequence is invalid.
The LeetCode contract guarantees a valid mountain can be formed and allows
3–1000 elements. No impossible-input return convention is added.

Time is O(n²), extra space O(n). Input is not modified.

## Run locally

Run `bash run.sh` from this folder. Paste only Solution.kt into LeetCode.
The tests include the published examples, duplicate heights, and cases where
an invalid one-sided candidate would otherwise beat a valid mountain.
Local results are not an online-judge acceptance claim.
