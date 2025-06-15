/*!
 @file vector2.h
 @brief two-dimensional vector
*/

#ifndef LIBA_VECTOR2_H
#define LIBA_VECTOR2_H

#include "a.h"
#include "math.h"

/*!
 @ingroup liba
 @addtogroup a_vector2 two-dimensional vector
 @{
*/

/* clang-format off */
/*! constructs a two-dimensional vector from cartesian coordinate */
#define A_VECTOR2_C(x, y) {a_real_c(x), a_real_c(y)}
/* clang-format on */

/*! static cast to \ref a_vector2 */
#define a_vector2_c(x) a_cast_s(a_vector2, x)
#define a_vector2_(_, x) a_cast_s(a_vector2 _, x)

typedef struct a_vector2 a_vector2;

#if defined(__cplusplus)
namespace a
{
typedef struct a_vector2 vector2;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR2_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN a_real a_vector2_set_dir(a_vector2 *ctx, a_real x, a_real y);
A_INTERN void a_vector2_val(a_vector2 const *ctx, a_real *x, a_real *y);
A_INTERN void a_vector2_set_val(a_vector2 *ctx, a_real x, a_real y);
A_INTERN void a_vector2_pol(a_vector2 const *ctx, a_real *rho, a_real *theta);
A_INTERN void a_vector2_set_pol(a_vector2 *ctx, a_real rho, a_real theta);

A_INTERN void a_vector2_add(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res);
A_INTERN void a_vector2_sub(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res);
A_INTERN void a_vector2_mul(a_vector2 const *lhs, a_real rhs, a_vector2 *res);
A_INTERN void a_vector2_div(a_vector2 const *lhs, a_real rhs, a_vector2 *res);
A_INTERN void a_vector2_neg(a_vector2 const *ctx, a_vector2 *res);

A_EXTERN a_real a_vector2_unit(a_vector2 *ctx);
A_EXTERN a_real a_vector2_norm(a_vector2 const *ctx);
A_EXTERN a_real a_vector2_norm1(a_vector2 const *ctx);
A_EXTERN a_real a_vector2_norm2(a_vector2 const *ctx);
A_EXTERN a_real a_vector2_dot(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_real a_vector2_dist(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_real a_vector2_dist1(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_real a_vector2_dist2(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_real a_vector2_angle(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_bool a_vector2_isver(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_bool a_vector2_ispar(a_vector2 const *lhs, a_vector2 const *rhs);
A_EXTERN a_real a_vector2_cross(a_vector2 const *lhs, a_vector2 const *rhs);

A_EXTERN void a_vector2_rot_(a_vector2 const *ctx, a_real sin, a_real cos, a_vector2 *res);
A_EXTERN void a_vector2_rot(a_vector2 const *ctx, a_real angle, a_vector2 *res);

#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

struct a_point2;
/*!
 @brief instance structure for two-dimensional vector
*/
struct a_vector2
{
    a_real x, y;
#if defined(__cplusplus)
    A_INLINE void set(a_point2 const &p, a_point2 const &q);
    A_INLINE a_real set_dir(a_real x_, a_real y_)
    {
        return a_vector2_set_dir(this, x_, y_);
    }
    A_INLINE void val(a_real &x_, a_real &y_) const
    {
        a_vector2_val(this, &x_, &y_);
    }
    A_INLINE void set_val(a_real x_, a_real y_)
    {
        a_vector2_set_val(this, x_, y_);
    }
    A_INLINE void pol(a_real &rho, a_real &theta) const
    {
        a_vector2_pol(this, &rho, &theta);
    }
    A_INLINE void set_pol(a_real rho, a_real theta)
    {
        a_vector2_set_pol(this, rho, theta);
    }
    A_INLINE void add(a_vector2 const &rhs, a_vector2 &res) const
    {
        a_vector2_add(this, &rhs, &res);
    }
    A_INLINE void sub(a_vector2 const &rhs, a_vector2 &res) const
    {
        a_vector2_sub(this, &rhs, &res);
    }
    A_INLINE void mul(a_real rhs, a_vector2 &res) const
    {
        a_vector2_mul(this, rhs, &res);
    }
    A_INLINE void div(a_real rhs, a_vector2 &res) const
    {
        a_vector2_div(this, rhs, &res);
    }
    A_INLINE void neg(a_vector2 &res) const
    {
        a_vector2_neg(this, &res);
    }
    A_INLINE a_real unit() { return a_vector2_unit(this); }
    A_INLINE a_real norm() const { return a_vector2_norm(this); }
    A_INLINE a_real norm1() const { return a_vector2_norm1(this); }
    A_INLINE a_real norm2() const { return a_vector2_norm2(this); }
    A_INLINE a_real dot(a_vector2 const &rhs) const { return a_vector2_dot(this, &rhs); }
    A_INLINE a_real dist(a_vector2 const &rhs) const { return a_vector2_dist(this, &rhs); }
    A_INLINE a_real dist1(a_vector2 const &rhs) const { return a_vector2_dist1(this, &rhs); }
    A_INLINE a_real dist2(a_vector2 const &rhs) const { return a_vector2_dist2(this, &rhs); }
    A_INLINE a_real angle(a_vector2 const &rhs) const { return a_vector2_angle(this, &rhs); }
    A_INLINE a_bool isver(a_vector2 const &rhs) const { return a_vector2_isver(this, &rhs); }
    A_INLINE a_bool ispar(a_vector2 const &rhs) const { return a_vector2_ispar(this, &rhs); }
    A_INLINE a_real cross(a_vector2 const &rhs) const { return a_vector2_cross(this, &rhs); }
    A_INLINE void rot(a_real angle, a_vector2 &res) const { a_vector2_rot(this, angle, &res); }
    friend A_INLINE a_real operator^(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        return a_vector2_cross(&lhs, &rhs);
    }
    friend A_INLINE void operator+=(a_vector2 &lhs, a_vector2 const &rhs) { a_vector2_add(&lhs, &rhs, &lhs); }
    friend A_INLINE a_vector2 operator+(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_add(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator-=(a_vector2 &lhs, a_vector2 const &rhs) { a_vector2_sub(&lhs, &rhs, &lhs); }
    friend A_INLINE a_vector2 operator-(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_sub(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator*=(a_vector2 &lhs, a_real rhs) { a_vector2_mul(&lhs, rhs, &lhs); }
    friend A_INLINE a_real operator*(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        return a_vector2_dot(&lhs, &rhs);
    }
    friend A_INLINE a_vector2 operator*(a_real lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_mul(&rhs, lhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator*(a_vector2 const &lhs, a_real rhs)
    {
        a_vector2 res;
        a_vector2_mul(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE void operator/=(a_vector2 &lhs, a_real rhs) { a_vector2_div(&lhs, rhs, &lhs); }
    friend A_INLINE a_vector2 operator/(a_vector2 const &lhs, a_real rhs)
    {
        a_vector2 res;
        a_vector2_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator+(a_vector2 const &rhs) { return rhs; }
    friend A_INLINE a_vector2 operator-(a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_VECTOR2_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VECTOR2_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_VECTOR2_C)

A_INLINE a_real a_vector2_set_dir(a_vector2 *ctx, a_real x, a_real y)
{
    ctx->x = x;
    ctx->y = y;
    return a_vector2_unit(ctx);
}
A_INTERN void a_vector2_val(a_vector2 const *ctx, a_real *x, a_real *y)
{
    *x = ctx->x;
    *y = ctx->y;
}
A_INTERN void a_vector2_set_val(a_vector2 *ctx, a_real x, a_real y)
{
    ctx->x = x;
    ctx->y = y;
}
A_INTERN void a_vector2_pol(a_vector2 const *ctx, a_real *rho, a_real *theta)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
}
A_INTERN void a_vector2_set_pol(a_vector2 *ctx, a_real rho, a_real theta)
{
    a_real_pol2cart(rho, theta, &ctx->x, &ctx->y);
}
A_INTERN void a_vector2_add(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res)
{
    res->x = lhs->x + rhs->x;
    res->y = lhs->y + rhs->y;
}
A_INTERN void a_vector2_sub(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res)
{
    res->x = lhs->x - rhs->x;
    res->y = lhs->y - rhs->y;
}
A_INTERN void a_vector2_mul(a_vector2 const *lhs, a_real rhs, a_vector2 *res)
{
    res->x = lhs->x * rhs;
    res->y = lhs->y * rhs;
}
A_INTERN void a_vector2_div(a_vector2 const *lhs, a_real rhs, a_vector2 *res)
{
    res->x = lhs->x / rhs;
    res->y = lhs->y / rhs;
}
A_INTERN void a_vector2_neg(a_vector2 const *ctx, a_vector2 *res)
{
    res->x = -ctx->x;
    res->y = -ctx->y;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_VECTOR2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VECTOR2_C */

/*! @} a_vector2 */

#endif /* a/vector2.h */
