# Candy: why the second scan preserves the first scan's constraints

This note records the preservation proof developed in the discussion. It
explains why the two scans satisfy the neighbor constraints; a proof of minimum
total candies is a separate question not developed here yet.

## The implementation being proved

Initialize every entry of `dp` to 1. The two scans are:

```kotlin
for (i in 1 until n) {
    if (ratings[i] > ratings[i - 1]) {
        dp[i] = maxOf(dp[i], dp[i - 1] + 1)
    }
}
for (i in n - 2 downTo 0) {
    if (ratings[i] > ratings[i + 1]) {
        dp[i] = maxOf(dp[i], dp[i + 1] + 1)
    }
}
```

Each loop only writes its current entry `dp[i]`. The first processes left
dependencies before their dependents; the second does the same for right
dependencies. Each loop costs O(n), with O(n) auxiliary space for `dp`.

## Preservation proof for an arbitrary adjacent pair

Let A be the array after the first scan and B the array after the second scan.
Choose any adjacent pair satisfying `ratings[i] > ratings[i - 1]`.
The first scan establishes:

```text
A[i] >= A[i - 1] + 1
```

During the second scan, entry i can only stay unchanged or increase, because
its update uses `maxOf`. Therefore `B[i] >= A[i]`.

Entry `i - 1` could change only in its own iteration, whose guard is
`ratings[i - 1] > ratings[i]`. This contradicts the chosen pair's ordering.
Its guard is false, so `B[i - 1] = A[i - 1]`.

Combining these facts:

```text
B[i] >= A[i] >= A[i - 1] + 1 = B[i - 1] + 1
```

The pair was arbitrary, so every inequality established by the first scan
survives. The second scan establishes the right-neighbor inequalities because
`dp[i + 1]` has already been finalized when i is processed. Every entry stays
at least 1. Together these facts prove the result satisfies all constraints.

## Example and the mistaken shortcut

For `ratings = [1,2,1,2,1]`, initialization is `[1,1,1,1,1]`, the first scan
produces `[1,2,1,2,1]`, and the second scan leaves that array unchanged.
The proof above does not depend on this example or on exact rating values.

The reason the left member of the chosen pair cannot increase is that its
actual guard contradicts the pair's ordering, not that some other comparison
is missing from the loop. `maxOf` alone cannot protect an inequality if its
right-hand side also increases: `2 >= 1 + 1` fails when 1 becomes 2.

## From a heap to directional passes

The original approach processes children by increasing rating using a min-heap,
so lower-rated neighbors are handled before a child depends on their candies.
It costs O(n log n) time and O(n) auxiliary space.

Two directional scans handle the two dependency directions separately. The
preservation proof shows that satisfying the second family does not undo the
first. This removes the priority-ordering cost and gives O(n) time, still with
O(n) auxiliary space. Feasibility of either method does not, by itself, prove
that its total is the minimum possible.

Reusable rule: [Preserving earlier constraints](../../study-notes/algorithm-concepts-cheatsheet.md#prove-that-later-writes-preserve-earlier-constraints).
