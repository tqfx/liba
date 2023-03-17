#include "a/real.h"
#include "a/mf.h"

a_real_t a_mf_gauss(a_real_t const x, a_real_t const sigma, a_real_t const c)
{
    return a_real_exp(a_real_pow((x - c) / sigma, 2) / -2);
}

a_real_t a_mf_gbell(a_real_t const x, a_real_t const a, a_real_t const b, a_real_t const c)
{
    return 1 / (a_real_pow(a_real_abs((x - c) / a), 2 * b) + 1);
}

a_real_t a_mf_sig(a_real_t const x, a_real_t const a, a_real_t const c)
{
    return 1 / (a_real_exp((c - x) * a) + 1);
}

a_real_t a_mf_trap(a_real_t x, a_real_t const a, a_real_t const b, a_real_t const c, a_real_t const d)
{
    if (x < b)
    {
        if (x > a) // a < x <= b
        {
            x = (x - a) / (b - a);
        }
        else // x <= a
        {
            x = 0;
        }
    }
    else if (x > c)
    {
        if (x < d) // c <= x < d
        {
            x = (d - x) / (d - c);
        }
        else // d <= x
        {
            x = 0;
        }
    }
    else // b <= x <= c
    {
        x = 1;
    }
    return x;
}

a_real_t a_mf_tri(a_real_t x, a_real_t const a, a_real_t const b, a_real_t const c)
{
    if (x < b)
    {
        if (x > a) // a < x <= b
        {
            x = (x - a) / (b - a);
        }
        else // x <= a
        {
            x = 0;
        }
    }
    else
    {
        if (x < c) // b <= x < c
        {
            x = (c - x) / (c - b);
        }
        else // c <= x
        {
            x = 0;
        }
    }
    return x;
}

a_real_t a_mf_z(a_real_t x, a_real_t const a, a_real_t const b)
{
    if (x < a)
    {
        x = 1;
    }
    else if (x < (a + b) / 2)
    {
        x = 1 - 2 * a_real_pow((x - a) / (b - a), 2);
    }
    else if (x < b)
    {
        x = 2 * a_real_pow((x - b) / (b - a), 2);
    }
    else
    {
        x = 0;
    }
    return x;
}

a_real_t a_mf(a_uint_t const e, a_real_t const x, a_real_t const *const a)
{
    switch (e)
    {
    case A_MF_GAUSS:
        return a_mf_gauss(x, a[0], a[1]);
    case A_MF_GBELL:
        return a_mf_gbell(x, a[0], a[1], a[2]);
    case A_MF_SIG:
        return a_mf_sig(x, a[0], a[1]);
    case A_MF_TRAP:
        return a_mf_trap(x, a[0], a[1], a[2], a[3]);
    case A_MF_TRI:
        return a_mf_tri(x, a[0], a[1], a[2]);
    case A_MF_Z:
        return a_mf_z(x, a[0], a[1]);
    case A_MF_NUL:
    default:
        return 0;
    }
}
