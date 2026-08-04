#!/usr/bin/env bash
# Report control-flow protection and frame-pointer usage for every ELF object in
# the wheels under the given directory. Informational; never fails the build.
set -uo pipefail

WHEELHOUSE=${1:-wheelhouse}
TMP=$(mktemp -d); trap 'rm -rf "${TMP}"' EXIT

emit() { echo "$@"; [ -n "${GITHUB_STEP_SUMMARY:-}" ] && echo "$@" >> "${GITHUB_STEP_SUMMARY}"; }

emit "### Wheel hardening report"
emit ""
emit "| object | control-flow protection | frame pointers |"
emit "|---|---|---|"

shopt -s nullglob
for whl in "${WHEELHOUSE}"/*.whl; do
    d="${TMP}/$(basename "${whl}" .whl)"; mkdir -p "${d}"
    unzip -qq -o "${whl}" -d "${d}" || continue
    while IFS= read -r -d '' so; do
        file -b "${so}" | grep -q ELF || continue
        prop=$(readelf -nW "${so}" 2>/dev/null | grep -oE '(x86|AArch64) feature: .*' | head -1)
        fp=$(objdump -d --no-show-raw-insn -j .text "${so}" 2>/dev/null | awk '
            /^[0-9a-f]+ <.*>:$/ { total++; n=0; hit=0; push=0; next }
            NF==0 { next }
            { n++
              if (n<=4 && !hit) {
                  if ($0 ~ /push[ \t]+%rbp/)                  push=1
                  else if (push && $0 ~ /mov[ \t]+%rsp,%rbp/) { fp++; hit=1 }
                  if ($0 ~ /(mov|add)[ \t]+x29, ?sp/)         { fp++; hit=1 }
              } }
            END { if (total) printf "%d/%d (%.1f%%)", fp, total, 100*fp/total; else printf "n/a" }')
        emit "| \`$(basename "${so}")\` | ${prop:-**none**} | ${fp} |"
    done < <(find "${d}" -type f \( -name '*.so' -o -name '*.so.*' \) -print0)
done

emit ""
emit "Frame-pointer percentages are a disassembly heuristic: leaf functions and"
emit "functions touching no stack never get a frame pointer regardless of flags."
