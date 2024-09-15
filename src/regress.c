#include "a/regress.h"

void a_regress_odm_(a_float *odm, a_float const *p, a_size n, a_float p_mean)
{
    for (; n; --n) { *odm++ = *p++ - p_mean; }
}

a_float a_regress_odm(a_float *odm, a_float const *p, a_size n)
{
    a_float m = a_float_mean(p, n);
    a_regress_odm_(odm, p, n, m);
    return m;
}
