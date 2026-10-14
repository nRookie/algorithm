#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-sample}"
case "$mode" in sample|stdin) ;; *) echo "Use sample or stdin" >&2; exit 1 ;; esac
mkdir -p .build
kotlinc Main.kt -include-runtime -d .build/1129.jar
case "$mode" in
sample) java -jar .build/1129.jar < sample.in ;;
stdin) java -jar .build/1129.jar ;;
esac
