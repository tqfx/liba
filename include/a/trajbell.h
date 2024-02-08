/*!
 @file trajbell.h
 @brief bell-shaped velocity trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJBELL_H
#define LIBA_TRAJBELL_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_TRAJBELL bell-shaped velocity trajectory
 @{
*/

typedef struct a_trajbell a_trajbell;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for bell-shaped velocity trajectory
 @param[in,out] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] jm defines the maximum jerk during system operation
 @param[in] am defines the maximum acceleration during system operation
 @param[in] vm defines the maximum velocity during system operation
 @param[in] q0 defines the initial position
 @param[in] q1 defines the final position
 @param[in] v0 defines the initial velocity
 @param[in] v1 defines the final velocity
 @return total duration
*/
A_EXTERN a_float a_trajbell_gen(a_trajbell *ctx, a_float jm, a_float am, a_float vm,
                                a_float q0, a_float q1, a_float v0, a_float v1);

/*!
 @brief calculate position for bell-shaped velocity trajectory
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_trajbell_pos(a_trajbell const *ctx, a_float dt);

/*!
 @brief calculate velocity for bell-shaped velocity trajectory
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_trajbell_vel(a_trajbell const *ctx, a_float dt);

/*!
 @brief calculate acceleration for bell-shaped velocity trajectory
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_trajbell_acc(a_trajbell const *ctx, a_float dt);

/*!
 @brief calculate jerk for bell-shaped velocity trajectory
 @param[in] ctx points to an instance of bell-shaped velocity trajectory
 @param[in] dt difference between current time and initial time
 @return jerk output
*/
A_EXTERN a_float a_trajbell_jer(a_trajbell const *ctx, a_float dt);

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
    a_float t; //!< total duration
    a_float tv; //!< constant velocity phase
    a_float ta; //!< acceleration phase
    a_float td; //!< deceleration phase
    a_float taj; //!< time-interval in which the jerk is constant (j max or j min ) during the acceleration phase
    a_float tdj; //!< time-interval in which the jerk is constant (j max or j min ) during the deceleration phase
    a_float q0; //!< initial position
    a_float q1; //!< final position
    a_float v0; //!< initial velocity
    a_float v1; //!< final velocity
    a_float vm; //!< maximum velocity
    a_float jm; //!< maximum jerk
    a_float am; //!< maximum acceleration
    a_float dm; //!< maximum deceleration
#if defined(__cplusplus)
    A_INLINE a_float gen(a_float _jm, a_float _am, a_float _vm, a_float _q0, a_float _q1,
                         a_float _v0 = 0, a_float _v1 = 0)
    {
        return a_trajbell_gen(this, _jm, _am, _vm, _q0, _q1, _v0, _v1);
    }
    A_INLINE a_float pos(a_float dt)
    {
        return a_trajbell_pos(this, dt);
    }
    A_INLINE a_float vel(a_float dt)
    {
        return a_trajbell_vel(this, dt);
    }
    A_INLINE a_float acc(a_float dt)
    {
        return a_trajbell_acc(this, dt);
    }
    A_INLINE a_float jer(a_float dt)
    {
        return a_trajbell_jer(this, dt);
    }
#endif /* __cplusplus */
};

/*! @} A_TRAJBELL */

#endif /* a/trajbell.h */
