#include "a/fuzzy.h"
#include "a/real.h"

a_real_t a_fuzzy_or(a_uint_t const e, a_real_t const l, a_real_t const r)
{
    switch (e)
    {
    case A_FUZZY_ALGEBRA:
        return l + r - l * r;
    case A_FUZZY_BOUNDED:
        return a_real_min(1, l + r);
    case A_FUZZY_DEFAULT:
    default:
        return a_real_max(l, r);
    }
}

a_real_t a_fuzzy_and(a_uint_t const e, a_real_t const l, a_real_t const r)
{
    switch (e)
    {
    case A_FUZZY_ALGEBRA:
        return l * r;
    case A_FUZZY_BOUNDED:
        return a_real_max(0, l + r - 1);
    case A_FUZZY_DEFAULT:
    default:
        return a_real_min(l, r);
    }
}

a_real_t a_fuzzy_equ(a_real_t const gamma, a_real_t const l, a_real_t const r)
{
    return a_real_pow(l * r, 1 - gamma) * a_real_pow(1 - (1 - l) * (1 - r), gamma);
}
