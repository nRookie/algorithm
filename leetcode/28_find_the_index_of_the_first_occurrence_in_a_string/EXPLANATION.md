# Find the Index of the First Occurrence in a String

Return the smallest index where `needle` occurs contiguously in `haystack`,
or `-1` if it does not occur. Let `n = haystack.length` and
`m = needle.length`. The saved implementation assumes `m > 0`.
In an interview, clarify whether an empty pattern is allowed and whether a
built-in search is acceptable. Kotlin strings use `.length`, not `.size`.

## Your reasoning, polished

This is a polished account of the reasoning you supplied, with corrections
identified below.

“My baseline is to try each possible starting position in the text and compare
the pattern from its beginning. If a comparison fails, I try the next start.
The repeated work is that overlapping attempts compare characters I have
already matched.

“Suppose I have matched `sas` and the next comparison fails. I cannot always
skip directly to the mismatching text character: the final `s` of the matched
part could be the beginning of another occurrence. But I already know that
this `s` matches the first character of the pattern, so I do not need to compare
it again.

“More generally, I want the longest suffix of the matched part that is also a
prefix of the pattern. That overlap is the longest partial match I can retain.
It lets me shift the candidate start forward while keeping the text pointer
at the same mismatching character.

“I precompute these overlaps in the pattern. My table stores the last index
of each overlap, with `-1` representing an empty overlap. During the search,
`i` is the next text index to compare and `j` is the last matched pattern index.
On a mismatch, I set `j = dp[j]` and retry the same text character against
`needle[j + 1]`. If `j` is already `-1`, no overlap remains, so I advance `i`.
Once `j` reaches `m - 1`, the whole pattern has matched, and its start is
`i - m` because `i` has already advanced past the match.”

## Terminology

| Term | Meaning | Example |
| --- | --- | --- |
| Text / pattern | `haystack` / `needle` | Search for pattern `sasasa` in the text |
| Substring | A contiguous sequence of characters | `asa` inside `sasasa` |
| Prefix | A substring beginning at the first character | `sas` is a prefix of `sasasa` |
| Suffix | A substring ending at the last character | `asa` is a suffix of `sasasa` |
| Proper prefix | A prefix shorter than the whole string | `sasas` is a proper prefix of `sasasa` |
| Border | A proper prefix that is also a suffix | `sas` is a border of `sasas` |
| Failure table / prefix table | Precomputed borders used after mismatches | Your `dp` array |
| Fallback | Retaining a shorter valid partial match | `j = dp[j]` |
| KMP | Knuth–Morris–Pratt string matching | Your final algorithm |

Your table is an index-based version of the usual **LPS** table (“longest
proper prefix which is also a suffix”). The common LPS convention stores a
length: `lps[k] = dp[k] + 1`. Never mix their update formulas.

The useful overlap is a **suffix** of what has matched and a **prefix** of the
pattern; an arbitrary earlier substring is insufficient. “Proper” prevents
falling back to the same full matched portion forever.

## Solution evolution

### 1. Built-in search

`haystack.indexOf(needle)` expresses the contract directly. Whether it satisfies
the interview exercise depends on whether library search is permitted.
Do not assume its implementation or complexity merely from the method name.

**What to say:** “There is a built-in search, but I can implement the matching
logic if that is what we want to assess.”

### 2. Compare at every possible start

Your commented baseline compares characters directly, without allocating
substrings. Its `j1` is the number of matched characters, unlike the final
KMP `j`, which is the last matched index.

```kotlin
val n = haystack.length
val m = needle.length
for (i in haystack.indices) {
    var j1 = 0
    for (j in i..minOf(i + m - 1, n - 1)) {
        if (haystack[j] == needle[j1]) {
            j1++
        } else {
            break
        }
    }
    if (j1 == m) return i
}
return -1
```

For a nonempty pattern this is correct: it returns only after all `m`
characters match, and it tries starts in increasing order. Truncated attempts
near the end cannot produce false matches. A small improvement is to try
only starts `0..n - m`, returning `-1` immediately when `m > n`; it avoids
impossible attempts but leaves worst-case repeated comparisons.

With `1 <= m <= n`, that restricted baseline costs
O((n - m + 1)m) time and O(1) auxiliary space, commonly bounded by O(nm).
For example, a text of repeated `a` characters and pattern `aaaaab` makes
many attempts fail only at their last comparison.

**What to say:** “I try starts from left to right and compare the whole pattern.
This guarantees the first occurrence, but overlapping starts repeat comparisons.”

### 3. Reuse matched overlaps with KMP

We currently discard every partial match after a mismatch. A border lets us
retain the suffix that already matches a pattern prefix.

For `haystack = "sasbsasbsasasa"` and `needle = "sasasa"`, the first attempt
matches `sas` and fails at text index 3. Its longest border is `s`.
Keep that one-character match, shift the implied start from 0 to 2, and
compare text index 3 again. No text pointer reversal is needed.

The table is:

```text
index:   0  1  2  3  4  5
needle:  s  a  s  a  s  a
dp:     -1 -1  0  1  2  3
lps:     0  0  1  2  3  4
```

Both preprocessing and search use the same operation: try to extend a matched
prefix; if extension fails, fall back to its longest border and try again.
The saved [28.kt](28.kt) preserves your executable logic and polishes comments.

**What to say:** “I preprocess the pattern's prefix–suffix overlaps. After a
mismatch, those overlaps tell me which already matched characters I can keep.
I shorten the pattern match and retry the same text character, so the text
pointer never moves backward.”

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Direct comparisons | O(nm) upper bound | O(1) |
| KMP preprocessing and search | O(n + m) | O(m) |

## Variable meanings and invariants

### Building `dp`

At each loop entry, `dp[0 until i]` is complete. `j + 1` is the length of the
current candidate border of `needle[0 until i]`. Initially the processed
prefix has one character and only the empty proper border, so `i = 1`, `j = -1`.

- Match: `needle[i] == needle[j + 1]` extends that border by one character.
  Store its last index with `dp[i] = j + 1`, then advance both pointers.
- Mismatch with `j >= 0`: `j = dp[j]` tries the longest border of the current
  candidate. Keep `i` fixed because its character has not been handled yet.
- Mismatch with `j == -1`: even the empty border cannot extend. Leave
  `dp[i] = -1` and advance `i`.

Why do we follow `dp[j]`? Any shorter valid border of the processed prefix
must also be a border of its current longest border: their ends align within
the same suffix, and their beginnings align within the same prefix. Repeating
these links enumerates the remaining candidates in decreasing length.

### Searching the text

At loop entry, the last `j + 1` consumed text characters equal
`needle[0..j]`. In half-open range notation:

```text
haystack[i - (j + 1) until i] == needle[0 until j + 1]
```

For `j = -1`, both ranges are empty. The implied candidate start is
`i - (j + 1)`. It does not need a separate variable.

On a match, advancing `i` and `j` extends the equality. On a fallback, the
retained border is still a suffix of the consumed text, so the equality remains
true for the shorter match. On a mismatch with no matched prefix, advancing
`i` retains the empty equality.

## Execution traces

Each row shows state **before** one comparison and the state after it.

Building the table for `sasasa`:

| Before `(i, j)` | Comparison | Action | After `(i, j)` |
| --- | --- | --- | --- |
| `(1, -1)` | `a != s` | Leave `dp[1] = -1`; advance | `(2, -1)` |
| `(2, -1)` | `s == s` | Set `dp[2] = 0` | `(3, 0)` |
| `(3, 0)` | `a == a` | Set `dp[3] = 1` | `(4, 1)` |
| `(4, 1)` | `s == s` | Set `dp[4] = 2` | `(5, 2)` |
| `(5, 2)` | `a == a` | Set `dp[5] = 3` | `(6, 3)`; stop |

Search for `sasasa` in `sasbsasbsasasa`:

```text
index:     0 1 2 3 4 5 6 7 8 9 10 11 12 13
haystack:  s a s b s a s b s a  s  a  s  a
```

| Before `(i, j)` | Comparison | Action | After `(i, j)` |
| --- | --- | --- | --- |
| `(0, -1)` | `s == s` | Extend | `(1, 0)` |
| `(1, 0)` | `a == a` | Extend | `(2, 1)` |
| `(2, 1)` | `s == s` | Extend | `(3, 2)` |
| `(3, 2)` | `b != a` | `j = dp[2] = 0`; keep `s` | `(3, 0)` |
| `(3, 0)` | `b != a` | `j = dp[0] = -1` | `(3, -1)` |
| `(3, -1)` | `b != s` | Advance text | `(4, -1)` |
| `(4, -1)` | `s == s` | Extend | `(5, 0)` |
| `(5, 0)` | `a == a` | Extend | `(6, 1)` |
| `(6, 1)` | `s == s` | Extend | `(7, 2)` |
| `(7, 2)` | `b != a` | `j = dp[2] = 0` | `(7, 0)` |
| `(7, 0)` | `b != a` | `j = dp[0] = -1` | `(7, -1)` |
| `(7, -1)` | `b != s` | Advance text | `(8, -1)` |
| `(8, -1)` | `s == s` | Extend | `(9, 0)` |
| `(9, 0)` | `a == a` | Extend | `(10, 1)` |
| `(10, 1)` | `s == s` | Extend | `(11, 2)` |
| `(11, 2)` | `a == a` | Extend | `(12, 3)` |
| `(12, 3)` | `s == s` | Extend | `(13, 4)` |
| `(13, 4)` | `a == a` | Full match | `(14, 5)`; return `14 - 6 = 8` |

A fallback can itself fail. Building `dp` for `sssssa`, the final `a` is
compared while `j` follows `3 → 2 → 1 → 0 → -1`. None extends with `a`,
so `dp[5] = -1`, giving `[-1, 0, 1, 2, 3, -1]` as you predicted.

## Corrections to the original wording and traces

- We retry from the next **candidate start**, not from the beginning of the
  entire text on every failure.
- For `ssbbutsad` versus `sad`, the first failure is at text index 1
  (`s != a`), not index 2. That example does not first match `sa`.
- With your final convention, after matching `sas`, `j = 2`, not 3.
  The matched **length** is 3. After retaining `s`, `j = 0`, not 1.
- After matching `sasas`, fallback is `j: 4 → 2 → 0 → -1`, retaining
  lengths `5 → 3 → 1 → 0`. The table determines these steps; there is
  no fixed amount to subtract.
- We retain the **ending** part of the matched text: its suffix. A retained
  prefix at the old start would not establish a new match at a later start.
- `i` never moves backward. `j` deliberately moves backward on mismatches;
  preserving all pattern progress is not possible in general.
- Prefer Kotlin `!=` for numeric value comparison. Your original `j !== -1`
  is preserved in the code, but referential inequality is inappropriate for
  expressing this numeric condition and can produce a compiler warning.
- For a general API allowing an empty pattern, add
  `if (needle.isEmpty()) return 0` before the search. The original code can
  index an empty pattern, or return `-1` for two empty strings.

## Correctness, first occurrence, and termination

After a mismatch, any new start inside the already matched text must make a
suffix of that text equal a prefix of the pattern. Since the matched text
equals a pattern prefix, exactly the borders describe these viable overlaps.
The failure chain tries them longest first, which corresponds to trying
candidate starts earliest first, and skips only impossible overlaps.

If no retained prefix can extend, the current text character cannot complete
any of those attempts. With no matched prefix remaining, its failure against
`needle[0]` also rules it out as a new start, so advancing is safe.
No potentially earlier occurrence is discarded. Full matches all have length
`m`, so the first completed occurrence also has the smallest starting index.
At that point `i` is the exclusive end and `i - m` is the required start.

Every loop step either advances its scanning pointer or strictly decreases
`j`. The scanning pointer is bounded by the input length, and `j` is bounded
below by `-1`, so neither loop can run forever.

## Why the time is linear

Keeping `i` monotonic is helpful but does not alone prove linear time:
some characters are compared repeatedly during fallback.

In preprocessing, a successful step raises `j` by one, at most `m - 1` times.
Every fallback decreases it by at least one; it cannot decrease more than the
total increases because it starts at and cannot fall below `-1`. Steps with
`j == -1` advance `i`. Thus preprocessing takes O(m) time.

The same accounting applies to search: at most n successful advances raise
`j`, total fallback decreases are O(n), and no-prefix mismatches advance `i`.
Search takes O(n), for O(n + m) total time and O(m) auxiliary space for `dp`.

## Interview explanation and rehearsal

Verification: the saved Kotlin implementation compiled and passed 64,391
comparisons against Kotlin `indexOf`: all binary texts of lengths 0–8 paired
with all nonempty binary patterns of lengths 1–6, plus five targeted cases
including the examples above. The compiler warned about `j !== -1`.
These checks support the review; the invariant and fallback argument establish
correctness beyond the tested inputs. Empty patterns were excluded.

“The direct approach tries every start and may repeat O(m) comparisons at
each one. I can reuse those comparisons when the matched part has a suffix
equal to a pattern prefix. I precompute the longest such proper overlaps in a
failure table. During search, my text pointer identifies the next character,
and my pattern pointer identifies the last matched character. On failure,
I shorten the partial match using the table and retry the same text character.
On a full match, I return the exclusive text end minus the pattern length.
Preprocessing is O(m), searching is O(n), and the table uses O(m) space.”

Practice explaining why `dp` stores proper borders, why fallback keeps the text
pointer fixed, why `j = dp[j]` may need several repetitions, and why a monotonic
text pointer still needs an amortized argument for the time bound.
