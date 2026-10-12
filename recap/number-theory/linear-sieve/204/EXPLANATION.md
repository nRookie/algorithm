# 204 — Count Primes: deriving the linear sieve

## Problem and boundary

[LeetCode 204 — Count Primes](https://leetcode.com/problems/count-primes/description/)
asks for the number of primes **strictly below n**, with `0 <= n <= 5,000,000`.
It is a Medium problem with a publicly available statement. The Kotlin API is
`class Solution` with `fun countPrimes(n: Int): Int`.

The original memo counts primes up to and including n. The saved solution
adapts that boundary: n = 3 returns 1 (only 2), not 2. The original code and
the learner's two later Kotlin attempts are preserved in [SOURCE.md](SOURCE.md).

## Solution evolution

Derive the method before translating it into loops.

### 1. Test every candidate independently

For each candidate x, try divisors from 2 through its square root. The square
root of x is the nonnegative number whose square equals x; for example,
sqrt(36) = 6. If x = a * b, at least one of a and b is at most sqrt(x),
because if both were larger, their product would exceed x.

Thus, finding a divisor proves x composite; finding none proves it prime.
The time upper bound is O(n sqrt(n)), with O(1) auxiliary space. The repeated
work is searching for divisors independently for every candidate.

What to say: “I can test each number for a divisor up to its square root.
This is correct, but repeatedly searches for the same factors.”

### 2. Let each prime mark its multiples: Eratosthenes

Instead of asking each candidate whether 2 divides it, mark multiples of 2
as composite together. Then use the next unmarked number, 3, to mark its
multiples, and continue with other primes.

Why does every composite have a prime factor? Choose its smallest divisor p
greater than 1. If p were composite, one of its smaller divisors would also
divide the original number, contradicting the choice of p. So p is prime.

We can start marking a prime p's multiples at p squared. Smaller multiples
p * k, with 2 <= k < p, already have a smaller prime factor and were marked
earlier. Conversely, if p is a composite x's smallest prime factor, x / p
cannot be smaller than p, so x >= p squared. Marking from p squared reaches x.
No prime is marked, because every marked product has two factors greater than 1.

The marking work is bounded by n/2 + n/3 + n/5 + ..., over primes. The sum
of prime reciprocals grows as O(log log n), yielding O(n log log n) time and
O(n) space. This reciprocal-sum bound is a number-theoretic result, not a
consequence of nested loops alone.

What to say: “I share divisibility work by marking multiples of each prime.
Every composite has a prime factor, so this reaches every composite.”

But 12 can still be marked by both 2 and 3. Can we remove this repeated work?

### 3. Give each composite one generating pair: linear sieve

Assign every composite to its smallest prime factor:

| Composite | Chosen pair | Pair we skip |
| --- | --- | --- |
| 12 | 2 * 6 | 3 * 4 |
| 18 | 2 * 9 | 3 * 6 |
| 15 | 3 * 5 | 5 * 3 |

Process a current number i and pair it with discovered primes p. The product
is p * i. We use multiplication to generate a new composite; x / p appears
only when reasoning backward from an existing composite x.

“Prime factors inside i” simply means prime numbers dividing i. For example,
12 = 2 * 2 * 3, so multiplying it by 5 gives 5 * 2 * 2 * 3: the product
still contains prime factors 2 and 3. Multiplication does not remove them.

Let spf(i) mean i's smallest prime factor. Then:

    spf(p * i) = min(p, spf(i))

To make p the product's smallest prime factor, allow only p <= spf(i).
Visit known primes in ascending order. The first one dividing i is spf(i):
include its product, then stop. We do not need to factor i separately.

What to say: “I only pair a number with primes no larger than its smallest
prime factor. This assigns each composite to one prime and avoids duplicate markings.”

## Overall process in simple terms

1. Create a false-filled table st and an empty list primes.
2. Visit each i from 2 through n - 1. If st[i] is false, append i to primes.
3. Visit discovered primes p in ascending order. If p * i is outside the
   range, stop. Otherwise mark st[p * i] as true.
4. After marking, if p divides i, stop this inner traversal. Continue with
   the next outer-loop number i.
5. Return primes.size.

Both prime and composite values of i generate products. In particular,
4, 6, and 8 are generated with p = 2 at different outer iterations:
i = 2, i = 3, and i = 4. We do not mark all multiples of 2 at once.

### Why stop after the first prime dividing i?

At i = 4, mark 2 * 4 = 8, then stop because 2 divides 4. Trying p = 3 would
mark 12, but 12 has smaller prime factor 2. Leave it for 2 * 6.

This does not mean “i is already marked, so skip its products.” We still
need the products, such as 8. It means larger primes would generate products
under the wrong prime factor.

Stopping affects only the current i. It does not stop prime 3 from marking
15 later: at i = 5, use p = 2 to mark 10, then p = 3 to mark 15. Neither
prime divides 5, so neither triggers the divisibility break.

At i = 6, mark 2 * 6 = 12 and stop. Trying 3 * 6 = 18 would duplicate the
later marking 2 * 9 = 18.

## Correctness

### Every generated product uses its smallest prime factor

Before the first prime dividing i, all visited primes p are smaller than
spf(i). At the first dividing prime, p equals spf(i). Consequently every
marking has p <= spf(i), so spf(p * i) = p.

The condition i % p != 0 alone is insufficient: 6 % 5 != 0, but 5 is larger
than 6's prime factors. It is the ascending order plus the earlier stopping
rule that makes the claim true in this algorithm.

### Every composite is marked before it is classified

For any composite x < n, choose p = spf(x) and i = x / p.

- Every prime factor of i is at least p, or x would have a smaller prime
  factor. Thus p <= spf(i), and no earlier prime stops the traversal.
- p <= i < x: the smallest factor of a composite is at most its square root.
  So p is discovered by iteration i, including appending i itself if p = i.
- The product fits because p * i = x < n.

Therefore iteration i marks x before iteration x. Formally, use induction
on the outer iterations: earlier classifications are correct, so the required
prime is already available; the base case is 2, which is unmarked and prime.

### No prime is marked, and no composite is marked twice

Every marked number is p * i with both factors at least 2, so no prime is marked.
For a fixed composite x, the marking rule forces p = spf(x), which uniquely
fixes i = x / p. Each pair is visited once, so x is marked exactly once.

Together these establish that st[i] is false exactly for primes when i is
classified. Indices 0 and 1 are never classified.

## Time and space complexity

Each inner marking corresponds to a different composite. There are fewer
than n composites below n, so the total number of markings is O(n), even
though the markings are distributed across nested loops. Each marking takes
constant time in the integer model used here.

Each outer iteration contributes at most one additional bound-failing inner
check. Initialization, outer scanning, and amortized prime-list appends also
cost O(n). Therefore total time is Theta(n) for growing n, and auxiliary space
is O(n) for the table and prime list.

Fewer than n composites is not enough by itself: the proof depends on marking
each one exactly once. Repeated markings are what the break eliminates.

## Implementation and boundary fix

The saved [Solution.kt](Solution.kt) follows the learner's BooleanArray and
mutable prime list. BooleanArray stores primitive flags compactly, while the
prime list is growable and boxes Int values on the JVM. This keeps the user's
chosen representation; no manual prime-count variable is needed.

The implementation is:

```kotlin
class Solution {
    fun countPrimes(n: Int): Int {
        if (n <= 2) return 0

        val st = BooleanArray(n)
        val primes = mutableListOf<Int>()

        for (i in 2 until n) {
            if (!st[i]) primes.add(i)

            for (p in primes) {
                if (p > (n - 1) / i) break
                st[p * i] = true
                if (i % p == 0) break
            }
        }
        return primes.size
    }
}
```

### Why p >= n / i breaks too early

Integer division truncates. With n = 10, i = 3, p = 3:

    p * i = 9 < 10       // Must mark 9.
    n / i = 10 / 3 = 3
    p >= n / i           // True: incorrectly stops before marking 9.

The first attempt therefore returns 5 instead of 4 for n = 10, counting 9
as prime. Convert the strict product boundary into an inclusive one first:

    p * i < n
    p * i <= n - 1
    p <= (n - 1) / i     // Equivalent for positive integers.

Stop when p > (n - 1) / i. Check this before multiplying to avoid Int overflow.
The accepted product is at most n - 1, so it is a valid BooleanArray(n) index.

The learner's second version, BooleanArray(n + 1) with p > n / i, is also
correct: it allows marking n, but the outer loop excludes n, so n is never
counted. That extra entry and marking are unnecessary rather than incorrect.

### Other details resolved during practice

- “p divides i” is i % p == 0, not p % i == 0.
- Mark before checking divisibility. Breaking first would skip 4 at i = 2.
- Append a newly discovered prime before generating products, so 2 can mark 4.
- The list is modified only before its traversal, not during it.
- Return 0 for n <= 2. All state is local, so repeated calls are independent.
- The original C++ snippet's abbreviated example should mark st[p * i], not
  st[p]. Its omitted j < cnt is safe under the invariant: a discovered divisor
  of i stops traversal, unless the size bound stops it sooner.

## Complete trace: n = 11

Initially primes is empty and every st entry is false. Allowed products are
at most 10.

| i | Newly appended prime | Products marked | Why stop? |
| --- | --- | --- | --- |
| 2 | 2 | 4 | 2 divides 2 |
| 3 | 3 | 6, 9 | 3 divides 3 |
| 4 | — | 8 | 2 divides 4 |
| 5 | 5 | 10 | Next product 15 exceeds 10 |
| 6 | — | None | First product 12 exceeds 10 |
| 7 | 7 | None | First product 14 exceeds 10 |
| 8 | — | None | First product 16 exceeds 10 |
| 9 | — | None | First product 18 exceeds 10 |
| 10 | — | None | First product 20 exceeds 10 |

Stop the outer loop before 11. Return 4 for the primes [2, 3, 5, 7].

## Spoken explanation

“I keep a table of composite numbers and a list of discovered primes. I visit
numbers below n in increasing order. An unmarked number is prime, so I add it
to the list. For each current number, I mark its products with known primes
in increasing order. I stop if the product is outside the range, or after
using the first prime that divides the current number. This makes every
product use its smallest prime factor, so each composite is marked exactly
once. Total time and space are linear.”

## Local validation and practice

Run `bash run.sh` in this folder. [Test.kt](Test.kt) checks every n from 0
through 2000 against independent trial division, including the n = 10
regression, the maximum input 5,000,000 against 348,513, and a repeated small
call for stale state. Validation uses a 256 MB JVM heap; these are local
checks, not a claim of an online judge submission.

Independent practice: reconstruct LeetCode 204 from the spoken explanation.
Optional recall: explain why 15 is still marked after stopping at i = 4,
and why an exclusive product limit needs (n - 1) / i.
