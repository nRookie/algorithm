# 122. Best Time to Buy and Sell Stock II

Return the maximum profit from unlimited transactions, while holding at most
one share at any time. Buying spends money; selling receives money. There is
no transaction fee or cooldown. The input does not need to change.
Unlike question 121, profits from multiple completed transactions can accumulate.

## Review of your implementation

Your implementation correctly keeps the best balance for each of two states.
Its time complexity is O(n), and its auxiliary space is O(n).
The code already handles two details missing from your draft comments:

- Before any days have been processed, not holding has balance 0, but holding
  is impossible. Setting both states to 0 would give you a free stock: `[5]`
  would incorrectly return 5.
- Each transition must include doing nothing. The transition is a maximum of
  keeping the old state and making a trade, not just the result of a trade.

Your `-10000000` represents an impossible state and is sufficiently negative
for this exercise. It is a finite sentinel, not mathematical negative infinity;
do not assume it works for arbitrary larger price ranges. An alternative for
nonempty input is to initialize after day 1 with cash 0 and holding balance
`-prices[0]`, then process the remaining days.

## Solution evolution

### 1. Enumerate legal decisions

At each day, either do nothing or change your holding state. If you hold a
share, you can sell; otherwise, you can buy. Explore both branches and keep
the largest final balance among branches ending without a share.

Same-day buy/sell pairs have zero net effect, since both use the same price.
They can be removed, so at most one state-changing action per day suffices.

For `[7,1,5,3,6,4]`, one branch buys at 1, sells at 5, buys at 3, and sells at
6, earning 7. Enumerating all branches takes O(2^n) time and O(n) recursion
space. Many histories reach the same day and holding state.

**What to say:** “I can enumerate every legal daily decision, but many histories
leave me with the same future choices. I only need the best balance for each
holding state at each day.”

### 2. Merge equivalent histories: your DP

Two histories at the same day with the same holding state have identical future
options. The history with a smaller balance can never catch up by taking those
same future actions, so discard it.

Your arrays store states **after processing the first i days**:

| Variable | Meaning |
| --- | --- |
| `nonhold_max_profit[i]` | Best balance with no stock after the first i days |
| `hold_max_profit[i]` | Best balance with one stock after the first i days |
| `prices[i - 1]` | Price on the day being processed |
| index `0` | Before processing any days |

The holding balance includes the cost of buying the currently held share.
It is not the value you would get by selling that share. It can become positive
after earlier profitable transactions.

```text
nonhold_max_profit[i] = max(
    nonhold_max_profit[i - 1],                 // rest without stock
    hold_max_profit[i - 1] + prices[i - 1]     // sell
)

hold_max_profit[i] = max(
    hold_max_profit[i - 1],                    // keep holding
    nonhold_max_profit[i - 1] - prices[i - 1]  // buy
)
```

This merges exponentially many histories into two states per day: O(n) time
and O(n) auxiliary space.

**What to say:** “For each day, I track the best balance with and without a
share. Each state either carries over or comes from a trade using yesterday's
opposite state. I return the final balance without a share.”

### 3. Keep only yesterday's states

Every update reads only index `i - 1`; older entries are unused. Two variables
and temporary values therefore reduce auxiliary space to O(1), with O(n) time.
This is an optional improvement, separate from your saved implementation.

```kotlin
fun maxProfit(prices: IntArray): Int {
    if (prices.isEmpty()) return 0
    var nonhold = 0
    var hold = -prices[0]
    for (i in 1 until prices.size) {
        val previousNonhold = nonhold
        val previousHold = hold
        nonhold = maxOf(previousNonhold, previousHold + prices[i])
        hold = maxOf(previousHold, previousNonhold - prices[i])
    }
    return nonhold
}
```

**What to say:** “Only the previous day's states are needed, so I can keep two
balances instead of two arrays, preserving the same recurrence.”

### 4. Use this problem's unlimited, fee-free trading rule

Holding from day a to day b earns `prices[b] - prices[a]`. This equals the sum
of the adjacent daily changes over that interval. Any strategy therefore earns
at most the sum of all positive daily changes. That bound is achievable by
holding during every rising interval and avoiding every falling interval.
Consecutive rises can be combined into a single transaction.

For `[7,1,5,3,6,4]`, changes are `-6,+4,-2,+3,-2`; take `4+3=7`.
For `[1,2,3,4,5]`, adding four gains of 1 gives the same profit as buying at
1 and selling at 5.

```kotlin
fun maxProfit(prices: IntArray): Int {
    var profit = 0
    for (i in 1 until prices.size) {
        profit += maxOf(0, prices[i] - prices[i - 1])
    }
    return profit
}
```

This is also O(n) time and O(1) auxiliary space. It simplifies the reasoning
and code but does not improve asymptotic costs over compressed DP. Fees,
cooldowns, or transaction limits require rethinking this greedy rule.

**What to say:** “Because transactions are unlimited and free, I can capture
every positive adjacent price change. Every longer holding period decomposes
into those daily changes, so no strategy can earn more.”

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Exhaustive decisions | O(2^n) | O(n) |
| Your DP arrays | O(n) | O(n) |
| Compressed DP | O(n) | O(1) |
| Sum positive changes | O(n) | O(1) |

## Trace of your code

Each row shows states after processing that day. `−∞` below means your
`-10000000` sentinel. The two columns represent alternative histories, not
two simultaneous holdings or a single shared sequence of trades.

| i | Price | `nonhold_max_profit[i]` | Choice | `hold_max_profit[i]` | Choice |
| --- | --- | --- | --- | --- | --- |
| 0 | — | 0 | Initial | −∞ | Impossible |
| 1 | 7 | 0 | Rest | -7 | Buy |
| 2 | 1 | 0 | Rest | -1 | Buy from previous cash 0 |
| 3 | 5 | 4 | Sell | -1 | Keep holding |
| 4 | 3 | 4 | Rest | 1 | Buy from previous cash 4 |
| 5 | 6 | 7 | Sell | 1 | Keep holding |
| 6 | 4 | 7 | Rest | 3 | Buy from previous cash 7 |

Return `nonhold_max_profit[6] = 7`. The last holding state has balance 3 and a
share still held; it is not the requested final realized profit.

## Correctness and termination

Initially, cash 0 is the only feasible state. Assume both states at index
`i - 1` store the best feasible balances. Any history ending day i without a
share either already had no share and rested, or held a share and sold it.
Your first maximum considers both cases. Similarly, a history ending with a
share either kept it or bought it; your second maximum considers both cases.
Each transition is legal and every relevant possibility is covered, so the
invariant holds at i by induction. Same-day zero-net trades add no better cases.

The loop advances through exactly n days and terminates. The no-stock state
at n is the best completed trading balance. Returning it avoids treating an
unfinished position as realized profit.

## Interview rehearsal

“I track the best balance after each day with and without a share. Initially
I have zero cash profit and cannot already own a share. For each day, I can
keep either state or trade from the other previous state. This covers all legal
choices while discarding worse histories with identical future options. I return
the final no-share balance. The arrays take linear time and space; keeping just
yesterday's two values reduces space to constant.”

Try explaining these without looking at the code:

1. Why does initializing the holding state to 0 fail for `[5]`?
2. Why does each recurrence need the “do nothing” candidate?
3. Why is `hold_max_profit[4]` equal to 1 in the trace?
4. Why are previous-day transitions sufficient despite same-day trades being allowed?
5. What information lets us discard earlier histories and then earlier array entries?
6. Why would a transaction fee break the sum-of-positive-changes argument?

## My answers, polished for an interview

### 1. Why does initializing the holding state to 0 fail for `[5]`?

“Setting the initial holding balance to zero means I already own a share
without paying for it. For `[5]`, I could sell that imaginary share and report
a profit of 5. Before processing any days, holding a share must be impossible.
Buying at a price of zero is allowed; starting with a free share is the error.”

### 2. Why does each recurrence need the ‘do nothing’ candidate?

“Doing nothing is a valid action. I can reach each state either by keeping
yesterday's state and balance, or by trading from yesterday's opposite state.
I must consider both possibilities to find the maximum balance. Doing nothing
keeps my balance unchanged, even though the stock price may change.”

### 3. Why is `hold_max_profit[4]` equal to 1?

“In `[7,1,5,3,6,4]`, I can buy at 1 and sell at 5, earning 4. Then I buy at
3, leaving a balance of `4 - 3 = 1` while holding one share. The holding state
stores the best balance after all trades so far, including the cost of the
share I currently own. It does not just track the cheapest purchase price;
profits from earlier transactions also contribute.”

### 4. Why are previous-day transitions sufficient despite same-day trades?

“Yesterday's two best balances already summarize the relevant earlier
decisions. Today's choices depend only on those balances, whether I hold a
share, and today's price. Buying and selling on the same day uses the same
price and has no fee, so a same-day round trip changes neither my balance nor
my final holding state. Removing those round trips loses no profit, which
means previous-day transitions are sufficient.”

### 5. Why can we discard earlier histories and older array entries?

“Many different trading histories reach the same day with the same holding
state. Those histories have identical future choices. If one has a lower
balance, following any future sequence of trades keeps it behind the history
with the higher balance. I therefore keep only the maximum balance for each
state. Separately, each recurrence reads only yesterday's two values, so I
can replace the arrays with two variables and preserve the previous values
while calculating the next ones.”

### 6. Why does a transaction fee break the sum-of-positive-changes argument?

“Capturing every rise can require more transactions, and every transaction
can incur another fee. Combining rises into one longer holding period may
therefore earn more, even if I hold through a temporary price drop.
For `[1,3,2,4]` with a fee of 2 per sale, taking both rises earns
`(3 - 1 - 2) + (4 - 2 - 2) = 0`, while buying at 1 and selling at 4 earns
`4 - 1 - 2 = 1`.

“The two-state DP still works with the same state definitions. I can subtract
the fee when selling, charging it once per completed transaction. The fee is
an input parameter; it does not require an additional DP state.”

```text
nonhold[i] = max(nonhold[i - 1], hold[i - 1] + price - fee)
hold[i] = max(hold[i - 1], nonhold[i - 1] - price)
```

### Follow-up: Why discard a holding balance of −2 when another is 1?

“Both histories reach the same day holding one share, so they have exactly
the same future choices. Any future trades add the same amount to both
balances, and the balance of 1 always stays 3 ahead of −2. Even if the −2
history bought its share at a lower price, that purchase price is already
reflected in its balance and gives it no future advantage. I can permanently
discard that history.”
