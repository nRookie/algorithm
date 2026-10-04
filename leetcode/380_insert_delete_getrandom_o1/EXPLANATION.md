# 380. Insert Delete GetRandom O(1)

Implement a set with insertion, removal, and uniformly random selection, all
in average O(1) time. Insertion returns false for an existing value; removal
returns false for a missing value. `getRandom()` is called only when nonempty.
Element order does not matter.

The task is to combine existing collections into a new abstraction, not to
implement a HashMap from scratch. The final idiomatic Kotlin implementation
is in [380.kt](380.kt).

## Solution evolution

### 1. HashSet: efficient membership, insertion, and removal

You first suggested a HashSet. These operations take average O(1), but a
HashSet does not provide O(1) access to an element by index. A correct baseline
could copy its elements into a list for each random selection, then pick a
uniform index. That takes O(n) time and temporary space per selection, so it
does not meet this problem's requirement.

**What to say:** “A HashSet handles membership and updates, but I also need
efficient indexed access to select a random element.”

### 2. ArrayList: efficient indexed selection

You suggested an array for indexed access. An ArrayList supplies that access
while managing growth and shrinkage. Each unique value occupies one slot, so
a uniform random index selects a uniform random value.

An ArrayList alone still needs O(n) scanning to detect duplicates or find a
value to remove. Order-preserving removal also shifts later elements. You
identified that deleting `20` from `[10, 20, 30, 40]` would shift elements left.

**What to say:** “Indexed storage solves random selection, but finding a
value and shifting elements are still linear work.”

### 3. Remove without preserving order; store each value's index

When prompted to use the fact that order is irrelevant, you chose `40` to
replace `20`. After replacing that slot, remove the last slot. Only a constant
number of list operations is needed.

You then proposed a HashMap to find the slot in average O(1), and identified
the required update: after moving `40`, its map entry must become `40 → 1`.
The same map detects duplicates, so a separate HashSet is unnecessary.

**What to say:** “I store values in a list and map each value to its index.
To remove a value, I fill its slot with the last value, update that value's
index, and pop the last slot.”

| Approach | Insert | Remove | Random selection | Stored space |
| --- | --- | --- | --- | --- |
| HashSet; copy for random selection | Average O(1) | Average O(1) | O(n) | O(n) |
| ArrayList alone; scan for values | O(n) | O(n) | O(1) | O(n) |
| ArrayList + index map; replace with last | Expected amortized O(1) | Average O(1) | O(1) | O(n) |

## What the variables mean

| Name | Meaning |
| --- | --- |
| `values` | Dense list containing each current set member exactly once |
| `indices` | Map from each current value to its position in `values` |
| `v` | Value requested for insertion or removal |
| `removedIndex` | Slot occupied by the value being removed |
| `last` | Last value, saved before overwriting any slot |

Between public method calls, `indices[values[i]] == i` for every valid index.
The map contains exactly the values in the list, with no duplicates or holes.
Temporary duplicate values during removal are fine; the invariant must be
restored before the method returns.

## Trace: removal and insertion

Start by inserting `10`, `20`, `30`, and `40` into the empty structure:

| Call | Result | `values` afterward | `indices` afterward |
| --- | --- | --- | --- |
| Initial state | — | `[]` | `{}` |
| `insert(10)` | true | `[10]` | `{10: 0}` |
| `insert(20)` | true | `[10,20]` | `{10: 0, 20: 1}` |
| `insert(30)` | true | `[10,20,30]` | `{10: 0, 20: 1, 30: 2}` |
| `insert(40)` | true | `[10,20,30,40]` | `{10: 0, 20: 1, 30: 2, 40: 3}` |

For `remove(20)`, first read `removedIndex = 1` and save `last = 40`.

| Statement | `values` afterward | `indices` afterward |
| --- | --- | --- |
| Before mutation | `[10,20,30,40]` | `{10: 0, 20: 1, 30: 2, 40: 3}` |
| `values[removedIndex] = last` | `[10,40,30,40]` | `{10: 0, 20: 1, 30: 2, 40: 3}` |
| `indices[last] = removedIndex` | `[10,40,30,40]` | `{10: 0, 20: 1, 30: 2, 40: 1}` |
| `indices.remove(v)` | `[10,40,30,40]` | `{10: 0, 30: 2, 40: 1}` |
| `values.removeAt(values.lastIndex)` | `[10,40,30]` | `{10: 0, 30: 2, 40: 1}` |

Return true. Next, `insert(50)` records `indices[50] = 3`, appends `50`, and
returns true. Calling `insert(40)` returns false without changing either
collection. Calling `remove(99)` likewise returns false without changes.

### Removing the last or only element

For `remove(50)` from `[10,40,30,50]`, `last` is `v` itself. The two assignments
write back the same value and index; deleting the map entry and last slot
finishes correctly. This also works for a singleton list, leaving both
collections empty. Keep `indices.remove(v)` after `indices[last] = removedIndex`:
reversing those statements would reintroduce the deleted key in this case.

## Why the probabilities are equal

Kotlin's collection `random()` selects a random index and retrieves its element.
For an ArrayList, this indexed access is O(1). For n current members, every
index from 0 through n - 1 has probability 1/n. Because each value occupies
exactly one index, each value also has probability 1/n.

For `[10,40,30]`, the three values each have probability 1/3. Moving `40` into
a different slot does not change that fact. Uniformity describes each call's
probabilities, not a promise of equal counts in a finite sample; repeats are
normal. Frequency tests alone cannot prove uniformity.

## Kotlin details and the indexing correction

- `Array` has fixed length, although its elements can be replaced. `ArrayList`
  can grow and shrink; it manages an internal array with spare capacity.
- Reading or replacing an ArrayList element by index and removing its last
  element take O(1). Removing a middle element while preserving order takes
  O(n). Appending is amortized O(1): occasional growth copies existing elements.
- Your first insertion appended and then saved `values.size`, which was one
  too large. You corrected it to `values.size - 1`. The final version instead
  records `values.size` **before** appending; both corrected orders work.
- `v in indices` tests map keys. `indices[v] ?: return false` combines lookup
  with an early return when the key is absent.
- Finding `v` in the map implies that the list is nonempty, so `values.last()`
  is safe while the invariant holds; `lastOrNull()` is unnecessary here.
- Early returns remove unnecessary `else` nesting. `getRandom()` uses an
  expression body because it returns a single expression.
- Kotlin uses camelCase for variables and functions (`removedIndex`,
  `getRandom`), PascalCase for classes (`RandomizedSet`), and UPPER_SNAKE_CASE
  for `const val` constants. `val` prevents reassignment of a reference; it
  does not prevent mutation of the referenced ArrayList or HashMap.

The saved code preserves your algorithm, with the idiomatic refinements we
discussed: camelCase, early returns, one lookup for removal, and an expression
body for random selection.

## Correctness and complexity

Initially both collections are empty, satisfying the invariant. A duplicate
insertion or missing removal changes nothing. A successful insertion adds a
previously absent value at the end and records precisely that index.

A successful removal finds the correct slot through the map. Moving the last
value preserves all other values; updating its map entry keeps its position
accurate. Deleting the requested key and last list slot removes exactly the
requested value and restores uniqueness and density. The same reasoning holds
when the removed slot is already last. Uniform selection follows from the
one-to-one correspondence between current values and uniformly chosen indices.
Each method performs a bounded sequence of collection operations with no
user-written traversal or recursion.

HashMap operations are average/expected O(1); ArrayList append is amortized
O(1). Combined, insertion is expected amortized O(1), removal is average O(1),
and random selection is O(1). This is not a worst-case constant-time guarantee
for every individual insertion. Storage is O(n) for n stored elements; backing
capacity may remain allocated after deletions, so retained allocation can
reflect the historical peak size.

## Interview rehearsal

“I combine an ArrayList with a value-to-index HashMap. The map detects
duplicates and locates values; the list supports uniform random indexing.
Order does not matter, so removal replaces the target with the last element,
updates its index, and removes the last slot. Each member occupies one slot,
so a uniform index gives a uniform member. Operations meet the average O(1)
requirement, with amortized list growth, using O(n) storage.”

Try reconstructing the methods from the invariant, then check:

1. Why is a separate HashSet unnecessary?
2. Why does deleting the map key before updating the moved value fail when
   removing the last element?
3. When is `values.size` the correct insertion index?
4. Why does changing element order preserve uniform random selection?
5. How does amortized list growth differ from every append being O(1)?

References: [Kotlin collection random implementation](https://github.com/JetBrains/kotlin/blob/master/libraries/stdlib/common/src/generated/_Collections.kt),
[LeetCode problem](https://leetcode.com/problems/insert-delete-getrandom-o1/).
