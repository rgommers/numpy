/*
 * Prototypes for C99 complex-math functions probed as a batch by meson.build.
 *
 * For the MSVC runtime we must include <complex.h> to pick up the non-standard
 * _Fcomplex/_Dcomplex/_Lcomplex typedefs, since that runtime doesn't provide the C99
 * `_Complex` types. For every other compiler we avoid including <complex.h> so that
 * macro-based declarations (notably musl's `#define crealf(x) ((float)(x))`) don't
 * conflict with the plain prototypes below.
 *
 * The condition below must be kept in sync by hand with the complex typedefs in
 * `include/numpy/npy_common.h`; this file is compiled standalone by the meson probes,
 * so it cannot use `NPY_CPLX_IS_STRUCT`. In particular, do not add compiler front-end
 * exemptions here - which runtime provides which types is not a front-end property.
 */

#if defined(_MSC_VER)
#include <complex.h>
typedef _Fcomplex cfloat;
typedef _Dcomplex cdouble;
typedef _Lcomplex cldouble;
#else
typedef float  _Complex cfloat;
typedef double _Complex cdouble;
typedef long double _Complex cldouble;
#endif

/* Mandatory complex math (double) */
cdouble csin(cdouble);
cdouble csinh(cdouble);
cdouble ccos(cdouble);
cdouble ccosh(cdouble);
cdouble ctan(cdouble);
cdouble ctanh(cdouble);
double         creal(cdouble);
double         cimag(cdouble);
cdouble conj(cdouble);

/* float variants */
cfloat  csinf(cfloat);
cfloat  csinhf(cfloat);
cfloat  ccosf(cfloat);
cfloat  ccoshf(cfloat);
cfloat  ctanf(cfloat);
cfloat  ctanhf(cfloat);
float          crealf(cfloat);
float          cimagf(cfloat);
cfloat  conjf(cfloat);

/* long double variants */
cldouble csinl(cldouble);
cldouble csinhl(cldouble);
cldouble ccosl(cldouble);
cldouble ccoshl(cldouble);
cldouble ctanl(cldouble);
cldouble ctanhl(cldouble);
long double     creall(cldouble);
long double     cimagl(cldouble);
cldouble conjl(cldouble);

/* C99 complex (double) */
double         cabs(cdouble);
cdouble cacos(cdouble);
cdouble cacosh(cdouble);
double         carg(cdouble);
cdouble casin(cdouble);
cdouble casinh(cdouble);
cdouble catan(cdouble);
cdouble catanh(cdouble);
cdouble cexp(cdouble);
cdouble clog(cdouble);
cdouble cpow(cdouble, cdouble);
cdouble csqrt(cdouble);

/* C99 complex (float) */
float          cabsf(cfloat);
cfloat  cacosf(cfloat);
cfloat  cacoshf(cfloat);
float          cargf(cfloat);
cfloat  casinf(cfloat);
cfloat  casinhf(cfloat);
cfloat  catanf(cfloat);
cfloat  catanhf(cfloat);
cfloat  cexpf(cfloat);
cfloat  clogf(cfloat);
cfloat  cpowf(cfloat, cfloat);
cfloat  csqrtf(cfloat);

/* C99 complex (long double) */
long double     cabsl(cldouble);
cldouble cacosl(cldouble);
cldouble cacoshl(cldouble);
long double     cargl(cldouble);
cldouble casinl(cldouble);
cldouble casinhl(cldouble);
cldouble catanl(cldouble);
cldouble catanhl(cldouble);
cldouble cexpl(cldouble);
cldouble clogl(cldouble);
cldouble cpowl(cldouble, cldouble);
cldouble csqrtl(cldouble);
