/*!
 @file convexhull.h
 @brief convex hull algorithms
 @details https://en.wikipedia.org/wiki/Convex_hull_algorithms
*/

#ifndef LIBA_CONVEXHULL_H
#define LIBA_CONVEXHULL_H

#include "point2.h"
#include "point3.h"

/*!
 @ingroup liba
 @addtogroup a_convexhull convex hull algorithms
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief compute the convex hull of a set of 2D points using the Monotone Chain algorithm.
 @param[in,out] i_p points to the input 2D points in memory
 @param[in] i_n number of the input 2D points in memory
 @param[out] o_p points to the output memory where the convex hull points will be stored
 @param[in] o_n number of the output memory where the convex hull points will be stored
 @param[in] opt In-place sort option for the pre-processing step.
 If the following values are not used, assume the input points are ordered.
  @arg \b 'x'/'X' sort points primarily by X-coordinate, then by Y-coordinate.
  @arg \b 'y'/'Y' sort points primarily by Y-coordinate, then by X-coordinate.
 @param[in] tol tolerance value for collinearity checks
 @return the number of points in the computed convex hull
  @retval 0 if the output memory is too small to hold the result
*/
A_EXTERN a_size a_convexhull2(a_point2 *i_p, a_size i_n, a_point2 *o_p, a_size o_n, a_uint opt, a_real tol);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_convexhull */

#endif /* a/convexhull.h */
