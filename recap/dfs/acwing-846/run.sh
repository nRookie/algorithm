#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-test}"
case "$mode" in
  test|sample|stdin|build) ;;
  *) echo "Usage: bash run.sh [test|sample|stdin|build]" >&2; exit 1 ;;
esac
mkdir -p .build
kotlinc Solution.kt Main.kt Test.kt -include-runtime -d .build/846.jar
case "$mode" in
  test) java -cp .build/846.jar TestKt ;;
  sample) java -cp .build/846.jar MainKt < sample.in ;;
  stdin) java -cp .build/846.jar MainKt ;;
  build) echo "Starter compiled successfully." ;;
esac
