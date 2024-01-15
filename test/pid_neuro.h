#define MAIN_(x) A_CAST_2(x, _pid_neuro)
#include "test.h"
#include "a/tf.h"
#include "a/math.h"
#include "a/pid_neuro.h"

static A_INLINE a_float input(a_float const x)
{
#if 0
    return a_float_sin(4 * A_FLOAT_PI * x);
#else
    return (void)x, 1;
#endif
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);

    a_float num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf tf;
    a_float tf_input[A_LEN(num)];
    a_float tf_output[A_LEN(den)];
    a_tf_init(&tf, A_LEN(num), num, tf_input, A_LEN(den), den, tf_output);

    a_pid_neuro ctx;
    ctx.pid.kp = A_FLOAT_C(4.0);
    ctx.pid.ki = A_FLOAT_C(0.04);
    ctx.pid.kd = A_FLOAT_C(1.0);
    ctx.pid.outmax = +A_FLOAT_MAX;
    ctx.pid.outmin = -A_FLOAT_MAX;
    ctx.k = A_FLOAT_C(4000.0);
    ctx.wp = A_FLOAT_C(0.1);
    ctx.wi = A_FLOAT_C(0.1);
    ctx.wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(&ctx);
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float const in = input(A_FLOAT_C(0.001) * a_float_c(i));
        a_tf_iter(&tf, a_pid_neuro_inc(&ctx, in, *tf.output));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              A_FLOAT_C(0.001) * a_float_c(i), in, *tf.output, ctx.pid.err);
    }
    a_pid_neuro_zero(&ctx);
    a_tf_zero(&tf);

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_ASSERT_BUILD(std::is_pod<a_pid_neuro>::value);
#endif /* __cplusplus */

    return 0;
}
