# 134. Gas Station

## Problem and movement meaning

Given equal-length, nonempty arrays `gas` and `cost`, start with an empty car
at a station and travel one full circle clockwise. The capacity is unlimited.
Return a valid starting index, or `-1` if no start works. The problem guarantees
that a solution, if present, is unique; the algorithm does not need uniqueness
to find a valid start. The inputs are not modified.

At station `i`, collect `gas[i]`, then pay `cost[i]` for the trip from `i`
to the next station. At the last index, the next station is `0`.

```text
change[i] = gas[i] - cost[i]
leftOver after attempting the trip = leftOver before collecting + change[i]
```

Exactly zero is allowed. A negative calculated `leftOver` means the trip
cannot be completed; it is a failure calculation, not an actual negative
amount carried to the next station.

## Your implementation

[134.kt](134.kt) preserves your supplied algorithm and variable names. Only
formatting and unused commented-out prefix code were cleaned up.

```kotlin
class Solution {
    fun canCompleteCircuit(gas: IntArray, cost: IntArray): Int {
        var total = 0
        val n = gas.size
        var leftOver = 0
        val change = IntArray(n) { 0 }
        for (i in cost.indices) {
            change[i] = gas[i] - cost[i]
        }

        var start = 0
        for (i in 0 until n) {
            total += change[i]
            leftOver += change[i]
            if (leftOver < 0) {
                start = i + 1
                leftOver = 0
            }
        }

        if (total < 0) {
            return -1
        } else {
            return start
        }
    }
}
```

| Name | Meaning |
| --- | --- |
| `n` | Number of stations |
| `change[i]` | Net gas change for the trip leaving station `i` |
| `start` | Current candidate; “final start” means its value when the loop finishes |
| `leftOver` | Combined change for the current attempt; reset to `0` after failure |
| `total` | Combined change over all processed stations; never reset |

Before processing `i`, `leftOver` is the sum of changes from `start` through
`i - 1`. After adding `change[i]`, it includes `i` as well. If that sum is
negative, the attempt fails on the trip `i → i + 1` and a fresh attempt begins
at the next station with `leftOver = 0`.

## Solution evolution

### 1. Your initial reasoning: simulate every start

Your initial comments correctly identified the empty initial car, the update
`gas[i] - cost[i]`, and the requirement that gas never become negative during
the drive. Try each possible start, checking up to `n` trips and stopping at
the first failure. Modular indexing handles the circular route.

This takes O(n²) worst-case time and O(1) auxiliary space. Your alternative
of duplicating the arrays simplifies indexing but uses O(n) auxiliary space
without removing the repeated simulations.

What to say: “I can simulate one circle from each station, but different
starting attempts repeatedly inspect the same trips.”

### 2. Reuse a failure instead of retrying every start

The next observation we developed together was: when an attempt fails on the
trip leaving `i`, every start from its current `start` through `i` can be
discarded. Set `start = i + 1` and reset `leftOver = 0`.

Separately, accumulate `total` without resetting. A negative total rules out
every possible start. A nonnegative total alone does not validate an arbitrary
start; the failure-skipping rule is what chooses a suitable candidate.

Your resulting implementation precomputes `change`, then scans it once.
Both passes are O(n), and storing `change` uses O(n) auxiliary space.

What to say: “A failed attempt rules out a whole consecutive group of starts,
so I move directly to the next candidate. I keep a separate total to check
whether the whole route has enough gas.”

### 3. Optional space improvement

This is a further storage improvement, not a replacement of your saved code.
Compute the change inside the scanning loop instead of storing all changes:

```kotlin
val change = gas[i] - cost[i]
total += change
leftOver += change
```

The same reset and return rules apply. This keeps O(n) time and reduces
auxiliary space to O(1). No prefix array or DP table is necessary.

## Complete trace: negative changes separated by a positive change

This is the example you used to question whether positive changes invalidate
the proof. Both original arrays are shown so each trip is fully specified.

```text
station:  0  1  2  3
gas:      1  4  1  8
cost:     2  1  6  1
change:  -1  3 -5  7
```

The first loop constructs `change = [-1, 3, -5, 7]`.
Before the second loop: `start = 0`, `leftOver = 0`, `total = 0`.

| i / attempted trip | change[i] | leftOver before | leftOver after addition | total after addition | Action | start after | leftOver after action |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 / `0 → 1` | -1 | 0 | -1 | -1 | Fail; reset | 1 | 0 |
| 1 / `1 → 2` | 3 | 0 | 3 | 2 | Keep candidate | 1 | 3 |
| 2 / `2 → 3` | -5 | 3 | -2 | -3 | Fail; reset | 3 | 0 |
| 3 / `3 → 0` | 7 | 0 | 7 | 4 | Keep candidate | 3 | 7 |

The loop finishes with `start = 3`, `leftOver = 7`, `total = 4`.
The return value is `3`.

The implementation does not run another loop. To illustrate the circular
drive from its answer, simulate these trips separately:

| Trip from start 3 | Gas remaining before collecting | Collect | Pay | Gas remaining after trip |
| --- | --- | --- | --- | --- |
| `3 → 0` | 0 | 8 | 1 | 7 |
| `0 → 1` | 7 | 1 | 2 | 6 |
| `1 → 2` | 6 | 4 | 1 | 9 |
| `2 → 3` | 9 | 1 | 6 | 4 |

Returning to station `3` finishes the circle. Do not collect its gas a second
time. “Wrapping” means the ordinary trip from the last station to station `0`.

## General correctness proof without prefix sums

This proof uses combined sums of `change`, not particular numbers. It assumes
an empty initial car and unlimited capacity. The code needs no `pre` array.

### 1. Why a failure lets us skip starts

Suppose an attempt from `start` first fails on the trip leaving station `i`.
Pick any station `k` between that `start` and `i`, inclusive.

The attempt successfully reached `k`, so it arrived with nonnegative gas,
before collecting `gas[k]`. Starting directly at `k` would give us zero gas.
From there, both attempts collect the same gas and pay the same costs.
Starting directly at `k` therefore never has more gas than the failed attempt.
It must fail by the same trip, possibly earlier.

Thus every start from the old `start` through `i` is invalid. Moving to
`i + 1` does not skip a possible answer. Resetting `leftOver` to zero represents
a fresh attempt; the negative result is not carried into it.

### 2. Why a negative total means no solution

Every full circle includes each station's change exactly once, whichever
station we start at. Starting empty, the final gas would be `total`.
If `total < 0`, completing all trips while keeping nonnegative gas is impossible.

For the rest of the proof, assume `total >= 0`.

### 3. The final candidate can reach station 0

The final `start` is the candidate remaining when the loop finishes. From
that index through `n - 1`, its accumulated `leftOver` never becomes negative;
otherwise the loop would replace the candidate again.

Therefore all trips in this portion work, including the trip from the last
station to station `0`.

The final `start` is an actual index when `total >= 0`. If a reset made it
`n`, all stations would be partitioned into failed attempts, each with a
negative combined change. Their sum would make `total < 0`, a contradiction.

If the final `start` is `0`, reaching station `0` already completes the circle.
Otherwise, we must prove that the return portion also works.

### 4. Every remaining portion before the final start has negative change

All stations before the final `start` are partitioned into consecutive failed
attempts. Each such section has a negative combined change: that is precisely
why the code reset after processing its last station.

```text
[failed attempt] [failed attempt] ... [final start ... n - 1]
```

Choose any station `k < final start`. It belongs to one of those sections.
Split that failed attempt into two parts:

```text
[stations before k | stations from k through the failed trip]
```

The first part has a nonnegative combined change because the attempt
successfully reached `k`. The whole failed section has a negative change.
Therefore:

```text
change from k through that failure
= whole failed section's change - change before reaching k
= a negative number - a nonnegative number
< 0
```

The subtraction is simply a partition of a sum: whole = first part + second
part, so second part = whole - first part. If `k` is the section's starting
station, the first part is empty and its sum is zero.

From the end of that section to the final `start`, every later section is
another failed attempt with a negative combined change. Thus:

```text
change from station k through station final start - 1
= negative remainder of k's section
  + negative sums of any later failed sections
< 0
```

Positive individual changes can occur anywhere inside these sections. We use
the sums of failed sections, not a claim that every station's change is negative.
At the final `start` itself, no trips remain and the remaining change is zero.

### 5. Why subtracting the remaining change proves the return portion works

Imagine continuing the drive after reaching station `0`. On arrival at an
earlier station `k`, before collecting its gas, the full circle splits into:

```text
Completed stations: [start ... n - 1] and [0 ... k - 1]
Remaining stations: [k ... start - 1]
```

Each station appears exactly once in those two portions. Consequently:

```text
change of completed trips + change of remaining trips = total
```

Starting empty, the completed trips' combined change equals the gas remaining
at that moment. Therefore:

```text
gas remaining at k = total - remaining change
```

We subtract the remaining portion to extract the completed portion from the
whole. Step 4 proved that the remaining change is negative for `k < start`.
Since `total >= 0`:

```text
gas remaining at k >= total >= 0
```

This holds at every station on the return portion. Each trip therefore reaches
its destination with nonnegative gas. At the final `start`, the remaining
portion is empty, so the completed circle leaves exactly `total` gas.

**Important distinction:** `leftOver` at the end of the actual loop contains
only the changes from `start` through `n - 1`. Gas remaining later in the
imagined drive additionally includes changes from `0` through `k - 1`.
The implementation does not update `leftOver` after the loop; that continuation
is used only to prove its returned candidate is valid.

## Complexity and termination

Your code makes two finite passes of length `n`, so its time is O(n). It
allocates an `IntArray(n)` for `change`, so its auxiliary space is O(n).
Computing each change directly in the second loop would give O(1) auxiliary
space. The original arrays are not copied or modified by your saved version.

## Verification

The saved Kotlin submission compiled and passed 9 example and boundary cases:
the two standard examples, both examples discussed here, single-station cases
with equal/surplus/insufficient gas, a zero-total route valid from station 0,
and an impossible route that resets `start` to `n`.

It also passed 3,905 exhaustive small cases: all change arrays of lengths 1–5
with values from -2 through 2. An independent checker simulated every possible
start for a full circle. The result had to be a valid simulated start, or `-1`
exactly when none worked. This check also includes cases with multiple valid
starts, beyond the problem's uniqueness promise. These are observed checks;
the general correctness argument is the proof above.

## Interview explanation and recall

For the later discussion of a valid DP formulation, see the separate
[minimum-required-gas DP implementation and explanation](dp/EXPLANATION.md).
Its full table uses O(n²) time and space; its state differs from the undefined
DP sketch in the original attempt.

> “I track the gas remaining for one candidate start and the total change for
> the whole route. If a candidate fails, every start reached during that attempt
> would have no more gas, so I skip them and reset at the next station. A negative
> total makes the route impossible. Otherwise, the final candidate survives
> through the array's end. Every remaining section before it has negative net
> change, so gas remaining on the return portion is at least the nonnegative
> total. My stored-change version takes O(n) time and O(n) extra space; computing
> each change directly would reduce extra space to O(1).”

Reconstruct the proof in small steps:

1. Why does reaching `k` imply nonnegative gas before collecting `gas[k]`?
2. Why does starting empty at `k` lose any advantage of the earlier attempt?
3. Why is the remainder of a failed section negative even with positive changes
   inside it?
4. Why does completed change plus remaining change equal `total`?
5. What does `leftOver` include when the actual loop ends, versus gas remaining
   later in the imagined drive?

## Retrospective: where your original reasoning became unreliable

This reviews the comments and code you supplied. They show the steps you wrote
down; they cannot establish every thought you had privately. The observations
below are about specific reasoning steps, not a judgment about your ability.

### What you already had right

You manually simulated the standard example correctly. You identified an
empty initial car, the update `gas[i] - cost[i]`, the need for nonnegative gas
after every trip, and circular indexing. Your exhaustive baseline was correct,
and you correctly recognized its O(n²) repeated work. Your question “is there
any information we can get from the previous outer loop?” was exactly the
right direction for an optimization.

You also computed `pre` and `min_pre` correctly in the active prefix code.
That code was already O(n) time. The missing piece was a correct acceptance
rule, not finding a way to compute sums faster.

### 1. The central error: replacing every-trip feasibility with an endpoint sum

Your original decision rule was:

```kotlin
val leftPath = pre[n] - pre[i]
if (leftover[i] >= 0 && leftPath >= abs(min_pre)) {
    return i
}
```

Here, the original array `leftover[i]` means one station's `gas[i] - cost[i]`.
It is not the accumulated gas remaining from a candidate. `leftPath` is the
combined change from stations `i` through `n - 1`, not the minimum gas remaining
while driving through those stations.

The first condition checks the first trip. The second compares an endpoint
sum with a deficit. Neither checks whether an intermediate trip before the
end of the array fails. A large positive change later cannot rescue a car
that cannot reach that station.

Here is a small counterexample with a unique valid start:

```text
station:        0   1   2
gas:            3   1   5
cost:           1   4   1
gas-cost:       2  -3   4
pre:           [0, 2, -1, 3]
min_pre:       -1
```

Your rule accepts station 0:

```text
leftover[0] = 2 >= 0
leftPath = pre[3] - pre[0] = 3 >= abs(-1)
```

But the actual attempt fails:

```text
0 → 1: gas remaining = 0 + 3 - 1 = 2
1 → 2: calculated remaining = 2 + 1 - 4 = -1
```

The valid start is station 2. Its trip changes are `4, 2, -3`, giving remaining
gas `4, 6, 3`. The comparison above was evaluated directly against a circular
simulation; it is a counterexample to your acceptance rule.

Your own last comment, `[-1,-1,-1,1,-4,-1,68]`, exposes the same problem:
your predicate accepts index 3 because its suffix has a large surplus, but
the attempt's first two changes are `1, -4`, so it fails before reaching 68.

### 2. Why your main example hid that mistake

Your main example had:

```text
station:  0  1  2  3  4
gas:      1  2  3  4  5
cost:     3  4  5  1  2
change:  -2 -2 -2  3  3
pre:     [0, -2, -4, -6, -3, 0]
total:   0
```

Because `pre[0] = 0`, `min_pre <= 0`. With `total = 0`, your condition becomes:

```text
0 - pre[i] >= -min_pre
therefore pre[i] <= min_pre
```

Since `min_pre` is the minimum, this forces `pre[i] == min_pre`. That selects
the correct minimum boundary in this example. With a positive total, however,
the condition can also accept a boundary above the minimum, including an
invalid start like index 0 in the counterexample.

The testing lesson is to vary the property supporting a successful example:
here, try both zero and positive totals, with an early deficit before a later
surplus. Repeating the zero-total example cannot expose this particular flaw.

### 3. Prefix/suffix sums were usable; the query needed a precise meaning

Your comments moved between a single trip's change, a cumulative change from
station 0, a suffix total, and actual gas remaining. The label `leftover` was
used both for a scalar accumulated amount and for the array of individual
changes. Some suffix values also changed while you were exploring the idea.
Those shifts made it harder to see which condition was still unproved.

For a candidate at index `i`, an intermediate boundary `j` before wrapping
has accumulated gas `pre[j] - pre[i]`. Every such difference must be
nonnegative; checking only `j = n` loses the intermediate condition. A suffix
of totals is not a suffix of minimum cumulative values.

One valid prefix approach is to reject a negative total, then choose an index
whose prefix is smallest among the possible starting boundaries. The prefix
idea did not need to be abandoned. The constructive fact that a minimum
boundary works was the missing justification. The greedy reset loop tracks
that boundary as it scans, so it needs no prefix array.

Useful definitions before coding would have been:

```text
change[i]: one trip's gas minus cost
pre[k]: combined change for stations 0 through k - 1
leftOver: accumulated change from the current candidate, at a stated moment
```

Each condition then needs to answer a particular question: first-trip
feasibility, all intermediate trips, the wrapped portion, or the whole-route
gas budget. These questions cannot be replaced by one vaguely named sum.

### 4. Why the better transition was hard to find

Your written process recognized repeated scans, then tried to summarize the
entire route with prefix/suffix arrays and later a two-dimensional DP table.
The key inference from a failed simulation had not yet been established:

```text
The old attempt reached an intermediate station with nonnegative gas.
A fresh attempt there would start with zero.
Therefore that fresh attempt cannot do better on the same remaining trips.
```

That comparison turns “start failed” into “this whole interval of starts
failed.” Without it, advancing to `i + 1` would be an unsupported guess.
With it, repeated simulations can be replaced by one scan.

The useful optimization question is therefore not only “what sum can I save?”
but also “what candidates can the work I just did rule out?” This is a
problem-specific comparison of resources, not a rule that every failure in
every search permits skipping candidates.

### 5. The DP detour did not repair the missing condition

The late comments propose a longest increasing subarray and `dp[i][j]`, but
the problem does not require increasing changes or positive totals at every
global prefix. It requires nonnegative cumulative gas relative to a chosen
start. A valid drive can include negative individual changes.

The proposed `dp[i][j]` did not yet have a consistent stored-answer definition
and transition tied to that requirement. `pre[j] > 0` still refers to the sum
from station 0, not feasibility from candidate `i`.

There are also separate implementation issues in that sketch: it sits after
an unconditional `return -1`, so it cannot affect the function's result. If
moved into reachable code, its `else` branch does not advance `j`; at initial
`j = 0`, `pre[0] > 0` is false and it would repeat forever. These are secondary
to the undefined recurrence. Adding more states cannot repair a condition
that has not been justified.

### 6. What the coaching made harder

The explanations also contributed to the confusion. They switched among
“tank,” “balance,” and `leftover`, repeatedly reused one convenient example,
and did not always restate the actual input data. They also blurred gas
remaining at the end of the loop with gas remaining during a hypothetical
continuation around the circle. Your questions about those distinctions were
necessary checks, not evidence that you lacked the reasoning ability.

Keep one term, state the source and destination of every trip, and explicitly
label the point before collecting gas. For a general proof, use a general
partition of the sum; examples illustrate it but do not substitute for it.

### A concrete process to use next time

1. Keep the correct baseline and state the exact success condition: every
   trip must leave nonnegative gas.
2. Freeze each quantity's meaning, range, and point in time before comparing it.
3. For an acceptance rule, try to break it with an early shortage and late
   surplus. Compare its result with the baseline before adding DP or more arrays.
4. For repeated failed attempts, compare the old and fresh candidates at the
   same station and prove which candidates can be discarded.
5. Separate the gas budget for the whole route from gas for one attempt.
   Account for the return portion before declaring the candidate valid.

Reusable facts are recorded in the
[concepts cheatsheet](../../study-notes/algorithm-concepts-cheatsheet.md).
Process reminders are integrated into the
[solving workflow](../../study-notes/algorithm-solving-workflow.md).

## Follow-up discussion: revisiting the greedy proof (2026-10-04)

You returned to this proof because the earlier explanation was still unclear.
You said that introducing prefixes seemed to make the original problem more
complex. Your follow-up questions separated several gaps in understanding:

1. What does “wrapping” mean, and why does it matter for Gas Station?
2. Why can a failure at `i` eliminate every start from `start` through `i`?
3. Why can we use a value from a previous failed trip to reason about a fresh
   start?
4. Even after eliminating those starts, why does the final candidate actually
   complete the circle?

After the failed-section explanation below, you said “I see” and asked to
append it so you could remember that you had revisited these questions. This
records that discussion; it does not assume the proof is permanently settled.

### Wrapping means continuing at station 0 without resetting the gas

Starting at `s`, the circular order is:

```text
s → … → n - 1 → 0 → … → s - 1 → back to s
                ↑ wrapping
```

Reaching the array's end is only part of the trip when `s > 0`. The gas earned
before wrapping must also let us complete the earlier stations. Prefix sums
can express this, but they are not required for the following proof.

### A previous failed trip is evidence, not fuel carried into a new attempt

Suppose an attempt from `start` first fails on the trip leaving station `i`.
At any intermediate station `j`, it arrived with some gas `C >= 0`, before
collecting that station's gas. A fresh start at `j` instead begins with zero.
Both attempts face the same fixed changes from `j` through `i`.

```text
Previous attempt's calculated balance at i = C + changes from j through i < 0
Fresh attempt's calculated balance at i    =     changes from j through i
                                          = previous balance - C < 0
```

For example, if the previous attempt arrived at `j` with `3` gas and failed
at `i` with calculated balance `-1`, a fresh attempt's balance through the
same segment would be `-4`. It fails at `i` or earlier. Negative balances
describe hypothetical failure calculations; the actual car cannot continue
past its first unaffordable trip.

Thus every start in `[start, i]` is impossible. `i + 1` is the next candidate
not yet eliminated, not a candidate already guaranteed to work. The code
resets `leftOver` to zero when testing it.

### Why the last candidate succeeds when total is nonnegative

The resets partition the array into failed sections followed by one final
section:

```text
[failed section A] [failed section B] … [final section]
                                       ↑ final start
```

Each failed section, when tested from zero, has nonnegative running balances
until its last trip. Its final balance is negative; that is what triggered
the reset. Write its total as `-d`, where `d > 0`.

The final section never triggers a reset, so the candidate can traverse it
from zero. Let its final accumulated gas be `F`, the loop's final `leftOver`.
If the failed sections have deficits `d₁, d₂, …`, then:

```text
total = F - d₁ - d₂ - …
total >= 0 therefore implies F >= d₁ + d₂ + …
```

After wrapping, we enter the failed sections with `F` gas. Within each such
section, every balance relative to its beginning is nonnegative until its
last trip, where it becomes `-d`. Therefore entering with at least `d` gas
is enough to survive every trip in that section.

We have enough for all deficits together: after paying the first section's
deficit, we still have enough for all later sections, and so on. This proves
every intermediate trip after wrapping is feasible, not just the endpoint.

If there are no failed sections, `start = 0` and the final section itself is
the whole circle. If every section failed, their negative totals would sum
to a negative `total`; therefore that cannot happen when `total >= 0`.

### Small example of the whole argument

```text
station:          0   1 | 2   3 | 4
gas:              3   1 | 2   1 | 5
cost:             1   4 | 1   4 | 1
change:          +2  -3 |+1  -3 |+4
section totals:     -1 |    -2 |+4
                                ↑ final start = 4
```

The scan fails at stations `1` and `3`, leaving `start = 4`, `leftOver = 4`,
and `total = 1`. The final section provides `4` gas, enough to cover the
earlier section deficits `1 + 2 = 3`.

| Station whose trip is taken | 4 | 0 | 1 | 2 | 3 |
| --- | --- | --- | --- | --- | --- |
| Net change | +4 | +2 | -3 | +1 | -3 |
| Gas remaining after trip | 4 | 6 | 3 | 4 | 1 |

The trip leaving station `4` wraps to `0`; the trip leaving station `3`
returns to the starting station `4` and finishes the circle.

### The distinction to recall next time

The elimination argument proves that we do not skip a possible answer.
The failed-section argument proves that the final candidate completes the
circle when `total >= 0`. Both are needed. If `total < 0`, no start can work
because every full circle has that same negative total change.

This comparison relies on fixed additive changes and unlimited capacity:
carried gas is not discarded. Rehearse the proof by asking: “Why is there
enough gas at the beginning of each failed section, and why does that also
cover every trip inside it?”
