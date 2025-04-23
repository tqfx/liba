/*!
 @file point3.h
 @brief three-dimensional point
*/

#ifndef LIBA_POINT3_H
#define LIBA_POINT3_H

#include "a.h"
#include "vector3.h"

/*!
 @ingroup liba
 @addtogroup a_point3 three-dimensional point
 @{
*/

/* clang-format off */
/*! constructs a three-dimensional point from cartesian coordinate */
#define A_POINT3_C(x, y, z) {a_real_c(x), a_real_c(y), a_real_c(z)}
/* clang-format on */

/*! static cast to \ref a_point3 */
#define a_point3_c(x) a_cast_s(a_point3, x)
#define a_point3_(_, x) a_cast_s(a_point3 _, x)

typedef struct a_point3 a_point3;

#if defined(__cplusplus)
namespace a
{
typedef struct a_point3 point3;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN void a_point3_xyz(a_point3 const *ctx, a_real *x, a_real *y, a_real *z);
A_INTERN void a_point3_set_xyz(a_point3 *ctx, a_real x, a_real y, a_real z);
A_INTERN void a_point3_pol(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z);
A_INTERN void a_point3_set_pol(a_point3 *ctx, a_real rho, a_real theta, a_real z);
A_INTERN void a_point3_sph(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *alpha);
A_INTERN void a_point3_set_sph(a_point3 *ctx, a_real rho, a_real theta, a_real alpha);

A_INTERN void a_point3_tov(a_point3 const *ctx, a_point3 const *tgt, a_vector3 *res);
A_INTERN void a_point3_add(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
A_INTERN void a_point3_sub(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
A_INTERN void a_point3_mul(a_point3 const *lhs, a_real rhs, a_point3 *res);
A_INTERN void a_point3_div(a_point3 const *lhs, a_real rhs, a_point3 *res);

A_EXTERN a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs);
A_EXTERN a_real a_point3_dist1(a_point3 const *lhs, a_point3 const *rhs);
A_EXTERN a_real a_point3_dist2(a_point3 const *lhs, a_point3 const *rhs);

#if !defined A_HAVE_INLINE || defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for three-dimensional point
*/
struct a_point3
{
    a_real x, y, z;
#if defined(__cplusplus)
    A_INLINE void xyz(a_real &ox, a_real &oy, a_real &oz) const
    {
        a_point3_xyz(this, &ox, &oy, &oz);
    }
    A_INLINE void set_xyz(a_real ix, a_real iy, a_real iz)
    {
        a_point3_set_xyz(this, ix, iy, iz);
    }
    A_INLINE void pol(a_real &rho, a_real &theta, a_real &oz) const
    {
        a_point3_pol(this, &rho, &theta, &oz);
    }
    A_INLINE void set_pol(a_real rho, a_real theta, a_real iz)
    {
        a_point3_set_pol(this, rho, theta, iz);
    }
    A_INLINE void sph(a_real &rho, a_real &theta, a_real &alpha) const
    {
        a_point3_sph(this, &rho, &theta, &alpha);
    }
    A_INLINE void set_sph(a_real rho, a_real theta, a_real alpha)
    {
        a_point3_set_sph(this, rho, theta, alpha);
    }
    A_INLINE a_vector3 tov(a_point3 const &tgt) const
    {
        a_vector3 res;
        a_point3_tov(this, &tgt, &res);
        return res;
    }
    A_INLINE a_point3 add(a_vector3 const &rhs) const
    {
        a_point3 res;
        a_point3_add(this, &rhs, &res);
        return res;
    }
    A_INLINE a_point3 sub(a_vector3 const &rhs) const
    {
        a_point3 res;
        a_point3_sub(this, &rhs, &res);
        return res;
    }
    A_INLINE a_point3 mul(a_real rhs) const
    {
        a_point3 res;
        a_point3_mul(this, rhs, &res);
        return res;
    }
    A_INLINE a_point3 div(a_real rhs) const
    {
        a_point3 res;
        a_point3_div(this, rhs, &res);
        return res;
    }
    A_INLINE a_real dist(a_point3 const &rhs) const { return a_point3_dist(this, &rhs); }
    A_INLINE a_real dist1(a_point3 const &rhs) const { return a_point3_dist1(this, &rhs); }
    A_INLINE a_real dist2(a_point3 const &rhs) const { return a_point3_dist2(this, &rhs); }
    friend A_INLINE a_vector3 operator-(a_point3 const &lhs, a_point3 const &rhs) { return rhs.tov(lhs); }
    friend A_INLINE a_point3 operator+(a_point3 const &lhs, a_vector3 const &rhs) { return lhs.add(rhs); }
    friend A_INLINE void operator+=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_add(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point3 operator-(a_point3 const &lhs, a_vector3 const &rhs) { return lhs.sub(rhs); }
    friend A_INLINE void operator-=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_sub(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point3 operator*(a_real lhs, a_point3 const &rhs) { return rhs.mul(lhs); }
    friend A_INLINE a_point3 operator*(a_point3 const &lhs, a_real rhs) { return lhs.mul(rhs); }
    friend A_INLINE void operator*=(a_point3 &lhs, a_real rhs) { a_point3_mul(&lhs, rhs, &lhs); }
    friend A_INLINE a_point3 operator/(a_point3 const &lhs, a_real rhs) { return lhs.div(rhs); }
    friend A_INLINE void operator/=(a_point3 &lhs, a_real rhs) { a_point3_div(&lhs, rhs, &lhs); }
#endif /* __cplusplus */
};

#if defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_POINT3_C */

#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_xyz(a_point3 const *ctx, a_real *x, a_real *y, a_real *z)
{
    *x = ctx->x;
    *y = ctx->y;
    *z = ctx->z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_set_xyz(a_point3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->x = x;
    ctx->y = y;
    ctx->z = z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_pol(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
    *z = ctx->z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_set_pol(a_point3 *ctx, a_real rho, a_real theta, a_real z)
{
    a_real_pol2cart(rho, theta, &ctx->x, &ctx->y);
    ctx->z = z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_sph(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *alpha)
{
    a_real_cart2sph(ctx->x, ctx->y, ctx->z, rho, theta, alpha);
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_set_sph(a_point3 *ctx, a_real rho, a_real theta, a_real alpha)
{
    a_real_sph2cart(rho, theta, alpha, &ctx->x, &ctx->y, &ctx->z);
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_tov(a_point3 const *ctx, a_point3 const *tgt, a_vector3 *res)
{
    res->x = tgt->x - ctx->x;
    res->y = tgt->y - ctx->y;
    res->z = tgt->z - ctx->z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_add(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res)
{
    res->x = lhs->x + rhs->x;
    res->y = lhs->y + rhs->y;
    res->z = lhs->z + rhs->z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_sub(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res)
{
    res->x = lhs->x - rhs->x;
    res->y = lhs->y - rhs->y;
    res->z = lhs->z - rhs->z;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_mul(a_point3 const *lhs, a_real rhs, a_point3 *res)
{
    res->x = lhs->x * rhs;
    res->y = lhs->y * rhs;
    res->z = lhs->z * rhs;
}
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)
A_INTERN void a_point3_div(a_point3 const *lhs, a_real rhs, a_point3 *res)
{
    res->x = lhs->x / rhs;
    res->y = lhs->y / rhs;
    res->z = lhs->z / rhs;
}
#endif /* A_HAVE_INLINE */

#if defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_POINT3_C */

/*! @} a_point3 */

#endif /* a/point3.h */
