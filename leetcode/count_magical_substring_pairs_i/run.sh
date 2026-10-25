#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mkdir -p .build
for source in IntervalDpSolution.kt HistogramSolution.kt Solution.kt; do
    printf 'Testing %s\n' "$source"
    kotlinc "$source" Main.kt -include-runtime -d .build/tests.jar
    java -jar .build/tests.jar
done
