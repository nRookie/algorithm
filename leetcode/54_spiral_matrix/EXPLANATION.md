# 54. Spiral Matrix

## Contract and review

Given a nonempty rectangular matrix, return its elements in clockwise spiral
order, starting at the top-left cell. Do not modify the matrix.

**Your implementation is correct for this problem's nonempty input.** It
tracks the remaining rectangle and checks whether it is empty between sides.
These checks handle single rows, single columns, and the center of a spiral.

[54.kt](54.kt) preserves your algorithm, variable names, and explicit loops.
Formatting and comments are polished. The condition
`!(leftB <= rightB && upB <= downB)` is written equivalently as
`leftB > rightB || upB > downB`, and the next side's coordinates are assigned
after its empty-rectangle check. No traversal behavior changes.

## Your explanation, polished

“I represent all unvisited cells as a rectangle using four inclusive
boundaries: `upB`, `downB`, `leftB`, and `rightB`.

I visit its top row from left to right. That entire row is now finished, so
I increase `upB` to exclude it. I then visit the remaining right column from
top to bottom and decrease `rightB`. Next, I visit the remaining bottom row
from right to left and decrease `downB`. Finally, I visit the remaining left
column from bottom to top and increase `leftB`.

Each boundary update removes exactly the side just visited. The next side
uses the updated boundaries, so its corners are not visited twice.

After consuming a side, the remaining rectangle may be empty. I check for
that before starting the next side. Otherwise, I repeat the same process
on the smaller rectangle until every cell has been visited.”

The main idea is **consume a side, then remove that side from the remaining
rectangle**. The boundary being updated describes the side consumed, not
the direction of movement. For example, moving right consumes the top row,
so it changes `upB`, not `rightB`.

## Variable definitions

All four boundaries are inclusive. Unlike your `[left, right)` string
windows, this rectangle includes both ends of each coordinate range.

| Variable | Meaning | Initial value |
| --- | --- | --- |
| `m` | Number of rows | `matrix.size` |
| `n` | Number of columns | `matrix[0].size` |
| `upB` | First unvisited row | `0` |
| `downB` | Last unvisited row | `m - 1` |
| `leftB` | First unvisited column | `0` |
| `rightB` | Last unvisited column | `n - 1` |
| `row` | Row coordinate used while traversing the current side | Reset for each side |
| `col` | Column coordinate used while traversing the current side | Reset for each side |
| `ans` | Values already visited, in spiral order | Empty list |

The remaining rectangle exists exactly when:

```kotlin
leftB <= rightB && upB <= downB
```

Equality means one column or one row remains; it does not mean empty.
The rectangle is empty when either pair of boundaries crosses.

| Direction | Fixed coordinate | Moving coordinate | Remove consumed side |
| --- | --- | --- | --- |
| Right | `row = upB` | `col = leftB .. rightB` | `upB++` |
| Down | `col = rightB` | `row = upB .. downB` | `rightB--` |
| Left | `row = downB` | `col = rightB downTo leftB` | `downB--` |
| Up | `col = leftB` | `row = downB downTo upB` | `leftB++` |

Each row of this table uses boundaries after the preceding updates.

## Corrections to your handwritten explanation

- For a 3-by-3 matrix, initially `upB = 0`, not 2.
- A layer starts at `(row, col) = (upB, leftB)`, not `(leftB, upB)`.
  Rows correspond to vertical boundaries; columns to horizontal boundaries.
- After the top row, exclude that entire row with `upB++`.
- After the right column, use `rightB--`; `downB` changes after the bottom row.
- Your trace accidentally dropped `6` from the accumulated answer. Values
  already appended remain in `ans`.

Your executable code already uses these coordinates and updates correctly.

## Solution evolution

### 1. Simulate movement with a visited grid

Keep a current position, a direction cycling through right/down/left/up, and
a Boolean grid. Append the current cell and mark it visited. Before moving,
turn clockwise if the next cell is outside the matrix or already visited.
Stop after collecting `m * n` values.

This directly models the movement, takes O(mn) time, and uses O(mn) extra
visited storage, excluding the result. For the 3-by-3 example below, it turns
after 3, 9, and 7 as it reaches edges, then after 4 because 1 is already visited.

**What to say:** “I can simulate the spiral with directions and visited cells,
but the visited grid stores more detail than the shape of the traversal needs.”

### 2. Your solution: represent remaining cells with four boundaries

After consuming a complete side, all unvisited cells still form a rectangle.
Four boundaries therefore replace the visited grid. The next side never
crosses a consumed row or column because that boundary has moved inward.

Time remains O(mn); auxiliary working space falls to O(1), excluding the
output. This is a space improvement, not an asymptotic time improvement.
Producing all `mn` values already requires Ω(mn) time.

**What to say:** “I use the rectangular shape of the unvisited region to
replace individual visited flags with four boundaries.”

## Complete 3-by-3 trace

```text
1 2 3
4 5 6
7 8 9
```

Initially `(upB, downB, leftB, rightB) = (0, 2, 0, 2)`, `ans = []`.

| Side | Cells visited in order | Boundary after side | Remaining rectangle | `ans` after side |
| --- | --- | --- | --- | --- |
| Top → | `(0,0)=1`, `(0,1)=2`, `(0,2)=3` | `upB = 1` | Rows 1..2, columns 0..2 | `[1,2,3]` |
| Right ↓ | `(1,2)=6`, `(2,2)=9` | `rightB = 1` | Rows 1..2, columns 0..1 | `[1,2,3,6,9]` |
| Bottom ← | `(2,1)=8`, `(2,0)=7` | `downB = 1` | Row 1, columns 0..1 | `[1,2,3,6,9,8,7]` |
| Left ↑ | `(1,0)=4` | `leftB = 1` | Only `(1,1)` | `[1,2,3,6,9,8,7,4]` |
| Next top → | `(1,1)=5` | `upB = 2` | Empty: `upB > downB` | `[1,2,3,6,9,8,7,4,5]` |
| Stop | No further access | — | Empty | Return answer |

The inner loops advance `row` or `col` one position beyond the side after its
last visit. That temporary cursor is not accessed again; it is reset for the
next side. The boundaries, not these temporary cursors, define remaining work.

## Why the checks between sides matter

The outer loop checks whether a rectangle exists before visiting its top
side. Consuming that side can exhaust it before the next outer-loop check.

For `[[1, 2, 3]]`, the top traversal visits all three values and increments
`upB` from 0 to 1 while `downB` remains 0. The rectangle is now empty, so
the code must stop. Continuing through later sides without suitable guards
can revisit values from the same row.

For `[[1], [2], [3]]`, the top traversal visits 1 and the right traversal
visits 2 and 3. Decrementing `rightB` from 0 to -1 crosses `leftB = 0`, so
the second check stops the scan before any remaining side is attempted.

After the left side, the next outer-loop condition performs the needed check;
an additional immediate check there is unnecessary.

## Correctness and termination

At the beginning of each side, if the rectangle is nonempty, it contains
exactly the unvisited cells. The completed output is the spiral prefix before
that side. Initially, the whole matrix is unvisited and the prefix is empty.

Traversing the appropriate side visits each cell on that side once in the
required direction. Moving its boundary inward excludes exactly those cells,
leaving the other unvisited cells as a smaller rectangle. This preserves the
invariant. Updated boundaries exclude corners already visited on the previous
side.

If the boundaries cross, no unvisited cells remain and returning `ans` is
correct. Every side entered consumes at least one cell, so progress is finite
and the algorithm terminates.

Time is **O(mn)** because each cell is appended once. Working space is
**O(1)**, excluding the required **O(mn)** output list.

## Edge cases and recall

| Input | Expected result |
| --- | --- |
| `[[1]]` | `[1]` |
| `[[1,2,3]]` | `[1,2,3]` |
| `[[1],[2],[3]]` | `[1,2,3]` |
| `[[1,2],[3,4]]` | `[1,2,4,3]` |
| `[[1,2,3],[4,5,6]]` | `[1,2,3,6,5,4]` |
| `[[1,2,3],[4,5,6],[7,8,9]]` | `[1,2,3,6,9,8,7,4,5]` |

- Explain why moving right updates the top boundary.
- State which coordinate is fixed during each side traversal.
- Explain why equality between boundaries still represents unvisited cells.
- Explain why the outer-loop condition alone is insufficient.

Next review: trace a single column and state exactly which boundary crossing
ends the traversal.
