# 209. Minimum Size Subarray Sum

## Contract and implementation review

[Official problem](https://leetcode.com/problems/minimum-size-subarray-sum/):
given positive integers `nums` and a positive `target`, return the minimum
length of a contiguous subarray with sum **greater than or equal to** `target`.
Return `0` if no such subarray exists.

**Your implementation is correct.** Your explanation already identifies the
essential property: positive values make the sum increase when extending right
and decrease when removing from the left. The main clarification is to define
the window precisely and separate the reasons for expanding and shrinking.

Two small corrections:

1. In your comments, replace `subSum > target` with `subSum >= target`.
   Equality is valid and must also trigger recording and shrinking. Your
   actual shrinking loop already handles this correctly.
2. Your final line `if (windowSum == target) ans = minOf(ans, right - left)`
   is redundant. After the shrinking loop, the sum is below `target`.
   If the window becomes empty, its sum is zero, also below the positive
   target. Equality has already been handled inside the loop.

## Your explanation, polished

“I first consider enumerating each left boundary and extending a right
boundary while maintaining the subarray sum. Whenever the sum is at least
the target, I update the minimum length. This takes O(n²) time in the worst
case because I restart the right boundary for each left boundary.

All values are positive, so extending a window increases its sum and removing
its leftmost value decreases its sum. I can therefore maintain a single
window and move both boundaries only forward.

I define the current window as `[left, right)`: `left` is included and
`right` is excluded. Its length is `right - left`, and `windowSum` is exactly
the sum of the values inside it.

When the sum is below the target, I add `nums[right]` and advance `right`.
When the sum reaches or exceeds the target, I record the current length,
then remove `nums[left]` and advance `left` to try a shorter window. I keep
shrinking while the window is valid.

I record a valid window before removing anything, because the removal may
make it invalid. Once the sum is too small again, I expand to the right.
Each boundary advances at most n times, giving O(n) total time and O(1)
extra space. If no valid window was found, I return zero.”

This is your existing approach with its boundary convention and update order
made explicit, not a different algorithm.

## Variable definitions

| Variable | Exact meaning | Initial value |
| --- | --- | --- |
| `target` | Minimum acceptable sum; equality qualifies | Input |
| `nums` | Input array of positive integers; never modified | Input |
| `n` | Number of input elements; also the largest possible exclusive right boundary | `nums.size` |
| `left` | Inclusive start index of the current window; next index to remove when shrinking | `0` |
| `right` | Exclusive end index of the current window; next index to add when expanding | `0` |
| `windowSum` | Sum of `nums[left]` through `nums[right - 1]`; zero for an empty window | `0` |
| `ans` | Smallest valid window length recorded so far; sentinel means none found | `Int.MAX_VALUE` |

The boundary invariant is `0 <= left <= right <= n`.

```text
Indices:     0   1   2   3   4   5
Values:      2   3   1   2   4   3
                 ↑           ↑
                left        right

left = 1, right = 4
Window = nums[1..3] = [3, 1, 2]
windowSum = 6
Window length = right - left = 3
nums[right] = 4 is outside the window and would be added next.
```

When `right == n`, it is a valid boundary but not a valid array index.
The guard `right < n` must hold before accessing `nums[right]`.
When `left == right`, the window is empty; neither endpoint identifies an
element currently inside it.

## Solution evolution

### 1. Enumerate left boundaries and extend right

For each `left`, reset a sum to zero and add elements from that index onward.
Using an inclusive right index in this baseline, a valid length is
`right - left + 1`. With positive values, the first valid window for a fixed
left boundary is its shortest, so that inner scan can stop there.

This is correct because each possible start gets its shortest valid ending,
if one exists. It still costs O(n²) in the worst case, such as when the target
exceeds the total array sum. Extra space is O(1).

For `target = 7`, `nums = [2, 3, 1, 2, 4, 3]`, starting at index 0 first
reaches the target with `[2, 3, 1, 2]`. Restarting from index 1 would repeat
work on values already visited.

**What to say:** “The baseline checks each start independently. Its repeated
work comes from resetting the sum and right boundary.”

### 2. Reuse one window with two forward boundaries

After removing the leftmost positive value, the sum becomes smaller.
An earlier ending that was insufficient before removing that value cannot
become sufficient afterward. There is no reason to move `right` backward.

Maintain `[left, right)` and its sum instead of rebuilding each candidate.
After `[2, 3, 1, 2]` reaches sum 8, record length 4 and remove 2. The remaining
window `[3, 1, 2]` has sum 6; add the next value, 4, to continue from there.

This reuses previous work, reducing time to O(n) with O(1) extra space.

**What to say:** “Positivity lets me keep the right boundary where it is when
the left boundary advances. Each element is added at most once and removed
at most once.”

| Approach | Time | Extra space | Repeated work |
| --- | --- | --- | --- |
| Restart for each left boundary | O(n²) | O(1) | Rebuild overlapping window sums |
| Reuse the sliding window | O(n) | O(1) | Each value enters and leaves at most once |

## Polished implementation

Your two-phase loop and variable names are preserved. The only behavioral
code removed is the unreachable equality check after shrinking.

```kotlin
class Solution {
    fun minSubArrayLen(target: Int, nums: IntArray): Int {
        val n = nums.size
        var left = 0
        var right = 0
        var windowSum = 0
        var ans = Int.MAX_VALUE

        // Current window: [left, right).
        while (right < n) {
            // Expand until valid, or until no more values are available.
            while (right < n && windowSum < target) {
                windowSum += nums[right]
                right++
            }

            // Record each valid window before trying a shorter one.
            while (left < right && windowSum >= target) {
                ans = minOf(ans, right - left)
                windowSum -= nums[left]
                left++
            }
        }

        return if (ans == Int.MAX_VALUE) 0 else ans
    }
}
```

Under the official limits, `nums.size <= 100_000` and `nums[i] <= 10_000`.
The total sum is at most 1,000,000,000, so `Int` is sufficient here.

## Update order: keep the window and sum synchronized

Expand:

```kotlin
windowSum += nums[right] // Add the first element outside the window.
right++                 // Move the boundary past that element.
```

Shrink:

```kotlin
ans = minOf(ans, right - left) // Record the currently valid window.
windowSum -= nums[left]       // Remove its first element.
left++                       // Move the boundary past that element.
```

After each complete add/advance or remove/advance pair, `windowSum` again
equals the sum in `[left, right)`. Avoid mixing this exclusive-right
convention with the baseline's inclusive-right length formula.

## Full trace

`target = 7`, `nums = [2, 3, 1, 2, 4, 3]`.
Each row shows the state **after** the listed action. `∞` represents the
sentinel `Int.MAX_VALUE`.

| Action | `left` | `right` | `windowSum` | `ans` | Current window |
| --- | --- | --- | --- | --- | --- |
| Initialize | 0 | 0 | 0 | ∞ | `[]` |
| Add index 0: 2 | 0 | 1 | 2 | ∞ | `[2]` |
| Add index 1: 3 | 0 | 2 | 5 | ∞ | `[2, 3]` |
| Add index 2: 1 | 0 | 3 | 6 | ∞ | `[2, 3, 1]` |
| Add index 3: 2 | 0 | 4 | 8 | ∞ | `[2, 3, 1, 2]` |
| Record length 4; remove index 0: 2 | 1 | 4 | 6 | 4 | `[3, 1, 2]` |
| Sum too small; add index 4: 4 | 1 | 5 | 10 | 4 | `[3, 1, 2, 4]` |
| Record length 4; remove index 1: 3 | 2 | 5 | 7 | 4 | `[1, 2, 4]` |
| Record length 3; remove index 2: 1 | 3 | 5 | 6 | 3 | `[2, 4]` |
| Sum too small; add index 5: 3 | 3 | 6 | 9 | 3 | `[2, 4, 3]` |
| Record length 3; remove index 3: 2 | 4 | 6 | 7 | 3 | `[4, 3]` |
| Record length 2; remove index 4: 4 | 5 | 6 | 3 | 2 | `[3]` |
| Shrinking stops; outer condition fails | 5 | 6 | 3 | 2 | Return `2` |

Notice that reaching `right == n` does not immediately end the current outer
iteration. Its shrinking phase still runs, which is how `[4, 3]` is found.

## Why no better answer is skipped

There are two safe decisions:

1. **Expand an invalid window.** If its sum is below the target, removing a
   positive value only decreases it further. No shorter suffix at this right
   boundary can be valid, so the algorithm needs more values from the right.
2. **Record and shrink a valid window.** Record the current length first.
   Afterward, future windows with this same left boundary and a farther right
   boundary are longer, so they cannot improve on the recorded length. It is
   safe to discard this left boundary permanently.

While the window stays valid, repeated shrinking tests shorter candidates.
When it becomes invalid, further shrinking cannot help. These decisions
discard only candidates that cannot improve the answer. All recorded windows
are valid, so their minimum is exactly the required minimum.

After each shrinking phase, the sum is below the target. If more values
remain, the next expansion advances `right` at least once. Each pointer is
bounded by `n`, so the algorithm terminates. If no window was recorded, the
sentinel remains and the result is `0`.

## Why nested loops are still O(n)

Count total pointer movements across the entire execution, not loop nesting:

- `right` moves from 0 to at most `n`, adding each element at most once.
- `left` moves from 0 to at most `n`, removing each element at most once.
- Each outer iteration advances `right`, so outer-loop overhead is also O(n).

Total time is O(n); only a fixed number of variables is stored, giving O(1)
extra space.

## Edge cases and debugging checkpoints

Expected results from manual review; no executable tests were run.

| `target` | `nums` | Result | What it checks |
| --- | --- | --- | --- |
| 7 | `[7]` | 1 | Equality qualifies |
| 7 | `[8]` | 1 | Overshooting also qualifies |
| 7 | `[1, 2, 3]` | 0 | No valid window |
| 7 | `[2, 2, 3]` | 3 | Only the whole array works |
| 4 | `[1, 4, 4]` | 1 | Shrink repeatedly, not just once |
| 7 | `[2, 3, 1, 2, 4, 3]` | 2 | Best window ends at the array boundary |

For debugging, check these statements before changing conditions:

- Is `right` exclusive everywhere, including the length calculation?
- Does the stored sum match the current window after every boundary update?
- Is the answer recorded before removing the leftmost element?
- Does the shrinking condition include equality?
- Does shrinking still run after expansion reaches `n`?

The positivity assumption is essential to this reasoning. With negative
values, removing an element can increase the sum. For example, for target 3
and `[1, -1, 3]`, this approach records length 3, removes 1, and stops
shrinking at sum 2, missing the length-1 window `[3]`. That input is outside
this problem's contract.

## Recall for the next review

- Define `[left, right)` and explain why its length is `right - left`.
- Explain why an invalid window needs expansion and a valid one permits shrinking.
- Explain why discarding a left boundary after recording it is safe.
- Explain why reaching the end does not skip the last shrinking phase.

Next time, write the window definition and the two update pairs before the
loops. Then trace `[7]` with target 7 to check equality, answer-update order,
and the empty-window state in one small example.
