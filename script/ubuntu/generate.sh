#!/bin/bash

rm -rf marimbash

set -euo pipefail

BASE_PATH="$(dirname "$0")/../.."
cd "$BASE_PATH"

INPUT="$1"
shift 1
cat "$INPUT" | build/Compiler "$@"
cd marimbash
mvn clean install 
mvn compile exec:java -Dexec.mainClass=org.marimbash.MarimbaMusic

