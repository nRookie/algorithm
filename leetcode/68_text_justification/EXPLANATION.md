# 68. Text Justification — Kotlin

## Contract

Given nonempty `words`, produce lines of exactly `maxWidth` characters. Keep
words in their original order and greedily put as many words as possible on
each line. Every word is nonempty and its length does not exceed `maxWidth`.
The input is not modified.

For a non-last line with multiple words, distribute spaces evenly between
words, giving the leftmost gaps any remainder. The last line has single
spaces between words and padding at the end. A single-word line also has
padding at the end.

Using `·` to show spaces, both of these lines have width 16:

```text
Left-justified:  This·is·an······
Fully justified: This····is····an
```

Left justification means the text begins at the left edge; unused space goes
after the text. Full justification spreads that space between words.

## Your reasoning, polished

This is a polished account of the reasoning you supplied, followed by the
refinements discussed together:

> I first try to put as many words as possible on the current line. When I
> try another word, I include its length and one separator unless the line
> is empty. If the candidate length is at most `maxWidth`, I accept it and
> advance `i`. Otherwise, I finish the current line and leave `i` unchanged,
> because I have not appended that word yet. It will be tried on the next line.
>
> I originally stored word indexes and separate space counts. Keeping those
> structures synchronized made the state difficult to maintain. Storing the
> words directly and tracking `wordWidth`, the total length of accepted words
> without spaces, makes the spacing calculation simpler: the total number of
> spaces needed is `maxWidth - wordWidth`.
>
> For a normal line, I distribute those spaces across the gaps. My first
> implementation cycles through gaps from left to right, adding one space
> at a time. Division gives the number each gap receives, and the remainder
> tells me how many leftmost gaps get one more. For a single-word line, all
> spaces go at the end. For the last line, I use one space between words and
> put the remaining spaces at the end.

Corrections to the original comments:

- The acceptance test is `<= maxWidth`, because an exact fit is valid.
- `This`, `is`, and `an` have 8 word characters. At width 16, they need
  **8 total spaces**, or **6 additional spaces** beyond the two minimum
  separators. Do not mix these quantities.
- The final line is known after all its words are accepted: `i == words.size`.
  Merely pointing at the final input word does not mean it has been consumed.
- In your latest code, `candidateWidth` accumulates accepted width and then
  temporarily includes a rejected candidate. In the readable version it is
  a fresh local calculation, so it has one meaning each time it is used.

## Solution evolution

### 1. Store indexes and spacing separately

Your first approach stored indexes in `positions` and space counts in a
parallel structure, then reconstructed the result. This can represent the
answer, but requires clear agreement about whether a count means spaces
before or after a word. In your supplied early attempt, the `slotNumber == 1`
branch adds spaces before the first word even for a two-word non-last line;
the last-line reconstruction also omits single separators. Treat it as an
intermediate attempt rather than a correct baseline.

### 2. Your working baseline: store words and distribute spaces cyclically

[OriginalSolution.kt](OriginalSolution.kt) preserves your latest version,
with formatting polished and the class renamed so both implementations can
be compiled together. It greedily selects words, formats each completed row,
and joins the stored strings at the end.

Cycling through gaps is correct: every full pass adds one space to every gap;
the final partial pass gives an extra space to a prefix of the gaps. However,
`+= " "` copies a growing immutable string on each append. Keeping all rows
also retains intermediate text until the final joining step.

**What to say:** “My algorithm is correct, but its state mixes line selection
and formatting. I can process one line at a time and compute the gap sizes
directly instead of repeatedly updating strings.”

### 3. Readable implementation: choose a line, then format it

[68.kt](68.kt) is the submission code. The outer loop processes one line.
The inner loop selects its words; `formatLine` applies the appropriate rule.

With `k` existing words and `wordWidth` accepted word characters, adding the
candidate creates `k` gaps. Therefore:

```text
candidateWidth = wordWidth + candidateWord.length + k
```

This includes the separator count without maintaining another counter.
If the candidate does not fit, the inner loop breaks before changing state.
Thus `i` already points to the next line's first word.

For `g` gaps and `S = maxWidth - wordWidth` spaces:

```text
spacesPerGap = S / g
extraSpaces = S % g
gap j gets spacesPerGap + (1 if j < extraSpaces, otherwise 0)
```

Handle last lines and single-word lines before division, so `g` is positive
whenever this formula is used. Append the words and spaces to a builder.

**What to say:** “I separate selecting words from formatting them. Once a
line is selected, division and remainder determine every gap, and a mutable
builder constructs the result without repeatedly copying prefixes.”

| Approach | Main state | Worst-case time | Auxiliary space excluding returned output |
| --- | --- | --- | --- |
| Working baseline | All rows, word characters, accumulated width, gap cursor | O(n + L·W²) | O(n + L·W) |
| Readable version | Current line, word characters, next input index | O(n + L·W) | O(W) |

Here `n` is the number of words, `L` the number of output lines, and
`W = maxWidth`. The baseline bound includes repeated immutable string copies.
Each implementation returns O(L·W) characters. The readable implementation
does work proportional to traversal and output construction.

## Variable meanings and formatting cases

| Variable | Meaning |
| --- | --- |
| `i` | Next word not yet accepted into a line |
| `lineWords` | Accepted words of this line, in input order |
| `wordWidth` | Sum of their lengths, excluding all spaces |
| `candidateWidth` | Minimum line length if the next word were accepted |
| `isLastLine` | All input words have now been accepted |
| `gapCount` | Number of gaps between words |
| `totalSpaces` | All spaces needed to make this line width W |
| `extraSpaces` | Number of leftmost gaps receiving one additional space |

| Line type | Formatting |
| --- | --- |
| Last line | Join with single spaces; pad the end |
| Other line with one word | Pad the end |
| Other line with multiple words | Divide spaces evenly; give the remainder to the left |

The first two cases share the same implementation. `j < gapCount` prevents
adding a gap after the final word.

## Execution trace

Input: `["a", "b", "c", "dddd"]`, `maxWidth = 6`.
The table shows the readable implementation. `·` denotes a space.

| Step | State before: i / words / wordWidth | Candidate width | Action and state after |
| --- | --- | --- | --- |
| Initial | 0 / [] / 0 | — | Start first line |
| Try a | 0 / [] / 0 | 0 + 1 + 0 = 1 | Accept: 1 / [a] / 1 |
| Try b | 1 / [a] / 1 | 1 + 1 + 1 = 3 | Accept: 2 / [a, b] / 2 |
| Try c | 2 / [a, b] / 2 | 2 + 1 + 2 = 5 | Accept: 3 / [a, b, c] / 3 |
| Try dddd | 3 / [a, b, c] / 3 | 3 + 4 + 3 = 10 | Break; i remains 3 |
| Format | 3 / [a, b, c] / 3 | — | 3 spaces, 2 gaps: base 1, remainder 1; output `a··b·c` |
| Start next line | 3 / [] / 0 | — | Reset only local line state |
| Try dddd | 3 / [] / 0 | 0 + 4 + 0 = 4 | Accept: 4 / [dddd] / 4 |
| Inner loop ends | 4 / [dddd] / 4 | — | All words consumed: last line |
| Format | 4 / [dddd] / 4 | — | Output `dddd··` |
| Finished | i = 4 | — | Outer loop ends; return both lines |

## Why it works

Before each inner iteration, `lineWords` contains exactly the words accepted
for this line, `wordWidth` is their character sum, and `i` points to the next
unconsumed word. Accepting a candidate updates all three consistently.
Breaking changes none of them.

The fit calculation includes the minimum required separators. A rejected
word would make the line too long even with one space per gap, so it cannot
be included. Since words stay in order, stopping there gives the longest
allowed prefix, as required by the greedy rule.

Line selection guarantees enough room for one separator per gap. For normal
lines, writing `S = q·g + r` shows that the gap formula uses exactly S spaces.
Gap sizes differ by at most one, and only the first r gaps are larger.
Left-justified lines fit when joined with single spaces and are padded to W.
Every output line therefore has exactly W characters and preserves word order.

Every word fits on an empty line by the input guarantee, so each outer
iteration accepts at least one word. Accepted words advance `i`, and there
are only n words. Both loops terminate; every word is emitted exactly once.

## StringBuilder: capacity versus length

```kotlin
val line = StringBuilder(maxWidth)
```

This starts with length **0** and reserves initial capacity for `maxWidth`
characters. It is not a fixed-size buffer or a maximum-length restriction:
the builder can grow if more characters are appended. Our formatting logic
ensures the final length is exactly `maxWidth`.

`StringBuilder()` also works. Providing the known final size avoids needing
to grow the backing storage while constructing the line. Directly appending
spaces with `repeat(gapWidth)` avoids allocating temporary space strings;
`line.append(" ".repeat(gapWidth))` is also correct and has the same linear
time bound for line construction.

## Edge cases and local verification

Derive tests from decisions: below, exactly at, or above the width boundary;
then last line, single-word line, or multiple-word line. Use tiny inputs that
exercise those rules instead of trying to imagine every large input.

[Main.kt](Main.kt) checks the standard width-16 example, exact fit, a rejected
candidate and single-word rows, uneven gaps, a two-word non-last line, one
input word, and width 1. It compares both implementations with explicit
expected outputs and checks every line's width.

From this folder:

```sh
kotlinc 68.kt OriginalSolution.kt Main.kt -include-runtime -d /private/tmp/text-justification-check.jar
java -jar /private/tmp/text-justification-check.jar
```

Submit only `68.kt`. Passing examples supports the review; the invariant and
formatting argument above establish correctness for all valid inputs.

## Interview explanation and rehearsal

> “I process one line at a time. I greedily accept words while their total
> character count plus the minimum separators fits the width. When the next
> word does not fit, I leave its index unchanged. I then format the selected
> line: the last line or a single-word line is left-justified; otherwise, I
> divide the required spaces by the gap count and give the remainder to the
> leftmost gaps. I build the line with StringBuilder. The time is O(n + L·W),
> and working space is O(W), excluding the returned lines.”

Practice explaining these without looking at the code:

1. Why does adding a word to k existing words require k separators?
2. Why does an exact fit belong in the accept branch?
3. Why must `i` stay unchanged when the candidate does not fit?
4. Why is the current line never empty when formatting begins?
5. What do the quotient and remainder represent? Explain `S = 3`, `g = 2`.
6. Why does a last line with multiple words use a different rule?
7. Does `StringBuilder(maxWidth)` create a string of that length?

Next, explain the four-word execution trace aloud, naming the meaning of each
variable before describing its updates.
