/*!
 @file trajtrap.h
 @brief trapezoidal velocity trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJTRAP_H
#define LIBA_TRAJTRAP_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_TRAJTRAP trapezoidal velocity trajectory
 @{
*/

typedef struct a_trajtrap a_trajtrap;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for trapezoidal velocity trajectory
 @details Assuming that there is no constant velocity phase, but only acceleration and deceleration phases,
  the maximum velocity in the motion is \f$v\f$, then we have \f[\frac{v^2-v_0^2}{2a}+\frac{v_1^2-v^2}{2d}=q_1-q_0\f]
  Solving for the maximum velocity is \f[|v|=\sqrt{\frac{av_1^2-dv_0^2-2ad(q_1-q_0)}{a-d}}\f]
  1. If \f$|v|>|v_m|\f$, then there is a constant velocity phase.
  \f[q_a=q_0+v_0T_a+\frac{1}{2}aT_a^2\f] \f[a_d=q_1-v_cT_d-\frac{1}{2}dT_d^2\f]
  \f[\begin{cases}T_a=\cfrac{v_m-v_0}{a}\\T_c=\cfrac{q_d-q_a}{v_c}\\T_d=\cfrac{v_1-v_m}{d}\\\end{cases}\f]
  2. Otherwise there is no constant velocity phase. \n
  a. If \f$|v_0|<|v|\le|v_1|\f$, there is only an acceleration phase.
  \f[|v_1|=\sqrt{v_0^2+2a(q_1-q_0)}\f]
  \f[\begin{cases}T_a=\cfrac{v_1-v_0}{a}\\T_c=0\\T_d=0\\\end{cases}\f]
  b. If \f$|v_0|\ge|v|>|v_1|\f$, there is only a deceleration phase.
  \f[|v_1|=\sqrt{v_0^2+2d(q_1-q_0)}\f]
  \f[\begin{cases}T_a=0\\T_c=0\\T_d=\cfrac{v_1-v_0}{d}\end{cases}\\\f]
  c. If \f$|v|>|v_0|\f$, \f$|v|>|v_1|\f$, then there are acceleration and deceleration phases.
  \f[\begin{cases}T_a=\cfrac{v-v_0}{a}\\T_c=0\\T_d=\cfrac{v_1-v}{d}\\\end{cases}\f]
  3. Finally, the position and velocity are calculated using the formula.
 @param[in,out] ctx points to an instance of trapezoidal velocity trajectory
 @param[in] vm defines the maximum velocity during system operation
 @param[in] ac defines the acceleration before constant velocity
 @param[in] de defines the acceleration after constant velocity
 @param[in] q0 defines the initial position
 @param[in] q1 defines the final position
 @param[in] v0 defines the initial velocity
 @param[in] v1 defines the final velocity
 @return total duration
*/
A_EXTERN a_float a_trajtrap_gen(a_trajtrap *ctx, a_float vm, a_float ac, a_float de,
                                a_float q0, a_float q1, a_float v0, a_float v1);

/*!
 @brief calculate position for trapezoidal velocity trajectory
 \f[
  q(t)=\begin{cases}v_0+\frac{1}{2}at^2,&0\le t<t_a\\q_a+v_c(t-t_a),&t_a\le t<t_d\\
  q_d+v_c(t-t_d)+\frac{1}{2}d(t-t_d)^2,&t_d\le t<t_1\end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_trajtrap_pos(a_trajtrap const *ctx, a_float dt);

/*!
 @brief calculate velocity for trapezoidal velocity trajectory
 \f[
  v(t)=\begin{cases}v_0+at,&0\le t<t_a\\v_c,&t_a\le t<t_d\\v_c+d(t-t_d),&t_d\le t<t_1\end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_trajtrap_vel(a_trajtrap const *ctx, a_float dt);

/*!
 @brief calculate acceleration for trapezoidal velocity trajectory
 \f[
  a(t)=\begin{cases}a,&0\le t<t_a\\0,&t_a\le t<t_d\\d,&t_d\le t<t_1\end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_trajtrap_acc(a_trajtrap const *ctx, a_float dt);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_trajtrap trajtrap;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for trapezoidal velocity trajectory
*/
struct a_trajtrap
{
    a_float t; //!< total duration
    a_float q0; //!< initial position
    a_float q1; //!< final position
    a_float v0; //!< initial velocity
    a_float v1; //!< final velocity
    a_float vc; //!< constant velocity
    a_float ta; //!< time before constant velocity
    a_float td; //!< time after constant velocity
    a_float qa; //!< position before constant velocity
    a_float qd; //!< position after constant velocity
    a_float ac; //!< acceleration before constant velocity
    a_float de; //!< acceleration after constant velocity
#if defined(__cplusplus)
    A_INLINE a_float gen(a_float vm, a_float _ac, a_float _de, a_float _q0, a_float _q1,
                         a_float _v0 = 0, a_float _v1 = 0)
    {
        return a_trajtrap_gen(this, vm, _ac, _de, _q0, _q1, _v0, _v1);
    }
    A_INLINE a_float pos(a_float dt)
    {
        return a_trajtrap_pos(this, dt);
    }
    A_INLINE a_float vel(a_float dt)
    {
        return a_trajtrap_vel(this, dt);
    }
    A_INLINE a_float acc(a_float dt)
    {
        return a_trajtrap_acc(this, dt);
    }
#endif /* __cplusplus */
};

/*! @} A_TRAJTRAP */

#endif /* a/trajtrap.h */
