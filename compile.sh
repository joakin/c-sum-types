#!/bin/bash
set -euo pipefail

case "${1:-}" in
expand)
  # -E: preprocess only (expand macros), -P: suppress linemarkers
  clang -E -P main.c
  ;;
expand-and-compile)
  # -E: preprocess only, pipe to... -fsyntax-only: parse+typecheck only,
  # -x c: force C language, -: read from stdin
  clang -E main.c | clang -fsyntax-only -x c -
  ;;
"")
  clang -o main main.c && ./main
  ;;
*)
  echo "Usage: $0 [expand|expand-and-compile]"
  exit 1
  ;;
esac
