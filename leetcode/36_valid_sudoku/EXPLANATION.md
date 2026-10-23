# 36. Valid Sudoku

## Contract and review

Given a 9-by-9 board containing digits `'1'` through `'9'` and `'.'` for empty
cells, check whether any filled digit repeats in a row, column, or 3-by-3 box.
The board need not be complete. Validity here does not require proving that
the board can be solved. Do not modify the board.

**Your implementation is correct under this input contract.** The code uses
the correct box formula; one explanatory comment omitted the final `/ 3`.
The correct formula is `(row / 3) * 3 + col / 3`.

The polished submission is in [36.kt](36.kt).

## Your thought process, expressed clearly

“I only need to detect repeated digits among the filled cells. Each filled
cell belongs to exactly one row, one column, and one 3-by-3 box, so I can check
all three rules while visiting the board once.

I create three Boolean tables. `rows[r][d]` records whether digit index `d`
has already appeared in row `r`. `columns[c][d]` records the same information
for column `c`, and `blocks[b][d]` records it for box `b`.

I scan the board row by row and skip empty cells. For a filled cell, I convert
its character to a zero-based digit index and calculate its box index. If
any of its three table entries is already true, an earlier cell has the same
digit in that region, so the board is invalid. Otherwise, I mark all three
entries and continue.

If the scan finishes without finding a duplicate, all three rules hold for
every filled cell, so I return true.”

The important invariant is more precise than “the board does not change”:
**before processing a cell, the tables describe exactly the filled cells
already processed.** Not modifying the board alone would not establish that
the tables are correct.

## Variable definitions

| Variable | Meaning |
| --- | --- |
| `matrix` | Input board; `'.'` denotes an empty cell |
| `n` | Board side length, fixed at 9 |
| `row`, `col` | Zero-based coordinates of the current cell |
| `char` | Character stored in the current cell |
| `digitIndex` | Digit's zero-based table index: `'1' → 0`, ..., `'9' → 8` |
| `block` | Zero-based index of the current cell's 3-by-3 box |
| `rows[r][d]` | Whether an earlier cell in row `r` contained digit index `d` |
| `columns[c][d]` | Whether an earlier cell in column `c` contained digit index `d` |
| `blocks[b][d]` | Whether an earlier cell in box `b` contained digit index `d` |

## Improving the digit conversion

Your original expression is correct:

```kotlin
val digit = char - '0' - 1
```

It first converts `'1'..'9'` to numbers 1..9, then subtracts one for indexing.
The same mapping can be expressed directly:

```kotlin
val digitIndex = char - '1'
```

| Character | `char - '0' - 1` | `char - '1'` |
| --- | --- | --- |
| `'1'` | `1 - 1 = 0` | 0 |
| `'5'` | `5 - 1 = 4` | 4 |
| `'9'` | `9 - 1 = 8` | 8 |

Subtracting two Kotlin `Char` values produces an `Int` difference. Because
the digit characters are consecutive, subtracting `'1'` directly gives the
desired index. This is a clarity improvement, not a meaningful change in
algorithmic complexity.

Use the name `digitIndex` to distinguish an array index from the digit's
numeric value. `char.digitToInt() - 1` is another readable option, but the
direct offset is sufficient for this problem's known character range.

The polished code also replaces the original `if (char.isDigit())` wrapper
with:

```kotlin
if (char == '.') continue
val digitIndex = char - '1'
```

This expresses the actual input contract: skip empty cells; every remaining
cell is a digit from `'1'` through `'9'`. `isDigit()` is broader than that
range, so it should not be interpreted as general validation for this index
calculation. If arbitrary input were allowed, validate `'1'..'9'` explicitly
before indexing. That extra validation is unnecessary for this judge.

Finally, `BooleanArray(n)` already initializes every entry to `false`; the
explicit `{ false }` initializer is unnecessary.

## Deriving the box formula

First identify the row and column within the grid of boxes:

```text
boxRow = row / 3       // 0, 1, or 2
boxCol = col / 3       // 0, 1, or 2
```

Integer division groups cell coordinates 0..2 together, 3..5 together, and
6..8 together. Flatten the box coordinates using three boxes per row:

```text
block = boxRow * 3 + boxCol
      = (row / 3) * 3 + col / 3

Box indexes:
0 1 2
3 4 5
6 7 8
```

For `(row, col) = (2, 5)`, `boxRow = 0`, `boxCol = 1`, so `block = 1`.
This is the second box in human counting, but its array index is 1.
Using `+ col` instead would mix a cell coordinate with a box coordinate.

## Solution evolution

### 1. Check each region independently

For every row, create fresh digit-presence state and check for repetitions.
Repeat for every column and every box. This directly implements the three
rules and is a correct, straightforward baseline.

Each cell participates in three checks. On the fixed 9-by-9 board this uses
O(1) time and space. If generalized to a side length N with appropriate box
dimensions, it takes O(N²) time and can reuse O(N) presence storage for one
region at a time.

**What to say:** “I could validate each row, column, and box separately, using
a fresh set of seen digits for each region.”

### 2. Your approach: check all three regions during one traversal

Each cell already tells us which row, column, and box it belongs to. Maintain
all region tables simultaneously and update its three entries in one visit.

This consolidates the traversal and the duplicate-check logic. It does not
improve the asymptotic time bound: both approaches are O(N²) for a generalized
board. Your approach uses O(N²) table space instead of reusing one region's
O(N) state. For this problem, all sizes are fixed and small.

**What to say:** “I keep one presence table per region type, so each cell can
check all three constraints immediately.”

## Compact complete trace

Consider a board with `'5'` at `(0, 0)` and `(1, 1)` and `'.'` everywhere else.
These digits are in different rows and columns but the same box. The table
groups the intervening empty cells, which all take the identical skip branch.

| Visited cell(s) | Action | Relevant state |
| --- | --- | --- |
| Before scanning | Initialize tables | All entries false |
| `(0, 0) = '5'` | `digitIndex = 4`, `block = 0`; all checks false; mark | `rows[0][4]`, `columns[0][4]`, `blocks[0][4]` become true |
| `(0, 1)` through `(0, 8)` | Skip eight empty cells | Unchanged |
| `(1, 0)` | Skip empty cell | Unchanged |
| `(1, 1) = '5'` | Row and column entries false; `blocks[0][4]` true | Return false before marking |
| Remaining cells | Not visited after return | — |

If the second `'5'` is removed, all remaining cells are skipped and the scan
returns true. An entirely empty board also returns true.

## Correctness and complexity

Initially, no cells have been processed and every table entry is false, so
the invariant holds. Skipping an empty cell preserves it. For a filled cell,
a true entry identifies an earlier equal digit in one of its regions, which
violates a rule. If no entry is true, marking the three entries records this
cell and preserves the invariant.

If a duplicate pair exists, whichever cell is visited second finds the entry
set by the first. Thus finishing without a conflict proves that no row,
column, or box contains a repeated filled digit. The two finite loops visit
at most 81 cells, so termination is immediate.

For the fixed board, time and auxiliary space are both **O(1)**: at most 81
cell visits and `3 * 9 * 9 = 243` Boolean entries, plus array overhead.
For a generalized N-by-N board, this implementation's time and table space
are both O(N²).

## Recall

- Why must checks happen before marking the current digit?
- What exactly does `rows[row][digitIndex]` describe before each cell?
- Why does `char - '1'` produce an index rather than the numeric digit?
- Derive the box index as “box row × boxes per row + box column.”
- Why can an incomplete board be valid without being a proven solvable puzzle?

Next review: explain the invariant aloud, then derive the box index for
cell `(7, 4)` without memorizing the formula.
