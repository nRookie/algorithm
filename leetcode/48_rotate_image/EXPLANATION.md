# 48. Rotate Image

## Contract and review

Rotate an n-by-n matrix 90 degrees clockwise in place, using O(1) auxiliary
space. The input is a nonempty square matrix.

**Your implementation is correct.** The missing connection is the geometric
meaning of the first pass: swapping top and bottom rows is a reflection
across the horizontal middle line, **not a 180-degree rotation**.

Your two operations are:

1. Reverse the order of rows: top becomes bottom, bottom becomes top.
2. Transpose across the main diagonal: exchange row and column coordinates.

Together they move every original element `(r, c)` to `(c, n - 1 - r)`,
which is exactly a 90-degree clockwise rotation.

## Your reasoning, preserved and clarified

You first observed that an original row becomes a column: the first row
becomes the last column, the middle row becomes the middle column, and the
last row becomes the first column. You wrote a correct extra-matrix approach
and then looked for a constant-space transformation. You considered saving
a row, a 45-degree rotation, and a 180-degree rotation before trying a row
reversal followed by diagonal swaps.

The useful observation you reached is that **two simple swaps-based
transformations can produce the desired coordinate mapping**. Your code
implements this correctly; only the name “180-degree rotation” was wrong.
The proof below explains the transformation you actually implemented rather
than treating that mistaken name as part of the solution.

For example, a true 180-degree rotation would produce:

```text
Original             Reverse row order       Actual 180° rotation
1 2 3                7 8 9                   9 8 7
4 5 6                4 5 6                   6 5 4
7 8 9                1 2 3                   3 2 1
```

Your first pass changes row coordinates but leaves column coordinates alone.
A true 180-degree rotation changes both.

## Solution evolution

### 1. Use an extra matrix to express the destination directly

An original element at row `r`, column `c` moves to:

```text
new row    = c
new column = n - 1 - r
```

Why? The original top row becomes the rightmost column. More generally,
original row `r` becomes column `n - 1 - r`. Reading that original row from
left to right becomes reading its destination column from top to bottom,
so original column `c` becomes the new row.

The direct assignment is:

```kotlin
rotated[c][n - 1 - r] = matrix[r][c]
```

Equivalently, ask where each destination cell gets its value:

```kotlin
rotated[i][j] = matrix[n - 1 - j][i]
```

Your commented code uses this second formula correctly. The earlier comment
`matrix[n - j][i]` was off by one: at `j = 0`, it would access row `n`,
which is outside the matrix. Valid indexes end at `n - 1`.

This approach takes O(n²) time and O(n²) auxiliary space. Copying the result
back would mutate the original matrix but would still violate the O(1)
extra-space requirement.

**What to say:** “I know the destination of each element, but assigning into
a new matrix uses quadratic extra space. I need to realize that mapping
using in-place operations.”

### 2. Your solution: compose a row reversal and a transpose

Both operations can be performed by swapping pairs of elements, requiring
only one temporary value. Their composition produces the required mapping,
so a second matrix is unnecessary.

The total time stays O(n²), while auxiliary space becomes O(1).

**What to say:** “I can split the target coordinate mapping into two simple
transformations: reverse the row index, then exchange the coordinates. Each
transformation can be done with independent swaps.”

| Approach | Time | Auxiliary space | Meets in-place requirement? |
| --- | --- | --- | --- |
| Fill a new matrix | O(n²) | O(n²) | No |
| Reverse rows, then transpose | O(n²) | O(1) | Yes |

## How to discover the operations instead of guessing

Intuition can suggest transformations, but the coordinate mapping lets you
derive and verify them. Start with the required destination, before choosing
any loops:

```text
Original position:    (r, c)
Required destination: (c, n - 1 - r)
```

Compare the two expressions. The original row coordinate must be reversed
(`r → n - 1 - r`), and the two coordinates must exchange places. Those are
exactly the effects of reversing row order and transposing:

```text
Reverse the row coordinate first:
(r, c) → (n - 1 - r, c)

Then exchange the coordinates:
(n - 1 - r, c) → (c, n - 1 - r)
```

This gives your algorithm without guessing a rotation angle. The geometric
picture helps establish the desired mapping; the algebra determines whether
a proposed sequence of operations actually achieves it.

You can also derive a different sequence by exchanging coordinates first:

```text
(r, c) → (c, r) → (c, n - 1 - r)
```

After the exchange, the original row coordinate is now the **column**
coordinate. Therefore the second operation must reverse columns within each
row, not reverse row order.

| First operation | Second operation | Combined destination |
| --- | --- | --- |
| Reverse row order | Transpose | `(c, n - 1 - r)` |
| Transpose | Reverse each row's elements | `(c, n - 1 - r)` |

Use this mental model: **derive the destination → decompose the mapping →
implement each transformation**. Deriving the mapping proves where elements
belong; the swap ranges separately prove that the in-place implementation
does not overwrite values or undo its own work.

The reusable concept is recorded in the
[concepts cheatsheet](../../study-notes/algorithm-concepts-cheatsheet.md#derive-rearrangements-by-composing-index-mappings).

## Coordinate proof: follow one original element

Let an arbitrary original element start at `(r, c)`.

**After reversing row order:**

```text
(r, c) → (n - 1 - r, c)
```

**After transposing:** exchange its current row and column:

```text
(n - 1 - r, c) → (c, n - 1 - r)
```

Therefore the combined mapping is:

```text
(r, c) → (n - 1 - r, c) → (c, n - 1 - r)
```

This equals the desired clockwise-rotation mapping for every original cell.
Because both operations are swaps, they preserve all values without losing
or duplicating any element. Together, these facts prove the algorithm.

You can also prove it by reading a final position. Let `A` be the original
matrix, `B` the row-reversed matrix, and `C` the transposed result:

```text
B[i][j] = A[n - 1 - i][j]
C[i][j] = B[j][i] = A[n - 1 - j][i]
```

This is exactly your extra-matrix formula. `A`, `B`, and `C` name mathematical
states here; the implementation does not allocate those extra matrices.

### The order matters

If you transpose first and then reverse row order, the mapping becomes:

```text
(r, c) → (c, r) → (n - 1 - c, r)
```

That is a 90-degree counterclockwise rotation. The two operations cannot be
reordered freely. Another clockwise method is transpose first, then reverse
the elements within each row; that is a different second operation from yours.

## Variable definitions

| Variable | Meaning |
| --- | --- |
| `matrix` | The same mutable matrix throughout both transformations |
| `n` | Number of rows and columns |
| `row`, `col` in the first pass | Cell in the top half whose value is swapped with the mirrored bottom-half cell |
| `n - row - 1` | Mirror row on the opposite side of the horizontal middle line |
| `row`, `col` in the second pass | Cell strictly below the main diagonal |
| `matrix[col][row]` | Its mirror cell above the main diagonal |
| `placeholder` | Temporary original value needed to complete one swap without overwriting it |

`row` and `col` are loop coordinates for the current transformation. They do
not permanently identify where a particular original element now resides.

## Your implementation with polished comments

The executable logic and variable names below match your supplied code.

```kotlin
class Solution {
    fun rotate(matrix: Array<IntArray>): Unit {
        val n = matrix.size

        // Reverse row order: (r, c) -> (n - 1 - r, c).
        // Visit only the top half so each mirrored pair is swapped once.
        for (row in 0 until n / 2) {
            for (col in 0 until n) {
                val placeholder = matrix[row][col]
                matrix[row][col] = matrix[n - row - 1][col]
                matrix[n - row - 1][col] = placeholder
            }
        }

        // Transpose: (r, c) -> (c, r).
        // Visit only cells below the diagonal so each pair is swapped once.
        for (row in 0 until n) {
            for (col in 0 until row) {
                val placeholder = matrix[row][col]
                matrix[row][col] = matrix[col][row]
                matrix[col][row] = placeholder
            }
        }
    }
}
```

## Loop boundaries: why these exact ranges?

Kotlin's `until` includes its start and excludes its end. Integer division
`n / 2` rounds down for positive `n`.

### First pass: `row in 0 until n / 2`

The mirror of row `row` is `n - 1 - row`. Swapping the top member of each
pair is enough:

| n | Visited row indexes | Row pairs swapped | Untouched middle row |
| --- | --- | --- | --- |
| 1 | None | None | 0 |
| 3 | 0 | 0 ↔ 2 | 1 |
| 4 | 0, 1 | 0 ↔ 3, 1 ↔ 2 | None |
| 5 | 0, 1 | 0 ↔ 4, 1 ↔ 3 | 2 |

For odd n, the middle row mirrors itself, so it is already in the right
position for this transformation. For even n, there are exactly n/2 pairs.

If the loop visited every row, it would swap each pair twice and undo the
reversal. For n = 3, swapping row 0 with row 2 and later row 2 with row 0
returns them to their original order.

The inner range `col in 0 until n` visits every column in the two rows.
We need all n element swaps to exchange their complete contents. It excludes
column n because valid column indexes are 0 through n - 1.

**Invariant:** after each completed outer iteration, all row pairs processed
so far have exchanged their entire contents; unprocessed pairs are unchanged.

### Second pass: `row in 0 until n`, `col in 0 until row`

The main diagonal has coordinates where `row == col`. Those cells map to
themselves under transpose and need no swap.

The condition `col < row` selects the lower triangle, excluding the diagonal:

```text
n = 4; X marks a visited cell, D the diagonal.

      col 0 1 2 3
row 0     D . . .
row 1     X D . .
row 2     X X D .
row 3     X X X D
```

Every off-diagonal pair consists of `(r, c)` and `(c, r)`. Exactly one lies
below the diagonal, so iterating over that triangle swaps each pair exactly
once. At row 0, `0 until 0` is empty, which is intentional.

The outer loop must reach row n - 1 because its lower-triangle cells still
need swapping. It excludes n to remain within the matrix.

Using all columns for each row would swap `(r, c)` with `(c, r)` and later
swap them back. For a 2-by-2 matrix, swapping `(0,1)` with `(1,0)` and then
`(1,0)` with `(0,1)` cancels the transpose.

You could instead visit the upper triangle with
`col in row + 1 until n`. Choose one triangle, not both.

**Invariant:** after each swap, that off-diagonal pair has its transposed
values. No later iteration touches the same pair, so completed swaps stay
correct. Unvisited pairs remain unchanged until their own iteration.

## Complete 3-by-3 execution trace

Initial state:

```text
1 2 3
4 5 6
7 8 9
```

Here n/2 = 1, so the first pass visits only row 0 and swaps it with row 2.
Matrices in the table use `/` to separate rows.

| Pass | `(row, col)` | Swap | Matrix after swap |
| --- | --- | --- | --- |
| Reverse rows | `(0,0)` | 1 ↔ 7 | `7 2 3 / 4 5 6 / 1 8 9` |
| Reverse rows | `(0,1)` | 2 ↔ 8 | `7 8 3 / 4 5 6 / 1 2 9` |
| Reverse rows | `(0,2)` | 3 ↔ 9 | `7 8 9 / 4 5 6 / 1 2 3` |
| Transpose, row 0 | No inner iteration | None | Unchanged |
| Transpose | `(1,0)` | 4 ↔ 8 | `7 4 9 / 8 5 6 / 1 2 3` |
| Transpose | `(2,0)` | 1 ↔ 9 | `7 4 1 / 8 5 6 / 9 2 3` |
| Transpose | `(2,1)` | 2 ↔ 6 | `7 4 1 / 8 5 2 / 9 6 3` |
| End | Both passes complete | — | Return Unit; matrix is rotated |

Final state:

```text
7 4 1
8 5 2
9 6 3
```

For one concrete element, original value 2 starts at `(0,1)`, moves to
`(2,1)` after row reversal, and then to `(1,2)` after transpose. This agrees
with `(r,c) → (c,n-1-r)`.

## Complexity and boundaries

- First pass: `floor(n/2) * n` swaps.
- Second pass: `0 + 1 + ... + (n-1) = n(n-1)/2` swaps.
- Total time: O(n²); auxiliary space: O(1). Loop variables and one temporary
  value do not grow with the input, and no second matrix is allocated.
- Both passes use finite ranges, so termination is guaranteed.

For n = 1, both passes perform zero swaps, correctly leaving the only value
unchanged. For odd n, the first pass preserves the middle row; the second
pass can still move its off-diagonal elements. Being untouched in the first
pass does not mean a cell stays fixed throughout the whole algorithm.

This method relies on a square matrix. An m-by-n matrix with m != n would
rotate to an n-by-m shape, and these same in-place loops would not apply.

The execution trace above was checked manually; no executable tests were
run as part of saving this Markdown explanation.

## Interview explanation and recall

“A clockwise rotation maps `(r, c)` to `(c, n - 1 - r)`. Reversing the row
order first maps it to `(n - 1 - r, c)`, and transposing then gives exactly
the desired destination. I swap only half the row pairs and one triangle
of off-diagonal cells, so each pair is processed once. This takes O(n²)
time and O(1) extra space.”

- Explain the difference between reversing row order and rotating 180 degrees.
- Derive the final coordinates by composing the two transformations.
- Explain why the first loop visits half the rows but every column.
- Explain why the transpose visits only one triangle and skips the diagonal.
- Predict what happens if the two operations are performed in reverse order.

Next review: follow an arbitrary coordinate through both operations before
looking at any concrete matrix. That coordinate proof explains every size
at once; the small trace checks the implementation's boundaries.
