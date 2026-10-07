# Is Subsequence: many-query follow-up

## Contract

Determine whether all characters of `s` can be matched to distinct positions
in `t` in their original order. Characters may be skipped in `t`, but matches
must use strictly increasing indexes. An empty `s` is always a subsequence.

The follow-up keeps `t` fixed while many queries `s1, s2, ...` arrive. Its purpose
is to recognize that reusable preprocessing can replace repeated scans of the
same input. A billion queries motivates this trade-off; it does not require
storing a billion queries at once.

## Solution evolution

### 1. Your original implementation: scan t for each query

```kotlin
class Solution {
    fun isSubsequence(s: String, t: String): Boolean {
        var j = 0
        if (s.length == 0) return true
        for (c in t) {
            if (s[j] == c) {
                j++
                if (j == s.length) return true
            }
        }
        return false
    }
}
```

This is correct. `j` is the number of characters already matched in `s`, so
`s[j]` is the next needed character. After each processed prefix of `t`, those
first `j` characters have matched in order. A match advances `j`; an unrelated
character is skipped. The early return prevents accessing `s[s.length]`.

For n = `t.length`, one query takes O(n) worst-case time and O(1) extra space.
For q queries, worst-case total time is O(qn). The repeated work is scanning
the same fixed `t` again for every query.

**What to say:** “For one query I scan t once, advancing the query pointer
whenever the next required character appears.”

### 2. Index t once, then binary-search occurrence lists

**Your reasoning, polished:** “Use a map whose key is a character and whose
value is the list of positions where it occurs. Process each query from left
to right and choose increasing positions, always choosing the leftmost valid
one. This avoids scanning all of t for every query.”

The binary-search technique was supplied during coaching. The important
correction we established: “leftmost” means **strictly after the last match**,
not the first occurrence in the entire list. One position cannot serve twice.

```text
t = "abacb"
     01234

'a' -> [0, 2]
'b' -> [1, 4]
'c' -> [3]
```

Initialize `lastMatchedIndex = -1` for each query. For each character, find the
first stored position greater than that index. If none exists, return false.
Otherwise update `lastMatchedIndex` to that stored position.

| Query `abb`: state before step | Positions | Choice / next state |
| --- | --- | --- |
| Need `a`, last match = -1 | `[0, 2]` | Choose 0; last match = 0 |
| Need first `b`, last match = 0 | `[1, 4]` | Choose 1; last match = 1 |
| Need second `b`, last match = 1 | `[1, 4]` | Choose 4; last match = 4 |
| All characters matched | — | Return true |

For `abbb`, the third `b` needs a position greater than 4. None exists, so the
query fails. A too-small occurrence alone is not failure; search past it first.

## Kotlin implementation

Construct this checker **once** for a fixed `t`, then reuse it. This is a
many-query interface rather than the original judge's `Solution` signature.

```kotlin
class SubsequenceChecker(t: String) {
    private val positions = mutableMapOf<Char, MutableList<Int>>()

    init {
        for (i in t.indices) {
            positions.getOrPut(t[i]) { mutableListOf() }.add(i)
        }
    }

    fun isSubsequence(s: String): Boolean {
        var lastMatchedIndex = -1

        for (c in s) {
            val occurrences = positions[c] ?: return false
            var left = 0
            var right = occurrences.size

            // Search interval is [left, right).
            while (left < right) {
                val mid = left + (right - left) / 2
                if (occurrences[mid] <= lastMatchedIndex) {
                    left = mid + 1
                } else {
                    right = mid
                }
            }

            if (left == occurrences.size) return false
            lastMatchedIndex = occurrences[left]
        }
        return true
    }
}

val checker = SubsequenceChecker("abacb")
// checker.isSubsequence("abb")  -> true
// checker.isSubsequence("abbb") -> false
// checker.isSubsequence("ba")   -> true
```

Lists are automatically sorted because preprocessing visits indexes in increasing
order. Binary search finds a **list index**; the value at that index is the
**position in t**. For `[0, 2, 5, 8, 11]` and last match 5, the result is list
index 3, but `lastMatchedIndex` becomes 8, not 3.

The search maintains that entries before `left` are too small, and entries at
or after `right` are valid candidates. If the middle value is too small or equal,
discard it and everything left of it. Otherwise keep it as a candidate by moving
`right` to `mid`. The interval strictly shrinks. At convergence, `left` identifies
the first valid entry, or the list size if no entry is valid.

## Why choosing the earliest valid match works

After each character, our chosen position is the earliest possible endpoint
for a match of that query prefix. Initially -1 represents matching nothing.
If another valid matching uses a later endpoint, all future positions available
after that endpoint are also available after ours. Choosing the earliest next
occurrence cannot remove a possible completion. Thus failure to find the next
occurrence means no complete matching exists; successful completion supplies
strictly increasing positions for every query character.

## Complexity and interview explanation

For n characters in t and m characters in one query:

| Approach | Preparation | Query time | Stored index |
| --- | --- | --- | --- |
| Scan t for each query | None | O(n) worst case | O(1) |
| Occurrence lists | O(n) expected/amortized | O(1 + m log(n + 1)) | O(n) |

Map access uses expected constant-time lookup; dynamic-list appends are amortized.
Binary search costs O(log(f + 1)) for a character with f occurrences. Query
working space is O(1), excluding the shared O(n) index and input string.
For q queries, the upper bound is O(n + q + sum(m_i) log(n + 1)).
The indexed approach is useful for many short queries, but is not guaranteed
faster for every workload. Rebuilding the index per query loses its main benefit.

**What to say:** “Since t is fixed, I index each character's positions once.
For each query I binary-search the earliest occurrence strictly after the last
match. If none exists, I return false. This trades linear shared storage for
avoiding a full scan of t on every query.”

## Review later

Predict the results for empty `s`, empty `t`, a character missing from t, and
`s = "aa"`, `t = "a"`. Explain why the comparison must be `>` rather than `>=`,
why each query starts at -1, and why a list index differs from a position in t.
These notes record the derived approach; no new executable solution was added
or run as part of saving this Markdown file.
