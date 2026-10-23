# 49. Group Anagrams

## Contract and review

[Official problem](https://leetcode.com/problems/group-anagrams/): group strings
that contain the same letters with the same multiplicities. Group order does
not matter. Each input occurrence must appear in the result, including repeated
identical strings.

There are 1 to 10,000 strings, each containing 0 to 100 lowercase English
letters. Empty strings are valid. The input does not need to be modified.

**Your implementation is correct.** Sorting each string produces a canonical
key shared by exactly its anagrams. `getOrPut` creates one list per key and
appends each original string to its group.

## Your ideas and comment corrections

Your comments propose a hash map with string keys and lists as values, and
mention summing ASCII codes as a possible simple key. Your actual code uses
sorted strings, which correctly preserves letter multiplicities.

- **An ASCII sum is insufficient.** `"ad"` and `"bc"` both have sum 197,
  but are not anagrams. Even combining length and sum would not distinguish
  this pair. The key must preserve enough information to distinguish all
  different letter multisets.
- **The map does not create duplicate groups.** Equal sorted keys use the same
  list. If the input contains `"eat"` twice, both copies belong in the result;
  these are required input occurrences, not a grouping bug.
- **A hash collision is different from a bad key.** A `HashMap` checks key
  equality as well as hashes, so different sorted strings remain distinct even
  if their internal hash codes collide. Using the same ASCII-sum key for two
  different letter multisets has already lost the information needed to
  distinguish them.

## Your implementation

Algorithm and variable names preserved; comments below clarify the reviewed
behavior.

```kotlin
class Solution {
    fun groupAnagrams(strs: Array<String>): List<List<String>> {
        val hashMap = HashMap<String, MutableList<String>>()

        for (str in strs) {
            val key = str.toCharArray().sorted().joinToString("")
            hashMap.getOrPut(key) { mutableListOf() }.add(str)
        }

        // Each map value is one complete group.
        val res = mutableListOf<List<String>>()
        for (list in hashMap.values) {
            res.add(list)
        }
        return res
    }
}
```

The final loop is correct. It can also be written as
`return hashMap.values.toList()`. This is a readability change, not an
asymptotic improvement. Both versions create an outer list that references
the existing group lists; they do not copy the strings or inner lists.

## Solution evolution

Let `n` be the number of strings, `k` the maximum string length, and `S` the
total number of characters across all strings.

### 1. Compare each string against existing groups

Maintain groups and compare each new string with a representative of each
group. For lowercase letters, two 26-entry frequency arrays can determine
whether a pair is anagram-equivalent. Add to the first matching group, or
create a group if no representative matches.

This works because matching letter counts define the groups. However, with
many distinct groups, each new string may check nearly all previous groups.
Repeated pairwise checks take O(n²(k + 1)) worst-case time. The grouped result
stores O(n) references, with O(26) temporary comparison storage.

**What to say:** “I can compare against each group's representative, but I
would repeatedly search the existing groups. A canonical key would let me
look up the right group directly.”

### 2. Your solution: sorted strings as canonical keys

Sorting removes character order while retaining every character and its
multiplicity:

```text
eat, tea, ate → aet
tan, nat     → ant
bat          → abt
```

Two strings are anagrams if and only if their sorted forms are equal.
The map therefore replaces repeated group comparisons with expected constant
hash-table probing, plus the cost of constructing and hashing each key.

The total expected time is O(n + S log(k + 1)), bounded by
O(n(1 + k log(k + 1))). The common shorthand for nonempty strings is
O(nk log k), with linear key construction and hashing also included.
Using `k + 1` and the `n` term accounts for empty and one-character strings.
Total auxiliary storage, including the grouped result, is O(n + S).

**What to say:** “Anagrams become the same string after sorting. I use that
sorted string as a map key, and append the original string to its group.”

### 3. Further optimization: frequency keys for a fixed alphabet

This is a possible improvement, not the implementation you submitted.
Because there are only 26 possible letters, count each letter instead of
sorting. Encode all 26 counts into an unambiguous key, such as a string with
separators. Building the counts costs O(length), and encoding costs O(26)
under these constraints. Expected total time becomes O(n + S).

Do not concatenate counts without separators: count prefixes `[1, 11]` and
`[11, 1]` both produce `"111"`. Also, a plain Kotlin `IntArray` used directly
as a map key does not provide the structural equality needed to group
separately allocated equal-count arrays. Use an unambiguous string encoding
or a key type with content-based equality and hashing.

**What to say:** “Sorting gives a reliable key. Since the alphabet is fixed,
I can represent the same letter multiset with 26 counts and avoid sorting.”

| Approach | Time | Storage including result |
| --- | --- | --- |
| Compare against group representatives | O(n²(k + 1)) worst case | O(n + 26) |
| Sorted-string keys: your code | Expected O(n + S log(k + 1)) | O(n + S) |
| Fixed-alphabet frequency keys | Expected O(n + S) | O(n), with fixed-size keys under these constraints |

## Variables and Kotlin operations

| Name / operation | Meaning |
| --- | --- |
| `str` | Current original string; this is what gets stored in the result |
| `key` | Sorted representation of its letter multiset |
| `hashMap` | One canonical key mapped to all processed strings with that key |
| `getOrPut(key) { mutableListOf() }` | Return the existing group, or create and store an empty group |
| `.add(str)` | Append exactly this input occurrence |
| `res` | Outer list containing all completed groups |

`toCharArray()` copies the characters. `sorted()` produces a sorted character
list, and `joinToString("")` builds the key without separators. These allocate
temporary storage proportional to the current string length. The original
string and input array are unchanged.

## Execution trace

Input: `["eat", "tea", "tan", "ate", "nat", "bat"]`.
Initially, `hashMap` is empty.

| `str` | `key` | Branch | Group after append |
| --- | --- | --- | --- |
| `eat` | `aet` | Create list | `aet → [eat]` |
| `tea` | `aet` | Reuse list | `aet → [eat, tea]` |
| `tan` | `ant` | Create list | `ant → [tan]` |
| `ate` | `aet` | Reuse list | `aet → [eat, tea, ate]` |
| `nat` | `ant` | Reuse list | `ant → [tan, nat]` |
| `bat` | `abt` | Create list | `abt → [bat]` |
| End | — | Input exhausted | Three groups complete |

The result loop starts with `res = []`. For an illustrative map-value order:

```text
Add [eat, tea, ate] → [[eat, tea, ate]]
Add [tan, nat]      → [[eat, tea, ate], [tan, nat]]
Add [bat]          → [[eat, tea, ate], [tan, nat], [bat]]
Values exhausted  → return res
```

Hash-map group iteration order is unspecified, which is allowed. Within each
group, your append operations preserve input order.

## Correctness and termination

Invariant: after processing any prefix of the input, each processed occurrence
appears exactly once, in the list keyed by its sorted form. Each map list
contains exactly the processed occurrences with that key.

The empty map satisfies this initially. On each iteration, `getOrPut` selects
the unique list for the current key, and `.add(str)` appends the current
occurrence once, preserving the invariant.

Equal sorted forms imply equal character counts, and equal character counts
produce equal sorted forms. Thus every group contains only anagrams, and all
anagrams share one group. Once the input is exhausted, the map values give
exactly the required grouping. Copying those values into `res` preserves it.

The first loop processes `n` strings; each sort operates on a finite array.
The second loop processes at most `n` groups. Both loops terminate.

## Edge cases

Expected results from review; no executable tests were run.

| Input | One valid result | Purpose |
| --- | --- | --- |
| `[""]` | `[[""]]` | Empty string has empty sorted key |
| `["", ""]` | `[["", ""]]` | Preserve repeated empty strings |
| `["a"]` | `[["a"]]` | Single input |
| `["eat", "eat", "tea"]` | `[["eat", "eat", "tea"]]` | Preserve repeated occurrences |
| `["ad", "bc"]` | `[["ad"], ["bc"]]` | ASCII sums cannot distinguish these |
| `["ab", "aab"]` | `[["ab"], ["aab"]]` | Multiplicity matters |

## Interview explanation and later recall

“Anagrams have the same character counts, so sorting each string produces a
canonical key. I map that key to a list and append each original string using
`getOrPut`. Equal keys group exactly the anagrams, and every occurrence is
added once. For maximum word length k, the usual time bound is expected
O(nk log k), with O(n + S) storage including keys and grouped references.
With a fixed lowercase alphabet, a frequency key can avoid sorting.”

- Why does a sorted key preserve enough information, while a character sum does not?
- Why do repeated identical input strings remain in the output?
- What repeated work does the map remove from representative comparisons?
- Why does each loop terminate, and what is true after each input iteration?

Next review: explain the `"ad"` / `"bc"` counterexample, then reconstruct the
map invariant without reading the implementation.
