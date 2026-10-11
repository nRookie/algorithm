# Algorithm concepts cheatsheet

Transferable rules, organized by concept rather than by exercise. Each entry
states when a rule applies and why it works. Problem links are references for
the derivation, code, and detailed proof; the rule should make sense without them.

For the process of deriving a solution, use
[the solving workflow](algorithm-solving-workflow.md).

For binary-search conventions, proof patterns, and wording corrections from
our practice, use [the binary search cheatsheet](binary-search-cheatsheet.md).

## Input access determines what must be retained

An algorithm that needs earlier input or both endpoints cannot directly reuse
that access on a one-pass stream. Clarify the finite-input boundary, replay
availability, and storage permissions. Consumed data must be retained when
future decisions still depend on it; chunk boundaries do not restore access.

Filter information during ingestion only when the contract makes it irrelevant.
Retaining k relevant items out of n uses O(k) storage, but remains O(n) in the
worst case when every item matters. Lossless compression does not guarantee
smaller arbitrary input, and a fixed-size hash can collide, so it cannot alone
provide an exact substitute for the original data.

Reference: [Stream palindrome interview](../leetcode/125_valid_palindrome/STREAM_INTERVIEW.md).

## Separate processing work, RAM, external storage, and I/O

Waiting for input affects elapsed time separately from the work performed on
each item. Reading n items and then scanning them once is O(n) processing,
even when network or disk delays dominate the observed duration.

When external storage is available, block buffering can bound RAM without
removing the stored data: k fixed-size items can occupy O(k) disk storage while
being processed with O(B) RAM for block capacity B. A constant number of full
scans needs O(1 + k/B) block transfers in the ideal block model. Keep files open
and process many items per read to reduce I/O overhead; device latency, seeks,
and throughput still affect runtime. No fixed disk-to-RAM speed ratio applies.

Reference: [Disk blocks and endpoint comparison](../leetcode/125_valid_palindrome/STREAM_INTERVIEW.md).

## Preprocess fixed input to serve repeated queries

When many queries share unchanged data, build an index once to avoid repeating
the same scan. Compare preparation cost, per-query cost, and shared storage;
preprocessing is not automatically worthwhile for one query or every workload.
For ordered occurrence queries, scanning positions in increasing order creates
sorted lists without a separate sort. Reuse the index but reset query-local state.

Reference: [Many-query subsequence checks](../leetcode/392_is_subsequence/EXPLANATION.md).

## Find the first strictly later position and preserve future choices

In a sorted list, binary search can find the first value greater than a threshold:
with bounds `[left, right)`, discard `mid` and earlier entries when its value is
`<= threshold`; otherwise move `right` to `mid` to retain that candidate.
Convergence at the list size means no valid value exists. Distinguish the returned
list index from its stored value.

For matching an ordered sequence into fixed text, choosing the earliest valid
occurrence preserves every continuation available after a later occurrence.
This justifies greedy matching. Require strictly increasing text positions:
reusing one position cannot match two query characters. This argument assumes
earlier endpoints offer all the later endpoint's future choices; it is not a
general rule that every greedy earliest choice is correct.

Reference: [Occurrence lists and greedy matching](../leetcode/392_is_subsequence/EXPLANATION.md).

## Access a logical sequence without materializing it

If an algorithm needs indexed access rather than a copied representation,
calculate each logical element from the original storage. Constant-time
mapping preserves the algorithm's lookup cost while avoiding linear copying
time and storage. Include mapping costs if access is not constant-time.

For a rectangular matrix with m rows and n > 0 columns, row-major index
`i = row * n + column` is inverted by `row = i / n`, `column = i % n`.
The division theorem uniquely expresses i as `q * n + s`, with `0 <= s < n`;
for `0 <= i < m * n`, both coordinates are valid. This proves a one-to-one
mapping. Require fixed row width and arithmetic that does not overflow.

Index correctness does not imply sorted values. Binary search additionally
requires a monotone virtual sequence: sorted rows and ordered boundaries
between rows suffice. Sorted rows alone do not: `[[1,5],[2,6]]` flattens to
`[1,5,2,6]`.

A reverse view of a sequence of length N maps logical index i to `N - 1 - i`.
When only reverse traversal is needed, a descending index avoids a reversed
copy. This removes copying and allocations, but an already-linear scan remains
O(N); any separately constructed output still counts toward space usage.

References: [Virtual indexing and its proof](../leetcode/74_search_a_2d_matrix/EXPLANATION.md),
[Reverse traversal without input copies](../leetcode/67_add_binary/EXPLANATION.md).

## Split a digit total into remainder and carry

For nonnegative column total s in positional base k >= 2, the division identity
`s = k * (s / k) + s % k` gives the output digit `s % k` and next carry `s / k`.
Process least significant digits first because their carry affects the next
column. For two numbers, valid digits and an incoming carry at most 1 imply
`s <= 2 * (k - 1) + 1`, so the outgoing carry is also at most 1.

Align numbers at their least significant digits; missing higher digits contribute
zero. Continue while either input has digits **or** carry remains. Append the
digits as discovered and reverse once. Fixed-width integer conversion cannot
handle arbitrary-length input; per-column arithmetic avoids that overflow when
the column total itself fits the chosen integer type.

Reference: [String addition and carry invariant](../leetcode/67_add_binary/EXPLANATION.md).

## Bitwise operations act on integer bits, not Boolean conditions

Kotlin uses named operations on `Int` (32 bits) and `Long` (64 bits), rather
than C++ bitwise symbols. AND keeps positions set in both operands, OR keeps
positions set in either, XOR keeps differing positions, and inversion flips
every bit, including the sign bit.

| Operation | C++ | Kotlin |
| --- | --- | --- |
| Bitwise AND | `a & b` | `a and b` |
| Bitwise OR | `a \| b` | `a or b` |
| Bitwise XOR | `a ^ b` | `a xor b` |
| Bitwise NOT | `~a` | `a.inv()` |
| Left shift | `a << k` | `a shl k` |
| Right shift preserving sign | `a >> k` on signed values (see caveat below) | `a shr k` |
| Right shift filling with zeros | `a >> k` on unsigned values | `a ushr k` |

C++ guarantees arithmetic right shift of negative signed values since C++20;
earlier versions made it implementation-defined. The table compares operations,
not all overflow and shift-count rules across languages.

For nonnegative x, `x and 1` equals `x % 2`, and `x shr 1` equals integer
`x / 2`: the last bit is the remainder, and removing it gives the quotient.
Example: `3 = 11₂`, so masking gives 1 and shifting gives 1. These replacements
do not improve asymptotic complexity. For negative values the equivalence can
fail: `-3 shr 1` is -2, but `-3 / 2` is -1. `shr` preserves the sign;
`ushr` inserts zeros. Left shift multiplies by powers of two only when the
mathematical result fits without overflow. `6.inv()` is -7, not a flip of only
the three displayed bits of `110`.

For bit index k counted from zero at the right, use `mask = 1 shl k`:

| Purpose | Kotlin |
| --- | --- |
| Check bit k | `(x and mask) != 0` |
| Set bit k | `x or mask` |
| Clear bit k | `x and mask.inv()` |
| Toggle bit k | `x xor mask` |

Use k in `0..31` for `Int`; use `1L shl k` with k in `0..63` for `Long`.
Kotlin masks shift counts to the type width, so shifting by the width does not
select a new bit. Parenthesize bitwise expressions before comparisons.
Boolean short-circuit operations remain `&&`, `||`, and `!` in both languages;
they are separate from integer bitwise operations.

Each hexadecimal digit represents four bits: `3 = 0011`, `5 = 0101`,
`F = 1111`. Eight hex digits can display a full 32-bit mask. Repeated patterns
are easier to inspect in hex: `0x55555555` selects alternating bits throughout
an `Int`, whereas `0x55` selects them only in the lowest byte. Leading zeros
in a literal are optional; the required higher-position ones are not.
Use a positive selection mask's `.inv()` for its full-width complement;
a positive literal such as `0xAAAAAAAA` exceeds `Int.MAX_VALUE` and is inferred
as `Long` when no narrower compatible type applies.

References: [Binary addition with arithmetic or bitwise operations](../leetcode/67_add_binary/EXPLANATION.md),
[Hexadecimal masks and signed shifts](../leetcode/190_reverse_bits/EXPLANATION.md).

## Respect fixed-width representation boundaries

When a task transforms a W-bit pattern, process all W positions, including
leading zeros and the sign bit. Stopping when the numeric value becomes zero
loses positions: reversing `110` gives `011`, but reversing an 8-bit pattern
`00000110` gives `01100000`. Signed values still contain valid bit patterns;
`current > 0` skips all negative inputs.

`shr` copies the sign bit; `ushr` inserts zeros. Repeated `shr` on a negative
value eventually reaches -1 and stays there, so a loop waiting for zero cannot
terminate. In a loop extracting the lowest bit **before** each shift exactly
W times, either shift reads the same original W bits: inserted bits would first
be read on extraction W + 1. This equivalence is specific to that access order;
group recombination can require `ushr` to keep vacated positions zero.

Reference: [Fixed-width reversal and shift qualification](../leetcode/190_reverse_bits/EXPLANATION.md).

## Reverse larger blocks by swapping already-reversed halves

For a fixed-width bit pattern whose width W is a power of two, swap neighboring
groups of sizes `1, 2, 4, ..., W / 2`. After swapping groups of size s, every
2s-bit block is reversed relative to the original. Initially single-bit groups
are trivially reversed; exchanging `reverse(A)` and `reverse(B)` produces
`reverse(B) + reverse(A) = reverse(A + B)`, establishing the next larger block.

Select the lower s bits of every 2s-bit block with a mask, select the upper
groups with its full-width complement, and shift the groups by s in opposite
directions. OR combines them because their destination fields are disjoint.
Masks must cover the full word at every stage; a short mask clears higher data.
Use unsigned right shift so negative masked values do not introduce extra ones.

There are log₂ W swap stages. This is a stage count with word-operation costs
accounted for separately, not a constant-cost claim for arbitrary-precision
integers. For native 32-bit words, both five swap stages and a 32-iteration
bit loop have O(1) time and space; actual speed requires measurement.

Reference: [Growing-group reversal proof and diagram](../leetcode/190_reverse_bits/EXPLANATION.md).

## Keep binary-search boundaries consistent with the search objective

For a sorted sequence of length N, a lower-bound search starts with
`left = 0`, `right = N`. Maintain values before left `< target` and values
at or after right `>= target`. Discard through mid with `left = mid + 1`
when its value is smaller; otherwise retain mid with `right = mid`.
The undecided elements occupy `[left, right)`, but the answer may be either
endpoint. Strict shrinking gives convergence to the first qualifying index,
or N if none exists. Check the result is below N before testing equality.

Initializing `right = N` also makes the classified suffix empty, so its
invariant holds without assuming that the last element qualifies. N represents
a no-match boundary, not an element index. Convert that boundary to a problem
answer only with a separate justification; modulo is not a general no-match fix.

For direct membership, search inclusive candidates `[left, right]`, starting
with `right = N - 1` and looping while `left <= right`. Return on equality;
otherwise discard mid with `left = mid + 1` or `right = mid - 1`. An empty
interval proves absence. Do not mix initialization, updates, or termination
from different conventions; a progress argument must accompany the invariant.

For nonempty inclusive candidates with `while left < right`, retaining mid
on the right (`right = mid`) requires a lower midpoint to ensure `mid < right`.
Retaining mid on the left (`left = mid`) requires an upper midpoint to ensure
`mid > left`. Pair the other update with `left = mid + 1` or `right = mid - 1`,
respectively. A lower midpoint with `left = mid` can stall on two candidates.

For a rightmost-true boundary search, a passing midpoint need not be the final
answer: retain it with `left = mid` and search farther right. A failing midpoint
and every later candidate can be discarded only when the predicate is true
then false. The remaining interval contains the boundary; it need not consist
entirely of passing candidates. With `left < right`, process the singleton
after convergence. Establish that a passing candidate exists, or separately
handle the case where none exists.

In a sorted array, first `>= target` and last `<= target` give the ends of
the target's equal-value block once existence is verified. An inclusive
first-qualifying search initialized with `right = N - 1` stops at the last
index if nothing qualifies; convergence alone does not prove a match.

References: [Lower-bound proof](../leetcode/35_search_insert_position/EXPLANATION.md),
[Membership variants](../leetcode/74_search_a_2d_matrix/EXPLANATION.md),
[First and last occurrences](../leetcode/34_find_first_and_last_position_of_element_in_sorted_array/EXPLANATION.md).

For English wording about positions and ranges, see
[the interview phrases cheatsheet](algorithm-interview-phrases.md#prepositions-for-positions-ranges-and-updates).

## Recover an order statistic from a partition of sorted sequences

For two nondecreasing sequences and rank `1 <= h <= m + n`, a left portion
containing the h smallest elements takes a prefix from each: counts i and j
satisfy `i + j = h`.
A cut is a count, not an element index: the last left index is `i - 1`,
and the first right index is i. For length m, cuts range from 0 through m.

Within each sequence, sortedness already orders its left and right portions.
It therefore suffices to check the two cross-sequence boundaries:
`lastLeftA <= firstRightB` and `lastLeftB <= firstRightA`.
When both hold, the largest left boundary is the h-th smallest element;
the smallest right boundary is the next one, when present. Equality is valid.
Neither combined portion needs to be physically sorted or materialized.

For a nonempty combined input, choosing `h = (m + n + 1) / 2` places an odd
median on the left. Return the largest left value for odd totals; average
the largest left and smallest right values for even totals. Represent absent
left boundaries by negative infinity and absent right boundaries by positive
infinity for comparisons; guard the array accesses themselves.

Increasing i decreases j, so `lastLeftA <= firstRightB` changes only from
true to false. Its rightmost passing cut also satisfies the other inequality:
if a next cut exists, its failure compares the current first-right A value
with the current last-left B value; at the end of A, its right side is empty.
For this middle-rank choice, searching the shorter sequence over all its cuts
keeps j within bounds. This gives O(1 + log(min(m, n) + 1)) time and O(1)
auxiliary space, including an empty shorter sequence.

Example: `[1,3 | 8]` and `[2 | 7,9]` give middle values 3 and 7, not 3 and 8.

## Halving must preserve the kind of answer requested

A first/last boundary search requires a monotone predicate: truth values
change at most once over the domain. The values themselves need not be
globally sorted if another classification is monotone. A rotated distinct
ascending array has a single boundary for `value >= firstValue`; duplicates
can invalidate that classification.

When classifying by an anchor, assign equality to exactly one side and check
the anchor itself. Distinct values still include the anchor's equality with
itself. On `[3,4,5,1,2]`, `value <= firstValue` produces
`true,false,false,true,true`, which cannot support a first-true search;
`value < firstValue` produces `false,false,false,true,true`. Non-rotated input
makes the latter predicate false everywhere, so the no-match boundary matters.

Searching for any valid answer can instead retain a half proved to contain
one. With unequal adjacent values and negative-infinity outside neighbors,
an interval whose endpoints exceed their outside neighbors contains a peak:
a maximum within the interval is strictly higher than both its neighbors.
A midpoint slope establishes a new endpoint condition while leaving the
other unchanged. This finds any peak, not necessarily the first, and does
not prove the discarded half has no peaks.

References: [Peak existence invariant](../leetcode/162_find_peak_element/EXPLANATION.md),
[Monotone rotation classification](../leetcode/33_search_in_rotated_sorted_array/EXPLANATION.md).

Related mistake note: [Anchor equality and the no-match boundary](<../leetcode/153_find_minimum_in_rotated_sorted_array/mistake I made.md>).

## Reuse exact matches through prefix–suffix overlaps

For contiguous exact string matching, after a mismatch, a candidate starting
inside the already matched region can survive only if its retained text suffix
equals a pattern prefix. Because the matched region equals a pattern prefix,
its proper borders (prefixes also equal to suffixes) identify these overlaps.
Try the longest border first; borders of that border give the shorter candidates.
This avoids rescanning text without skipping a possible occurrence.

Define whether the failure table stores a length or a last index. With a last
matched index `j` and `-1` for no match, the matched length is `j + 1`, the next
pattern character is at `j + 1`, and fallback is `j = failure[j]` while keeping
the mismatching text character fixed. For matched `sasas`, retained lengths
are `5 → 3 → 1 → 0`. An arbitrary substring is not a valid retained overlap.

**Cost:** KMP takes O(n + m) time and O(m) auxiliary space for text length n
and pattern length m. Fallbacks can retry one text character repeatedly;
linear time follows because total decreases of matched length are bounded by
total increases, each charged to an advancing scan step. Monotonic text scanning
alone is insufficient to establish this bound.

Reference: [String matching and failure tables](../leetcode/28_find_the_index_of_the_first_occurrence_in_a_string/EXPLANATION.md).

## Define aggregates by ranges, not by ambiguous index names

For n elements, boundaries 0 through n describe cuts between elements. A useful
convention is `prefix[k]` over `[0, k)` and `suffix[k]` over `[k, n)`.
State these ranges explicitly: an inclusive suffix and an exclusive suffix
require different formulas.

Use the operation's identity for an empty range: 0 for sums, 1 for products.
This makes boundary cases follow the same recurrence as other positions.
For products, the aggregate excluding index i is
`prefix[i] * suffix[i + 1]`, because those ranges omit exactly that element.
For `[1,2,3,4]`, excluding index 2 gives `2 * 4 = 8`.

**Limit:** Numeric overflow still matters. Removing an element by division
requires assumptions that fail at zero.

Widen operands before arithmetic when their combined result may overflow.
For example, convert both integer middle values to `Double` before adding
and averaging them; converting an already-overflowed sum cannot repair it.

Reference: [Product Except Self](../leetcode/238_product_of_array_except_self/EXPLANATION.md).

## Replace stored aggregates with running values when access is sequential

If an aggregate is consumed only once in scan order, it may need only a running
value. Keep it equal to the range required by the current answer; extend it
only after using it if the current element must be excluded.

Reuse an output slot only after its old value's final use. This is a dependency
argument: compression is safe because no future computation needs the erased
information. Arbitrary later queries may still require the full aggregate array.

**Cost:** This can reduce auxiliary space without changing time complexity.
O(1) auxiliary space excluding an n-element output still means O(n) total
additional storage including that output.

Reference: [Product Except Self](../leetcode/238_product_of_array_except_self/EXPLANATION.md).

## Endpoint totals and intermediate feasibility are different conditions

For additive changes, define `pre[k] = sum(change[0 until k])`. The change over
`[a, b)` is `pre[b] - pre[a]`. Starting with resource R at boundary a leaves
`R + pre[b] - pre[a]` at boundary b.

If the resource must stay at least L, check this inequality at every visited
boundary, not just the destination. For changes `[2,-3,4]`, the final change is
positive, but starting with 0 violates a lower bound of 0 after the second step.

For a fixed sequence, let m be the minimum prefix sum, including the empty
prefix 0. The minimum initial resource is `L - m`: it raises the lowest point
to L, and any smaller initial amount fails there. This assumes additive changes,
no capacity limit that discards gains, and the same lower bound initially and
after every step.

Reference: [Minimum Value to Get Positive Step by Step Sum](../leetcode/1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md).

## A minimum prefix can select a feasible rotation

For a nonempty circular sequence of additive changes with total T >= 0,
choose a smallest prefix boundary s among `0 until n`.

- Before wrapping, each partial change is `pre[k] - pre[s] >= 0`.
- After wrapping, it is `T + pre[k] - pre[s] >= 0`.

Both inequalities follow from the minimum-prefix choice. Thus the rotation
starting at s keeps every partial sum nonnegative. Negative total makes every
rotation impossible when starting empty.

**Condition:** Gains must accumulate without being discarded; a capacity limit
can invalidate this reasoning. A nonnegative total alone does not make an
arbitrary starting boundary feasible.

Reference: [Gas Station](../leetcode/134_gas_station/EXPLANATION.md).

## Use dominance to eliminate candidates in groups

Suppose attempt A first fails after step i. At an earlier boundary k it had
nonnegative resource. Attempt B starts empty at k and faces the same future
additive changes, so it has no more resource than A at every later boundary.
It therefore also fails by i. One failure can rule out an entire interval of
candidate starts, instead of retrying each one.

**General rule:** Candidate B can be discarded when another candidate starts
at least as favorably, faces equivalent future choices, and still cannot succeed.
The comparison must persist through future transitions; an apparent advantage
is insufficient if the candidates have different options or resource behavior.

**Pitfall:** Eliminating earlier candidates proves they fail; it does not alone
prove the surviving candidate completes the whole task. Prove the remaining
portion separately, including any wraparound.

Reference: [Gas Station](../leetcode/134_gas_station/EXPLANATION.md).

## Enforce a one-to-one correspondence in both directions

For two equal-length indexed sequences, a valid one-to-one replacement requires
each source value to keep the same target and each target to belong to only one
source. Maintain forward and reverse maps; for each pair, create a missing
mapping or verify that its stored value matches. The maps remain inverses on
all processed pairs. Check conflicts before overwriting; a map cannot retain
two different values for one key.

The reverse direction is essential: `[a,b] → [x,x]` passes forward consistency
but fails target uniqueness. Pairing values at the same index already checks
order, so these checks can run during map construction without a second pass.
For local mapping constraints, the first conflict is irreversible. Merging
two linear passes improves early failure and constants, not the O(n) bound.
Include key hashing/comparison costs when keys are strings.

References: [Character correspondence](../leetcode/205_isomorphic_strings/EXPLANATION.md),
[Character-to-word correspondence](../leetcode/290_word_pattern/EXPLANATION.md).

## Scan literal separators with an explicit empty-token policy

For a nonempty literal separator, skip consecutive matches, remember the word
start, then scan until the next match or end. Emit only nonempty spans if empty
tokens should be ignored. Advance by the separator length when consuming a
match, and by one character while scanning ordinary content. A complete string
separator is different from a set of separator characters or a regular expression.

Every transition advances the index, proving termination; an empty separator
breaks this progress argument and must be handled separately or rejected.
With naive matching, scanning N characters against a D-character separator
can cost O(ND), despite monotonic advancement. A single-character separator
gives O(N) scanning. Example: `"dog  cat"` split on `" "` has two words under
the ignore-empty policy; consuming only one space can produce an empty token.

Reference: [Literal string splitter and trace](../leetcode/290_word_pattern/EXPLANATION.md).

## Combine data structures through an explicit shared invariant

A dense array and a value-to-index map complement each other: the array gives
indexed access, and the map gives location by value. For unique values, maintain
`indices[values[i]] == i` after every operation.

When order and stable indices are unnecessary, deletion can move the last
element into the deleted slot, repair its map entry, then remove the old key and
last slot. This avoids shifting. Updating the moved entry before deleting the
requested key also handles deletion of the last element correctly.

**Cost:** Indexed access is O(1), dynamic-array append is amortized O(1), and
hash lookup/update is expected O(1), not a per-operation worst-case guarantee.

Uniformly sampling an array index samples values uniformly only if each value
occupies exactly one slot. Duplicates weight values by multiplicity. Equal
probabilities do not guarantee equal observed counts in a small sample.

Reference: [RandomizedSet](../leetcode/380_insert_delete_getrandom_o1/EXPLANATION.md).

## Choose traversal order according to the objective

In a finite graph, complete DFS and BFS both answer reachability when repeated
states are handled correctly. Their order may change the first path found.

BFS also guarantees a path with the fewest edges: FIFO processing finishes
distance d before distance d + 1. This minimizes total cost when every edge
has the same positive cost. DFS's first success has no such guarantee;
ordinary BFS does not guarantee minimum cost with unequal edge costs.

| Order | Deque operations | Meaning |
| --- | --- | --- |
| Stack | `addLast`, `removeLast` | Last in, first out |
| Queue | `addLast`, `removeFirst` | First in, first out |

Two queues can represent current and next BFS layers. Finish one layer before
advancing distance; order within a layer does not affect equal-cost distances.
Layer organization alone does not reduce neighbor-generation work.
Store distances to return a count and parents to reconstruct a path.

References: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md),
[BFS distance layers](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).

## A visited key must identify equivalent future situations

Explore a state once only when revisiting it offers no new relevant choices.
A physical position alone is not a sufficient key if remaining resources,
move budgets, or history change what can happen next.

For basic reachability, permanent visited marks prevent cycles and repeated
expansion. A repeated visit being skipped does not mean that state's answer
has been proved false: visited marks and cached subproblem answers have
different meanings. Path enumeration may require different marking rules.

Marking before enqueueing prevents duplicate pending entries. In equal-cost
BFS, first discovery also fixes the shortest distance and its parent.
Marking when removing can still work if duplicates are skipped before expansion,
but pending duplicates must be counted in time and space analysis.

Reference: [Jump Game III](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Count total work, not just states or loop nesting

Time is the sum of work performed over all processed states. Visiting n states
once can still take O(n²) if each generates O(n) transitions. Adjacency-list
traversal is O(V + E) because both vertices and edges are counted.

Nested loops can be linear when their combined inner iterations visit globally
disjoint new items. Prove that a boundary only advances or that each item is
charged a bounded number of times. A visited set may prevent enqueueing without
preventing repeated checks of overlapping neighbors.

For an unobstructed m-by-n grid with right/down moves, complete corner-to-corner
paths number `C(m + n - 2, m - 1)`. Scanning every complete path separately costs
O((m + n) times that count). A DFS sharing prefixes requires counting its calls
instead. A DP with mn states and constant work per state takes Θ(mn), regardless
of the number of paths. Square-grid path counts grow exponentially in side
length, not in total cell count.

Include pending entries, recursion depth, copies, and library operations in
the analysis; qualify amortized costs. Reducing stored data does not automatically
reduce computation.

References: [Counting range scans](../leetcode/45_jump_game_ii/dp/EXPLANATION.md),
[Path enumeration versus DP](../leetcode/174_dungeon_game/LEARNING_SUMMARY.md).

## Execution style, search order, and DP describe different things

Iteration and recursion describe how code executes. DFS can use recursive calls
or an explicit stack; both may require memory proportional to search depth.

Dynamic programming stores and reuses subproblem results. It can be recursive
or iterative. Replacing recursion with loops does not by itself create DP.
BFS organizes work by distance; DP organizes it around subproblem dependencies.
These views can overlap, but neither is implied merely by a request to minimize.

**Pitfalls:** Memoization alone does not resolve cyclic dependencies. Recursive
short-circuiting, such as `search(a) || search(b)`, allows early success but does
not prevent cycles or replace visited-state handling.

Reference: [BFS and DP comparison](../leetcode/45_jump_game_ii/two_queue_bfs/EXPLANATION.md).

## Compress state only when discarded distinctions cannot affect the answer

If a reachable set is guaranteed to be a continuous prefix, one endpoint can
represent it. Extend it only from a reachable source and never decrease it.
If exact moves leave holes, the farthest endpoint cannot describe which
intermediate positions are reachable.

The same structure can remove repeated scans: when discoveries are guaranteed
to form a prefix, examine only positions beyond the discovery boundary. Define
whether the boundary means discovered or processed; those are different states.

**Extra condition for optimization values:** Discovering a destination once
does not generally finalize its best value. Later sources must be unable to
improve it, for example because sources are processed in nondecreasing optimal
cost and all outgoing moves add the same cost. Prove that ordering property
before skipping updates.

Test any summary by asking: can two situations with the same summary have
different relevant futures? If yes, the compression loses necessary information.

References: [Reachable-prefix structure](../leetcode/55_jump_game/EXPLANATION.md),
[Finalizing new destinations](../leetcode/45_jump_game_ii/dp/EXPLANATION.md),
[Exact moves with holes](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Keep frequencies when individual identity and order are unnecessary

If only category counts affect the answer, use buckets instead of storing or
sorting individual items. Each item must enter exactly one category. For n
items and B buckets, counting and scanning cost O(n + B) time and O(B) space.
A huge category range can make direct indexing impractical.

Threshold queries can justify merging categories: if every query is `value >= h`
with h <= U, replacing values above U with U preserves those answers. It does
not preserve exact-value queries, sums, or distinctions among larger values.
For example, capping at 5 preserves `value >= 4`, but not `value == 100`.

Prefix counts answer “at most”; suffix counts answer “at least.” Add counts of
disjoint buckets to avoid double-counting. Scanning candidate thresholds from
largest to smallest makes the first passing candidate maximal, provided the
predicate is tested correctly and every larger candidate was considered.

Reference: [Capped buckets and threshold counts](../leetcode/274_h_index/EXPLANATION.md).

## Cancel unequal pairs when one value exceeds all others combined

A strict majority occurs m times among n items with `m > n - m`. Removing
two unequal values preserves that majority: removing one majority and one
other leaves the difference unchanged; removing two others increases it by 2.
The positive excess therefore cannot disappear, so the majority must survive.

Boyer–Moore compresses the uncanceled values into a candidate and a balance.
After every prefix, its items partition into unequal canceled pairs plus
`balance` copies of the candidate. A match adds a copy; a mismatch cancels
one; at zero balance the next item starts a new candidate. At the end, the
surviving candidate must be the guaranteed majority: O(n) time, O(1) space.

**Limits:** The balance is not the candidate's frequency. Zero balance describes
only the processed prefix. Without a strict-majority guarantee, count the final
candidate in a second pass and check `occurrences > n / 2`; a unique mode is
insufficient. For example, `[1,1,2,3]` has a unique mode but no majority.

Reference: [Majority Element](../leetcode/169_majority_element/EXPLANATION.md).

## Separate the identity of a DP subproblem from its stored answer

A state identifies a situation; its value stores that situation's answer
(a Boolean, count, minimum requirement, or best score). Include enough information
to distinguish histories with different relevant futures.

Adding a remaining-step dimension can turn cyclic position dependencies into
acyclic state dependencies: layer k reads only layer k - 1. This is a valid
formulation, not necessarily the most efficient one.

For finite, history-independent reachability, remove cycles from a successful
path to obtain a witness of at most V - 1 edges. This can bound a step-budget
dimension. The argument does not apply to counting walks, requiring exactly k
moves, or collecting resources through repeated visits. An “at most k” state
must allow immediate success using zero moves.

Reference: [Budget-layer DP](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Backward requirements can summarize an entire future

With additive resource changes, a fixed lower bound L, no capacity limit, and
acyclic dependencies, store the minimum resource required **before** the current
change to complete the remaining task. If any one successor is sufficient,
let q be the smallest successor requirement. For current change d:

```text
required = max(L, q - d)
```

Resource R must satisfy both `R >= L` and `R + d >= q`; the formula is the
smallest R satisfying both. Compute successors first. Reverse computation
does not reverse the task's legal movement.

Use L as the requirement after the final change when the same bound must still
hold. Invalid continuations must stay unavailable. The stored requirement is
not the actual resource remaining during a forward journey.

**Distinction:** `min` chooses a continuation; `max` enforces survival. Combining
them does not mean minimizing path length. Final totals alone cannot represent
intermediate resource shortages.

References: [Resource requirements on a path](../leetcode/1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md),
[Resource requirements with route choices](../leetcode/174_dungeon_game/EXPLANATION.md).

## Prove that later writes preserve earlier constraints

Suppose `x >= y + c` has been established, with fixed c. A sufficient condition
for preservation is that later writes only increase x and leave y unchanged:

```text
x' >= x >= y + c = y' + c
```

Check every write to both sides. A guard can prove an entry stays unchanged
when its condition contradicts the ordering assumed by the earlier constraint.
The contradiction must follow from the actual predicates, not from an absent
if statement. Preserving a relationship does not require freezing both values.

**Pitfall:** Increasing values with `max` alone is insufficient if the right
side can also increase: `2 >= 1 + 1` fails when the 1 becomes 2. The sufficient
condition above is one proof method, not a necessary condition for every algorithm.

**Transferable optimization:** Separate constraint families into dependency-ordered
passes when each pass establishes its constraints and preserves the others.
This can remove repeated correction or priority ordering. The gain still needs
a work count; it is not a universal rule for skipping DP iterations.
Constraint satisfaction and minimum total cost require separate arguments.

Reference: [Two directional scans: preservation proof](../leetcode/135_candy/EXPLANATION.md).

## Rolling arrays must preserve the meaning of a layer

If layer k reads only layer k - 1, two arrays suffice: keep the previous layer
unchanged until every new value is computed, then swap. In-place updates can
read new values and accidentally perform multiple transitions within one layer.

For a chain A → B → C, starting with only A reachable, an in-place scan might
mark B and then C in a layer intended to allow only one move. Using the old
layer reaches B but not C. The same immediate propagation might be appropriate
for eventual reachability, which is a different state definition.

**Cost:** Keeping two layers reduces space; it does not remove the work of
computing every layer. Rejustify correctness when changing update order.

Reference: [Layered reachability](../leetcode/1306_jump_game_iii/EXPLANATION.md).

## Process changed answers through their dependents

If a changed answer affects only known dependents, record those dependencies
and queue the affected work instead of repeatedly scanning every state.
For an edge `a → b`, record a in `predecessors[b]`: outgoing edges from b
generally cannot reveal who points to b.

For Boolean reachability, seed known-success states and propagate success to
their predecessors. Initially false means “not established yet”; after exhaustive
propagation, remaining false states cannot reach a seed. Each state changes
from false to true at most once, so processing its incoming edges costs O(V + E).

**Condition:** This bound depends on one-time changes and bounded dependency
processing. If values improve repeatedly, count every change and repeated edge
scan; using a queue alone does not guarantee linear time.

Reference: [Reverse dependency propagation](../leetcode/1306_jump_game_iii/dp_to_reverse_bfs/EXPLANATION.md).
