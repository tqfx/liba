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

A_INTERN void a_vector3_set(a_vector3 *ctx, a_point3 const *p, a_point3 const *q);

A_INTERN void a_point3_val(a_point3 const *ctx, a_real *x, a_real *y, a_real *z);
A_INTERN void a_point3_set_val(a_point3 *ctx, a_real x, a_real y, a_real z);
A_INTERN void a_point3_pol(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z);
A_INTERN void a_point3_set_pol(a_point3 *ctx, a_real rho, a_real theta, a_real z);
A_INTERN void a_point3_sph(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *alpha);
A_INTERN void a_point3_set_sph(a_point3 *ctx, a_real rho, a_real theta, a_real alpha);

A_INTERN void a_point3_add(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
A_INTERN void a_point3_sub(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
A_INTERN void a_point3_mul(a_point3 const *lhs, a_real rhs, a_point3 *res);
A_INTERN void a_point3_div(a_point3 const *lhs, a_real rhs, a_point3 *res);
A_INTERN void a_point3_pos(a_point3 const *ctx, a_vector3 *res);
A_INTERN void a_point3_neg(a_point3 const *ctx, a_vector3 *res);

A_EXTERN a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs);
A_EXTERN a_real a_point3_dist2(a_point3 const *lhs, a_point3 const *rhs);

#if !defined A_HAVE_INLINE || defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
A_INLINE void a_vector3::set(a_point3 const &p, a_point3 const &q)
{
    a_vector3_set(this, &p, &q);
}
#endif /* __cplusplus */

/*!
 @brief instance structure for three-dimensional point
*/
struct a_point3
{
    a_real x, y, z;
#if defined(__cplusplus)
    A_INLINE void val(a_real &x_, a_real &y_, a_real &z_) const
    {
        a_point3_val(this, &x_, &y_, &z_);
    }
    A_INLINE void set_val(a_real x_, a_real y_, a_real z_)
    {
        a_point3_set_val(this, x_, y_, z_);
    }
    A_INLINE void pol(a_real &rho, a_real &theta, a_real &z_) const
    {
        a_point3_pol(this, &rho, &theta, &z_);
    }
    A_INLINE void set_pol(a_real rho, a_real theta, a_real z_)
    {
        a_point3_set_pol(this, rho, theta, z_);
    }
    A_INLINE void sph(a_real &rho, a_real &theta, a_real &alpha) const
    {
        a_point3_sph(this, &rho, &theta, &alpha);
    }
    A_INLINE void set_sph(a_real rho, a_real theta, a_real alpha)
    {
        a_point3_set_sph(this, rho, theta, alpha);
    }
    A_INLINE void add(a_vector3 const &rhs, a_point3 &res) const
    {
        a_point3_add(this, &rhs, &res);
    }
    A_INLINE void sub(a_vector3 const &rhs, a_point3 &res) const
    {
        a_point3_sub(this, &rhs, &res);
    }
    A_INLINE void mul(a_real rhs, a_point3 &res) const
    {
        a_point3_mul(this, rhs, &res);
    }
    A_INLINE void div(a_real rhs, a_point3 &res) const
    {
        a_point3_div(this, rhs, &res);
    }
    A_INLINE void pos(a_vector3 &res) const
    {
        a_point3_pos(this, &res);
    }
    A_INLINE void neg(a_vector3 &res) const
    {
        a_point3_neg(this, &res);
    }
    A_INLINE a_real dist(a_point3 const &rhs) const { return a_point3_dist(this, &rhs); }
    A_INLINE a_real dist2(a_point3 const &rhs) const { return a_point3_dist2(this, &rhs); }
    friend A_INLINE void operator+=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_add(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point3 operator+(a_point3 const &lhs, a_vector3 const &rhs)
    {
        a_point3 res;
        a_point3_add(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator-=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_sub(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point3 operator-(a_point3 const &lhs, a_vector3 const &rhs)
    {
        a_point3 res;
        a_point3_sub(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator-(a_point3 const &lhs, a_point3 const &rhs)
    {
        a_vector3 res;
        a_vector3_set(&res, &rhs, &lhs);
        return res;
    }
    friend A_INLINE void operator*=(a_point3 &lhs, a_real rhs) { a_point3_mul(&lhs, rhs, &lhs); }
    friend A_INLINE a_point3 operator*(a_real lhs, a_point3 const &rhs)
    {
        a_point3 res;
        a_point3_mul(&rhs, lhs, &res);
        return res;
    }
    friend A_INLINE a_point3 operator*(a_point3 const &lhs, a_real rhs)
    {
        a_point3 res;
        a_point3_mul(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE void operator/=(a_point3 &lhs, a_real rhs) { a_point3_div(&lhs, rhs, &lhs); }
    friend A_INLINE a_point3 operator/(a_point3 const &lhs, a_real rhs)
    {
        a_point3 res;
        a_point3_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator+(a_point3 const &rhs)
    {
        a_vector3 res;
        a_point3_pos(&rhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator-(a_point3 const &rhs)
    {
        a_vector3 res;
        a_point3_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_POINT3_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT3_C)

A_INTERN void a_vector3_set(a_vector3 *ctx, a_point3 const *p, a_point3 const *q)
{
    ctx->x = q->x - p->x;
    ctx->y = q->y - p->y;
    ctx->z = q->z - p->z;
}
A_INTERN void a_point3_val(a_point3 const *ctx, a_real *x, a_real *y, a_real *z)
{
    *x = ctx->x;
    *y = ctx->y;
    *z = ctx->z;
}
A_INTERN void a_point3_set_val(a_point3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->x = x;
    ctx->y = y;
    ctx->z = z;
}
A_INTERN void a_point3_pol(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
    *z = ctx->z;
}
A_INTERN void a_point3_set_pol(a_point3 *ctx, a_real rho, a_real theta, a_real z)
{
    a_real_pol2cart(rho, theta, &ctx->x, &ctx->y);
    ctx->z = z;
}
A_INTERN void a_point3_sph(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *alpha)
{
    a_real_cart2sph(ctx->x, ctx->y, ctx->z, rho, theta, alpha);
}
A_INTERN void a_point3_set_sph(a_point3 *ctx, a_real rho, a_real theta, a_real alpha)
{
    a_real_sph2cart(rho, theta, alpha, &ctx->x, &ctx->y, &ctx->z);
}
A_INTERN void a_point3_add(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res)
{
    res->x = lhs->x + rhs->x;
    res->y = lhs->y + rhs->y;
    res->z = lhs->z + rhs->z;
}
A_INTERN void a_point3_sub(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res)
{
    res->x = lhs->x - rhs->x;
    res->y = lhs->y - rhs->y;
    res->z = lhs->z - rhs->z;
}
A_INTERN void a_point3_mul(a_point3 const *lhs, a_real rhs, a_point3 *res)
{
    res->x = lhs->x * rhs;
    res->y = lhs->y * rhs;
    res->z = lhs->z * rhs;
}
A_INTERN void a_point3_div(a_point3 const *lhs, a_real rhs, a_point3 *res)
{
    res->x = lhs->x / rhs;
    res->y = lhs->y / rhs;
    res->z = lhs->z / rhs;
}
A_INTERN void a_point3_pos(a_point3 const *ctx, a_vector3 *res)
{
    res->x = +ctx->x;
    res->y = +ctx->y;
    res->z = +ctx->z;
}
A_INTERN void a_point3_neg(a_point3 const *ctx, a_vector3 *res)
{
    res->x = -ctx->x;
    res->y = -ctx->y;
    res->z = -ctx->z;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_POINT3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_POINT3_C */

/*! @} a_point3 */

#endif /* a/point3.h */
