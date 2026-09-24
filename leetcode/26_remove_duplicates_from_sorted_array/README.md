# 26. Remove Duplicates from Sorted Array — Kotlin

Your submission is in `26.kt`; local tests are in `Main.kt`.

Run from the repository root:

```sh
bash leetcode/26_remove_duplicates_from_sorted_array/run.sh
```

Or run `bash run.sh` inside this folder. VS Code also provides **Terminal → Run
Task → Kotlin: test LeetCode 26**. Build output is ignored in `.build/`.

Copy to LeetCode's Kotlin editor from the repository root:

```sh
pbcopy < leetcode/26_remove_duplicates_from_sorted_array/26.kt
```

Only copy `26.kt`. The tests check the returned count and the exact ordered
prefix, ignoring the remaining array positions.

See [EXPLANATION.md](EXPLANATION.md) for solution evolution, interview wording,
and a trace of your implementation. The code assumes a nonempty sorted array,
as required by the [problem statement](https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/).
