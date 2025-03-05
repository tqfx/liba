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
 @param[in] ts difference between current time and initial time
 @param[in] p0 initial position
 @param[in] p1 final position
 @param[in] v0 initial velocity
 @param[in] v1 final velocity
*/
A_EXTERN void a_trajpoly3_gen(a_trajpoly3 *ctx, a_real ts,
                              a_real p0, a_real p1,
                              a_real v0, a_real v1);

/*!
 @brief calculate coefficients of position for cubic polynomial trajectory
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[out] c coefficients of position
*/
A_EXTERN void a_trajpoly3_c0(a_trajpoly3 const *ctx, a_real c[4]);

/*!
 @brief calculate coefficients of velocity for cubic polynomial trajectory
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[out] c coefficients of velocity
*/
A_EXTERN void a_trajpoly3_c1(a_trajpoly3 const *ctx, a_real c[3]);

/*!
 @brief calculate coefficients of acceleration for cubic polynomial trajectory
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[out] c coefficients of acceleration
*/
A_EXTERN void a_trajpoly3_c2(a_trajpoly3 const *ctx, a_real c[2]);

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
    a_real c[4]; /*!< coefficients of position */
#if defined(__cplusplus)
    A_INLINE void gen(a_real ts, a_real p0, a_real p1,
                      a_real v0 = 0, a_real v1 = 0)
    {
        a_trajpoly3_gen(this, ts, p0, p1, v0, v1);
    }
    A_INLINE a_real pos(a_real x) const
    {
        return a_trajpoly3_pos(this, x);
    }
    A_INLINE a_real vel(a_real x) const
    {
        return a_trajpoly3_vel(this, x);
    }
    A_INLINE a_real acc(a_real x) const
    {
        return a_trajpoly3_acc(this, x);
    }
    A_INLINE void c0(a_real x[4]) const
    {
        a_trajpoly3_c0(this, x);
    }
    A_INLINE void c1(a_real x[3]) const
    {
        a_trajpoly3_c1(this, x);
    }
    A_INLINE void c2(a_real x[2]) const
    {
        a_trajpoly3_c2(this, x);
    }
#endif /* __cplusplus */
};

/*! @} a_trajpoly3 */

#endif /* a/trajpoly3.h */
