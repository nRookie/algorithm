#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-stdin}"
case "$mode" in
    stdin|sample|build|test) ;;
    *) echo "Usage: bash run.sh [stdin|sample|build|test]" >&2; exit 1 ;;
esac
mkdir -p .build
kotlinc Main.kt -include-runtime -d .build/104.jar
case "$mode" in
    stdin) java -jar .build/104.jar ;;
    sample) java -jar .build/104.jar < sample.in ;;
    build) echo "Compiled .build/104.jar" ;;
    test) python3 test.py ;;
esac
