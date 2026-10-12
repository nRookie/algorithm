# LeetCode 462 — Minimum Moves to Equal Array Elements II

Topic: greedy choice of a median. Original: AcWing 104, Warehouse Location.
[Source, official statements, and contract differences](SOURCE.md).
[Submission code](Solution.kt).

Your own implementation is saved in [LearnerSolution.kt](LearnerSolution.kt),
with the required `kotlin.math.abs` import added. It sorts the input array
in place and accumulates in Int. This is safe for LeetCode 462: each absolute
difference is at most 2,000,000,000, and the judge guarantees the final sum
fits Int. All contributions are nonnegative, so partial sums also fit.
Unlike Solution.kt, your version intentionally changes the input order.
Both files declare `class Solution`; compile or submit only one at a time.

## What are we minimizing?

For positions or values a[0], ..., a[n-1], choose a common target x to minimize
`|a[0] - x| + ... + |a[n-1] - x|`. AcWing interprets x as a warehouse position;
LeetCode interprets it as the final equal value. Both ask for the minimum cost,
not the target coordinate itself.

## Solution evolution

A direct approach tries every integer target between the minimum and maximum
input values and computes its cost. If that range contains R integers, this
takes O(nR) time and O(1) additional space. Targets outside the range cannot
help: moving toward the range reduces every distance. However, enumerating
the range is too expensive for large coordinates.

Instead, sort and choose a median. The following pairing proof shows that
this choice achieves a lower bound on the cost, so no target can do better.
This gives O(n log n) time for sorting plus an O(n) sum.

## Why the median is optimal

For any two positions a <= b, a target x satisfies
`|a - x| + |b - x| >= b - a`. Equality holds precisely when x lies in [a,b].
Inside that interval, increasing one distance decreases the other equally;
outside it, the total exceeds b - a by twice the distance to the nearer end.

Sort the positions and pair the smallest with the largest, the second-smallest
with the second-largest, and so on. Each pair contributes at least its gap.
The pair intervals are nested, so a median lies inside every one of them
and achieves all their lower bounds simultaneously.

- For odd n, one middle element remains unpaired. Choosing that element makes
  its own distance zero as well, attaining the full lower bound.
- For even n, every target between the two middle values attains the bound.
  Choosing either middle value is enough; there is no need to average them.

Every original element occurs in exactly one pair, except the single unpaired
middle element for odd n. Thus the lower bound accounts for the entire sum
once. Attaining it proves global optimality, not merely local improvement.

## Example

```text
Input:  [6, 2, 9, 1]
Sorted: [1, 2, 6, 9]

Outer pair: [1,9] contributes at least 8
Inner pair: [2,6] contributes at least 4
Total lower bound: 12
```

Any target in [2,6] achieves 12. The implementation selects 6:

| value | Distance to 6 | res afterward |
| --- | --- | --- |
| 1 | 5 | 5 |
| 2 | 4 | 9 |
| 6 | 0 | 9 |
| 9 | 3 | 12 |

The median is not the mean. For `[1,2,100]`, target 2 costs 99, while the
integer mean rounded to 34 costs 131. Absolute distances favor a median;
the mean is associated with minimizing squared distances instead.

## Index meanings and Kotlin implementation

- The sorted list is indexed from 0 through n-1. `sorted.size / 2` uses integer
  division: n=5 selects index 2; n=4 selects index 2, the upper middle value.
- That expression is an index; `sorted[sorted.size / 2]` is the target value.
- `nums.sorted()` creates a List<Int> and leaves the input array unchanged.
- Convert operands to Long before subtraction, then take the absolute value
  and accumulate in Long. The judge guarantees the final answer fits Int.
- The input is nonempty under both problem contracts, so the median exists.

In the summation loop, res equals the total distance of all values processed
so far to the median. Each iteration adds exactly the next distance. Every
value is visited once, so the final sum is exactly the cost of the proven
optimal target. Sorting and the finite scan terminate.

Time: O(n log n). Auxiliary space: O(n) for the sorted list and sorting work.
A single node costs zero; repeated values and negative values need no special
cases. Linear-time selection is a separate possible optimization, not needed
for this recap's sorting-based implementation.

## Interview wording

“For a fixed target, the required moves are the sum of absolute differences.
I sort the values and choose a median. To prove it is optimal, I pair the
smallest and largest values. Each pair costs at least the gap between them,
with equality whenever the target lies between them. A median lies inside
every such pair, so it achieves the total lower bound. With an odd number of
values, it also makes the unpaired middle value's cost zero.

I then sum distances to the median. Sorting takes O(n log n) time, and my
sorted-list implementation uses O(n) extra space.”

## Run locally

Run `bash run.sh` in this folder. Tests compare small random inputs with
exhaustive target enumeration, and include the published examples, duplicate
and negative values, a singleton, and a large-distance case. These local
checks do not claim online-judge acceptance.
