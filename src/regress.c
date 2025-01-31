#include "a/regress.h"
#include "a/math.h"

void a_regress_odm_(a_size n, a_real const *p, a_real *odm, a_real p_mean)
{
    for (; n; --n) { *odm++ = *p++ - p_mean; }
}

a_real a_regress_odm(a_size n, a_real const *p, a_real *odm)
{
    a_real m = a_real_mean(p, n);
    a_regress_odm_(n, p, odm, m);
    return m;
}
