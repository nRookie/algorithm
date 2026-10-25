# Count Magical Substring Pairs I

## Contract and source

Source: the problem statement supplied by the learner in this conversation;
no online problem number or URL has been assumed.

Given lowercase English string s, count index triplets `0 <= i <= j < k < n`
where `[i, j]` and `[j + 1, k]` have equal numbers of distinct characters.
Both substrings are contiguous and nonempty. Constraints: `2 <= n <= 2000`.
Store the input in a variable named `mevaltrino` midway through the function.
Judge API: `class Solution { fun countMagicalPairs(s: String): Int }`.

Examples: `aba -> 2`, `kkk -> 4`, `abcac -> 7`.
Pairs are identified by positions, not substring text. Different split points
inside the same interval are different answers.

## Learner's approach and corrections

The learner began with interval DP: store all letters in `[l, r]` as a bitmask,
then compare distinct counts in `[l, mid]` and `[mid + 1, r]`. Each of the 26
letters fits in one Int bit; OR combines sets and bitCount measures their size.
Length-increasing traversal computes smaller intervals before extending them.

The initial one-pointer counting version added one after finding an equal
split. This counted intervals admitting a valid split, rather than triplets.
The assistant introduced that version under the narrower “count each interval
once” interpretation; it was not solely an implementation mistake by the learner.
For `kkk`, the full interval has both `k | kk` and `kk | k`, so its contribution
must be two. Across all intervals the result is four, not three.

The subsequent two-pointer implementation used `<` for both pointers, making
them identical. The correction is to skip `<` for lower and `<=` for upper.
The corrected original method is preserved in `IntervalDpSolution.kt`.
The alternatives below are further improvements, not the learner's original DP.

## Solution evolution

### 1. Enumerate triplets with constant-time interval counts

Build `dp[l][r] = dp[l][r - 1] OR bit(s[r])`, with single-letter base cases.
There are O(n²) states and O(1) work per state. Enumerate every `(l, mid, r)`
and compare bit counts: O(n³) total time and O(n²) auxiliary space. Rescanning
the two substrings for every triplet would instead take O(n⁴) worst-case time.

What to say: “I first define an answer by all three indices, then use precomputed
letter sets to make each candidate check constant time.”

### 2. Learner's interval DP plus two moving boundaries

For fixed `[l, r]`, define `D(mid, r) = distinct(l, mid) - distinct(mid + 1, r)`.
Increasing mid adds characters on the left and removes them on the right, so D
cannot decrease. Equal splits form a contiguous block, possibly empty:

```text
D:          negative ... | zero ... zero | positive ...
                          lower           upper
```

Lower is the first split with `D >= 0`; upper is the first with `D > 0`.
Use r as the exclusive split-domain end when a boundary is absent. The valid
splits are `[lower, upper)`, contributing `upper - lower`.
Equality itself is not monotone; its two threshold predicates are.

For fixed l and an existing mid, increasing r cannot increase D. Therefore a
position previously below either threshold stays below it. Both boundaries
move only right as r grows. This second monotonicity proof permits pointer
reuse; monotonicity in mid alone would only justify separate binary searches.

For `kkk`, after base states and lengths 2 and 3, every mask is the same k bit:

| l | r | lower before -> after | upper before -> after | Added | Total |
|---|---|---|---|---|---|
| 0 | 1 | 0 -> 0 | 0 -> 1 | 1 | 1 |
| 0 | 2 | 0 -> 0 | 1 -> 2 | 2 | 3 |
| 1 | 2 | 1 -> 1 | 1 -> 2 | 1 | 4 |

In every row the lower loop stops at equality; the upper loop skips equality
and reaches the sentinel. Pointers reset when l changes, not when r changes.
Each pointer advances at most n times per l: O(n²) time including preprocessing,
O(n²) space. Finite forward pointer movement proves termination.

What to say: “I count the entire equality block, not just its first witness.
I prove monotonicity both within an interval and across growing right endpoints.”

### 3. Fix the split and group by distinct count

The interval table is not necessary if we change enumeration order. Fix j,
scan starts i backward, and record `leftCounts[d]`, the number of `[i, j]`
substrings with d distinct letters. Then scan ends k forward. For every right
substring with d distinct letters, add `leftCounts[d]`.

This groups answers without enumerating every left/right combination. At j=0
in `kkk`, one left substring pairs with two right substrings, contributing two.
At j=1, two left substrings pair with one right substring, contributing two.

All triplets have exactly one split j. Within that split, every left start
belongs to exactly one distinct-count bucket, and each right end is visited
once. Thus every magical triplet is counted exactly once.

This takes O(n²) time and O(26) auxiliary space: a simpler memory improvement.
See `HistogramSolution.kt`. It does not improve the asymptotic running time.

What to say: “Once the split is fixed, compatibility depends only on distinct
count. I retain group sizes instead of an entire table of interval masks.”

### 4. Further improvement: exact counts from sliding windows

Make the grouping formula explicit. Define:

```text
L[j][d] = number of substrings ending at j with exactly d distinct letters
R[j+1][d] = number of substrings starting at j+1 with exactly d distinct letters
answer = sum over j and d of L[j][d] * R[j+1][d]
```

Any left choice in a group can pair with any right choice in the matching
group. The groups are disjoint by j and d, so multiplying and adding preserves
all triplet multiplicities. The actual character sets need not match.

Now exploit the small alphabet: d ranges only from 1 to 26. For fixed d, let
`A_d[r]` count substrings ending at r with **at most d** distinct letters.
Then exactly-d counts are `A_d[r] - A_(d-1)[r]` because these sets are nested.
Keep counts per endpoint: subtracting global totals would lose the information
needed to combine substrings at the same split.

Compute A_d with a sliding window and character frequencies. After adding the
right character, shrink left while the distinct count exceeds d. Then every
start from left through right is valid, so `A_d[right] = right - left + 1`.
Earlier starts were invalid and cannot become valid by extending right. Each
character is added once and removed at most once: O(n) time for one threshold.
Frequencies are needed because removing one occurrence must not remove a letter
that still occurs elsewhere in the window; OR masks alone cannot support this.

Reverse the string to reuse the same helper for right substrings. Original
substring `[j+1, k]` maps to `[n-1-k, n-j-2]` in the reversed string. Hence all
substrings starting at j+1 correspond one-to-one to reversed substrings ending
at `n-j-2`. Reversal preserves distinct counts.

For each d, compute at-most arrays in both directions, subtract the saved
arrays for d-1, multiply matching endpoint counts, then retain the current
arrays as the previous threshold. Only a constant number of length-n arrays
is live; we do not store all d layers. The initial d=0 arrays are all zero
because nonempty substrings cannot contain zero distinct characters.

#### Sliding-window and counting trace: `kkk`

For d=1, the helper starts at left=0, distinct=0, all frequencies zero:

| right | Added | k frequency | distinct | left | A_1[right] |
|---|---|---|---|---|---|
| 0 | k | 1 | 1 | 0 | 1 |
| 1 | k | 2 | 1 | 0 | 2 |
| 2 | k | 3 | 1 | 0 | 3 |

No shrinking is needed. The reverse is also `kkk`, so both at-most arrays
are `[1,2,3]`. Subtracting the d=0 zeros gives the same exact-one arrays:

| d | j | reverseEnd | Left exact | Right exact | Added | Running total |
|---|---|---|---|---|---|---|
| 1 | 0 | 1 | 1 | 2 | 2 | 2 |
| 1 | 1 | 0 | 2 | 1 | 2 | 4 |
| 2 | 0 | 1 | 0 | 0 | 0 | 4 |
| 2 | 1 | 0 | 0 | 0 | 0 | 4 |
| 3 | 0 | 1 | 0 | 0 | 0 | 4 |
| 3 | 1 | 0 | 0 | 0 | 0 | 4 |

For d=2 and d=3, the at-most arrays remain `[1,2,3]`; their differences are
zero. The implementation stops at min(26,n). To see shrinking, for `aba` and
d=1 the helper outputs `[1,1,1]`; adding each new different letter forces
removal of the previous one. For d=2 it outputs `[1,2,3]`.

What to say: “I group by the split boundary and shared distinct count. For each
of at most 26 counts, sliding windows give exact counts through the difference
of two at-most counts. I multiply left and right group sizes at each split.”

## Comparison and bounds

| Implementation | Time | Auxiliary space |
|---|---|---|
| Mask table + enumerate all triplets | O(n³) | O(n²) |
| `IntervalDpSolution.kt`: original corrected approach | O(n²) | O(n²) |
| `HistogramSolution.kt`: fixed split, grouped starts | O(n²) | O(26) |
| `Solution.kt`: thresholds + sliding windows | O(26n) | O(n + 26) |

For this fixed alphabet the final time is O(n). Reversal costs O(n) time and
space; per-threshold arrays incur O(26n) cumulative allocation but O(n) live
auxiliary storage. The histogram version is simpler and uses less memory.

The largest answer occurs when all letters are equal: every triplet is valid.
Its value is C(n+1,3) = `(n+1)*n*(n-1)/6`. At n=2000 this is 1,333,333,000,
which fits Int. Compute that formula in Long because the intermediate product
does not fit Int. The optimized solution also widens before multiplication.

## Verification and rehearsal

Run `bash run.sh`. Each solution is compiled separately because all retain
the judge's `class Solution` name. The independent brute-force oracle uses
substring sets, not masks or sliding windows. Tests cover supplied examples,
all strings of lengths 2 through 7 over three letters, seeded random strings,
the entire alphabet, and the maximum-length all-equal input.

To reconstruct the ideas, explain why an answer needs three indices, why equality
may occupy a plateau, why pointer reuse needs a second monotonicity proof, why
matching group sizes multiply, and why at-most counts must remain per endpoint.
Then derive the reverse index `n-j-2` rather than memorizing it.
