#include "a/convexhull.h"
#include <stdlib.h>

#if A_PREREQ_GNUC(8, 0) || __has_warning("-Wcast-function-type")
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif /* -Wfloat-equal */

a_size a_convexhull2(a_point2 *i_p, a_size i_n, a_point2 *o_p, a_size o_n, a_uint opt, a_real tol)
{
    a_real x;
    a_size b, i, r = 0;
    a_vector2 v21, v10;
    switch (opt & 0x7F)
    {
    case 'x':
    case 'X': qsort(i_p, i_n, sizeof(*i_p), (int (*)(void const *, void const *))a_point2_cmpx); break;
    case 'y':
    case 'Y': qsort(i_p, i_n, sizeof(*i_p), (int (*)(void const *, void const *))a_point2_cmpy); break;
    default: break;
    }
    if (tol < 0) { tol = 0; }
    for (i = 0; i < i_n; ++i)
    {
        a_point2 const *p_0 = i_p + i;
        for (; r > 1; --r)
        {
            a_point2 const *p_2 = o_p + r - 2;
            a_point2 const *p_1 = o_p + r - 1;
            a_vector2_set(&v21, p_2, p_1);
            a_vector2_set(&v10, p_1, p_0);
            x = a_vector2_cross(&v21, &v10);
            if (x > tol || (x > 0 && a_vector2_dot(&v21, &v10) < 0)) { break; }
        }
        if (r < o_n) { o_p[r++] = *p_0; }
        else { return 0; }
    }
    b = r;
    for (i = i_n; i > 1; --i)
    {
        a_point2 const *p_0 = i_p + i - 2;
        for (; r > b; --r)
        {
            a_point2 const *p_2 = o_p + r - 2;
            a_point2 const *p_1 = o_p + r - 1;
            a_vector2_set(&v21, p_2, p_1);
            a_vector2_set(&v10, p_1, p_0);
            x = a_vector2_cross(&v21, &v10);
            if (x > tol || (x > 0 && a_vector2_dot(&v21, &v10) < 0)) { break; }
        }
        if (r < o_n) { o_p[r++] = *p_0; }
        else { return 0; }
    }
    if (r > 1) { --r; }
    return r;
}
