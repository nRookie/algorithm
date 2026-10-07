# Valid Palindrome: stream follow-up interview

A polished record of our mock interview. These are practice questions, not a
guaranteed question list for any company. The original string solution and proof
are in [EXPLANATION.md](EXPLANATION.md).

## Clarify the contract first

**Interviewer:** What if the input arrives as a stream?

**Your question:** When does the stream end, and how is that indicated?

A final whole-string answer needs a finite input boundary. A file can signal
EOF; a network protocol can supply a length or an end marker. A chunk boundary
alone does not indicate the end. For example, `"aba"` is a palindrome, but
receiving another `"c"` changes the result.

Our simulated contract: a finite ASCII character stream, initially at most
200,000 characters, read once through an iterator. `hasNext()` becomes false
at the end. We require an exact answer after completion. Later, the interviewer
removes the assumption that the stream fits in RAM.

**Your question:** Does reading once mean I can call `hasNext()` only once?

No. `hasNext()` can be called repeatedly and does not consume a character.
`next()` consumes the next character. One pass means no rewinding or rereading
consumed input unless you saved it yourself.

```kotlin
while (stream.hasNext()) {
    val c = stream.next()
    // Retain information needed later.
}
```

Also clarify whether replay or external storage is allowed. Checking every
prefix is a different requirement from checking one complete message.

## Solution evolution

### 1. Buffer the finite stream, then reuse two pointers

**Your proposal, polished:** “I would save the incoming characters, then reuse
my previous palindrome implementation once the stream ends. How large is the
stream, and does it fit in memory?”

Buffering restores indexed access to both ends. Reading n characters and then
checking them costs O(n) processing time and O(n) extra storage. Appending to a
builder avoids repeated immutable-string concatenation and its repeated copying.
Network waiting affects elapsed time separately from algorithmic work.

**Size correction:** 200,000 ASCII bytes occupy 200,000 bytes, about 200 KB
(decimal), not 20,000 bytes. A Kotlin/JVM `CharArray` uses two bytes per element,
about 400 KB for that many characters, plus overhead. Actual string/builder
storage depends on implementation; ASCII content alone does not imply one byte
per character in every in-memory representation.

**What to say:** “If it fits in memory, I will buffer the stream and reuse two
pointers. Processing is O(n), and the buffer takes O(n) extra space.”

### 2. Filter and lowercase while receiving

**Your proposal, polished:** “As in our original code, I can skip punctuation
as the characters arrive.”

Store only lowercase alphanumeric characters. After the stream ends, compare
`buffer[left] == buffer[right]`; no further filtering or lowercasing is needed.
This discards exactly the information that the problem says to ignore and
preserves the order of the retained sequence.

For n incoming characters and k retained characters, processing is O(n), with
O(k) stored data (plus any input chunk buffer). Worst-case storage remains O(n)
because all characters might be alphanumeric. A builder preallocated to n would
still reserve O(n) space even when k is small.

Chunks do not make independent palindrome checks valid: `"ab" | "ba"` forms
`"abba"`, even though neither chunk is a palindrome by itself.

**What to say:** “I will normalize during ingestion and retain only the relevant
characters. This uses O(k) storage, but still O(n) in the worst case.”

### 3. Explore compression when RAM is insufficient

**Your proposal, polished:** “Since I need to compare both ends, could I compress
the saved input?”

Lossless compression can help repeated or structured data, but cannot guarantee
that arbitrary input shrinks enough to fit. Exact comparison must preserve all
distinctions that could affect the answer. A hash can collide, so a fingerprint
alone is not an exact replacement. Our mock interview did not derive a hashing
algorithm; it kept the exact-answer requirement.

**What to say:** “Compression might help typical inputs, but I cannot rely on
it for a worst-case memory guarantee. Is external storage available?”

### 4. Save normalized data to disk and compare blocks

**Your proposal, polished:** “I can save the stream to a file, then use two
pointers to compare it from both ends, chunk by chunk.”

Assume enough disk space and random access to a file. Write lowercase ASCII
alphanumeric characters as single bytes, using a bounded write buffer. Once
ingestion ends, the file length k is known.

Keep the file open. Load a block from the beginning and another from the end.
Compare the left block forward against the right block backward. Refill when
a block is exhausted and move the global indexes inward. Stop at a mismatch,
or when the indexes meet/cross; do not compare beyond the middle.

Example: normalized file `"abccba"`, block capacity B = 2:

| State before comparison | Global indexes | Pair | Next state |
| --- | --- | --- | --- |
| Left block `ab`, right block `ba` | `(0,5)` | `a == a` | `(1,4)` |
| Same blocks | `(1,4)` | `b == b` | `(2,3)` |
| Refill for remaining interval `cc` | `(2,3)` | `c == c` | `(3,2)` |
| Pointers crossed | `(3,2)` | None | Return true |

**Correctness:** Every pair outside `[left, right]` has matched. Blocks only
change how characters are fetched; they do not change which mirrored pairs
are compared. A successful comparison shrinks the interval by two, so it ends.
Empty and single-byte files need no comparisons. Final partial blocks and
overlapping blocks must respect the global indexes.

**Costs:** O(n) processing, O(B) RAM, and O(k) disk storage. Buffered output and
block reads require O(1 + k/B) block operations each in the ideal block model.
Wall-clock performance also depends on device latency, seeks, and throughput.
Moving storage to disk bounds RAM; it does not eliminate total storage.

**Interviewer:** Why blocks instead of reading one character at a time?

**Your reasoning, polished:** “Disk access is expensive, especially seeks on an
HDD. I want to compare many characters in memory per disk operation.”

Keep the file open rather than reopening it per character. Blocks reduce small
reads and repeated seeking. Avoid a fixed claim such as “disk is 1,000 times
slower than RAM”; the ratio depends on hardware and access patterns.

**What to say:** “I will write a normalized file, then read blocks from both
ends and compare them in opposite directions. This gives an exact result with
O(B) RAM and O(k) disk storage, while reducing disk operations.”

## Rehearsal

Explain the progression aloud: clarify the end signal and access model; buffer
if it fits; filter during ingestion; if it does not fit, ask about disk storage
and compare blocks. Distinguish CPU work, elapsed time, RAM, and disk usage.

Try tracing `"abccba"` again with B = 4: how do global pointers prevent extra
comparisons when the loaded blocks overlap?
