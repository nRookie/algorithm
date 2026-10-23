# 862. Shortest Subarray with Sum at Least K

[Official problem](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/):
return the shortest nonempty subarray whose sum is at least `k`, or `-1`.
Elements may be negative; `k > 0`.

## Learner's reasoning: why `while`, not `if`?

The learner's intuition was that we must keep shrinking to see the intermediate
candidates, using `[1, 1, 1, 1, 7]` as the example. More precisely: exhaust all
valid candidate starts for the current endpoint before advancing the endpoint.
Each later start produces a shorter subarray ending at the same position.

Let `k = 7`. Prefix sums are `pre = [0, 1, 2, 3, 4, 11]`.
`pre[i]` is the sum of the first `i` elements, so start `j` and endpoint `i`
represent `nums[j until i]`, with sum `pre[i] - pre[j]` and length `i - j`.
The deque stores prefix indices, not prefix values.

Following the learner's second version (remove backs, append `i`, remove fronts):

| `i` | `pre[i]` | Valid fronts removed | Queue after iteration | Best length |
| --- | --- | --- | --- | --- |
| 0 | 0 | None | `[0]` | None |
| 1 | 1 | None | `[0,1]` | None |
| 2 | 2 | None | `[0,1,2]` | None |
| 3 | 3 | None | `[0,1,2,3]` | None |
| 4 | 4 | None | `[0,1,2,3,4]` | None |
| 5 | 11 | `0,1,2,3,4` | `[5]` | 1 |

At the final endpoint `i = 5`, the front-removal loop performs:

| Start `j` | Sum `11 - pre[j]` | Length `5 - j` |
| --- | --- | --- |
| 0 | 11 | 5 |
| 1 | 10 | 4 |
| 2 | 9 | 3 |
| 3 | 8 | 2 |
| 4 | 7 | 1 |

An `if` with front removal would record only length 5 and remove start 0.
There is no next endpoint to process the remaining starts. The `while` reaches
start 4 and records the correct answer, 1.

```kotlin
while (queue.isNotEmpty() && pre[i] - pre[queue.first()] >= k.toLong()) {
    minLen = minOf(minLen, i - queue.first())
    queue.removeFirst()
}
```

## Why removal and stopping are safe

After recording a valid start `j` at endpoint `i`, any later endpoint `t > i`
has length `t - j > i - j`. That same start cannot improve the recorded answer,
so it can be permanently removed.

Deque indices increase, and their prefix sums strictly increase. If the front
fails the sum threshold, every subsequent candidate has a larger prefix sum,
giving an even smaller difference from `pre[i]`. None can qualify now, so stop.
This stopping argument depends on the deque invariant, not on arbitrary input
elements being positive.

Back removal has a different justification: when `j < i` and
`pre[j] >= pre[i]`, start `i` gives at least as large a sum and a shorter length
for every future endpoint. Remove all such dominated backs to restore the
strictly increasing prefix-sum invariant.

## Corrections to the supplied implementations

- The first version used `== k`; the condition must be `>= k`. For `[3]`,
  `k = 2`, equality misses the valid length 1.
- The first version checked only one front and never removed it, despite the
  comment describing safe removal. The second version fixes both issues.
- Both versions used `IntArray` for `pre`. Use `LongArray(n + 1)` and compute
  `pre[i] = pre[i - 1] + nums[i - 1].toLong()`. Up to 100,000 elements of
  value 100,000 can produce a sum of 10,000,000,000. Overflow can corrupt
  both deque ordering and threshold checks.
- The second version's order is valid for this problem: backs removed before
  the query satisfy `pre[i] - pre[j] <= 0 < k`, so cannot be answers ending
  here. Appending `i` before the query is safe because its self-difference is
  zero and `k > 0`; it cannot create an empty answer.

Each index is appended once and removed at most once, from either end.
Thus the nested `while` loops total O(n) time, with O(n) auxiliary space.

Interview wording: “For each endpoint, I repeatedly record and remove valid
fronts, because later starts can shorten the current answer. Once a start has
produced a valid answer, using it with a later endpoint can only be longer.”
