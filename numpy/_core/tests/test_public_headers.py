"""Structural invariants of the installed public C headers.

These are deliberately cheap text checks that need no compiler. The regression
they guard against shipped in 2.4.5 precisely because nothing in CI compiles the
public headers with a compiler that disagrees with MSVC about complex types:
``npy_common.h`` stopped using the MSVC runtime's ``_Dcomplex`` & co. for the
Intel LLVM compilers, while ``npy_math.h`` kept calling the runtime's
``creal()``, which is declared as taking ``_Dcomplex`` no matter which front end
compiles it. The result was that ``#include <numpy/npy_math.h>`` no longer
compiled on its own.
"""
import pathlib
import re

import pytest

import numpy as np

# Headers are included as `<numpy/npy_math.h>`, so `get_include()` is their parent.
HEADER_DIR = pathlib.Path(np.get_include()) / "numpy"


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


def test_complex_typedefs_follow_the_c_runtime():
    block = _block(
        _read_header("npy_common.h"),
        "#define NPY_SIZEOF_HASH_T NPY_SIZEOF_INTP",
        "numarray-style bit-width typedefs",
    )

    assert "_MSC_VER" in block, (
        "npy_common.h no longer selects the complex typedefs on `_MSC_VER`; "
        "the choice must follow the C runtime"
    )
    assert "__INTEL_LLVM_COMPILER" not in block, (
        "npy_common.h exempts `__INTEL_LLVM_COMPILER` from the MSVC runtime's "
        "complex types. Which of them exist is a property of the C runtime, "
        "not of the compiler front end - exempting a front end leaves "
        "`npy_cdouble` as `double _Complex` while npy_math.h keeps calling the "
        "runtime's `creal(_Dcomplex)`, so `#include <numpy/npy_math.h>` stops "
        "compiling with icx on Windows."
    )
