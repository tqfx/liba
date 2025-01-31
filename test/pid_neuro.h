#define MAIN(x) pid_neuro##x
#include "test.h"
#include "a/tf.h"
#include "a/pid_neuro.h"

static A_INLINE a_real input(a_real const x)
{
#if defined(LIBA_MATH_H)
    return a_real_sin(4 * A_REAL_PI * x);
#else
    return (void)x, 1;
#endif
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    unsigned int i;
    a_real num[] = {A_REAL_C(6.59492796e-05), A_REAL_C(6.54019884e-05)};
    a_real den[] = {A_REAL_C(-1.97530991), A_REAL_C(0.97530991)};

    a_tf tf;
    a_real tf_input[A_LEN(num)];
    a_real tf_output[A_LEN(den)];
    a_pid_neuro ctx;

    main_init(argc, argv, 1);
    a_tf_init(&tf, A_LEN(num), num, tf_input, A_LEN(den), den, tf_output);

    ctx.pid.kp = A_REAL_C(4.0);
    ctx.pid.ki = A_REAL_C(0.04);
    ctx.pid.kd = A_REAL_C(1.0);
    ctx.pid.outmax = +A_REAL_MAX;
    ctx.pid.outmin = -A_REAL_MAX;
    ctx.k = A_REAL_C(4000.0);
    ctx.wp = A_REAL_C(0.1);
    ctx.wi = A_REAL_C(0.1);
    ctx.wd = A_REAL_C(0.1);
    a_pid_neuro_init(&ctx);
    for (i = 0; i < 100; ++i)
    {
        a_real const ix = input(A_REAL_C(0.001) * a_real_c(i));
        a_tf_iter(&tf, a_pid_neuro_inc(&ctx, ix, *tf.output));
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              A_REAL_C(0.001) * a_real_c(i), ix, *tf.output, ctx.pid.err);
    }
    a_pid_neuro_zero(&ctx);
    a_tf_zero(&tf);

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_pid_neuro>::value);
#endif /* __cplusplus */

    return 0;
}
