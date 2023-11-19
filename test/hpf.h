#define MAIN_(x) A_CAST_2(x, _hpf)
#include "test.h"
#include "a/hpf.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);
    a_hpf_s ctx = A_HPF_INIT(A_HPF_GEN(10, 0.01));
    a_hpf_init(&ctx, a_hpf_gen(10, A_FLOAT_C(0.01)));
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float_t x = A_FLOAT_PI / 10 * a_float_c(, i);
        a_float_t x1 = a_float_sin(x);
        a_float_t x2 = a_hpf_iter(&ctx, x1);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), x, x1, x2);
    }
    a_hpf_zero(&ctx);
    return 0;
}
