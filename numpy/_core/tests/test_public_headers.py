"""Structural invariants of the installed public C headers.

These are deliberately cheap text checks that need no compiler. The regression
they guard against shipped in 2.4.5 precisely because nothing in CI compiles the
public headers with a compiler that disagrees with MSVC about complex types:
``npy_common.h`` stopped using the MSVC runtime's ``_Dcomplex`` & co. for the
Intel compilers, while ``npy_math.h`` kept calling the UCRT's ``creal()``, which
is declared as taking ``_Dcomplex`` no matter which front end compiles it. The
result was that ``#include <numpy/npy_math.h>`` no longer compiled on its own.
"""
import pathlib
import re

import pytest

import numpy as np

# Headers are included as `<numpy/npy_math.h>`, so `get_include()` is their parent.
HEADER_DIR = pathlib.Path(np.get_include()) / "numpy"

# Compiler front-end macros that must not influence the complex typedefs. Which
# complex types exist is a property of the C runtime, not of the front end, and
# every compiler targeting a given runtime has to agree - otherwise the ~60
# npymath functions taking or returning these types by value silently change
# signature between NumPy's own build and a downstream extension's.
FRONTEND_MACROS = (
    "__INTEL_COMPILER",
    "__INTEL_LLVM_COMPILER",
    "__clang__",
    "__GNUC__",
    "_M_ARM64",
)


def _read_header(name):
    path = HEADER_DIR / name
    if not path.is_file():
        pytest.skip(f"{name} not found in {HEADER_DIR}")
    return path.read_text(encoding="utf-8")


def _block(text, start, end):
    """Return the slice of `text` from `start` up to the next `end`.

    Comments are stripped: the invariants below are about the preprocessor
    conditions, and the comments explaining them necessarily name the macros
    that must not appear in the code.
    """
    first = text.index(start)
    block = text[first:text.index(end, first)]
    block = re.sub(r"/\*.*?\*/", " ", block, flags=re.DOTALL)
    return re.sub(r"//[^\n]*", " ", block)


def test_complex_typedefs_key_only_on_the_c_runtime():
    block = _block(
        _read_header("npy_common.h"),
        "#define NPY_SIZEOF_HASH_T NPY_SIZEOF_INTP",
        "numarray-style bit-width typedefs",
    )

    assert "_MSC_VER" in block, (
        "npy_common.h no longer selects the complex typedefs on `_MSC_VER`; "
        "the choice must follow the C runtime"
    )
    for macro in FRONTEND_MACROS:
        assert macro not in block, (
            f"npy_common.h keys the complex typedefs on `{macro}`. Only "
            "`_MSC_VER` (i.e. the C runtime) may be used here - a front-end "
            "specific exemption breaks `#include <numpy/npy_math.h>` and "
            "changes the ABI of the shipped npymath static library."
        )
    # Once for the C++ path, once for the MSVC runtime path.
    assert block.count("#define NPY_CPLX_IS_STRUCT") == 2


def test_complex_accessors_key_off_the_shared_macro():
    block = _block(
        _read_header("npy_math.h"),
        "static inline double npy_creal(const npy_cdouble z)",
        "static inline npy_cdouble npy_cpack(double x, double y)",
    )

    # npy_creal, npy_cimag, npy_crealf, npy_cimagf, npy_creall, npy_cimagl
    assert block.count("#ifdef NPY_CPLX_IS_STRUCT") == 6, (
        "each of the six complex accessors in npy_math.h must branch on "
        "`NPY_CPLX_IS_STRUCT`"
    )
    for macro in ("_MSC_VER", "__cplusplus", *FRONTEND_MACROS):
        assert macro not in block, (
            f"npy_math.h re-derives the complex typedef choice from `{macro}`. "
            "It must branch on `NPY_CPLX_IS_STRUCT` instead, so that the "
            "accessors can never disagree with the typedefs in npy_common.h."
        )


def test_feature_detection_cmath_stays_in_sync():
    # Not an installed header - it is compiled standalone by the meson probes,
    # so it cannot use NPY_CPLX_IS_STRUCT and has to be kept in sync by hand.
    path = pathlib.Path(np.__file__).parent / "_core" / "feature_detection_cmath.h"
    if not path.is_file():
        pytest.skip("feature_detection_cmath.h is not shipped in wheels")

    block = _block(path.read_text(encoding="utf-8"), "#if defined(", "typedef float")
    assert "_MSC_VER" in block
    for macro in FRONTEND_MACROS:
        assert macro not in block, (
            f"feature_detection_cmath.h keys its complex typedefs on `{macro}`; "
            "keep it in sync with npy_common.h"
        )
