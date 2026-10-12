# AcWing 104 — Warehouse Location

[Original problem](https://www.acwing.com/problem/content/106/).
[Your Kotlin implementation](Main.kt) uses built-in Scanner, a MutableList,
in-place sorting, and a median. Only formatting and the median comment were
polished; the supplied algorithm and Int arithmetic are preserved.

Input: n, then n positions. Output: the minimum total distance to a warehouse.
The previously verified constraints are `1 <= n <= 100000` and
`0 <= position <= 40000`. This is a local Kotlin/JVM runner; no AcWing Kotlin
submission or online acceptance is claimed.

## Run from the repository root

Official sample (prints 12):

```sh
bash recap/greedy/acwing-104/run.sh sample
```

Type your own input:

```sh
bash recap/greedy/acwing-104/run.sh
```

For example, enter `4`, then `6 2 9 1`. The program finishes after reading
all four positions; you do not need to send end-of-file.

Read from your own input file:

```sh
bash recap/greedy/acwing-104/run.sh < input.txt
```

Run the local cases, including a maximum-size input:

```sh
bash recap/greedy/acwing-104/run.sh test
```

Each command recompiles Main.kt so your edits take effect. Kotlin/JVM and
Java are required; test mode also uses Python 3. Compilation products stay
in the ignored .build directory.

## Review

- The algorithm is correct: a median minimizes total absolute distance.
- `positions[n / 2]` is the upper median for even n, not an upper-bound search.
- Int is sufficient under these specific constraints. Pairing the sorted
  extremes expresses the optimal sum as at most `floor(n / 2)` gaps, each
  at most 40000. Thus the sum is at most 2,000,000,000, below Int.MAX_VALUE.
  Each individual subtraction is also safe. Broader coordinate ranges may
  require Long, with conversion before subtraction.
- Time is O(n log n), and space is O(n), including list storage and JVM sort
  workspace. Scanner is convenient locally; local passing tests do not prove
  compliance with an online judge's time limit.

See the [median proof and explanation](../leetcode-462-minimum-moves-to-equal-array-elements-ii/EXPLANATION.md)
and the related LeetCode 462 version for the function-based judge interface.
