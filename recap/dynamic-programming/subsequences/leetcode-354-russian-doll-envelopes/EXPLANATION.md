# LeetCode 354 — Russian Doll Envelopes

[Online judge](https://leetcode.com/problems/russian-doll-envelopes/description/)

Status: completed O(n log n) implementation in [Solution.kt](Solution.kt).
Your algorithm is preserved; formatting and comments were polished. In
particular, the binary search finds the first tail **>= x**, not <= x.
The earlier O(n²) attempt is preserved below for comparison. No online
acceptance is claimed.

## Your optimized implementation

Sort width ascending and height descending for equal widths, then compute
strictly increasing LIS on heights with the minimum-tail method.

Width sorting makes widths non-decreasing. Equal-width heights decrease,
so a strictly increasing height subsequence can select at most one envelope
from each equal-width group. Consequently every selected chain has strictly
increasing widths and heights. Conversely, every valid nesting chain appears
in width order and has strictly increasing heights, so this reduction loses
no valid chain.

For `[2,3], [2,4]`, ascending heights would append both 3 and 4 and incorrectly
report length 2. Descending heights processes 4 then 3: tails becomes `[4]`
then `[3]`, with length still 1. Both envelopes are processed, but they cannot
both be counted in the same chain. Equal heights across different widths
also cannot extend the chain because the search uses the first tail >= x.

`tails[p]` is the minimum ending height for a chain of length p+1 among the
processed envelopes. It is not necessarily the height sequence of one actual
chain. Binary search and replacement follow the
[LeetCode 300 explanation](../leetcode-300-longest-increasing-subsequence/README.md).

Example: sorting `[[5,4],[6,4],[6,7],[2,3]]` produces
`[[2,3],[5,4],[6,7],[6,4]]`. The tails states are `[3]`, `[3,4]`,
`[3,4,7]`, `[3,4,7]`; answer 3. The last height 4 replaces the existing 4.

Sorting and all binary searches take O(n log n) total time. Extra space is
O(n) for tails and sorting workspace. Sorting reorders the input array;
individual envelope dimensions are not changed. Run `bash run.sh` in this
folder for official examples, tie cases, a large input, and small random
comparisons with two-dimensional DP.

## Your supplied implementation

The code below preserves your original attempt, including comments. It needs
`import kotlin.math.max` for standalone compilation, or both max calls can
be replaced by maxOf.

```kotlin
class Solution {
    fun maxEnvelopes(envelopes: Array<IntArray>): Int {
        envelopes.sortWith(compareBy({ it[0] }, { it[1] }))
        //for (envelope in envelopes) println(envelope.contentToString())
        // we sort the envelop from small to bigger
        val n = envelopes.size
        val dp = IntArray(n) // use dp[i] indicate the number of envelops we can Russian doll from 0..i
        // we already sorted the array in order
        // so the width already in order, what matters is the height, we need to find LIS
        // for i > j
        // envelops[i][1] > envelops[j][1]
        // we increase the dp
        var res = 0
        for (i in 0 until n) {
            dp[i] = 1
            for (j in 0 until i) {
                val a = envelopes[i]
                val b = envelopes[j]
                if (a[0] > b[0] && a[1] > b[1])
                    dp[i] = max(dp[i], dp[j] + 1)
            }
            res = max(res, dp[i])
        }
        return res
    }
}
```

## Review and polished state definition

`dp[i]` is the maximum nesting-chain length **ending exactly at envelope i**
in sorted order. It is not the best length anywhere in indexes 0..i; res
tracks that prefix-wide maximum after each iteration.

Sorting width ascending and height ascending is valid for this implementation
because every transition explicitly checks **both** dimensions strictly.
Each envelope alone gives length 1. Every smaller nested predecessor appears
earlier by width, so the recurrence tries every possible predecessor and
admits only valid extensions.

The comment saying that only height matters needs qualification: sorting
widths makes them non-decreasing, not strictly increasing. With envelopes
`[2,3]` and `[2,4]`, heights increase but nesting is impossible. Your explicit
width comparison correctly rejects that transition. Do not drop it when
changing approaches without addressing equal widths.

Sorting changes the input array's order. Runtime is O(n²), dominated by
n(n-1)/2 predecessor checks; extra space is O(n) for dp and sorting workspace.
At n=100,000, that is 4,999,950,000 checks, so this is a correct baseline but
not suitable for the full judge limit.

## Completed prerequisite

Study the difference between an endpoint-based DP state and a minimum-tail
state in [LeetCode 300](../leetcode-300-longest-increasing-subsequence/README.md).
The minimum-tail implementation and envelope tie-handling adaptation are
now completed above; the original baseline remains here for comparison.
