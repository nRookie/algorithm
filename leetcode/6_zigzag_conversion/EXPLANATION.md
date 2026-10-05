# 6. Zigzag Conversion — Kotlin

## Contract

Write the characters of `s` down and diagonally up through `numRows` rows,
repeating that movement. Return the rows concatenated from top to bottom.
Assume `numRows >= 1`; the input string is not modified.

For `s = "PAYPALISHIRING"` and `numRows = 3`:

```text
P   A   H   N
A P L S I I G
Y   I   R

Result: "PAHNAPLSIIGYIR"
```

## Your reasoning, polished

> I start at the top row and move downward. At the bottom row, I reverse
> direction and move upward; at the top, I reverse again. Each row has its own
> buffer. Since the answer reads each row from left to right, I can append each
> character directly to its row and omit the spaces and column positions.
> Finally, I concatenate the row buffers from top to bottom.

Your original explanation grouped the 3-row example into `PAY`, `P`, `ALI`,
`S`, `HIR`, `I`, `NG`. Those groups yield the correct row sequence. Tracking
the current row and reversing at the endpoints expresses the rule more clearly
for arbitrary row counts.

## Solution evolution

### 1. Your implementation: row strings and a Boolean direction

This is a correct simulation for valid row counts. Before appending a character,
`row` identifies its destination. After moving to an endpoint, your code changes
`down`, so the next iteration writes at that endpoint before moving away.

The original implementation, with comments and formatting shortened:

```kotlin
class Solution {
    fun convert(s: String, numRows: Int): String {
        val strs = Array<String>(numRows) { "" }
        var row = 0
        var down = true
        if (numRows == 0 || numRows == 1) return s

        for (c in s) {
            strs[row] += c
            if (down == true) {
                row++
                if (row == numRows - 1) down = false
            } else {
                row--
                if (row == 0) down = true
            }
        }

        var res = ""
        for (str in strs) res += str
        return res
    }
}
```

The limitation is allocation and copying: Kotlin strings are immutable.
`strs[row] += c` constructs a new string containing the previous row and the
new character. For a row receiving k characters, the copied lengths add up to
`1 + 2 + ... + k = Θ(k²)`. `res += str` also copies accumulated output.

Let n be the string length and r the row count. This implementation has
O(n² + r) worst-case time and O(n + r) peak auxiliary space, including the
row array. Cumulative allocation can be quadratic even though peak live
storage is linear. The one-row case returns early.

**What to say:** “The simulation is correct, but repeatedly appending to
immutable strings copies previous characters. I can keep the same traversal
and replace each row string with a mutable builder.”

### 2. Idiomatic rewrite: row builders and a signed step

The submission is saved in [6.kt](6.kt):

```kotlin
class Solution {
    fun convert(s: String, numRows: Int): String {
        if (numRows == 1 || numRows >= s.length) return s

        val rows = Array(numRows) { StringBuilder() }
        var row = 0
        var step = 1

        for (c in s) {
            rows[row].append(c)

            when (row) {
                0 -> step = 1
                numRows - 1 -> step = -1
            }
            row += step
        }

        return rows.joinToString(separator = "")
    }
}
```

- `rows` replaces `strs` with one independent mutable buffer per row.
- `row` still identifies where the current character belongs.
- `step` replaces `down`: +1 moves downward; -1 moves upward.
- `when` chooses the next movement at the current endpoint, after appending.
- `joinToString(separator = "")` combines the rows without extra separators.

The direction update has moved: the original switches after moving to the next
row; this rewrite switches at the current row before moving. Both produce the
same destinations. Do not mix the timing of these two implementations.

With one row, movement is unnecessary. With at least n rows, each character
occupies a separate row before any upward movement, so reading rows returns s.
Checking these cases before allocation avoids unnecessary buffers.

Builder append is amortized O(1) per character; joining reads all n characters
and visits r buffers. The nontrivial case has `r < n`, so total time is O(n)
and auxiliary space is O(n), including the builders. The returned string also
occupies O(n) space. Producing an n-character result requires Ω(n) work in
the general case, so this meets the output-size lower bound.

## Execution trace

For `s = "ABCDE"`, `numRows = 3`, using the rewritten code:

| Character | Row before append | Buffers after append | Boundary action | Next row / step |
| --- | --- | --- | --- | --- |
| Initial | 0 | `"", "", ""` | — | `0 / +1` |
| A | 0 | `"A", "", ""` | Top: step = +1 | `1 / +1` |
| B | 1 | `"A", "B", ""` | Interior: keep step | `2 / +1` |
| C | 2 | `"A", "B", "C"` | Bottom: step = -1 | `1 / -1` |
| D | 1 | `"A", "BD", "C"` | Interior: keep step | `0 / -1` |
| E | 0 | `"AE", "BD", "C"` | Top: step = +1 | `1 / +1` |
| Finished | — | Join buffers | No more input | `"AEBDC"` |

## Why it works

Before each iteration, `row` is the destination of the next character, and
each buffer contains exactly the already processed characters assigned to
that row, in their original order.

Initially, all buffers are empty and the first destination is row 0. Appending
places the next character correctly. Choosing +1 at the top and -1 at the
bottom, while retaining the step in the interior, follows the zigzag and keeps
the next row in bounds. The early return handles the case where top and bottom
would be the same row.

The loop processes exactly n characters and ends. Concatenating the buffers
then gives exactly the required row-by-row output.

## Interview explanation and recall

> “I only need each character's row, so I store one StringBuilder per row.
> I append the character, reverse direction at the top or bottom, and move
> one row. Finally, I join the rows. Each character is appended and copied
> into the result a bounded number of times, giving O(n) time and O(n) space.”

Try explaining these without looking at the code:

1. Why can column positions and spaces be discarded?
2. Why does the one-row case require special handling?
3. What row sequence does the code generate for two rows?
4. Why can a single loop still take quadratic time with immutable strings?
