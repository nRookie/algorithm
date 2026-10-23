# 3. Longest Substring Without Repeating Characters

## Contract and review

Return the maximum length of a contiguous substring with no repeated
characters. Return `0` for an empty string. Characters are not limited to
letters: spaces and symbols also count.

**Your implementation is correct.** It maintains a duplicate-free window
using a `HashSet<Char>`. Include `import kotlin.math.max` for your original
`max` call, or use `maxOf` as in the code below.

The main explanation correction is that your comments describe a **last-index
map**, but your implementation uses a **current-window set**. Both approaches
work, but their state and left-boundary updates have different meanings.

## Your explanation, polished

“I maintain a substring `[left, right)` containing no repeated characters.
The set `seen` contains exactly the characters in that substring.

If `s[right]` is not in the set, I can safely add it, advance `right`, and
update the maximum length.

If `s[right]` is already in the set, I leave `right` where it is. I remove
characters from the left of the current window until the existing copy of
`s[right]` has been removed. The next expansion can then add `s[right]`
without creating a duplicate.

Both boundaries move only forward. Each character position enters the window
once and leaves at most once, so the total time is expected O(n).”

The incoming duplicate is **not yet inside the window**. Your code shrinks
before adding it, so the current window remains duplicate-free throughout.

## Variable definitions

| Variable | Exact meaning | Initial value |
| --- | --- | --- |
| `s` | Input string; not modified | Input |
| `n` | Number of indexed characters in `s` | `s.length` |
| `left` | Inclusive window start; next position removed when shrinking | `0` |
| `right` | Exclusive window end; next position considered for addition | `0` |
| `seen` | Exactly the characters currently in `s[left until right]`; no indexes or historical entries | Empty set |
| `ans` | Maximum valid window length recorded so far | `0` |

Always maintain `0 <= left <= right <= n`. The window length is
`right - left`. When `right == n`, it is a valid boundary but cannot be used
to access `s[right]`.

```text
s = a b c d b
    0 1 2 3 4
    ↑       ↑
   left    right

Window [0, 4) = "abcd"
seen = {a, b, c, d}
Incoming character s[4] = 'b' is outside the window.

Remove 'a', then the old 'b':
Window [2, 4) = "cd", seen = {c, d}

Now add the incoming 'b':
Window [2, 5) = "cdb", seen = {c, d, b}
```

## Solution evolution

### 1. Restart a scan at every left boundary

For each start, create an empty set and extend right until a character repeats.
Record the maximum length. Once a duplicate appears, extending further cannot
make that substring duplicate-free, so that start's scan can stop.

This checks the longest valid substring for every start and is correct, but
revisits overlapping characters. Its usual upper bound is O(n²) expected
time with hash-set operations and O(min(n, A)) space, where `A` is the number
of possible distinct characters. More precisely, the time is bounded by
O(n · min(n, A + 1)); the quadratic case requires sufficiently many distinct
characters.

**What to say:** “I can restart for each start position, but I repeatedly
rebuild sets for overlapping substrings.”

### 2. Your solution: preserve the valid suffix

When `"abcd"` encounters another `'b'`, clearing all state loses useful
information: `"cd"` can still be reused. Remove only the prefix through the
old `'b'`, then add the new one to obtain `"cdb"`.

The set tells us whether the incoming character conflicts with the current
window. Advancing `left` while removing characters finds and removes the
conflicting occurrence without restarting `right`.

**What to say:** “I preserve the longest usable suffix and remove only enough
characters to make the next addition valid. Both pointers move forward.”

| Approach | Expected time | Extra space |
| --- | --- | --- |
| Restart each start's scan | O(n²) upper bound | O(min(n, A)) |
| Reuse a set and window | O(n) | O(min(n, A)) |

### The map idea in your comments: an alternative

A map `lastIndex[character] = latest processed index` lets you jump directly
past a previous occurrence. When processing index `right`, use:

```kotlin
left = maxOf(left, previousIndex + 1)
```

The `maxOf` is essential because the previous occurrence may be outside the
current window. For `"abba"`, after handling the second `'b'`, `left = 2`.
The final `'a'` has previous index 0; assigning `left = 1` would incorrectly
move backward and include `"bba"`.

This map keeps history; your set keeps only current membership. Direct jumps
are an alternative O(n) approach, not an asymptotic improvement over your
set solution. A jump alone would not correctly update your existing set:
the removed prefix's characters would also need to be removed.

## Your implementation with clarified comments

The loop structure and variable names are preserved. `maxOf` replaces `max`
to avoid requiring an import.

```kotlin
class Solution {
    fun lengthOfLongestSubstring(s: String): Int {
        val seen = HashSet<Char>()
        var left = 0
        var right = 0
        val n = s.length
        var ans = 0

        // [left, right) is duplicate-free; seen represents this window.
        while (right < n) {
            // Add characters while each addition remains valid.
            while (right < n && !seen.contains(s[right])) {
                seen.add(s[right])
                right++
                ans = maxOf(ans, right - left)
            }

            // Leave the incoming character outside until its old copy is gone.
            while (right < n && left < right && seen.contains(s[right])) {
                seen.remove(s[left])
                left++
            }
        }
        return ans
    }
}
```

There is no need to update `ans` during shrinking: each new window is shorter
than the valid window it came from, which was already recorded.

## Complete trace

Input `"abcdb"`. Each row shows state after the action. Set order is only
illustrative.

| Action | `left` | `right` | `seen` | Window | `ans` |
| --- | --- | --- | --- | --- | --- |
| Initialize | 0 | 0 | `{}` | `""` | 0 |
| Add index 0: a | 0 | 1 | `{a}` | `"a"` | 1 |
| Add index 1: b | 0 | 2 | `{a, b}` | `"ab"` | 2 |
| Add index 2: c | 0 | 3 | `{a, b, c}` | `"abc"` | 3 |
| Add index 3: d | 0 | 4 | `{a, b, c, d}` | `"abcd"` | 4 |
| Incoming b already exists; stop expansion | 0 | 4 | `{a, b, c, d}` | `"abcd"` | 4 |
| Remove index 0: a; b still exists | 1 | 4 | `{b, c, d}` | `"bcd"` | 4 |
| Remove index 1: b; stop shrinking | 2 | 4 | `{c, d}` | `"cd"` | 4 |
| Next outer iteration: add index 4: b | 2 | 5 | `{c, d, b}` | `"cdb"` | 4 |
| End: `right == n` | 2 | 5 | `{c, d, b}` | `"cdb"` | Return 4 |

The final window is not necessarily the longest window. That is why `ans`
must preserve the best earlier length.

## Correctness and termination

Initially the window is empty and the set matches it. Adding a character
absent from the set preserves uniqueness. Removing the leftmost character
preserves uniqueness and, because no character repeats in the window,
removing that character from the set preserves exact membership.

Suppose the incoming character already occurs at position `p` within the
window. Any substring ending at the incoming position and starting at or
before `p` would contain both copies. Its start must therefore be at least
`p + 1`. Your shrinking loop removes exactly through `p`, retaining the
longest valid suffix before adding the new character.

Previously excluded starts cannot become valid again by extending right:
the duplicate pair that excluded them would still be present. Thus after
each addition, the algorithm has the longest valid substring ending at that
position. Taking the maximum over all additions gives the global answer.

If shrinking begins, the incoming character has exactly one occurrence in
the current window, so advancing `left` eventually removes it. The next
expansion then advances `right`. Both boundaries are bounded by `n`, so the
algorithm terminates.

## Complexity and edge cases

Each input position is added once and removed at most once. Hash-set
operations are expected O(1), so total time is expected O(n), despite the
nested loops. Set storage is O(min(n, A)); the pointers use O(1) space.

Expected results from manual review; no executable tests were run.

| Input | Result | What it checks |
| --- | --- | --- |
| `""` | 0 | No iterations |
| `"a"` | 1 | Single character |
| `"bbbbb"` | 1 | Remove the old occurrence before adding the next |
| `"abcdb"` | 4 | Best window can occur before the final window |
| `"abba"` | 2 | Repeated shrinking; no backward pointer movement |
| `"pwwkew"` | 3 | Contiguous substring, not a subsequence |
| `"a a"` | 2 | Space counts as a character |

## Recall for later

- Does `seen` represent all past characters or only the current window?
- Is the incoming duplicate already inside `[left, right)`?
- Why must shrinking continue until the old duplicate is removed?
- Why is removing a character from a set sufficient here without a count?
- Why does the map alternative need `maxOf(left, previousIndex + 1)`?

Next review: trace `"abba"` while stating the window and set after each move.
Keep the set-based explanation separate from the last-index-map explanation.
