/*!
 @file traptraj.h
 @brief trapezoidal velocity profile trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAPTRAJ_H
#define LIBA_TRAPTRAJ_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_TRAPTRAJ trapezoidal velocity profile trajectory
 @{
*/

typedef struct a_traptraj a_traptraj;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for trapezoidal velocity profile trajectory
 @details Assuming that there is no constant velocity phase, but only acceleration and deceleration phases,
  the maximum velocity in the motion is \f$v\f$, then we have \f[q=q_a+q_c=\frac{v^2-v_s^2}{2a}+\frac{v_e^2-v^2}{2d}\f]
  Solving for the maximum velocity is \f[|v|=\sqrt{\frac{av_e^2-dv_s^2-2qad}{a-d}}\f]
  1. If \f$|v|>|v_m|\f$, then there is a constant velocity phase.
  \f[\begin{cases}t_a=\cfrac{v_m-v_s}{a}\\t_c=\cfrac{q-q_a-q_d}{v_c}\\t_d=\cfrac{v_e-v_m}{d}\end{cases}\f]
  2. Otherwise there is no constant velocity phase. \n
  a. If \f$|v_s|<|v|\le|v_e|\f$, there is only an acceleration phase.
  \f[|v_e|=\sqrt{v_s^2+2qa}\f]
  \f[\begin{cases}t_a=\cfrac{v_e-v_s}{a}\\t_c=0\\t_d=0\end{cases}\f]
  b. If \f$|v_s|\ge|v|>|v_e|\f$, there is only a deceleration phase.
  \f[|v_e|=\sqrt{v_s^2+2qd}\f]
  \f[\begin{cases}t_a=0\\t_c=0\\t_d=\cfrac{v_e-v_s}{d}\end{cases}\f]
  c. If \f$|v|>|v_s|\f$, \f$|v|>|v_e|\f$, then there are acceleration and deceleration phases.
  \f[\begin{cases}t_a=\cfrac{v-v_s}{a}\\t_c=0\\t_d=\cfrac{v_e-v}{d}\end{cases}\f]
  3. Finally, the displacement and velocity are calculated using the formula.
 @param[in,out] ctx points to an instance of trapezoidal velocity profile trajectory
 @param[in] qm defines the distance from the start point to the end point
 @param[in] vm defines the maximum velocity at which the system can work
 @param[in] ac defines the acceleration before constant velocity
 @param[in] de defines the acceleration after constant velocity
 @param[in] vs defines the starting velocity
 @param[in] ve defines the ending velocity
 @return total time
*/
A_EXTERN a_float a_traptraj_gen(a_traptraj *ctx, a_float qm, a_float vm, a_float ac, a_float de, a_float vs, a_float ve);

/*!
 @brief calculate for trapezoidal velocity profile trajectory position
 \f[
  q(t)=\begin{cases}
  v_s+\frac{1}{2}at^2,&0\le t<t_a\\q_a+v_c(t-t_a),&t_a\le t<t_a+t_c\\
  q_a+q_c+v_c(t-t_a-t_c)+\frac{1}{2}d(t-t_a-t_c)^2,&t_a+t_c\le t<t_a+t_c+t_d
  \end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity profile trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_traptraj_pos(a_traptraj const *ctx, a_float dt);

/*!
 @brief calculate for trapezoidal velocity profile trajectory velocity
 \f[
  v(t)=\begin{cases}
  v_s+at,&0\le t<t_a\\v_c,&t_a\le t<t_a+t_c\\
  v_c+d(t-t_a-t_c),&t_a+t_c\le t<t_a+t_c+t_d
  \end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity profile trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_traptraj_vel(a_traptraj const *ctx, a_float dt);

/*!
 @brief calculate for trapezoidal velocity profile trajectory acceleration
 \f[
  a(t)=\begin{cases}
  a,&0\le t<t_a\\0,&t_a\le t<t_a+t_c\\d,&t_a+t_c\le t<t_a+t_c+t_d
  \end{cases}
 \f]
 @param[in] ctx points to an instance of trapezoidal velocity profile trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_traptraj_acc(a_traptraj const *ctx, a_float dt);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_traptraj traptraj;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for trapezoidal velocity profile trajectory
*/
struct a_traptraj
{
    a_float ac; //!< acceleration before constant velocity
    a_float de; //!< acceleration after constant velocity
    a_float ta; //!< time period of increased velocity
    a_float qa; //!< displacement as velocity increases
    a_float tc; //!< time period of constant velocity
    a_float qc; //!< displacement at constant velocity
    a_float td; //!< time period of decreased velocity
    a_float qd; //!< displacement as velocity decreases
    a_float vs; //!< initial velocity
    a_float vc; //!< constant velocity
    a_float ve; //!< final velocity
#if defined(__cplusplus)
    A_INLINE a_float gen(a_float qm, a_float vm,
                         a_float _ac, a_float _de,
                         a_float _vs, a_float _ve)
    {
        return a_traptraj_gen(this, qm, vm, _ac, _de, _vs, _ve);
    }
    A_INLINE a_float pos(a_float dt)
    {
        return a_traptraj_pos(this, dt);
    }
    A_INLINE a_float vel(a_float dt)
    {
        return a_traptraj_vel(this, dt);
    }
    A_INLINE a_float acc(a_float dt)
    {
        return a_traptraj_acc(this, dt);
    }
#endif /* __cplusplus */
};

/*! @} A_TRAPTRAJ */

#endif /* a/traptraj.h */
