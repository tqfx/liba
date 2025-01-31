#define MAIN(x) hpf##x
#include "test.h"
#include "a/hpf.h"

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    a_hpf ctx = A_HPF_1(A_HPF_GEN(10, 0.01));
    a_real x, Ts = A_REAL_C(1.0);
    a_real f_0 = A_REAL_C(1.0);
    a_real f_e = A_REAL_C(1000.0);
    a_real c = (f_e - f_0) / Ts;
    a_real T = A_REAL_C(1.0) / 10000;
    main_init(argc, argv, 1);
    a_hpf_init(&ctx, a_hpf_gen(10, A_REAL_C(0.01)));
    for (x = 0; x < Ts; x += T) /* NOLINT */
    {
        a_real x1 = a_real_cos(A_REAL_TAU * (f_0 * x + A_REAL_C(0.5) * c * x * x) + 0);
        a_real x2 = a_hpf_iter(&ctx, x1);
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n", x, x1, x2);
    }
    a_hpf_zero(&ctx);
#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_hpf>::value);
#endif /* __cplusplus */
    return 0;
}
