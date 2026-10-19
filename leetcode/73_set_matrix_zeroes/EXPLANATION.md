# 73. Set Matrix Zeroes

Given a nonempty `m × n` integer matrix, if a cell originally contains `0`, set its entire row and column to `0`. Modify the matrix in place using O(1) auxiliary space.

The word **originally** matters: zeros introduced by our writes must not trigger additional rows or columns.

## Your reasoning, polished

You first considered using `2` as a temporary marker and later converting it to `0`. However, `2` may already occur in the input, so it cannot distinguish an original value from a marker. The signed 32-bit integer range is `-2^31` through `2^31 - 1`; no `Int` value is guaranteed to be unused.

You then considered copying `matrix[row - 1][col]` into `matrix[row][col]`. This overwrites the destination's original information, including whether it was zero, before that information has necessarily been recorded.

The useful question became: **what information do we actually need to preserve?** For each row and each column, we only need to know whether it originally contained at least one zero.

During our guided discussion, we chose the first column for row markers and the first row for column markers. You identified that a zero at `(1, 1)` should mark `(1, 0)` and `(0, 1)`, and assembled the correct implementation below.

One clarification to your explanation: `row0` and `col0` remember whether the first row and first column originally contained a zero. They do not record which individual elements were nonzero.

## Solution evolution

### 1. Record affected rows and columns separately

A straightforward correct baseline is to scan the original matrix and record two Boolean arrays:

- `zeroRows[row]`: this row originally contained a zero.
- `zeroCols[col]`: this column originally contained a zero.

In a second pass, zero a cell if either flag is true. Separating discovery from filling prevents newly written zeros from affecting our decisions.

This takes O(mn) time and O(m + n) auxiliary space. It explains the information needed, but does not meet the constant-space target.

### 2. Store those markers inside the matrix

Instead of allocating arrays, use existing boundary cells:

| Storage | Meaning after the marking pass |
| --- | --- |
| `matrix[row][0] == 0`, for `row >= 1` | This row originally contained a zero. |
| `matrix[0][col] == 0`, for `col >= 1` | This column originally contained a zero. |
| `row0` | The first row originally contained a zero. |
| `col0` | The first column originally contained a zero. |

When an original zero is found at `(row, col)`, write:

```kotlin
matrix[0][col] = 0
matrix[row][0] = 0
```

Using `0` as a marker is safe here because the marker has a designated location and meaning. An original zero in that location already means the corresponding row or column must be cleared.

The first row and first column also need their own final decisions. A single shared cell, `matrix[0][0]`, does not represent these two independent Boolean facts in this scheme, so we keep `row0` and `col0` separately.

This preserves O(mn) time while reducing auxiliary space to O(1).

## Kotlin implementation

This preserves your implementation and traversal order, with polished comments and braces.

```kotlin
class Solution {
    fun setZeroes(matrix: Array<IntArray>): Unit {
        val m = matrix.size
        val n = matrix[0].size
        var row0 = false
        var col0 = false

        // Record original zeros using the first row and column as markers.
        for (row in 0 until m) {
            for (col in 0 until n) {
                if (matrix[row][col] == 0) {
                    matrix[0][col] = 0
                    matrix[row][0] = 0
                    if (row == 0) row0 = true
                    if (col == 0) col0 = true
                }
            }
        }

        // Consume the markers without changing their storage.
        for (row in 1 until m) {
            for (col in 1 until n) {
                if (matrix[row][0] == 0 || matrix[0][col] == 0) {
                    matrix[row][col] = 0
                }
            }
        }

        // The markers are no longer needed; finish the boundaries.
        if (row0) {
            for (col in 0 until n) {
                matrix[0][col] = 0
            }
        }
        if (col0) {
            for (row in 0 until m) {
                matrix[row][0] = 0
            }
        }
    }
}
```

## Why recording the flags during this scan is safe

Your code does not require a separate preliminary scan of the boundaries because it visits rows from top to bottom and columns from left to right.

1. The first row is scanned before later rows can write markers into it. Within the first row, a zero at a later column can overwrite `(0, 0)`, but that cell has already been inspected.
2. In each later row, column `0` is inspected before a zero at a later column can overwrite that row's marker.
3. Interior cells are never modified during the marking pass.

Therefore, each cell's zero check sees its original value: newly introduced zeros are written only into already inspected cells. `row0` and `col0` consequently record original boundary zeros correctly. This reasoning depends on the traversal order; changing that order requires revisiting the proof.

## Dry run

Original matrix:

```text
       c0 c1 c2
r0      1  2  3
r1      4  0  6
r2      7  8  9
```

Initially, `row0 = false` and `col0 = false`.

### Marking pass

| Inspected cell | Value at inspection | Action |
| --- | --- | --- |
| `(0, 0)` | 1 | None |
| `(0, 1)` | 2 | None |
| `(0, 2)` | 3 | None |
| `(1, 0)` | 4 | None |
| `(1, 1)` | 0 | Set `(0, 1)` and `(1, 0)` to zero; both flags stay false. |
| `(1, 2)` | 6 | None |
| `(2, 0)` | 7 | None |
| `(2, 1)` | 8 | None |
| `(2, 2)` | 9 | None |

After marking:

```text
1 0 3
0 0 6
7 8 9
```

### Interior pass

| Cell | Row marker | Column marker | Action |
| --- | --- | --- | --- |
| `(1, 1)` | 0 | 0 | Write 0; already zero. |
| `(1, 2)` | 0 | 3 | Change 6 to 0. |
| `(2, 1)` | 7 | 0 | Change 8 to 0. |
| `(2, 2)` | 7 | 3 | Keep 9. |

The matrix becomes:

```text
1 0 3
0 0 0
7 0 9
```

Both flags are false, so neither boundary is cleared in full. This is the final result. The boundary cells changed during marking are already correctly zero because their corresponding columns or rows were affected.

## Why the boundaries must be finished last

Before the interior pass ends, the first row and first column still hold decisions for other cells. Clearing them early would destroy those markers.

For example:

```text
Original:       After marking:
1 0 3           0 0 3
4 5 6           4 5 6
```

Here `row0 = true` and `col0 = false`. If we clear the whole first row immediately, its column-2 marker becomes zero. The interior pass would then incorrectly erase `6`, even though its original row and column contained no zero. It would also incorrectly erase `4`.

The correct order is **record decisions → fill the interior → finish the boundaries**.

## Correctness argument

After the marking pass, for every nonfirst row, its first cell is zero exactly when that row originally contained a zero. An original boundary zero already supplies the marker; an original interior zero writes it. No other row can write that marker. The corresponding statement holds for every nonfirst column.

The flags correctly describe the original first row and first column because of the scan order explained above.

During the interior pass, the markers remain unchanged. Each interior cell is set to zero exactly when its original row or column contained a zero. Otherwise, its original value is retained.

Finally, if `row0` is true, the entire first row must be zero. If it is false, only first-row cells belonging to affected columns must be zero, and the column markers have already made precisely those changes. The same argument applies to the first column using `col0`.

All loops traverse finite index ranges, so the algorithm terminates with exactly the required matrix.

## Complexity and boundary cases

- **Time:** O(mn). The two matrix passes plus boundary cleanup take O(mn + m + n), which is O(mn) for a nonempty matrix.
- **Auxiliary space:** O(1). Only dimensions, loop indices, and two Boolean flags are stored outside the input.

The O(mn) worst-case time is optimal: every original cell must be inspected because an unseen zero could change the required output.

Useful boundary cases to reason through:

| Input | Flags after marking | Final result |
| --- | --- | --- |
| `[[1, 0, 3]]` | `row0 = true`, `col0 = false` | `[[0, 0, 0]]` |
| `[[1], [0], [3]]` | `row0 = false`, `col0 = true` | `[[0], [0], [0]]` |
| `[[0, 2], [3, 4]]` | Both true | `[[0, 0], [0, 4]]` |
| `[[1, 2], [3, 4]]` | Both false | Unchanged |
| `[[0]]` | Both true | `[[0]]` |

With a single row or column, the interior loops are empty; boundary cleanup still produces the correct result. These are reasoning examples, not a report of executed tests.

## Step-by-step interview explanation

Use the following as a spoken walkthrough while deriving and writing the solution. Explain the purpose of each pass before writing its loops.

### 1. Confirm the required behavior

“For each zero in the original matrix, I need to clear its entire row and column. Zeros that I introduce must not trigger further clearing. I’ll modify the matrix directly and aim for constant extra space.”

### 2. Explain why immediate clearing is unsafe

“If I clear a row and column as soon as I encounter a zero, later iterations may encounter the zeros I just wrote and incorrectly clear more cells. I need to record which rows and columns are affected before filling them.”

“A special integer marker such as `2` also does not work reliably because it can already occur in the input.”

### 3. Establish a straightforward correct approach

“I only need one Boolean per row and per column: did it originally contain a zero? I could record those in two arrays, then make a second pass and clear a cell when either its row flag or its column flag is true. That takes O(mn) time and O(m + n) extra space.”

### 4. Reduce the extra storage

“To remove those extra arrays, I can store the row flags in the first column and the column flags in the first row. When I find a zero at `(row, col)`, I set `matrix[row][0]` and `matrix[0][col]` to zero.”

For example, finding the middle zero below marks `(1, 0)` and `(0, 1)`:

```text
Original:       Marked:
1 2 3           1 0 3
4 0 6           0 0 6
7 8 9           7 8 9
```

“A zero already present at a marker location is fine: it already means that row or column must be cleared.”

### 5. Preserve the boundaries' own decisions

“The first row and column now serve as marker storage, so their current zeros will not tell me whether those boundaries originally needed clearing. I keep two Booleans: `row0` for an original zero in the first row, and `col0` for an original zero in the first column.”

Write the dimensions and initialize both flags to `false`.

### 6. Write the marking pass and explain its order

“I scan top to bottom and left to right. Whenever I encounter zero, I write its two markers. If the current position is in the first row or first column, I also set the corresponding Boolean.”

“This order lets me collect those Booleans during the same pass: I read the first row before later rows can change it, and I read each row's first cell before later columns can change it. Any newly written marker is at a position I have already inspected, so it cannot be mistaken for an original zero later in the scan.”

Write the first nested loop. At its end, state what has been established:

“For every interior cell, its row marker and column marker now correctly tell me whether its original row or column contained a zero.”

### 7. Fill the interior while preserving the markers

“Next, I iterate from row `1` and column `1`. If `matrix[row][0] == 0` or `matrix[0][col] == 0`, I set the current cell to zero. Otherwise, I leave it unchanged.”

“I exclude the first row and column because I still need their markers throughout this pass.”

Write the second nested loop. In the example, the result is:

```text
1 0 3
0 0 0
7 0 9
```

### 8. Finish the first row and first column

“Once every interior cell is processed, I no longer need the markers. If `row0` is true, I clear the first row. If `col0` is true, I clear the first column.”

“If a flag is false, I leave that boundary as it is: its marker zeros already correspond to cells that must be zero because of an affected column or row.”

Write the two final conditional loops. For the example above, both flags are false, so the matrix is already complete.

### 9. Close with correctness, complexity, and a boundary check

“The first pass records exactly the affected rows and columns. The second pass uses those records without modifying them, so each interior cell gets the correct value. The final two loops handle the boundaries using their saved original information.”

“The total time is O(mn), and the extra space is O(1). Each loop advances through a finite range. A single-row or single-column input also works: the interior pass is empty, and the boundary flags handle the result.”

For a quick check, use `[[1, 0, 3]]`: the marking pass gives `row0 = true` and `col0 = false`. Although marking changes `(0, 0)` to zero, that cell was already inspected, so `col0` stays false. Final row cleanup correctly produces `[[0, 0, 0]]`.

## Short interview recap

“Each row and column only needs one flag indicating whether it originally contained a zero. Separate flag arrays would use O(m + n) space, so I store those flags in the matrix's first column and first row. I keep two Booleans for whether the boundaries themselves originally contained zeros. My scan order reads each boundary cell before marker writes can change it. I then fill the interior using the markers and clear the boundaries last, once their markers are no longer needed. The solution takes O(mn) time and O(1) extra space.”

## Recall questions

1. Why can a designated boundary cell safely use zero as a marker, even though an arbitrary temporary value such as `2` is unsafe?
2. Why does this implementation record original boundary zeros correctly without a preliminary scan?
3. What information would be destroyed by clearing the first row before processing the interior?
