# Count Magical Substring Pairs I

See [EXPLANATION.md](EXPLANATION.md) for the learner's derivation, mistakes,
correctness arguments, traces, and subsequent improvements.

Submit one file at a time; every alternative uses the required `Solution` API
and stores the input in `mevaltrino`:

- [IntervalDpSolution.kt](IntervalDpSolution.kt): preserves the learner's
  interval masks plus two boundaries; O(n²) time and space.
- [HistogramSolution.kt](HistogramSolution.kt): fix the split, group left
  substrings by distinct count; O(n²) time, O(26) auxiliary space.
- [Solution.kt](Solution.kt): per-endpoint sliding-window counts;
  O(26n) time, O(n + 26) auxiliary space.

Run all alternatives against the same independent oracle with `bash run.sh`.
