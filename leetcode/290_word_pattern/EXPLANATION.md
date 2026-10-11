# Word Pattern: one-to-one mapping and literal string splitting

## Contract

Split `s` into words, then determine whether each `pattern[i]` consistently
corresponds to `words[i]`, with different pattern characters assigned different
words. The number of words must equal the pattern length. A valid example is
`pattern = "abba"`, `s = "dog cat cat dog"`.

For the custom splitter discussed here, the delimiter is a nonempty, complete
literal string. Skip empty tokens caused by leading, trailing, or repeated
delimiters. Thus `"--"` is one separator, not a set of individual characters
or a regular expression. Spaces are separators when the delimiter is `" "`.
This empty-token policy is part of our helper's contract, not a claim about
every built-in split function.

## Your reasoning and the correction we discussed

**Your reasoning, polished:** “This is like Isomorphic Strings, except I first
split the sentence into words. Store character-to-word and word-to-character
maps and check whether new pairs conflict with existing mappings.”

Your initial solution built maps first and checked them in a second pass.
You were concerned that merging the passes might lose the pattern's order.
The correction: order is checked by pairing `pattern[i]` with `words[i]` at
the same index. Moving that pair's checks into the first pass preserves exactly
the same positional constraint.

Checking only for key presence would be insufficient. An existing key must
also have the expected value; otherwise it is a conflict. A map stores one
value per key, so check before overwriting a conflicting mapping.

You implemented the single-pass checks and the repeated-space fix. The full
string-delimiter helper below was supplied during coaching at your request.

## Solution evolution

### 1. Your original solution: split, build maps, then validate

Original implementation, with formatting normalized and sketch comments omitted:

```kotlin
class Solution {
    fun split(s: String, delimiters: String): List<String> {
        var l = 0
        var r = s.length - 1
        val res = mutableListOf<String>()
        while (l <= r && s[l] == ' ') l++
        while (l <= r && s[r] == ' ') r--

        while (l <= r) {
            val sb = StringBuilder()
            while (l <= r && s[l] != ' ') {
                sb.append(s[l])
                l++
            }
            res.add(sb.toString())
            l++
        }
        return res
    }

    fun wordPattern(pattern: String, s: String): Boolean {
        val words = split(s, " ")
        val ptos = HashMap<Char, String>()
        val stop = HashMap<String, Char>()

        val n = pattern.length
        val m = words.size
        if (n != m) return false

        for (i in 0 until n) {
            if (pattern[i] !in ptos) {
                ptos[pattern[i]] = words[i]
            }
            if (words[i] !in stop) {
                stop[words[i]] = pattern[i]
            }
        }
        for (i in 0 until n) {
            val c = pattern[i]
            if (ptos[c] != words[i]) return false
            if (stop[words[i]] != c) return false
        }
        return true
    }
}
```

The mapping logic is correct. `ptos` retains the first word for each character;
`stop` retains the first character for each word. The second loop rejects
later pairs that disagree with either first assignment.

For sentence length N and pattern length P, the implementation takes expected
O(N + P) time with ordinary space splitting and hash-map operations, including
the total word content processed. Extra space is O(N + P), including the word
list and maps. Two linear mapping passes are still linear, not quadratic.

The original splitter has two limitations outside its single-space assumptions:
it ignores `delimiters`, and it consumes only one space between words.
For `"dog  cat"`, it adds an empty word:

```text
Indexes: 0 1 2 3 4 5 6 7
Text:    d o g ␠ ␠ c a t

Read "dog": l becomes 3.
Single l++: l becomes 4, still a space.
Inner word loop runs zero times: add "".
Single l++: l becomes 5.
Read "cat": add "cat".

Result: ["dog", "", "cat"]
```

**What to say:** “I first assign each character and word its first partner,
then check every indexed pair against those assignments. This is linear,
but the checks can happen when each pair first arrives.”

### 2. Your improvement: validate while building; skip all spaces

Your revised splitter replaces the single increment after a word with:

```kotlin
while (l <= r && s[l] == ' ') l++
```

With the initial trimming retained, each word-building iteration begins on a
non-space character. No empty word is added, including for empty or all-space
input: the outer condition fails before indexing or building a word.

Your revised mapping loop is:

```kotlin
for (i in 0 until n) {
    val c = pattern[i]
    val d = words[i]
    if (c !in ptos) {
        ptos[c] = d
    } else {
        if (ptos.getValue(c) != d) return false
    }
    if (d !in stop) {
        stop[d] = c
    } else {
        if (stop.getValue(d) != c) return false
    }
}
return true
```

This preserves your “create if absent, otherwise verify” structure. `d` is
the current word; `word` would make that role clearer. More descriptive map
names would be `charToWord` and `wordToChar`; the code below retains your names.

| Mapping approach | Expected mapping work, including word content | Difference |
| --- | --- | --- |
| Build, then validate | O(N + P) | Validation waits for the second pass |
| Validate while building | O(N + P) | One mapping pass; stops at the first conflict |

The improvement reduces passes and permits earlier failure; it does not change
the asymptotic bound. Splitting still happens before the mapping loop.

**What to say:** “For each indexed character–word pair, I check both directions
before accepting it. Since the checks use the same index, they already enforce
the pattern's order. I do not need a separate ordering pass.”

### 3. Requested extension: a complete string delimiter

Instead of checking one character against `' '`, check whether the complete
separator starts at the current index: `s.startsWith(delimiters, l)`.
Consuming a separator advances by `delimiters.length`; scanning a word advances
by one character. Reject an empty delimiter, which would otherwise allow the
separator-skipping loop to make no progress.

Here is the complete version combining your single-pass mapping loop with the
generalized splitter supplied during coaching:

```kotlin
class Solution {
    fun split(s: String, delimiters: String): List<String> {
        require(delimiters.isNotEmpty()) {
            "Delimiter must not be empty"
        }

        var l = 0
        val res = mutableListOf<String>()

        while (l < s.length) {
            // Skip consecutive separators.
            while (l < s.length && s.startsWith(delimiters, l)) {
                l += delimiters.length
            }

            val start = l

            // Read until the next separator.
            while (l < s.length && !s.startsWith(delimiters, l)) {
                l++
            }

            if (start < l) {
                res.add(s.substring(start, l))
            }
        }

        return res
    }

    fun wordPattern(pattern: String, s: String): Boolean {
        val words = split(s, " ")
        if (pattern.length != words.size) return false

        val ptos = HashMap<Char, String>()
        val stop = HashMap<String, Char>()

        for (i in pattern.indices) {
            val c = pattern[i]
            val word = words[i]

            if (c !in ptos) {
                ptos[c] = word
            } else {
                if (ptos.getValue(c) != word) return false
            }

            if (word !in stop) {
                stop[word] = c
            } else {
                if (stop.getValue(word) != c) return false
            }
        }

        return true
    }
}
```

The old right boundary `r` is unnecessary: skipping separators and adding
only nonempty spans handles both leading and trailing separators.
`substring(start, l)` includes start and excludes l.

Expected helper results, reasoned from the code:

| Text | Delimiter | Words |
| --- | --- | --- |
| `" dog  cat "` | `" "` | `["dog", "cat"]` |
| `"--dog----cat--"` | `"--"` | `["dog", "cat"]` |
| `"   "` | `" "` | `[]` |
| `""` | `" "` | `[]` |
| `"dog"` | `"--"` | `["dog"]` |
| `"a-b--c"` | `"--"` | `["a-b", "c"]` |

These examples show that an isolated `'-'` is ordinary word content when the
delimiter is `"--"`. Matches are consumed from left to right without overlap;
for `"---"` and `"--"`, the remaining `"-"` is a word.

## Splitter trace: `s = "dog  cat"`, delimiter `" "`

The string has indexes `0..7`: `d, o, g, space, space, c, a, t`.

| Outer iteration | l before skipping | l after skipping / start | l after scanning | Action / result |
| --- | --- | --- | --- | --- |
| 1 | 0 | 0 | 3 | Add `[0, 3)` = `"dog"`; `["dog"]` |
| 2 | 3 | 5 | 8 | Add `[5, 8)` = `"cat"`; `["dog", "cat"]` |
| End | 8 | — | — | Outer condition false; return list |

Every separator match advances l by a positive amount. Every scanned word
character advances l by one. If skipping reaches the end, `start == l`, so
the helper adds no empty token and exits on the next outer condition.

## Mapping traces: order is already checked

For `pattern = "abba"`, `words = ["dog", "cat", "cat", "dog"]`, both maps
start empty:

| Index | Pair | Action | ptos after step | stop after step |
| --- | --- | --- | --- | --- |
| 0 | `a → dog` | Insert both | `{a: dog}` | `{dog: a}` |
| 1 | `b → cat` | Insert both | `{a: dog, b: cat}` | `{dog: a, cat: b}` |
| 2 | `b → cat` | Both existing values match | Unchanged | Unchanged |
| 3 | `a → dog` | Both existing values match | Unchanged | Unchanged |
| End | All four pairs passed | Return true | Unchanged | Unchanged |

Now change the words to `["dog", "cat", "dog", "cat"]`. Steps 0 and 1 are
unchanged. At index 2:

```text
Current pair: b → dog
ptos['b'] = "cat", which does not equal "dog".
Return false immediately.
```

The reverse check would also fail because `stop["dog"] = 'a'`, not `'b'`.
The actual code returns at the forward conflict before reaching that check.
The same word collection in a different order is therefore rejected.

## Why the mapping works

After each successful iteration, every processed indexed pair agrees with
both maps, which are inverses on the characters and words seen so far.
Empty maps satisfy this initially. A new pair either agrees with an existing
assignment or creates a new one; both direction checks exclude inconsistent
assignments and shared words. Thus each successful iteration preserves the
one-to-one relationship.

A conflict proves that the current pair cannot coexist with an earlier pair.
If the counts match and every pair passes, the maps describe a valid pattern
for all words at their original indexes. Advancing i processes each pair once;
the loop terminates after the pattern length or on the first conflict.

## Complexity

Let N be sentence length, P pattern length, and D the nonempty delimiter length.

- Generalized splitter: O(ND) worst-case character-comparison work, because
  each `startsWith` may compare up to D characters. Monotonic l alone does not
  make variable-length delimiter matching linear. Output storage is O(N),
  with O(1) working state excluding the returned list and strings.
- `wordPattern` uses D = 1, so splitting takes O(N). The mapping phase takes
  expected O(N + P), accounting for hashing/comparing the words' content and
  expected hash-map behavior. Overall expected time remains O(N + P).
- Total extra space for the word list and both maps is O(N + P). Maps store
  references to words already produced by the splitter, not full new copies
  of each word on every lookup.

## Interview explanation and review later

“I split the sentence and check that word count matches pattern length. Then
I compare corresponding pairs in order, maintaining maps in both directions.
One prevents a character from changing words, and the other prevents different
characters from sharing a word. I reject the first conflict. For a space
delimiter, the total expected time is linear in the input size.”

- Explain why `"ab"` with `"dog dog"` needs the reverse map.
- Explain why indexed checks also verify order, without comparing sorted words.
- Trace leading, trailing, and repeated delimiters; explain why no empty token
  is added.
- Explain why the empty delimiter is rejected and why a matched separator
  advances by its whole length.
- Rebuild the two-map checks using [Isomorphic Strings](../205_isomorphic_strings/EXPLANATION.md)
  as the character-to-character version of the same concept.

These notes record the conversation and code reasoning. No executable solution
or test harness was added or run as part of saving the Markdown files.
