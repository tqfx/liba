/*!
 @file point2.h
 @brief two-dimensional point
*/

#ifndef LIBA_POINT2_H
#define LIBA_POINT2_H

#include "a.h"
#include "vector2.h"

/*!
 @ingroup liba
 @addtogroup a_point2 two-dimensional point
 @{
*/

/* clang-format off */
/*! constructs a two-dimensional point from cartesian coordinate */
#define A_POINT2_C(x, y) {a_real_c(x), a_real_c(y)}
/* clang-format on */

/*! static cast to @ref a_point2 */
#define a_point2_c(x) a_cast_s(a_point2, x)
#define a_point2_(_, x) a_cast_s(a_point2 _, x)

typedef struct a_point2 a_point2;

#if defined(__cplusplus)
namespace a
{
typedef struct a_point2 point2;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_POINT2_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN void a_vector2_set(a_vector2 *ctx, a_point2 const *p, a_point2 const *q);

A_INTERN void a_point2_val(a_point2 const *ctx, a_real *x, a_real *y);
A_INTERN void a_point2_set_val(a_point2 *ctx, a_real x, a_real y);
A_INTERN void a_point2_pol(a_point2 const *ctx, a_real *rho, a_real *theta);
A_INTERN void a_point2_set_pol(a_point2 *ctx, a_real rho, a_real theta);

A_INTERN void a_point2_add(a_point2 const *lhs, a_vector2 const *rhs, a_point2 *res);
A_INTERN void a_point2_sub(a_point2 const *lhs, a_vector2 const *rhs, a_point2 *res);
A_INTERN void a_point2_mul(a_point2 const *lhs, a_real rhs, a_point2 *res);
A_INTERN void a_point2_div(a_point2 const *lhs, a_real rhs, a_point2 *res);
A_INTERN void a_point2_pos(a_point2 const *ctx, a_vector2 *res);
A_INTERN void a_point2_neg(a_point2 const *ctx, a_vector2 *res);

/*!
 @brief compute the distance between two 2D points.
 @details In two dimensions,
 let point \f$p\f$ have coordinates \f$(p_1,p_2)\f$ and
 let point \f$q\f$ have coordinates \f$(q_1,q_2)\f$.
 Then the distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)=\sqrt{(p_1-q_1)^2+(p_2-q_2)^2}
 \f]
 @param[in] lhs is left-hand side 2D point
 @param[in] rhs is right-hand side 2D point
 @return the distance between two 2D points
*/
A_EXTERN a_real a_point2_dist(a_point2 const *lhs, a_point2 const *rhs);
/*!
 @brief compute the squared distance between two 2D points.
 @details In two dimensions,
 let point \f$p\f$ have coordinates \f$(p_1,p_2)\f$ and
 let point \f$q\f$ have coordinates \f$(q_1,q_2)\f$.
 Then the squared distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)^2=(p_1-q_1)^2+(p_2-q_2)^2
 \f]
 @param[in] lhs is left-hand side 2D point
 @param[in] rhs is right-hand side 2D point
 @return the squared distance between two 2D points
*/
A_EXTERN a_real a_point2_dist2(a_point2 const *lhs, a_point2 const *rhs);

#if !defined A_HAVE_INLINE || defined(LIBA_POINT2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
A_INLINE void a_vector2::set(a_point2 const &p, a_point2 const &q)
{
    a_vector2_set(this, &p, &q);
}
#endif /* __cplusplus */

/*!
 @brief instance structure for two-dimensional point
*/
struct a_point2
{
    a_real x, y;
#if defined(__cplusplus)
    A_INLINE void val(a_real &x_, a_real &y_) const
    {
        a_point2_val(this, &x_, &y_);
    }
    A_INLINE void set_val(a_real x_, a_real y_)
    {
        a_point2_set_val(this, x_, y_);
    }
    A_INLINE void pol(a_real &rho, a_real &theta) const
    {
        a_point2_pol(this, &rho, &theta);
    }
    A_INLINE void set_pol(a_real rho, a_real theta)
    {
        a_point2_set_pol(this, rho, theta);
    }
    A_INLINE void add(a_vector2 const &rhs, a_point2 &res) const
    {
        a_point2_add(this, &rhs, &res);
    }
    A_INLINE void sub(a_vector2 const &rhs, a_point2 &res) const
    {
        a_point2_sub(this, &rhs, &res);
    }
    A_INLINE void mul(a_real rhs, a_point2 &res) const
    {
        a_point2_mul(this, rhs, &res);
    }
    A_INLINE void div(a_real rhs, a_point2 &res) const
    {
        a_point2_div(this, rhs, &res);
    }
    A_INLINE void pos(a_vector2 &res) const
    {
        a_point2_pos(this, &res);
    }
    A_INLINE void neg(a_vector2 &res) const
    {
        a_point2_neg(this, &res);
    }
    /*! @copybrief a_point2_dist @see a_point2_dist */
    A_INLINE a_real dist(a_point2 const &rhs) const { return a_point2_dist(this, &rhs); }
    /*! @copybrief a_point2_dist2 @see a_point2_dist2 */
    A_INLINE a_real dist2(a_point2 const &rhs) const { return a_point2_dist2(this, &rhs); }
    friend A_INLINE void operator+=(a_point2 &lhs, a_vector2 const &rhs) { a_point2_add(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point2 operator+(a_point2 const &lhs, a_vector2 const &rhs)
    {
        a_point2 res;
        a_point2_add(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE void operator-=(a_point2 &lhs, a_vector2 const &rhs) { a_point2_sub(&lhs, &rhs, &lhs); }
    friend A_INLINE a_point2 operator-(a_point2 const &lhs, a_vector2 const &rhs)
    {
        a_point2 res;
        a_point2_sub(&lhs, &rhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator-(a_point2 const &lhs, a_point2 const &rhs)
    {
        a_vector2 res;
        a_vector2_set(&res, &rhs, &lhs);
        return res;
    }
    friend A_INLINE void operator*=(a_point2 &lhs, a_real rhs) { a_point2_mul(&lhs, rhs, &lhs); }
    friend A_INLINE a_point2 operator*(a_real lhs, a_point2 const &rhs)
    {
        a_point2 res;
        a_point2_mul(&rhs, lhs, &res);
        return res;
    }
    friend A_INLINE a_point2 operator*(a_point2 const &lhs, a_real rhs)
    {
        a_point2 res;
        a_point2_mul(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE void operator/=(a_point2 &lhs, a_real rhs) { a_point2_div(&lhs, rhs, &lhs); }
    friend A_INLINE a_point2 operator/(a_point2 const &lhs, a_real rhs)
    {
        a_point2 res;
        a_point2_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator+(a_point2 const &rhs)
    {
        a_vector2 res;
        a_point2_pos(&rhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator-(a_point2 const &rhs)
    {
        a_vector2 res;
        a_point2_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_POINT2_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_POINT2_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_POINT2_C)

A_INTERN void a_vector2_set(a_vector2 *ctx, a_point2 const *p, a_point2 const *q)
{
    ctx->x = q->x - p->x;
    ctx->y = q->y - p->y;
}
A_INTERN void a_point2_val(a_point2 const *ctx, a_real *x, a_real *y)
{
    *x = ctx->x;
    *y = ctx->y;
}
A_INTERN void a_point2_set_val(a_point2 *ctx, a_real x, a_real y)
{
    ctx->x = x;
    ctx->y = y;
}
A_INTERN void a_point2_pol(a_point2 const *ctx, a_real *rho, a_real *theta)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
}
A_INTERN void a_point2_set_pol(a_point2 *ctx, a_real rho, a_real theta)
{
    a_real_pol2cart(rho, theta, &ctx->x, &ctx->y);
}
A_INTERN void a_point2_add(a_point2 const *lhs, a_vector2 const *rhs, a_point2 *res)
{
    res->x = lhs->x + rhs->x;
    res->y = lhs->y + rhs->y;
}
A_INTERN void a_point2_sub(a_point2 const *lhs, a_vector2 const *rhs, a_point2 *res)
{
    res->x = lhs->x - rhs->x;
    res->y = lhs->y - rhs->y;
}
A_INTERN void a_point2_mul(a_point2 const *lhs, a_real rhs, a_point2 *res)
{
    res->x = lhs->x * rhs;
    res->y = lhs->y * rhs;
}
A_INTERN void a_point2_div(a_point2 const *lhs, a_real rhs, a_point2 *res)
{
    res->x = lhs->x / rhs;
    res->y = lhs->y / rhs;
}
A_INTERN void a_point2_pos(a_point2 const *ctx, a_vector2 *res)
{
    res->x = +ctx->x;
    res->y = +ctx->y;
}
A_INTERN void a_point2_neg(a_point2 const *ctx, a_vector2 *res)
{
    res->x = -ctx->x;
    res->y = -ctx->y;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_POINT2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_POINT2_C */

/*! @} a_point2 */

#endif /* a/point2.h */
