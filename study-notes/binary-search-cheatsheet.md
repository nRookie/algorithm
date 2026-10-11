# Binary search cheatsheet

Lessons from Search Insert Position, Search a 2D Matrix, Find Peak Element,
Search in Rotated Sorted Array, and Find First and Last Position. This sheet
collects reusable rules and the explanation mistakes observed in our discussion.
Full implementations, traces, and detailed proofs stay in the problem notes.

For English sentence patterns, see
[Algorithm interview phrases](algorithm-interview-phrases.md).

## Define the objective before selecting a template

| Objective | Meaning | Important qualification |
| --- | --- | --- |
| Membership | Decide whether a target exists, or return its index | Can return immediately on equality |
| First qualifying position | Find the first value meeting a threshold | Equality may qualify; the result need not equal the target |
| Last qualifying position | Find the last value meeting a threshold | Keep the rightmost candidate, not the first one found |
| Any valid element | Return any peak, for example | Discarded regions may also contain valid answers |

Do not describe all binary searches as finding the first index. The objective
determines what must survive an update and what convergence proves.

## Two different reasons binary search works

### A monotone predicate identifies one boundary

A predicate is a true/false test. Boundary search requires its truth values
to change at most once across the search domain.

```text
Sorted array, first >= target:     false false | true true
Sorted array, last <= target:      true true   | false false
Rotated distinct array, >= nums[0]: true true  | false false
```

Prove this structure from the input assumptions; do not infer it merely from
using a binary-search loop. Distinct rotated values make comparison with the
first value classify two contiguous portions. Duplicates can break it:
`[2,2,0,1,2]` produces `true,true,false,false,true`.

### An existence invariant retains some valid answer

For an unsorted array with unequal adjacent values and imaginary outside
neighbors of negative infinity, peak search preserves:

```text
The left endpoint is higher than its outside-left neighbor.
The right endpoint is higher than its outside-right neighbor.
```

A maximum element within such an interval is a peak. A falling middle edge
establishes a new right boundary; a rising edge establishes a new left
boundary. The retained half therefore contains a peak, even if the discarded
half contains another.

The descent predicate is not monotone: `[1,3,2,4,5,1]` rises and falls
repeatedly. Your peak search returns index 4, not the first peak at index 1.
Adjacent inequality is essential for a strict peak; `[2,2]` has none.

Reference: [Peak-search proof](../leetcode/162_find_peak_element/EXPLANATION.md).

## Distinguish elements from possible answer positions

- `[l, r]` includes both endpoint elements. If `l == r`, one element remains.
- `[l, r)` excludes element r. If `l == r`, no elements remain in that range.
- A range of n elements has n + 1 insertion positions. A boundary answer
  can equal n, even though element index n is invalid.

In a half-open lower-bound search, undecided elements occupy `[l, r)`, but
possible answer positions occupy `[l, r]`. This explains why r may equal n
without ever reading `nums[n]` inside the loop.

Bounds alone do not determine termination: an inclusive search can stop at
one candidate with `l < r`, or search until empty with `l <= r`. Match the
initialization, updates, loop condition, invariant, and final check.

## Match midpoint rounding to the updates

For nonnegative indexes, use:

```kotlin
val lowerMid = l + (r - l) / 2
val upperMid = l + (r - l + 1) / 2
```

| Search template | Initialization | Loop | Updates | Midpoint |
| --- | --- | --- | --- | --- |
| Half-open first >= target | `l=0, r=n` | `l < r` | Smaller: `l=mid+1`; otherwise `r=mid` | Lower |
| Inclusive first >= target | `l=0, r=n-1` | `l < r` | Smaller: `l=mid+1`; otherwise `r=mid` | Lower |
| Inclusive last <= target | `l=0, r=n-1` | `l < r` | Qualifies: `l=mid`; otherwise `r=mid-1` | Upper |
| Direct membership | `l=0, r=n-1` | `l <= r` | Smaller: `l=mid+1`; larger: `r=mid-1`; equal: return | Lower works |

The two inclusive boundary templates require nonempty input. While `l < r`:

- Lower midpoint satisfies `l <= mid < r`, so `r = mid` makes progress.
- Upper midpoint satisfies `l < mid <= r`, so `l = mid` makes progress.

For two candidates, a lower midpoint equals l. Using `l = mid` then changes
nothing and can loop forever. Derive rounding from the updates rather than
memorizing the formulas independently.

## Convergence is not always success

| Template | If no element qualifies |
| --- | --- |
| Half-open first qualifying position | Returns n; guard the access |
| Inclusive first qualifying element | Stops at `n - 1`; verify the candidate |
| Inclusive last qualifying element | Stops at 0; verify the candidate or establish existence first |
| Direct membership | Candidate interval becomes empty; report absence |

For inclusive first-qualifying search, if every comparison fails, only l
moves; r stays at the last index. Since `mid + 1 <= r`, l cannot pass r.
They eventually meet there. This is pointer convergence, not proof of a match.

For first and last occurrences, verify equality after the first search.
Once existence is established, the last value `<= target` must equal the
target because equal values form a consecutive block in sorted order.

Reference: [First and last occurrences](../leetcode/34_find_first_and_last_position_of_element_in_sorted_array/EXPLANATION.md).

## Prove correctness in four steps

1. **Initialization:** State precisely what the pointers mean and why the
   invariant holds before the first iteration. Empty outside regions can
   make classification statements true initially.
2. **Preservation:** For each branch, use the input structure to justify
   the update. Prove every part of the invariant: a changed boundary needs
   a new argument; an unchanged boundary retains its earlier condition.
3. **Termination and safety:** Show the interval strictly shrinks without
   losing required candidates. Derive access bounds, such as `mid < r`
   implying `mid + 1 <= r`, rather than assuming a midpoint equals l.
4. **Result:** Explain what a singleton, shared boundary, or empty interval
   means for this objective. Add an equality or bounds check when necessary.

An update such as `r = mid` is an operation, not an invariant. An invariant
is a statement that remains true. Examples illustrate a proof; they do not
establish correctness for every input.

## Access a virtual sequence without copying it

For a rectangular matrix with m rows and n > 0 columns:

```text
i = row * n + column
row = i / n
column = i % n
```

The row accounts for complete groups of n elements, and the column is the
offset within a group. Division uniquely decomposes i into quotient and
remainder with `0 <= remainder < n`. For `0 <= i < m*n`, both coordinates
are valid, and the conversion covers every cell exactly once.

Prove ordering separately: rows must be sorted, and each next row must start
after the previous row's last value. Sorted rows alone do not make the virtual
sequence sorted. Fixed row width and non-overflowing arithmetic are required.

An alternative is to find the first row whose last value is at least the
target, then search that row. Earlier rows are too small; later rows start
above the selected row's last value and are too large. No qualifying row
means absence; an inclusive row search can instead select the last row and
let the final equality check reject the target.

Reference: [Matrix methods and mapping proof](../leetcode/74_search_a_2d_matrix/EXPLANATION.md).

## Specify the searched domain separately from its boundary

A terminal boundary may be a valid index outside the elements inspected by
the loop. In your rotated-array implementation, the first target search
inspects `[0, turn)`: `mid < r <= turn` guarantees it never compares the
element at turn inside the loop. That index is checked afterward.

This matters because `[0, turn]` may be unsorted. For `[4,5,6,7,0,1,2]`,
the prefix `[4,5,6,7]` is sorted, but including the boundary value 0 is not.

Also distinguish a true pivot from a fallback index. Your split search returns
the minimum index when a smaller-than-first portion exists, but the last
index otherwise. Both still divide the array into sorted search domains.

Reference: [Rotated-array domain and fallback proof](../leetcode/33_search_in_rotated_sorted_array/EXPLANATION.md).

## Count preparation and sequential searches

- Physical matrix flattening takes `O(m*n)` time and space, even if the
  subsequent search is logarithmic.
- Virtual mapping takes `O(1)` per lookup, so search takes `O(log(m*n))`
  time and `O(1)` space without allocating the flattened sequence.
- Row search followed by column search takes `O(log m + log n)`, equivalent
  to `O(log(m*n))` for positive dimensions. The costs add.
- Two or three sequential `O(log n)` searches remain `O(log n)` overall.
  This is not a claim that their constant factors are identical.

## Your observed explanation mistakes and corrected reasoning

These are patterns and specific corrections from the submitted explanations,
not claims that every mistake appeared in every problem.

| Wording or reasoning to improve | Correction | Takeaway |
| --- | --- | --- |
| “All elements on the left side are bigger” | Define whether the endpoint is included, and use the exact `<`, `<=`, `>`, or `>=` relation | State the range and comparison explicitly |
| “Greater than target” when equality qualifies | “Greater than or equal to target,” or “at least target” | Equality determines which portion contains the boundary |
| “Distinct values mean mid cannot equal nums[0]” | Index 0 still equals itself | Distinctness compares different indexes |
| “mid equals l, so mid + 1 exists” | While `l < r`, the lower midpoint satisfies `mid < r` | Prove safety with inequalities |
| “Find the first descending pair” for peak search | Find any peak by retaining an interval containing one | State the actual objective |
| “The array is ascending” for a rotated array | Each portion is ascending; the whole array may not be | Identify exactly where sorted order applies |
| “If mid is below nums[0], everything from l through mid is too” | The interval may cross the split; everything at or after mid is in the smaller portion | Use the monotone classification, not global ascending order |
| “turn is always the rotation point” | Your implementation returns the last index when no smaller portion exists | Explain fallback meanings |
| “The first target search covers sorted [0, turn]” | It inspects sorted `[0, turn)` and checks turn afterward | Separate element domains from boundary positions |
| Reversing the last-occurrence portions | Values `<= target` come before values `> target` | Draw the partition in array order |
| “The loop finished, so the target was found” | Convergence may identify a nonmatching candidate or a sentinel | Explain and perform the final check |

## Your recurring wording patterns and natural alternatives

| Original pattern | More precise English |
| --- | --- |
| “The element at the left side of l” | “The elements before l” or “the elements at or before l,” depending on inclusion |
| “The first row greater than target” | “The first row whose last element is at least the target” |
| “Greater or equal to” | “Greater than or equal to,” or “at least” |
| “O(n) times” | “O(n) time”; use “n iterations” for a count |
| “The condition not hold anymore” | “The condition no longer holds” |
| “There is target exist” | “The target exists in the array” |
| “Move l to mid” without justification | “Keep mid as a candidate by setting l to mid” |
| “Two dimensional notation to one notation” | “Map two-dimensional coordinates to a one-dimensional index” |

Use **in** for membership, **at** for a position, **before/after** for exclusive
positions, and **through** for an included endpoint:

> “The value at index mid is in the remaining interval. Everything through
> mid is too small, so I set l to mid + 1.”

For the complete preposition table, see
[Positions, ranges, and updates](algorithm-interview-phrases.md#prepositions-for-positions-ranges-and-updates).

## Problem references and one takeaway each

| Problem | Main transferable lesson |
| --- | --- |
| [35. Search Insert Position](../leetcode/35_search_insert_position/EXPLANATION.md) | An answer may be a boundary position with no element at it |
| [74. Search a 2D Matrix](../leetcode/74_search_a_2d_matrix/EXPLANATION.md) | Virtual indexed access can eliminate copying; mapping and ordering need separate proofs |
| [162. Find Peak Element](../leetcode/162_find_peak_element/EXPLANATION.md) | Halving can preserve existence without a monotone value predicate |
| [33. Search in Rotated Sorted Array](../leetcode/33_search_in_rotated_sorted_array/EXPLANATION.md) | A classification can be monotone even when values are not globally sorted |
| [34. Find First and Last Position](../leetcode/34_find_first_and_last_position_of_element_in_sorted_array/EXPLANATION.md) | First and last boundaries require different retained endpoints and midpoint rounding |

For rehearsal, explain one implementation from its objective, invariant,
updates, termination, and final check before tracing a concrete example.
