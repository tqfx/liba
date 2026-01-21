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
 @addtogroup a_line2 two-dimensional line
 @{
*/

/*! static cast to \ref a_line2 */
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
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN a_real a_line2_lim(a_line2 const *ctx);
A_INTERN a_point2 const *a_line2_org(a_line2 const *ctx);
A_INTERN a_vector2 const *a_line2_dir(a_line2 const *ctx);
A_INTERN void a_line2_tgt(a_line2 const *ctx, a_point2 *res);
A_INTERN void a_line2_set_org(a_line2 *ctx, a_real x, a_real y);
A_INTERN void a_line2_set_lim(a_line2 *ctx, a_real max);

A_EXTERN int a_line2_set_dir(a_line2 *ctx, a_real x, a_real y);
A_EXTERN int a_line2_set_tgt(a_line2 *ctx, a_real x, a_real y);
A_EXTERN int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v);
A_EXTERN int a_line2_set(a_line2 *ctx, a_point2 const *p, a_point2 const *q);
A_EXTERN void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res);
A_EXTERN a_real a_line2_parm(a_line2 const *ctx, a_point2 const *rhs);
A_EXTERN a_real a_line2_proj(a_line2 const *ctx, a_point2 const *rhs, a_point2 *res);
A_EXTERN a_real a_line2_limparm(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs);
A_EXTERN a_real a_line2_limproj(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_point2 *res);

A_EXTERN a_real a_line2_sdist(a_line2 const *ctx, a_point2 const *rhs);
A_EXTERN a_real a_line2_dist(a_line2 const *ctx, a_point2 const *rhs);

A_EXTERN a_real a_line2_limdist(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_real *w, a_point2 *p);
A_EXTERN a_real a_line2_limdist2(a_line2 const *ctx, a_real min, a_real max, a_point2 const *rhs, a_real *w, a_point2 *p);

A_EXTERN a_real a_line2_segdist(a_line2 const *ctx, a_line2 const *rhs,
                                a_real min1, a_real max1, a_real min2, a_real max2,
                                a_real *w1, a_real *w2, a_point2 *p1, a_point2 *p2);
A_EXTERN a_real a_line2_segdist2(a_line2 const *ctx, a_line2 const *rhs,
                                 a_real min1, a_real max1, a_real min2, a_real max2,
                                 a_real *w1, a_real *w2, a_point2 *p1, a_point2 *p2);

A_EXTERN int a_line2_int0(a_line2 const *ctx, a_point2 const *rhs, a_real min, a_real max, a_real *w);
A_EXTERN int a_line2_int1(a_line2 const *ctx, a_line2 const *rhs,
                          a_real min1, a_real max1, a_real min2, a_real max2,
                          a_real *w1, a_real *w2);

A_EXTERN void a_line2_rot(a_line2 const *ctx, a_point2 const *rhs, a_real angle, a_line2 *res);

#if !defined A_HAVE_INLINE || defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for two-dimensional line
*/
struct a_line2
{
    a_point2 orig;
    a_vector2 dir_;
    a_real max;
#if defined(__cplusplus)
    A_INLINE a_real lim() const { return max; }
    A_INLINE void set_lim(a_real max_) { max = max_; }
    A_INLINE a_point2 const &org() const { return orig; }
    A_INLINE void set_org(a_real x, a_real y)
    {
        a_line2_set_org(this, x, y);
    }
    A_INLINE a_vector2 const &dir() const { return dir_; }
    A_INLINE int set_dir(a_real x, a_real y)
    {
        return a_line2_set_dir(this, x, y);
    }
    A_INLINE void tgt(a_point2 &res) const { a_line2_tgt(this, &res); }
    A_INLINE int set_tgt(a_real x, a_real y)
    {
        return a_line2_set_tgt(this, x, y);
    }
    A_INLINE int set(a_point2 const &p, a_vector2 const &v)
    {
        return a_line2_setv(this, &p, &v);
    }
    A_INLINE int set(a_point2 const &p, a_point2 const &q)
    {
        return a_line2_set(this, &p, &q);
    }
    A_INLINE void eval(a_real w, a_point2 &res) const
    {
        a_line2_eval(this, w, &res);
    }
    A_INLINE a_real parm(a_point2 const &rhs) const
    {
        return a_line2_parm(this, &rhs);
    }
    A_INLINE a_real proj(a_point2 const &rhs, a_point2 &res) const
    {
        return a_line2_proj(this, &rhs, &res);
    }
    A_INLINE a_real limparm(a_real min, a_real max_, a_point2 const &rhs) const
    {
        return a_line2_limparm(this, min, max_, &rhs);
    }
    A_INLINE a_real limproj(a_real min, a_real max_, a_point2 const &rhs, a_point2 &res) const
    {
        return a_line2_limproj(this, min, max_, &rhs, &res);
    }
    A_INLINE a_real sdist(a_point2 const &rhs) const
    {
        return a_line2_sdist(this, &rhs);
    }
    A_INLINE a_real dist(a_point2 const &rhs) const
    {
        return a_line2_dist(this, &rhs);
    }
    A_INLINE a_real limdist(a_real min, a_real max_, a_point2 const &rhs, a_real &w, a_point2 &p)
    {
        return a_line2_limdist(this, min, max_, &rhs, &w, &p);
    }
    A_INLINE a_real limdist2(a_real min, a_real max_, a_point2 const &rhs, a_real &w, a_point2 &p)
    {
        return a_line2_limdist2(this, min, max_, &rhs, &w, &p);
    }
    A_INLINE a_real segdist(a_line2 const &rhs, a_real min1, a_real max1, a_real min2, a_real max2,
                            a_real &w1, a_real &w2, a_point2 &p1, a_point2 &p2) const
    {
        return a_line2_segdist(this, &rhs, min1, max1, min2, max2, &w1, &w2, &p1, &p2);
    }
    A_INLINE a_real segdist2(a_line2 const &rhs, a_real min1, a_real max1, a_real min2, a_real max2,
                             a_real &w1, a_real &w2, a_point2 &p1, a_point2 &p2) const
    {
        return a_line2_segdist2(this, &rhs, min1, max1, min2, max2, &w1, &w2, &p1, &p2);
    }
    A_INLINE int int0(a_point2 const &rhs, a_real min, a_real max_, a_real &w) const
    {
        return a_line2_int0(this, &rhs, min, max_, &w);
    }
    A_INLINE int int1(a_line2 const &rhs, a_real min1, a_real max1, a_real min2, a_real max2,
                      a_real &w1, a_real &w2) const
    {
        return a_line2_int1(this, &rhs, min1, max1, min2, max2, &w1, &w2);
    }
    A_INLINE void rot(a_point2 const &rhs, a_real angle, a_line2 &res) const
    {
        a_line2_rot(this, &rhs, angle, &res);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_LINE2_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_LINE2_C)

A_INTERN a_real a_line2_lim(a_line2 const *ctx)
{
    return ctx->max;
}
A_INTERN a_point2 const *a_line2_org(a_line2 const *ctx)
{
    return &ctx->orig;
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
    ctx->orig.x = x;
    ctx->orig.y = y;
}
A_INTERN void a_line2_set_lim(a_line2 *ctx, a_real max)
{
    ctx->max = max;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_LINE2_C */

/*! @} a_line2 */

#endif /* a/line2.h */
