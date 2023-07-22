#ifndef TEST_PID_NEURON_H
#define TEST_PID_NEURON_H
#define MAIN_(s, argc, argv) A_CAST_2(pid_neuron, s)(argc, argv)
#include "../test.h"
#include "a/tf.h"
#include "a/math.h"
#include "a/pid/neuron.h"

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input[a_count_of(num)];
    a_float_t output[a_count_of(den)];
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, input, a_count_of(den), den, output);
    a_pid_neuron_s ctx;
    ctx.pid.kp = A_FLOAT_C(0.1);
    ctx.pid.ki = A_FLOAT_C(0.1);
    ctx.pid.kd = A_FLOAT_C(0.1);
    ctx.pid.outmax = +10;
    ctx.pid.outmin = -10;
    ctx.pid.mode = A_PID_INC;
    ctx.k = A_FLOAT_C(10.0);
    ctx.wp.f = A_FLOAT_C(0.1);
    ctx.wi.f = A_FLOAT_C(0.1);
    ctx.wd.f = A_FLOAT_C(0.1);
    a_pid_neuron_init(&ctx, 0);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        a_tf_iter(&tf, a_pid_neuron_outf(&ctx, 1, output[0]));
    }
    a_pid_neuron_zero(&ctx);
    a_tf_zero(&tf);
}

static void test_p(void)
{
    a_float_t num0[] = {A_FLOAT_C(5.59492796e-05), A_FLOAT_C(5.54019884e-05)};
    a_float_t den0[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num1[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den1[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num2[] = {A_FLOAT_C(7.59492796e-05), A_FLOAT_C(7.54019884e-05)};
    a_float_t den2[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input0[a_count_of(num0)];
    a_float_t output0[a_count_of(den0)];
    a_float_t input1[a_count_of(num1)];
    a_float_t output1[a_count_of(den1)];
    a_float_t input2[a_count_of(num2)];
    a_float_t output2[a_count_of(den2)];
    a_tf_s tf[3];
    a_tf_init(tf + 0, a_count_of(num0), num0, input0, a_count_of(den0), den0, output0);
    a_tf_init(tf + 1, a_count_of(num1), num1, input1, a_count_of(den1), den1, output1);
    a_tf_init(tf + 2, a_count_of(num2), num2, input2, a_count_of(den2), den2, output2);
    a_pid_neuron_s ctx;
    ctx.pid.kp = A_FLOAT_C(0.1);
    ctx.pid.ki = A_FLOAT_C(0.1);
    ctx.pid.kd = A_FLOAT_C(0.1);
    ctx.pid.outmax = +10;
    ctx.pid.outmin = -10;
    ctx.pid.mode = A_PID_INC;
    ctx.k = A_FLOAT_C(10.0);
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        static a_float_t ec[3];
        static a_float_t wp[3] = {A_FLOAT_C(0.1), A_FLOAT_C(0.1), A_FLOAT_C(0.1)};
        static a_float_t wi[3] = {A_FLOAT_C(0.1), A_FLOAT_C(0.1), A_FLOAT_C(0.1)};
        static a_float_t wd[3] = {A_FLOAT_C(0.1), A_FLOAT_C(0.1), A_FLOAT_C(0.1)};
        a_pid_neuron_chan(&ctx, 3, out, fdb, tmp, err, ec, wp, wi, wd);
    }
    a_float_t set[3] = {1, 1, 1};
    for (unsigned int n = 0; n < 1000; ++n)
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].output;
        }
        a_float_t const *const out = a_pid_neuron_outp(&ctx, set, fdb);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, out[i]);
        }
    }
}

static A_INLINE a_float_t input(a_float_t const x)
{
#if 0
    return a_float_sin(4 * A_FLOAT_PI * x);
#else
    return (void)x, 1;
#endif
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(MAIN_ONCE)
    FILE *log = A_NULL;
    if (argc > 1)
    {
        log = freopen(argv[1], "wb", stdout);
    }
#else /* !MAIN_ONCE */
    (void)(argc);
    (void)(argv);
#endif /* MAIN_ONCE */
    test_f();
    test_p();

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf_s tf;
    a_float_t tf_input[a_count_of(num)];
    a_float_t tf_output[a_count_of(den)];
    a_tf_init(&tf, a_count_of(num), num, tf_input, a_count_of(den), den, tf_output);

    a_pid_neuron_s ctx;
    ctx.pid.kp = A_FLOAT_C(4.0);
    ctx.pid.ki = A_FLOAT_C(0.04);
    ctx.pid.kd = A_FLOAT_C(1.0);
    ctx.pid.outmax = +A_FLOAT_MAX;
    ctx.pid.outmin = -A_FLOAT_MAX;
    ctx.pid.mode = A_PID_INC;
    ctx.k = A_FLOAT_C(4000.0);
    ctx.wp.f = A_FLOAT_C(0.1);
    ctx.wi.f = A_FLOAT_C(0.1);
    ctx.wd.f = A_FLOAT_C(0.1);
    a_pid_neuron_init(&ctx, 0);
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float_t const in = input(A_FLOAT_C(0.001) * a_float_c(, i));
        a_tf_iter(&tf, *a_pid_neuron_iter(&ctx, &in, tf.output));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.001) * a_float_c(, i), in, *tf.output, ctx.pid.err.f);
#endif /* MAIN_ONCE */
    }
    a_pid_neuron_zero(&ctx);
    a_tf_zero(&tf);

#if defined(MAIN_ONCE)
    if (log)
    {
        if (fclose(log))
        {
            perror(A_FUNC);
        }
    }
#endif /* MAIN_ONCE */

    return 0;
}

#endif /* test/pid/neuron.h */
