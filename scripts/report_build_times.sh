#!/usr/bin/env bash
set -euo pipefail

# Reports the N slowest build steps from a Ninja build, using the build
# directory's .ninja_log. A build-performance regression signal: catches
# "someone added a header that balloons compile time across the project"
# before it quietly becomes an ignored slow-CI problem.

BUILD_DIR="${1:-build}"
TOP_N="${2:-10}"
LOG_FILE="${BUILD_DIR}/.ninja_log"

if [[ ! -f "$LOG_FILE" ]]; then
    echo "error: no ninja log found at $LOG_FILE (did you build with Ninja?)" >&2
    exit 1
fi

echo "Top ${TOP_N} slowest build steps in ${BUILD_DIR}:"
echo

tail -n +2 "$LOG_FILE" \
    | awk -F'\t' '{ printf "%.2fs\t%s\n", ($2 - $1) / 1000, $4 }' \
    | sort -rn \
    | head -n "$TOP_N"
