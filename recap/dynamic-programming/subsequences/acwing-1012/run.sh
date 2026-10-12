#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-sample}"
case "$mode" in sample|stdin|test) ;; *) echo "Use sample, stdin, or test" >&2; exit 1 ;; esac
mkdir -p .build
kotlinc Main.kt -include-runtime -d .build/1012.jar
case "$mode" in
sample) java -jar .build/1012.jar < sample.in ;;
stdin) java -jar .build/1012.jar ;;
test) python3 test.py ;;
esac
