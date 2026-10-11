# Isomorphic Strings: checking a one-to-one mapping

## Contract

Two strings are isomorphic when their characters can be consistently replaced
to produce the other string, without two different source characters sharing
one target character. Compare characters at corresponding indexes; a character
may map to itself. The exercise guarantees equal lengths. A reusable helper can
check lengths explicitly.

Examples: `"egg" → "add"` is valid; `"aa" → "ab"` and `"ab" → "cc"` are not.

## Your reasoning, polished

“Store the corresponding characters in two maps, one for each direction. For
each pair, check whether either existing mapping conflicts with the new pair.
If so, the strings do not satisfy the one-to-one mapping requirement.”

This was your approach, and your implementation already validates in one pass.
The wording correction from the review: a map cannot store two values for one
key simultaneously. The check detects an attempt to assign a different value
to an existing key. Overwriting without checking would erase that evidence.

## Solution evolution

### 1. Your submitted solution: two maps, immediate validation

Your original code, with formatting normalized and explanatory comments omitted:

```kotlin
class Solution {
    fun isIsomorphic(s: String, t: String): Boolean {
        val map = HashMap<Char, Char>()
        val mapd = HashMap<Char, Char>()

        for (i in s.indices) {
            val c = s[i]
            val d = t[i]
            if (c in map) {
                if (map.getValue(c) != d) return false
            } else {
                map[c] = d
            }
            if (d in mapd) {
                if (mapd.getValue(d) != c) return false
            } else {
                mapd[d] = c
            }
        }
        return true
    }
}
```

The first map checks consistency: one source character always produces the
same target. The second checks uniqueness: one target character belongs to
only one source. Both conditions are required.

| Input | Forward check | Reverse check | Result |
| --- | --- | --- | --- |
| `s = "aa", t = "ab"` | `a → a` conflicts with `a → b` | Targets differ | False |
| `s = "ab", t = "cc"` | `a → c` and `b → c` individually fit | `c → a` conflicts with `c → b` | False |
| `s = "egg", t = "add"` | Repeated `g → d` is consistent | Repeated `d → g` is consistent | True |

There is no need to add a slower baseline: your submitted approach already
performs the necessary checks during a single traversal.

**What to say:** “I compare each pair at the same index. A forward map prevents
one source from changing its target, and a reverse map prevents two sources
from sharing a target. I reject a conflict as soon as I find it.”

### 2. Readability improvement: name the directions

Rename `map` to `sourceToTarget`, `mapd` to `targetToSource`, `c` to `source`,
and `d` to `target`. These names clarify the existing algorithm. The length
guard makes the function usable without the exercise's equal-length guarantee.

```kotlin
class Solution {
    fun isIsomorphic(s: String, t: String): Boolean {
        if (s.length != t.length) return false

        val sourceToTarget = HashMap<Char, Char>()
        val targetToSource = HashMap<Char, Char>()

        for (i in s.indices) {
            val source = s[i]
            val target = t[i]

            if (source in sourceToTarget) {
                if (sourceToTarget.getValue(source) != target) return false
            } else {
                sourceToTarget[source] = target
            }

            if (target in targetToSource) {
                if (targetToSource.getValue(target) != source) return false
            } else {
                targetToSource[target] = source
            }
        }

        return true
    }
}
```

The changes supplied during review improve naming and the input contract;
they do not improve asymptotic complexity.

## Trace: `s = "egg"`, `t = "add"`

Before index 0, both maps are empty.

| Index | Pair | Action | Forward map after step | Reverse map after step |
| --- | --- | --- | --- | --- |
| 0 | `e → a` | Both absent; insert | `{e: a}` | `{a: e}` |
| 1 | `g → d` | Both absent; insert | `{e: a, g: d}` | `{a: e, d: g}` |
| 2 | `g → d` | Both present and matching; keep | `{e: a, g: d}` | `{a: e, d: g}` |
| End | All pairs processed | Return true | Unchanged | Unchanged |

## Why it works and terminates

After every successful iteration, both maps agree with every processed pair
and are inverses on the characters seen so far. This holds initially for empty
maps. For a new pair, checking both directions rejects any inconsistency or
shared target. Otherwise, inserting a missing mapping or retaining a matching
one preserves the relationship.

A conflict proves no valid mapping can satisfy all pairs. If all pairs pass,
the forward map is a consistent, one-to-one replacement that produces `t`
from `s`. Indexed pairing already checks the original order.

The loop processes one next index per iteration and ends after `s.length`
pairs, unless a conflict returns earlier.

## Complexity and interview explanation

For length n and k distinct characters across both inputs, expected time is
O(n), assuming expected O(1) hash-map operations on `Char` keys. Extra space
is O(k), at most O(n); a fixed character alphabet also bounds k.

A valid input may require checking the last pair, so linear worst-case scanning
is necessary. Clearer names do not change this work or storage.

**What to say:** “The two maps enforce opposite directions of the same
one-to-one relationship. After each index, all earlier pairs agree with them.
A mismatch rejects immediately; completing the scan proves the mapping works.”

## Review later

- Explain why `"ab" → "cc"` needs the reverse check.
- Predict results for `"paper" → "title"`, empty strings, and unequal lengths.
- Explain why checking only whether a key exists is insufficient.
- Rebuild the loop from “create a missing mapping; otherwise verify it.”

See [Word Pattern](../290_word_pattern/EXPLANATION.md) for the same relationship
between characters and whole words. These Markdown notes were reviewed without
adding or running an executable solution or test harness.
