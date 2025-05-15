/*!
 @file plane.h
 @brief three-dimensional plane
*/

#ifndef LIBA_PLANE_H
#define LIBA_PLANE_H

#include "a.h"
#include "point3.h"

/*!
 @ingroup liba
 @addtogroup a_plane three-dimensional plane
 @{
*/

/*! static cast to \ref a_plane */
#define a_plane_c(x) a_cast_s(a_plane, x)
#define a_plane_(_, x) a_cast_s(a_plane _, x)

typedef struct a_plane a_plane;

#if defined(__cplusplus)
namespace a
{
typedef struct a_plane plane;
} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if !defined A_HAVE_INLINE || defined(LIBA_PLANE_C)
#undef A_INTERN
#define A_INTERN A_PUBLIC extern
#endif /* A_HAVE_INLINE */

A_INTERN a_point3 const *a_plane_org(a_plane const *ctx);
A_INTERN a_vector3 const *a_plane_dir(a_plane const *ctx);
A_INTERN a_vector3 const *a_plane_u(a_plane const *ctx);
A_INTERN a_vector3 const *a_plane_v(a_plane const *ctx);
A_INTERN void a_plane_set_org(a_plane *ctx, a_real x, a_real y, a_real z);

A_EXTERN int a_plane_set_dir(a_plane *ctx, a_real x, a_real y, a_real z);
A_EXTERN int a_plane_set(a_plane *ctx, a_point3 const *p, a_vector3 const *v);
A_EXTERN int a_plane_set3(a_plane *ctx, a_point3 const *a, a_point3 const *b, a_point3 const *c);
A_EXTERN int a_plane_set4(a_plane *ctx, a_real a, a_real b, a_real c, a_real d);
A_EXTERN void a_plane_eval(a_plane const *ctx, a_real u, a_real v, a_point3 *res);
A_EXTERN void a_plane_parm(a_plane const *ctx, a_point3 const *p, a_real *u, a_real *v);
A_EXTERN a_real a_plane_proj(a_plane const *ctx, a_point3 const *p, a_point3 *res);

A_EXTERN a_real a_plane_sdist(a_plane const *ctx, a_point3 const *p);
A_EXTERN a_real a_plane_dist(a_plane const *ctx, a_point3 const *p);

#if !defined A_HAVE_INLINE || defined(LIBA_PLANE_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* A_HAVE_INLINE */
#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief instance structure for three-dimensional plane
*/
struct a_plane
{
    a_point3 orig;
    a_vector3 dir_, u_, v_;
#if defined(__cplusplus)
    A_INLINE a_point3 const &org() const { return orig; }
    A_INLINE void set_org(a_real x, a_real y, a_real z)
    {
        a_plane_set_org(this, x, y, z);
    }
    A_INLINE a_vector3 const &dir() const { return dir_; }
    A_INLINE int set_dir(a_real x, a_real y, a_real z)
    {
        return a_plane_set_dir(this, x, y, z);
    }
    A_INLINE a_vector3 const &u() const { return u_; }
    A_INLINE a_vector3 const &v() const { return v_; }
    A_INLINE int set(a_point3 const &p, a_vector3 const &v)
    {
        return a_plane_set(this, &p, &v);
    }
    A_INLINE int set(a_point3 const &a, a_point3 const &b, a_point3 const &c)
    {
        return a_plane_set3(this, &a, &b, &c);
    }
    A_INLINE void eval(a_real u, a_real v, a_point3 &res) const
    {
        a_plane_eval(this, u, v, &res);
    }
    A_INLINE void parm(a_point3 const &p, a_real &u, a_real &v) const
    {
        a_plane_parm(this, &p, &u, &v);
    }
    A_INLINE a_real proj(a_point3 const &p, a_point3 &res) const
    {
        return a_plane_proj(this, &p, &res);
    }
    A_INLINE a_real sdist(a_point3 const &p) const
    {
        return a_plane_sdist(this, &p);
    }
    A_INLINE a_real dist(a_point3 const &p) const
    {
        return a_plane_dist(this, &p);
    }
#endif /* __cplusplus */
};

#if defined(LIBA_PLANE_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_PLANE_C */
#if defined(A_HAVE_INLINE) || defined(LIBA_PLANE_C)

A_INTERN a_point3 const *a_plane_org(a_plane const *ctx)
{
    return &ctx->orig;
}
A_INTERN a_vector3 const *a_plane_dir(a_plane const *ctx)
{
    return &ctx->dir_;
}
A_INTERN a_vector3 const *a_plane_u(a_plane const *ctx)
{
    return &ctx->u_;
}
A_INTERN a_vector3 const *a_plane_v(a_plane const *ctx)
{
    return &ctx->v_;
}
A_INTERN void a_plane_set_org(a_plane *ctx, a_real x, a_real y, a_real z)
{
    ctx->orig.x = x;
    ctx->orig.y = y;
    ctx->orig.z = z;
}

#endif /* A_HAVE_INLINE */
#if defined(LIBA_PLANE_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_PLANE_C */

/*! @} a_plane */

#endif /* a/plane.h */
