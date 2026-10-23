#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mkdir -p .build
version="${1:-list}"
case "$version" in
list) source_file=Solution.kt ;;
matrix) source_file=MatrixSolution.kt ;;
heap) source_file=HeapSolution.kt ;;
spfa) source_file=SpfaSolution.kt ;;
*) echo "Use list, matrix, heap, or spfa" >&2; exit 1 ;;
esac
kotlinc "$source_file" Test.kt -include-runtime -d ".build/tests-$version.jar"
java -jar ".build/tests-$version.jar"
