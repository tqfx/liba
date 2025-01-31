/*!
 @file trajpoly3.h
 @brief cubic polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJPOLY3_H
#define LIBA_TRAJPOLY3_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_trajpoly3 cubic polynomial trajectory
 @{
*/

typedef struct a_trajpoly3 a_trajpoly3;

#if !defined A_TRAJPOLY3
#define A_TRAJPOLY3 3
#endif /* A_TRAJPOLY3 */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for cubic polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  p=p_{1}-p_{0}\\
  c_{0}=p_{0}\\
  c_{1}=v_{0}\\
  c_{2}=\cfrac{\left(-2\,v_{0}-v_{1}\right)\,t+3\,p}{t^2}\\
  c_{3}=\cfrac{\left(v_{0}+v_{1}\right)\,t-2\,p}{t^3}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of cubic polynomial trajectory
 @param[in] ts difference between final time and initial time
 @param[in] p0 initial position
 @param[in] p1 final position
 @param[in] v0 initial velocity
 @param[in] v1 final velocity
*/
A_EXTERN void a_trajpoly3_gen(a_trajpoly3 *ctx, a_real ts,
                              a_real p0, a_real p1,
                              a_real v0, a_real v1);
A_EXTERN void a_trajpoly3_gen0(a_trajpoly3 *ctx, a_real ts,
                               a_real p0, a_real p1,
                               a_real v0, a_real v1);
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
A_EXTERN void a_trajpoly3_gen1(a_trajpoly3 *ctx);
#endif /* A_TRAJPOLY3 */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
A_EXTERN void a_trajpoly3_gen2(a_trajpoly3 *ctx);
#endif /* A_TRAJPOLY3 */

/*!
 @brief calculate position for cubic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return position output
*/
A_EXTERN a_real a_trajpoly3_pos(a_trajpoly3 const *ctx, a_real x);

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
/*!
 @brief calculate velocity for cubic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_real a_trajpoly3_vel(a_trajpoly3 const *ctx, a_real x);
#endif /* A_TRAJPOLY3 */

#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
/*!
 @brief calculate acceleration for cubic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_real a_trajpoly3_acc(a_trajpoly3 const *ctx, a_real x);
#endif /* A_TRAJPOLY3 */

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_trajpoly3 trajpoly3;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for cubic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3} \\
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2} \\
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
*/
struct a_trajpoly3
{
    a_real p[4]; /*!< coefficients of position */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
    a_real v[3]; /*!< coefficients of velocity */
#endif /* A_TRAJPOLY3 */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
    a_real a[2]; /*!< coefficients of acceleration */
#endif /* A_TRAJPOLY3 */
#if defined(__cplusplus)
    A_INLINE void gen(a_real ts, a_real p0, a_real p1,
                      a_real v0 = 0, a_real v1 = 0)
    {
        a_trajpoly3_gen(this, ts, p0, p1, v0, v1);
    }
    A_INLINE void gen0(a_real ts, a_real p0, a_real p1,
                       a_real v0 = 0, a_real v1 = 0)
    {
        a_trajpoly3_gen0(this, ts, p0, p1, v0, v1);
    }
    A_INLINE a_real pos(a_real x) const
    {
        return a_trajpoly3_pos(this, x);
    }
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 1)
    A_INLINE void gen1() { a_trajpoly3_gen1(this); }
    A_INLINE a_real vel(a_real x) const
    {
        return a_trajpoly3_vel(this, x);
    }
#endif /* A_TRAJPOLY3 */
#if defined(A_TRAJPOLY3) && (A_TRAJPOLY3 + 0 > 2)
    A_INLINE void gen2() { a_trajpoly3_gen2(this); }
    A_INLINE a_real acc(a_real x) const
    {
        return a_trajpoly3_acc(this, x);
    }
#endif /* A_TRAJPOLY3 */
#endif /* __cplusplus */
};

/*! @} a_trajpoly3 */

#endif /* a/trajpoly3.h */
