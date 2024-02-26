#define LIBA_FUZZY_C
#include "a/fuzzy.h"
#include "a/math.h"

a_float a_fuzzy_equ(a_float a, a_float b)
{
    return a_float_sqrt(a * b) * a_float_sqrt(1 - (1 - a) * (1 - b));
}

a_float a_fuzzy_equ_(a_float gamma, a_float a, a_float b)
{
    return a_float_pow(a * b, 1 - gamma) * a_float_pow(1 - (1 - a) * (1 - b), gamma);
}
