/*!
 @file line3.h
 @brief three-dimensional line
*/

#ifndef LIBA_LINE3_H
#define LIBA_LINE3_H

#include "a.h"
#include "point3.h"

/*!
 @ingroup liba
 @addtogroup a_line3 three-dimensional line
 @{
*/

/*! static cast to \ref a_line3 */
#define a_line3_c(x) a_cast_s(a_line3, x)
#define a_line3_(_, x) a_cast_s(a_line3 _, x)

typedef struct a_line3 a_line3;

#if defined(__cplusplus)
namespace a
{
typedef struct a_line3 line3;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN a_real a_line3_len(a_line3 const *ctx);
A_INTERN a_point3 const *a_line3_org(a_line3 const *ctx);
A_INTERN a_vector3 const *a_line3_dir(a_line3 const *ctx);
A_INTERN void a_line3_tgt(a_line3 const *ctx, a_point3 *res);
A_INTERN void a_line3_set_org(a_line3 *ctx, a_real x, a_real y, a_real z);
A_INTERN void a_line3_set_len(a_line3 *ctx, a_real max);

A_EXTERN int a_line3_set_dir(a_line3 *ctx, a_real x, a_real y, a_real z);
A_EXTERN int a_line3_set_tgt(a_line3 *ctx, a_real x, a_real y, a_real z);
A_EXTERN int a_line3_setv(a_line3 *ctx, a_point3 const *p, a_vector3 const *v);
A_EXTERN int a_line3_set(a_line3 *ctx, a_point3 const *p, a_point3 const *q);
A_EXTERN void a_line3_eval(a_line3 const *ctx, a_real w, a_point3 *res);
A_EXTERN a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *res);

A_EXTERN a_real a_line3_dist(a_line3 const *ctx, a_point3 const *p);
A_EXTERN a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *p);
A_EXTERN a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *p);

A_EXTERN int a_line3_int0(a_line3 const *ctx, a_point3 const *rhs, a_real min, a_real max, a_real *res);
A_EXTERN int a_line3_int1(a_line3 const *ctx, a_line3 const *rhs,
                          a_real min1, a_real max1, a_real min2, a_real max2,
                          a_real *res1, a_real *res2);

#if !defined A_HAVE_INLINE || defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for three-dimensional line
*/
struct a_line3
{
    a_point3 orig;
    a_vector3 dir_;
    a_real max;
#if defined(__cplusplus)
    A_INLINE a_real len() const { return max; }
    A_INLINE void set_len(a_real max_) { max = max_; }
    A_INLINE a_point3 const &org() const { return orig; }
    A_INLINE void set_org(a_real x, a_real y, a_real z)
    {
        a_line3_set_org(this, x, y, z);
    }
    A_INLINE a_vector3 const &dir() const { return dir_; }
    A_INLINE int set_dir(a_real x, a_real y, a_real z)
    {
        return a_line3_set_dir(this, x, y, z);
    }
    A_INLINE void tgt(a_point3 &res) const { a_line3_tgt(this, &res); }
    A_INLINE int set_tgt(a_real x, a_real y, a_real z)
    {
        return a_line3_set_tgt(this, x, y, z);
    }
    A_INLINE int set(a_point3 const &p, a_vector3 const &v)
    {
        return a_line3_setv(this, &p, &v);
    }
    A_INLINE int set(a_point3 const &p, a_point3 const &q)
    {
        return a_line3_set(this, &p, &q);
    }
    A_INLINE void eval(a_real w, a_point3 &res) const
    {
        a_line3_eval(this, w, &res);
    }
    A_INLINE a_real proj(a_point3 const &p, a_point3 &res) const
    {
        return a_line3_proj(this, &p, &res);
    }
    A_INLINE a_real dist(a_point3 const &p) const
    {
        return a_line3_dist(this, &p);
    }
    A_INLINE a_real dist1(a_point3 const &p) const
    {
        return a_line3_dist1(this, &p);
    }
    A_INLINE a_real dist2(a_point3 const &p) const
    {
        return a_line3_dist2(this, &p);
    }
    A_INLINE int int0(a_point3 const &rhs, a_real min, a_real max_, a_real &res) const
    {
        return a_line3_int0(this, &rhs, min, max_, &res);
    }
    A_INLINE int int1(a_line3 const &rhs, a_real min1,
                      a_real max1, a_real min2, a_real max2,
                      a_real &res1, a_real &res2) const
    {
        return a_line3_int1(this, &rhs, min1, max1, min2, max2, &res1, &res2);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_LINE3_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_LINE3_C)

A_INTERN a_real a_line3_len(a_line3 const *ctx)
{
    return ctx->max;
}
A_INTERN a_point3 const *a_line3_org(a_line3 const *ctx)
{
    return &ctx->orig;
}
A_INTERN a_vector3 const *a_line3_dir(a_line3 const *ctx)
{
    return &ctx->dir_;
}
A_INTERN void a_line3_tgt(a_line3 const *ctx, a_point3 *res)
{
    a_line3_eval(ctx, ctx->max, res);
}
A_INTERN void a_line3_set_org(a_line3 *ctx, a_real x, a_real y, a_real z)
{
    ctx->orig.x = x;
    ctx->orig.y = y;
    ctx->orig.z = z;
}
A_INTERN void a_line3_set_len(a_line3 *ctx, a_real max)
{
    ctx->max = max;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_LINE3_C */

/*! @} a_line3 */

#endif /* a/line3.h */
