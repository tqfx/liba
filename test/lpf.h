#define MAIN_(x) A_CAST_2(x, _lpf)
#include "test.h"
#include "a/lpf.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);
    a_lpf_s ctx = A_LPF_INIT(A_LPF_GEN(10, 0.01));
    a_lpf_init(&ctx, a_lpf_gen(10, A_FLOAT_C(0.01)));
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float_t x = A_FLOAT_PI / 10 * a_float_c(, i);
        a_float_t x1 = a_float_sin(x);
        a_float_t x2 = a_lpf_iter(&ctx, x1);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), x, x1, x2);
    }
    a_lpf_zero(&ctx);
    return 0;
}
