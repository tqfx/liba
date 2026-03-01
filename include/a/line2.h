/*!
 @file line2.h
 @brief two-dimensional line
*/

#ifndef LIBA_LINE2_H
#define LIBA_LINE2_H

#include "a.h"
#include "point2.h"

/*!
 @ingroup liba
 @addtogroup a_line2 two-dimensional line defined by an origin, a direction vector, and a length
 @{
*/

/*! static cast to @ref a_line2 */
#define a_line2_c(x) a_cast_s(a_line2, x)
#define a_line2_(_, x) a_cast_s(a_line2 _, x)

typedef struct a_line2 a_line2;

#if defined(__cplusplus)
namespace a
{
typedef struct a_line2 line2;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_LINE2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
/*! @endcond */
#endif /* A_HAVE_INLINE */

/*!
 @brief get the maximum length of the line segment.
 @param[in] ctx points to an instance of the two-dimensional line
 @return the maximum length value
*/
A_INTERN a_real a_line2_max(a_line2 const *ctx);
/*!
 @brief get the address of the origin point of the line.
 @param[in] ctx points to an instance of the two-dimensional line
 @return the address of the origin point
*/
A_INTERN a_point2 const *a_line2_org(a_line2 const *ctx);
/*!
 @brief get the address of the direction vector of the line.
 @param[in] ctx points to an instance of the two-dimensional line
 @return the address of the direction vector
*/
A_INTERN a_vector2 const *a_line2_dir(a_line2 const *ctx);
/*!
 @brief compute the target endpoint of the line segment.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[out] res stores the target endpoint of the line segment
*/
A_INTERN void a_line2_tgt(a_line2 const *ctx, a_point2 *res);
/*!
 @brief set the origin coordinates of the line.
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] x is the x-coordinate of the origin
 @param[in] y is the y-coordinate of the origin
*/
A_INTERN void a_line2_set_org(a_line2 *ctx, a_real x, a_real y);
/*!
 @brief set the maximum length of the line segment.
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] max is the maximum length
*/
A_INTERN void a_line2_set_max(a_line2 *ctx, a_real max);

/*!
 @brief set the direction vector and length of the line using raw components.
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] x is X component of the direction vector
 @param[in] y is Y component of the direction vector
 @return error code value
  @retval <0 failure
  @retval 0 success
*/
A_EXTERN int a_line2_set_dir(a_line2 *ctx, a_real x, a_real y);
/*!
 @brief Set the line direction and length based on a target point relative to the current origin.
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] x is X coordinate of the target point
 @param[in] y is Y coordinate of the target point
 @return error code value
  @retval <0 failure
  @retval 0 success
*/
A_EXTERN int a_line2_set_tgt(a_line2 *ctx, a_real x, a_real y);
/*!
 @brief initialize the line segment from a start point and a direction vector.
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] p points to the start point (origin)
 @param[in] v points to the direction vector (defines direction and length)
 @return error code value
  @retval <0 failure
  @retval 0 success
*/
A_EXTERN int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v);
/*!
 @brief initialize the line segment from two points (start point p, end point q).
 @param[in,out] ctx points to an instance of the two-dimensional line
 @param[in] p points to the start point (origin)
 @param[in] q points to the end point (target)
 @return error code value
  @retval <0 failure
  @retval 0 success
*/
A_EXTERN int a_line2_set(a_line2 *ctx, a_point2 const *p, a_point2 const *q);
/*!
 @brief evaluate a point on the line at a given parameter.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[in] w is the scalar parameter
 @param[out] res stores the result
*/
A_INTERN void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res);
/*!
 @brief compute the scalar projection parameter of a point onto the infinite line.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[in] rhs points to the point to project
 @return the scalar parameter
*/
A_EXTERN a_real a_line2_parm(a_line2 const *ctx, a_point2 const *rhs);
/*!
 @brief project a point onto the infinite line.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[in] rhs points to the point to project
 @param[in] res stores the projection result
 @return the projection parameter
*/
A_EXTERN a_real a_line2_proj(a_line2 const *ctx, a_point2 const *rhs, a_point2 *res);
/*!
 @brief compute the scalar projection parameter of a point onto the line segment.
 @param[in] ctx points to an instance of the line segment
 @param[in] min is the lower bound of the line segment
 @param[in] max is the upper bound of the line segment
 @param[in] rhs points to the point to project
 @return the clamped scalar parameter
*/
A_EXTERN a_real a_line2_limparm(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs);
/*!
 @brief project a point onto a line segment.
 @param[in] ctx points to an instance of the line segment
 @param[in] min is the lower bound of the line segment
 @param[in] max is the upper bound of the line segment
 @param[in] rhs points to the point to project
 @param[in] res stores the projection result
 @return the clamped projection parameter
*/
A_EXTERN a_real a_line2_limproj(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_point2 *res);

/*!
 @brief compute the signed distance from a point to the infinite line.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[in] rhs points to the point
 @return the signed distance
*/
A_EXTERN a_real a_line2_sdist(a_line2 const *ctx, a_point2 const *rhs);
/*!
 @brief compute the absolute distance from a point to the infinite line.
 @param[in] ctx points to an instance of the two-dimensional line
 @param[in] rhs points to the point
 @return the absolute distance
*/
A_EXTERN a_real a_line2_dist(a_line2 const *ctx, a_point2 const *rhs);

/*!
 @brief compute the distance from a point to the closest point on a line segment.
 @param[in] ctx points to an instance of the line segment
 @param[in] min is the lower bound of the line segment
 @param[in] max is the upper bound of the line segment
 @param[in] rhs points to the point
 @param[out] w stores the parameter of the closest point
 @param[out] p stores the coordinates of the closest point
 @return the distance
*/
A_EXTERN a_real a_line2_limdist(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_real *w, a_point2 *p);
/*!
 @brief compute the squared distance from a point to the closest point on a line segment.
 @param[in] ctx points to an instance of the line segment
 @param[in] min is the lower bound of the line segment
 @param[in] max is the upper bound of the line segment
 @param[in] rhs points to the point
 @param[out] w stores the parameter of the closest point
 @param[out] p stores the coordinates of the closest point
 @return the squared distance
*/
A_EXTERN a_real a_line2_limdist2(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_real *w, a_point2 *p);

/*!
 @brief compute the distance between two line segments.
 @param[in] ctx points to an instance of the first line segment
 @param[in] min1 is the lower bound of the first line segment
 @param[in] max1 is the upper bound of the first line segment
 @param[in] rhs points to an instance of the second line segment
 @param[in] min2 is the lower bound of the second line segment
 @param[in] max2 is the upper bound of the second line segment
 @param[out] w1 stores parameter of the closest point on the first segment
 @param[out] p1 stores coordinates of the closest point on the first segment
 @param[out] w2 stores parameter of the closest point on the second segment
 @param[out] p2 stores coordinates of the closest point on the second segment
 @return the distance between the two segments
*/
A_EXTERN a_real a_line2_segdist(a_line2 const *ctx, a_real min1, a_real max1,
                                a_line2 const *rhs, a_real min2, a_real max2,
                                a_real *w1, a_point2 *p1, a_real *w2, a_point2 *p2);
/*!
 @brief compute the squared distance between two line segments.
 @param[in] ctx points to an instance of the first line segment
 @param[in] min1 is the lower bound of the first line segment
 @param[in] max1 is the upper bound of the first line segment
 @param[in] rhs points to an instance of the second line segment
 @param[in] min2 is the lower bound of the second line segment
 @param[in] max2 is the upper bound of the second line segment
 @param[out] w1 stores parameter of the closest point on the first segment
 @param[out] p1 stores coordinates of the closest point on the first segment
 @param[out] w2 stores parameter of the closest point on the second segment
 @param[out] p2 stores coordinates of the closest point on the second segment
 @return the squared distance between the two segments
*/
A_EXTERN a_real a_line2_segdist2(a_line2 const *ctx, a_real min1, a_real max1,
                                 a_line2 const *rhs, a_real min2, a_real max2,
                                 a_real *w1, a_point2 *p1, a_real *w2, a_point2 *p2);

/*!
 @brief compute the intersection between a point and a line segment.
 @param[in] ctx points to an instance of the line segment
 @param[in] min is the lower bound of the line segment
 @param[in] max is the upper bound of the line segment
 @param[in] rhs points to the point to intersect
 @param[out] w stores the parameter on the segment
 @return the intersection type
  @retval 1 intersection found
  @retval 0 no intersection
*/
A_EXTERN int a_line2_int0(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_real *w);
/*!
 @brief compute the intersection between two line segments.
 @param[in] ctx points to an instance of the first line segment
 @param[in] min1 is the lower bound of the first line segment
 @param[in] max1 is the upper bound of the first line segment
 @param[in] rhs points to an instance of the second line segment
 @param[in] min2 is the lower bound of the second line segment
 @param[in] max2 is the upper bound of the second line segment
 @param[out] w1 stores parameter of the point on the first segment or the start point on the first segment
 @param[out] w2 stores parameter of the point on the second segment or the end point on the first segment
 @return the intersection type
  @retval 2 intersection is a segment, the start point and the end point on the first segment
  @retval 1 intersection is a point, the point on the first segment and the second segment
  @retval 0 no intersection
*/
A_EXTERN int a_line2_int1(a_line2 const *ctx, a_real min1, a_real max1,
                          a_line2 const *rhs, a_real min2, a_real max2,
                          a_real *w1, a_real *w2);

/*!
 @brief rotate a line segment around a pivot point using pre-calculated sine and cosine values.
 @param[in] ctx points to an instance of the line segment
 @param[in] rhs points to the pivot point
 @param[in] sin is precomputed \f$\sin(\theta)\f$
 @param[in] cos is precomputed \f$\cos(\theta)\f$
 @param[out] res stores the result line segment
*/
A_EXTERN void a_line2_rot_(a_line2 const *ctx, a_point2 const *rhs, a_real sin, a_real cos, a_line2 *res);
/*!
 @brief rotate a line segment around a specified pivot point.
 @param[in] ctx points to an instance of the line segment
 @param[in] rhs points to the pivot point
 @param[in] angle is rotation angle in radians
 @param[out] res stores the result line segment
*/
A_EXTERN void a_line2_rot(a_line2 const *ctx, a_point2 const *rhs, a_real angle, a_line2 *res);

#if !defined A_HAVE_INLINE || defined(LIBA_LINE2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for two-dimensional line defined by an origin, a direction vector, and a length
*/
struct a_line2
{
    a_point2 org; /*!< origin point of the line */
    a_vector2 dir_; /*!< normalized direction vector of the line */
    a_real max; /*!< maximum length of the line segment */
#if defined(__cplusplus)
    /*! @copybrief a_line2_set_max @see a_line2_set_max */
    A_INLINE void set_max(a_real max_) { max = max_; }
    /*! @copybrief a_line2_set_org @see a_line2_set_org */
    A_INLINE void set_org(a_real x, a_real y)
    {
        a_line2_set_org(this, x, y);
    }
    /*! @copybrief a_line2_dir @see a_line2_dir */
    A_INLINE a_vector2 const &dir() const { return dir_; }
    /*! @copybrief a_line2_set_dir @see a_line2_set_dir */
    A_INLINE int set_dir(a_real x, a_real y)
    {
        return a_line2_set_dir(this, x, y);
    }
    /*! @copybrief a_line2_tgt @see a_line2_tgt */
    A_INLINE void tgt(a_point2 &res) const { a_line2_tgt(this, &res); }
    /*! @copybrief a_line2_set_tgt @see a_line2_set_tgt */
    A_INLINE int set_tgt(a_real x, a_real y)
    {
        return a_line2_set_tgt(this, x, y);
    }
    /*! @copybrief a_line2_setv @see a_line2_setv */
    A_INLINE int set(a_point2 const &p, a_vector2 const &v)
    {
        return a_line2_setv(this, &p, &v);
    }
    /*! @copybrief a_line2_set @see a_line2_set */
    A_INLINE int set(a_point2 const &p, a_point2 const &q)
    {
        return a_line2_set(this, &p, &q);
    }
    /*! @copybrief a_line2_eval @see a_line2_eval */
    A_INLINE void eval(a_real w, a_point2 &res) const
    {
        a_line2_eval(this, w, &res);
    }
    /*! @copybrief a_line2_parm @see a_line2_parm */
    A_INLINE a_real parm(a_point2 const &rhs) const
    {
        return a_line2_parm(this, &rhs);
    }
    /*! @copybrief a_line2_proj @see a_line2_proj */
    A_INLINE a_real proj(a_point2 const &rhs, a_point2 &res) const
    {
        return a_line2_proj(this, &rhs, &res);
    }
    /*! @copybrief a_line2_limparm @see a_line2_limparm */
    A_INLINE a_real limparm(a_real min_, a_real max_, a_point2 const &rhs) const
    {
        return a_line2_limparm(this, min_, max_, &rhs);
    }
    /*! @copybrief a_line2_limproj @see a_line2_limproj */
    A_INLINE a_real limproj(a_real min_, a_real max_, a_point2 const &rhs, a_point2 &res) const
    {
        return a_line2_limproj(this, min_, max_, &rhs, &res);
    }
    /*! @copybrief a_line2_sdist @see a_line2_sdist */
    A_INLINE a_real sdist(a_point2 const &rhs) const
    {
        return a_line2_sdist(this, &rhs);
    }
    /*! @copybrief a_line2_dist @see a_line2_dist */
    A_INLINE a_real dist(a_point2 const &rhs) const
    {
        return a_line2_dist(this, &rhs);
    }
    /*! @copybrief a_line2_limdist @see a_line2_limdist */
    A_INLINE a_real limdist(a_real min_, a_real max_, a_point2 const &rhs, a_real &w, a_point2 &p)
    {
        return a_line2_limdist(this, min_, max_, &rhs, &w, &p);
    }
    /*! @copybrief a_line2_limdist2 @see a_line2_limdist2 */
    A_INLINE a_real limdist2(a_real min_, a_real max_, a_point2 const &rhs, a_real &w, a_point2 &p)
    {
        return a_line2_limdist2(this, min_, max_, &rhs, &w, &p);
    }
    /*! @copybrief a_line2_segdist @see a_line2_segdist */
    A_INLINE a_real segdist(a_real min1, a_real max1, a_line2 const &rhs, a_real min2, a_real max2,
                            a_real &w1, a_point2 &p1, a_real &w2, a_point2 &p2) const
    {
        return a_line2_segdist(this, min1, max1, &rhs, min2, max2, &w1, &p1, &w2, &p2);
    }
    /*! @copybrief a_line2_segdist2 @see a_line2_segdist2 */
    A_INLINE a_real segdist2(a_real min1, a_real max1, a_line2 const &rhs, a_real min2, a_real max2,
                             a_real &w1, a_point2 &p1, a_real &w2, a_point2 &p2) const
    {
        return a_line2_segdist2(this, min1, max1, &rhs, min2, max2, &w1, &p1, &w2, &p2);
    }
    /*! @copybrief a_line2_int0 @see a_line2_int0 */
    A_INLINE int int0(a_real min_, a_real max_, a_point2 const &rhs, a_real &w) const
    {
        return a_line2_int0(this, min_, max_, &rhs, &w);
    }
    /*! @copybrief a_line2_int1 @see a_line2_int1 */
    A_INLINE int int1(a_real min1, a_real max1, a_line2 const &rhs, a_real min2, a_real max2,
                      a_real &w1, a_real &w2) const
    {
        return a_line2_int1(this, min1, max1, &rhs, min2, max2, &w1, &w2);
    }
    /*! @copybrief a_line2_rot_ @see a_line2_rot_ */
    A_INLINE void rot(a_point2 const &rhs, a_real sin, a_real cos, a_line2 &res) const
    {
        a_line2_rot_(this, &rhs, sin, cos, &res);
    }
    /*! @copybrief a_line2_rot @see a_line2_rot */
    A_INLINE void rot(a_point2 const &rhs, a_real angle, a_line2 &res) const
    {
        a_line2_rot(this, &rhs, angle, &res);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_LINE2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN A_INLINE
/*! @endcond */
#endif /* LIBA_LINE2_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_LINE2_C)

A_INTERN a_real a_line2_max(a_line2 const *ctx)
{
    return ctx->max;
}
A_INTERN a_point2 const *a_line2_org(a_line2 const *ctx)
{
    return &ctx->org;
}
A_INTERN a_vector2 const *a_line2_dir(a_line2 const *ctx)
{
    return &ctx->dir_;
}
A_INTERN void a_line2_tgt(a_line2 const *ctx, a_point2 *res)
{
    a_line2_eval(ctx, ctx->max, res);
}
A_INTERN void a_line2_set_org(a_line2 *ctx, a_real x, a_real y)
{
    ctx->org.x = x;
    ctx->org.y = y;
}
A_INTERN void a_line2_set_max(a_line2 *ctx, a_real max)
{
    ctx->max = max;
}

A_INTERN void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res)
{
    a_point2 const *const o = &ctx->org;
    a_vector2 const *const d = &ctx->dir_;
    res->x = o->x + d->x * w;
    res->y = o->y + d->y * w;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_LINE2_C)
/*! @cond */
#undef A_INTERN
#define A_INTERN static A_INLINE
/*! @endcond */
#endif /* LIBA_LINE2_C */

/*! @} a_line2 */

#endif /* a/line2.h */
