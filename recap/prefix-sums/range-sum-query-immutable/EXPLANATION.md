# Immutable range sums: explaining prefix boundaries

This recap polishes the learner's supplied `NumArray` implementation and
boundary ("hole") explanation. The implementation is correct; the original
comments needed the endpoint corrections listed below.

## Contract

The input stays unchanged after preprocessing. Each query supplies zero-based
element indexes `left` and `right`, with both endpoints included. Return their
range sum. Assume valid indexes: `0 <= left <= right < nums.size`.

This matches [LeetCode 303: Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/description/)
(Easy; official statement checked during this recap). The statement was publicly
readable; submission access was not tested.

The original [AcWing implementation](../../../acwing/basic/795.cpp) uses
one-based query positions and standard input/output. Its formula is
`pre[r] - pre[l - 1]`. The supplied Kotlin class adapts the same idea to
zero-based element indexes and a constructor/method interface. Original AcWing
constraints were not independently verified.

## Solution evolution

### 1. Sum each requested interval directly

For a query, scan from `left` through `right` and add the values. This works
because it visits exactly the requested elements once. A query costs
O(right - left + 1) time and O(1) auxiliary space. With n elements and q queries,
the worst-case total query cost is O(nq).

What to say: "A straightforward approach is to scan each requested interval.
That uses constant extra space, but overlapping queries repeat additions."

### 2. Store cumulative sums once

Because the input does not change, sums computed during preprocessing can be
reused. A range sum is the difference between two prefixes: one ending just
after the range, and one ending just before it.

What to say: "I can avoid repeated scans by preprocessing prefix sums. Each
query then needs two lookups and one subtraction."

| Approach | Preprocessing | One query | Total for q queries | Extra space |
| --- | --- | --- | --- | --- |
| Scan each range | None | O(n) worst case | O(nq) | O(1) |
| Prefix sums | O(n) | O(1) | O(n + q) | O(n) |

## Your boundary reasoning, polished

"I think of prefix indexes as boundaries between elements. For n elements,
there are n + 1 boundaries, numbered 0 through n. Boundary b has exactly b
elements before it. I define `preSum[b]` as the sum of those first b elements."

```text
Boundary:  0     1     2     3     4
             [1]   [2]   [3]   [4]
Element:      0     1     2     3

preSum:    0     1     3     6    10
```

Equivalently, `preSum[b]` sums the half-open element interval `[0, b)`:
index 0 is included and index b is excluded. Boundary 0 represents the empty
prefix, so `preSum[0] = 0`. Boundary n represents the entire input.

"Boundary" is more conventional interview terminology than "hole".
The statement "sum of the first b elements" is enough to define the idea
without drawing a diagram.

## Build the prefix sums

Before processing element i, `preSum[i]` already contains the sum of the first
i elements. Including `nums[i]` extends that prefix by one element:

```kotlin
preSum[i + 1] = preSum[i] + nums[i]
```

For `nums = [1, 2, 3, 4]`, the complete construction is:

| Step | Read | Write | preSum after the step |
| --- | --- | --- | --- |
| Initialize | — | All entries initialized to 0 | `[0, 0, 0, 0, 0]` |
| i = 0 | preSum[0] = 0, nums[0] = 1 | preSum[1] = 1 | `[0, 1, 0, 0, 0]` |
| i = 1 | preSum[1] = 1, nums[1] = 2 | preSum[2] = 3 | `[0, 1, 3, 0, 0]` |
| i = 2 | preSum[2] = 3, nums[2] = 3 | preSum[3] = 6 | `[0, 1, 3, 6, 0]` |
| i = 3 | preSum[3] = 6, nums[3] = 4 | preSum[4] = 10 | `[0, 1, 3, 6, 10]` |
| Finished | Every element processed | — | `[0, 1, 3, 6, 10]` |

Uncomputed entries being zero does not make them valid prefix sums yet.
The loop advances through n elements and finishes after writing `preSum[n]`.

## Map the query's element indexes to boundaries

The API receives element indexes. The prefix table uses boundary indexes.

| Query endpoint | Boundary needed | Boundary index |
| --- | --- | --- |
| left | Immediately before the first included element | left |
| right | Immediately after the last included element | right + 1 |

Therefore the inclusive range `[left, right]` corresponds to the half-open
interval `[left, right + 1)`, giving:

```kotlin
preSum[right + 1] - preSum[left]
```

`preSum[right + 1]` includes everything through element right.
`preSum[left]` includes everything strictly before element left.
Subtracting cancels the shared earlier elements and leaves precisely the
requested interval. This cancellation works with negative values too.

For `sumRange(1, 2)` on `[1, 2, 3, 4]`:

```text
preSum[3] - preSum[1]
= (1 + 2 + 3) - 1
= 2 + 3
= 5
```

## Your implementation with polished comments

This preserves the supplied algorithm and `IntArray` storage. Only the
explanatory comments are rewritten.

```kotlin
class NumArray(nums: IntArray) {
    // preSum[b] is the sum of the first b elements: nums[0 until b].
    // n elements have n + 1 boundaries, including the empty prefix.
    private val preSum = IntArray(nums.size + 1)

    init {
        for (i in nums.indices) {
            // Extend the prefix by including the element at index i.
            preSum[i + 1] = preSum[i] + nums[i]
        }
    }

    fun sumRange(left: Int, right: Int): Int {
        // Keep elements left through right, inclusive:
        // remove the prefix before left from the prefix through right.
        return preSum[right + 1] - preSum[left]
    }
}
```

For the collection version preferred in recap, change only the storage line:

```kotlin
private val preSum = MutableList(nums.size + 1) { 0 }
```

The constructor parameter stays `IntArray` to match the judge interface.
The recurrence and query expression stay identical. The list version has the
same asymptotic costs, but boxed integers add memory overhead compared with
`IntArray` on the JVM.

## Corrections to the original explanation

- Four elements have five boundaries numbered 0 through 4. Boundary 5 does
  not exist for this input.
- `preSum[4]` includes the element at index 3. It excludes index 4, which is
  already beyond the input.
- `preSum[left]` includes elements before left; subtracting it removes them
  from the query result. Be explicit about whether you mean the stored prefix
  or the result after subtraction.
- `preSum[ei + 1] - preSum[ei]` gives one element. For a general range, use
  separate element indexes: `preSum[right + 1] - preSum[left]`.

## Correctness and boundary checks

Construction is correct by induction: the empty prefix has sum zero; adding
element i to the correct prefix of length i produces the correct prefix of
length i + 1. Thus every needed prefix is correct after the loop. The query
is correct because subtracting the shared prefix cancels exactly the elements
before left.

For `[1, 2, 3, 4]`:

| Query | Expression | Result |
| --- | --- | --- |
| First element, [0, 0] | preSum[1] - preSum[0] | 1 |
| Last element, [3, 3] | preSum[4] - preSum[3] | 4 |
| Whole input, [0, 3] | preSum[4] - preSum[0] | 10 |
| Interior range, [1, 2] | preSum[3] - preSum[1] | 5 |

No special branch is needed when left is zero because the empty prefix is
stored explicitly. Valid right indexes are at most n - 1, so right + 1 is
at most n and fits the n + 1 prefix entries.

Under the verified LeetCode limits (at most 10,000 elements, each with
absolute value at most 100,000), prefix and range sums fit in Kotlin `Int`.
For a different contract with larger sums, use `Long` storage and arithmetic.
If values change after construction, these stored prefixes describe the old
input; this implementation provides no update operation.

## Interview version

"We need to answer inclusive range-sum queries on an array that stays unchanged.
A straightforward approach scans each requested range, which takes O(n) time
per query in the worst case. Since queries can repeat work, I preprocess
prefix sums.

I define `preSum[b]` as the sum of the first b elements. Its index represents
a boundary, so n elements need n + 1 prefix entries. `preSum[0]` is zero for
the empty prefix. I build the table with
`preSum[i + 1] = preSum[i] + nums[i]`.

For a query from left through right, the boundary before left is left and
the boundary after right is right + 1. I return
`preSum[right + 1] - preSum[left]`. This removes everything before left and
leaves exactly the requested elements.

Preprocessing takes O(n) time and O(n) extra space. Each query takes O(1)
time, so q queries take O(n + q) time including preprocessing."
