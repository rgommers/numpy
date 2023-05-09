#include <Accelerate/Accelerate.h>
#include "npy_blas_lapack.h"
#include "lapack/accelerate_legacy.h"

void
accelerate_sgeev
(
    char *jobvl,
    char *jobvr,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    float wr[],
    float wi[],
    float vl[],
    fortran_int *ldvl,
    float vr[],
    fortran_int *ldvr,
    float work[],
    fortran_int lwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        sgeev_(jobvl, jobvr, n, a, lda, wr, wi, vl, ldvl, vr, ldvr, work, lwork, info);
    } else {
        sgeev$LEGACY(jobvl, jobvr, n, a, lda, wr, wi, vl, ldvl, vr, ldvr, work, lwork, info);
    }
}

void
accelerate_dgeev
(
    char *jobvl,
    char *jobvr,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    double wr[],
    double wi[],
    double vl[],
    fortran_int *ldvl,
    double vr[],
    fortran_int *ldvr,
    double work[],
    fortran_int lwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgeev_(jobvl, jobvr, n, a, lda, wr, wi, vl, ldvl, vr, ldvr, work, lwork, info);
    } else {
        dgeev$LEGACY(jobvl, jobvr, n, a, lda, wr, wi, vl, ldvl, vr, ldvr, work, lwork, info);
    }
}

void
accelerate_cgeev
(
    char *jobvl,
    char *jobvr,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    f2c_complex w[],
    f2c_complex vl[],
    fortran_int *ldvl,
    f2c_complex vr[],
    fortran_int *ldvr,
    f2c_complex work[],
    fortran_int *lwork,
    float rwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cgeev_(jobvl, jobvr, n, a, lda, w, vl, ldvl, vr, ldvr, work, lwork, rwork, info);
    } else {
        cgeev$LEGACY(jobvl, jobvr, n, a, lda, w, vl, ldvl, vr, ldvr, work, lwork, rwork, info);
    }
}

void
accelerate_zgeev
(
    char *jobvl,
    char *jobvr,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    f2c_doublecomplex w[],
    f2c_doublecomplex vl[],
    fortran_int *ldvl,
    f2c_doublecomplex vr[],
    fortran_int *ldvr,
    f2c_doublecomplex work[],
    fortran_int *lwork,
    double rwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgeev_(jobvl, jobvr, n, a, lda, w, vl, ldvl, vr, ldvr, work, lwork, rwork, info);
    } else {
        zgeev$LEGACY(jobvl, jobvr, n, a, lda, w, vl, ldvl, vr, ldvr, work, lwork, rwork, info);
    }
}

void
accelerate_ssyevd
(
    char *jobz,
    char *uplo,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    float w[],
    float work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *liwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        ssyevd_(jobz, uplo, n, a, lda, w, work, lwork, iwork, liwork, info);
    } else {
        ssyevd$LEGACY(jobz, uplo, n, a, lda, w, work, lwork, iwork, liwork, info);
    }
}

void
accelerate_dsyevd
(
    char *jobz,
    char *uplo,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    double w[],
    double work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *liwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dsyevd_(jobz, uplo, n, a, lda, w, work, lwork, iwork, liwork, info);
    } else {
        dsyevd$LEGACY(jobz, uplo, n, a, lda, w, work, lwork, iwork, liwork, info);
    }
}

void
accelerate_cheevd
(
    char *jobz,
    char *uplo,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    float w[],
    f2c_complex work[],
    fortran_int *lwork,
    float rwork[],
    fortran_int *lrwork,
    fortran_int iwork[],
    fortran_int *liwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cheevd_(jobz, uplo, n, a, lda, w, work, lwork, rwork, lrwork, iwork, liwork, info);
    } else {
        cheevd$LEGACY(jobz, uplo, n, a, lda, w, work, lwork, rwork, lrwork, iwork, liwork, info);
    }
}

void
accelerate_zheevd
(
    char *jobz,
    char *uplo,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    double w[],
    f2c_doublecomplex work[],
    fortran_int *lwork,
    double rwork[],
    fortran_int *lrwork,
    fortran_int iwork[],
    fortran_int *liwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zheevd_(jobz, uplo, n, a, lda, w, work, lwork, rwork, lrwork, iwork, liwork, info);
    } else {
        zheevd$LEGACY(jobz, uplo, n, a, lda, w, work, lwork, rwork, lrwork, iwork, liwork, info);
    }
}

void
accelerate_sgelsd
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *nrhs,
    float a[],
    fortran_int *lda,
    float b[],
    fortran_int *ldb,
    float s[],
    float *rcond,
    fortran_int *rank,
    float work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        sgelsd_(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, iwork, info);
    } else {
        sgelsd$LEGACY(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, iwork, info);
    }
}

void
accelerate_dgelsd
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *nrhs,
    double a[],
    fortran_int *lda,
    double b[],
    fortran_int *ldb,
    double s[],
    double *rcond,
    fortran_int *rank,
    double work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgelsd_(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, iwork, info);
    } else {
        dgelsd$LEGACY(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, iwork, info);
    }
}

void
accelerate_cgelsd
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *nrhs,
    f2c_complex a[],
    fortran_int *lda,
    f2c_complex b[],
    fortran_int *ldb,
    float s[],
    float *rcond,
    fortran_int *rank,
    f2c_complex work[],
    fortran_int *lwork,
    float rwork[],
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cgelsd_(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, rwork, iwork, info);
    } else {
        cgelsd$LEGACY(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, rwork, iwork, info);
    }
}

void
accelerate_zgelsd
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *nrhs,
    fortran_doublecomplex a[],
    fortran_int *lda,
    fortran_doublecomplex b[],
    fortran_int *ldb,
    double s[],
    double *rcond,
    fortran_int *rank,
    fortran_doublecomplex work[],
    fortran_int *lwork,
    double rwork[],
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgelsd_(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, rwork, iwork, info);
    } else {
        zgelsd$LEGACY(m, n, nrhs, a, lda, b, ldb, s, rcond, rank, work, lwork, rwork, iwork, info);
    }
}

void
accelerate_dgeqrf
(
    fortran_int *m,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    double tau[],
    double work[],
    fortran_int *lwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgeqrf_(m, n, a, lda, tau, work, lwork, info);
    } else {
        dgeqrf$LEGACY(m, n, a, lda, tau, work, lwork, info);
    }
}

void
accelerate_zgeqrf
(
    fortran_int *m,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    f2c_doublecomplex tau[],
    f2c_doublecomplex work[],
    fortran_int *lwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgeqrf_(m, n, a, lda, tau, work, lwork, info);
    } else {
        zgeqrf$LEGACY(m, n, a, lda, tau, work, lwork, info);
    }
}

void
accelerate_dorgqr
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    double a[],
    fortran_int *lda,
    double tau[],
    double work[],
    fortran_int *lwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dorgqr_(m, n, k, a, lda, tau, work, lwork, info);
    } else {
        dorgqr$LEGACY(m, n, k, a, lda, tau, work, lwork, info);
    }
}

void
accelerate_zungqr
(
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    f2c_doublecomplex a[],
    fortran_int *lda,
    f2c_doublecomplex tau[],
    f2c_doublecomplex work[],
    fortran_int *lwork,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zungqr_(m, n, k, a, lda, tau, work, lwork, info);
    } else {
        zungqr$LEGACY(m, n, k, a, lda, tau, work, lwork, info);
    }
}

void
accelerate_sgesv
(
    fortran_int *n,
    fortran_int *nrhs,
    float a[],
    fortran_int *lda,
    fortran_int ipiv[],
    float b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        sgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
    } else {
        sgesv$LEGACY(n, nrhs, a, lda, ipiv, b, ldb, info);
    }
}

void
accelerate_dgesv
(
    fortran_int *n,
    fortran_int *nrhs,
    double a[],
    fortran_int *lda,
    fortran_int ipiv[],
    double b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
    } else {
        dgesv$LEGACY(n, nrhs, a, lda, ipiv, b, ldb, info);
    }
}

void
accelerate_cgesv
(
    fortran_int *n,
    fortran_int *nrhs,
    f2c_complex a[],
    fortran_int *lda,
    fortran_int ipiv[],
    f2c_complex b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
    } else {
        cgesv$LEGACY(n, nrhs, a, lda, ipiv, b, ldb, info);
    }
}

void
accelerate_zgesv
(
    fortran_int *n,
    fortran_int *nrhs,
    f2c_doublecomplex a[],
    fortran_int *lda,
    fortran_int ipiv[],
    f2c_doublecomplex b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
    } else {
        zgesv$LEGACY(n, nrhs, a, lda, ipiv, b, ldb, info);
    }
}

fortran_int
accelerate_sgetrf
(
    fortran_int *m,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    fortran_int ipiv[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        sgetrf_(m, n, a, lda, ipiv, info);
    } else {
        sgetrf$LEGACY(m, n, a, lda, ipiv, info);
    }
}

fortran_int
accelerate_dgetrf
(
    fortran_int *m,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    fortran_int ipiv[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgetrf_(m, n, a, lda, ipiv, info);
    } else {
        dgetrf$LEGACY(m, n, a, lda, ipiv, info);
    }
}

fortran_int
accelerate_cgetrf
(
    fortran_int *m,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    fortran_int ipiv[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cgetrf_(m, n, a, lda, ipiv, info);
    } else {
        cgetrf$LEGACY(m, n, a, lda, ipiv, info);
    }
}

fortran_int
accelerate_zgetrf
(
    fortran_int *m,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    fortran_int ipiv[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgetrf_(m, n, a, lda, ipiv, info);
    } else {
        zgetrf$LEGACY(m, n, a, lda, ipiv, info);
    }
}

void
accelerate_spotrf
(
    char *uplo,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        spotrf_(uplo, n, a, lda, info);
    } else {
        spotrf$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_dpotrf
(
    char *uplo,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dpotrf_(uplo, n, a, lda, info);
    } else {
        dpotrf$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_cpotrf
(
    char *uplo,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cpotrf_(uplo, n, a, lda, info);
    } else {
        cpotrf$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_zpotrf
(
    char *uplo,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zpotrf_(uplo, n, a, lda, info);
    } else {
        zpotrf$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_sgesdd
(
    char *jobz,
    fortran_int *m,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    float s[],
    float u[],
    fortran_int *ldu,
    float vt[],
    fortran_int *ldvt,
    float work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        sgesdd_(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, iwork, info);
    } else {
        sgesdd$LEGACY(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, iwork, info);
    }
}

void
accelerate_dgesdd
(
    char *jobz,
    fortran_int *m,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    double s[],
    double u[],
    fortran_int *ldu,
    double vt[],
    fortran_int *ldvt,
    double work[],
    fortran_int *lwork,
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dgesdd_(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, iwork, info);
    } else {
        dgesdd$LEGACY(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, iwork, info);
    }
}

void
accelerate_cgesdd
(
    char *jobz,
    fortran_int *m,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    float s[],
    f2c_complex u[],
    fortran_int *ldu,
    f2c_complex vt[],
    fortran_int *ldvt,
    f2c_complex work[],
    fortran_int *lwork,
    float rwork[],
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cgesdd_(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, rwork, iwork, info);
    } else {
        cgesdd$LEGACY(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, rwork, iwork, info);
    }
}

void
accelerate_zgesdd
(
    char *jobz,
    fortran_int *m,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    double s[],
    f2c_doublecomplex u[],
    fortran_int *ldu,
    f2c_doublecomplex vt[],
    fortran_int *ldvt,
    f2c_doublecomplex work[],
    fortran_int *lwork,
    double rwork[],
    fortran_int iwork[],
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zgesdd_(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, rwork, iwork, info);
    } else {
        zgesdd$LEGACY(jobz, m, n, a, lda, s, u, ldu, vt, ldvt, work, lwork, rwork, iwork, info);
    }
}

void
accelerate_spotrs
(
    char *uplo,
    fortran_int *n,
    fortran_int *nrhs,
    float a[],
    fortran_int *lda,
    float b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        spotrs_(uplo, n, nrhs, a, lda, b, ldb, info);
    } else {
        spotrs$LEGACY(uplo, n, nrhs, a, lda, b, ldb, info);
    }
}

void
accelerate_dpotrs
(
    char *uplo,
    fortran_int *n,
    fortran_int *nrhs,
    double a[],
    fortran_int *lda,
    double b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dpotrs_(uplo, n, nrhs, a, lda, b, ldb, info);
    } else {
        dpotrs$LEGACY(uplo, n, nrhs, a, lda, b, ldb, info);
    }
}

void
accelerate_cpotrs
(
    char *uplo,
    fortran_int *n,
    fortran_int *nrhs,
    f2c_complex a[],
    fortran_int *lda,
    f2c_complex b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cpotrs_(uplo, n, nrhs, a, lda, b, ldb, info);
    } else {
        cpotrs$LEGACY(uplo, n, nrhs, a, lda, b, ldb, info);
    }
}

void
accelerate_zpotrs
(
    char *uplo,
    fortran_int *n,
    fortran_int *nrhs,
    f2c_doublecomplex a[],
    fortran_int *lda,
    f2c_doublecomplex b[],
    fortran_int *ldb,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zpotrs_(uplo, n, nrhs, a, lda, b, ldb, info);
    } else {
        zpotrs$LEGACY(uplo, n, nrhs, a, lda, b, ldb, info);
    }
}

void
accelerate_spotri
(
    char *uplo,
    fortran_int *n,
    float a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        spotri_(uplo, n, a, lda, info);
    } else {
        spotri$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_dpotri
(
    char *uplo,
    fortran_int *n,
    double a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        dpotri_(uplo, n, a, lda, info);
    } else {
        dpotri$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_cpotri
(
    char *uplo,
    fortran_int *n,
    f2c_complex a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        cpotri_(uplo, n, a, lda, info);
    } else {
        cpotri$LEGACY(uplo, n, a, lda, info);
    }
}

void
accelerate_zpotri
(
    char *uplo,
    fortran_int *n,
    f2c_doublecomplex a[],
    fortran_int *lda,
    fortran_int *info
){
    if(__builtin_available(macos 13.3, *)){
        zpotri_(uplo, n, a, lda, info);
    } else {
        zpotri$LEGACY(uplo, n, a, lda, info);
    }
}

fortran_int
accelerate_scopy
(
    fortran_int *n,
    float *sx,
    fortran_int *incx,
    float *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        scopy_(n, sx, incx, sy, incy);
    } else {
        scopy$LEGACY(n, sx, incx, sy, incy);
    }
}

fortran_int
accelerate_dcopy
(
    fortran_int *n,
    double *sx,
    fortran_int *incx,
    double *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        dcopy_(n, sx, incx, sy, incy);
    } else {
        dcopy$LEGACY(n, sx, incx, sy, incy);
    }
}

fortran_int
accelerate_ccopy
(
    fortran_int *n,
    f2c_complex *sx,
    fortran_int *incx,
    f2c_complex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        ccopy_(n, sx, incx, sy, incy);
    } else {
        ccopy$LEGACY(n, sx, incx, sy, incy);
    }
}

fortran_int
accelerate_zcopy
(
    fortran_int *n,
    f2c_doublecomplex *sx,
    fortran_int *incx,
    f2c_doublecomplex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        zcopy_(n, sx, incx, sy, incy);
    } else {
        zcopy$LEGACY(n, sx, incx, sy, incy);
    }
}

float
accelerate_sdot
(
    fortran_int *n,
    float *sx,
    fortran_int *incx,
    float *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        sdot_(n, sx, incx, sy, incy);
    } else {
        sdot$LEGACY(n, sx, incx, sy, incy);
    }
}

double
accelerate_ddot
(
    fortran_int *n,
    double *sx,
    fortran_int *incx,
    double *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        ddot_(n, sx, incx, sy, incy);
    } else {
        ddot$LEGACY(n, sx, incx, sy, incy);
    }
}

void
accelerate_cdotu
(
    f2c_complex *ret,
    fortran_int *n,
    f2c_complex *sx,
    fortran_int *incx,
    f2c_complex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        cdotu_(ret, n, sx, incx, sy, incy);
    } else {
        cdotu$LEGACY(ret, n, sx, incx, sy, incy);
    }
}

void
accelerate_zdotu
(
    f2c_doublecomplex *ret,
    fortran_int *n,
    f2c_doublecomplex *sx,
    fortran_int *incx,
    f2c_doublecomplex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        zdotu_(ret, n, sx, incx, sy, incy);
    } else {
        zdotu$LEGACY(ret, n, sx, incx, sy, incy);
    }
}

void
accelerate_cdotc
(
    f2c_complex *ret,
    fortran_int *n,
    f2c_complex *sx,
    fortran_int *incx,
    f2c_complex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        cdotc_(ret, n, sx, incx, sy, incy);
    } else {
        cdotc$LEGACY(ret, n, sx, incx, sy, incy);
    }
}

void
accelerate_zdotc
(
    f2c_doublecomplex *ret,
    fortran_int *n,
    f2c_doublecomplex *sx,
    fortran_int *incx,
    f2c_doublecomplex *sy,
    fortran_int *incy
){
    if(__builtin_available(macos 13.3, *)){
        zdotc_(ret, n, sx, incx, sy, incy);
    } else {
        zdotc$LEGACY(ret, n, sx, incx, sy, incy);
    }
}

void
accelerate_sgemm
(
    char *transa,
    char *transb,
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    float *alpha,
    float *a,
    fortran_int *lda,
    float *b,
    fortran_int *ldb,
    float *beta,
    float *c,
    fortran_int *ldc
){
    if(__builtin_available(macos 13.3, *)){
        sgemm_(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    } else {
        sgemm$LEGACY(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }
}

void
accelerate_dgemm
(
    char *transa,
    char *transb,
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    double *alpha,
    double *a,
    fortran_int *lda,
    double *b,
    fortran_int *ldb,
    double *beta,
    double *c,
    fortran_int *ldc
){
    if(__builtin_available(macos 13.3, *)){
        dgemm_(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    } else {
        dgemm$LEGACY(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }
}

void
accelerate_cgemm
(
    char *transa,
    char *transb,
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    f2c_complex *alpha,
    f2c_complex *a,
    fortran_int *lda,
    f2c_complex *b,
    fortran_int *ldb,
    f2c_complex *beta,
    f2c_complex *c,
    fortran_int *ldc
){
    if(__builtin_available(macos 13.3, *)){
        cgemm_(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    } else {
        cgemm$LEGACY(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }
}

void
accelerate_zgemm
(
    char *transa,
    char *transb,
    fortran_int *m,
    fortran_int *n,
    fortran_int *k,
    f2c_doublecomplex *alpha,
    f2c_doublecomplex *a,
    fortran_int *lda,
    f2c_doublecomplex *b,
    fortran_int *ldb,
    f2c_doublecomplex *beta,
    f2c_doublecomplex *c,
    fortran_int *ldc
){
    if(__builtin_available(macos 13.3, *)){
        zgemm_(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    } else {
        zgemm$LEGACY(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
    }
}

