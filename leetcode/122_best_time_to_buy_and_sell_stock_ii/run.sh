#!/usr/bin/env bash
set -euo pipefail

cd -- "$(dirname -- "$0")"
if ! command -v kotlinc >/dev/null 2>&1; then
    echo 'Kotlin compiler missing. Install it with: brew install kotlin' >&2
    exit 1
fi

mkdir -p .build
kotlinc 122.kt Main.kt -include-runtime -d .build/122.jar
java -jar .build/122.jar
