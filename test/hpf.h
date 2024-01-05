#define MAIN_(x) A_CAST_2(x, _hpf)
#include "test.h"
#include "a/hpf.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);
    a_hpf_s ctx = A_HPF_INIT(A_HPF_GEN(10, 0.01));
    a_hpf_init(&ctx, a_hpf_gen(10, A_FLOAT_C(0.01)));
    a_float_t Ts = A_FLOAT_C(1.0);
    a_float_t f_0 = A_FLOAT_C(1.0);
    a_float_t f_e = A_FLOAT_C(1000.0);
    a_float_t c = (f_e - f_0) / Ts;
    a_float_t T = A_FLOAT_C(1.0) / 10000;
    for (a_float_t x = 0; x < Ts; x += T) // NOLINT
    {
        a_float_t x1 = a_float_cos(2 * A_FLOAT_PI * (f_0 * x + A_FLOAT_C(0.5) * c * x * x) + 0);
        a_float_t x2 = a_hpf_iter(&ctx, x1);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), x, x1, x2);
    }
    a_hpf_zero(&ctx);
    return 0;
}
