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
A_INTERN void a_line3_org(a_line3 const *ctx, a_point3 *res);
A_INTERN void a_line3_tgt(a_line3 const *ctx, a_point3 *res);
A_INTERN void a_line3_dir(a_line3 const *ctx, a_vector3 *res);

A_EXTERN int a_line3_set1(a_line3 *ctx, a_point3 const *p, a_vector3 const *v);
A_EXTERN int a_line3_set2(a_line3 *ctx, a_point3 const *p, a_point3 const *q);
A_EXTERN void a_line3_eval(a_line3 const *ctx, a_real val, a_point3 *res);
A_EXTERN a_real a_line3_proj(a_line3 const *ctx, a_point3 const *p, a_point3 *q);

A_EXTERN a_real a_line3_dist(a_line3 const *ctx, a_point3 const *p);
A_EXTERN a_real a_line3_dist1(a_line3 const *ctx, a_point3 const *p);
A_EXTERN a_real a_line3_dist2(a_line3 const *ctx, a_point3 const *p);

#if !defined A_HAVE_INLINE || defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#undef max
/*!
 @brief instance structure for three-dimensional line
*/
struct a_line3
{
    a_point3 orig;
    a_vector3 dir;
    a_real max;
#if defined(__cplusplus)
    A_INLINE a_real len() const { return max; }
    A_INLINE void org(a_point3 &res) const { a_line3_org(this, &res); }
    A_INLINE void tgt(a_point3 &res) const { a_line3_tgt(this, &res); }
    A_INLINE int set(a_point3 const &p, a_vector3 const &v)
    {
        return a_line3_set1(this, &p, &v);
    }
    A_INLINE int set(a_point3 const &p, a_point3 const &q)
    {
        return a_line3_set2(this, &p, &q);
    }
    A_INLINE void eval(a_real val, a_point3 &res) const
    {
        a_line3_eval(this, val, &res);
    }
    A_INLINE a_real proj(a_point3 const &p, a_point3 &q) const
    {
        return a_line3_proj(this, &p, &q);
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
A_INTERN void a_line3_org(a_line3 const *ctx, a_point3 *res)
{
    *res = ctx->orig;
}
A_INTERN void a_line3_tgt(a_line3 const *ctx, a_point3 *res)
{
    a_line3_eval(ctx, ctx->max, res);
}
A_INTERN void a_line3_dir(a_line3 const *ctx, a_vector3 *res)
{
    *res = ctx->dir;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_LINE3_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_LINE3_C */

/*! @} a_line3 */

#endif /* a/line3.h */
