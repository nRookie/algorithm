# LeetCode 2049 — Count Nodes With the Highest Score

Online judge: [LeetCode problem 2049](https://leetcode.com/problems/count-nodes-with-the-highest-score/).
Topic: DFS, subtree sizes, components after removing a node.

- [Your recursive implementation](LearnerSolution.kt)
- [Your polished explanation and interview wording](LEARNER_EXPLANATION.md)
- [Iterative implementation for deep trees](Solution.kt)
- [Full algorithm explanation](EXPLANATION.md)
- [Relationship to AcWing 846](SOURCE.md)

Both Kotlin implementations use LeetCode's `class Solution` and
`countHighestScoreNodes(parents: IntArray): Int` signature. Submit or compile
one implementation at a time. The recursive version passed small local checks
but overflowed the JVM call stack on a 100,000-node chain.

Run the iterative solution's tests from this folder with `bash run.sh`.
The recursive version's test instructions are in its explanation.
