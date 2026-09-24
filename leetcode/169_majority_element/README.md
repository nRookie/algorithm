# 169. Majority Element — Kotlin

Run from the repository root:

```sh
bash leetcode/169_majority_element/run.sh
```

Inside this folder, use `bash run.sh`. VS Code provides **Terminal → Run Task →
Kotlin: test LeetCode 169**. Generated files stay in the ignored `.build/` folder.

Copy only the submission file to LeetCode's Kotlin editor:

```sh
pbcopy < leetcode/169_majority_element/169.kt
```

Run the copy command from the repository root. `Main.kt` contains named tests
and an exhaustive small-input check against a frequency-map oracle. All tested
inputs are nonempty and have a strict majority, matching the supplied contract.

The executable uses the standard Boyer–Moore update order, adapted from your
proposal. See [EXPLANATION.md](EXPLANATION.md) for the exact changes, original
version, solution evolution, and step-by-step trace.
