/*!
 @file polytraj3.h
 @brief cubic polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_POLYTRAJ3_H
#define LIBA_POLYTRAJ3_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_POLYTRAJ3 cubic polynomial trajectory
 @{
*/

#if !defined A_POLYTRAJ3
#define A_POLYTRAJ3 3
#endif /* A_POLYTRAJ3 */
typedef struct a_polytraj3 a_polytraj3;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for cubic polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{\left(-2\,v_{0}-v_{1}\right)\,t+3\,q}{t^2}\\
  k_{3}=\cfrac{\left(v_{0}+v_{1}\right)\,t-2\,q}{t^3}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of cubic polynomial trajectory
 @param[in] t0 time for source
 @param[in] t1 time for target
 @param[in] q0 position for source
 @param[in] q1 position for target
 @param[in] v0 velocity for source
 @param[in] v1 velocity for target
*/
A_EXTERN void a_polytraj3_gen(a_polytraj3 *ctx,
                              a_float t0, a_float t1,
                              a_float q0, a_float q1,
                              a_float v0, a_float v1);
A_EXTERN void a_polytraj3_gen0(a_polytraj3 *ctx,
                               a_float t0, a_float t1,
                               a_float q0, a_float q1,
                               a_float v0, a_float v1);
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
A_EXTERN void a_polytraj3_gen1(a_polytraj3 *ctx);
#endif /* A_POLYTRAJ3 */
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
A_EXTERN void a_polytraj3_gen2(a_polytraj3 *ctx);
#endif /* A_POLYTRAJ3 */

/*!
 @brief calculate for cubic polynomial trajectory position
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_polytraj3_pos(a_polytraj3 const *ctx, a_float dt);

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
/*!
 @brief calculate for cubic polynomial trajectory velocity
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_polytraj3_vel(a_polytraj3 const *ctx, a_float dt);
#endif /* A_POLYTRAJ3 */

#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
/*!
 @brief calculate for cubic polynomial trajectory acceleration
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in] ctx points to an instance of cubic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_polytraj3_acc(a_polytraj3 const *ctx, a_float dt);
#endif /* A_POLYTRAJ3 */

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_polytraj3 polytraj3;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for cubic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
*/
struct a_polytraj3
{
    a_float q[4]; //!< coefficients of position
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
    a_float v[3]; //!< coefficients of velocity
#endif /* A_POLYTRAJ3 */
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
    a_float a[2]; //!< coefficients of acceleration
#endif /* A_POLYTRAJ3 */
#if defined(__cplusplus)
    A_INLINE void gen(a_float t0, a_float t1,
                      a_float q0, a_float q1,
                      a_float v0 = 0, a_float v1 = 0)
    {
        a_polytraj3_gen(this, t0, t1, q0, q1, v0, v1);
    }
    A_INLINE void gen0(a_float t0, a_float t1,
                       a_float q0, a_float q1,
                       a_float v0 = 0, a_float v1 = 0)
    {
        a_polytraj3_gen0(this, t0, t1, q0, q1, v0, v1);
    }
    A_INLINE a_float pos(a_float dt)
    {
        return a_polytraj3_pos(this, dt);
    }
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 1)
    A_INLINE void gen1() { a_polytraj3_gen1(this); }
    A_INLINE a_float vel(a_float dt)
    {
        return a_polytraj3_vel(this, dt);
    }
#endif /* A_POLYTRAJ3 */
#if defined(A_POLYTRAJ3) && (A_POLYTRAJ3 + 0 > 2)
    A_INLINE void gen2() { a_polytraj3_gen2(this); }
    A_INLINE a_float acc(a_float dt)
    {
        return a_polytraj3_acc(this, dt);
    }
#endif /* A_POLYTRAJ3 */
#endif /* __cplusplus */
};

/*! @} A_POLYTRAJ3 */

#endif /* a/polytraj3.h */
