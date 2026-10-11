# 74. Search a 2D Matrix

## Contract and ordering

Return whether `target` occurs in a nonempty rectangular matrix. Each row is
sorted in nondecreasing order, and the first value of each row is greater
than the last value of the previous row. Do not modify the matrix.

These two ordering conditions make the entire row-by-row sequence sorted:

```text
Matrix:                   Virtual sequence:
 1   3   5   7            [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
10  11  16  20
23  30  34  60
```

Sorted rows alone are insufficient. For example, `[[1, 5], [2, 6]]` has
sorted rows but its row-by-row sequence `[1, 5, 2, 6]` is not sorted.

Source: [Official problem statement](https://leetcode.com/problems/search-a-2d-matrix/).

## Solution evolution

### 1. Physically flatten, then binary search

Your starting idea was to create a list:

```kotlin
val nums = matrix.flatMap { it.toList() }
```

Then use the lower-bound search from Search Insert Position. This is correct
with a guarded final check:

```kotlin
return l < nums.size && nums[l] == target
```

The guard matters because the lower bound can equal the sequence length
when every element is smaller than the target.

For `m` rows and `n` columns, flattening takes `O(m * n)` time and extra
space. Adding a logarithmic search does not remove this linear preparation
cost, so this approach does not meet the required `O(log(m * n))` time.

What to say:

> “Flattening gives me a sorted sequence, but copying every element costs
> linear time and space. I only need access to the middle element at each step.”

### 2. Access the flattened sequence virtually

Your improvement avoids creating the list. For virtual index `i`, access:

```kotlin
matrix[i / n][i % n]
```

The binary search operates on the same sequence, but each lookup calculates
its coordinates in constant time. This gives `O(log(m * n))` time and
`O(1)` auxiliary space.

What to say:

> “I can treat the matrix as a sorted array without copying it. Division
> gives the row, and remainder gives the column.”

## Proof of the virtual index conversion

Assume `m` rows, the same positive number `n` of columns in every row, and
zero-based indexes.

### From coordinates to a flat index

Before row `row`, there are exactly `row` complete rows, containing
`row * n` elements. Within that row, `column` elements precede the selected
element. Therefore:

```text
i = row * n + column
```

For example, row `1`, column `2` in a four-column matrix has index
`1 * 4 + 2 = 6`.

### From a flat index to coordinates

The integer division theorem says that for every nonnegative integer `i`
and positive integer `n`, there are unique integers `q` and `s` such that:

```text
i = q * n + s, where 0 <= s < n
q = i / n
s = i % n
```

Compare this with `i = row * n + column`. Since a valid column lies between
`0` and `n - 1`, uniqueness tells us:

```text
row = i / n
column = i % n
```

For `i = 6` and `n = 4`, `6 = 1 * 4 + 2`, so the coordinates are `(1, 2)`.

### Validity and completeness

If `0 <= i < m * n`, then `0 <= i / n < m` and `0 <= i % n < n`, so
the calculated coordinates are valid. Conversely, valid coordinates produce
an index between `0` and `m * n - 1`.

The two conversions undo each other. Thus, every virtual index names exactly
one cell, and every cell has exactly one virtual index: no omissions or
collisions.

### Ordering is a separate proof

The conversion proves that indexes correctly identify cells; it does not
prove that the values are sorted. Within each row, values are nondecreasing.
At each row boundary, the next row's first value exceeds the previous row's
last value. Hence the virtual sequence is sorted, making binary search valid.

**Limits:** The constant-width formula does not apply to ragged arrays.
For larger inputs, ensure that `m * n` fits the chosen integer type. The
problem's dimensions are small enough for Kotlin `Int`.

## Your reasoning and implementation, polished

You correctly moved from physical flattening to virtual access and reused
the boundary-search updates from problem 35. The important change is that
your final code starts with `r = m * n - 1`, rather than `r = m * n`.
That changes the invariant and the meaning of the terminal position.

Your implementation, with comments refined and logic preserved:

```kotlin
class Solution {
    fun searchMatrix(matrix: Array<IntArray>, target: Int): Boolean {
        val m = matrix.size
        val n = matrix[0].size
        var l = 0
        var r = m * n - 1

        // Before l: values < target.
        // Strictly after r: values >= target.
        while (l < r) {
            val mid = l + (r - l) / 2
            val midx = mid / n
            val midy = mid % n
            if (matrix[midx][midy] < target) {
                l = mid + 1
            } else {
                r = mid
            }
        }

        val x = l / n
        val y = l % n
        return matrix[x][y] == target
    }
}
```

### Correctness and termination

Let `A[i] = matrix[i / n][i % n]` and `N = m * n`. `A` is a mathematical
description, not an allocated array.

Your invariant is:

- `0 <= l <= r < N`.
- Every value strictly before `l` is smaller than the target.
- Every value strictly after `r` is greater than or equal to the target.

Initially, both outside regions are empty, so these statements hold.
If `A[mid] < target`, sorted order classifies every value through `mid` as
too small, justifying `l = mid + 1`. Otherwise, every value from `mid`
onward qualifies, justifying `r = mid` while retaining `mid` as a candidate.

Whenever `l < r`, `l <= mid < r`. Both updates strictly decrease `r - l`
without crossing the pointers, so the loop terminates with `l == r`.

If any value qualifies, let `p` be the first index with `A[p] >= target`.
Initially `p` lies in `[l, r]`. The smaller-value branch implies `p > mid`;
the other branch implies `p <= mid`. Therefore, neither update discards
`p`, and convergence gives `l = p`. Testing equality there correctly decides
whether the target exists.

If no value qualifies, every comparison takes the smaller-value branch.
`r` stays at `N - 1`, and `l` eventually reaches it. The final value is still
smaller than the target, so the function correctly returns `false`.

Thus your terminal index is the lower bound when one exists, and otherwise
the last element's index. This is sufficient for membership testing, but it
is not the insertion position `N` returned by problem 35.

### Trace of your exact code

Use the example matrix above with target `16`; initially `(l, r) = (0, 11)`.

| `l` before | `r` before | `mid` | Coordinates | Value | Update |
| --- | --- | --- | --- | --- | --- |
| 0 | 11 | 5 | `(1, 1)` | 11 | `l = 6` |
| 6 | 11 | 8 | `(2, 0)` | 23 | `r = 8` |
| 6 | 8 | 7 | `(1, 3)` | 20 | `r = 7` |
| 6 | 7 | 6 | `(1, 2)` | 16 | `r = 6` |
| 6 | 6 | — | `(1, 2)` | 16 | Loop ends; return `true` |

Corrections to the intermediate comments: with `[1, 2, 3, 4]`, `l = 0`
and `r = 4`, the first midpoint is index `2`, whose value is `3`.
With `r = 3`, it is index `1`, whose value is `2`. Keep values and indexes
distinct, and do not mix traces from different interval conventions.

## Other good implementations

### Option A: Direct membership binary search

For a Boolean result, this is my recommended version: it returns immediately
on equality and uses the simple invariant that any occurrence still lies in
the inclusive candidate interval `[l, r]`.

```kotlin
class Solution {
    fun searchMatrix(matrix: Array<IntArray>, target: Int): Boolean {
        val n = matrix[0].size
        var l = 0
        var r = matrix.size * n - 1

        while (l <= r) {
            val mid = l + (r - l) / 2
            val value = matrix[mid / n][mid % n]
            when {
                value < target -> l = mid + 1
                value > target -> r = mid - 1
                else -> return true
            }
        }
        return false
    }
}
```

Sorted order justifies discarding `mid` and everything on the impossible side.
Each unsuccessful iteration shrinks the candidate interval. When `l > r`,
it is empty, so the target is absent. This is a simpler membership proof,
with the same worst-case time and space as your solution.

### Option B: Reuse the exact lower-bound template from problem 35

Choose this version if you want one boundary-search template for both tasks.
It searches undecided elements in `[l, r)` and allows the result to be `total`.

```kotlin
class Solution {
    fun searchMatrix(matrix: Array<IntArray>, target: Int): Boolean {
        val n = matrix[0].size
        val total = matrix.size * n
        var l = 0
        var r = total

        while (l < r) {
            val mid = l + (r - l) / 2
            if (matrix[mid / n][mid % n] < target) {
                l = mid + 1
            } else {
                r = mid
            }
        }
        return l < total && matrix[l / n][l % n] == target
    }
}
```

The invariant and proof are exactly those in
[Search Insert Position](../35_search_insert_position/EXPLANATION.md).
Kotlin's short-circuit `&&` prevents an invalid access when `l == total`.
This also has the same worst-case time and space as your solution.

### Option C: Search for a row, then search within it

Binary search for the first row whose last value is at least the target.
If none exists, return false. Otherwise, binary search that row. Every
earlier row is too small, and every later row begins after the selected
row's last value, so only this row can contain the target.

This takes `O(log m + log n)` time, equivalently `O(log(m * n))` for
positive dimensions, and `O(1)` space. It is a valid alternative if thinking
in rows is more natural; it introduces two searches instead of one.

#### Your two-stage implementation

Your submitted code is correct for the problem's nonempty rectangular input.
Its logic is preserved below; the comments include the fallback when no
value qualifies.

```kotlin
class Solution {
    fun searchMatrix(matrix: Array<IntArray>, target: Int): Boolean {
        val m = matrix.size
        val n = matrix[0].size

        var top = 0
        var bottom = m - 1

        while (top < bottom) {
            val mid = top + (bottom - top) / 2
            // Find the first row whose last element is >= target,
            // or stop at the last row if none qualifies.
            if (target <= matrix[mid].last()) {
                bottom = mid
            } else {
                top = mid + 1
            }
        }

        var left = 0
        var right = n - 1
        while (left < right) {
            val mid = left + (right - left) / 2
            // Find the first element >= target in the selected row,
            // or stop at its last element if none qualifies.
            if (target <= matrix[top][mid]) {
                right = mid
            } else {
                left = mid + 1
            }
        }
        return target == matrix[top][left]
    }
}
```

#### Your explanation, polished

> “First, I binary search for the first row whose last element is greater
> than or equal to the target. Every earlier row ends below the target,
> so all its elements are too small. Every later row starts above the
> selected row's last element, so all its elements are too large.
> Therefore, the selected row is the only row that could contain the target.
>
> I then binary search within that row and test the remaining element for
> equality. If no row qualifies, my first search stops at the last row;
> the second search stops at its last element, and the equality check
> correctly returns false.”

The correction to your earlier wording is **greater than or equal to**, not
strictly greater: a target equal to a row's last element must keep that row.
Also, say “the first row whose last element is at least the target,” rather
than describing an entire row as greater than the target.

#### What inclusive bounds mean

Inclusive bounds include both endpoints. `[0, 3]` contains indexes
`0, 1, 2, 3`; `[0, 3)` contains `0, 1, 2` and excludes `3`.

Your row search uses the inclusive candidate interval `[top, bottom]`.
Your column search uses `[left, right]`. When the endpoints meet, one
candidate remains. The row search uses that row next; the column search
uses that element in the final equality check.

By contrast, problem 35 starts with `right = size`: the undecided elements
occupy the half-open interval `[left, right)`. When the endpoints meet,
no undecided elements remain, but the shared boundary gives the answer.

Inclusive bounds alone do not require stopping at one candidate. The direct
membership version above also uses inclusive bounds, but loops while
`left <= right`, excludes `mid` on both unequal branches, and stops when the
interval becomes empty. The meaning comes from the bounds **together with**
the loop condition and updates.

#### Why your searches stop at the last index when nothing qualifies

Consider a sorted, nonempty sequence of length `N` and your template:

```text
low = 0, high = N - 1
while low < high:
    mid = low + (high - low) / 2
    if value[mid] >= target: high = mid
    else: low = mid + 1
```

If every value is smaller than the target, every comparison takes the
`low = mid + 1` branch. `high` never changes from `N - 1`.

While `low < high`, `low <= mid < high`, so `mid + 1 <= high`. Thus low
strictly increases without crossing high. Eventually they meet at `N - 1`.
For `N = 1`, they already meet there and the loop does not run.

The loop stops because the pointers meet, not because a qualifying value
was found. Your final equality check distinguishes those outcomes.

With row endings `[3, 7, 11, 15]` and target `100`:

| `top` before | `bottom` before | `mid` | Row ending | Update |
| --- | --- | --- | --- | --- |
| 0 | 3 | 1 | 7 | `top = 2` |
| 2 | 3 | 2 | 11 | `top = 3` |
| 3 | 3 | — | — | Stop at the last row |

For matrix `[[1,3],[5,7],[9,11],[13,15]]`, the selected row is `[13,15]`:

| `left` before | `right` before | `mid` | Value | Update |
| --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 13 | `left = 1` |
| 1 | 1 | — | 15 | Stop; `100 == 15` is false |

#### Proof for both searches

For the template above, maintain:

- `0 <= low <= high < N`.
- All values before low are smaller than the target.
- All values strictly after high are greater than or equal to the target.

Both outside regions are initially empty. Sorted order preserves these
statements after either update, and each iteration strictly shrinks
`high - low` without crossing the pointers.

If a first qualifying index p exists, it initially belongs to `[low, high]`.
A smaller midpoint value implies `p > mid`; a qualifying midpoint value
implies `p <= mid`. Neither update discards p. At convergence, the sole
remaining index is therefore p. If no p exists, the search instead ends
at the last index, as proved above.

Apply this proof first to the sorted row endings, then to the selected row.
If a qualifying row exists, earlier rows are too small and later rows are
too large. Searching that row and testing equality correctly decides
membership. If no row qualifies, every matrix value is too small, and the
final equality check returns false. This proves the complete implementation.

#### Successful trace and complexity

For the original three-by-four example and target `16`:

| Search | Bounds before | `mid` | Compared value | Update |
| --- | --- | --- | --- | --- |
| Row | `top=0, bottom=2` | 1 | Row ending 20 | `bottom = 1` |
| Row | `top=0, bottom=1` | 0 | Row ending 7 | `top = 1` |
| Row | `top=1, bottom=1` | — | — | Select row `[10,11,16,20]` |
| Column | `left=0, right=3` | 1 | 11 | `left = 2` |
| Column | `left=2, right=3` | 2 | 16 | `right = 2` |
| Column | `left=2, right=2` | — | 16 | Return true |

The two searches run sequentially, so their times add:
`O(log m + log n)`, equivalent to `O(log(m * n))`. Indexing and `.last()`
on an `IntArray` take constant time. Extra space is `O(1)`; no row is copied.

Rehearse: why does selecting a qualifying row not guarantee a match?
Trace target `8` in the original matrix, then explain why a final equality
check is needed even though the selected row ends above the target.

| Approach | Worst-case time | Auxiliary space | Main reason to choose it |
| --- | --- | --- | --- |
| Physical flattening plus search | `O(m * n)` | `O(m * n)` | Simple baseline; misses required time |
| Your virtual boundary search | `O(log(m * n))` | `O(1)` | Preserves your implementation |
| Direct virtual membership search | `O(log(m * n))` | `O(1)` | Simple Boolean search and proof |
| Virtual lower bound with guard | `O(log(m * n))` | `O(1)` | Reuses the problem 35 template |
| Row search, then column search | `O(log m + log n)` | `O(1)` | Separates row and column reasoning |

All code above assumes the problem's nonempty rectangular input. For a
general API allowing empty input, check it before accessing `matrix[0]`.

## Interview explanation

> “The row ordering makes the matrix a sorted sequence when read row by row.
> Flattening would copy every element, so I access that sequence virtually.
> With `n` columns, index `i` maps to row `i / n` and column `i % n`, because
> `i` equals the number of elements in complete rows plus the column offset.
>
> For membership testing, I binary search an inclusive candidate interval.
> If the middle value is too small, I discard it and everything before it;
> if it is too large, I discard it and everything after it. Equality returns
> true. If the interval becomes empty, the target is absent. This takes
> logarithmic time in the number of cells and constant extra space.”

## Takeaways and rehearsal

- A logical sequence need not be physically allocated if each element can
  be accessed efficiently in its original storage.
- Prove index validity and one-to-one coverage separately from value ordering.
- Match initialization, updates, loop condition, invariant, and final access
  to the same interval convention.
- A boundary search may return the sequence length; membership testing then
  needs a bounds check before reading that position.

Practice proving the mapping at a row boundary: why does index `n - 1` map
to `(0, n - 1)`, while index `n` maps to `(1, 0)`? Then explain which matrix
ordering condition allows binary search across that boundary.
