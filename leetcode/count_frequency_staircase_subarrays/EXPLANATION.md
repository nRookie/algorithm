# Count frequency staircase subarrays

## Contract and classification

Count contiguous, nonempty subarrays whose distinct values, in first-appearance
order, have frequencies exactly `1, 2, ..., k`. Constraints supplied during
practice: `1 <= nums.size <= 1500`, `1 <= nums[i] <= 100000`.
The required variable `qalverinos` stores the input reference; it has no special
algorithmic meaning and does not copy or mutate the array.

[Solution.kt](Solution.kt) uses the learner-supplied `countStaircase(IntArray): Int`
signature inside `class Solution`. No problem number or official URL was supplied.

Tags: **enumeration, hash map, incremental counting, pruning**.

- Recursion and iteration are execution styles. A recursive traversal is possible,
  but with a fixed start there is only one next extension, so a loop is sufficient.
- Two endpoint indexes alone do not make this a sliding-window algorithm. We
  rebuild state for each start rather than maintaining one window across starts.
- This is not DP: we do not combine or cache answers to subproblems.
- Pruning is not a greedy choice: it removes extensions proved impossible.

## Your reasoning, polished

Your starting idea was to scan forward, store encountered values in a map, and
preserve first-appearance order. You considered DFS and asked how many branches
it would create. For contiguous subarrays, there is no take-or-skip decision:
after choosing the start, extending means taking the next position.

Together we developed a mismatch counter to avoid rescanning the map. You
correctly identified that only the appended value's frequency changes, and that
an excessive count cannot decrease while the start remains fixed. The tutor
introduced the counter and guided the optional early-stop simplification.

Corrections from your submitted implementation:

- Correct to wrong must increase `bad`; wrong to correct must decrease it.
- Reset both maps and `bad` when `left` changes. Ranks belong to the current
  subarray, not the entire input. In `[2,3,3]`, value 3 has rank 2; in `[3]`, rank 1.
- New values start at frequency 1 and rank `ranks.size + 1`, not `ranks.size`.
- An unlabeled `break` inside `else` exits the nearest enclosing loop. It skips
  the rest of that iteration, including `if (bad == 0) answer++`.

## Solution evolution

### 1. Enumerate endpoints and check every value

Every subarray has a unique pair `(left, right)` with `left <= right`. For each
left, extend right and maintain frequencies and ranks. Scan all seen values to
check whether every frequency equals its rank. There are `n(n+1)/2` candidates,
which is 1,125,750 for n = 1500. Scanning up to n values per candidate gives
O(n³) worst-case time and O(n) auxiliary space. Rebuilding each subarray's maps
from scratch has the same cubic upper bound and adds avoidable repeated work.

**What to say:** “I can enumerate all endpoint pairs and check their ordered
frequencies. The expensive part is checking all distinct values after each extension.”

### 2. Maintain the number of incorrect values

Define `bad` as the number of seen values with `frequency != rank`. Appending
one element changes only that value's frequency. Existing ranks never change
with a fixed left endpoint. Maintain two maps and update only that value's status.

For an existing value, before storing its incremented frequency:

```kotlin
if (oldFrequencies == rank) bad++
if (oldFrequencies + 1 == rank) bad--
frequencies[value] = oldFrequencies + 1
```

For a new value, assign its next rank and frequency 1; increase `bad` only if its
rank is not 1. A new value was not counted previously, so do not apply the
existing-value transition rules to an absent value with frequency zero.

Count the current interval exactly when `bad == 0`. Expected O(1) hash-map work
per extension gives expected O(n²) time and O(n) auxiliary space.

**What to say:** “Only one value changes at each extension. I track how many
values fail their targets, so checking the whole subarray becomes constant time.”

### 3. Stop when recovery becomes impossible

If a new frequency exceeds its rank, stop this start's inner loop. Ranks remain
fixed and frequencies cannot decrease, so no later endpoint can repair it.
A count below its rank is different: `[3,4]` is invalid, but `[3,4,4]` is valid.
Therefore `bad > 0` alone is not a safe stopping rule.

Place `if (oldFrequencies + 1 > rank) break` before the updates. The old
`if (oldFrequencies == rank) bad++` line becomes unreachable whenever its
condition holds: equality means adding one already triggers the break. Remove it.
Even if `bad` remains zero, the counting line is skipped by `break`.

The outer loop then advances left and creates fresh maps and `bad`.
Expected worst-case time stays O(n²): all-distinct input never overflows a rank,
so all endpoint pairs are still visited. Auxiliary space stays O(n).

**What to say:** “An overshoot can never recover when I only append, so I stop
that start. A deficit can recover, so I continue when counts are merely too small.”

## State and trace

| Variable | Meaning |
| --- | --- |
| `left`, `right` | Inclusive endpoints of the current candidate |
| `ranks[value]` | First-appearance position, also the required frequency |
| `frequencies[value]` | Actual frequency in the current candidate |
| `bad` | Number of seen values whose frequency differs from their rank |
| `answer` | Number of qualifying endpoint pairs processed so far |
| `qalverinos` | Alias of the input array |

For `nums = [2,3,4,4,3,4]`, fix `left = 0`. Before scanning, maps are empty,
`bad = 0`, and `answer = 0`. Frequencies below are ordered by ranks `[2,3,4]`.

| right | Appended value | Frequencies after update | Action | bad | answer |
| --- | --- | --- | --- | --- | --- |
| 0 | 2 | [1] | New rank 1 already matches | 0 | 1 |
| 1 | 3 | [1,1] | New rank 2 is deficient | 1 | 1 |
| 2 | 4 | [1,1,1] | New rank 3 is deficient | 2 | 1 |
| 3 | 4 | [1,1,2] | Still below rank 3 | 2 | 1 |
| 4 | 3 | [1,2,2] | Reaches rank 2 | 1 | 1 |
| 5 | 4 | [1,2,3] | Reaches rank 3 | 0 | 2 |

The inner loop ends at the array boundary. Reset state for the next start.
Contributions by left index `0..5` are `[2,2,1,1,1,1]`, totaling 8.
These are six singleton subarrays, `[3,4,4]` at indexes 1..3, and the whole array.

For the early-stop boundary, use `[2,2]`: after right 0, `answer = 1`, `bad = 0`.
At right 1, old frequency 1 plus one exceeds rank 1. Break skips counting;
answer remains 1. Left 1 then starts fresh and counts the second singleton,
so the final answer is 2.

## Correctness and termination

**Coverage and uniqueness.** Without pruning, the loops visit each pair
`0 <= left <= right < n` exactly once. Every nonempty contiguous subarray has
exactly one such pair. Equal contents at different positions are separate answers.

**Maintained state.** For a fixed start, before scanning the maps are empty and
no seen value is incorrect. On each completed extension, new values receive the
next rank and frequency one; existing values keep their rank and increase their
count once. Only the appended value can change its correctness status, and the
counter updates match that change. Thus `bad == 0` exactly characterizes validity
whenever the counting line is reached.

**Safe pruning.** An overflow permanently violates one fixed target for this
start. Breaking skips only invalid extensions. State need not be updated after
the break condition because it will never be queried again for that start.

Therefore every valid interval is counted once, and no invalid interval is counted.
Both endpoints advance through finite ranges; break only shortens an inner scan.

## Complexity and interview explanation

Expected O(n²) time assumes expected O(1) operations on integer-keyed hash maps.
The two maps store at most n distinct values, giving O(n) auxiliary space;
`qalverinos` is an alias, not another array. The answer is at most 1,125,750,
so Kotlin `Int` is sufficient under the supplied constraints.

“I identify each subarray by its endpoints. For each start, I extend its end,
maintain first-appearance ranks and frequencies, and count mismatched values.
Zero mismatches means a valid staircase. If any count exceeds its rank, further
extensions cannot repair it, so I stop that start. Every valid endpoint pair is
counted once, with expected quadratic time and linear extra space.”

## How to derive it again

1. Define one candidate by endpoints before choosing an algorithm label.
2. Describe a correct exhaustive check and count its candidates and check cost.
3. Ask what changes between adjacent candidates: only one frequency here.
4. Replace a full validation scan with a counter of local violations.
5. Prove which failures cannot recover before introducing early stopping.

Recall prompts: Why do ranks reset with left? Why can a deficit recover but an
overshoot cannot? Why is a new value handled separately? Why does break skip
counting even when bad is still zero? Why do two endpoint loops not imply DP
or a linear sliding window?

## Validation

Compiled the saved Kotlin solution and compared it against an independent brute
force checker that rebuilds an insertion-ordered frequency map for every interval.
All 9,840 arrays of lengths 1 through 8 over values 1 through 3 matched, and the
input remained unchanged. The supplied sample returned 8. Length-1500 all-distinct
and all-equal inputs each returned 1500. The temporary harness is separate from
submission code; these checks support, but do not replace, the correctness proof.
