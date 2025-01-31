#define LIBA_FUZZY_C
#include "a/fuzzy.h"
#include "a/math.h"

a_real a_fuzzy_equ(a_real a, a_real b)
{
    return a_real_sqrt(a * b) * a_real_sqrt(1 - (1 - a) * (1 - b));
}

a_real a_fuzzy_equ_(a_real gamma, a_real a, a_real b)
{
    return a_real_pow(a * b, 1 - gamma) * a_real_pow(1 - (1 - a) * (1 - b), gamma);
}
