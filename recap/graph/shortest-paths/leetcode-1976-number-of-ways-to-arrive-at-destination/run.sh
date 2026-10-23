#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mkdir -p .build
kotlinc Solution.kt Test.kt -include-runtime -d .build/tests.jar
java -jar .build/tests.jar
