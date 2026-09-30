# 121. Best Time to Buy and Sell Stock

These notes organize your baseline-to-one-pass derivation using the
[algorithm-solving workflow](../../study-notes/algorithm-solving-workflow.md).
Your final implementation is correct. The refinements below concern why it works.

## Goal and contract

Given daily prices, return the greatest profit from buying once and selling
on a strictly later day. Return 0 if no profitable transaction exists.
Return the profit, not the two days; the algorithm does not modify the array.
In an interview, clarify that only one transaction is allowed and the sale
must occur after the purchase. With one day, there is no valid pair and the answer is 0.

## Solution evolution

### 1. Check every buy/sell pair

Your baseline chooses each `buy_day`, then checks every `sell_day > buy_day`:

```kotlin
var max_profit = 0
var buy_day = 0
while (buy_day < prices.size) {
    var sell_day = buy_day + 1
    while (sell_day < prices.size) {
        max_profit = maxOf(max_profit, prices[sell_day] - prices[buy_day])
        sell_day++
    }
    buy_day++
}
return max_profit
```

For `[7, 1, 5, 3, 6, 4]`, this includes buying at index 1 and selling at index 4,
earning `6 - 1 = 5`. Every legal pair is checked, so the greatest profit is found.
Starting at 0 handles all losing pairs without forcing a purchase.

For n days, there are `n(n - 1) / 2` pairs: O(n²) time and O(1) auxiliary space.

**What to say:** “I can try every purchase day and every later sale day. This
covers every legal transaction, but repeatedly scans future days for each purchase.”

### 2. Remove the repeated comparisons

Ask your study-note question: **What work am I repeating?**

The same sale day is compared with many earlier purchase days. For a fixed
sale price, only the cheapest earlier purchase can produce the best profit.
So process sale days once from left to right, remembering that cheapest day.

For the shared example, when the sale price is 6, the earlier prices are
`[7, 1, 5, 3]`. Their best purchase price is 1; there is no need to compare 6
with each earlier price again. The running purchase candidate already stores it.

If today's price is no greater than the current purchase price, today becomes
the purchase candidate for future sales. For any later price `p`:

```text
new_buy_price <= old_buy_price
p - new_buy_price >= p - old_buy_price
```

Every future sale works at least as well with the new purchase. Completed
opportunities stay recorded in `max_profit`, so replacing `buy_day` loses nothing.

**What to say:** “For each sale day, the best purchase is the cheapest earlier
day. I can remember that day instead of checking every pair. I keep the best
profit separately because a later cheaper purchase must not erase an earlier win.”

| Approach | Work | Time | Extra space |
|---|---|---|---|
| All pairs | Every earlier purchase for every sale | O(n²) | O(1) |
| Your one-pass solution | One purchase candidate per sale | O(n) | O(1) |

### Refine three statements from your comments

1. **“Find the minimum price, then the maximum price after it.”** Choosing the
   global minimum first can fail. For `[2, 10, 1, 3]`, that earns 2, but buying
   at 2 and selling at 10 earns 8. Keep the minimum **among earlier days** for
   each sale, together with the best profit seen so far.
2. **“Move the sell day if we find a higher price.”** `sell_day` advances every
   iteration, regardless of the price. Every day is considered as a possible sale.
3. **“Move the buy day to the next day.”** Your code correctly jumps directly
   to `sell_day` when its price is lower or equal. It does not use `buy_day++`.
   This is safe because the new candidate is no more expensive for every future
   sale—not because the immediately following day is guaranteed to be profitable.

Equality goes into your `else` branch. Replacing a purchase with an equally
priced later day is safe for future sales, and a sale today could earn only 0.

## State and transition

At the start of an iteration:

| Variable | Meaning |
|---|---|
| `sell_day` | Index of the next day to consider as a sale |
| `buy_day` | Index of a cheapest price in `0 until sell_day` |
| `max_profit` | Best nonnegative profit with a sale strictly before `sell_day` |

If today's price exceeds the purchase price, compare today's best profit with
`max_profit`. Otherwise, update `buy_day` to today for future sales. Then always
increment `sell_day`.

After `buy_day = sell_day`, the indices temporarily match. No transaction is
calculated then; after the increment, the purchase is strictly before the next sale.

## Execution trace

```text
index:   0  1  2  3  4  5
prices:  7  1  5  3  6  4
```

Initialization: `buy_day = 0`, `sell_day = 1`, `max_profit = 0`.
Each row shows state before the body and after the final `sell_day++`.

| Sale index (price) | Buy index before (price) | Branch and action | Buy after | Profit after | Next sale |
|---|---|---|---|---|---|
| 1 (1) | 0 (7) | `else`: replace purchase | 1 | 0 | 2 |
| 2 (5) | 1 (1) | `if`: compare profit 4 | 1 | 4 | 3 |
| 3 (3) | 1 (1) | `if`: compare profit 2 | 1 | 4 | 4 |
| 4 (6) | 1 (1) | `if`: compare profit 5 | 1 | 5 | 5 |
| 5 (4) | 1 (1) | `if`: compare profit 3 | 1 | 5 | 6 |

Terminal state: `sell_day = 6 = prices.size`; the loop stops and returns 5.
Notice that a falling sale price, such as 5 → 3, does not stop the scan.

## Correctness and completion

**Invariant:** Before each iteration, `buy_day` identifies a minimum price
strictly before `sell_day`, and `max_profit` is the best nonnegative profit
among transactions whose sale day has already been processed.

**Initialization:** With `sell_day = 1`, the only earlier price is at index 0.
No legal transaction can sell before day 1, so the best profit is 0.

**Preservation:** If today's price is greater than the stored minimum, their
difference is the best profit ending today. Updating the maximum includes all
transactions ending today, and the earlier minimum stays valid. Otherwise,
no earlier purchase can make a positive profit today, so the recorded maximum
stays valid. Today becomes a minimum for the next iteration. Advancing the
sale index restores both parts of the invariant in either branch.

**Termination:** `sell_day` increases by one every iteration. Once it equals
the array length, every possible sale day has been processed. The invariant
therefore gives the required answer. A single-day input skips the loop and returns 0.

## Complexity and verification

The loop processes n − 1 sale days with constant work per day: O(n) time.
Three integer variables use O(1) auxiliary space. No arrays are copied by the solution.

The local harness checks increasing, decreasing, equal, single-day, zero-price,
and changing-purchase cases, including the global-minimum counterexample.
It also compares against all-pairs brute force for every array of lengths 1–7
with prices 0–3. These checks support the implementation; the invariant above
explains correctness for all valid inputs.

## Summary: interview explanation

“I can first try every buy day and every later sell day, keeping the largest
profit starting from zero. That takes O(n²) time and O(1) extra space.

For a fixed sell day, only the cheapest earlier purchase matters, so I can
scan sell days once while remembering that purchase day. If today's price
is higher, I calculate the profit and update the maximum; otherwise, today
becomes the purchase candidate for future days.

Replacing the purchase is safe because a lower or equal purchase price gives
at least as much profit for every future sale, while earlier profits remain
saved in `max_profit`.

Before each iteration, the purchase candidate is the cheapest earlier day,
and `max_profit` covers all previously processed sell days. Once every sell
day is processed, it contains the answer. The algorithm takes O(n) time and
O(1) extra space.”

### Precision reminders

- Explain the observation before introducing the optimized variables:
  only the cheapest earlier purchase matters for a fixed sell day.
- Justify replacing the purchase by comparing both purchase prices for the
  same future sell day. A loss today alone does not prove replacement is safe.
- Before the loop body, `max_profit` covers sell days strictly before
  `sell_day`. After processing today, it includes today. Incrementing
  `sell_day` restores the original boundary for the next iteration.
- Your code replaces `buy_day` on equal prices too; future profits are equal,
  so this is safe.

## Vocabulary: sell, sale, buy, purchase

| Word | Common grammatical role | Meaning and example |
|---|---|---|
| sell | Verb | Give something in exchange for money: “I sell the stock.” |
| sale | Noun | The act or transaction of selling: “The sale earns a profit.” |
| buy | Usually a verb | Obtain something by paying money: “I buy the stock.” |
| purchase | Verb or noun; more formal than buy | “I purchase the stock.” / “The purchase happens first.” |

Verb forms: **buy → bought → bought**, **sell → sold → sold**, and
**purchase → purchased → purchased**. `Sale` is not the past tense of `sell`.

For this problem, say “buy first, then sell” or “the purchase happens before
the sale.” Your variable names `buy_day` and `sell_day` are clear and consistent.
In ordinary prose, “the day I buy” and “the day I sell” are natural;
“purchase date” and “sale date” are noun-based alternatives.

`Buy` can also be a noun, as in “a good buy” (something worth its price).
`Sale` can also mean a discount event, as in “the shop has a sale”; that is
not its meaning in this algorithm discussion.

## Recall practice

Try reconstructing the loop from these questions without looking at the code:

- Which repeated comparisons disappear when we remember the cheapest earlier day?
- Why can a cheaper purchase replace the old candidate for every future sale?
- Why must `max_profit` survive when `buy_day` changes?
- Why does `sell_day` advance even when the price falls?
- What makes the initial state valid, and why does the stopping condition finish the job?

Next rehearsal: trace `[2, 10, 1, 3]` aloud and explain why the answer remains
8 after the purchase candidate changes to the price 1.
