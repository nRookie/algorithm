# AcWing 1012 — Friendly Cities

[Your corrected Kotlin implementation](Main.kt)
· [Original C++](../../../../acwing/dp/line/lineup/1012.cpp)

## Contract and source

The user supplied the problem statement: N cities lie on each of two straight,
parallel river banks. Coordinates are distinct within each bank. Each south
city is paired with exactly one north city, and vice versa. Choose the maximum
number of straight routes without crossings. Input is N followed by N pairs
`(south, north)`. Output the maximum route count.

Bounds: `1 <= N <= 5000`, coordinates from 0 to 10000. The
[original statement URL](https://www.acwing.com/problem/content/1014/) was
unavailable during the recap; the supplied statement is the contract source.
The local sample below is illustrative, not an official sample.

## Your reasoning and code corrections

Your approach is to store pairs, sort by south coordinate, and compute a
strictly increasing subsequence of north coordinates. The saved implementation
preserves that algorithm and IntArray DP. Syntax/name corrections were:

- `iimport` becomes `import`.
- Use `pairs` consistently instead of mixing `paris` and `pairs`.
- `for (j in until i)` becomes `for (j in 0 until i)`.
- Use `maxOf` rather than an unimported `max`.

Your question about equality identifies an important assumption: two cities
**cannot** share a coordinate on the same bank. Consequently, north coordinates
of different pairs never tie, and `>` and `>=` behave identically on valid
input. We use `>` to express strictly matching coordinate order. This is not
a general justification for allowing equality in other two-coordinate problems.

## Why increasing order means no crossings

Take two routes A and B with `southA < southB`. Their endpoints have the same
left-to-right order on both banks exactly when `northA < northB`. In that case
the straight routes cannot cross. If `northA > northB`, their order reverses
and they must intersect inside the river.

More precisely, at fraction t across the river, the horizontal difference
between route B and route A is
`(1-t) * (southB-southA) + t * (northB-northA)`.
With both differences positive it stays positive. With opposite signs it
passes through zero for some 0 < t < 1, which is an intersection.

After sorting by south coordinate, earlier pairs have strictly smaller south
coordinates. Thus a selection is non-crossing exactly when its north
coordinates are strictly increasing. Keep the pairs together: sorting each
bank independently would change which cities are friends.

## Solution evolution

A direct baseline enumerates subsets and checks every selected pair for
crossings, taking O(N² × 2^N) time and O(N) temporary space. Sorting converts
the compatibility condition to increasing north coordinates. We can then
retain only the best selection length for each final pair, replacing the
exponential subset search with O(N²) DP.

The original C++ uses coordinate-indexed arrays and scans coordinate values.
The Kotlin implementation instead stores only the N actual pairs and sorts
them, so it does not need storage indexed by every possible coordinate.

## State and transitions

`dp[i]` is the maximum number of non-crossing routes in a selection ending
with sorted pair i. Here i and j are positions in the sorted list;
`pairs[i].first` and `.second` are coordinates, not list indexes.

Initialize dp[i] to 1: route i alone is valid. For every j < i, if
`pairs[j].second < pairs[i].second`, try `dp[j] + 1`. Update res after all
predecessors have been considered. The optimum can end at any i.

## Trace

```text
Input pairs:  [(3,2), (1,3), (4,4), (2,1)]
Sorted pairs: [(1,3), (2,1), (3,2), (4,4)]
North values:    3      1      2      4
```

| i | Initial dp[i] | Predecessor checks | Final dp[i] | res |
| --- | --- | --- | --- | --- |
| 0 | 1 | None | 1 | 1 |
| 1 | 1 | j=0: 3 < 1 is false | 1 | 1 |
| 2 | 1 | j=0 rejected; j=1 gives 1+1=2 | 2 | 2 |
| 3 | 1 | j=0 gives 2; j=1 gives 2; j=2 gives 3 | 3 | 3 |

Select `(2,1), (3,2), (4,4)`: three routes with matching endpoint order.

## Correctness and complexity

For each i, every valid selection ending there is either the singleton i
or has a previous selected pair j with a smaller north coordinate. All those
j are considered. Appending i to a valid selection ending at j is safe for
every earlier route because all their north coordinates are smaller still.
Replacing that prefix with the best prefix ending at j cannot hurt. Induction
over increasing i proves each dp[i] correct; maximizing over all endpoints
gives the optimum. Each finite index loop terminates.

Sorting takes O(N log N), and the DP checks N(N-1)/2 pairs, giving **O(N²)
total time**. At N=5000, this is 12,497,500 predecessor checks. The pair list,
DP array, and sorting workspace use **O(N) extra space**. The answer is at
most N, so Int is sufficient. Local passing tests do not establish compliance
with a particular online judge's time limit.

## Interview wording

“Two straight routes cross when their endpoint orders are reversed between
the banks. I sort the friendly-city pairs by south coordinate, preserving
each pair, and find the longest strictly increasing subsequence of north
coordinates. My state is the maximum number of routes ending at a particular
sorted pair. I try every earlier pair with a smaller north coordinate and
extend its best count by one. Both banks have distinct coordinates, so ties
need no special handling here. Time is O(N²), with O(N) extra space.”

## Run locally

```sh
bash recap/dynamic-programming/subsequences/acwing-1012/run.sh sample
bash recap/dynamic-programming/subsequences/acwing-1012/run.sh stdin
bash recap/dynamic-programming/subsequences/acwing-1012/run.sh test
```

## LeetCode practice

[LeetCode 354 — Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/description/)
(Hard) asks for the maximum nested chain, with both width and height strictly
increasing and no rotation. This practices ordering pairs and reducing a
two-coordinate condition to a subsequence problem.

It is **not an identical contract**: dimensions may tie and there may be
100,000 envelopes. The current O(N²) method is useful for initial reasoning
but does not scale to that limit. Practice tie handling and an O(N log N)
LIS approach for the full judge. The solution is intentionally not supplied.
