#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-sample}"
case "$mode" in sample|stdin) ;; *) echo "Use sample or stdin" >&2; exit 1 ;; esac
mkdir -p .build
kotlinc Dijkstra.kt -include-runtime -d .build/dijkstra.jar
case "$mode" in
sample) java -jar .build/dijkstra.jar < sample.in ;;
stdin) java -jar .build/dijkstra.jar ;;
esac
