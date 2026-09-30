# Learning to prove why algorithms work

The skill to practice is turning an observation into a general proof: explain
why an algorithm works for every allowed input, not only the examples tested.

## Mathematical ideas from our reversal discussion

| Idea | How we used it |
| --- | --- |
| Direct proof | Start from definitions and derive the desired result. |
| Reasoning about an arbitrary element | Follow any valid index i, rather than a particular index such as 2. |
| Function composition | Describe reversal as f(i), then two reversals as f(f(i)). |
| Involution | An operation that is its own inverse: applying it twice restores the original object. |

Direct proof is the proof method. Involution is the property we proved for reversal.

## A reusable process

### 1. State precisely what you want to prove

Instead of “reversal works,” write:

> For every nonempty sequence of length L and every valid index i, reversing
> twice returns the element originally at i to its original position.

State the assumptions too: indexes start at zero, and `0 <= i < L`.
For an empty sequence, reversing twice trivially leaves it empty.

### 2. Use examples to discover a relationship

For length 5, reversal changes indexes as follows:

```text
0 → 4
1 → 3
2 → 2
3 → 1
4 → 0
```

Each original index and destination add to 4. This suggests the formula
`destination = L - 1 - i`.

Examples help discover a pattern; they do not establish it for every length.
A single valid counterexample can disprove a universal claim, while many passing
examples generally cannot prove it.

### 3. Derive the relationship from the definition

Index i is i steps from the beginning. Reversal puts that element i steps from
the end. Since the last index is `L - 1`, the destination is:

```text
f(i) = L - 1 - i
```

This follows from the meaning of reversal, not just the observed example.
The formula also produces a valid index: `0 <= L - 1 - i < L`.

### 4. Follow an arbitrary element

Let i be any valid index. Apply the same transformation twice:

```text
f(f(i))
= L - 1 - (L - 1 - i)
= i
```

We did not assume a particular value of i or L. The calculation applies to every
valid index in every nonempty sequence.

“Arbitrary” is not “randomly selected.” An arbitrary index stands for any index;
the argument may use only the stated assumptions, not special properties of a
convenient example. Even when array values repeat, we can follow their original
positions separately.

### 5. Connect the result back to the claim

Every element returns to its original position. Therefore the entire sequence
is restored by two reversals.

Do not stop at the algebra: explain why it establishes the property you wanted.

## How this connects to the three-reversal algorithm

Let A be the first n-s elements and B the last s, where `s = k % n`.
A right rotation should transform A B into B A. Write R(X) for reversing X.

```text
A B → R(B) R(A) → B R(A) → B A
```

The first step uses `R(A B) = R(B) R(A)`: reading the joined sequence backward
encounters B backward, then A backward. The next two steps use `R(R(X)) = X`.
Because A and B are arbitrary blocks, this is a general direct proof.

Read [PROOF.md](PROOF.md) for the full block proof, independent index proof,
and correctness argument for the reversal helper.

## When the algorithm contains a loop

Ask what remains true after every iteration. That property is a loop invariant.
For example, in Remove Element, the prefix before the write pointer contains
exactly the retained elements from the input already scanned.

To use an invariant in a correctness proof:

1. **Initialization:** show it holds before the first iteration.
2. **Maintenance:** assume it holds before an iteration and show the body preserves it.
3. **Result at exit:** combine the invariant with the false loop condition to obtain the desired result.
4. **Termination:** show that the loop actually stops, for example because an index advances toward a fixed bound.

Initialization and maintenance are an application of mathematical induction
over the number of iterations. An invariant alone does not prove termination.

## Reading references

### First: direct proof and definitions

[Richard Hammack — Book of Proof](https://richardhammack.github.io/BookOfProof/)

Start with Chapter 4, “Direct Proof,” especially the sections on definitions,
direct proof, and cases. Work through exercises, writing why each step follows.
If the logical notation is unfamiliar, consult the earlier logic material.
Later, study mathematical induction to support reasoning about loops and recursion.

### Next: connect proofs to programs

[Cornell CS 2112 — Loop Invariants](https://www.cs.cornell.edu/courses/cs2112/2021fa/lectures/lecture.html?id=loopinv)

Study initialization, preservation, the result at loop exit, and termination.
Apply those ideas to one of your existing two-pointer implementations.

### Optional terminology: self-inverse operations

[Wolfram MathWorld — Involution](https://mathworld.wolfram.com/Involution.html)

Reversal is an example of an operation that undoes itself. The terminology is
useful, but understanding the index argument matters more than memorizing the name.

## Practice with our existing problems

- **Reversal:** derive why reversing an inclusive interval [a,b] sends index i
  to `a + b - i`; then prove a second reversal restores i.
- **Remove Element:** state exactly what the prefix before `left` contains and
  explain why writing there cannot overwrite unread input.
- **Remove Duplicates:** explain which sorted-input property lets one comparison
  decide whether a value should be kept.
- **Majority Element:** show why deleting two unequal values preserves a strict
  majority, then connect that fact to the vote balance.

For each algorithm, ask:

> Can I explain what happens to an arbitrary element, or what remains true
> after every iteration?

Use examples to build intuition, a general argument to establish correctness,
and tests to check that the implementation matches that argument.
