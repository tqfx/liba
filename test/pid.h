#ifndef TEST_PID_H
#define TEST_PID_H
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */
#define MAIN_(s, argc, argv) pid##s(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/pid.h"
#include "a/math.h"

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t u[a_count_of(num)];
    a_float_t v[a_count_of(den)];
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, u, a_count_of(den), den, v);
    a_pid_s ctx;
    a_pid_init(&ctx, A_FLOAT_C(0.01), -10, +10);
    a_pid_kpid(&ctx, 10, A_FLOAT_C(0.01), A_FLOAT_C(0.1));
    a_pid_set_dt(a_pid_off(a_pid_inc(a_pid_pos(&ctx, 10))), A_FLOAT_C(0.001));
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.v));
    }
    a_pid_set_reg(&ctx, A_PID_POS);
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.v));
    }
    a_pid_set_reg(&ctx, A_PID_INC);
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_tf_iter(&tf, a_pid_outf(&ctx, 1, *tf.v));
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
    a_float_t u0[a_count_of(num0)];
    a_float_t v0[a_count_of(den0)];
    a_float_t u1[a_count_of(num1)];
    a_float_t v1[a_count_of(den1)];
    a_float_t u2[a_count_of(num2)];
    a_float_t v2[a_count_of(den2)];
    a_tf_s tf[3];
    a_tf_init(tf + 0, a_count_of(num0), num0, u0, a_count_of(den0), den0, v0);
    a_tf_init(tf + 1, a_count_of(num1), num1, u1, a_count_of(den1), den1, v1);
    a_tf_init(tf + 2, a_count_of(num2), num2, u2, a_count_of(den2), den2, v2);
    a_pid_s ctx;
    a_pid_init(&ctx, A_FLOAT_C(0.01), -10, +10);
    a_pid_kpid(&ctx, 10, A_FLOAT_C(0.01), A_FLOAT_C(0.1));
    a_pid_set_dt(a_pid_off(a_pid_inc(a_pid_pos(&ctx, 10))), A_FLOAT_C(0.001));
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        a_pid_chan(&ctx, 3, out, fdb, tmp, err);
    }
    a_float_t set[3] = {1, 1, 1};
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].v;
        }
        a_float_t const *const out = a_pid_outp(&ctx, set, fdb);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, out[i]);
        }
    }
    a_pid_set_reg(&ctx, A_PID_POS);
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_float_t buf[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            buf[i] = *tf[i].v;
        }
        a_float_t const *const ptr = a_pid_outp(&ctx, set, buf);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, ptr[i]);
        }
    }
    a_pid_set_reg(&ctx, A_PID_INC);
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_float_t buf[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            buf[i] = *tf[i].v;
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
    a_float_t pos_u[a_count_of(num)];
    a_float_t pos_v[a_count_of(den)];
    a_tf_init(&pos_tf, a_count_of(num), num, pos_u, a_count_of(den), den, pos_v);
    a_tf_s inc_tf;
    a_float_t inc_u[a_count_of(num)];
    a_float_t inc_v[a_count_of(den)];
    a_tf_init(&inc_tf, a_count_of(num), num, inc_u, a_count_of(den), den, inc_v);

    a_pid_s pos_pid;
    a_pid_s inc_pid;
    a_pid_pos(a_pid_init(&pos_pid, A_FLOAT_C(0.001), -10, +10), 10);
    a_pid_inc(a_pid_init(&inc_pid, A_FLOAT_C(0.001), -10, +10));
    a_pid_kpid(&pos_pid, 10, A_FLOAT_C(0.01), A_FLOAT_C(0.1));
    a_pid_kpid(&inc_pid, 10, A_FLOAT_C(0.1), A_FLOAT_C(0.09));
    for (a_float_t t = 0; t < A_FLOAT_C(0.5); t += A_FLOAT_C(0.001))
    {
        a_float_t in = input(t);
        a_tf_iter(&pos_tf, a_pid_outf(&pos_pid, in, *pos_tf.v));
        a_tf_iter(&inc_tf, a_pid_outf(&inc_pid, in, *inc_tf.v));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), t, in, *pos_tf.v, *inc_tf.v);
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

#endif /* pid.h */
