/*!
 @file polytraj5.h
 @brief quintic polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_POLYTRAJ5_H
#define LIBA_POLYTRAJ5_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_POLYTRAJ5 quintic polynomial trajectory
 @{
*/

#if !defined A_POLYTRAJ5
#define A_POLYTRAJ5 3
#endif /* A_POLYTRAJ5 */
typedef struct a_polytraj5 a_polytraj5;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for quintic polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{a_{0}}{2}\\
  k_{3}=\cfrac{\left(a_{1}-3\,a_{0}\right)\,t^2+\left(-12\,v_{0}-8\,v_{1}\right)\,t+20\,q}{2\,t^3}\\
  k_{4}=\cfrac{\left(3\,a_{0}-2\,a_{1}\right)\,t^2+\left(16\,v_{0}+14\,v_{1}\right)\,t-30\,q}{2\,t^4}\\
  k_{5}=\cfrac{\left(a_{1}-a_{0}\right)\,t^2+\left(-6\,v_{0}-6\,v_{1}\right)\,t+12\,q}{2\,t^5}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of quintic polynomial trajectory
 @param[in] t0 time for source
 @param[in] t1 time for target
 @param[in] q0 position for source
 @param[in] q1 position for target
 @param[in] v0 velocity for source
 @param[in] v1 velocity for target
 @param[in] a0 acceleration for source
 @param[in] a1 acceleration for target
*/
A_EXTERN void a_polytraj5_gen(a_polytraj5 *ctx,
                              a_float t0, a_float t1,
                              a_float q0, a_float q1,
                              a_float v0, a_float v1,
                              a_float a0, a_float a1);
A_EXTERN void a_polytraj5_gen0(a_polytraj5 *ctx,
                               a_float t0, a_float t1,
                               a_float q0, a_float q1,
                               a_float v0, a_float v1,
                               a_float a0, a_float a1);
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
A_EXTERN void a_polytraj5_gen1(a_polytraj5 *ctx);
#endif /* A_POLYTRAJ5 */
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
A_EXTERN void a_polytraj5_gen2(a_polytraj5 *ctx);
#endif /* A_POLYTRAJ5 */

/*!
 @brief calculate for quintic polynomial trajectory position
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_polytraj5_pos(a_polytraj5 const *ctx, a_float dt);

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
/*!
 @brief calculate for quintic polynomial trajectory velocity
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_polytraj5_vel(a_polytraj5 const *ctx, a_float dt);
#endif /* A_POLYTRAJ5 */

#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
/*!
 @brief calculate for quintic polynomial trajectory acceleration
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in] ctx points to an instance of quintic polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_polytraj5_acc(a_polytraj5 const *ctx, a_float dt);
#endif /* A_POLYTRAJ5 */

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_polytraj5 polytraj5;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for quintic polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
*/
struct a_polytraj5
{
    a_float q[6]; //!< coefficients of position
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
    a_float v[5]; //!< coefficients of velocity
#endif /* A_POLYTRAJ5 */
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
    a_float a[4]; //!< coefficients of acceleration
#endif /* A_POLYTRAJ5 */
#if defined(__cplusplus)
    A_INLINE void gen(a_float t0, a_float t1,
                      a_float q0, a_float q1,
                      a_float v0 = 0, a_float v1 = 0,
                      a_float a0 = 0, a_float a1 = 0)
    {
        a_polytraj5_gen(this, t0, t1, q0, q1, v0, v1, a0, a1);
    }
    A_INLINE void gen0(a_float t0, a_float t1,
                       a_float q0, a_float q1,
                       a_float v0 = 0, a_float v1 = 0,
                       a_float a0 = 0, a_float a1 = 0)
    {
        a_polytraj5_gen0(this, t0, t1, q0, q1, v0, v1, a0, a1);
    }
    A_INLINE a_float pos(a_float dt)
    {
        return a_polytraj5_pos(this, dt);
    }
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 1)
    A_INLINE void gen1() { a_polytraj5_gen1(this); }
    A_INLINE a_float vel(a_float dt)
    {
        return a_polytraj5_vel(this, dt);
    }
#endif /* A_POLYTRAJ5 */
#if defined(A_POLYTRAJ5) && (A_POLYTRAJ5 + 0 > 2)
    A_INLINE void gen2() { a_polytraj5_gen2(this); }
    A_INLINE a_float acc(a_float dt)
    {
        return a_polytraj5_acc(this, dt);
    }
#endif /* A_POLYTRAJ5 */
#endif /* __cplusplus */
};

/*! @} A_POLYTRAJ5 */

#endif /* a/polytraj5.h */
