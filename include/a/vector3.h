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
/*! @cond */
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
/*! @endcond */
#endif /* A_HAVE_INLINE */

/*!
 @brief set the components of a 3D vector and normalize it in place.
 @return the original length of the vector
*/
A_INTERN a_real a_vector3_set_dir(a_vector3 *ctx, a_real x, a_real y, a_real z);
/*!
 @brief get the cartesian coordinates of a 3D vector.
*/
A_INTERN void a_vector3_val(a_vector3 const *ctx, a_real *x, a_real *y, a_real *z);
/*!
 @brief set the cartesian coordinates of a 3D vector.
*/
A_INTERN void a_vector3_set_val(a_vector3 *ctx, a_real x, a_real y, a_real z);
/*!
 @brief get the cylindrical coordinates of a 3D vector.
*/
A_INTERN void a_vector3_cyl(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *z);
/*!
 @brief set the cylindrical coordinates of a 3D vector.
*/
A_INTERN void a_vector3_set_cyl(a_vector3 *ctx, a_real rho, a_real theta, a_real z);
/*!
 @brief get the spherical coordinates of a 3D vector.
*/
A_INTERN void a_vector3_sph(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *alpha);
/*!
 @brief set the spherical coordinates of a 3D vector.
*/
A_INTERN void a_vector3_set_sph(a_vector3 *ctx, a_real rho, a_real theta, a_real alpha);

/*!
 @brief add a 3D vector to a 3D vector.
*/
A_INTERN void a_vector3_add(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
/*!
 @brief subtract a 3D vector from a 3D vector.
*/
A_INTERN void a_vector3_sub(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
/*!
 @brief multiplie a 3D vector by a scalar.
*/
A_INTERN void a_vector3_mul(a_vector3 const *lhs, a_real rhs, a_vector3 *res);
/*!
 @brief divide a 3D vector by a scalar.
*/
A_INTERN void a_vector3_div(a_vector3 const *lhs, a_real rhs, a_vector3 *res);
/*!
 @brief negate a 3D vector.
*/
A_INTERN void a_vector3_neg(a_vector3 const *ctx, a_vector3 *res);

/*!
 @brief normalize a 3D vector in-place to unit length.
 @param[in] ctx points to the input vector
 @return the original length of the vector
*/
A_EXTERN a_real a_vector3_unit(a_vector3 *ctx);
/*!
 @brief compute the magnitude of a 3D vector.
 @details In three-dimensional space,
 a vector \f$\vec{v}\f$ with coordinates \f$(x,y,z)\f$ has a magnitude defined as:
 \f[
  \|\vec{v}\|=\sqrt{x^2+y^2+z^2}
 \f]
 @param[in] ctx points to the input vector
 @return the magnitude of the vector
*/
A_EXTERN a_real a_vector3_norm(a_vector3 const *ctx);
/*!
 @brief compute the squared magnitude of a 3D vector.
 @details In three-dimensional space,
 a vector \f$\vec{v}\f$ with coordinates \f$(x,y,z)\f$ has a squared magnitude defined as:
 \f[
  \|\vec{v}\|^2=x^2+y^2+z^2
 \f]
 @param[in] ctx points to the input vector
 @return the squared magnitude of the vector
*/
A_EXTERN a_real a_vector3_norm2(a_vector3 const *ctx);
/*!
 @brief compute the dot product (scalar product) of two 3D vectors.
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the dot product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \cdot \vec{b} = a_x b_x + a_y b_y + a_z b_z
 \f]
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return the dot product of two 3D vectors
*/
A_EXTERN a_real a_vector3_dot(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief compute the distance between two 3D vectors.
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the distance between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  d(\vec{a},\vec{b})=\sqrt{(a_x-b_x)^2+(a_y-b_y)^2+(a_z-b_z)^2}
 \f]
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return the distance between two 3D vectors
*/
A_EXTERN a_real a_vector3_dist(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief compute the squared distance between two 3D vectors.
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the squared distance between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  d(\vec{a},\vec{b})^2=(a_x-b_x)^2+(a_y-b_y)^2+(a_z-b_z)^2
 \f]
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return the squared distance between two 3D vectors
*/
A_EXTERN a_real a_vector3_dist2(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief compute the angle between two 3D vectors in radians.
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the angle between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  \theta=\arccos\left(\frac{\vec{a}\cdot\vec{b}}{\|\vec{a}\|\|\vec{b}\|}\right)
        =\arccos\left(\frac{\vec{a}\cdot\vec{b}}{\sqrt{\|\vec{a}\|^2\|\vec{b}\|^2}}\right)
 \f]
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return the angle between two 3D vectors in radians, in the range \f$[0,\pi]\f$
  @retval 0 if the vector is null
*/
A_EXTERN a_real a_vector3_angle(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief check if two 3D vectors are orthogonal.
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return whether the vectors are nearly orthogonal
  @retval true if the vector is null
*/
A_EXTERN a_bool a_vector3_isver(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief check if two 3D vectors are parallel or anti-parallel.
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @return whether the vectors are nearly parallel or anti-parallel
  @retval true if the vector is null
*/
A_EXTERN a_bool a_vector3_ispar(a_vector3 const *lhs, a_vector3 const *rhs);
/*!
 @brief compute the cross product (vector product) of two 3D vectors
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the cross product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \times \vec{b} = \begin{pmatrix}
   a_y b_z - a_z b_y \\ a_z b_x - a_x b_z \\ a_x b_y - a_y b_x
  \end{pmatrix}
 \f]
 https://en.wikipedia.org/wiki/Cross_product
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @param[out] res stores the result vector
*/
A_EXTERN void a_vector3_cross(a_vector3 const *lhs, a_vector3 const *rhs, a_vector3 *res);
/*!
 @brief compute the outer product (tensor product) of two 3D vectors.
 @details In three-dimensional space,
 let vector \f$\vec{a}\f$ have coordinates \f$(a_x,a_y,a_z)\f$ and
 let vector \f$\vec{b}\f$ have coordinates \f$(b_x,b_y,b_z)\f$.
 Then the outer product of vectors \f$\vec{a}\f$ and \f$\vec{b}\f$ is defined as:
 \f[
  \vec{a} \otimes \vec{b} = \begin{bmatrix}
   a_x b_x & a_x b_y & a_x b_z \\ a_y b_x & a_y b_y & a_y b_z \\ a_z b_x & a_z b_y & a_z b_z
  \end{bmatrix}
 \f]
 https://en.wikipedia.org/wiki/Outer_product
 @param[in] lhs is left-hand side 3D vector
 @param[in] rhs is right-hand side 3D vector
 @param[out] res stores the 3×3 matrix in row-major order
*/
A_EXTERN void a_vector3_outer(a_vector3 const *lhs, a_vector3 const *rhs, a_real res[9]);
/*!
 @brief construct an orthonormal basis from a given 3D direction vector.
 @details Let \f$\vec{n}\f$ be a non-zero 3D vector. The orthonormal vectors \f$\vec{u}\f$ and \f$\vec{v}\f$
 such that \f$\{\vec{u},\vec{v},\vec{n}\}\f$ forms a right-handed orthogonal basis are given by:<br><br>
 If \f$|c_x| \ge |c_y|\f$:
 \f[
  \vec{u} = \frac{\mathbf{j}\times\vec{n}}{\|\mathbf{j}\times\vec{n}\|} \quad
  \vec{v} = \frac{\vec{n}\times\vec{u}}{\|\vec{n}\times\vec{u}\|}
 \f]
 Otherwise:
 \f[
  \vec{v} = \frac{\vec{n}\times\mathbf{i}}{\|\vec{n}\times\mathbf{i}\|} \quad
  \vec{u} = \frac{\vec{v}\times\vec{n}}{\|\vec{v}\times\vec{n}\|}
 \f]
 @param[in] ctx points to the input direction vector
 @param[out] u stores first orthogonal unit vector
 @param[out] v stores second orthogonal unit vector
 @return error code value
  @retval <0 failure
  @retval 0 success
*/
A_EXTERN int a_vector3_ortho(a_vector3 const *ctx, a_vector3 *u, a_vector3 *v);
/*!
 @brief rotate a 3D vector around an arbitrary unit axis using Rodrigues' rotation formula.
 @details In three-dimensional space, let \f$u\f$ be a unit vector defining a rotation axis and
 let \f$v\f$ be any vector to rotate about \f$u\f$ by angle \f$\theta\f$ (right hand rule, anticlockwise).
 Then the rotated vector \f$\vec{v}'\f$ is given by:
 \f[
  \vec{v}' = \vec{v}\cos\theta + (\vec{u}\times\vec{v})\sin\theta + \vec{u}(\vec{u}\cdot\vec{v})(1-\cos\theta)
 \f]
 https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
 @param[in] ctx points to the input vector to rotate
 @param[in] dir points to the normalized rotation axis
 @param[in] sin is precomputed \f$\sin(\theta)\f$
 @param[in] cos is precomputed \f$\cos(\theta)\f$
 @param[out] res stores the result vector
*/
A_EXTERN void a_vector3_rot_(a_vector3 const *ctx, a_vector3 const *dir, a_real sin, a_real cos, a_vector3 *res);
/*!
 @brief rotate a 3D vector around an arbitrary unit axis using Rodrigues' rotation formula.
 @details In three-dimensional space, let \f$u\f$ be a unit vector defining a rotation axis and
 let \f$v\f$ be any vector to rotate about \f$u\f$ by angle \f$\theta\f$ (right hand rule, anticlockwise).
 Then the rotated vector \f$\vec{v}'\f$ is given by:
 \f[
  \vec{v}' = \vec{v}\cos\theta + (\vec{u}\times\vec{v})\sin\theta + \vec{u}(\vec{u}\cdot\vec{v})(1-\cos\theta)
 \f]
 https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
 @param[in] ctx points to the input vector to rotate
 @param[in] dir points to the normalized rotation axis
 @param[in] angle is rotation angle in radians
 @param[out] res stores the result vector
*/
A_EXTERN void a_vector3_rot(a_vector3 const *ctx, a_vector3 const *dir, a_real angle, a_vector3 *res);
/*!
 @brief rotate a 2D basis in the plane spanned by two orthogonal vectors.
 @details Let \f$\vec{u}\f$ and \f$\vec{v}\f$ be an orthonormal basis in the plane,
 and let \f$\theta\f$ be the counterclockwise rotation angle about the origin.
 The new basis vectors \f$\vec{u}'\f$ and \f$\vec{v}'\f$ after rotation are given by:
 \f{aligned}{
  \vec{u}'=\left(\begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \begin{bmatrix} 1 \\ 0 \end{bmatrix}\right)
           \cdot \begin{bmatrix} \vec{u} \\ \vec{v} \end{bmatrix}
          =\cos\theta\vec{u}+\sin\theta\vec{v} \\
  \vec{v}'=\left(\begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \begin{bmatrix} 0 \\ 1 \end{bmatrix}\right)
           \cdot \begin{bmatrix} \vec{u} \\ \vec{v} \end{bmatrix}
          =\cos\theta\vec{v}-\sin\theta\vec{u}
 \f}
 @param[in] iu points to first axis vector
 @param[in] iv points to second axis vector
 @param[in] angle is rotation angle in radians
 @param[out] ou stores rotated first axis vector
 @param[out] ov stores rotated second axis vector
*/
A_EXTERN void a_vector3_rot2d(a_vector3 const *iu, a_vector3 const *iv, a_real angle,
                              a_vector3 *ou, a_vector3 *ov);

#if !defined A_HAVE_INLINE || defined(LIBA_VECTOR3_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
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
    /*! @copybrief a_vector3_set @see a_vector3_set */
    A_INLINE void set(a_point3 const &p, a_point3 const &q);
    /*! @copybrief a_vector3_set_dir @see a_vector3_set_dir */
    A_INLINE a_real set_dir(a_real x_, a_real y_, a_real z_)
    {
        return a_vector3_set_dir(this, x_, y_, z_);
    }
    /*! @copybrief a_vector3_val @see a_vector3_val */
    A_INLINE void val(a_real &x_, a_real &y_, a_real &z_) const
    {
        a_vector3_val(this, &x_, &y_, &z_);
    }
    /*! @copybrief a_vector3_set_val @see a_vector3_set_val */
    A_INLINE void set_val(a_real x_, a_real y_, a_real z_)
    {
        a_vector3_set_val(this, x_, y_, z_);
    }
    /*! @copybrief a_vector3_cyl @see a_vector3_cyl */
    A_INLINE void cyl(a_real &rho, a_real &theta, a_real &z_) const
    {
        a_vector3_cyl(this, &rho, &theta, &z_);
    }
    /*! @copybrief a_vector3_set_cyl @see a_vector3_set_cyl */
    A_INLINE void set_cyl(a_real rho, a_real theta, a_real z_)
    {
        a_vector3_set_cyl(this, rho, theta, z_);
    }
    /*! @copybrief a_vector3_sph @see a_vector3_sph */
    A_INLINE void sph(a_real &rho, a_real &theta, a_real &alpha) const
    {
        a_vector3_sph(this, &rho, &theta, &alpha);
    }
    /*! @copybrief a_vector3_set_sph @see a_vector3_set_sph */
    A_INLINE void set_sph(a_real rho, a_real theta, a_real alpha)
    {
        a_vector3_set_sph(this, rho, theta, alpha);
    }
    /*! @copybrief a_vector3_add @see a_vector3_add */
    A_INLINE void add(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_add(this, &rhs, &res);
    }
    /*! @copybrief a_vector3_sub @see a_vector3_sub */
    A_INLINE void sub(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_sub(this, &rhs, &res);
    }
    /*! @copybrief a_vector3_mul @see a_vector3_mul */
    A_INLINE void mul(a_real rhs, a_vector3 &res) const
    {
        a_vector3_mul(this, rhs, &res);
    }
    /*! @copybrief a_vector3_div @see a_vector3_div */
    A_INLINE void div(a_real rhs, a_vector3 &res) const
    {
        a_vector3_div(this, rhs, &res);
    }
    /*! @copybrief a_vector3_neg @see a_vector3_neg */
    A_INLINE void neg(a_vector3 &res) const
    {
        a_vector3_neg(this, &res);
    }
    /*! @copybrief a_vector3_unit @see a_vector3_unit */
    A_INLINE a_real unit() { return a_vector3_unit(this); }
    /*! @copybrief a_vector3_norm @see a_vector3_norm */
    A_INLINE a_real norm() const { return a_vector3_norm(this); }
    /*! @copybrief a_vector3_norm2 @see a_vector3_norm2 */
    A_INLINE a_real norm2() const { return a_vector3_norm2(this); }
    /*! @copybrief a_vector3_dot @see a_vector3_dot */
    A_INLINE a_real dot(a_vector3 const &rhs) const { return a_vector3_dot(this, &rhs); }
    /*! @copybrief a_vector3_dist @see a_vector3_dist */
    A_INLINE a_real dist(a_vector3 const &rhs) const { return a_vector3_dist(this, &rhs); }
    /*! @copybrief a_vector3_dist2 @see a_vector3_dist2 */
    A_INLINE a_real dist2(a_vector3 const &rhs) const { return a_vector3_dist2(this, &rhs); }
    /*! @copybrief a_vector3_angle @see a_vector3_angle */
    A_INLINE a_real angle(a_vector3 const &rhs) const { return a_vector3_angle(this, &rhs); }
    /*! @copybrief a_vector3_isver @see a_vector3_isver */
    A_INLINE a_bool isver(a_vector3 const &rhs) const { return a_vector3_isver(this, &rhs); }
    /*! @copybrief a_vector3_ispar @see a_vector3_ispar */
    A_INLINE a_bool ispar(a_vector3 const &rhs) const { return a_vector3_ispar(this, &rhs); }
    /*! @copybrief a_vector3_cross @see a_vector3_cross */
    A_INLINE void cross(a_vector3 const &rhs, a_vector3 &res) const
    {
        a_vector3_cross(this, &rhs, &res);
    }
    /*! @copybrief a_vector3_outer @see a_vector3_outer */
    A_INLINE void outer(a_vector3 const &rhs, a_real res[9]) const
    {
        a_vector3_outer(this, &rhs, res);
    }
    /*! @copybrief a_vector3_ortho @see a_vector3_ortho */
    A_INLINE int ortho(a_vector3 &u, a_vector3 &v) const
    {
        return a_vector3_ortho(this, &u, &v);
    }
    /*! @copybrief a_vector3_rot @see a_vector3_rot */
    A_INLINE void rot(a_vector3 const &dir, a_real angle, a_vector3 &res) const
    {
        a_vector3_rot(this, &dir, angle, &res);
    }
    /*! @copybrief a_vector3_rot_ @see a_vector3_rot_ */
    A_INLINE void rot(a_vector3 const &dir, a_real sin, a_real cos, a_vector3 &res) const
    {
        a_vector3_rot_(this, &dir, sin, cos, &res);
    }
    /*! @copybrief a_vector3_rot2d @see a_vector3_rot2d */
    static A_INLINE void rot2d(a_vector3 const &iu, a_vector3 const &iv, a_real angle,
                               a_vector3 &ou, a_vector3 &ov)
    {
        a_vector3_rot2d(&iu, &iv, angle, &ou, &ov);
    }
    /*! @copybrief a_vector3_cross @see a_vector3_cross */
    friend A_INLINE a_vector3 operator^(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_cross(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_add @see a_vector3_add */
    friend A_INLINE void operator+=(a_vector3 &lhs, a_vector3 const &rhs) { a_vector3_add(&lhs, &rhs, &lhs); }
    /*! @copybrief a_vector3_add @see a_vector3_add */
    friend A_INLINE a_vector3 operator+(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_add(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_sub @see a_vector3_sub */
    friend A_INLINE void operator-=(a_vector3 &lhs, a_vector3 const &rhs) { a_vector3_sub(&lhs, &rhs, &lhs); }
    /*! @copybrief a_vector3_sub @see a_vector3_sub */
    friend A_INLINE a_vector3 operator-(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_sub(&lhs, &rhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_dot @see a_vector3_dot */
    friend A_INLINE a_real operator*(a_vector3 const &lhs, a_vector3 const &rhs)
    {
        return a_vector3_dot(&lhs, &rhs);
    }
    /*! @copybrief a_vector3_mul @see a_vector3_mul */
    friend A_INLINE void operator*=(a_vector3 &lhs, a_real rhs) { a_vector3_mul(&lhs, rhs, &lhs); }
    /*! @copybrief a_vector3_mul @see a_vector3_mul */
    friend A_INLINE a_vector3 operator*(a_real lhs, a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_mul(&rhs, lhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_mul @see a_vector3_mul */
    friend A_INLINE a_vector3 operator*(a_vector3 const &lhs, a_real rhs)
    {
        a_vector3 res;
        a_vector3_mul(&lhs, rhs, &res);
        return res;
    }
    /*! @copybrief a_vector3_div @see a_vector3_div */
    friend A_INLINE void operator/=(a_vector3 &lhs, a_real rhs) { a_vector3_div(&lhs, rhs, &lhs); }
    /*! @copybrief a_vector3_div @see a_vector3_div */
    friend A_INLINE a_vector3 operator/(a_vector3 const &lhs, a_real rhs)
    {
        a_vector3 res;
        a_vector3_div(&lhs, rhs, &res);
        return res;
    }
    friend A_INLINE a_vector3 operator+(a_vector3 const &rhs) { return rhs; }
    /*! @copybrief a_vector3_neg @see a_vector3_neg */
    friend A_INLINE a_vector3 operator-(a_vector3 const &rhs)
    {
        a_vector3 res;
        a_vector3_neg(&rhs, &res);
        return res;
    }
#endif /* __cplusplus */
};

#if defined(LIBA_VECTOR3_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_INLINE
/*! @endcond */
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
A_INTERN void a_vector3_cyl(a_vector3 const *ctx, a_real *rho, a_real *theta, a_real *z)
{
    a_real_cart2pol(ctx->x, ctx->y, rho, theta);
    *z = ctx->z;
}
A_INTERN void a_vector3_set_cyl(a_vector3 *ctx, a_real rho, a_real theta, a_real z)
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
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* LIBA_VECTOR3_C */

/*! @} a_vector3 */

#endif /* a/vector3.h */
