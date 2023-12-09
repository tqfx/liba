/*!
 @file polytraj7.h
 @brief hepta polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_POLYTRAJ7_H
#define LIBA_POLYTRAJ7_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_POLYTRAJ7 hepta polynomial trajectory
 @{
*/

/*!
 @brief instance structure for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
*/
typedef struct a_polytraj7_s
{
#if !defined A_POLYTRAJ7
#define A_POLYTRAJ7 4
#endif /* A_POLYTRAJ7 */
    a_float_t q[8]; //!< coefficients of position
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 1)
    a_float_t v[7]; //!< coefficients of velocity
#endif /* A_POLYTRAJ7 */
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 2)
    a_float_t a[6]; //!< coefficients of acceleration
#endif /* A_POLYTRAJ7 */
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 3)
    a_float_t j[5]; //!< coefficients of jerk
#endif /* A_POLYTRAJ7 */
} a_polytraj7_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for hepta polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{a_{0}}{2}\\
  k_{3}=\cfrac{j_{0}}{6}\\
  k_{4}=\cfrac{\left(-4\,j_{0}-j_{1}\right)\,t^3+\left(15\,a_{1}-30\,a_{0}\right)\,t^2+\left(-120\,v_{0}-90\,v_{1}\right)\,t+210\,q}{6\,t^4}\\
  k_{5}=\cfrac{\left(2\,j_{0}+j_{1}\right)\,t^3+\left(20\,a_{0}-14\,a_{1}\right)\,t^2+\left(90\,v_{0}+78\,v_{1}\right)\,t-168\,q}{2\,t^5}\\
  k_{6}=\cfrac{\left(-4\,j_{0}-3\,j_{1}\right)\,t^3+\left(39\,a_{1}-45\,a_{0}\right)\,t^2+\left(-216\,v_{0}-204\,v_{1}\right)\,t+420\,q}{6\,t^6}\\
  k_{7}=\cfrac{\left(j_{0}+j_{1}\right)\,t^3+\left(12\,a_{0}-12\,a_{1}\right)\,t^2+\left(60\,v_{0}+60\,v_{1}\right)\,t-120\,q}{6\,t^7}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of hepta polynomial trajectory
 @param[in] t0 time for source
 @param[in] t1 time for target
 @param[in] q0 position for source
 @param[in] q1 position for target
 @param[in] v0 velocity for source
 @param[in] v1 velocity for target
 @param[in] a0 acceleration for source
 @param[in] a1 acceleration for target
 @param[in] j0 jerk for source
 @param[in] j1 jerk for target
*/
A_EXTERN void a_polytraj7_gen(a_polytraj7_s *ctx,
                              a_float_t t0, a_float_t t1,
                              a_float_t q0, a_float_t q1,
                              a_float_t v0, a_float_t v1,
                              a_float_t a0, a_float_t a1,
                              a_float_t j0, a_float_t j1);
A_EXTERN void a_polytraj7_gen0(a_polytraj7_s *ctx,
                               a_float_t t0, a_float_t t1,
                               a_float_t q0, a_float_t q1,
                               a_float_t v0, a_float_t v1,
                               a_float_t a0, a_float_t a1,
                               a_float_t j0, a_float_t j1);
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 1)
A_EXTERN void a_polytraj7_gen1(a_polytraj7_s *ctx);
#endif /* A_POLYTRAJ7 */
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 2)
A_EXTERN void a_polytraj7_gen2(a_polytraj7_s *ctx);
#endif /* A_POLYTRAJ7 */
#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 3)
A_EXTERN void a_polytraj7_gen3(a_polytraj7_s *ctx);
#endif /* A_POLYTRAJ7 */

/*!
 @brief calculate for hepta polynomial trajectory position
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float_t a_polytraj7_pos(a_polytraj7_s const *ctx, a_float_t dt);

#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 1)
/*!
 @brief calculate for hepta polynomial trajectory velocity
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float_t a_polytraj7_vel(a_polytraj7_s const *ctx, a_float_t dt);
#endif /* A_POLYTRAJ7 */

#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 2)
/*!
 @brief calculate for hepta polynomial trajectory acceleration
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float_t a_polytraj7_acc(a_polytraj7_s const *ctx, a_float_t dt);
#endif /* A_POLYTRAJ7 */

#if defined(A_POLYTRAJ7) && (A_POLYTRAJ7 + 0 > 3)
/*!
 @brief calculate for hepta polynomial trajectory jerk
 \f{aligned}{
  \begin{array}{l}
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return jerk output
*/
A_EXTERN a_float_t a_polytraj7_jer(a_polytraj7_s const *ctx, a_float_t dt);
#endif /* A_POLYTRAJ7 */

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_POLYTRAJ7 */

#endif /* a/polytraj7.h */
