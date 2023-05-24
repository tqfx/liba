#include "a/fuzzy.h"
#include "a/math.h"

a_float_t a_fuzzy_or(unsigned int const e, a_float_t const l, a_float_t const r)
{
    switch (e)
    {
    case A_FUZZY_ALGEBRA:
        return l + r - l * r;
    case A_FUZZY_BOUNDED:
        return a_float_min(1, l + r);
    case A_FUZZY_DEFAULT:
    default:
        return a_float_max(l, r);
    }
}

a_float_t a_fuzzy_and(unsigned int const e, a_float_t const l, a_float_t const r)
{
    switch (e)
    {
    case A_FUZZY_ALGEBRA:
        return l * r;
    case A_FUZZY_BOUNDED:
        return a_float_max(0, l + r - 1);
    case A_FUZZY_DEFAULT:
    default:
        return a_float_min(l, r);
    }
}

a_float_t a_fuzzy_equ(a_float_t const gamma, a_float_t const l, a_float_t const r)
{
    return a_float_pow(l * r, 1 - gamma) * a_float_pow(1 - (1 - l) * (1 - r), gamma);
}
