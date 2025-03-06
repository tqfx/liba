/*!
 @file trajbell.h
 @brief bell-shaped velocity trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJBELL_H
#define LIBA_TRAJBELL_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_trajbell bell-shaped velocity trajectory
 @{
*/

typedef struct a_trajbell a_trajbell;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for bell-shaped velocity trajectory
 @details If \f$p_0>p_1\f$, then \f{aligned}{p_0=-p_0\\p_1=-p_1\\v_0=-v_0\\v_1=-v_1\f}
 1. If \f$(v_m-v_0)j_m<a_m^2\f$, the maximum acceleration is not reached,
 then \f{aligned}{T_{aj}&=\sqrt{\frac{v_m-v_0}{j_m}}\\T_a&=2T_{aj}\\a_m&=+j_mT_{aj}\f}
 else \f{aligned}{T_{aj}&=\frac{a_m}{j_m}\\T_a&=T_{aj}+\frac{v_m-v_0}{a_m}\\a_m&=+a_m\f}
 2. If \f$(v_m-v_1)j_m<a_m^2\f$, the maximum deceleration is not reached,
 then \f{aligned}{T_{dj}&=\sqrt{\frac{v_m-v_1}{j_m}}\\T_d&=2T_{dj}\\d_m&=-j_mT_{dj}\f}
 else \f{aligned}{T_{dj}&=\frac{a_m}{j_m}\\T_d&=T_{dj}+\frac{v_m-v_1}{a_m}\\d_m&=-a_m\f}
 3. Calculate the constant velocity phase \f[T_v=\frac{p_1-p_0}{v_m}
 -\frac{T_a}{2}\left(1+\frac{v_0}{v_m}\right)-\frac{T_d}{2}\left(1+\frac{v_1}{v_m}\right)\f]
 If \f$T_v>0\f$, then there is a constant velocity phase and the phase calculation ends.
 4. If \f$T_v<=0\f$, then \f$T_v=0\f$, \f{aligned}{T_{aj}&=T_{dj}=T_{j}=\frac{a_m}{j_m}\\
 T_a&=\cfrac{\frac{a_m^2}{j_m}+\sqrt\Delta-2v_0}{2a_m}\\T_d&=\cfrac{\frac{a_m^2}{j_m}+\sqrt\Delta-2v_1}{2a_m}\\
 \Delta&=\frac{a_m^4}{j_m^2}+2(v_0^2+v_1^2)+a_m\left(4(p_1-p_0)-2\frac{a_m}{j_m}(v_0+v_1)\right)\f}<br>
 a. If \f$T_a<0\f$, there is only deceleration phase, then \f$T_a=0\f$,\f$T_{aj}=0\f$,
 \f{aligned}{T_d&=2\cfrac{p_1-p_0}{v_1+v_0}\\
 T_{dj}&=\frac{j_m(p_1-p_0)-\sqrt{j_m(j_m(p_1-p_0)^2+(v_1-v_0)(v_1+v_0)^2)}}{j_m(v_1+v_0 )}\f}
 b. If \f$T_d<0\f$, there is only acceleration phase, then \f$T_d=0\f$,\f$T_{dj}=0\f$,
 \f{aligned}{T_a&=2\cfrac{p_1-p_0}{v_1+v_0}\\
 T_{aj}&=\frac{j_m(p_1-p_0)-\sqrt{j_m(j_m(p_1-p_0)^2+(v_0-v_1)(v_1+v_0)^2)}}{j_m(v_1+v_0 )}\f}
 c. If \f$T_a\ge2T_j\f$, \f$T_d\ge2T_j\f$, then
 \f{aligned}{a_m&=+j_mT_{aj}\\d_m&=-j_mT_{dj}\\v_m&=v_0+(T_a-T_{aj})a_m=v_1-(T_d-T_{dj})d_m\f}
 d. If none of the above conditions are met, let \f$a_m=\alpha a_m, 0<\alpha<1\f$, and then repeat step 4.
 5. Finally, use formulas to compute position, velocity and acceleration.
 @param[in,out] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] jm defines the maximum jerk during system operation
 @param[in] am defines the maximum acceleration during system operation
 @param[in] vm defines the maximum velocity during system operation
 @param[in] p0 defines the initial position
 @param[in] p1 defines the final position
 @param[in] v0 defines the initial velocity
 @param[in] v1 defines the final velocity
 @return total duration
*/
A_EXTERN a_real a_trajbell_gen(a_trajbell *ctx, a_real jm, a_real am, a_real vm,
                               a_real p0, a_real p1, a_real v0, a_real v1);

/*!
 @brief compute position for bell-shaped velocity trajectory
 \f[
  p(t)=\begin{cases}
  p_0+v_0t+j_m\cfrac{t^3}{6},&t\in[0,T_{aj}]\\
  p_0+v_0t+\cfrac{a_m}{6}(3t^3-3tT_{aj}+T_{aj}^2),&t\in[T_{aj},T_a-T_{aj}]\\
  p_0+(v_m+v_0)\cfrac{T_a}{2}-v_m(T_a-t)+j_m\cfrac{(T_a-t)^3}{6},&t\in[T_a-T_{aj},T_a]\\
  p_0+(v_m+v_0)\cfrac{T_a}{2}+v_m(t-T_a),&t\in[T_a,T_a+T_v]\\
  p_1-(v_m+v_1)\cfrac{T_d}{2}+v_m(t-T+T_d)-j_m\cfrac{(t-T+T_d)^3}{6},&t\in[T-T_d,T-T_d+T_{dj}]\\
  p_1-(v_m+v_1)\cfrac{T_d}{2}+v_m(t-T+T_d)\\
  \quad+\cfrac{d_m}{6}\left(3(t-T+T_d)^2-3(t-T+T_d)T_{dj}+T_{dj}^2\right),&t\in[T-T_d+T_{dj},T-T_{dj}]\\
  p_1-v_1(T-t)-j_m\cfrac{(T-t)^3}{6},&t\in[T-T_{dj},T]
  \end{cases}
 \f]
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] x difference between current time and initial time
 @return position output
*/
A_EXTERN a_real a_trajbell_pos(a_trajbell const *ctx, a_real x);

/*!
 @brief compute velocity for bell-shaped velocity trajectory
 \f[
  \dot{p}(t)=\begin{cases}
  v_0+j_m\frac{t^2}{2},&t\in[0,T_{aj}]\\
  v_0+a_m(t-\cfrac{T_{aj}}{2}),&t\in[T_{aj},T_a-T_{aj}]\\
  v_m-j_m\cfrac{(T_a-t)^2}{2},&t\in[T_a-T_{aj},T_a]\\
  v_m,&t\in[T_a,T_a+T_v]\\
  v_m-j_m\cfrac{(t-T+T_d)^2}{2},&t\in[T-T_d,T-T_d+T_{dj}]\\
  v_m+d_m(t-T+T_d-\cfrac{T_{dj}}{2}),&t\in[T-T_d+T_{dj},T-T_{dj}]\\
  v_1+j_m\cfrac{(T-t)^2}{2},&t\in[T-T_{dj},T]
  \end{cases}
 \f]
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] x difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_real a_trajbell_vel(a_trajbell const *ctx, a_real x);

/*!
 @brief compute acceleration for bell-shaped velocity trajectory
 \f[
  \ddot{p}(t)=\begin{cases}
  j_mt,&t\in[0,T_{aj}]\\
  j_mT_{aj}=a_m,&t\in[T_{aj},T_a-T_{aj}]\\
  j_m(T_a-t),&t\in[T_a-T_{aj},T_a]\\
  0,&t\in[T_a,T_a+T_v]\\
  -j_m(t-T+T_d),&t\in[T-T_d,T-T_d+T_{dj}]\\
  -j_mT_{dj}=d_m,&t\in[T-T_d+T_{dj},T-T_{dj}]\\
  -j_m(T-t),&t\in[T-T_{dj},T]
  \end{cases}
 \f]
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] x difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_real a_trajbell_acc(a_trajbell const *ctx, a_real x);

/*!
 @brief compute jerk for bell-shaped velocity trajectory
 \f[
  p^{(3)}(t)=\begin{cases}
  j_m,&t\in[0,T_{aj}]\\
  0,&t\in[T_{aj},T_a-T_{aj}]\\
  -j_m,&t\in[T_a-T_{aj},T_a]\\
  0,&t\in[T_a,T_a+T_v]\\
  -j_m,&t\in[T-T_d,T-T_d+T_{dj}]\\
  0,&t\in[T-T_d+T_{dj},T-T_{dj}]\\
  j_m,&t\in[T-T_{dj},T]
  \end{cases}
 \f]
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] x difference between current time and initial time
 @return jerk output
*/
A_EXTERN a_real a_trajbell_jer(a_trajbell const *ctx, a_real x);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_trajbell trajbell;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for bell-shaped velocity trajectory
*/
struct a_trajbell
{
    a_real t; /*!< total duration */
    a_real tv; /*!< constant velocity phase */
    a_real ta; /*!< acceleration phase */
    a_real td; /*!< deceleration phase */
    a_real taj; /*!< time-interval in which the jerk is constant (j max or j min ) during the acceleration phase */
    a_real tdj; /*!< time-interval in which the jerk is constant (j max or j min ) during the deceleration phase */
    a_real p0; /*!< initial position */
    a_real p1; /*!< final position */
    a_real v0; /*!< initial velocity */
    a_real v1; /*!< final velocity */
    a_real vm; /*!< maximum velocity */
    a_real jm; /*!< maximum jerk */
    a_real am; /*!< maximum acceleration */
    a_real dm; /*!< maximum deceleration */
#if defined(__cplusplus)
    A_INLINE a_real gen(a_real jm_, a_real am_, a_real vm_, a_real p0_, a_real p1_,
                        a_real v0_ = 0, a_real v1_ = 0)
    {
        return a_trajbell_gen(this, jm_, am_, vm_, p0_, p1_, v0_, v1_);
    }
    A_INLINE a_real pos(a_real x) const
    {
        return a_trajbell_pos(this, x);
    }
    A_INLINE a_real vel(a_real x) const
    {
        return a_trajbell_vel(this, x);
    }
    A_INLINE a_real acc(a_real x) const
    {
        return a_trajbell_acc(this, x);
    }
    A_INLINE a_real jer(a_real x) const
    {
        return a_trajbell_jer(this, x);
    }
#endif /* __cplusplus */
};

/*! @} a_trajbell */

#endif /* a/trajbell.h */
