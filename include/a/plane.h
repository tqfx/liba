/*!
 @file plane.h
 @brief three-dimensional plane
*/

#ifndef LIBA_PLANE_H
#define LIBA_PLANE_H

#include "a.h"
#include "line3.h"

/*!
 @ingroup liba
 @addtogroup a_plane three-dimensional plane
 @{
*/

/*! static cast to @ref a_plane */
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
A_EXPORT int a_plane_set_uv(a_plane *ctx, a_vector3 const *u, a_vector3 const *v);
A_EXPORT int a_plane_set_u(a_plane *ctx, a_vector3 const *n, a_vector3 const *u);
A_EXPORT int a_plane_set_v(a_plane *ctx, a_vector3 const *n, a_vector3 const *v);
A_EXTERN int a_plane_set(a_plane *ctx, a_point3 const *p, a_vector3 const *n);
A_EXTERN int a_plane_set3(a_plane *ctx, a_point3 const *p1, a_point3 const *p2, a_point3 const *p3);
A_EXTERN int a_plane_set4(a_plane *ctx, a_real a, a_real b, a_real c, a_real d);
A_EXTERN void a_plane_eval(a_plane const *ctx, a_real u, a_real v, a_point3 *res);
A_EXTERN void a_plane_parm(a_plane const *ctx, a_point3 const *p, a_real *u, a_real *v);
A_EXTERN a_real a_plane_proj(a_plane const *ctx, a_point3 const *p, a_point3 *res);

A_EXTERN a_real a_plane_sdist(a_plane const *ctx, a_point3 const *rhs);
A_EXTERN a_real a_plane_dist(a_plane const *ctx, a_point3 const *rhs);

A_EXTERN int a_plane_int0(a_plane const *ctx, a_point3 const *rhs, a_real *u, a_real *v);
A_EXTERN int a_plane_int1(a_plane const *ctx, a_line3 const *rhs, a_real min, a_real max, a_real *w);
A_EXTERN int a_plane_int2(a_plane const *ctx, a_plane const *rhs, a_line3 *res);

A_EXTERN void a_plane_rot2d(a_plane *ctx, a_real angle);

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
    A_INLINE int set_uv(a_vector3 const &u, a_vector3 const &v)
    {
        return a_plane_set_uv(this, &u, &v);
    }
    A_INLINE int set_u(a_vector3 const &n, a_vector3 const &u)
    {
        return a_plane_set_u(this, &n, &u);
    }
    A_INLINE int set_v(a_vector3 const &n, a_vector3 const &v)
    {
        return a_plane_set_v(this, &n, &v);
    }
    A_INLINE a_vector3 const &u() const { return u_; }
    A_INLINE a_vector3 const &v() const { return v_; }
    A_INLINE int set(a_point3 const &p, a_vector3 const &n)
    {
        return a_plane_set(this, &p, &n);
    }
    A_INLINE int set(a_point3 const &p1, a_point3 const &p2, a_point3 const &p3)
    {
        return a_plane_set3(this, &p1, &p2, &p3);
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
    A_INLINE a_real sdist(a_point3 const &rhs) const
    {
        return a_plane_sdist(this, &rhs);
    }
    A_INLINE a_real dist(a_point3 const &rhs) const
    {
        return a_plane_dist(this, &rhs);
    }
    A_INLINE int int0(a_point3 const &rhs, a_real &u, a_real &v) const
    {
        return a_plane_int0(this, &rhs, &u, &v);
    }
    A_INLINE int int1(a_line3 const &rhs, a_real min, a_real max, a_real &w) const
    {
        return a_plane_int1(this, &rhs, min, max, &w);
    }
    A_INLINE int int2(a_plane const &rhs, a_line3 &res) const
    {
        return a_plane_int2(this, &rhs, &res);
    }
    A_INLINE void rot2d(a_real angle)
    {
        a_plane_rot2d(this, angle);
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
