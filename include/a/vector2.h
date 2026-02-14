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

/*! static cast to @ref a_vector2 */
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
/*! @cond */
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
/*! @endcond */
#endif /* A_HAVE_INLINE */

/*!
 @brief set the components of a 2D vector and normalize it in place.
 @return the original length of the vector
*/
A_INTERN a_real a_vector2_set_dir(a_vector2 *ctx, a_real x, a_real y);
/*!
 @brief get the cartesian coordinates of a 2D vector.
*/
A_INTERN void a_vector2_val(a_vector2 const *ctx, a_real *x, a_real *y);
/*!
 @brief set the cartesian coordinates of a 2D vector.
*/
A_INTERN void a_vector2_set_val(a_vector2 *ctx, a_real x, a_real y);
/*!
 @brief get the polar coordinates of a 2D vector.
*/
A_INTERN void a_vector2_pol(a_vector2 const *ctx, a_real *rho, a_real *theta);
/*!
 @brief set the polar coordinates of a 2D vector.
*/
A_INTERN void a_vector2_set_pol(a_vector2 *ctx, a_real rho, a_real theta);

/*!
 @brief add a 2D vector to a 2D vector.
*/
A_INTERN void a_vector2_add(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res);
/*!
 @brief subtract a 2D vector from a 2D vector.
*/
A_INTERN void a_vector2_sub(a_vector2 const *lhs, a_vector2 const *rhs, a_vector2 *res);
/*!
 @brief multiplie a 2D vector by a scalar.
*/
A_INTERN void a_vector2_mul(a_vector2 const *lhs, a_real rhs, a_vector2 *res);
/*!
 @brief divide a 2D vector by a scalar.
*/
A_INTERN void a_vector2_div(a_vector2 const *lhs, a_real rhs, a_vector2 *res);
/*!
 @brief negate a 2D vector.
*/
A_INTERN void a_vector2_neg(a_vector2 const *ctx, a_vector2 *res);

/*!
 @brief normalize a 2D vector in-place to unit length.
 @param[in] ctx points to the input vector
 @return the original length of the vector
*/
A_EXTERN a_real a_vector2_unit(a_vector2 *ctx);
/*!
 @brief compute the magnitude of a 2D vector.
 @details In two-dimensional space,
 a vector \f$\vec{v}\f$ with coordinates \f$(x,y)\f$ has a magnitude defined as:
 \f[
  \|\vec{v}\|=\sqrt{x^2+y^2}
 \f]
 @param[in] ctx points to the input vector
 @return the magnitude of the vector
*/
A_EXTERN a_real a_vector2_norm(a_vector2 const *ctx);
/*!
 @brief compute the squared magnitude of a 2D vector.
 @details In two-dimensional space,
 a vector \f$\vec{v}\f$ with coordinates \f$(x,y)\f$ has a squared magnitude defined as:
 \f[
  \|\vec{v}\|^2=x^2+y^2
 \f]
 @param[in] ctx points to the input vector
 @return the squared magnitude of the vector
*/
A_EXTERN a_real a_vector2_norm2(a_vector2 const *ctx);
/*!
 @brief compute the dot product (scalar product) of two 2D vectors.
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the dot product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \cdot \vec{b} = a_x b_x + a_y b_y
 \f]
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return the dot product of two 2D vectors
*/
A_EXTERN a_real a_vector2_dot(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief compute the distance between two 2D vectors.
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the distance between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  d(\vec{a},\vec{b})=\sqrt{(a_x-b_x)^2+(a_y-b_y)^2}
 \f]
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return the distance between two 2D vectors
*/
A_EXTERN a_real a_vector2_dist(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief compute the squared distance between two 2D vectors.
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the squared distance between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  d(\vec{a},\vec{b})^2=(a_x-b_x)^2+(a_y-b_y)^2
 \f]
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return the squared distance between two 2D vectors
*/
A_EXTERN a_real a_vector2_dist2(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief compute the angle between two 2D vectors in radians.
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the angle between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  \theta=\arccos\left(\frac{\vec{a}\cdot\vec{b}}{\|\vec{a}\|\|\vec{b}\|}\right)
        =\arccos\left(\frac{\vec{a}\cdot\vec{b}}{\sqrt{\|\vec{a}\|^2\|\vec{b}\|^2}}\right)
 \f]
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return the angle between two 2D vectors in radians, in the range \f$[0,\pi]\f$
  @retval 0 if the vector is null
*/
A_EXTERN a_real a_vector2_angle(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief check if two 2D vectors are orthogonal.
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return whether the vectors are nearly orthogonal
  @retval true if the vector is null
*/
A_EXTERN a_bool a_vector2_isver(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief check if two 2D vectors are parallel or anti-parallel.
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return whether the vectors are nearly parallel or anti-parallel
  @retval true if the vector is null
*/
A_EXTERN a_bool a_vector2_ispar(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief compute the cross product (vector product) of two 2D vectors
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the cross product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \times \vec{b} = a_x b_y - a_y b_x
 \f]
 https://en.wikipedia.org/wiki/Cross_product
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @return the cross product of two 2D vectors
*/
A_EXTERN a_real a_vector2_cross(a_vector2 const *lhs, a_vector2 const *rhs);
/*!
 @brief compute the outer product (tensor product) of two 2D vectors.
 @details In two-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y)\f$.
 Then the outer product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \otimes \vec{b} = \begin{bmatrix}
   a_x b_x & a_x b_y \\ a_y b_x & a_y b_y
  \end{bmatrix}
 \f]
 https://en.wikipedia.org/wiki/Outer_product
 @param[in] lhs is left-hand side 2D vector
 @param[in] rhs is right-hand side 2D vector
 @param[out] res stores the 2×2 matrix in row-major order
*/
A_EXTERN void a_vector2_outer(a_vector2 const *lhs, a_vector2 const *rhs, a_real res[4]);

/*!
 @brief rotate a 2D vector by a specified angle (in radians).
 @details In two-dimensional space,
 let \f$v\f$ be any vector to rotate by angle \f$\theta\f$ (right hand rule, anticlockwise).
 Then the rotated vector \f$\vec{v}'\f$ is given by:
 \f[
  \vec{v}' = \begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \vec{v}
 \f]
 https://en.wikipedia.org/wiki/Rotation_matrix
 @param[in] ctx points to the input vector to rotate
 @param[in] sin is precomputed \f$\sin(\theta)\f$
 @param[in] cos is precomputed \f$\cos(\theta)\f$
 @param[out] res stores the result vector
*/
A_EXTERN void a_vector2_rot_(a_vector2 const *ctx, a_real sin, a_real cos, a_vector2 *res);
/*!
 @brief rotate a 2D vector by a specified angle (in radians).
 @details In two-dimensional space,
 let \f$v\f$ be any vector to rotate by angle \f$\theta\f$ (right hand rule, anticlockwise).
 Then the rotated vector \f$\vec{v}'\f$ is given by:
 \f[
  \vec{v}' = \begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \vec{v}
 \f]
 https://en.wikipedia.org/wiki/Rotation_matrix
 @param[in] ctx points to the input vector to rotate
 @param[in] angle is rotation angle in radians
 @param[out] res stores the result vector
*/
A_EXTERN void a_vector2_rot(a_vector2 const *ctx, a_real angle, a_vector2 *res);

#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
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
    /*! @copybrief a_vector2_set @see a_vector2_set */
    A_INLINE void set(a_point2 const &p, a_point2 const &q);
    /*! @copybrief a_vector2_set_dir @see a_vector2_set_dir */
    A_INLINE a_real set_dir(a_real x_, a_real y_)
    {
        return a_vector2_set_dir(this, x_, y_);
    }
    /*! @copybrief a_vector2_val @see a_vector2_val */
    A_INLINE void val(a_real &x_, a_real &y_) const
    {
        a_vector2_val(this, &x_, &y_);
    }
    /*! @copybrief a_vector2_set_val @see a_vector2_set_val */
    A_INLINE void set_val(a_real x_, a_real y_)
    {
        a_vector2_set_val(this, x_, y_);
    }
    /*! @copybrief a_vector2_pol @see a_vector2_pol */
    A_INLINE void pol(a_real &rho, a_real &theta) const
    {
        a_vector2_pol(this, &rho, &theta);
    }
    /*! @copybrief a_vector2_set_pol @see a_vector2_set_pol */
    A_INLINE void set_pol(a_real rho, a_real theta)
    {
        a_vector2_set_pol(this, rho, theta);
    }
    /*! @copybrief a_vector2_add @see a_vector2_add */
    A_INLINE void add(a_vector2 const &rhs, a_vector2 &res) const
    {
        a_vector2_add(this, &rhs, &res);
    }
    /*! @copybrief a_vector2_sub @see a_vector2_sub */
    A_INLINE void sub(a_vector2 const &rhs, a_vector2 &res) const
    {
        a_vector2_sub(this, &rhs, &res);
    }
    /*! @copybrief a_vector2_mul @see a_vector2_mul */
    A_INLINE void mul(a_real rhs, a_vector2 &res) const
    {
        a_vector2_mul(this, rhs, &res);
    }
    /*! @copybrief a_vector2_div @see a_vector2_div */
    A_INLINE void div(a_real rhs, a_vector2 &res) const
    {
        a_vector2_div(this, rhs, &res);
    }
    /*! @copybrief a_vector2_neg @see a_vector2_neg */
    A_INLINE void neg(a_vector2 &res) const
    {
        a_vector2_neg(this, &res);
    }
    /*! @copybrief a_vector2_unit @see a_vector2_unit */
    A_INLINE a_real unit() { return a_vector2_unit(this); }
    /*! @copybrief a_vector2_norm @see a_vector2_norm */
    A_INLINE a_real norm() const { return a_vector2_norm(this); }
    /*! @copybrief a_vector2_norm2 @see a_vector2_norm2 */
    A_INLINE a_real norm2() const { return a_vector2_norm2(this); }
    /*! @copybrief a_vector2_dot @see a_vector2_dot */
    A_INLINE a_real dot(a_vector2 const &rhs) const { return a_vector2_dot(this, &rhs); }
    /*! @copybrief a_vector2_dist @see a_vector2_dist */
    A_INLINE a_real dist(a_vector2 const &rhs) const { return a_vector2_dist(this, &rhs); }
    /*! @copybrief a_vector2_dist2 @see a_vector2_dist2 */
    A_INLINE a_real dist2(a_vector2 const &rhs) const { return a_vector2_dist2(this, &rhs); }
    /*! @copybrief a_vector2_dist2 @see a_vector2_dist2 */
    A_INLINE a_real angle(a_vector2 const &rhs) const { return a_vector2_angle(this, &rhs); }
    /*! @copybrief a_vector2_isver @see a_vector2_isver */
    A_INLINE a_bool isver(a_vector2 const &rhs) const { return a_vector2_isver(this, &rhs); }
    /*! @copybrief a_vector2_ispar @see a_vector2_ispar */
    A_INLINE a_bool ispar(a_vector2 const &rhs) const { return a_vector2_ispar(this, &rhs); }
    /*! @copybrief a_vector2_cross @see a_vector2_cross */
    A_INLINE a_real cross(a_vector2 const &rhs) const { return a_vector2_cross(this, &rhs); }
    /*! @copybrief a_vector2_outer @see a_vector2_outer */
    A_INLINE void outer(a_vector2 const &rhs, a_real res[4]) const { a_vector2_outer(this, &rhs, res); }
    /*! @copybrief a_vector2_rot @see a_vector2_rot */
    A_INLINE void rot(a_real angle, a_vector2 &res) const { a_vector2_rot(this, angle, &res); }
    /*! @copybrief a_vector2_rot_ @see a_vector2_rot_ */
    A_INLINE void rot(a_real sin, a_real cos, a_vector2 &res) const { a_vector2_rot_(this, sin, cos, &res); }
    /*! @copybrief a_vector2_cross @see a_vector2_cross */
    friend A_INLINE a_real operator^(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        return a_vector2_cross(&lhs, &rhs);
    }
    /*! @copybrief a_vector2_add @see a_vector2_add */
    friend A_INLINE void operator+=(a_vector2 &lhs, a_vector2 const &rhs) { a_vector2_add(&lhs, &rhs, &lhs); }
    /*! @copybrief a_vector2_add @see a_vector2_add */
    friend A_INLINE a_vector2 operator+(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_add(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector2_sub @see a_vector2_sub */
    friend A_INLINE void operator-=(a_vector2 &lhs, a_vector2 const &rhs) { a_vector2_sub(&lhs, &rhs, &lhs); }
    /*! @copybrief a_vector2_sub @see a_vector2_sub */
    friend A_INLINE a_vector2 operator-(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_sub(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector2_dot @see a_vector2_dot */
    friend A_INLINE a_real operator*(a_vector2 const &lhs, a_vector2 const &rhs)
    {
        return a_vector2_dot(&lhs, &rhs);
    }
    /*! @copybrief a_vector2_mul @see a_vector2_mul */
    friend A_INLINE void operator*=(a_vector2 &lhs, a_real rhs) { a_vector2_mul(&lhs, rhs, &lhs); }
    /*! @copybrief a_vector2_mul @see a_vector2_mul */
    friend A_INLINE a_vector2 operator*(a_real lhs, a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_mul(&rhs, lhs, &res);
        return res;
    }
    /*! @copybrief a_vector2_mul @see a_vector2_mul */
    friend A_INLINE a_vector2 operator*(a_vector2 const &lhs, a_real rhs)
    {
        a_vector2 res;
        a_vector2_mul(&lhs, rhs, &res);
        return res;
    }
    /*! @copybrief a_vector2_div @see a_vector2_div */
    friend A_INLINE void operator/=(a_vector2 &lhs, a_real rhs) { a_vector2_div(&lhs, rhs, &lhs); }
    /*! @copybrief a_vector2_div @see a_vector2_div */
    friend A_INLINE a_vector2 operator/(a_vector2 const &lhs, a_real rhs)
    {
        a_vector2 res;
        a_vector2_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector2 operator+(a_vector2 const &rhs) { return rhs; }
    /*! @copybrief a_vector2_neg @see a_vector2_neg */
    friend A_INLINE a_vector2 operator-(a_vector2 const &rhs)
    {
        a_vector2 res;
        a_vector2_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_VECTOR2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_INLINE
/*! @endcond */
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
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* LIBA_VECTOR2_C */

/*! @} a_vector2 */

#endif /* a/vector2.h */
