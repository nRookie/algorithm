#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-sample}"
case "$mode" in sample|stdin|test) ;; *) echo "Use sample, stdin, or test" >&2; exit 1 ;; esac
mkdir -p .build
kotlinc Solution.kt Main.kt Test.kt -include-runtime -d .build/1017.jar
case "$mode" in
sample) java -cp .build/1017.jar MainKt < sample.in ;;
stdin) java -cp .build/1017.jar MainKt ;;
test) java -cp .build/1017.jar TestKt ;;
esac
