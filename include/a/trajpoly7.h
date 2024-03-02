/*!
 @file trajpoly7.h
 @brief hepta polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJPOLY7_H
#define LIBA_TRAJPOLY7_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_TRAJPOLY7 hepta polynomial trajectory
 @{
*/

typedef struct a_trajpoly7 a_trajpoly7;

#if !defined A_TRAJPOLY7
#define A_TRAJPOLY7 4
#endif /* A_TRAJPOLY7 */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief generate for hepta polynomial trajectory
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  p=p_{1}-p_{0}\\
  c_{0}=p_{0}\\
  c_{1}=v_{0}\\
  c_{2}=\cfrac{a_{0}}{2}\\
  c_{3}=\cfrac{j_{0}}{6}\\
  c_{4}=\cfrac{\left(-4\,j_{0}-j_{1}\right)\,t^3+\left(15\,a_{1}-30\,a_{0}\right)\,t^2+\left(-120\,v_{0}-90\,v_{1}\right)\,t+210\,p}{6\,t^4}\\
  c_{5}=\cfrac{\left(2\,j_{0}+j_{1}\right)\,t^3+\left(20\,a_{0}-14\,a_{1}\right)\,t^2+\left(90\,v_{0}+78\,v_{1}\right)\,t-168\,p}{2\,t^5}\\
  c_{6}=\cfrac{\left(-4\,j_{0}-3\,j_{1}\right)\,t^3+\left(39\,a_{1}-45\,a_{0}\right)\,t^2+\left(-216\,v_{0}-204\,v_{1}\right)\,t+420\,p}{6\,t^6}\\
  c_{7}=\cfrac{\left(j_{0}+j_{1}\right)\,t^3+\left(12\,a_{0}-12\,a_{1}\right)\,t^2+\left(60\,v_{0}+60\,v_{1}\right)\,t-120\,p}{6\,t^7}
  \end{array}\right.
 \f}
 @param[in,out] ctx points to an instance of hepta polynomial trajectory
 @param[in] ts difference between final time and initial time
 @param[in] p0 initial position
 @param[in] p1 final position
 @param[in] v0 initial velocity
 @param[in] v1 final velocity
 @param[in] a0 initial acceleration
 @param[in] a1 final acceleration
 @param[in] j0 initial jerk
 @param[in] j1 final jerk
*/
A_EXTERN void a_trajpoly7_gen(a_trajpoly7 *ctx, a_float ts,
                              a_float p0, a_float p1,
                              a_float v0, a_float v1,
                              a_float a0, a_float a1,
                              a_float j0, a_float j1);
A_EXTERN void a_trajpoly7_gen0(a_trajpoly7 *ctx, a_float ts,
                               a_float p0, a_float p1,
                               a_float v0, a_float v1,
                               a_float a0, a_float a1,
                               a_float j0, a_float j1);
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
A_EXTERN void a_trajpoly7_gen1(a_trajpoly7 *ctx);
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
A_EXTERN void a_trajpoly7_gen2(a_trajpoly7 *ctx);
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
A_EXTERN void a_trajpoly7_gen3(a_trajpoly7 *ctx);
#endif /* A_TRAJPOLY7 */

/*!
 @brief calculate position for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3}+c_{4}\left(t-t_{0}\right)^{4}+c_{5}\left(t-t_{0}\right)^{5}+c_{6}\left(t-t_{0}\right)^{6}+c_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return position output
*/
A_EXTERN a_float a_trajpoly7_pos(a_trajpoly7 const *ctx, a_float dt);

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
/*!
 @brief calculate velocity for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2}+4 c_{4}\left(t-t_{0}\right)^{3}+5 c_{5}\left(t-t_{0}\right)^{4}+6 c_{6}\left(t-t_{0}\right)^{5}+7 c_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_float a_trajpoly7_vel(a_trajpoly7 const *ctx, a_float dt);
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
/*!
 @brief calculate acceleration for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)+12 c_{4}\left(t-t_{0}\right)^{2}+20 c_{5}\left(t-t_{0}\right)^{3}+30 c_{6}\left(t-t_{0}\right)^{4}+42 c_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_float a_trajpoly7_acc(a_trajpoly7 const *ctx, a_float dt);
#endif /* A_TRAJPOLY7 */

#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
/*!
 @brief calculate jerk for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p^{(3)}(t)=6 c_{3}+24 c_{4}\left(t-t_{0}\right)+60 c_{5}\left(t-t_{0}\right)^{2}+120 c_{6}\left(t-t_{0}\right)^{3}+210 c_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] dt difference between current time and initial time
 @return jerk output
*/
A_EXTERN a_float a_trajpoly7_jer(a_trajpoly7 const *ctx, a_float dt);
#endif /* A_TRAJPOLY7 */

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_trajpoly7 trajpoly7;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3}+c_{4}\left(t-t_{0}\right)^{4}+c_{5}\left(t-t_{0}\right)^{5}+c_{6}\left(t-t_{0}\right)^{6}+c_{7}\left(t-t_{0}\right)^{7}\\
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2}+4 c_{4}\left(t-t_{0}\right)^{3}+5 c_{5}\left(t-t_{0}\right)^{4}+6 c_{6}\left(t-t_{0}\right)^{5}+7 c_{7}\left(t-t_{0}\right)^{6}\\
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)+12 c_{4}\left(t-t_{0}\right)^{2}+20 c_{5}\left(t-t_{0}\right)^{3}+30 c_{6}\left(t-t_{0}\right)^{4}+42 c_{7}\left(t-t_{0}\right)^{5}\\
  p^{(3)}(t)=6 c_{3}+24 c_{4}\left(t-t_{0}\right)+60 c_{5}\left(t-t_{0}\right)^{2}+120 c_{6}\left(t-t_{0}\right)^{3}+210 c_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
*/
struct a_trajpoly7
{
    a_float p[8]; //!< coefficients of position
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
    a_float v[7]; //!< coefficients of velocity
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
    a_float a[6]; //!< coefficients of acceleration
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
    a_float j[5]; //!< coefficients of jerk
#endif /* A_TRAJPOLY7 */
#if defined(__cplusplus)
    A_INLINE void gen(a_float ts, a_float p0, a_float p1,
                      a_float v0 = 0, a_float v1 = 0,
                      a_float a0 = 0, a_float a1 = 0,
                      a_float j0 = 0, a_float j1 = 0)
    {
        a_trajpoly7_gen(this, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }
    A_INLINE void gen0(a_float ts, a_float p0, a_float p1,
                       a_float v0 = 0, a_float v1 = 0,
                       a_float a0 = 0, a_float a1 = 0,
                       a_float j0 = 0, a_float j1 = 0)
    {
        a_trajpoly7_gen0(this, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }
    A_INLINE a_float pos(a_float dt) const
    {
        return a_trajpoly7_pos(this, dt);
    }
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 1)
    A_INLINE void gen1() { a_trajpoly7_gen1(this); }
    A_INLINE a_float vel(a_float dt) const
    {
        return a_trajpoly7_vel(this, dt);
    }
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 2)
    A_INLINE void gen2() { a_trajpoly7_gen2(this); }
    A_INLINE a_float acc(a_float dt) const
    {
        return a_trajpoly7_acc(this, dt);
    }
#endif /* A_TRAJPOLY7 */
#if defined(A_TRAJPOLY7) && (A_TRAJPOLY7 + 0 > 3)
    A_INLINE void gen3() { a_trajpoly7_gen3(this); }
    A_INLINE a_float jer(a_float dt) const
    {
        return a_trajpoly7_jer(this, dt);
    }
#endif /* A_TRAJPOLY7 */
#endif /* __cplusplus */
};

/*! @} A_TRAJPOLY7 */

#endif /* a/trajpoly7.h */
