#include "a/regress.h"

void a_regress_odm_(a_size n, a_float const *p, a_float *odm, a_float p_mean)
{
    for (; n; --n) { *odm++ = *p++ - p_mean; }
}

a_float a_regress_odm(a_size n, a_float const *p, a_float *odm)
{
    a_float m = a_float_mean(p, n);
    a_regress_odm_(n, p, odm, m);
    return m;
}
