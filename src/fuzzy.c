#define LIBA_FUZZY_C
#include "a/fuzzy.h"
#include "a/math.h"

a_float_t a_fuzzy_equ(a_float_t const gamma, a_float_t const a, a_float_t const b)
{
    return a_float_pow(a * b, 1 - gamma) * a_float_pow(1 - (1 - a) * (1 - b), gamma);
}
