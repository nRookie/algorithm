# 174. Dungeon Game

## Problem and your saved implementation

Start in the top-left cell of a nonempty rectangular dungeon. Each cell adds
or removes health, including the starting cell and the princess's bottom-right
cell. Move only right or down. Return the smallest positive initial health
that allows a path to the princess while keeping health at least 1 throughout.
Zero health means death. The input grid does not change.

[174.kt](174.kt) preserves your supplied algorithm, array dimensions, boundary
initialization, and loop directions. Debugging prints were removed and the
comments were corrected. The active recurrence you supplied was already correct.

```kotlin
class Solution {
    fun calculateMinimumHP(dungeon: Array<IntArray>): Int {
        val m = dungeon.size
        val n = dungeon[0].size
        // Minimum health before applying this cell, to survive to the princess.
        val dp = Array(m + 1) {
            IntArray(n + 1) { Int.MAX_VALUE }
        }

        // Virtual successors of the princess require 1 health after her cell.
        dp[m - 1][n] = 1
        dp[m][n - 1] = 1

        for (i in m - 1 downTo 0) {
            for (j in n - 1 downTo 0) {
                dp[i][j] = maxOf(
                    minOf(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j],
                    1
                )
            }
        }

        return dp[0][0]
    }
}
```

## Solution evolution

### 1. A correct baseline: inspect every complete route

Enumerate all paths made of right/down moves. For each path, combine its cell
values in order and find the smallest cumulative sum, including zero before
entering the first cell. The minimum initial health for that path is 1 minus
that smallest sum, just as in [1413](../1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md).
Take the smallest requirement across paths.

Every path visits L = m + n - 1 cells. There are
`C(m + n - 2, m - 1)` complete paths, since a route chooses the positions of
its m - 1 downward moves among all moves. Enumerating and inspecting each full
path takes O(L times number of paths), with O(L) working space if routes are
processed one at a time. The path count becomes exponential on growing square
grids. This is a conceptual baseline, not a claim that you implemented it.

Different paths can reach the same cell, after which they face the same future
choices. Recomputing those suffix paths is the repeated work to remove.

What to say: “For each route I could find its largest cumulative deficit,
but many routes share the same remaining dungeon. I want to reuse the minimum
health requirement of each remaining position.”

### 2. Your backward DP: solve the remaining dungeon once per cell

Your comments started with “minimum health required to get to this cell,”
then your actual implementation switched to the backward requirement:

```text
dp[i][j] = minimum health needed BEFORE applying dungeon[i][j],
           to survive from this cell to the princess along some valid path.
```

This definition describes a future subproblem. It does not describe health
left after entering the cell, or minimum initial health to reach it. An amount
at least `dp[i][j]` suffices; a smaller amount cannot complete any valid suffix
path. More incoming health never removes a possible path under these rules.

The knight still travels right/down. Only the calculation proceeds backward,
so the requirements of those possible next cells are ready first.

What to say: “At each cell I store the minimum incoming health needed to
finish. I choose the next cell with the smaller requirement, undo the current
cell's health change, and enforce the minimum health of 1.”

## Derive the transition

From `(i, j)`, the knight may choose down `(i + 1, j)` or right `(i, j + 1)`.
Because either route is sufficient, the health needed after the current cell
is the smaller successor requirement:

```text
required afterward = min(dp[i + 1][j], dp[i][j + 1])
```

Applying the current cell gives:

```text
health before cell + dungeon[i][j] >= required afterward
health before cell >= required afterward - dungeon[i][j]
```

Health before the cell must also be at least 1. Hence:

```text
dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j])
```

Subtracting a negative cell value increases the required incoming health.
A positive cell can reduce the requirement, but never below 1. Use `min`
because we choose one continuation; `max` would require enough for both.

## Why the padded boundaries work

The real grid uses zero-based indexes: `dp[i][j]` corresponds directly to
`dungeon[i][j]`. The extra row m and column n are outside the dungeon; they
do not shift the indexing by one.

Initialize every entry to `Int.MAX_VALUE`, then set:

```kotlin
dp[m - 1][n] = 1
dp[m][n - 1] = 1
```

These are the two virtual successors immediately right of and below the
princess. They encode the requirement to remain alive after applying her cell.
They are not actual cells the knight must visit. All other outside entries
stay infinite so the recurrence cannot choose an invalid exit from the grid.

At the princess, the formula therefore becomes:

```text
dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1])
```

Every real cell has a finite route to the princess. In reverse order, at least
one successor requirement is finite before evaluating each cell; at the
princess, both virtual successors are finite. Thus the minimum is never the
infinite sentinel when subtracting the cell value. This avoids arithmetic
with `Int.MAX_VALUE` in this particular rectangular, unobstructed dungeon.

## Illustration: the entire table and every update

Use this fully specified dungeon:

```text
         column
         0    1    2
row 0   -2   -3    3
row 1   -5  -10    1
row 2   10   30   -5  ← princess
```

After allocating dp and initializing its virtual successors, with `∞` meaning
`Int.MAX_VALUE`:

```text
         j=0  j=1  j=2  j=3 (outside)
i=0       ∞    ∞    ∞    ∞
i=1       ∞    ∞    ∞    ∞
i=2       ∞    ∞    ∞    1
i=3       ∞    ∞    1    ∞   (outside)
```

Your loops calculate rows from bottom to top, and each row from right to left:

| Order | Cell (i,j) | dungeon[i][j] | Down requirement | Right requirement | Calculation | dp[i][j] |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | (2,2) | -5 | 1 | 1 | max(1, 1 - (-5)) | 6 |
| 2 | (2,1) | 30 | ∞ | 6 | max(1, 6 - 30) | 1 |
| 3 | (2,0) | 10 | ∞ | 1 | max(1, 1 - 10) | 1 |
| 4 | (1,2) | 1 | 6 | ∞ | max(1, 6 - 1) | 5 |
| 5 | (1,1) | -10 | 1 | 5 | max(1, 1 - (-10)) | 11 |
| 6 | (1,0) | -5 | 1 | 11 | max(1, 1 - (-5)) | 6 |
| 7 | (0,2) | 3 | 5 | ∞ | max(1, 5 - 3) | 2 |
| 8 | (0,1) | -3 | 11 | 2 | max(1, 2 - (-3)) | 5 |
| 9 | (0,0) | -2 | 6 | 5 | max(1, 5 - (-2)) | 7 |

Final real-cell requirements:

```text
          0    1    2
row 0     7    5    2
row 1     6   11    5
row 2     1    1    6
```

Return `dp[0][0] = 7`. Those values are incoming health requirements for
different suffixes, not the health along one actual walk.

One valid walk with initial health 7 is right, right, down, down:

```text
[-2] → [-3] → [ 3]
               ↓
             [ 1]
               ↓
             [-5]
```

| Cell entered | Health before applying cell | Cell change | Health after applying cell |
| --- | --- | --- | --- |
| (0,0) | 7 | -2 | 5 |
| (0,1) | 5 | -3 | 2 |
| (0,2) | 2 | 3 | 5 |
| (1,2) | 5 | 1 | 6 |
| (2,2) | 6 | -5 | 1 |

Every result is at least 1. The proof below establishes minimality across all
paths, not only this illustrated route.

## Correctness and termination

At the princess, `max(1, 1 - cell value)` is the exact minimum incoming health
that is positive before the cell and remains positive after it.

Assume the requirements for the legal successors of a cell are correct. Their
minimum is the exact amount needed after the current cell to allow at least
one continuation. Applying the current cell and enforcing positive incoming
health gives the recurrence. Its result suffices by choosing a successor with
the smaller requirement. Any smaller incoming amount either is below 1, or
leaves less than every legal successor requires; neither can succeed.

Before each update, its downward and rightward requirements are ready:
the lower row was processed earlier, and the next column in the current row
was processed earlier. The same meanings therefore hold for the newly computed
entry. Induction in this reverse order proves the returned requirement at
the starting cell is correct.

Both loops advance toward zero and each real cell is processed exactly once.
There are mn constant-time transitions, so time is O(mn). The padded table
has `(m + 1)(n + 1)` entries, so auxiliary space is O(mn) for nonempty grids.
The input is not modified. A rolling row could reduce storage to O(n), but
that is a separate improvement and is not part of your saved implementation.

## Connection to 1413 and Gas Station DP

All three use a minimum incoming-resource requirement:

```text
required before = max(minimum allowed, required afterward - current change)
```

- In [1413](../1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md),
  there is one next suffix and the lower bound is 1.
- In [Gas Station DP](../134_gas_station/dp/EXPLANATION.md), there is one next
  station, an explicit remaining-trip count, and the lower bound is 0.
- In Dungeon Game, there are two possible next cells. Take the smaller of
  their required health values, then apply the same resource calculation with
  lower bound 1. Right/down moves make these dependencies acyclic.

The linear Gas Station solution is greedy; it uses a different argument that
eliminates starting candidates after a failure.

## Corrections to the comments, not the algorithm

Your active transition and initialization were correct. For the reasoning:

- “Minimum health to get to this cell” should be “minimum incoming health to
  survive from this cell to the princess.”
- Health must be at least 1, not strictly greater than 1.
- Backward calculation does not change the knight's legal right/down moves.
- Padding adds an outside row and column, not a shift to `dungeon[i - 1][j - 1]`.
- The early comment `dp[0][0] = 0` does not describe this backward DP. Its
  starting-cell requirement is calculated last from the terminal requirement 1.

## Interview explanation and recall

The saved Kotlin file compiled and passed 9 example/boundary cases plus all
680 grids with values from -2 through 2 and dimensions 1×1, 1×2, 2×1, or 2×2.
An independent checker enumerated every legal right/down path and calculated
its initial-health requirement from cumulative changes. The fixed cases
included the standard dungeon, positive/negative/zero single cells, single
rows and columns, and grids requiring a choice of path. These are observed
checks; the induction above is the general correctness argument.

> “I define dp[i][j] as the minimum health before entering that cell that
> permits survival to the princess. I compute from bottom-right backward.
> The knight can choose right or down, so I take the smaller future requirement,
> subtract the current cell's change, and enforce at least 1 health. Virtual
> successors of the princess have requirement 1; other outside entries are
> infinite. Each cell is solved once, giving O(mn) time and space.”

Recall questions: What point in time does dp describe? Why choose the smaller
successor requirement? Why is the terminal requirement 1? Why are only two
outside entries set to 1? Why does reverse calculation still represent a
forward right/down journey?
