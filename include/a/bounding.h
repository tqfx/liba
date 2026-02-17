/*!
 @file bounding.h
 @brief bounding volume
 @details https://en.wikipedia.org/wiki/Bounding_volume
*/

#ifndef LIBA_BOUNDING_H
#define LIBA_BOUNDING_H

#include "point2.h"
#include "point3.h"

/*!
 @ingroup liba
 @addtogroup a_bounding bounding volume
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief compute the axis-aligned bounding box (AABB) for a set of 2D points.
 @param[in] i_p points to the 2D points in memory
 @param[in] i_n number of the 2D points in memory
 @param[out] xmin stores the minimum X coordinate; may be NULL
 @param[out] xmax stores the maximum X coordinate; may be NULL
 @param[out] ymin stores the minimum Y coordinate; may be NULL
 @param[out] ymax stores the maximum Y coordinate; may be NULL
*/
A_EXTERN int a_bounding_box2(a_point2 const *i_p, a_size i_n,
                             a_real *xmin, a_real *xmax,
                             a_real *ymin, a_real *ymax);

/*!
 @brief compute the axis-aligned bounding box (AABB) for a set of 3D points.
 @param[in] i_p points to the 3D points in memory
 @param[in] i_n number of the 3D points in memory
 @param[out] xmin stores the minimum X coordinate; may be NULL
 @param[out] xmax stores the maximum X coordinate; may be NULL
 @param[out] ymin stores the minimum Y coordinate; may be NULL
 @param[out] ymax stores the maximum Y coordinate; may be NULL
 @param[out] zmin stores the minimum Z coordinate; may be NULL
 @param[out] zmax stores the maximum Z coordinate; may be NULL
*/
A_EXTERN int a_bounding_box3(a_point3 const *i_p, a_size i_n,
                             a_real *xmin, a_real *xmax,
                             a_real *ymin, a_real *ymax,
                             a_real *zmin, a_real *zmax);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_bounding */

#endif /* a/bounding.h */
