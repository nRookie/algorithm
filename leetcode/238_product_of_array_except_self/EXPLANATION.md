# 238. Product of Array Except Self

## Contract

Return `answers[i]`, the product of every input element except `nums[i]`, in
O(n) time without division. Do not modify `nums`. Let n be its length.
For `[1,2,3,4]`, return `[24,12,8,6]`.

The implementations below use Kotlin `Int`. Prefix and suffix products must
fit a 32-bit signed integer, and the answer products must fit as well; outside
such guarantees, choose an appropriate numeric representation.

## Solution evolution

### 1. Your starting reasoning: recompute each answer

This is a polished account of the reasoning you supplied, with corrections
called out rather than attributed to your original attempt.

You started by asking how to solve `[1,2,3,4]` directly: for each index i,
scan the array again and accumulate a product. The correct baseline sets
`product = 1`, multiplies `nums[j]` only when `j != i`, then stores the result.
This takes O(n²) time and O(1) auxiliary space excluding the output.

Your exploratory alternative multiplied everything and divided by `nums[i]`.
That fails with zeros: for `[0,2,3]`, the total is zero, but the answer at
index 0 is 6 and division by zero is undefined. Division is also disallowed.
Computing the same total inside every outer iteration repeats work; computing
it once would reduce time but would not fix those correctness/constraint issues.

What to say:

> “A straightforward solution scans all other elements for each index. That
> takes O(n²). I want to reuse the overlapping products instead.”

### 2. Your first implementation: two exclusive product arrays

Your key observation was that the answer separates into a left product and a
right product. For index 2, `answers[2] = nums[0] * nums[1] * nums[3]`.
Correction: this describes `answers[2]`, not the input value `nums[2]`.

Your initial explanation considered inclusive definitions, then your actual
code settled on these exclusive definitions:

- `prefix[i]`: product strictly before index i, range `[0, i)`.
- `suffix[i]`: product strictly after index i, range `[i + 1, n)`.
- `answers[i] = prefix[i] * suffix[i]`.

An empty product is 1, so `prefix[0] = 1` and `suffix[n - 1] = 1`.
Your original implementation, with comments condensed and formatting normalized:

```kotlin
class Solution {
    fun productExceptSelf(nums: IntArray): IntArray {
        val n = nums.size
        val prefix = IntArray(n) { 1 }
        val suffix = IntArray(n) { 1 }

        for (i in 1 until n) {
            prefix[i] = prefix[i - 1] * nums[i - 1]
        }
        for (i in n - 2 downTo 0) {
            suffix[i] = suffix[i + 1] * nums[i + 1]
        }

        val answers = IntArray(n)
        for (i in 0 until n) {
            answers[i] = prefix[i] * suffix[i]
        }
        return answers
    }
}
```

For `[1,2,3,4]`, `prefix = [1,1,2,6]` and `suffix = [24,12,4,1]`.
Each recurrence extends the already computed product by one element. Their
two disjoint ranges cover every index except i, proving the answer formula.
The three finite passes each visit at most n indices: O(n) time and O(n)
auxiliary space. No extra slot is necessary under these definitions.

What to say:

> “I precompute products strictly before and after each index. Multiplying
> them gives the answer without including that element. Three linear passes
> take O(n) time, and the two helper arrays use O(n) extra space.”

### 3. Your improved implementation: output reuse and a running suffix

We then asked whether every intermediate product needs separate storage.
You recognized that `answers` can first hold prefix products. For suffixes,
you initially suggested starting with 24 and dividing out elements while
moving forward. Zeros prevent that approach. Instead, walk backward and
build the suffix by multiplication, starting from the empty product 1.

A “backward pass” means iterating right to left. “Maintain a running suffix”
means updating one variable so it keeps representing the product strictly
to the right of the current index at the start of each iteration.

Your resulting implementation:

```kotlin
class Solution {
    fun productExceptSelf(nums: IntArray): IntArray {
        val n = nums.size
        val answers = IntArray(n) { 1 }
        var suffix = 1
        for (i in 1 until n) {
            answers[i] = answers[i - 1] * nums[i - 1]
        }

        for (i in n - 1 downTo 0) {
            answers[i] = answers[i] * suffix
            suffix *= nums[i]
        }
        return answers
    }
}
```

You explained the update order: `nums[i]` must not be included in `suffix`
when calculating the current answer. Include it afterward, because it belongs
to the right side of the next index, i - 1.

Complete trace for `[1,2,3,4]`:

| Prefix step | answers after step |
| --- | --- |
| Initialize | `[1,1,1,1]` |
| i = 1 | `[1,1,1,1]` |
| i = 2 | `[1,1,2,1]` |
| i = 3; prefix pass ends | `[1,1,2,6]` |

Initialize `suffix = 1` before the backward pass.

| i | suffix before use | answers after multiplying current slot | suffix after multiplying nums[i] |
| --- | --- | --- | --- |
| 3 | 1 | `[1,1,2,6]` | 4 |
| 2 | 4 | `[1,1,8,6]` | 12 |
| 1 | 12 | `[1,12,8,6]` | 24 |
| 0 | 24 | `[24,12,8,6]` | 24 |

After i = 0, the loop ends and returns the completed array.

**Correctness invariant:** Before processing i backward, `answers[i]` still
holds the product strictly to its left, `suffix` holds the product strictly
to its right, and positions greater than i already hold final answers.
Multiplying gives the correct answer; updating `suffix` establishes its meaning
for i - 1. Each pass advances toward its bound and visits each relevant index
once, so the algorithm terminates in O(n) time.

**Why O(1) auxiliary space?** You correctly noticed that the prefix storage
still takes n slots. Those slots are the returned `answers` array. Excluding
the output, only a constant number of variables remain. Including output,
total additional space is O(n). The original version additionally allocated
two helper arrays, so its auxiliary space was O(n) even excluding output.

This improvement does not change the answer formula. It eliminates unnecessary
storage by reusing the output and computing suffix products one at a time.
“Simplify the formula” is natural English, but “eliminate unnecessary storage”
describes this change more precisely. “Remove redundant work” describes a
computation improvement.

| Approach | Time | Auxiliary space excluding output |
| --- | --- | --- |
| Scan all other elements for each i | O(n²) | O(1) |
| Separate prefix and suffix arrays | O(n) | O(n) |
| Prefixes in answers, running suffix | O(n) | O(1) |

## Boundary indexing: how to shift the arrays correctly

Your concern was the indexing: you wanted to avoid `n - 2` and the risk of
accessing `nums[i - 1]` at i = 0. Padding is a valid alternative, but first
define what each slot means. It is an indexing choice, not a further space
optimization over your running-suffix solution.

### Step 1: put indexes on the cuts between elements

Four elements have five boundaries:

```text
boundary:  0     1     2     3     4
           |  1  |  2  |  3  |  4  |
```

Boundary k lies after the first k elements and before `nums[k]` when k < n.
At boundary n, all elements are on the left. This convention is common for
prefix sums/products and also works for suffixes; it is not the only valid one.

### Step 2: define prefix by the left side of a boundary

`prefix[k]` is the product of the first k elements: range `[0, k)`.
The left endpoint is included and the right endpoint excluded.

You identified `prefix[3] = nums[0] * nums[1] * nums[2] = 6`.
Moving boundary 3 to boundary 4 adds `nums[3]`, so you derived:

```text
prefix[4] = prefix[3] * nums[3] = 24
prefix[i + 1] = prefix[i] * nums[i]
```

At boundary 0, nothing is on the left. You initially suggested zero; the
correction is `prefix[0] = 1`. Zero would make every later product zero.
The empty product is 1 because multiplying by 1 preserves a value; an empty
sum is 0 because adding 0 preserves a value.

### Step 3: define suffix by the right side of the same boundary

`suffix[k]` is the product of range `[k, n)`, including `nums[k]` when k < n.

```text
boundary 2: [1, 2] | [3, 4]     suffix[2] = 12
boundary 3: [1, 2, 3] | [4]     suffix[3] = 4
boundary 4: [1, 2, 3, 4] |      suffix[4] = 1
```

You recognized that only 4 belongs to `suffix[3]`. Moving the boundary left
adds `nums[2]`, giving the recurrence you supplied:

```text
suffix[2] = suffix[3] * nums[2]
suffix[i] = suffix[i + 1] * nums[i]
```

You then identified `suffix[4] = 1` for the empty right side.
**Definition change:** unlike your original exclusive suffix array, this
`suffix[i]` includes `nums[i]`. Do not mix the two conventions.

### Step 4: exclude an element with two neighboring boundaries

```text
                    nums[2]
                       ↓
             [1, 2] | 3 | [4]
                    ↑   ↑
             boundary 2 boundary 3
```

You derived `answers[2] = prefix[2] * suffix[3]`. In general:

```text
answers[i] = prefix[i] * suffix[i + 1]
```

The left range `[0, i)` and right range `[i + 1, n)` omit exactly index i.

### Step 5: choose loop directions from dependencies

You identified left to right for prefixes because `prefix[i]` must be ready,
and right to left for suffixes because `suffix[i + 1]` must be ready.

```kotlin
class Solution {
    fun productExceptSelf(nums: IntArray): IntArray {
        val n = nums.size
        val prefix = IntArray(n + 1) { 1 }
        val suffix = IntArray(n + 1) { 1 }

        for (i in 0 until n) {
            prefix[i + 1] = prefix[i] * nums[i]
        }
        for (i in n - 1 downTo 0) {
            suffix[i] = suffix[i + 1] * nums[i]
        }

        val answers = IntArray(n)
        for (i in 0 until n) {
            answers[i] = prefix[i] * suffix[i + 1]
        }
        return answers
    }
}
```

Both loops now read `nums[i]` directly. The last suffix slot and first prefix
slot supply the initial empty products, eliminating special boundary branches.

| Boundary k | prefix[k] | suffix[k] |
| --- | --- | --- |
| 0 | 1 | 24 |
| 1 | 1 | 24 |
| 2 | 2 | 12 |
| 3 | 6 | 4 |
| 4 | 24 | 1 |

At i = 0, the answer uses `prefix[0] * suffix[1]`; at i = n - 1,
it uses `prefix[n - 1] * suffix[n]`. Both are valid without branches.
This version takes O(n) time and O(n) auxiliary space.

The reusable derivation is: **define the range → define the empty boundary →
derive the recurrence → derive the answer indexes**. Padding alone does not
determine the formulas; the meaning assigned to each index does.

## Boundary examples and interview rehearsal

Expected examples from the product definition (not a report of executed tests):

| Input | Output | What it checks |
| --- | --- | --- |
| `[1,2,3,4]` | `[24,12,8,6]` | Ordinary case |
| `[0,2,3]` | `[6,0,0]` | One zero; no division needed |
| `[0,2,0]` | `[0,0,0]` | Two zeros |
| `[-1,2,-3]` | `[-6,3,-2]` | Negative signs |
| `[2,3]` | `[3,2]` | Empty sides at both ends |

> “For each index, I need the product before it times the product after it.
> Recomputing those products takes O(n²), so I reuse them. I first store
> exclusive prefix products in the output array. Then I walk backward with
> a running suffix initialized to 1. I use the suffix before multiplying in
> the current element, so that element is excluded from its own answer.
> This takes O(n) time and O(1) auxiliary space excluding the output.”

Recall questions: What repeated work do prefixes remove? Why must the suffix
update happen after writing the answer? Why do the loops terminate? Why is an
empty product 1? How does boundary-based `suffix[i]` differ from the original
exclusive definition? Why do we still allocate O(n) space when auxiliary space
excluding output is O(1)?
