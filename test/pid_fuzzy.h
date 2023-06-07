#ifndef TEST_PID_FUZZY_H
#define TEST_PID_FUZZY_H
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */
#define MAIN_(s, argc, argv) pid_fuzzy##s(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/pid_fuzzy.h"

#undef NB
#undef NM
#undef NS
#undef ZO
#undef PS
#undef PM
#undef PB
#define NB -3 * S
#define NM -2 * S
#define NS -1 * S
#define ZO +0 * S
#define PS +1 * S
#define PM +2 * S
#define PB +3 * S

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

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num1[] = {A_FLOAT_C(5.59492796e-05), A_FLOAT_C(5.54019884e-05)};
    a_float_t den1[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num2[] = {A_FLOAT_C(7.59492796e-05), A_FLOAT_C(7.54019884e-05)};
    a_float_t den2[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t u[a_count_of(num)] = {0};
    a_float_t v[a_count_of(den)] = {0};
    a_float_t u0[a_count_of(num)] = {0};
    a_float_t v0[a_count_of(den)] = {0};
    a_float_t u1[a_count_of(num1)] = {0};
    a_float_t v1[a_count_of(den1)] = {0};
    a_float_t u2[a_count_of(num2)] = {0};
    a_float_t v2[a_count_of(den2)] = {0};
    a_tf_s tf[4];
    a_tf_init(tf + 0, a_count_of(num), num, u, a_count_of(den), den, v);
    a_tf_init(tf + 1, a_count_of(num), num, u0, a_count_of(den), den, v0);
    a_tf_init(tf + 2, a_count_of(num1), num1, u1, a_count_of(den1), den1, v1);
    a_tf_init(tf + 3, a_count_of(num2), num2, u2, a_count_of(den2), den2, v2);
    a_pid_fuzzy_s ctx[2];
#undef S
#define S 1
    static a_float_t const me[] = {
        A_MF_TRI, NB, NB, NM,
        A_MF_TRI, NB, NM, NS,
        A_MF_TRI, NM, NS, ZO,
        A_MF_TRI, NS, ZO, PS,
        A_MF_TRI, ZO, PS, PM,
        A_MF_TRI, PS, PM, PB,
        A_MF_TRI, PM, PB, PB};
#undef S
#define S 2
    static a_float_t const mec[] = {
        A_MF_TRI, NB, NB, NM,
        A_MF_TRI, NB, NM, NS,
        A_MF_TRI, NM, NS, ZO,
        A_MF_TRI, NS, ZO, PS,
        A_MF_TRI, ZO, PS, PM,
        A_MF_TRI, PS, PM, PB,
        A_MF_TRI, PM, PB, PB};
#undef S
#define S 5
    static a_float_t const mkp[] = {
        NB, NB, NM, NM, NS, ZO, ZO,
        NB, NB, NM, NS, NS, ZO, PS,
        NM, NM, NM, NS, ZO, PS, PS,
        NM, NM, NS, ZO, PS, PM, PM,
        NS, NS, ZO, PS, PS, PM, PM,
        NS, ZO, PS, PM, PM, PM, PB,
        ZO, ZO, PM, PM, PM, PB, PB};
#undef S
#define S 1
    static a_float_t const mki[] = {
        PB, PB, PM, PM, PS, ZO, ZO,
        PB, PB, PM, PS, PS, ZO, ZO,
        PB, PM, PS, PS, ZO, NS, NS,
        PM, PM, PS, ZO, NS, NM, NM,
        PM, PS, ZO, NS, NS, NM, NB,
        ZO, ZO, NS, NS, NM, NB, NB,
        ZO, ZO, NS, NM, NM, NB, NB};
#undef S
#define S 1
    static a_float_t const mkd[] = {
        NS, PS, PB, PB, PB, PM, NS,
        NS, PS, PB, PM, PM, PS, ZO,
        ZO, PS, PM, PM, PS, PS, ZO,
        ZO, PS, PS, PS, PS, PS, ZO,
        ZO, ZO, ZO, ZO, ZO, ZO, ZO,
        NB, NS, NS, NS, NS, NS, NB,
        NB, NM, NM, NM, NS, NS, NB};
    a_pid_fuzzy_init(ctx + 0, A_FLOAT_C(0.01), 7, me, mec, mkp, mki, mkd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(ctx + 0, idx, val);
        a_pid_fuzzy_pos(ctx + 0, 10);
    }
    a_pid_fuzzy_kpid(ctx + 0, 400, 200, A_FLOAT_C(0.005));
    a_pid_set_dt(&ctx[0].pid, A_FLOAT_C(0.001));
    a_pid_fuzzy_init(ctx + 1, A_FLOAT_C(0.01), 7, me, mec, mkp, mki, mkd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(ctx + 1, idx, val);
        a_pid_fuzzy_pos(ctx + 1, 10);
    }
    a_pid_fuzzy_kpid(ctx + 1, 400, 200, A_FLOAT_C(0.005));
    a_pid_set_dt(&ctx[1].pid, A_FLOAT_C(0.001));
    a_float_t set[3] = {1, 1, 1};
    a_float_t out[3];
    a_float_t fdb[3];
    a_float_t sum[3];
    a_float_t ec[3];
    a_float_t e[3];
    a_pid_fuzzy_chan(ctx + 1, 3, out, fdb, sum, ec, e);
    for (a_float_t t = 0; t < A_FLOAT_C(0.2); t += A_FLOAT_C(0.001))
    {
        a_float_t buf[3];
        buf[0] = *v0;
        buf[1] = *v1;
        buf[2] = *v2;
        a_float_t const *const ptr = a_pid_fuzzy_outp(ctx + 1, set, buf);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + 1 + i, ptr[i]);
        }
        a_tf_iter(tf, a_pid_fuzzy_outf(ctx + 0, 1, v[0]));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI(".3", "f ") A_FLOAT_PRI("", "g ") A_FLOAT_PRI("", "g ") A_FLOAT_PRI("", "g ") A_FLOAT_PRI("", "g ") A_FLOAT_PRI("", "g\n"),
               t, A_FLOAT_C(1.0), v[0], v0[0], v1[0], v2[0]);
#endif /* MAIN_ONCE */
    }
    a_tf_zero(tf);
    a_pid_fuzzy_zero(ctx);
    char buff[A_PID_FUZZY_BUF1(2)];
    a_pid_fuzzy_buf1(ctx, buff, 2);
    for (a_float_t t = 0; t < A_FLOAT_C(0.2); t += A_FLOAT_C(0.001))
    {
        u[0] = a_pid_fuzzy_outf(ctx, 1, v[0]);
        v[0] = a_tf_iter(tf, u[0]);
    }
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_EQU);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_OR_DEFAULT);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_OR_DEFAULT);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_OR_ALGEBRA);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_OR_ALGEBRA);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_OR_BOUNDED);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_OR_BOUNDED);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_AND_DEFAULT);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_AND_DEFAULT);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_AND_ALGEBRA);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_AND_ALGEBRA);
    a_pid_fuzzy_set_op(ctx, A_PID_FUZZY_AND_BOUNDED);
    TEST_BUG(a_pid_fuzzy_op(ctx) == A_PID_FUZZY_AND_BOUNDED);
    a_pid_fuzzy_exit(ctx);

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

#endif /* pid_fuzzy.h */