#include "a/math.h"
#include "a/mf.h"

a_float a_mf_gauss(a_float x, a_float sigma, a_float c)
{
    return a_float_exp(a_float_pow((x - c) / sigma, 2) / -2);
}

a_float a_mf_gauss2(a_float x, a_float sigma1, a_float c1, a_float sigma2, a_float c2)
{
    if (x < c1)
    {
        x = a_mf_gauss(x, sigma1, c1);
    }
    else if (x > c2)
    {
        x = a_mf_gauss(x, sigma2, c2);
    }
    else // c1 <= x <= c2
    {
        x = 1;
    }
    return x;
}

a_float a_mf_gbell(a_float x, a_float a, a_float b, a_float c)
{
    return 1 / (a_float_pow(a_float_abs((x - c) / a), 2 * b) + 1);
}

a_float a_mf_sig(a_float x, a_float a, a_float c)
{
    return 1 / (a_float_exp((c - x) * a) + 1);
}

a_float a_mf_dsig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2)
{
    return a_mf_sig(x, a1, c1) - a_mf_sig(x, a2, c2);
}

a_float a_mf_psig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2)
{
    return a_mf_sig(x, a1, c1) * a_mf_sig(x, a2, c2);
}

a_float a_mf_trap(a_float x, a_float a, a_float b, a_float c, a_float d)
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

a_float a_mf_tri(a_float x, a_float a, a_float b, a_float c)
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

a_float a_mf_lins(a_float x, a_float a, a_float b)
{
    if (x < a)
    {
        x = 0;
    }
    else if (x > b)
    {
        x = 1;
    }
    else // a <= x <= b
    {
        x = (x - a) / (b - a);
    }
    return x;
}

a_float a_mf_linz(a_float x, a_float a, a_float b)
{
    if (x < a)
    {
        x = 1;
    }
    else if (x > b)
    {
        x = 0;
    }
    else // a <= x <= b
    {
        x = (b - x) / (b - a);
    }
    return x;
}

a_float a_mf_s(a_float x, a_float a, a_float b)
{
    if (x > (a + b) / 2)
    {
        if (x < b)
        {
            x = 1 - 2 * a_float_pow((b - x) / (b - a), 2);
        }
        else // x >= b
        {
            x = 1;
        }
    }
    else // x <= (a+b)/2
    {
        if (x > a)
        {
            x = 2 * a_float_pow((x - a) / (b - a), 2);
        }
        else // x <= a
        {
            x = 0;
        }
    }
    return x;
}

a_float a_mf_z(a_float x, a_float a, a_float b)
{
    if (x < (a + b) / 2)
    {
        if (x > a)
        {
            x = 1 - 2 * a_float_pow((x - a) / (b - a), 2);
        }
        else // x <= a
        {
            x = 1;
        }
    }
    else // x >= (a+b)/2
    {
        if (x < b)
        {
            x = 2 * a_float_pow((b - x) / (b - a), 2);
        }
        else // x >= b
        {
            x = 0;
        }
    }
    return x;
}

a_float a_mf_pi(a_float x, a_float a, a_float b, a_float c, a_float d)
{
    if (x < b)
    {
        x = a_mf_s(x, a, b);
    }
    else if (x > c)
    {
        x = a_mf_z(x, c, d);
    }
    else
    {
        x = 1;
    }
    return x;
}

a_float a_mf(unsigned int e, a_float x, a_float const *a)
{
    switch (e)
    {
    case A_MF_PI:
        return a_mf_pi(x, a[0], a[1], a[2], a[3]);
    case A_MF_Z:
        return a_mf_z(x, a[0], a[1]);
    case A_MF_S:
        return a_mf_s(x, a[0], a[1]);
    case A_MF_LINZ:
        return a_mf_linz(x, a[0], a[1]);
    case A_MF_LINS:
        return a_mf_lins(x, a[0], a[1]);
    case A_MF_TRI:
        return a_mf_tri(x, a[0], a[1], a[2]);
    case A_MF_TRAP:
        return a_mf_trap(x, a[0], a[1], a[2], a[3]);
    case A_MF_PSIG:
        return a_mf_psig(x, a[0], a[1], a[2], a[3]);
    case A_MF_DSIG:
        return a_mf_dsig(x, a[0], a[1], a[2], a[3]);
    case A_MF_SIG:
        return a_mf_sig(x, a[0], a[1]);
    case A_MF_GBELL:
        return a_mf_gbell(x, a[0], a[1], a[2]);
    case A_MF_GAUSS2:
        return a_mf_gauss2(x, a[0], a[1], a[2], a[3]);
    case A_MF_GAUSS:
        return a_mf_gauss(x, a[0], a[1]);
    case A_MF_NUL:
    default:
        return 0;
    }
}
