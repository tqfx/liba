#define MAIN(x) pid##x
#include "test.h"
#include "a/tf.h"
#include "a/pid.h"

static A_INLINE a_float input(a_float const x)
{
#if defined(LIBA_MATH_H)
    return a_float_sin(4 * A_FLOAT_PI * x);
#else
    return (void)x, 1;
#endif
}

int main(int argc, char *argv[]) /* NOLINT(misc-definitions-in-headers) */
{
    unsigned int i;
    a_float num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf pos_tf;
    a_float pos_input[A_LEN(num)];
    a_float pos_output[A_LEN(den)];
    a_pid pos_pid;

    a_tf inc_tf;
    a_float inc_input[A_LEN(num)];
    a_float inc_output[A_LEN(den)];
    a_pid inc_pid;

    main_init(argc, argv, 1);
    a_tf_init(&pos_tf, A_LEN(num), num, pos_input, A_LEN(den), den, pos_output);
    a_tf_init(&inc_tf, A_LEN(num), num, inc_input, A_LEN(den), den, inc_output);

    pos_pid.kp = A_FLOAT_C(100.0);
    pos_pid.ki = A_FLOAT_C(0.01);
    pos_pid.kd = A_FLOAT_C(1200.0);
    pos_pid.summax = +A_FLOAT_MAX;
    pos_pid.summin = -A_FLOAT_MAX;
    pos_pid.outmax = +A_FLOAT_MAX;
    pos_pid.outmin = -A_FLOAT_MAX;
    a_pid_init(&pos_pid);

    inc_pid.kp = A_FLOAT_C(100.0);
    inc_pid.ki = A_FLOAT_C(0.01);
    inc_pid.kd = A_FLOAT_C(1200.0);
    inc_pid.outmax = +A_FLOAT_MAX;
    inc_pid.outmin = -A_FLOAT_MAX;
    a_pid_init(&inc_pid);

    for (i = 0; i < 100; ++i)
    {
        a_float const ix = input(A_FLOAT_C(0.001) * a_float_c(i));
        a_tf_iter(&pos_tf, a_pid_pos(&pos_pid, ix, *pos_tf.output));
        a_tf_iter(&inc_tf, a_pid_inc(&inc_pid, ix, *inc_tf.output));
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"),
              A_FLOAT_C(0.001) * a_float_c(i), ix, *pos_tf.output, *inc_tf.output);
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_pid>::value);
#endif /* __cplusplus */

    return 0;
}
