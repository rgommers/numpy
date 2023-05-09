#include <sys/cdefs.h>

#define __TEMPLATE_FUNC(func)       __CONCAT(func,$LEGACY)
#define __TEMPLATE_ALIAS(sym)       __asm("_" __STRING(sym))

#include "lapack/accelerate_legacy_blas.h"
#include "lapack/accelerate_legacy_cblas.h"
#include "lapack/accelerate_legacy_lapack.h"

#undef __TEMPLATE_FUNC
#undef __TEMPLATE_ALIAS