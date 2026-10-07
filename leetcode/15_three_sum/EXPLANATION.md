# 3Sum

Return every unique value triplet whose sum is zero, using three distinct array
indexes. Different index combinations producing the same three values count as
one result. Repeated values within a triplet are allowed when enough occurrences
exist: `[0, 0, 0]` is valid with three zeros.

## Your reasoning, polished

“A straightforward solution checks all triples with three nested loops. I also
considered mapping each value to its indexes, then checking whether a pair's
complement occurs at an index after that pair.

Since the answer contains values rather than original indexes, I can sort the
array. For each fixed index `i`, I search for two values in the suffix whose sum
is `-nums[i]`, using `left = i + 1` and `right = n - 1`.

If the total is too small, I move `left` right. If it is too large, I move `right`
left. If it equals zero, I record the triplet and move both pointers inward.

To avoid duplicate triplets, I handle duplicates in three places. I skip an
anchor if it has the same value as the previous anchor. After pointer movement,
I skip repeated values at `left` and `right`. Sorting makes equal values adjacent,
so these checks prevent repeating the same value triplet without removing
occurrences needed for triplets such as `[-1, -1, 2]`.”

Your implementation is correct for the standard 3Sum bounds. It sorts `nums`
in place, so it changes the input order. Its overall time complexity is O(n²).

## Solution evolution

### 1. Enumerate every triple

Check every `i < j < k`, keep triples summing to zero, and deduplicate their
values using a canonical representation such as a sorted triple in a set.
Distinct indexes alone do not ensure unique value triplets.

This takes O(n³) time and O(k) result/deduplication storage for k unique answers.

**What to say:** “Enumerating every triple is correct, but repeatedly searching
for a third element costs cubic time, and I still need to remove repeated answers.”

### 2. Your map-of-indexes idea

Store `value -> list of indexes`, then for each pair `i < j`, look for
`-(nums[i] + nums[j])` at an index greater than `j`. The `cindex > j` check
ensures three distinct indexes and considers each index triple in increasing order.

However, the commented implementation is not yet a complete optimization:

- It still adds repeated value triplets. For `[0, 0, 0, 0]`, different pairs
  can each produce `[0, 0, 0]`.
- Scanning a complement's index list for each pair can still take O(n³) time.
  With all zeros, there are O(n²) pairs, and each search scans past indexes
  `<= j` before finding a usable one or reaching the end.

The map takes O(n) extra storage, excluding answers. Its index lists are sorted
by construction, so binary search could improve this intermediate method, but
duplicate answers would still require handling.

**What to say:** “A map finds the complement's occurrences, but my linear scan
of those occurrences can still be expensive, and unique indexes do not imply
unique value triplets.”

### 3. Sort, fix an anchor, and use two pointers

Sorting provides both monotonic sums and adjacent duplicate values. For each
distinct anchor, the suffix search takes O(n) time without a map. This gives
O(n²) total search time, and duplicate handling can happen during traversal.

**What to say:** “Sorting lets me reduce each anchor's search to Two Sum with
two pointers, and skip repeated values directly instead of deduplicating results later.”

## Your implementation

The executable logic below is unchanged; formatting is polished.

```kotlin
class Solution {
    fun threeSum(nums: IntArray): List<List<Int>> {
        val res = mutableListOf<List<Int>>()
        nums.sort()

        val n = nums.size
        for (i in nums.indices) {
            if (i > 0 && nums[i] == nums[i - 1]) continue

            var left = i + 1
            var right = n - 1
            while (left < right) {
                val twoSum = nums[left] + nums[right]
                if (twoSum + nums[i] > 0) {
                    right--
                } else if (twoSum + nums[i] < 0) {
                    left++
                } else {
                    res.add(listOf(nums[i], nums[left], nums[right]))
                    left++
                    right--
                }

                while (left < right && left > i + 1 && nums[left] == nums[left - 1]) left++
                while (left < right && right < n - 1 && nums[right] == nums[right + 1]) right--
            }
        }

        return res
    }
}
```

## Three separate duplicate checks

### Anchor: do not repeat the same first value

```kotlin
if (i > 0 && nums[i] == nums[i - 1]) continue
```

`nums[i]` is the **first value of the current triplet**, not necessarily the
first element of the array. An earlier occurrence of the same anchor value
already searched a larger suffix, containing every pair available to this one.
Repeating that anchor cannot introduce a new value triplet.

This does not remove the next equal value from the earlier anchor's suffix.
For `[-1, -1, 2]`, the first `-1` can still pair with the second `-1` and `2`.

### Left pointer: do not repeat an already handled second value

```kotlin
while (left < right && left > i + 1 && nums[left] == nums[left - 1]) left++
```

The pointer moves right, so compare its new value with the value immediately
behind it. `left > i + 1` prevents skipping the initial suffix value merely
because it equals the anchor. Without that guard, an iteration that only moves
`right` could wrongly skip a necessary second occurrence of the anchor value.

### Right pointer: do not repeat an already handled third value

```kotlin
while (left < right && right < n - 1 && nums[right] == nums[right + 1]) right--
```

The pointer moves left, so compare its new value with the value immediately
behind it in that direction: `right + 1`. The guard `right < n - 1` ensures
that this neighboring index exists. In both loops, `left < right` preserves
two distinct suffix indexes and stops when there is no remaining pair.

Use `while`, rather than `if`, because there may be an entire run of equal values.
These checks skip redundant candidates; they do not delete duplicates from `nums`.

## Why the pointer moves and skips are safe

For a fixed anchor, a sum that is too small rules out the current left value
with every remaining partner: even the largest partner is insufficient. A sum
that is too large similarly rules out the current right value with every
remaining partner. Equal copies of those ruled-out values are also impossible,
so skipping them after unsuccessful comparisons is safe.

After a match, the complement is determined by the anchor and one endpoint
value. Keeping the same left value could only match the same right value,
and vice versa. That would repeat the same triplet, so both pointers advance
and repeated endpoint values can be skipped.

Your two skip loops run after every branch. An endpoint value already passed
over remains handled as the interval shrinks; the other pointer's movement
cannot make those discarded copies necessary again.

The search maintains `i < left < right` whenever it evaluates a pair. For each
distinct anchor, every unique valid pair is either already recorded or still
inside the remaining interval. Pointer elimination preserves that property,
and the interval strictly shrinks. Anchor skipping then prevents duplication
across outer iterations. Together, these establish completeness and uniqueness.

## Dry run focused on duplicates

Sorted input: `[-2, 0, 0, 2, 2]`. The triples sum to zero only as `[-2, 0, 2]`.
States below are before the comparison; skip actions are included in the next state.

| i | left | right | Total | Action / next state |
| --- | --- | --- | --- | --- |
| 0 | 1 | 4 | 0 | Add `[-2, 0, 2]`; move to left=2, right=3; skip repeated 0, making left=3; stop |
| 1 | 2 | 4 | 4 | right becomes 3; skip repeated 2, making right=2; stop |
| 2 | — | — | — | Skip anchor 0 because it equals the previous anchor |
| 3 | 4 | 4 | — | No distinct suffix pair; inner loop does not run |
| 4 | — | — | — | Skip anchor 2; outer loop ends; return `[[-2, 0, 2]]` |

## Complexity and review

Sorting takes O(n log n) time. Each anchor's main loop and duplicate-skipping
loops together take O(n): neither pointer ever moves backward. With O(n)
anchors, total time is O(n²), including sorting.

The pointer search uses O(1) working space excluding results and sorting.
The k returned triplets require O(k) storage. Sorting's auxiliary space depends
on the Kotlin platform and library implementation; in-place sorting does not
by itself prove O(1) total auxiliary space. Copying to preserve the input would
add O(n) space.

A Python translation of this exact pointer logic matched brute force on all
6,399 non-decreasing arrays of lengths 3–8 with values from -3 through 3, with
no duplicate results. Sorting makes these cover all input multisets in that
range. This checks the search logic; no Kotlin runner was executed. The proof
above explains why the method works beyond those examples.

Practice explaining why skipping an anchor does not forbid `[-1, -1, 2]`, why
three zeros are necessary for `[0, 0, 0]`, and why the skip loops do not make
each anchor's scan quadratic. For arbitrary `Int` inputs beyond the standard
problem bounds, widen the additions to `Long` to avoid overflow.
