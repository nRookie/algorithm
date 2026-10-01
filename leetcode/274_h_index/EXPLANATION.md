# 274. H-Index

## Contract

Given nonnegative citation counts, return the largest integer h such that at
least h papers each have at least h citations. Let n be the number of papers.
The answer is between 0 and n, inclusive. Five papers permit an h-index of
at most 5, not necessarily exactly 5.

Example: `[3,0,6,1,5]` has answer 3: the papers with 3, 6, and 5 citations
qualify. Four papers do not each have at least four citations.

## Solution evolution

### 1. Your starting solution: sort descending

You proposed sorting `[3,0,6,1,5]` into `[6,5,3,1,0]`. At index `current`,
there are `current + 1` papers in the prefix, and `citations[current]` is
the smallest citation count in that prefix. Therefore:

```text
current + 1 <= citations[current]
```

means that this prefix supplies enough papers for candidate `h = current + 1`.
Once the condition fails, later candidates also fail: the required count rises
while the sorted citation count cannot rise. Sorting ensures no other set of
h papers can qualify if even the h highest-cited papers fail.

Your original implementation, with formatting normalized:

```kotlin
class Solution {
    fun hIndex(citations: IntArray): Int {
        citations.sortDescending()
        val n = citations.size
        var cited = 0
        for (current in 0 until n) {
            if (current + 1 <= citations[current]) {
                cited = current + 1
            } else {
                break
            }
        }
        return cited
    }
}
```

| current | Citation count | Candidate h | Result |
| --- | --- | --- | --- |
| 0 | 6 | 1 | Valid; cited = 1 |
| 1 | 5 | 2 | Valid; cited = 2 |
| 2 | 3 | 3 | Valid; cited = 3 |
| 3 | 1 | 4 | Invalid; stop and return 3 |

The loop may also exhaust the array with every candidate valid, as in
`[3,3,3]`; the implementation correctly returns n. All-zero input returns 0.
Time is O(n log n), dominated by sorting. The scan uses O(1) extra space;
total auxiliary space also includes the library sort's implementation-specific
workspace. Sorting modifies the input.

What to say:

> “Sorting lets me validate an entire prefix using its smallest citation count.
> But I only need counts of papers meeting each threshold, not their full order.”

### 2. Bound the answer before choosing storage

During guided practice, you identified that h cannot exceed n: there cannot
be more qualifying papers than the total number of papers. Consequently,
100 citations and 5 citations are equivalent when there are five papers.
Both satisfy every possible candidate threshold.

This justifies grouping all citation counts at least n into one bucket.
It avoids allocating an array based on the largest citation value.

### 3. Count papers once instead of sorting them

The guided hint introduced a frequency table. We then established:

- `count[c]`, for `0 <= c < n`: papers with exactly c citations.
- `count[n]`: papers with at least n citations.

These are counts of papers, not sums of citations. Initialize all n + 1
buckets to zero. For each citation count x, increment `count[x]` if x < n;
otherwise increment `count[n]`. Each paper enters exactly one bucket.

A highly cited paper satisfies many thresholds, but we do not increment all
those buckets. We will combine the disjoint bucket counts during the scan.

### 4. Turn exact counts into “at least” counts

To check h = 3, we need papers with at least 3 citations, not just exactly 3.
You established that if two papers have at least 4 citations and one has
exactly 3, adding those counts gives three papers with at least 3 citations.

Lowering the threshold adds one new group. Keep a running total `papers`:

```text
papers += count[h]
if papers >= h, return h
```

The condition uses `papers`, not `count[h]`. For the example, `count[3] = 1`
but three papers meet the threshold. This is a suffix sum computed as we scan;
we do not need a separate suffix-sum array.

You explained why descending order matters: after higher candidates have
failed, the first passing candidate is the maximum. Checking 2 and 1 after
3 passes cannot produce a larger answer.

What to say:

> “There are only n + 1 possible answers. I count papers by citation count,
> capping the bucket index at n. Scanning downward accumulates how many papers
> meet each threshold. The first threshold with enough papers is the answer.”

| Approach | Time | Extra storage | Input modified? |
| --- | --- | --- | --- |
| Descending sort and scan | O(n log n) | O(1) scan state, plus sort workspace | Yes |
| Capped buckets and descending total | O(n) | O(n) | No |

## Your state definitions, refined

Your explanation established bucket construction, descending candidate order,
a cumulative paper count, and returning the first valid candidate. The precise
definitions are:

| Variable | Meaning |
| --- | --- |
| n | Total number of papers; maximum possible h-index |
| count | Frequencies of capped citation counts, including bucket 0 |
| h | Candidate h-index currently being checked |
| papers | After the update at h, number of papers with at least h citations |
| H | In your version, the answer saved before breaking out of the loop |

An update is an operation; an invariant is a statement that stays true.
`papers += count[h]` is the update, not itself the invariant.

**Precise loop invariant:** Before the update, `papers` equals the sum of
buckets h + 1 through n. After the update, it equals the sum of buckets h
through n, which counts exactly the papers with at least h citations.

Correction to the earlier coaching wording: before the first update at h = n,
`papers = 0` does not necessarily count papers with more than n citations;
those papers are inside `count[n]` and have not been added yet. The bucket-sum
definition above is valid even at that first iteration. After the update,
the “at least h” interpretation always holds.

## Final implementation

Your submitted bucket implementation is correct:

```kotlin
class Solution {
    fun hIndex(citations: IntArray): Int {
        var H = 0
        val n = citations.size
        val count = IntArray(n + 1) { 0 }
        for (x in citations) {
            if (x < n) {
                count[x]++
            } else {
                count[n]++
            }
        }
        var papers = 0
        for (h in n downTo 0) {
            papers += count[h]
            if (papers >= h) {
                H = h
                break
            }
        }
        return H
    }
}
```

Your concern about h's scope was reasonable: h is local to the loop. Saving
it in H before `break` works. Alternatively, `return h` inside the loop exits
the whole function immediately, so H is unnecessary. This is a simplification,
not an asymptotic improvement. `IntArray(n + 1)` already initializes to zeros.

```kotlin
class Solution {
    fun hIndex(citations: IntArray): Int {
        val n = citations.size
        val count = IntArray(n + 1)
        for (x in citations) {
            if (x < n) count[x]++ else count[n]++
        }

        var papers = 0
        for (h in n downTo 0) {
            papers += count[h]
            if (papers >= h) return h
        }
        return 0
    }
}
```

The final return satisfies Kotlin's return requirement. Mathematically, the
loop always returns by h = 0 for valid nonnegative citation counts.

## Complete trace of the bucket solution

Input: `[3,0,6,1,5]`; n = 5. Bucket positions are `[0,1,2,3,4,5]`.

| Input processed | Bucket incremented | count afterward |
| --- | --- | --- |
| None | None | `[0,0,0,0,0,0]` |
| 3 | 3 | `[0,0,0,1,0,0]` |
| 0 | 0 | `[1,0,0,1,0,0]` |
| 6 | 5 | `[1,0,0,1,0,1]` |
| 1 | 1 | `[1,1,0,1,0,1]` |
| 5 | 5 | `[1,1,0,1,0,2]` |

Initialize papers = 0.

| h | papers before | Added count[h] | papers after | Decision |
| --- | --- | --- | --- | --- |
| 5 | 0 | 2 | 2 | 2 < 5; continue |
| 4 | 2 | 0 | 2 | 2 < 4; continue |
| 3 | 2 | 1 | 3 | 3 >= 3; return 3 |

In your H version, the last row sets H = 3, breaks, then returns H.

## Correctness, termination, and complexity

Each paper enters exactly one bucket. Capping at n preserves all comparisons
against possible candidate values 0 through n. Adding bucket h to the already
accumulated higher buckets therefore counts exactly the papers meeting h.

The condition `papers >= h` is precisely the definition of a valid candidate.
All larger candidates have already failed, so the first success is maximal.
The loop decreases h each time. At h = 0, all n papers have been counted,
and n >= 0 guarantees success. The code also handles an empty array if allowed.

Bucket initialization, building, and scanning each take O(n) time; their costs
add rather than multiply. The array of n + 1 counts takes O(n) extra space.

**Time-optimal for arbitrary unsorted input:** On an all-zero input, an exact
algorithm must inspect every entry. Any unread entry could instead be 1,
changing the answer from 0 to 1. This gives an Omega(n) worst-case lower bound
in the usual array-access model. The bucket algorithm meets it with O(n) time.
This does not claim that O(n) extra space is optimal. Further space-saving
approaches were outside the requested discussion.

Boundary cases to check:

| Input | Answer | What it checks |
| --- | --- | --- |
| `[0]` | 0 | Bucket zero and final candidate |
| `[100]` | 1 | Capping a large citation count |
| `[0,0,0]` | 0 | All candidates above zero fail |
| `[3,3,3]` | 3 | Immediate success at n |
| `[4,0,6,1,5]` | 3 | Answer need not appear as an exact citation count |

## Interview rehearsal

> “My initial approach sorts descending and checks whether the first h papers
> each have at least h citations. That takes O(n log n). But h cannot exceed
> the total number of papers, and I only need threshold counts. I build n + 1
> buckets, putting all counts at least n into the last bucket. Then I scan h
> downward, accumulating papers with at least h citations. The first time
> papers is at least h, I return h. This takes O(n) time and O(n) extra space
> without modifying the input.”

Practice reconstructing why capping is safe, why the condition uses the running
total instead of one bucket, and why the first success is the maximum.

For reusable English sentence patterns and polished versions of your wording,
see [Algorithm interview phrases](../../study-notes/algorithm-interview-phrases.md).
