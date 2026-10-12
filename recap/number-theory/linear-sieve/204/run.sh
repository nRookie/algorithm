#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
build_dir=$(mktemp -d "${TMPDIR:-/tmp}/linear-sieve.XXXXXX")
trap 'rm -rf -- "$build_dir"' EXIT
kotlinc Solution.kt Test.kt -include-runtime -d "$build_dir/recap.jar"
java -Xmx256m -cp "$build_dir/recap.jar" TestKt
