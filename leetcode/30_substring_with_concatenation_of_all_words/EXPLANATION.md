# 30. Substring with Concatenation of All Words

## Contract and review

[Official problem](https://leetcode.com/problems/substring-with-concatenation-of-all-words/):
find every starting index whose substring consists of all entries in `words`,
in any order, with exactly their required multiplicities. All words have the
same positive length; `words` is nonempty. Answers may be returned in any order.

**Your revised implementation is correct.** Your original implementation has
two independent bugs:

1. It scans only word boundaries aligned with index 0, missing other starts.
2. It checks `right < n` before reading an entire word, which can read beyond
   the end of the string.

Your original shrink-before-add approach is not inherently wrong. It correctly
removes words until there is room for the incoming word, then retries that word
on the next inner iteration. The revised add-then-shrink structure makes the
state transitions simpler, but it is not the essential correctness fix.

## Your original reasoning, polished and corrected

“Since every word has the same length, I can scan in whole-word steps. Since
the word order does not matter, I compare word frequencies rather than word
positions. A set is insufficient because the same word may be required more
than once; I need a frequency map.

I maintain a window `[left, right)` containing complete words, with another
map for its frequencies and a counter for its total number of words.

An unknown word breaks any candidate crossing it, so I reset the window past
it. A required word that appears too often makes the window invalid, so I
remove words from the left until its count is allowed again.

Once every frequency is within its allowed limit, having the required total
number of words proves that all required counts match exactly.”

Add this missing part to that reasoning:

“Stepping by word length preserves the index remainder. I must run a separate
scan for each offset from 0 through `step - 1`, and read a word only when
`right + step <= n`.”

### Corrections to the early set/count comments

- A set loses multiplicity: `words = ["foo", "foo", "bar"]` requires three
  occurrences but has only two distinct words.
- A map's `.size` counts keys, not occurrences. `currentWordCount` is the
  sum of frequencies, not the map size. Your map can also retain zero-count
  keys after shrinking.
- Having fewer than `wordCount` words does not make any addition safe. For
  `words = ["foo", "bar", "baz"]`, the window `["foo", "foo"]` already
  violates a count limit even though its total is only two.
- Equal total count proves a match only after enforcing each word's upper
  bound. `["foo", "foo"]` has the same total as `["foo", "bar"]`, but is
  not a match.

Your original code already addresses these frequency issues; they are
corrections to the earlier explanation, not extra bugs in that code.

## Why the original fails

### Bug 1: one alignment does not cover all starting indexes

Use `s = "xfoobarxx"`, `words = ["foo", "bar"]`.
Here `step = 3`, `n = 9`, and the expected answer is `[1]`.

The original code reads only:

```text
right = 0: s[0, 3) = "xfo" → reset
right = 3: s[3, 6) = "oba" → reset
right = 6: s[6, 9) = "rxx" → reset
return []
```

The first omission is that index 1 is never considered as a word boundary.
There is no bounds error in this example; it isolates the alignment bug.
The offset-1 scan reads `"foo"` at index 1 and `"bar"` at index 4 and finds
the answer.

```text
Offset 0 boundaries: 0, 3, 6, ...
Offset 1 boundaries: 1, 4, 7, ...
Offset 2 boundaries: 2, 5, 8, ...
```

Every possible starting index belongs to exactly one of these scans according
to `index % step`.

### Bug 2: an available character is not necessarily an available word

Use `s = "foox"`, `words = ["foo"]`. The expected answer is `[0]`.

The original code first reads `"foo"`, records index 0, and removes it,
leaving `left = right = 3` and `currentWordCount = 0`.
Then `right < n` is true because `3 < 4`, so it attempts:

```kotlin
s.substring(3, 6) // Invalid: the string ends at exclusive index 4.
```

The guard must be `right + step <= n`. Apply the full-word condition to the
scan itself, not just its inner expansion loop: leaving an outer
`while (right < n)` with no possible progress at a trailing fragment can
create an infinite loop.

## Variable definitions

| Variable | Exact meaning |
| --- | --- |
| `wordMap` | Required frequency of each distinct word |
| `wordCount` | Total required occurrences, including duplicates; equals `words.size` |
| `step` | Length of one word; the amount both boundaries advance |
| `n` | Character length of `s` |
| `start` | Alignment offset for this pass, from 0 through `step - 1` |
| `left` | Inclusive start of the current whole-word window |
| `right` | Exclusive end; next word begins here before expansion |
| `rightWord` | Newly read word; after `right += step`, its span is `[right - step, right)` |
| `leftWord` | Word removed from `[left, left + step)` |
| `currentWordMap` | Frequencies in the current window; zero-count entries may remain |
| `currentWordCount` | Total number of word occurrences in the window |
| `answer` | Starting character indexes of all matches found so far |

At the end of each iteration, the bookkeeping satisfies:

```text
right - left == currentWordCount * step
currentWordCount == sum of currentWordMap frequencies
left and right have the same remainder modulo step
```

After an addition but before shrinking, the new word may be overrepresented.
After shrinking, all frequencies are within their required limits. The
temporary overfull state is intentional.

## Solution evolution

### 1. Check each starting index independently

Let `N = s.length`, `M = words.size`, `L = step`, and `D` be the number of
distinct required words. At each possible starting index, inspect `M`
length-`L` chunks and compare their frequency counts with the required map.

This directly checks the definition and takes O(NML) expected time as a
simple upper bound when creating and hashing word strings costs O(L).
It repeatedly processes overlapping candidates. Working storage is
O(DL + D), excluding answers, if unknown words are rejected immediately.

**What to say:** “I can check each candidate independently, but neighboring
candidates on the same word alignment repeat most of the same work.”

### 2. Your original sliding window

Reuse frequencies as words enter and leave a window. Unknown words reset the
window; excessive frequencies require removing a prefix. This is a valid
optimization for one alignment, but your original implementation does not
cover the other alignments and does not guard complete-word reads.

**What to say:** “The reusable window works on one sequence of word boundaries.
I still need to cover every possible remainder and stop before incomplete words.”

### 3. Revised solution: all alignments, add then repair

For each offset, start with fresh state. Read a complete word and advance
`right`. Reset on an unknown word; otherwise add its frequency and shrink
until its count is allowed. When the total is `M`, record the start and remove
one left word so that the next iteration can search for overlapping matches.

Only `rightWord` needs an overflow check: before this addition, all counts
were within their limits, and no other word's count increased.

**What to say:** “I scan all word alignments, maintaining required-word counts.
After repairing any excess count, a full-sized window must match exactly.”

## Revised implementation

Your revised code, with spacing normalized:

```kotlin
class Solution {
    fun findSubstring(s: String, words: Array<String>): List<Int> {
        val wordMap = HashMap<String, Int>()
        var wordCount = 0
        for (word in words) {
            wordMap[word] = wordMap.getOrDefault(word, 0) + 1
            wordCount++
        }

        val step = words[0].length
        val answer = mutableListOf<Int>()
        val n = s.length

        for (start in 0 until step) {
            val currentWordMap = HashMap<String, Int>()
            var currentWordCount = 0
            var left = start
            var right = start

            while (right + step <= n) {
                val rightWord = s.substring(right, right + step)
                right += step

                if (!wordMap.contains(rightWord)) {
                    currentWordMap.clear()
                    currentWordCount = 0
                    left = right
                    continue
                }

                currentWordMap[rightWord] =
                    currentWordMap.getOrDefault(rightWord, 0) + 1
                currentWordCount++

                while (currentWordMap.getOrDefault(rightWord, 0) >
                    wordMap.getOrDefault(rightWord, 0)) {
                    val leftWord = s.substring(left, left + step)
                    currentWordMap[leftWord] = currentWordMap.getValue(leftWord) - 1
                    currentWordCount--
                    left += step
                }

                if (currentWordCount == wordCount) {
                    answer.add(left)
                    val leftWord = s.substring(left, left + step)
                    currentWordMap[leftWord] = currentWordMap.getValue(leftWord) - 1
                    currentWordCount--
                    left += step
                }
            }
        }
        return answer
    }
}
```

## Trace: excess words, overlapping answers, and reset

Use `s = "foofoobarfooxxx"`, `words = ["foo", "bar"]`.
Required counts are `{foo: 1, bar: 1}`; `wordCount = 2`, `step = 3`.
The offset-0 pass starts at `(left, right, currentWordCount) = (0, 0, 0)`.
The table shows state after each action; zero-count map entries are omitted.

| Action | `left` | `right` | Current frequencies | Count | Answers |
| --- | --- | --- | --- | --- | --- |
| Add foo at 0 | 0 | 3 | `{foo: 1}` | 1 | `[]` |
| Add foo at 3; temporarily excessive | 0 | 6 | `{foo: 2}` | 2 | `[]` |
| Remove foo at 0 to repair | 3 | 6 | `{foo: 1}` | 1 | `[]` |
| Add bar at 6 | 3 | 9 | `{foo: 1, bar: 1}` | 2 | `[]` |
| Record 3; remove foo at 3 | 6 | 9 | `{bar: 1}` | 1 | `[3]` |
| Add foo at 9 | 6 | 12 | `{bar: 1, foo: 1}` | 2 | `[3]` |
| Record 6; remove bar at 6 | 9 | 12 | `{foo: 1}` | 1 | `[3, 6]` |
| Read xxx at 12; reset | 15 | 15 | `{}` | 0 | `[3, 6]` |
| No complete word remains | 15 | 15 | `{}` | 0 | `[3, 6]` |

For completeness, the other offsets read these chunks. Every chunk is unknown,
so each causes a reset with `left = right` and count zero:

| Offset | Chunk start indexes | Chunks read | `right` after each read | End |
| --- | --- | --- | --- | --- |
| 1 | 1, 4, 7, 10 | oof, oob, arf, oox | 4, 7, 10, 13 | `13 + 3 > 15` |
| 2 | 2, 5, 8, 11 | ofo, oba, rfo, oxx | 5, 8, 11, 14 | `14 + 3 > 15` |

Return `[3, 6]`. The matches overlap; removing one word after recording keeps
the reusable suffix instead of discarding the entire match.

## Correctness and termination

Every possible answer belongs to one offset pass. Within a pass, the window
contains only required words after reset handling. An unknown word invalidates
every candidate crossing it, so moving the left boundary past it is safe.

When the new word exceeds its allowed frequency, any window retaining all
those occurrences is invalid. Removing from the left until the excess is gone
discards only impossible starts. Other counts only decrease.

After repair, every current count is at most its required count. Their total
cannot exceed `wordCount`. If the totals are equal, no required count can be
short: otherwise, some other count would have to exceed its limit. Thus the
window is exactly a required permutation.

All valid windows have the same character length `wordCount * step`. Once
a start has been recorded, extending from that same start cannot produce a
second valid-length window. Removing one word is safe and preserves possible
overlapping answers. A start belongs to only one offset and `left` never
moves backward, so answers are not duplicated.

Each outer scan iteration advances `right` by positive `step`. Each shrinking
iteration advances `left` by the same amount and eventually removes an excess
occurrence. All scans terminate at the last complete word.

## Complexity

Across all offsets, there are O(N) complete-word reads and O(N) left removals:
approximately N/L per offset, with L offsets. Include O(L) offset-loop overhead
when words are longer than the input. Building required frequencies processes
M words.

Under expected hash-table operations and resets proportional to discarded
entries, the standard bound is O((N + M)L + L) time, including O(L) substring
creation and hashing. It is often described as O(N) scanning when word length
and preprocessing are treated separately. Working space is O(DL + D), plus
O(R) for R answer indexes.

**Kotlin/JVM implementation detail:** `HashMap.clear()` can traverse its retained
bucket capacity. After a large map has grown, repeated small refills followed
by resets can therefore cost more than the entries being discarded. For the
literal code, a conservative expected bound allowing this cost is
O((N + M)L + ND + L). The linear pointer-movement argument still holds; this
caveat concerns resets. Replacing the current map with a fresh map on reset
(using a `var`) can avoid repeatedly clearing a previously large table, if
that implementation detail needs optimization.

## Original implementation for reference

Executable logic preserved; exploratory comments and commented debug prints
are omitted. This version contains the two bugs demonstrated above.

```kotlin
class Solution {
    fun findSubstring(s: String, words: Array<String>): List<Int> {
        val wordMap = HashMap<String, Int>()
        var wordCount = 0
        for (word in words) {
            wordMap[word] = wordMap.getOrDefault(word, 0) + 1
            wordCount++
        }
        val currentWordMap = HashMap<String, Int>()
        var currentWordCount = 0
        val answer = mutableListOf<Int>()
        var left = 0
        var right = 0
        val step = words[0].length
        val n = s.length
        while (right < n) {
            while (right < n && currentWordCount < wordCount) {
                val rightWord = s.substring(right, right + step)
                if (currentWordMap.getOrDefault(rightWord, 0) <
                    wordMap.getOrDefault(rightWord, 0)) {
                    currentWordMap[rightWord] =
                        currentWordMap.getOrDefault(rightWord, 0) + 1
                    right += step
                    currentWordCount++
                } else if (!wordMap.contains(rightWord)) {
                    currentWordMap.clear()
                    currentWordCount = 0
                    right += step
                    left = right
                } else {
                    while (left < right &&
                        currentWordMap.getOrDefault(rightWord, 0) >=
                        wordMap.getOrDefault(rightWord, 0)) {
                        val leftWord = s.substring(left, left + step)
                        currentWordMap[leftWord] =
                            currentWordMap.getOrDefault(leftWord, 0) - 1
                        currentWordCount--
                        left += step
                    }
                }
            }
            if (currentWordCount == wordCount) {
                answer.add(left)
            }
            if (left < right && currentWordCount >= wordCount) {
                val leftWord = s.substring(left, left + step)
                currentWordMap[leftWord] = currentWordMap.getOrDefault(leftWord, 0) - 1
                currentWordCount--
                left += step
            }
        }
        return answer
    }
}
```

## Later review

These traces and counterexamples were checked manually; no executable tests
were run while saving these notes.

- Explain why stepping by L requires L separate alignments.
- Explain why the bound checks a whole word, not just its first character.
- Prove that bounded frequencies plus equal totals imply an exact match.
- Explain why only the newly added word can exceed its allowed count.
- Explain how removing one word after a match preserves overlapping matches.

Next review: use `"xfoobarxx"` to explain coverage, then `"foox"` to explain
bounds. These separate the actual bugs from the choice of loop structure.
