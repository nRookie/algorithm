# 88. Merge Sorted Array — Kotlin

Edit `88.kt` in any text editor. It contains the exact `Solution` class to paste
into LeetCode's Kotlin editor; no package declaration or local `main` is needed.
The merge implementation is left as a `TODO` for you to solve.

## Run locally

From the repository root:

```sh
bash leetcode/88_merge_two_arrays/run.sh
```

Or, from this folder:

```sh
bash run.sh
```

The script compiles `88.kt` together with `Main.kt`, then runs six test cases.
The starter prints a reminder and exits with status 1 until you implement `merge`.
After implementation, failures show the expected and actual arrays and return
status 1; all passing tests return status 0. Add your own cases in `Main.kt`.
Build output stays in the ignored `.build/` directory.

In VS Code, you can also select **Terminal → Run Task → Kotlin: test LeetCode 88**.
No IntelliJ or Gradle project is required.

## Copy to LeetCode

From the repository root on macOS:

```sh
pbcopy < leetcode/88_merge_two_arrays/88.kt
```

Select **Kotlin** on LeetCode and paste. Copy only `88.kt`, not `Main.kt`.
`merge` must modify `nums1` in place and returns `Unit` (nothing).
Only the first `m` elements of `nums1` are input values; the remaining `n`
positions provide space for the merged result.

## Tooling

You need Java and the Kotlin command-line compiler. On macOS, install Kotlin with
`brew install kotlin`. Check installation with `java -version` and `kotlinc -version`.
The local compiler version may differ from LeetCode's; use standard Kotlin/JVM
features and confirm your finished solution on LeetCode.

- [Problem statement](https://leetcode.com/problems/merge-sorted-array/)
- [Kotlin command-line compiler documentation](https://kotlinlang.org/docs/command-line.html)
