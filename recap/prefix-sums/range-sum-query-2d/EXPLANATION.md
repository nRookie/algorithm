# Two-dimensional prefix sums

Previous recap: [one-dimensional prefix boundaries](../range-sum-query-immutable/EXPLANATION.md).
Original code and assumptions: [SOURCE.md](SOURCE.md).
LeetCode-ready Kotlin collection implementation: [Solution.kt](Solution.kt).
Interactive diagrams: [Open the visualization](VISUALIZATION.html). Switch
between building a prefix and querying a rectangle; each cell shows its net
count as you add or subtract regions. Open the HTML file in a browser.

## Problem

Given an unchanged matrix, answer repeated queries for the sum inside a
rectangle. We use LeetCode 304's inclusive, zero-based coordinates:
`(row1, col1)` is its top-left cell and `(row2, col2)` its bottom-right cell.

For example:

```text
           column 0  1  2
row 0             1  2  3
row 1             4  5  6
row 2             7  8  9
```

The rectangle `(1,1)..(2,2)` contains 5, 6, 8, and 9, with sum 28.

## Solution evolution

### Direct summation

Visit every cell in the requested rectangle and add its value. This is
correct because each selected cell is counted once. A query costs time
proportional to its area: O(nm) in the worst case for n rows and m columns.
For q queries, worst-case time is O(qnm); auxiliary space is O(1), excluding
the stored input.

What to say: "I can scan each rectangle, but overlapping queries repeatedly
add the same cells. Since the matrix stays unchanged, I can reuse stored sums."

### Prefix rectangles

Extend the previous boundary model to both dimensions:

> `pre[r][c]` is the sum of the first r rows and the first c columns.

In zero-based matrix storage, these cells form `[0,r) × [0,c)`. The indexes
r and c are boundaries. There are n + 1 row boundaries and m + 1 column
boundaries, so the prefix table has dimensions `(n + 1) × (m + 1)`.

The first prefix row and column are zero: a rectangle with zero height or
zero width is empty. `pre[n][m]` covers the entire input.

This is an extension of the stored prefix sum, not a prefix sum for each row
alone. Each entry covers a rectangle anchored at the matrix's top-left corner.

| Approach | Preprocessing | Worst-case query | Extra space beyond input |
| --- | --- | --- | --- |
| Direct scan | None | O(nm) | O(1) |
| Prefix rectangles | O(nm) | O(1) | O(nm) |

## Construct a prefix rectangle

To build `pre[i][j]`, combine the rectangle above the current cell and the
rectangle to its left. Their top-left intersection was counted twice, so
subtract it once. Then include the current cell:

```kotlin
pre[i][j] = pre[i - 1][j] + pre[i][j - 1] -
    pre[i - 1][j - 1] + matrix[i - 1][j - 1]
```

The `i - 1` and `j - 1` in `matrix` convert prefix boundaries to the zero-based
index of the newly included cell. Row-major processing makes the upper,
left, and upper-left dependencies available before calculating the entry.

For the example matrix, starting with an all-zero 4-by-4 prefix table:

| i, j | Above + left − overlap + cell | Entry written |
| --- | --- | --- |
| 1, 1 | 0 + 0 − 0 + 1 | 1 |
| 1, 2 | 0 + 1 − 0 + 2 | 3 |
| 1, 3 | 0 + 3 − 0 + 3 | 6 |
| 2, 1 | 1 + 0 − 0 + 4 | 5 |
| 2, 2 | 3 + 5 − 1 + 5 | 12 |
| 2, 3 | 6 + 12 − 3 + 6 | 21 |
| 3, 1 | 5 + 0 − 0 + 7 | 12 |
| 3, 2 | 12 + 12 − 5 + 8 | 27 |
| 3, 3 | 21 + 27 − 12 + 9 | 45 |

The completed table, including empty boundaries:

```text
       c=0  1   2   3
r=0     0  0   0   0
r=1     0  1   3   6
r=2     0  5  12  21
r=3     0 12  27  45
```

## Answer a rectangle query

For LeetCode's zero-based, inclusive coordinates:

1. Start with the prefix ending at row boundary `row2 + 1` and column boundary
   `col2 + 1`.
2. Remove the rows before row1, across that prefix's full width.
3. Remove the columns before col1, across that prefix's full height.
4. Restore their top-left intersection, which was removed twice.

```kotlin
pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] -
    pre[row2 + 1][col1] + pre[row1][col1]
```

For `(1,1)..(2,2)`, this is `45 - 6 - 12 + 1 = 28`.

The top-left corner has coefficient `1 - 1 - 1 + 1 = 0`, each unwanted
strip has coefficient `1 - 1 = 0`, and the requested rectangle has coefficient
1. Thus every selected cell is counted exactly once and every other cell zero
times. Negative values do not change this argument.

Construction subtracts an overlap counted twice. Querying restores an overlap
removed twice. Keep these two uses of inclusion-exclusion distinct.

## Indexing and Kotlin translation

The original AcWing program reads one-based query positions. The saved Kotlin
implementation adapts that algorithm to LeetCode's zero-based NumMatrix API.
The conceptual prefix definition is unchanged: pre[r][c] covers the first r
rows and first c columns. As in NumArray, an inclusive right/bottom element
index becomes a boundary by adding one.

Use independent mutable rows:

```kotlin
val pre = MutableList(n + 1) { MutableList(m + 1) { 0 } }
```

Sharing one mutable row across the outer list would corrupt the table.
The constructor accepts `Array<IntArray>` because that is the judge interface;
internal prefix storage uses collections. Boxed Int values add memory overhead
compared with primitive arrays, while preserving O(nm) space.

LeetCode permits up to 200 × 200 cells of absolute value at most 10,000.
Prefix and rectangle sums have absolute value at most 400,000,000. Even a
conservative bound of four such terms fits Int, so construction and querying
are safe under this contract. For larger constraints, reconsider Long.

## Correctness, cost, and validation

Initially every empty prefix has its correct sum, zero. At each construction
step, already-correct neighboring rectangles plus inclusion-exclusion give
the correct enlarged rectangle. Finite loops visit each cell once. Query
correctness then follows from the cancellation argument above.

Preprocessing takes O(nm) time and O(nm) auxiliary space. Each query takes
O(1), for O(nm + q) total time. The class stores the prefix table without retaining the input matrix. The input is assumed immutable;
stored prefixes do not incorporate later edits to the matrix.

Run local checks from the repository root:

```sh
bash recap/prefix-sums/range-sum-query-2d/run.sh
```

The tests compare every rectangle in small fixed and seeded random matrices
against direct cell-by-cell summation. Cases cover single cells, single rows
and columns, negative values, input edges, and maximum permitted sum magnitudes.
The tests also run the three official example queries and maximum-size positive
and negative matrices. They support, but do not replace, the correctness argument.

Paste only [Solution.kt](Solution.kt) into LeetCode. It contains the NumMatrix
class with no console parser or main function. Test.kt remains a local harness.

## Interview wording

### Explain the indexes and boundaries

"The matrix uses zero-based cell indexes. In the prefix table, I use row and
column boundaries: `pre[r][c]` stores the sum of the first r rows and first c
columns. It includes matrix rows 0 through r − 1 and columns 0 through c − 1.

With n rows there are n + 1 row boundaries, and with m columns there are m + 1
column boundaries. That is why the prefix table has size `(n + 1) × (m + 1)`.
Boundary zero represents an empty dimension, so the first prefix row and
column are zero. `pre[n][m]` covers the whole matrix."

### Explain construction

"To build `pre[i][j]`, I add the prefix above and the prefix to the left.
Their intersection is counted twice, so I subtract it once, then add the new
cell `matrix[i - 1][j - 1]`. The minus-one offsets map the prefix boundaries
to the last included cell's zero-based indexes."

```kotlin
pre[i][j] = pre[i - 1][j] + pre[i][j - 1] -
    pre[i - 1][j - 1] + matrix[i - 1][j - 1]
```

### Map a query to its boundaries

"The query gives inclusive cell indexes, from `(row1, col1)` through
`(row2, col2)`. The boundary before row1 is row1; the boundary after row2 is
row2 + 1. Similarly, the column boundaries are col1 and col2 + 1.

I start with `pre[row2 + 1][col2 + 1]`. I subtract the prefix above row1 and
the prefix to the left of col1. Their shared top-left rectangle was removed
twice, so I add it back once. This leaves exactly the requested cells."

```kotlin
pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] -
    pre[row2 + 1][col1] + pre[row1][col1]
```

For example, inclusive cell rows 1 through 2 use row boundaries 1 and 3;
inclusive cell columns 1 through 2 use column boundaries 1 and 3. Thus the
query uses `pre[3][3] - pre[1][3] - pre[3][1] + pre[1][1]`.

### Finish with complexity

"Preprocessing takes O(nm) time and O(nm) extra space. Each query takes O(1)
time. A query touching the top or left edge uses the stored zero boundary,
so it does not need a special case."

## Practice

[LeetCode 304 — Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/description/)
is the recap's submission target. The saved Solution.kt uses its zero-based
NumMatrix API directly. See [SOURCE.md](SOURCE.md) for contract details and the
mapping from the original AcWing source. Local validation is not an online
judge acceptance result.
