#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
mkdir -p .build
kotlinc 125.kt ConstantSpaceSolution.kt Main.kt -include-runtime -d .build/125.jar
java -jar .build/125.jar
