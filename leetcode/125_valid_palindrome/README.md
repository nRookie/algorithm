# 125. Valid Palindrome — Kotlin

[Official problem](https://leetcode.com/problems/valid-palindrome/).
Ignore non-alphanumeric characters and letter case, then check whether the
remaining sequence reads the same forward and backward. Official inputs contain
1 through 200,000 printable ASCII characters.

| Input | Result | Normalized text |
| --- | --- | --- |
| `"A man, a plan, a canal: Panama"` | `true` | `amanaplanacanalpanama` |
| `"race a car"` | `false` | `raceacar` |
| `" "` | `true` | empty |

[125.kt](125.kt) preserves your implementation with comment/spacing cleanup.
[ConstantSpaceSolution.kt](ConstantSpaceSolution.kt) is a separate follow-up;
rename its class to `Solution` when submitting that version.
[EXPLANATION.md](EXPLANATION.md) covers the review and interview practice.
[STREAM_INTERVIEW.md](STREAM_INTERVIEW.md) records our mock interview on finite
streams, buffering, compression limits, and comparison using disk blocks.

Run from the repository root:

```sh
bash leetcode/125_valid_palindrome/run.sh
```

Build output stays in the locally ignored `.build/` directory.
