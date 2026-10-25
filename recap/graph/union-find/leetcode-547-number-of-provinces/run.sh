#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
case "${1:-seen}" in
seen) source_file=Solution.kt ;;
components) source_file=ComponentCountSolution.kt ;;
*) echo "Use seen or components" >&2; exit 1 ;;
esac
mkdir -p .build
kotlinc "$source_file" Test.kt -include-runtime -d .build/tests.jar
java -jar .build/tests.jar
