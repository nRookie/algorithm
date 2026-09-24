# 27. Remove Element — Kotlin

Implement `removeElement` in `27.kt`. Return the number `k` of values not equal
to `val`, placing those values in the first `k` positions of `nums`.
Their order does not matter, and positions after that prefix are ignored.
Kotlin arrays have fixed length; you do not need to physically shrink the array.
The backticks around `val` allow a Kotlin keyword to be used as a parameter name.

From the repository root, run:

```sh
bash leetcode/27_remove_element/run.sh
```

Or run `bash run.sh` from this folder. In VS Code, select **Terminal → Run Task →
Kotlin: test LeetCode 27**.

`Main.kt` checks eight cases, validating both the returned count and the retained
values, including duplicate counts. It accepts any order and ignores the unused
tail. Add more cases there as you practice.

The starter compiles but exits with status 1 and an implementation reminder until
you replace `TODO`. Completed solutions exit with status 0 only if all tests pass.
Generated files stay in the ignored `.build/` folder.

Copy only the submission file into LeetCode's Kotlin editor:

```sh
pbcopy < leetcode/27_remove_element/27.kt
```

Run that copy command from the repository root. Keep the local `Main.kt` separate
from your submission. The algorithm is left for you to practice.
