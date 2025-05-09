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

A_INTERN a_real a_line2_len(a_line2 const *ctx);
A_INTERN void a_line2_org(a_line2 const *ctx, a_point2 *res);
A_INTERN void a_line2_tgt(a_line2 const *ctx, a_point2 *res);
A_INTERN void a_line2_dir(a_line2 const *ctx, a_vector2 *res);

A_EXTERN int a_line2_setv(a_line2 *ctx, a_point2 const *p, a_vector2 const *v);
A_EXTERN int a_line2_set(a_line2 *ctx, a_point2 const *p, a_point2 const *q);
A_EXTERN void a_line2_eval(a_line2 const *ctx, a_real w, a_point2 *res);
A_EXTERN a_real a_line2_proj(a_line2 const *ctx, a_point2 const *p, a_point2 *q);

A_EXTERN a_real a_line2_dist_(a_line2 const *ctx, a_point2 const *p);
A_EXTERN a_real a_line2_dist(a_line2 const *ctx, a_point2 const *p);

#if !defined A_HAVE_INLINE || defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#undef max
/*!
 @brief instance structure for two-dimensional line
*/
struct a_line2
{
    a_point2 orig;
    a_vector2 dir;
    a_real max;
#if defined(__cplusplus)
    A_INLINE a_real len() const { return max; }
    A_INLINE void org(a_point2 &res) const { a_line2_org(this, &res); }
    A_INLINE void tgt(a_point2 &res) const { a_line2_tgt(this, &res); }
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
    A_INLINE a_real proj(a_point2 const &p, a_point2 &q) const
    {
        return a_line2_proj(this, &p, &q);
    }
    A_INLINE a_real dist_(a_point2 const &p) const
    {
        return a_line2_dist_(this, &p);
    }
    A_INLINE a_real dist(a_point2 const &p) const
    {
        return a_line2_dist(this, &p);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_LINE2_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_LINE2_C)

A_INTERN a_real a_line2_len(a_line2 const *ctx)
{
    return ctx->max;
}
A_INTERN void a_line2_org(a_line2 const *ctx, a_point2 *res)
{
    *res = ctx->orig;
}
A_INTERN void a_line2_tgt(a_line2 const *ctx, a_point2 *res)
{
    a_line2_eval(ctx, ctx->max, res);
}
A_INTERN void a_line2_dir(a_line2 const *ctx, a_vector2 *res)
{
    *res = ctx->dir;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_LINE2_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_LINE2_C */

/*! @} a_line2 */

#endif /* a/line2.h */
