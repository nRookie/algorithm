# 134. Gas Station: a full-table DP learning version

[134.kt](134.kt) implements the minimum-required-gas DP discussed after the
[greedy solution](../EXPLANATION.md). It uses the same nonempty, equal-length
inputs, empty initial car, unlimited capacity, and clockwise trips. This is
a separate learning implementation; the saved greedy implementation remains
the linear-time solution.

## Define the table before the loops

```text
dp[k][i] = minimum gas needed when arriving at station i,
           before collecting gas[i], to complete exactly k trips.
```

This is gas **required before starting**, not gas remaining after driving.
There are n + 1 rows for k = 0 through n, and n columns for station indexes.
For zero trips, no gas is needed: `dp[0][i] = 0` for every station. Kotlin's
new `IntArray` entries already start at zero.

## Build one row from the preceding row

From station i, the next station is `(i + 1) % n`. Suppose we arrive at i
with some initial gas. After the first trip, the remaining gas is:

```text
initial gas + gas[i] - cost[i]
```

It must be at least `dp[k - 1][next]`, the gas required for the remaining trips.
Therefore:

```text
initial gas >= cost[i] - gas[i] + dp[k - 1][next]
```

Initial gas cannot be negative, giving:

```kotlin
dp[k][i] = maxOf(0, cost[i] - gas[i] + dp[k - 1][next])
```

If station i provides enough surplus for the remaining trips, the result is
zero. Otherwise, it is the exact shortage to bring into that station.

The outer loop increases k from 1 to n. Each calculation reads only row
k - 1, which is already complete. The inner loop fills all stations in row k;
it does not depend on the order in which those stations are processed.

## Example: all rows, including the base row

```text
station:  0   1   2
gas:      3   1   5
cost:     1   4   1
gas-cost: 2  -3   4
```

| Trips k | dp[k][0] | dp[k][1] | dp[k][2] |
| --- | --- | --- | --- |
| 0 | 0 | 0 | 0 |
| 1 | 0 | 3 | 0 |
| 2 | 1 | 3 | 0 |
| 3 | 1 | 3 | 0 |

For example, `dp[2][0] = maxOf(0, 1 - 3 + dp[1][1]) = 1`:
starting at station 0, we need 1 initial gas to complete `0 → 1 → 2`.

The last row describes n trips, exactly one full circle. Starting empty at
i works if and only if `dp[n][i] == 0`. Here only station 2 qualifies.
The final loop returns that station, or `-1` if no entry in row n is zero.

## Correctness and complexity

The base row is correct because zero trips require zero gas. Assuming row
k - 1 is correct, the recurrence gives the smallest nonnegative initial gas
that leaves enough after the first trip to complete the remaining k - 1.
Because the next row's requirement is nonnegative, it also ensures that the
first trip itself is feasible. This proves each row by induction.

Both loops are finite. There are n rows to calculate, each with n constant-time
updates, followed by one scan of n candidates: O(n²) time. The full table uses
O(n²) auxiliary space. Retaining only two rows could reduce space to O(n),
but would still take O(n²) time. For large inputs, use the greedy implementation.

This is DP because the same smaller subproblems are stored and reused across
different starting stations. The greedy implementation instead eliminates
whole intervals of candidates using a failure argument.

The saved Kotlin code compiled and passed 9 example/boundary cases plus 3,905
exhaustive small cases against direct circular simulation, using the same
checker described in the [greedy notes](../EXPLANATION.md). Those checks
verify examples; the induction above is the general correctness argument.
