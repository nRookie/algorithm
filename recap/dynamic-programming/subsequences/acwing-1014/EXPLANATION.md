# AcWing 1014 — Mountain sightseeing

[Your Kotlin implementation](Main.kt) · [Original C++](../../../../acwing/dp/line/lineup/1014.cpp)

The contract and sample below come from the statement supplied by the user.
Visit sights in increasing index order, possibly skipping some. Consecutive
selected heights must differ; after beginning to descend, you cannot ascend
again. Maximize the number of selected sights. There are 2–1000 sights;
the supplied text gives no numeric height bound. The code retains Int heights
from the original implementation.

## Your implementation

The saved code preserves your arrays, variables, loops, and Scanner input.
Only formatting and the g comment were corrected: g describes a decreasing
subsequence starting at i, not an increasing one starting there.

| State | Meaning | Calculation order |
| --- | --- | --- |
| f[i] | Longest strictly increasing subsequence length ending at i | Left to right |
| g[i] | Longest strictly decreasing subsequence length starting at i | Right to left |

Both represented paths travel left to right. Calculation order follows the
dependencies, not the direction of travel. Each state starts at 1, counting
the sight itself.

For f, an earlier index j with h[j] < h[i] can precede i:
`f[i] = maxOf(f[i], f[j] + 1)`.

For g, a later index j with h[j] < h[i] can follow i:
`g[i] = maxOf(g[i], g[j] + 1)`. Processing i right to left ensures every g[j]
needed is already final. The inner loop's order is immaterial.

Try each i as the peak. Its combined length is `f[i] + g[i] - 1`, subtracting
the peak counted by both sides. Either side may consist of only the peak:
purely increasing or decreasing paths are allowed by this statement.

## Solution evolution and correctness

Enumerating subsequences and checking their shape costs O(n × 2^n) time.
Instead, retain the best length for each fixed endpoint or starting point.
Paths sharing that boundary have the same boundary height and compatible
remaining indexes, so the longest one is enough for future extensions.

Each increasing path ending at i is either the singleton i or has an earlier,
lower predecessor j. The f recurrence tries all such j and only such j.
The analogous argument for a later, lower next sight proves g. Induction in
the respective calculation orders gives correct lengths for every state.

For a fixed peak i, the left path uses indexes below i and the right path
uses indexes above i, so they cannot share any position except i. They can
therefore be joined safely. Every allowed path has a peak, including a peak
at an endpoint for a one-sided path; trying all i misses none. Taking a maximum
computes a length, not a count of paths, so ties do not cause overcounting.

## Supplied sample

```text
h = [186, 186, 150, 200, 160, 130, 197, 220]
f = [  1,   1,   1,   2,   2,   1,   3,   4]
g = [  3,   3,   2,   3,   2,   1,   1,   1]
```

At index 3, height 200, the combined length is 2 + 3 - 1 = 4:
`186 → 200 → 160 → 130`. The last index also gives a length-4 increasing
path. Output 4. The initial equal 186 values cannot extend each other.

Time is O(n²); extra space is O(n). Indexes are zero-based, and `until i`
excludes i while `downTo i + 1` stops strictly to its right.

## Run locally

From the repository root:

```sh
bash recap/dynamic-programming/subsequences/acwing-1014/run.sh sample
bash recap/dynamic-programming/subsequences/acwing-1014/run.sh stdin
bash recap/dynamic-programming/subsequences/acwing-1014/run.sh test
```

## Related practice: LeetCode 1671

[Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/description/)
is rated Hard; its public statement was verified. It uses the same
increase-then-decrease structure, but asks for the number of removals.
Unlike AcWing 1014, the remaining mountain must have a genuine increasing
side and a genuine decreasing side, with at least three elements. Its input
length is 3–1000 and a valid mountain is guaranteed possible.

This is a related exercise, not an identical contract. Your completed
[LeetCode 1671 solution and notes](../leetcode-1671-minimum-number-of-removals-to-make-mountain-array/README.md)
record the valid-peak check and conversion from kept length to removals.
