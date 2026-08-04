#!/usr/bin/env bash
# Install a GCC "specs" file inside the build container so frame pointers and
# control-flow protection become the *compiler default* for everything built
# afterwards: numpy's own sources, vendored static libraries, everything.
#
# Deliberately does NOT touch CFLAGS/CXXFLAGS -- nothing appears on any command
# line, so nothing leaks into a consumer's build and nothing breaks a non-GCC
# compiler. Explicit user flags always win (see the %{!flag:...} guards).
#
# Experiment only -- see https://discuss.python.org/t/building-extensions-with-hardening-flags-via-manylinux/108354
set -euo pipefail

command -v gcc > /dev/null || { echo "hardening-specs: no gcc, skipping"; exit 0; }

case "$(uname -m)" in
    x86_64|i686)   CF='%{!fcf-protection*:-fcf-protection=full}' ;;
    aarch64|arm64) CF='%{!mbranch-protection*:-mbranch-protection=standard}' ;;
    *)             CF='' ;;
esac

# -momit-leaf-frame-pointer is x86/arm/aarch64-only in GCC; probe it.
LEAF=''
if echo 'int main(void){return 0;}' |
        gcc -Werror -mno-omit-leaf-frame-pointer -x c -c -o /dev/null - 2>/dev/null; then
    LEAF='%{!momit-leaf-frame-pointer:%{!mno-omit-leaf-frame-pointer:-mno-omit-leaf-frame-pointer}}'
fi

SPEC_FILE="$(dirname "$(gcc -print-libgcc-file-name)")/specs"
echo "hardening-specs: gcc=$(readlink -f "$(command -v gcc)") -> ${SPEC_FILE}"

# Append; never clobber a vendor-supplied specs file.
{
    printf '\n*cc1_options:\n'
    printf '+ %%{!fomit-frame-pointer:%%{!fno-omit-frame-pointer:-fno-omit-frame-pointer}}'
    printf ' %s %s\n' "${LEAF}" "${CF}"
} >> "${SPEC_FILE}"

# Fail loudly rather than silently shipping an unhardened wheel.
printf 'int g(int);\nint probe(int x){return g(x)+1;}\n' > /tmp/_probe.c
gcc -O2 -fPIC -c /tmp/_probe.c -o /tmp/_probe.o

objdump -d --no-show-raw-insn /tmp/_probe.o |
    grep -qE 'mov[[:space:]]+%rsp,%rbp|(mov|add)[[:space:]]+x29, ?sp' || {
        echo "hardening-specs: ERROR - frame pointer default did not take effect" >&2; exit 1; }

if [ -n "${CF}" ]; then
    readelf -nW /tmp/_probe.o | grep -qE '(x86|AArch64) feature:' || {
        echo "hardening-specs: ERROR - control-flow protection did not take effect" >&2; exit 1; }
fi

echo "hardening-specs: verified"
readelf -nW /tmp/_probe.o | grep -E '(x86|AArch64) feature:' || true
