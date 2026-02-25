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
/*! @cond */
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
/*! @endcond */
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
 @details In three-dimensional space,
 let point \f$p\f$ have coordinates \f$(p_x,p_y,p_z)\f$ and
 let point \f$q\f$ have coordinates \f$(q_x,q_y,q_z)\f$.
 Then the distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)=\sqrt{(p_x-q_x)^2+(p_y-q_y)^2+(p_z-q_z)^2}
 \f]
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return the distance between two 3D points
*/
A_EXTERN a_real a_point3_dist(a_point3 const *lhs, a_point3 const *rhs);
/*!
 @brief compute the squared distance between two 3D points.
 @details In three-dimensional space,
 let point \f$p\f$ have coordinates \f$(p_x,p_y,p_z)\f$ and
 let point \f$q\f$ have coordinates \f$(q_x,q_y,q_z)\f$.
 Then the squared distance between \f$p\f$ and \f$q\f$ is given by:
 \f[
  d(p,q)^2=(p_x-q_x)^2+(p_y-q_y)^2+(p_z-q_z)^2
 \f]
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return the squared distance between two 3D points
*/
A_EXTERN a_real a_point3_dist2(a_point3 const *lhs, a_point3 const *rhs);

/*!
 @brief compute the minimum distance from a reference point to a point set.
 @param[in] ctx points to the reference point
 @param[in] i_p points to the points in memory
 @param[in] i_n number of the points in memory
 @param[out] o_p stores the nearest point; may be NULL
 @param[out] o_i stores the index of the nearest point; may be NULL
 @return the minimum distance from a reference point to a point set
  @retval +inf failure
*/
A_EXTERN a_real a_point3_mindist(a_point3 const *ctx, a_point3 const *i_p, a_size i_n,
                                 a_point3 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/);

/*!
 @brief compute the maximum distance from a reference point to a point set.
 @param[in] ctx points to the reference point
 @param[in] i_p points to the points in memory
 @param[in] i_n number of the points in memory
 @param[out] o_p stores the farthest point; may be NULL
 @param[out] o_i stores the index of the farthest point; may be NULL
 @return the maximum distance from a reference point to a point set
  @retval -inf failure
*/
A_EXTERN a_real a_point3_maxdist(a_point3 const *ctx, a_point3 const *i_p, a_size i_n,
                                 a_point3 *o_p /*=A_NULL*/, a_size *o_i /*=A_NULL*/);

/*!
 @brief compute linear interpolation (LERP) between two 3D points.
 @details Let \f$\vec{a}\f$ and \f$\vec{b}\f$ be two 3D points and let \f$t\f$ be the interpolation factor.
 Then the linear interpolation \f$\vec{p}\f$ between \f$\vec{a}\f$ and \f$\vec{b}\f$ is given by:
 \f[
  \vec{p} = \vec{a} + (\vec{b} - \vec{a}) * t
 \f]
 @param[in] lhs points to the starting point
 @param[in] rhs points to the ending point
 @param[in] val is the interpolation factor
 @param[out] res stores the interpolated point
*/
A_EXTERN void a_point3_lerp(a_point3 const *lhs, a_point3 const *rhs, a_real val, a_point3 *res);

/*!
 @brief compute the circumcenter and circumradius of a triangle defined by three 3D points.
 @param[in] p1 is the first 3D point on circle
 @param[in] p2 is the second 3D point on circle
 @param[in] p3 is the third 3D point on circle
 @param[out] pc stores the circumcenter
 @return the circumradius
  @retval 0 if points are collinear
 @see a_point3_tricir2
*/
A_EXTERN a_real a_point3_tricir(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 *pc);
/*!
 @brief compute the circumcenter and squared circumradius of a triangle defined by three 3D points.
 @details Solves for center (x,y,z) where distances to all three points are equal:
 \f[ (x_1-x)^2+(y_1-y)^2+(z_1-z)^2=(x_2-x)^2+(y_2-y)^2+(z_2-z)^2=(x_3-x)^2+(y_3-y)^2+(z_3-z)^2 \f]
 This simplifies to:
 \f{cases}{
  2(x_2−x_1)x + 2(y_2−y_1)y + 2(z_2−z_1)z = (x_2^2−x_1^2) + (y_2^2−y_1^2) + (z_2^2−z_1^2) \\
  2(x_3−x_1)x + 2(y_3−y_1)y + 2(z_3−z_1)z = (x_3^2−x_1^2) + (y_3^2−y_1^2) + (z_3^2−z_1^2)
 \f}
 The solution can be expressed in terms of parameters \f$k_1\f$ and \f$k_2\f$:
 \f{cases}{
  x=x_1+k_1(x_2−x_1)+k_2(x_2−x_1) \\
  y=y_1+k_1(y_2−y_1)+k_2(y_2−y_1) \\
  z=z_1+k_1(z_2−z_1)+k_2(z_2−z_1)
 \f}
 The parameters \f$k_1\f$ and \f$k_2\f$ are found by solving:
 \f{aligned}{
  2(\vec{v_1}\cdot\vec{v_1})k_1+2(\vec{v_1}\cdot\vec{v_2})k_2=\vec{v_1}\cdot\vec{v_1} \\
  2(\vec{v_1}\cdot\vec{v_2})k_1+2(\vec{v_2}\cdot\vec{v_2})k_2=\vec{v_2}\cdot\vec{v_2}
 \f}
 Where
 \f{aligned}{ \vec{v_1}&=(x_2−x_1,y_2−y_1,z_2−z_1) \\ \vec{v_2}&=(x_3−x_1,y_3−y_1,z_3−z_1) \f}
 Matrix form:
 \f[
  2\begin{bmatrix} a & b \\ b & c \end{bmatrix} \begin{bmatrix} k_1 \\ k_2 \end{bmatrix}
  =\begin{bmatrix} a \\ c \end{bmatrix}
 \f]
 Where
 \f{aligned}{
  a&=\vec{v_1}\cdot\vec{v_1} \\ b&=\vec{v_1}\cdot\vec{v_2} \\ c&=\vec{v_2}\cdot\vec{v_2}
 \f}
 Explicit Solution (Cramer's Rule):
 \f{aligned}{ k_1=\frac{c(a-b)}{2(ac-b^2)} \\ k_2=\frac{a(c-b)}{2(ac-b^2)} \f}
 Radius (r):
 \f[ r = \sqrt{(x_1-x)^2+(y_1-y)^2+(z_1-z)^2} \f]
 @param[in] p1 is the first 3D point on circle
 @param[in] p2 is the second 3D point on circle
 @param[in] p3 is the third 3D point on circle
 @param[out] pc stores the circumcenter
 @return the squared circumradius
  @retval 0 if points are collinear
*/
A_EXTERN a_real a_point3_tricir2(a_point3 const *p1, a_point3 const *p2, a_point3 const *p3, a_point3 *pc);

/*!
 @brief compute the circumcenter and circumradius of a tetrahedron defined by four 3D points.
 @param[in] p1 is the first 3D point on sphere
 @param[in] p2 is the second 3D point on sphere
 @param[in] p3 is the third 3D point on sphere
 @param[in] p4 is the fourth 3D point on sphere
 @param[out] pc stores the circumcenter
 @return the circumradius
  @retval 0 if points are coplanar
 @see a_point3_tetsph2
*/
A_EXTERN a_real a_point3_tetsph(a_point3 const *p1, a_point3 const *p2,
                                a_point3 const *p3, a_point3 const *p4,
                                a_point3 *pc);
/*!
 @brief compute the circumcenter and squared circumradius of a tetrahedron defined by four 3D points.
 @details Solves for center (x,y,z) where distances to all four points are equal:
 \f{aligned}{
  (x_1 - x)^2 + (y_1 - y)^2 + (z_1 - z)^2 &= \\ (x_2 - x)^2 + (y_2 - y)^2 + (z_2 - z)^2 &= \\
  (x_3 - x)^2 + (y_3 - y)^2 + (z_3 - z)^2 &= \\ (x_4 - x)^2 + (y_4 - y)^2 + (z_4 - z)^2
 \f}
 This simplifies to:
 \f{cases}{
  2(x_2−x_1)x+2(y_2−y_1)y+2(z_2−z_1)z = (x_2−x_1)(x_2+x_1)+(y_2−y_1)(y_2+y_1)+(z_2−z_1)(z_2+z_1) \\
  2(x_3−x_1)x+2(y_3−y_1)y+2(z_3−z_1)z = (x_3−x_1)(x_3+x_1)+(y_3−y_1)(y_3+y_1)+(z_3−z_1)(z_3+z_1) \\
  2(x_4−x_1)x+2(y_4−y_1)y+2(z_4−z_1)z = (x_4−x_1)(x_4+x_1)+(y_4−y_1)(y_4+y_1)+(z_4−z_1)(z_4+z_1)
 \f}
 Matrix form:
 \f[
  2\begin{bmatrix} x_{21}&y_{21}&z_{21} \\ x_{31}&y_{31}&z_{31} \\ x_{41}&y_{41}&z_{41} \end{bmatrix}
  \begin{bmatrix} x\\y\\z \end{bmatrix} = \begin{bmatrix} b_{21}\\b_{31}\\b_{41} \end{bmatrix}
 \f]
 Where
 \f{aligned}{
  x_{ji} &= x_j - x_i \\ y_{ji} &= y_j - y_i \\ z_{ji} &= z_j - z_i \\
  b_{ji} &= x_{ji}(x_j + x_i) + y_{ji}(y_j + y_i) + z_{ji}(z_j + z_i)
 \f}
 Explicit Solution (Cramer's Rule):
 \f{aligned}{ x&=\frac{D_x}{2D} \\ y&=\frac{D_y}{2D} \\ z&=\frac{D_z}{2D} \f}
 Where
 \f{aligned}{
  D   &= x_{41} \begin{vmatrix} y_{21}&z_{21}\\y_{31}&z_{31} \end{vmatrix} +
         y_{41} \begin{vmatrix} z_{21}&x_{21}\\z_{31}&x_{31} \end{vmatrix} +
         z_{41} \begin{vmatrix} x_{21}&y_{21}\\x_{31}&y_{31} \end{vmatrix} \\
  D_x &= b_{41} \begin{vmatrix} y_{21}&z_{21}\\y_{31}&z_{31} \end{vmatrix} +
         y_{41} \begin{vmatrix} z_{21}&b_{21}\\z_{31}&b_{31} \end{vmatrix} +
         z_{41} \begin{vmatrix} b_{21}&y_{21}\\b_{31}&y_{31} \end{vmatrix} \\
  D_y &= x_{41} \begin{vmatrix} b_{21}&z_{21}\\b_{31}&z_{31} \end{vmatrix} +
         b_{41} \begin{vmatrix} z_{21}&x_{21}\\z_{31}&x_{31} \end{vmatrix} +
         z_{41} \begin{vmatrix} x_{21}&b_{21}\\x_{31}&b_{31} \end{vmatrix} \\
  D_z &= x_{41} \begin{vmatrix} y_{21}&b_{21}\\y_{31}&b_{31} \end{vmatrix} +
         y_{41} \begin{vmatrix} b_{21}&x_{21}\\b_{31}&x_{31} \end{vmatrix} +
         b_{41} \begin{vmatrix} x_{21}&y_{21}\\x_{31}&y_{31} \end{vmatrix}
 \f}
 Radius (r):
 \f[ r = \sqrt{(x_1-x)^2+(y_1-y)^2+(z_1-z)^2} \f]
 @param[in] p1 is the first 3D point on sphere
 @param[in] p2 is the second 3D point on sphere
 @param[in] p3 is the third 3D point on sphere
 @param[in] p4 is the fourth 3D point on sphere
 @param[out] pc stores the circumcenter
 @return the squared circumradius
  @retval 0 if points are coplanar
*/
A_EXTERN a_real a_point3_tetsph2(a_point3 const *p1, a_point3 const *p2,
                                 a_point3 const *p3, a_point3 const *p4,
                                 a_point3 *pc);

/*!
 @brief compare two 3D points primarily by X, then by Y, and finally by Z.
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return relationship between 3D points
  @retval >0 if lhs is greater than rhs
  @retval <0 if lhs is less than rhs
  @retval 0 if lhs is equal to rhs
*/
A_EXTERN int a_point3_cmpxy(a_point3 const *lhs, a_point3 const *rhs);

/*!
 @brief compare two 3D points primarily by Y, then by X, and finally by Z.
 @param[in] lhs is left-hand side 3D point
 @param[in] rhs is right-hand side 3D point
 @return relationship between 3D points
  @retval >0 if lhs is greater than rhs
  @retval <0 if lhs is less than rhs
  @retval 0 if lhs is equal to rhs
*/
A_EXTERN int a_point3_cmpyx(a_point3 const *lhs, a_point3 const *rhs);

#if !defined A_HAVE_INLINE || defined(LIBA_POINT3_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
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
    /*! @copybrief a_point3_mindist @see a_point3_mindist */
    A_INLINE a_real mindist(a_point3 const *i_p, a_size i_n, a_point3 *o_p = A_NULL, a_size *o_i = A_NULL) const
    {
        return a_point3_mindist(this, i_p, i_n, o_p, o_i);
    }
    /*! @copybrief a_point3_maxdist @see a_point3_maxdist */
    A_INLINE a_real maxdist(a_point3 const *i_p, a_size i_n, a_point3 *o_p = A_NULL, a_size *o_i = A_NULL) const
    {
        return a_point3_maxdist(this, i_p, i_n, o_p, o_i);
    }
    /*! @copybrief a_point3_lerp @see a_point3_lerp */
    A_INLINE void lerp(a_point3 const &rhs, a_real val, a_point3 &res) const
    {
        a_point3_lerp(this, &rhs, val, &res);
    }
    /*! @copybrief a_point3_tricir @see a_point3_tricir */
    A_INLINE a_real tricir(a_point3 const &p2, a_point3 const &p3, a_point3 &pc) const
    {
        return a_point3_tricir(this, &p2, &p3, &pc);
    }
    /*! @copybrief a_point3_tricir2 @see a_point3_tricir2 */
    A_INLINE a_real tricir2(a_point3 const &p2, a_point3 const &p3, a_point3 &pc) const
    {
        return a_point3_tricir2(this, &p2, &p3, &pc);
    }
    /*! @copybrief a_point3_tetsph @see a_point3_tetsph */
    A_INLINE a_real tetsph(a_point3 const &p2, a_point3 const &p3, a_point3 const &p4, a_point3 &pc) const
    {
        return a_point3_tetsph(this, &p2, &p3, &p4, &pc);
    }
    /*! @copybrief a_point3_tetsph2 @see a_point3_tetsph2 */
    A_INLINE a_real tetsph2(a_point3 const &p2, a_point3 const &p3, a_point3 const &p4, a_point3 &pc) const
    {
        return a_point3_tetsph2(this, &p2, &p3, &p4, &pc);
    }
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
/*! @cond */
#undef A_INTERN
#define A_INTERN A_INLINE
/*! @endcond */
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
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* LIBA_POINT3_C */

/*! @} a_point3 */

#endif /* a/point3.h */
