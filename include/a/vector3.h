/*!
 @file vector3.h
 @brief three-dimensional vector
*/

#ifndef LIBA_VECTOR3_H
#define LIBA_VECTOR3_H

#include "a.h"
#include "math.h"

/*!
 @ingroup liba
 @addtogroup a_vector3 three-dimensional vector
 @{
*/

/* clang-format off */
/*! constructs a three-dimensional vector from cartesian coordinate */
#define A_VECTOR3_C(x, y, z) {a_real_c(x), a_real_c(y), a_real_c(z)}
/* clang-format on */

/*! static cast to @ref a_vector3 */
#define a_vector3_c(x) a_cast_s(a_vector3, x)
#define a_vector3_(_, x) a_cast_s(a_vector3 _, x)

typedef struct a_vector3 a_vector3;

#if defined(__cplusplus)
namespace a
{
typedef struct a_vector3 vector3;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR3_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN a_real a_vector3_set_dir(a_vector3 *ctx, a_real x, a_real y, a_real z);
A_INTERN void a_vector3_val(a_vector3 const *ctx, a_real *x, a_real *y, a_real *z);
A_INTERN void a_vector3_set_val(a_vector3 *ctx, a_real x, a_real y, a_real z);
A_INTERN void a_vector3_pol(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *z);
A_INTERN void a_vector3_set_pol(a_vector3 *ctx, a_real rho, a_real theta, a_real z);
A_INTERN void a_vector3_sph(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *alpha);
A_INTERN void a_vector3_set_sph(a_vector3 *ctx, a_real rho, a_real theta, a_real alpha);

A_INTERN void a_vector3_add(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
A_INTERN void a_vector3_sub(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
A_INTERN void a_vector3_mul(a_vector3 const *lhs, a_real rhs, a_vector3 *res);
A_INTERN void a_vector3_div(a_vector3 const *lhs, a_real rhs, a_vector3 *res);
A_INTERN void a_vector3_neg(a_vector3 const *ctx, a_vector3 *res);

A_EXTERN a_real a_vector3_unit(a_vector3 *ctx);
A_EXTERN a_real a_vector3_norm(a_vector3 const *ctx);
A_EXTERN a_real a_vector3_norm2(a_vector3 const *ctx);
A_EXTERN a_real a_vector3_dot(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN a_real a_vector3_dist(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN a_real a_vector3_dist2(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN a_real a_vector3_angle(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN a_bool a_vector3_isver(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN a_bool a_vector3_ispar(a_vector3 const *lhs, a_vector3 const *rhs);
A_EXTERN void a_vector3_cross(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
A_EXTERN void a_vector3_outer(a_vector3 const *lhs, a_vector3 const *rhs, a_real res[9]);
A_EXTERN int a_vector3_ortho(a_vector3 const *ctx, a_vector3 *u, a_vector3 *v);
A_EXTERN void a_vector3_rot_(a_vector3 const *ctx, a_vector3 const *dir, a_real sin, a_real cos, a_vector3 *res);
A_EXTERN void a_vector3_rot(a_vector3 const *ctx, a_vector3 const *dir, a_real angle, a_vector3 *res);
A_EXTERN void a_vector3_rot2d(a_vector3 const *iu, a_vector3 const *iv, a_real angle,
                              a_vector3 *ou, a_vector3 *ov);

#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

struct a_point3;
/*!
 @brief instance structure for three-dimensional vector
*/
struct a_vector3
{
    a_real x, y, z;
#if defined(__cplusplus)
    A_INLINE void set(a_point3 const &p, a_point3 const &q);
    A_INLINE a_real set_dir(a_real x_, a_real y_, a_real z_)
    {
        return a_vector3_set_dir(this, x_, y_, z_);
    }
    A_INLINE void val(a_real &x_, a_real &y_, a_real &z_) const
    {
        a_vector3_val(this, &x_, &y_, &z_);
    }
    A_INLINE void set_val(a_real x_, a_real y_, a_real z_)
    {
        a_vector3_set_val(this, x_, y_, z_);
    }
    A_INLINE void pol(a_real &rho, a_real &theta, a_real &z_) const
    {
        a_vector3_pol(this, &rho, &theta, &z_);
    }
    A_INLINE void set_pol(a_real rho, a_real theta, a_real z_)
    {
        a_vector3_set_pol(this, rho, theta, z_);
    }
    A_INLINE void sph(a_real &rho, a_real &theta, a_real &alpha) const
    {
        a_vector3_sph(this, &rho, &theta, &alpha);
    }
    A_INLINE void set_sph(a_real rho, a_real theta, a_real alpha)
    {
        a_vector3_set_sph(this, rho, theta, alpha);
    }
    A_INLINE void add(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_add(this, &rhs, &res);
    }
    A_INLINE void sub(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_sub(this, &rhs, &res);
    }
    A_INLINE void mul(a_real rhs, a_vector3 &res) const
    {
        a_vector3_mul(this, rhs, &res);
    }
    A_INLINE void div(a_real rhs, a_vector3 &res) const
    {
        a_vector3_div(this, rhs, &res);
    }
    A_INLINE void neg(a_vector3 &res) const
    {
        a_vector3_neg(this, &res);
    }
    A_INLINE a_real unit() { return a_vector3_unit(this); }
    A_INLINE a_real norm() const { return a_vector3_norm(this); }
    A_INLINE a_real norm2() const { return a_vector3_norm2(this); }
    A_INLINE a_real dot(a_vector3 const &rhs) const { return a_vector3_dot(this, &rhs); }
    A_INLINE a_real dist(a_vector3 const &rhs) const { return a_vector3_dist(this, &rhs); }
    A_INLINE a_real dist2(a_vector3 const &rhs) const { return a_vector3_dist2(this, &rhs); }
    A_INLINE a_real angle(a_vector3 const &rhs) const { return a_vector3_angle(this, &rhs); }
    A_INLINE a_bool isver(a_vector3 const &rhs) const { return a_vector3_isver(this, &rhs); }
    A_INLINE a_bool ispar(a_vector3 const &rhs) const { return a_vector3_ispar(this, &rhs); }
    A_INLINE void cross(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_cross(this, &rhs, &res);
    }
    A_INLINE void outer(a_vector3 const &rhs, a_real res[9]) const
    {
        a_vector3_outer(this, &rhs, res);
    }
    A_INLINE int ortho(a_vector3 &u, a_vector3 &v) const
    {
        return a_vector3_ortho(this, &u, &v);
    }
    A_INLINE void rot(a_vector3 const &dir, a_real angle, a_vector3 &res) const
    {
        a_vector3_rot(this, &dir, angle, &res);
    }
    static A_INLINE void rot2d(a_vector3 const &iu, a_vector3 const &iv, a_real angle,
                               a_vector3 &ou, a_vector3 &ov)
    {
        a_vector3_rot2d(&iu, &iv, angle, &ou, &ov);
    }
    friend A_INLINE a_vector3 operator^(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_cross(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator+=(a_vector3 &lhs, a_vector3 const &rhs) { a_vector3_add(&lhs, &rhs, &lhs); }
    friend A_INLINE a_vector3 operator+(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_add(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator-=(a_vector3 &lhs, a_vector3 const &rhs) { a_vector3_sub(&lhs, &rhs, &lhs); }
    friend A_INLINE a_vector3 operator-(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_sub(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator*=(a_vector3 &lhs, a_real rhs) { a_vector3_mul(&lhs, rhs, &lhs); }
    friend A_INLINE a_real operator*(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        return a_vector3_dot(&lhs, &rhs);
    }
    friend A_INLINE a_vector3 operator*(a_real lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_mul(&rhs, lhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator*(a_vector3 const &lhs, a_real rhs)
    {
        a_vector3 res;
        a_vector3_mul(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE void operator/=(a_vector3 &lhs, a_real rhs) { a_vector3_div(&lhs, rhs, &lhs); }
    friend A_INLINE a_vector3 operator/(a_vector3 const &lhs, a_real rhs)
    {
        a_vector3 res;
        a_vector3_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator+(a_vector3 const &rhs) { return rhs; }
    friend A_INLINE a_vector3 operator-(a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_VECTOR3_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VECTOR3_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_VECTOR3_C)

A_INLINE a_real a_vector3_set_dir(a_vector3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->x = x;
    ctx->y = y;
    ctx->z = z;
    return a_vector3_unit(ctx);
}
A_INTERN void a_vector3_val(a_vector3 const *ctx, a_real *x, a_real *y, a_real *z)
{
    *x = ctx->x;
    *y = ctx->y;
    *z = ctx->z;
}
A_INTERN void a_vector3_set_val(a_vector3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->x = x;
    ctx->y = y;
    ctx->z = z;
}
A_INTERN void a_vector3_pol(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *z)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
    *z = ctx->z;
}
A_INTERN void a_vector3_set_pol(a_vector3 *ctx, a_real rho, a_real theta, a_real z)
{
    a_real_pol2cart(rho, theta, &ctx->x, &ctx->y);
    ctx->z = z;
}
A_INTERN void a_vector3_sph(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *alpha)
{
    a_real_cart2sph(ctx->x, ctx->y, ctx->z, rho, theta, alpha);
}
A_INTERN void a_vector3_set_sph(a_vector3 *ctx, a_real rho, a_real theta, a_real alpha)
{
    a_real_sph2cart(rho, theta, alpha, &ctx->x, &ctx->y, &ctx->z);
}
A_INTERN void a_vector3_add(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res)
{
    res->x = lhs->x + rhs->x;
    res->y = lhs->y + rhs->y;
    res->z = lhs->z + rhs->z;
}
A_INTERN void a_vector3_sub(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res)
{
    res->x = lhs->x - rhs->x;
    res->y = lhs->y - rhs->y;
    res->z = lhs->z - rhs->z;
}
A_INTERN void a_vector3_mul(a_vector3 const *lhs, a_real rhs, a_vector3 *res)
{
    res->x = lhs->x * rhs;
    res->y = lhs->y * rhs;
    res->z = lhs->z * rhs;
}
A_INTERN void a_vector3_div(a_vector3 const *lhs, a_real rhs, a_vector3 *res)
{
    res->x = lhs->x / rhs;
    res->y = lhs->y / rhs;
    res->z = lhs->z / rhs;
}
A_INTERN void a_vector3_neg(a_vector3 const *ctx, a_vector3 *res)
{
    res->x = -ctx->x;
    res->y = -ctx->y;
    res->z = -ctx->z;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_VECTOR3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VECTOR3_C */

/*! @} a_vector3 */

#endif /* a/vector3.h */
