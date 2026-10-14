#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mode="${1:-sample}"
representation="${2:-matrix}"
case "$mode" in sample|stdin) ;; *) echo "Use sample or stdin" >&2; exit 1 ;; esac
case "$representation" in
matrix) source_file=Main.kt ;;
list) source_file=AdjacencyList.kt ;;
*) echo "Use matrix or list as the second argument" >&2; exit 1 ;;
esac
mkdir -p .build
jar=".build/dijkstra-$representation.jar"
kotlinc "$source_file" -include-runtime -d "$jar"
case "$mode" in
sample) java -jar "$jar" < sample.in ;;
stdin) java -jar "$jar" ;;
esac
