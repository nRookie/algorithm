# ABC 479 C — choosing dishes under a capacity limit

Problem: [AtCoder ABC 479 C](https://atcoder.jp/contests/abc479/tasks/abc479_c).
The official page could not be retrieved while writing these notes; the contract
below comes from the statement and constraints supplied in our discussion.

Choose each dish at most once. Maximize total deliciousness while total volume
is **at most** W. Choosing nothing is allowed. There are N ≤ 20 dishes;
W, Aᵢ, Bᵢ are positive integers at most 10⁹. Input is N W followed by N pairs
of deliciousness and volume. Output one maximum deliciousness.

## Recognize this quickly next time

This is 0/1 knapsack, but the problem name does not determine the algorithm.
Capacity DP depends on the numeric value of W; subset search depends on N.
Here, W = 10⁹ is huge and N = 20 is small: use take-or-skip DFS.

| Approach | Time | Auxiliary space | Fit for these limits? |
| --- | --- | --- | --- |
| Capacity DP, compressed to one row | O(NW) | O(W) | No: about 8 GB for the array alone |
| DFS returning the best suffix answer | O(2ᴺ) | O(N) stack | Yes: at most about 2.1 million calls |

LongArray(1_000_000_001) needs 8,000,000,008 bytes of element storage, before
object/runtime overhead. DP can also require about 20 billion updates.
The recurrence is mathematically correct; the implementation exceeds practical
resource limits. The precise runtime-error cause was not confirmed from a judge log.

## Your reasoning, polished and corrected

You recognized the capacity restriction as knapsack, defined a state using the
number of available dishes and bag capacity, then compressed the DP to one row.
After checking the constraints, you switched to branching on each dish.

Clarifications to the original DP comments:

- `dp[i][j]` means the maximum deliciousness using the **first i dishes** with
  capacity **at most j**. It does not mean selecting exactly i dishes.
- `dp[0][j] = 0` for every capacity: with no dishes, the empty selection is valid.
  `dp[i][0] = 0` because all volumes are positive. Zero initialization works for
  an at-most-capacity objective; an exact-volume DP needs unreachable states.
- Dish index `i - 1` corresponds to row i. When it fits, the two-dimensional
  transition is `max(dp[i - 1][j], dp[i - 1][j - vol[i - 1]] + del[i - 1])`.
- Equality fits: use `j >= vol[i - 1]`, not strict `>`.
- Descending capacity keeps the source value in the previous item layer.
  The issue with ascending capacity is **reusing the current dish**, not leaving
  older values unupdated. Keeping an old value intentionally represents skipping.

## Solution evolution

### 1. Capacity DP: valid recurrence, unsuitable state range

For each dish, either retain the best answer without it or add its deliciousness
to an answer that leaves enough room. These cases cover all valid selections.
Your implementation below retains the original logic; explanatory comments are
organized above. This is a reference implementation for smaller capacities.

```kotlin
fun run(n: Int, w: Int, del: LongArray, vol: IntArray): Long {
    val dp = LongArray(w + 1) { 0 }
    for (i in 1 until n + 1) {
        for (j in w downTo vol[i - 1]) {
            dp[j] = maxOf(dp[j], dp[j - vol[i - 1]] + del[i - 1])
        }
    }
    return dp[w]
}
```

For one dish `(del=4, vol=5)` and capacity 10, ascending updates produce
`dp[5]=4`, then `dp[10]=dp[5]+4=8`, illegally taking that dish twice.
Descending updates produce `dp[10]=4` before updating `dp[5]`.

**What to say:** “The recurrence is correct, but O(W) storage and O(NW) time
are too large when W reaches a billion. Compressing rows does not fix that.”

### 2. DFS: make the cost depend on the small item count

Every dish has two choices. Explore them directly instead of allocating an
entry for every possible capacity. Your second implementation is correct:

```kotlin
fun run(n: Int, w: Long, del: LongArray, vol: LongArray): Long {
    fun dfs(i: Int, w: Long): Long {
        if (i == n) return 0
        var get_del = 0L
        if (w >= vol[i]) {
            get_del = dfs(i + 1, w - vol[i]) + del[i]
        }
        return maxOf(dfs(i + 1, w), get_del)
    }
    return dfs(0, w)
}
```

| Name | Meaning |
| --- | --- |
| `i` | Next dish to decide; remaining dishes are indices `[i, n)` |
| Inner `w` | Remaining capacity, always nonnegative |
| `dfs(i, w)` | Best **additional** deliciousness obtainable from those dishes |
| `get_del` | Best result if taking dish i; stays 0 when taking is unavailable |

The inner `w` shadows the outer parameter, but each recursive invocation has
its own argument. No shared capacity is mutated and no undo operation is needed.
The return value already summarizes future deliciousness, so this version does
not need a total-deliciousness parameter or a global maximum.

Zero for an unavailable take branch is safe here because skipping everything
always achieves 0. This convention needs reconsideration if a selection is
mandatory or an exact volume must be reached.

This is exhaustive DFS, not memoized DP: equal `(i, w)` calls may be recomputed.
Memoization is unnecessary for this bound, and allocating an N-by-W cache would
reintroduce the capacity problem. Bitmask enumeration is another option; DFS is
not required by the problem type.

**What to say:** “N is only 20, so I can explore every take-or-skip selection.
I pass the remaining capacity and return the best score for the remaining dishes.”

## Complete call/return trace

Use `n=2`, `w=5`, `del=[4,3]`, `vol=[5,3]`. Your code explores taking first.

| Call in execution order | Work and return |
| --- | --- |
| `dfs(0,5)` | Dish 0 fits; call `dfs(1,0)` for taking it |
| `dfs(1,0)` | Dish 1 does not fit; `get_del=0`; call `dfs(2,0)` |
| `dfs(2,0)` | Base case returns 0; `dfs(1,0)` returns 0 |
| Resume `dfs(0,5)` | Take result is `0+4=4`; call skip branch `dfs(1,5)` |
| `dfs(1,5)` | Dish 1 fits; call `dfs(2,2)` |
| `dfs(2,2)` | Base case returns 0; take result at `(1,5)` is 3 |
| `dfs(2,5)` | Skip dish 1; base case returns 0 |
| Return `dfs(1,5)` | `max(0,3)=3` |
| Return `dfs(0,5)` | `max(3,4)=4` |

The over-capacity selection containing both dishes is never explored.
For your larger example, `W=13` and pairs `(4,5),(3,3),(5,9),(8,6)`, the
answer is 12: take the first and fourth dishes, with total volume 11.

## Why DFS is correct and terminates

At `i == n`, no dishes remain, so the best additional score is 0.
Assume recursive answers for index i+1 are correct. Every feasible selection
from index i either skips dish i, giving `dfs(i+1,w)`, or takes it. Taking is
legal only if `w >= vol[i]`, and then its best score is
`del[i] + dfs(i+1,w-vol[i])`. Taking the maximum therefore gives the optimum.
Positive volumes justify excluding a dish that does not fit; later selections
cannot restore capacity. Every recursive step increases i, so depth is bounded
and every dish is considered at most once along a path.

## Count DFS work and choose numeric types

At depth k there are at most 2ᵏ calls. A full tree has:

```text
leaves = 2ᴺ
total calls = 1 + 2 + 4 + ... + 2ᴺ = 2ᴺ⁺¹ - 1
N = 20: 1,048,576 leaves and 2,097,151 total calls
```

Each call performs constant work apart from its recursive calls, giving O(2ᴺ)
time. Infeasible take branches reduce actual work, but all dishes may fit, so
the worst case remains exponential. Scanning N dishes afresh at every leaf
would instead cost O(N·2ᴺ). The active call stack is only O(N); the tree is not
stored all at once. Input arrays also take O(N) space.

Call counts do not determine exact seconds: hardware, JVM startup, allocation,
and judge limits matter. A few million small calls are a practical scale here;
do not turn that into a universal calls-per-second guarantee.

Each input fits Int, but a deliciousness sum can reach `20 * 10⁹`, requiring
Long. A separately accumulated unrestricted volume sum would also require Long.
In this remaining-capacity DFS, `w` itself stays between 0 and the original W,
so Int capacity would be safe; your consistent Long usage is also safe.

## Shared input/output wrapper

Use this wrapper with **one** of the `run` functions above. The shown main is
for DFS. For the DP reference, read `w` with `nextInt()`, create an `IntArray`
for `vol`, and read each volume with `nextInt()` instead. Do not put both mains
or duplicate scanner classes into one submission.

```kotlin
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

private class FastScanner {
    private val reader = BufferedReader(InputStreamReader(System.`in`))
    private var tokens = StringTokenizer("")

    fun next(): String {
        while (!tokens.hasMoreTokens()) {
            val line = reader.readLine()
                ?: throw NoSuchElementException("No more input")
            tokens = StringTokenizer(line)
        }
        return tokens.nextToken()
    }

    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
    fun nextDouble(): Double = next().toDouble()
}

fun main() {
    val fs = FastScanner()
    val out = System.out.bufferedWriter()
    val n = fs.nextInt()
    val w = fs.nextLong()
    val del = LongArray(n)
    val vol = LongArray(n)
    repeat(n) { i ->
        del[i] = fs.nextLong()
        vol[i] = fs.nextLong()
    }
    val res = run(n, w, del, vol)
    out.write("$res\n")
    out.flush()
}
```

## Validation

Compiled the Kotlin functions and compared against independent bitmask subset
enumeration on 200 seeded random small cases and six examples/boundary cases:
the two examples above, no item fitting, exact fit, the one-item reuse trap,
and 20 items whose total deliciousness is 20,000,000,000. DFS passed all cases;
DP matched on the small-capacity cases (the billion-capacity allocation was
intentionally not executed). The DFS input/output wrapper also compiled and
printed 12 for the four-dish example. These are local checks, not a judge verdict.

## Recall prompts

- Which parameter makes capacity DP too expensive, and which makes DFS feasible?
- What does `dfs(i,w)` return, and why is accumulated deliciousness unnecessary?
- Why does descending capacity prevent selecting a dish twice?
- Why are there O(2ᴺ) calls but only O(N) stack space?

Interview summary: “This is 0/1 knapsack. Capacity DP is correct but exceeds
the resource limits because W is huge. With only 20 items, I branch on taking
or skipping each item, return the best feasible suffix score, and use Long for
the answer. This takes O(2ᴺ) time and O(N) recursion space.”
