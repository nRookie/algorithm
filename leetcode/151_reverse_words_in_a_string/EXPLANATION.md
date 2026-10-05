# Reverse Words in a String

## Contract and clarifications

Reverse the order of words while preserving the characters inside each word.
Separate output words with one ASCII space and remove outer spaces.
For example, `"  ab   cd  "` becomes `"cd ab"`.

The [LeetCode statement](https://leetcode.com/problems/reverse-words-in-a-string/)
limits input to English letters, digits, and ASCII spaces, with length between
1 and 10,000 and at least one word. Before implementing in an interview, clarify
whether tabs count as separators and whether input is mutable. This solution
uses `' '` because that is the stated separator; Kotlin `String` is immutable.

The original topic link is [InterviewChamp](https://interviewchamp.ai/company-coding/microsoft/reverse-words-in-a-string).
Its contents were unavailable during retrieval, so these notes do not claim to
reproduce that page's implementation or company attribution.

## Solution evolution

### 1. Split, filter, reverse, join

A straightforward Kotlin baseline is:

```kotlin
s.split(' ').filter { it.isNotEmpty() }.reversed().joinToString(" ")
```

Splitting identifies words and empty tokens; filtering removes the empty tokens
created by repeated or outer spaces. Reversing the list changes word order;
joining creates exactly one separator between consecutive words.
For `"  ab   cd  "`, the retained words are `[ab, cd]`, then `[cd, ab]`.

With `n = s.length`, this takes O(n) time and O(n) additional space for tokens,
collections, and constructed text. The total token characters are at most n;
the number of tokens is also O(n).

**What to say:** “I can tokenize the input, remove empty tokens, reverse the
word list, and join with one space. That gives a simple linear-time baseline.”

### 2. Scan from the end and append word ranges

We currently store a word list only to traverse it backward. Reading the input
backward lets us discover words directly in the required output order.
For each word, find its boundaries backward, then append its characters forward.
This preserves spelling without allocating a substring for every word.

The saved [151.kt](151.kt) implements this approach. It uses O(n) time and O(n)
space for its output builder and returned string. This reduces intermediate
allocations; it does not change the asymptotic time or total space bounds.
The pointer bookkeeping uses O(1) space, but the implementation as a whole does
not, even if the returned string is excluded: the builder still stores the output.

**What to say:** “The last word should be emitted first, so I scan from the end.
I skip spaces, find a word's start, and append that original range. I insert a
space only when the output already contains a word.”

### 3. Mutable-buffer follow-up

If given a mutable character buffer and allowed to return its logical length:

1. Compact words forward, keeping one separator and removing outer spaces.
2. Reverse the entire active prefix.
3. Reverse each word within that prefix.

For the shared example, normalization gives `ab cd`; whole-prefix reversal gives
`dc ba`; reversing each word gives `cd ab`. Reversing everything changes both
word order and internal character order. The per-word reversal restores spelling
while keeping the new word order.

Compaction is safe when the write pointer never passes the read pointer: writes
cannot destroy unread characters. Reversals use two pointers and swaps. The
buffer algorithm takes O(n) time and O(1) extra space; unused trailing buffer
positions are outside the returned logical length. Converting an immutable
Kotlin `String` into a `CharArray` first allocates O(n), so that adaptation would
not make the original `String -> String` implementation constant-space.

| Approach | Time | Additional space | Main tradeoff |
|---|---|---|---|
| Split/filter/reverse/join | O(n) | O(n) | Simple; stores tokens and lists |
| Backward range scan, saved implementation | O(n) | O(n) | Avoids token list and per-word substrings |
| Reversal in an existing mutable buffer | O(n) | O(1) | Requires mutable storage and logical length |

Any correct algorithm must inspect the input in the worst case: an unexamined
character could change a word or a separator. Thus O(n) time meets the
worst-case lower bound. Constant-space buffer processing is a separate constraint.

## Variables and trace

- `right`: current position while scanning backward; `-1` means input exhausted.
- `endExclusive`: one position after the current word's last character.
- `start`: the current word's first character, found as `right + 1`.
- `result`: completed words in reversed order, with normalized separators.

Trace for `"  ab   cd  "` (spaces shown as `·`):

```text
index:  0 1 2 3 4 5 6 7 8 9 10
input:  · · a b · · · c d · ·
```

| Iteration | `right` at entry | After skipping spaces | `endExclusive` | After scanning word | Appended range | Result |
|---|---:|---:|---:|---:|---|---|
| Initial | 10 | — | — | — | — | `""` |
| 1 | 10 | 8 | 9 | 6 | `[7, 9)` = `cd` | `"cd"` |
| 2 | 6 | 3 | 4 | 1 | `[2, 4)` = `ab` | `"cd ab"` |
| 3 | 1 | -1 | — | — | Break before indexing | `"cd ab"` |

In iteration 2, `result` is nonempty, so one space is appended before `ab`.
The final skip consumes leading spaces and the `right < 0` branch terminates.
Without leading spaces, scanning the first word itself reaches `-1`, and the
outer loop ends immediately after that word is appended.

## Correctness and termination

At each outer-loop entry, the suffix after `right` has been consumed. Every word
in that suffix appears in `result` exactly once, in right-to-left word order;
characters within each word retain their original order, and separators are
single spaces with no outer spaces.

Initially the suffix and result are empty. Skipping separators changes no words.
Scanning non-space characters finds exactly the next unprocessed word; appending
`[start, endExclusive)` in forward order preserves its characters. Adding a
separator only before a non-first word maintains the spacing condition.
This establishes the invariant for the next iteration.

`right` only decreases. Each nonterminal iteration consumes at least one word,
and the index is bounded below by -1. On termination every input word is consumed,
so the invariant gives the required result. Boundary checks precede all indexing,
including when the first word touches index 0.

## Complexity and pitfalls

The nested loops do not cause quadratic work: all scans share one pointer that
never moves right, so each input character is consumed once. Appending all word
ranges and constructing the returned string also take O(n) total time.
The builder and final string require O(n) space.

- Reversing characters alone gives `dc ba` for `ab cd`, which reverses spelling.
- Splitting on spaces without filtering retains empty tokens and extra spaces.
- Repeatedly prepending to an immutable string can repeatedly copy growing output,
  taking O(n²) time; append to a builder instead.
- `[start, endExclusive)` uses an exclusive end, not a substring length.
- “Two pointers” describes bookkeeping, not the full memory cost of the algorithm.

## Interview rehearsal

“I need to reverse words while preserving their characters and normalizing spaces.
A split-and-reverse solution is linear but stores a word list. I can avoid that
list by scanning from the right, skipping spaces and finding each word's bounds.
I append each range forward and add a separator only before subsequent words.
The scan pointer only decreases, giving linear time, and the output builder uses
linear space. With an existing mutable buffer, compaction and two levels of
reversal give a constant-extra-space alternative.”

Try explaining why `right + 1` is the word's start, predicting the trace for
`"ab cd"`, and showing why whole-string reversal needs per-word reversal afterward.
