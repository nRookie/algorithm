# Valid Palindrome: review and interview practice

Your implementation is correct for the ASCII problem contract. No particular
question list is guaranteed at any company; these are useful rehearsal prompts
based on your code.

## Contract and clarifications

Ignore punctuation and spaces, retain letters **and digits**, and ignore letter
case. Do not modify the input. Zero or one retained character is a palindrome.
The [official problem](https://leetcode.com/problems/valid-palindrome/) specifies
printable ASCII and input length 1 through 200,000.
Example 2 is `"race a car"` → `"raceacar"` → `false`.

## Solution evolution

### 1. Normalize, then compare with a reversed copy

Filter and lowercase the input, then compare it with its reverse.
For `"A, b! a"`, the normalized text and its reverse are both `"aba"`.
This follows directly from the palindrome definition. For original length n,
time and auxiliary space are O(n). Reversing allocates another buffer.

**What to say:** “I can normalize the string and compare it with its reverse.
This gives a simple linear-time baseline with linear extra space.”

### 2. Your solution: normalize, then compare endpoints

We already have indexed access to the normalized text, so comparing mirrored
pairs removes the need for a reversed copy and permits early comparison failure.
Your `left` and `right` index `sb`, not `s`. `n` is the original length;
`sb.length` is the number of retained characters.

For `"A, b! a"`, `sb` is `"aba"`:

| State before comparison | `left` | `right` | Action / next state |
| --- | --- | --- | --- |
| Initial | 0 (`a`) | 2 (`a`) | Equal; move to `(1, 1)` |
| Terminal | 1 (`b`) | 1 (`b`) | Loop condition false; return true |

For `"raceacar"`, compare indexes `(0,7)` → `r == r`, `(1,6)` → `a == a`,
`(2,5)` → `c == c`, then `(3,4)` → `e != a`: return false.

**Invariant:** Every mirrored pair outside `[left, right]` has matched. A
mismatch proves failure; a match removes two endpoints while preserving this
invariant. Meeting or crossing leaves at most one character, requiring no
comparison. Every successful iteration shrinks the interval by two, ensuring
termination. An empty builder gives `right = -1`, so the loop safely returns true.

**Cost:** O(n) time and O(n) auxiliary space. `StringBuilder(n)` reserves capacity
based on the original length even if few characters survive. Sequential linear
passes add their costs, rather than multiplying into O(n²). Early comparison
failure still occurs after the complete normalization pass.

**What to say:** “I build a lowercase alphanumeric sequence, then compare its
outermost remaining characters. Each match removes a pair. If no pair differs,
it is a palindrome. The scan is linear, and the builder takes linear space.”

### 3. Follow-up: normalize only the current endpoints

We store the entire normalized sequence, but each character is needed only for
one pair comparison. Skipping ignored characters in the original input retains
their order, so pointers can find the next relevant endpoints directly.
Lowercase only the characters being compared. See
[ConstantSpaceSolution.kt](ConstantSpaceSolution.kt).

For `"A, b! a"` (indexes 0 through 6), compare `A` at 0 with `a` at 6, then
advance to `(1,5)`. The left skip loop moves 1 → 2 → 3 (`b`), and the right
skip loop moves 5 → 4 → 3. The pointers meet; return true.

The invariant now concerns the **logically filtered sequence**. Skipping ignored
characters removes no relevant element, and each comparison checks its next
mirrored pair. Guard skip loops with `left < right`, then check whether the
pointers have met before comparing. This handles all-punctuation inputs safely.

Each pointer moves only inward, so all skips and comparisons together take
O(n) time despite nested loops. Auxiliary space becomes O(1). This improves
space, not asymptotic time. Worst-case linear time is necessary: on an all-`a`
input of length n >= 2, changing any unexamined position to `b` changes the answer.

**What to say:** “I can avoid the builder by skipping punctuation at both ends
of the original string. I lowercase and compare the next valid pair, then move
inward. Total pointer movements are linear, with constant extra space.”

| Approach | Worst-case time | Auxiliary space |
| --- | --- | --- |
| Normalize and reverse | O(n) | O(n) |
| Your builder and pointers | O(n) | O(n) |
| Skip directly in the input | O(n) | O(1) |

## Likely interview follow-ups

1. **Why two pointers?** Palindromes require symmetric pairs to match; each
   successful pair leaves the same task on a smaller interval.
2. **Can you reduce space?** Explain the transition from stored normalization
   to skipping ignored characters directly in the input.
3. **Why `left < right`?** A middle character matches itself; empty and
   single-character normalized sequences need no comparisons.
4. **Which edge cases matter?** All punctuation, one retained character,
   mixed case, digits, asymmetric punctuation, and late mismatch. `"0P"` is
   false; dropping digits would incorrectly return true.
5. **Why aren't the skip loops quadratic?** Bound total pointer movement
   over the entire execution, rather than multiplying loop bounds.
6. **What about Unicode?** The helpers work for the ASCII contract. For
   arbitrary Unicode, clarify code points versus UTF-16 units, normalization,
   and case folding first. A `Char` loop and single-character lowercasing do
   not implement every possible Unicode palindrome policy.

## Validation and rehearsal

`Main.kt` checks both implementations on boundary cases and against an independent
ASCII filter/reverse oracle for every nonempty string up to length 5 over six
representative characters. Passing cases supports, but does not replace, the proof.

Practice giving the 30-second explanation of your existing solution, then
derive the space improvement. Before coding again, predict both pointers on
`".,!?"` and `"a."`, and explain why the loops terminate.
