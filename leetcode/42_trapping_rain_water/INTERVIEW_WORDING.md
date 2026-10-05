# Trapping Rain Water: understanding the proof and explaining it naturally

Companion to [the implementation and explanation](EXPLANATION.md).
This note preserves the clarification and wording feedback from our discussion.

## How to request this naturally

Your sentence:

> Please add these into a md, so I can review it later.

A natural version:

> Please save these explanations in a Markdown file so I can review them later.

Or, more casually:

> Could you put this in a Markdown file so I can review it later?

Use “save in a file” or “add to a file.” Say “a Markdown file,” rather than
“a md.” Use “them” for multiple explanations and “it” for a single note or file.
You do not need a comma before “so” here.

For your parenthetical question, you can say:

> By the way, how can I say that more naturally?

## Understanding the rightmost global maximum

The proof is easier to understand if you think of the tallest bar as a
**dividing point**.

“Global maximum” means the tallest height anywhere in the array. If several
bars have that height, choose the last one:

```text
index:    0  1  2  3  4
height:  [3, 0, 3, 0, 2]
               ↑
               m = 2
```

Both indexes 0 and 2 have the maximum height, 3. The rightmost one is index 2.
We choose `m` to explain the algorithm; your code does not need to find it
explicitly.

### Forward scan

- At index 1, accumulate 3 units of potential water.
- At index 2, the height is also 3. Equality is accepted, so commit those 3 units.
- After index 2, every bar is shorter than 3. Nothing can close another segment,
  so any additional `ss` stays unconfirmed.

The forward scan has counted the water before `m`.

### Reverse scan

- Start at index 4, with boundary height 2.
- At index 3, accumulate 2 units of potential water.
- At index 2, height 3 is strictly greater than 2. Commit those 2 units.
- Continue left. Index 0 also has height 3, but equality does not close a segment
  in this scan. Nothing else gets committed.

The reverse scan has counted the water after `m`.

```text
height:       [3, 0, 3, 0, 2]
water:        [0, 3, 0, 2, 0]
                  ↑     ↑
              forward reverse
```

Total: `3 + 2 = 5`.

Both scans visit overlapping positions, but they do not add water from
overlapping regions to the answer. The reverse scan can accumulate potential
water that the forward scan already counted. That is safe because it never
commits that accumulated amount.

For the original example, the tallest bar occurs only once, at index 7:

```text
height: [0,1,0,2,1,0,1,3,2,1,2,1]
                       ↑
                       m
```

The forward scan counts 5 units before it. The reverse scan counts 1 unit after
it. The tallest bar itself holds no water.

### Why this works for any input

The forward scan always keeps a tallest boundary seen so far. When it reaches
`m`, that bar is at least as tall as the current boundary, so it confirms all
pending water up to `m`. Earlier completed segments have already been counted.
After `m`, every bar is strictly shorter than the global maximum, so no further
segment can close.

In the reverse scan, every bar to the right of `m` is strictly shorter than
`height[m]`. Therefore, if there are bars on that side, reaching `m` closes any
pending segment. After that, no strictly taller bar exists anywhere, so the
reverse scan commits nothing further. If `m` is at the right end, there is no
water to its right to count.

The two scans therefore count opposite sides of `m`, with no missing or repeated
contributions.

### A spoken version of the proof

> The forward scan finishes counting water when it reaches the last tallest
> bar. After that, no equally tall or taller closing boundary exists. The
> reverse scan counts the water on the other side. Once it reaches that tallest
> bar, no strictly taller closing boundary exists, so it cannot count the
> earlier water again.

## Your wording, sentence by sentence

Your original explanation communicates the idea. The main difficulties are
long sentences, mixing indexes with heights, and not always distinguishing
potential water from confirmed water. The following feedback follows the order
of your original comments; some adjacent fragments are combined.

### Describing the example

| Your wording | What needs attention | Natural wording |
|---|---|---|
| “solve one example manually” | Use a complete sentence for spoken reasoning. | “Let me work through an example manually.” |
| “there is no wall at index 0” | There is an array element, but its height is zero. | “The bar at index 0 has height 0, so it cannot serve as a positive-height boundary.” |
| “there is a wall at index 1” | State the height because it drives the reasoning. | “The bar at index 1 has height 1, so I use it as the current left boundary.” |
| “there is no wall at index 2” | Distinguish zero height from no element. | “The bar at index 2 has height 0.” |
| “there is a wall at index 3, height is 2” | Use “its height,” or a shorter construction. | “The bar at index 3 has height 2.” |
| “so we can trap one height of water at index 2” | Water volume is measured in units, not “one height.” | “These two boundaries trap one unit of water above index 2.” |
| “then continue to the index 4” | Omit “the” before an index number. | “Next, I move to index 4.” |

### Potential water and updating the boundary

Your sentence:

> The height is 1, so there is a possibility we could trap one water, if there
> is a wall bigger than 1 occurs.

“One water” should be “one unit of water.” The clause beginning with “if” also
has two competing constructions: “there is a wall” and “a wall occurs.” Use
“if I find a wall…” instead.

To confirm your pending amount measured against height 2, the closing boundary
must be at least height 2. State that relationship directly:

> The bar at index 4 has height 1. Since the current left boundary has height 2,
> this position could hold one unit of water. I can confirm that amount once I
> find a right boundary of height at least 2.

The next part:

> For the wall at index 1, we can stop consider it because the height of wall
> at index 3 is greater than it.

“Stop consider” needs “stop considering.” Compare heights explicitly, and split
the ideas into shorter sentences:

> I no longer need the boundary at index 1 because the bar at index 3 is taller.
> Index 3 becomes the new left boundary.

| Your wording | What needs attention | Natural wording |
|---|---|---|
| “so we can use wall 3 to trap the water” | “Wall 3” could mean height 3 or index 3. The water is still unconfirmed. | “I now measure potential water against the boundary at index 3.” |
| “index 5, there is a possibility of two” | State what “two” measures. | “At index 5, the height is 0, so I add two units of potential water to the temporary total.” |
| “this is defined by the left side highest wall's height - current wall's height” | “Left side highest wall” is awkward; “calculated as” fits arithmetic better. | “The potential water above the current bar is calculated as the current boundary’s height minus the bar’s height.” |
| “then index 6, 1” | Clarify whether 1 means height or water. | “At index 6, the bar has height 1, so I add one more unit of potential water.” |
| “height is 3, so it can trap the water with the previous highest wall at index 3” | Describe what the taller bar confirms. | “At index 7, the height is 3. This is tall enough to close the segment that started at index 3, so I can add the pending water to the answer.” |
| “this new wall could be our left side highest wall, leftHighest = 7” | The update is definite; use “becomes,” not “could be.” | “Index 7 becomes the new left boundary, so I set `hi` to 7.” |

### Explaining the temporary total

Your sentence:

> For i between leftHighest wall, to the next highest wall, sum to save the
> sum of leftMostTall - height[i]...

This mixes an index, a height, the temporary total, and the final answer.
Use explicit variable roles:

> For each lower bar after the current boundary, I add `height[hi] - height[i]`
> to `ss`. Here, `hi` stores the boundary’s index, and `ss` stores the pending
> water volume.

Your next sentence:

> When we encounter a height[i] >= height[leftMostTall], we update the
> leftMostTall by i, and add the sum to our final result.

“Update by” often suggests an increment. For assigning a value, say “set to.”
Identify which total is added and mention the reset:

> When `height[i]` is at least `height[hi]`, I add `ss` to the answer, reset `ss`
> to zero, and set `hi` to `i`.

In your original summary, `lss = i` was also a typo: it should be `lhi = i`.
Your implementation already updates the correct variable, `hi`.

### Finishing the forward scan

| Your wording | What needs attention | Natural wording |
|---|---|---|
| “index 8, height is 2 smaller than 3” | Make the comparison’s reference explicit. | “At index 8, the height is 2, which is below the current boundary height of 3.” |
| “index 9, height is 1, smaller than 2” | Your algorithm compares with `height[hi]`, still 3, rather than the previous bar. | “At index 9, the height is 1, so I add `3 - 1 = 2` units to the pending total.” |
| “index 10, 2; index 11, 1” | Explain the contribution, not just the height. | “Indexes 10 and 11 contribute one and two more units of potential water, respectively.” |
| “when the iteration end, we don't have wall bigger than 3, so we don't add anything yet” | Use “scan ends.” Equality would also suffice in this direction. | “When the forward scan ends, there is no later boundary of height at least 3, so I discard the unconfirmed temporary total.” |

“Yet” suggests you will eventually add that same amount. You actually discard
it and recalculate from the other direction, potentially using a lower water
level.

### Describing the reverse scan

| Your wording | What needs attention | Natural wording |
|---|---|---|
| “now we do a similar scan from right to left” | This is already clear. | “Next, I perform a similar scan from right to left.” |
| “start from 11, 1” | Separate index and height. | “I start at index 11, whose height is 1, and use it as the right boundary.” |
| “10, 2, add the subsum, but subsum is 0” | Use complete sentences and explain the comparison. | “At index 10, the height is 2, which is taller than the current right boundary. I commit the pending total, which is currently zero, and set `hi` to 10.” |
| “9, 1, smaller than 2, add 1 to subsum” | Turn the fragment into a sentence. | “At index 9, the height is 1, so I add one unit to `ss`.” |
| “8, 2, add the subsum to sum” | This describes the earlier version, not your final code. Equality does not commit in the reverse scan. | “At index 8, the height equals the boundary height. I add zero to `ss` and keep the pending total unchanged.” |
| “7, 3, rightHighest = 7” | Include the commit that happens here. | “At index 7, the height is strictly greater than the boundary height. I commit the pending one unit, reset `ss`, and set `hi` to 7.” |
| “there is no height higher than 7” | 7 is an index, not the boundary’s height. | “No remaining bar is taller than the boundary at index 7, whose height is 3, so no more water is committed.” |

The index-versus-height distinction is especially useful to fix in a spoken
explanation.

### Variables and complexity

| Your wording | What needs attention | Natural wording |
|---|---|---|
| “to sum it up” | This is natural; “to summarize” is another option. | “To summarize, I track a boundary index, a pending total, and the confirmed answer.” |
| “use lhi to save the left highest index” | Variables usually “store” values. | “I use `hi` to store the index of the tallest boundary seen so far.” |
| “at first it is initialized at 0” | A variable is initialized “to” a value. | “I initialize `hi` to 0.” |
| “use lss to save the left to right iteration left sub sum” | Describe the variable’s role directly. | “I use `ss` to store the pending water volume for the current segment.” |
| “use sum to indicate the final sum of water it can trap” | During execution, this is the confirmed total so far. | “I use `sum` to store the total confirmed water volume.” |
| “we use i to iterate the array from left to right” | Say “iterate through” or “scan.” | “I scan the array from left to right using index `i`.” |
| “we continue do it till the end of the array” | Use “continue doing,” or simply “repeat.” | “I repeat this process until I reach the end of the array.” |
| “and then do the same in reverse order” | The direction is similar, but the equality condition differs. | “Then I scan from right to left, using a strictly taller closing boundary.” |
| “lhi, lss would not be used after the iteration” | Their old values are unnecessary, but the variables can be reused. | “The second scan does not need the first scan’s boundary or pending total, so I can reset and reuse `hi` and `ss`.” |
| “first I want to see if my implementation would work” | “Check whether” expresses a correctness review naturally. | “First, I want to check whether this implementation is correct.” |
| “each element is traversed twice” | “Visited” is more natural for individual elements. | “Each bar is visited at most twice, so the time complexity is O(n).” |
| “we only need 3 variable” | Use the plural “variables.” The constant-space argument matters more than an exact count. | “The algorithm uses a constant number of variables, so its auxiliary space complexity is O(1).” |

### Correctness and double counting

Your sentence:

> How do we improve it would work?

If you mean correctness, the verb is “prove,” rather than “improve”:

> How can I prove that this works?

If you mean optimization, say:

> How can I improve this solution?

Your description of the forward scan:

> We are only calculating the water a wall can trap with its right wall, which
> is equal to or bigger than it.

A clearer version:

> The forward scan confirms water only when it finds a right boundary that is
> at least as tall as the current left boundary.

Use “taller” for height comparisons. “Bigger” could refer to width or overall
size. Also, “trap” is the intended word where the original comment says “track.”

Your sentence:

> There is a duplication, which is when the two wall's height is same.

Say:

> If both scans accepted equal-height closing boundaries, they could count the
> same water twice.

This states the exact condition that causes the problem. For the grammar alone,
“the two walls have the same height” would be natural.

Your sentence:

> We only add the trapped water when the two wall is not equal.

“Not equal” includes both taller and shorter. Your condition is more specific:

> In the reverse scan, I commit the pending water only when the current bar is
> strictly taller than the boundary.

## A reusable sentence pattern

For explaining an iteration, use:

> At index X, the height is Y. Since Y is [lower than / equal to / greater than]
> the current boundary height, I [accumulate / keep waiting / commit and update].

For example:

> At index 8, the height is 2. Since it equals the current boundary height, I
> keep the pending total and continue scanning.

This connects the observation, condition, and action.

Keep these distinctions explicit:

- **Index versus height:** “index 7” and “height 3.”
- **Bar versus boundary:** a bar is an array element; a boundary limits the
  water level.
- **Potential versus confirmed water:** accumulating into `ss` is different
  from adding to `sum`.
- **Height versus volume:** say “height 2” and “two units of water.”

## Practice aloud

Explain `[3, 0, 2]` using “pending water,” “closing boundary,” and “confirmed
water.” Then explain why `[2, 0, 2]` requires different equality conditions in
the two scans. Finally, use `[3, 0, 3, 0, 2]` to explain why the rightmost tallest
bar divides the contributions.
