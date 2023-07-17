#ifndef TEST_PID_H
#define TEST_PID_H
#define MAIN_(s, argc, argv) A_CASE_2(pid, s)(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/pid.h"
#include "a/math.h"

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input[a_count_of(num)];
    a_float_t output[a_count_of(den)];
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, input, a_count_of(den), den, output);
    a_pid_s ctx;
    ctx.kp = A_FLOAT_C(10.0);
    ctx.ki = A_FLOAT_C(0.01);
    ctx.kd = A_FLOAT_C(0.1);
    ctx.summax = +10;
    ctx.outmax = +10;
    ctx.outmin = -10;
    ctx.mode = A_PID_OFF;
    a_pid_init(&ctx, 0);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.output));
    }
    ctx.mode = A_PID_POS;
    for (unsigned int i = 0; i < 1000; ++i)
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.output));
    }
    ctx.mode = A_PID_INC;
    for (unsigned int i = 0; i < 1000; ++i)
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.output));
    }
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
    a_pid_s ctx;
    ctx.kp = A_FLOAT_C(10.0);
    ctx.ki = A_FLOAT_C(0.01);
    ctx.kd = A_FLOAT_C(0.1);
    ctx.summax = +10;
    ctx.outmax = +10;
    ctx.outmin = -10;
    ctx.mode = A_PID_OFF;
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        a_pid_chan(&ctx, 3, out, fdb, tmp, err);
    }
    a_float_t set[3] = {1, 1, 1};
    for (unsigned int n = 0; n < 1000; ++n)
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].output;
        }
        a_float_t const *const out = a_pid_outp(&ctx, set, fdb);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, out[i]);
        }
    }
    ctx.mode = A_PID_POS;
    for (unsigned int n = 0; n < 1000; ++n)
    {
        a_float_t buf[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            buf[i] = *tf[i].output;
        }
        a_float_t const *const ptr = a_pid_outp(&ctx, set, buf);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, ptr[i]);
        }
    }
    ctx.mode = A_PID_INC;
    for (unsigned int n = 0; n < 1000; ++n)
    {
        a_float_t buf[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            buf[i] = *tf[i].output;
        }
        a_float_t const *const ptr = a_pid_outp(&ctx, set, buf);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, ptr[i]);
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

    a_tf_s pos_tf;
    a_float_t pos_input[a_count_of(num)];
    a_float_t pos_output[a_count_of(den)];
    a_tf_init(&pos_tf, a_count_of(num), num, pos_input, a_count_of(den), den, pos_output);
    a_tf_s inc_tf;
    a_float_t inc_input[a_count_of(num)];
    a_float_t inc_output[a_count_of(den)];
    a_tf_init(&inc_tf, a_count_of(num), num, inc_input, a_count_of(den), den, inc_output);

    a_pid_s pos_pid;
    pos_pid.kp = A_FLOAT_C(100.0);
    pos_pid.ki = A_FLOAT_C(0.01);
    pos_pid.kd = A_FLOAT_C(1200.0);
    pos_pid.summax = +A_FLOAT_MAX;
    pos_pid.outmax = +A_FLOAT_MAX;
    pos_pid.outmin = -A_FLOAT_MAX;
    pos_pid.mode = A_PID_POS;
    a_pid_init(&pos_pid, 0);
    a_pid_s inc_pid;
    inc_pid.kp = A_FLOAT_C(100.0);
    inc_pid.ki = A_FLOAT_C(0.01);
    inc_pid.kd = A_FLOAT_C(1200.0);
    inc_pid.outmax = +A_FLOAT_MAX;
    inc_pid.outmin = -A_FLOAT_MAX;
    inc_pid.mode = A_PID_INC;
    a_pid_init(&pos_pid, 0);
    for (unsigned int i = 0; i < 100; ++i)
    {
        a_float_t const in = input(A_FLOAT_C(0.001) * a_float_c(, i));
        a_tf_iter(&pos_tf, *a_pid_iter(&pos_pid, &in, pos_tf.output));
        a_tf_iter(&inc_tf, *a_pid_iter(&inc_pid, &in, inc_tf.output));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.001) * a_float_c(, i), in, *pos_tf.output, *inc_tf.output);
#endif /* MAIN_ONCE */
    }

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

#endif /* test/pid.h */
