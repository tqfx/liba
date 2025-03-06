/*!
 @file trajpoly5.h
 @brief quintic polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJPOLY5_H
#define LIBA_TRAJPOLY5_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_trajpoly5 quintic polynomial trajectory
 @{
*/

typedef struct a_trajpoly5 a_trajpoly5;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for quintic polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  p=p_{1}-p_{0}\\
  c_{0}=p_{0}\\
  c_{1}=v_{0}\\
  c_{2}=\cfrac{a_{0}}{2}\\
  c_{3}=\cfrac{\left(a_{1}-3\,a_{0}\right)\,t^2+\left(-12\,v_{0}-8\,v_{1}\right)\,t+20\,p}{2\,t^3}\\
  c_{4}=\cfrac{\left(3\,a_{0}-2\,a_{1}\right)\,t^2+\left(16\,v_{0}+14\,v_{1}\right)\,t-30\,p}{2\,t^4}\\
  c_{5}=\cfrac{\left(a_{1}-a_{0}\right)\,t^2+\left(-6\,v_{0}-6\,v_{1}\right)\,t+12\,p}{2\,t^5}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of quintic polynomial trajectory
 @param[in] ts difference between final time and initial time
 @param[in] p0 initial position
 @param[in] p1 final position
 @param[in] v0 initial velocity
 @param[in] v1 final velocity
 @param[in] a0 initial acceleration
 @param[in] a1 final acceleration
*/
A_EXTERN void a_trajpoly5_gen(a_trajpoly5 *ctx, a_real ts,
                              a_real p0, a_real p1,
                              a_real v0, a_real v1,
                              a_real a0, a_real a1);

/*!
 @brief compute coefficients of position for quintic polynomial trajectory
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[out] c coefficients of position
*/
A_EXTERN void a_trajpoly5_c0(a_trajpoly5 const *ctx, a_real c[6]);

/*!
 @brief compute coefficients of velocity for quintic polynomial trajectory
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[out] c coefficients of velocity
*/
A_EXTERN void a_trajpoly5_c1(a_trajpoly5 const *ctx, a_real c[5]);

/*!
 @brief compute coefficients of acceleration for quintic polynomial trajectory
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[out] c coefficients of acceleration
*/
A_EXTERN void a_trajpoly5_c2(a_trajpoly5 const *ctx, a_real c[4]);

/*!
 @brief compute position for quintic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3}+c_{4}\left(t-t_{0}\right)^{4}+c_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return position output
*/
A_EXTERN a_real a_trajpoly5_pos(a_trajpoly5 const *ctx, a_real x);

/*!
 @brief compute velocity for quintic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2}+4 c_{4}\left(t-t_{0}\right)^{3}+5 c_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_real a_trajpoly5_vel(a_trajpoly5 const *ctx, a_real x);

/*!
 @brief compute acceleration for quintic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)+12 c_{4}\left(t-t_{0}\right)^{2}+20 c_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] x difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_real a_trajpoly5_acc(a_trajpoly5 const *ctx, a_real x);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_trajpoly5 trajpoly5;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for quintic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3}+c_{4}\left(t-t_{0}\right)^{4}+c_{5}\left(t-t_{0}\right)^{5}\\
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2}+4 c_{4}\left(t-t_{0}\right)^{3}+5 c_{5}\left(t-t_{0}\right)^{4}\\
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)+12 c_{4}\left(t-t_{0}\right)^{2}+20 c_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
*/
struct a_trajpoly5
{
    a_real c[6]; /*!< coefficients of position */
#if defined(__cplusplus)
    A_INLINE void gen(a_real ts, a_real p0, a_real p1,
                      a_real v0 = 0, a_real v1 = 0,
                      a_real a0 = 0, a_real a1 = 0)
    {
        a_trajpoly5_gen(this, ts, p0, p1, v0, v1, a0, a1);
    }
    A_INLINE a_real pos(a_real x) const
    {
        return a_trajpoly5_pos(this, x);
    }
    A_INLINE a_real vel(a_real x) const
    {
        return a_trajpoly5_vel(this, x);
    }
    A_INLINE a_real acc(a_real x) const
    {
        return a_trajpoly5_acc(this, x);
    }
    A_INLINE void c0(a_real x[6]) const
    {
        a_trajpoly5_c0(this, x);
    }
    A_INLINE void c1(a_real x[5]) const
    {
        a_trajpoly5_c1(this, x);
    }
    A_INLINE void c2(a_real x[4]) const
    {
        a_trajpoly5_c2(this, x);
    }
#endif /* __cplusplus */
};

/*! @} a_trajpoly5 */

#endif /* a/trajpoly5.h */
