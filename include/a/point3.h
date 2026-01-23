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

/*! static cast to @ref a_point3 */
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

/*!
 @brief set a 3D vector as the difference from point p to point q.
*/
A_INTERN void a_vector3_set(a_vector3 *ctx, a_point3 const *p, a_point3 const *q);

/*!
 @brief get the cartesian coordinates of a 3D point.
*/
A_INTERN void a_point3_val(a_point3 const *ctx, a_real *x, a_real *y, a_real *z);
/*!
 @brief set the cartesian coordinates of a 3D point.
*/
A_INTERN void a_point3_set_val(a_point3 *ctx, a_real x, a_real y, a_real z);
/*!
 @brief get the cylindrical coordinates of a 3D point.
*/
A_INTERN void a_point3_cyl(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z);
/*!
 @brief set the cylindrical coordinates of a 3D point.
*/
A_INTERN void a_point3_set_cyl(a_point3 *ctx, a_real rho, a_real theta, a_real z);
/*!
 @brief get the spherical coordinates of a 3D point.
*/
A_INTERN void a_point3_sph(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *alpha);
/*!
 @brief set the spherical coordinates of a 3D point.
*/
A_INTERN void a_point3_set_sph(a_point3 *ctx, a_real rho, a_real theta, a_real alpha);

/*!
 @brief add a 3D vector to a 3D point.
*/
A_INTERN void a_point3_add(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
/*!
 @brief subtract a 3D vector from a 3D point.
*/
A_INTERN void a_point3_sub(a_point3 const *lhs, a_vector3 const *rhs, a_point3 *res);
/*!
 @brief multiplie a 3D point by a scalar.
*/
A_INTERN void a_point3_mul(a_point3 const *lhs, a_real rhs, a_point3 *res);
/*!
 @brief divide a 3D point by a scalar.
*/
A_INTERN void a_point3_div(a_point3 const *lhs, a_real rhs, a_point3 *res);
/*!
 @brief convert it into a vector from the origin to the point.
*/
A_INTERN void a_point3_pos(a_point3 const *ctx, a_vector3 *res);
/*!
 @brief convert it into a vector from the point to the origin.
*/
A_INTERN void a_point3_neg(a_point3 const *ctx, a_vector3 *res);

/*!
 @brief compute the distance between two 3D points.
 @details In three dimensions,
 let point \f$p\f$ have coordinates \f$(p_1,p_2,p_3)\f$ and
 let point \f$q\f$ have coordinates \f$(q_1,q_2,q_3)\f$.
 Then the distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)=\sqrt{(p_1-q_1)^2+(p_2-q_2)^2+(p_3-q_3)^2}
 \f]
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return the distance between two 3D points
*/
A_EXTERN a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs);
/*!
 @brief compute the squared distance between two 3D points.
 @details In three dimensions,
 let point \f$p\f$ have coordinates \f$(p_1,p_2,p_3)\f$ and
 let point \f$q\f$ have coordinates \f$(q_1,q_2,q_3)\f$.
 Then the squared distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)^2=(p_1-q_1)^2+(p_2-q_2)^2+(p_3-q_3)^2
 \f]
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return the squared distance between two 3D points
*/
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
    /*! @copybrief a_point3_val @see a_point3_val */
    A_INLINE void val(a_real &x_, a_real &y_, a_real &z_) const
    {
        a_point3_val(this, &x_, &y_, &z_);
    }
    /*! @copybrief a_point3_set_val @see a_point3_set_val */
    A_INLINE void set_val(a_real x_, a_real y_, a_real z_)
    {
        a_point3_set_val(this, x_, y_, z_);
    }
    /*! @copybrief a_point3_cyl @see a_point3_cyl */
    A_INLINE void cyl(a_real &rho, a_real &theta, a_real &z_) const
    {
        a_point3_cyl(this, &rho, &theta, &z_);
    }
    /*! @copybrief a_point3_set_cyl @see a_point3_set_cyl */
    A_INLINE void set_cyl(a_real rho, a_real theta, a_real z_)
    {
        a_point3_set_cyl(this, rho, theta, z_);
    }
    /*! @copybrief a_point3_sph @see a_point3_sph */
    A_INLINE void sph(a_real &rho, a_real &theta, a_real &alpha) const
    {
        a_point3_sph(this, &rho, &theta, &alpha);
    }
    /*! @copybrief a_point3_set_sph @see a_point3_set_sph */
    A_INLINE void set_sph(a_real rho, a_real theta, a_real alpha)
    {
        a_point3_set_sph(this, rho, theta, alpha);
    }
    /*! @copybrief a_point3_add @see a_point3_add */
    A_INLINE void add(a_vector3 const &rhs, a_point3 &res) const
    {
        a_point3_add(this, &rhs, &res);
    }
    /*! @copybrief a_point3_sub @see a_point3_sub */
    A_INLINE void sub(a_vector3 const &rhs, a_point3 &res) const
    {
        a_point3_sub(this, &rhs, &res);
    }
    /*! @copybrief a_point3_mul @see a_point3_mul */
    A_INLINE void mul(a_real rhs, a_point3 &res) const
    {
        a_point3_mul(this, rhs, &res);
    }
    /*! @copybrief a_point3_div @see a_point3_div */
    A_INLINE void div(a_real rhs, a_point3 &res) const
    {
        a_point3_div(this, rhs, &res);
    }
    /*! @copybrief a_point3_pos @see a_point3_pos */
    A_INLINE void pos(a_vector3 &res) const
    {
        a_point3_pos(this, &res);
    }
    /*! @copybrief a_point3_neg @see a_point3_neg */
    A_INLINE void neg(a_vector3 &res) const
    {
        a_point3_neg(this, &res);
    }
    /*! @copybrief a_point3_dist @see a_point3_dist */
    A_INLINE a_real dist(a_point3 const &rhs) const { return a_point3_dist(this, &rhs); }
    /*! @copybrief a_point3_dist2 @see a_point3_dist2 */
    A_INLINE a_real dist2(a_point3 const &rhs) const { return a_point3_dist2(this, &rhs); }
    /*! @copybrief a_point3_add @see a_point3_add */
    friend A_INLINE void operator+=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_add(&lhs, &rhs, &lhs); }
    /*! @copybrief a_point3_add @see a_point3_add */
    friend A_INLINE a_point3 operator+(a_point3 const &lhs, a_vector3 const &rhs)
    {
        a_point3 res;
        a_point3_add(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_point3_sub @see a_point3_sub */
    friend A_INLINE void operator-=(a_point3 &lhs, a_vector3 const &rhs) { a_point3_sub(&lhs, &rhs, &lhs); }
    /*! @copybrief a_point3_sub @see a_point3_sub */
    friend A_INLINE a_point3 operator-(a_point3 const &lhs, a_vector3 const &rhs)
    {
        a_point3 res;
        a_point3_sub(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_set @see a_vector3_set */
    friend A_INLINE a_vector3 operator-(a_point3 const &lhs, a_point3 const &rhs)
    {
        a_vector3 res;
        a_vector3_set(&res, &rhs, &lhs);
        return res;
    }
    /*! @copybrief a_point3_mul @see a_point3_mul */
    friend A_INLINE void operator*=(a_point3 &lhs, a_real rhs) { a_point3_mul(&lhs, rhs, &lhs); }
    /*! @copybrief a_point3_mul @see a_point3_mul */
    friend A_INLINE a_point3 operator*(a_real lhs, a_point3 const &rhs)
    {
        a_point3 res;
        a_point3_mul(&rhs, lhs, &res);
        return res;
    }
    /*! @copybrief a_point3_mul @see a_point3_mul */
    friend A_INLINE a_point3 operator*(a_point3 const &lhs, a_real rhs)
    {
        a_point3 res;
        a_point3_mul(&lhs, rhs, &res);
        return res;
    }
    /*! @copybrief a_point3_div @see a_point3_div */
    friend A_INLINE void operator/=(a_point3 &lhs, a_real rhs) { a_point3_div(&lhs, rhs, &lhs); }
    /*! @copybrief a_point3_div @see a_point3_div */
    friend A_INLINE a_point3 operator/(a_point3 const &lhs, a_real rhs)
    {
        a_point3 res;
        a_point3_div(&lhs, rhs, &res);
        return res;
    }
    /*! @copybrief a_point3_pos @see a_point3_pos */
    friend A_INLINE a_vector3 operator+(a_point3 const &rhs)
    {
        a_vector3 res;
        a_point3_pos(&rhs, &res);
        return res;
    }
    /*! @copybrief a_point3_neg @see a_point3_neg */
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
A_INTERN void a_point3_cyl(a_point3 const *ctx, a_real *rho, a_real *theta, a_real *z)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
    *z = ctx->z;
}
A_INTERN void a_point3_set_cyl(a_point3 *ctx, a_real rho, a_real theta, a_real z)
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
