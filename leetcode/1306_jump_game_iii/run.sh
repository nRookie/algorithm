#!/usr/bin/env bash
set -euo pipefail

cd -- "$(dirname -- "$0")"
mkdir -p .build
kotlinc 1306.kt Main.kt -include-runtime -d .build/1306.jar
java -jar .build/1306.jar
