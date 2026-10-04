# Dungeon Game: lessons from the discussion

This summarizes the side conversation about backward DP, path enumeration,
and what Dungeon Game minimizes. The saved implementation, full trace, and
proof are in [EXPLANATION.md](EXPLANATION.md).

## 1. A DP state can describe what the future requires

Define the state at an exact moment:

```text
dp[i][j] = minimum health needed before applying dungeon[i][j],
           to survive from this cell to the princess.
```

It describes a required incoming amount, not health remaining during an actual
walk or the initial health needed merely to reach this cell. Any amount at
least that requirement allows a successful continuation under the problem's
additive health rules; a smaller amount cannot.

This lets us summarize all future routes from a cell with one requirement.

## 2. Derive the recurrence from an inequality

After applying the current cell, there must be enough health for a continuation:

```text
incoming health + current cell change >= required afterward
incoming health >= required afterward - current cell change
```

Incoming health must also be at least 1. Therefore:

```text
required before = max(1, required afterward - current cell change)
```

Write this requirement before memorizing the formula. It explains both the
subtraction and the lower bound.

## 3. Choosing a route and enforcing survival are two separate operations

The knight can choose either down or right:

```text
required afterward = min(dp[i + 1][j], dp[i][j + 1])
```

The smaller requirement suffices because only one continuation must work.
Then account for the current cell and enforce survival:

```text
dp[i][j] = max(1, required afterward - dungeon[i][j])
```

Thus `min` chooses the better continuation, while `max(1, ...)` enforces the
health constraint. This combines path optimization with a resource requirement.

It is not shortest path by number of moves. Every right/down route from the
top-left to the bottom-right makes exactly `m + n - 2` moves. What differs is
the initial health required by each route. A larger final health or total cell
sum alone does not establish a smaller initial requirement: intermediate
shortages still matter.

## 4. Calculation order follows dependencies, not movement direction

Each entry reads the requirements below it and to its right. Calculate from
bottom-right toward top-left so those entries are ready.

The knight still moves right/down. Computing backward means undoing the
current health change mathematically, not moving the knight backward.

Right/down moves make the dependencies acyclic. In a cyclic setting, the
state or processing method needs more justification; for example, the
Gas Station DP uses the remaining-trip count as a decreasing dependency.

## 5. The same requirement idea appears in the earlier DP problems

```text
required before = max(lower bound, required afterward - current change)
```

| DP problem | Current change | Future requirement | Lower bound |
| --- | --- | --- | --- |
| 1413 | nums[i] | Requirement of the next suffix | 1 |
| Gas Station DP | gas[i] - cost[i] | Requirement for one fewer trip at the next station | 0 |
| Dungeon Game | dungeon[i][j] | Smaller requirement of the down/right continuations | 1 |

In 1413, the index determines the remaining suffix. Gas Station's DP also
needs the number of trips remaining. Dungeon Game's coordinates identify the
remaining grid choices. The linear Gas Station implementation is greedy;
this shared pattern describes its alternative DP formulation.

Related notes: [1413](../1413_minimum_value_to_get_positive_step_by_step_sum/EXPLANATION.md)
and [Gas Station DP](../134_gas_station/dp/EXPLANATION.md).

## Solution evolution: from complete paths to reusable states

A conceptual baseline is a hypothetical simple method used for comparison;
it does not mean that you personally implemented it. Here, the baseline
enumerates every complete route and checks its initial-health requirement.

Different routes share future subproblems. Backward DP solves each cell's
requirement once and reuses it instead of inspecting every complete route.

### Count paths for the baseline

Every route has `m - 1` down moves and `n - 1` right moves. Choosing the positions
of its down moves determines a route:

```text
number of paths = C(m + n - 2, m - 1)
```

`C(a, b)` means choosing b positions from a positions. For a 3 × 3 grid,
`C(4, 2) = 6` paths, each visiting 5 cells.

If we separately scan every complete path, time is:

```text
O((m + n) × C(m + n - 2, m - 1))
```

This bound describes that specific baseline. A DFS that updates a running
sum while traversing shares some prefix work; analyze its recursive calls
instead of automatically assigning it the extra per-path scan factor.

For square grids, path counts are 2, 6, 20, and 70 for side lengths 2, 3, 4,
and 5. Their growth is exponential in the side length, not in the total
number of cells.

### Count states and transitions for your implementation

Your full-table backward DP has:

- `m × n` real states.
- Constant work per state: read two successors, choose their minimum,
  subtract the cell value, enforce 1, and store the result.
- O(mn) initialization of the padded table.

Therefore its time is **Θ(mn)** and its auxiliary space is **O(mn)**.
Changing the dungeon's values cannot add iterations to these loops. The
number of possible paths does not multiply its runtime because the stored
states summarize those possibilities.

## A reusable reasoning habit

1. State exactly what the DP stores and whether it describes before or after
   the current action.
2. Write the inequality that a valid next step must satisfy.
3. Decide how choices combine: here one continuation suffices, so use `min`.
4. Calculate dependencies first, then the current state.
5. Count states and the work at each state; count complete paths only when
   the implementation actually enumerates them.

What to say: “I store the minimum incoming health needed to finish from each
cell. I choose the easier continuation, undo the current cell's change, and
keep health at least 1. Each cell is solved once, so the algorithm takes
Θ(mn) time even though the grid has many complete routes.”

Recall: What does dp measure? Why do `min` and `max` have different jobs?
Why is this not shortest path by distance? Which operations make your
implementation Θ(mn)?
