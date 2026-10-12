# LeetCode 1626 — Best Team With No Conflicts

[Official problem](https://leetcode.com/problems/best-team-with-no-conflicts/description/)
· [Your implementation](Solution.kt)

Your supplied algorithm, variable names, IntArray state, and use of max are
preserved. Formatting was cleaned up and `import kotlin.math.max` was added
for standalone compilation.

## Problem contract

Choose a subset of players with maximum total score. A younger player having
a strictly higher score than an older player creates a conflict. Players of
the same age never conflict. Original input order does not constrain selection.
There are 1–1000 players, scores are 1–1,000,000, and ages are 1–1000.
The two input arrays have equal length; index i describes the same player
in both arrays. These details were verified against the official statement
during this recap.

## Your reasoning, polished

“I zip ages and scores to keep each player's data together, then sort by age
and break equal-age ties by score. I use maximum-sum subsequence DP to choose
a compatible team.”

This is a maximum-sum **non-decreasing** subsequence of scores, not a longest
strictly increasing subsequence. It extends AcWing 1016's sum objective but
adds sorting and allows equal scores. In AcWing 1016, original index order
must be preserved and equal values cannot extend the subsequence.

## Solution evolution

A baseline enumerates every subset, checks all selected pairs for conflicts,
and sums the scores of valid teams. A straightforward implementation takes
O(n² × 2^n) time and O(n) temporary space. It repeatedly explores teams that
share the same final player and can be extended in the same way.

Sorting by age, then score, gives a fixed order in which valid teams have
non-decreasing scores. We can retain only the best total for each final
player and extend those states, giving O(n²) time and O(n) extra space.

## Why the sorting and <= comparison matter

`ages.zip(scores)` produces `(age, score)` pairs. `.first` is age; `.second`
is score. Sort age ascending, and for equal ages sort score ascending.

For distinct ages, compatibility requires the younger player's score to be
at most the older player's score. Equal scores are allowed, so use `<=`.

For equal ages, any scores can coexist. Sorting their scores ascending makes
that freedom compatible with the same non-decreasing DP condition. Without
the tie-break, same-age players with scores `[5,2]` would appear in an order
that prevents combining them, even though their team score should be 7.
Likewise, using `<` would incorrectly prevent combining scores `[5,5]`.

Every conflict-free subset has non-decreasing scores in this sorted order:
the conflict rule enforces this across ages, and the tie-break enforces it
within one age. Conversely, a non-decreasing score subsequence in this order
cannot contain a younger player with a higher score. Thus the transformation
preserves exactly the allowed teams.

## State, initialization, and transition

`dp[i]` is the maximum total score of a valid team whose last player in the
sorted order is player i. It is a sum, not the number of selected players.
`dp[i] = players[i].second` represents selecting only player i.

For every j < i, if score[j] <= score[i], append i to the best team ending
at j and consider `dp[j] + score[i]`. All scores in that earlier team are
at most score[j], so testing the final score suffices for the entire team.

The outer loop moves left-to-right so dp[j] is ready. The best team may end
anywhere; update res after finishing each dp[i].

## Complete trace

```text
scores = [4,5,6,5]
ages   = [2,1,2,1]
Sorted players (age,score): [(1,5), (1,5), (2,4), (2,6)]
```

| i | Initial dp[i] | Earlier candidates, in order | Final dp[i] | res |
| --- | --- | --- | --- | --- |
| 0 | 5 | None | 5 | 5 |
| 1 | 5 | j=0: 5 <= 5, candidate 5+5=10 | 10 | 10 |
| 2 | 4 | j=0 and j=1: 5 > 4, both rejected | 4 | 10 |
| 3 | 6 | j=0: 5+6=11; j=1: 10+6=16; j=2: 4+6=10 | 16 | 16 |

The selected team has scores 5,5,6 and ages 1,1,2. Each input entry remains
a separate player even if its age and score equal another player's values.

## Correctness and complexity

Assume states before i are correct. A valid team ending at i is either the
singleton player i, or has a previous selected player j with score[j] <=
score[i]. The recurrence considers all such j. Replacing its earlier team
with the maximum-score team ending at that same j preserves compatibility
and cannot reduce the total. Each admitted extension is valid, so dp[i]
is both attainable and at least as good as every valid team ending there.
Induction proves all states correct. Every team has a last player in sorted
order, so res is the global optimum. The finite index loops terminate.

Sorting is O(n log n), and the DP considers n(n-1)/2 pairs: total O(n²).
Pairs, the sorted list, sorting workspace, and dp use O(n) extra space.
Input arrays are not modified. Int is sufficient because the total is at
most 1000 × 1,000,000 = 1,000,000,000.

## Interview wording

“I pair each player's age and score, then sort by age ascending and score
ascending for ties. In this order, a team is conflict-free exactly when its
scores are non-decreasing. Sorting equal-age scores lets those players be
combined even though their scores differ.

I define dp[i] as the maximum team score ending at player i. I initialize it
with that player's score and try every earlier player with a score no greater
than the current one. I add the current score to that player's best total,
then take the maximum over all endpoints. Time is O(n²), and space is O(n).”

## Local validation

Run `bash run.sh` in this folder. Tests cover the three official examples,
same-age score ordering, equal scores across ages, the maximum score total,
and small random instances checked by enumerating all subsets and evaluating
the original pairwise conflict rule. Inputs are checked for preservation.
These are local checks, not a claim of online-judge acceptance.
