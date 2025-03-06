/*!
 @file trajpoly7.h
 @brief hepta polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots
*/

#ifndef LIBA_TRAJPOLY7_H
#define LIBA_TRAJPOLY7_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_trajpoly7 hepta polynomial trajectory
 @{
*/

typedef struct a_trajpoly7 a_trajpoly7;

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
A_EXTERN void a_trajpoly7_gen(a_trajpoly7 *ctx, a_real ts,
                              a_real p0, a_real p1,
                              a_real v0, a_real v1,
                              a_real a0, a_real a1,
                              a_real j0, a_real j1);

/*!
 @brief compute coefficients of position for hepta polynomial trajectory
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[out] c coefficients of position
*/
A_EXTERN void a_trajpoly7_c0(a_trajpoly7 const *ctx, a_real c[8]);

/*!
 @brief compute coefficients of velocity for hepta polynomial trajectory
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[out] c coefficients of velocity
*/
A_EXTERN void a_trajpoly7_c1(a_trajpoly7 const *ctx, a_real c[7]);

/*!
 @brief compute coefficients of acceleration for hepta polynomial trajectory
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[out] c coefficients of acceleration
*/
A_EXTERN void a_trajpoly7_c2(a_trajpoly7 const *ctx, a_real c[6]);

/*!
 @brief compute coefficients of jerk for hepta polynomial trajectory
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[out] c coefficients of jerk
*/
A_EXTERN void a_trajpoly7_c3(a_trajpoly7 const *ctx, a_real c[5]);

/*!
 @brief compute position for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p(t)=c_{0}+c_{1}\left(t-t_{0}\right)+c_{2}\left(t-t_{0}\right)^{2}+c_{3}\left(t-t_{0}\right)^{3}+c_{4}\left(t-t_{0}\right)^{4}+c_{5}\left(t-t_{0}\right)^{5}+c_{6}\left(t-t_{0}\right)^{6}+c_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] x difference between current time and initial time
 @return position output
*/
A_EXTERN a_real a_trajpoly7_pos(a_trajpoly7 const *ctx, a_real x);

/*!
 @brief compute velocity for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \dot{p}(t)=c_{1}+2 c_{2}\left(t-t_{0}\right)+3 c_{3}\left(t-t_{0}\right)^{2}+4 c_{4}\left(t-t_{0}\right)^{3}+5 c_{5}\left(t-t_{0}\right)^{4}+6 c_{6}\left(t-t_{0}\right)^{5}+7 c_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] x difference between current time and initial time
 @return velocity output
*/
A_EXTERN a_real a_trajpoly7_vel(a_trajpoly7 const *ctx, a_real x);

/*!
 @brief compute acceleration for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  \ddot{p}(t)=2 c_{2}+6 c_{3}\left(t-t_{0}\right)+12 c_{4}\left(t-t_{0}\right)^{2}+20 c_{5}\left(t-t_{0}\right)^{3}+30 c_{6}\left(t-t_{0}\right)^{4}+42 c_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] x difference between current time and initial time
 @return acceleration output
*/
A_EXTERN a_real a_trajpoly7_acc(a_trajpoly7 const *ctx, a_real x);

/*!
 @brief compute jerk for hepta polynomial trajectory
 \f{aligned}{
  \begin{array}{l}
  p^{(3)}(t)=6 c_{3}+24 c_{4}\left(t-t_{0}\right)+60 c_{5}\left(t-t_{0}\right)^{2}+120 c_{6}\left(t-t_{0}\right)^{3}+210 c_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in] ctx points to an instance of hepta polynomial trajectory
 @param[in] x difference between current time and initial time
 @return jerk output
*/
A_EXTERN a_real a_trajpoly7_jer(a_trajpoly7 const *ctx, a_real x);

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
    a_real c[8]; /*!< coefficients of position */
#if defined(__cplusplus)
    A_INLINE void gen(a_real ts, a_real p0, a_real p1,
                      a_real v0 = 0, a_real v1 = 0,
                      a_real a0 = 0, a_real a1 = 0,
                      a_real j0 = 0, a_real j1 = 0)
    {
        a_trajpoly7_gen(this, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }
    A_INLINE a_real pos(a_real x) const
    {
        return a_trajpoly7_pos(this, x);
    }
    A_INLINE a_real vel(a_real x) const
    {
        return a_trajpoly7_vel(this, x);
    }
    A_INLINE a_real acc(a_real x) const
    {
        return a_trajpoly7_acc(this, x);
    }
    A_INLINE a_real jer(a_real x) const
    {
        return a_trajpoly7_jer(this, x);
    }
    A_INLINE void c0(a_real x[8]) const
    {
        a_trajpoly7_c0(this, x);
    }
    A_INLINE void c1(a_real x[7]) const
    {
        a_trajpoly7_c1(this, x);
    }
    A_INLINE void c2(a_real x[6]) const
    {
        a_trajpoly7_c2(this, x);
    }
    A_INLINE void c3(a_real x[5]) const
    {
        a_trajpoly7_c3(this, x);
    }
#endif /* __cplusplus */
};

/*! @} a_trajpoly7 */

#endif /* a/trajpoly7.h */
