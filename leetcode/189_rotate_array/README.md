# 189. Rotate Array — Kotlin

`189.kt` preserves your copy-based algorithm, with immutable local variables,
a `for` loop, and an early return for no rotation. It is ready to paste into
LeetCode's Kotlin editor. `ReversalSolution.kt` implements the constant-space
follow-up separately; rename its class to `Solution` if submitting that version.
`CyclicSolution.kt` is the other constant-space alternative; likewise rename
its class to `Solution` when submitting it on its own.

Run from the repository root:

```sh
bash leetcode/189_rotate_array/run.sh
```

Or run `bash run.sh` inside the folder. VS Code also has **Terminal → Run Task →
Kotlin: test LeetCode 189**. All three algorithms run against the same test cases.

Copy your primary solution from the repository root:

```sh
pbcopy < leetcode/189_rotate_array/189.kt
```

See [PROOF.md](PROOF.md) for the three-reversal proof, including block diagrams,
index mapping, and correctness of the reversal helper.

See [CYCLIC_PROOF.md](CYCLIC_PROOF.md) for cyclic replacement: saving displaced
values, index-cycle diagrams, the loop invariant, and why all positions are covered.

See [EXPLANATION.md](EXPLANATION.md) for the derivation, trace, rotation approaches,
and interview wording. Inputs follow the supplied contract: nonempty array and
nonnegative `k`. Generated files stay in the ignored `.build/` directory.
