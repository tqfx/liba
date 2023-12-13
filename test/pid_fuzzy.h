#define MAIN_(x) A_CAST_2(x, _pid_fuzzy)
#include "test.h"
#include "a/tf.h"
#include "a/mf.h"
#include "a/math.h"
#include "a/pid_fuzzy.h"

static A_INLINE a_float_t input(a_float_t const x)
{
#if 0
    return a_float_sin(4 * A_FLOAT_PI * x);
#else
    return (void)x, 1;
#endif
}

#define N (-1 * X)
#define Z (+0 * X)
#define P (+1 * X)
#undef X
#define X 1
static a_float_t const m3e[] = {
    A_MF_TRI, N, N, Z,
    A_MF_TRI, N, Z, P,
    A_MF_TRI, Z, P, P};
#undef X
#define X 2
static a_float_t const m3ec[] = {
    A_MF_TRI, N, N, Z,
    A_MF_TRI, N, Z, P,
    A_MF_TRI, Z, P, P};
#undef X
#define X A_FLOAT_C(5.0)
static a_float_t const m3kp[] = {
    N, N, N,
    N, P, P,
    P, P, P};
#undef X
#define X A_FLOAT_C(0.01)
static a_float_t const m3ki[] = {
    Z, Z, Z,
    P, P, P,
    Z, Z, Z};
#undef X
#define X A_FLOAT_C(0.1)
static a_float_t const m3kd[] = {
    N, N, Z,
    Z, Z, Z,
    Z, P, P};
#undef X

#undef NL
#undef NM
#undef NS
#undef ZO
#undef PS
#undef PM
#undef PL
#define NL (-3 * X)
#define NM (-2 * X)
#define NS (-1 * X)
#define ZO (+0 * X)
#define PS (+1 * X)
#define PM (+2 * X)
#define PL (+3 * X)
#undef X
#define X A_FLOAT_C(1.0) / 2
static a_float_t const m7e[] = {
    A_MF_TRI, NL, NL, NM,
    A_MF_TRI, NL, NM, NS,
    A_MF_TRI, NM, NS, ZO,
    A_MF_TRI, NS, ZO, PS,
    A_MF_TRI, ZO, PS, PM,
    A_MF_TRI, PS, PM, PL,
    A_MF_TRI, PM, PL, PL};
#undef X
#define X A_FLOAT_C(1.0) / 2
static a_float_t const m7ec[] = {
    A_MF_TRI, NL, NL, NM,
    A_MF_TRI, NL, NM, NS,
    A_MF_TRI, NM, NS, ZO,
    A_MF_TRI, NS, ZO, PS,
    A_MF_TRI, ZO, PS, PM,
    A_MF_TRI, PS, PM, PL,
    A_MF_TRI, PM, PL, PL};
#undef X
#define X A_FLOAT_C(500.0) / 6
static a_float_t const m7kp[] = {
    NL, NL, NM, NM, NS, ZO, ZO,
    NL, NL, NM, NS, NS, ZO, PS,
    NM, NM, NM, NS, ZO, PS, PS,
    NM, NM, NS, ZO, PS, PM, PM,
    NS, NS, ZO, PS, PS, PM, PM,
    NS, ZO, PS, PM, PM, PM, PL,
    ZO, ZO, PM, PM, PM, PL, PL};
#undef X
#define X A_FLOAT_C(10.0) / 3
static a_float_t const m7ki[] = {
    PL, PL, PM, PM, PS, ZO, ZO,
    PL, PL, PM, PS, PS, ZO, ZO,
    PL, PM, PS, PS, ZO, NS, NS,
    PM, PM, PS, ZO, NS, NM, NM,
    PM, PS, ZO, NS, NS, NM, NL,
    ZO, ZO, NS, NS, NM, NL, NL,
    ZO, ZO, NS, NM, NM, NL, NL};
#undef X
#define X A_FLOAT_C(5000.0) / 3
static a_float_t const m7kd[] = {
    NS, PS, PL, PL, PL, PM, NS,
    NS, PS, PL, PM, PM, PS, ZO,
    ZO, PS, PM, PM, PS, PS, ZO,
    ZO, PS, PS, PS, PS, PS, ZO,
    ZO, ZO, ZO, ZO, ZO, ZO, ZO,
    NL, NS, NS, NS, NS, NS, NL,
    NL, NM, NM, NM, NS, NS, NL};
#undef X

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    test_init(argc, argv, 1);

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf_s pos_tf;
    a_float_t pos_input[A_LEN(num)];
    a_float_t pos_output[A_LEN(den)];
    a_tf_init(&pos_tf, A_LEN(num), num, pos_input, A_LEN(den), den, pos_output);
    a_tf_s inc_tf;
    a_float_t inc_input[A_LEN(num)];
    a_float_t inc_output[A_LEN(den)];
    a_tf_init(&inc_tf, A_LEN(num), num, inc_input, A_LEN(den), den, inc_output);

    a_pid_fuzzy_s pos_pid;
    pos_pid.pid.summax = +10;
    pos_pid.pid.summin = -10;
    pos_pid.pid.outmax = +10;
    pos_pid.pid.outmin = -10;
    pos_pid.order = 3;
    pos_pid.me = m3e;
    pos_pid.mec = m3ec;
    pos_pid.mkp = m3kp;
    pos_pid.mki = m3ki;
    pos_pid.mkd = m3kd;
    pos_pid.order = 7;
    pos_pid.me = m7e;
    pos_pid.mec = m7ec;
    pos_pid.mkp = m7kp;
    pos_pid.mki = m7ki;
    pos_pid.mkd = m7kd;
    pos_pid.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(&pos_pid);
    a_byte_t pos_joint[A_PID_FUZZY_JOINT(2)];
    a_pid_fuzzy_set_joint(&pos_pid, pos_joint, 2);
    a_pid_fuzzy_s inc_pid;
    inc_pid.pid.outmax = +10;
    inc_pid.pid.outmin = -10;
    inc_pid.order = 3;
    inc_pid.me = m3e;
    inc_pid.mec = m3ec;
    inc_pid.mkp = m3kp;
    inc_pid.mki = m3ki;
    inc_pid.mkd = m3kd;
    inc_pid.order = 7;
    inc_pid.me = m7e;
    inc_pid.mec = m7ec;
    inc_pid.mkp = m7kp;
    inc_pid.mki = m7ki;
    inc_pid.mkd = m7kd;
    inc_pid.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(&inc_pid);
    a_byte_t inc_joint[A_PID_FUZZY_JOINT(2)];
    a_pid_fuzzy_set_joint(&inc_pid, inc_joint, 2);
    a_pid_fuzzy_kpid(&pos_pid, 600, A_FLOAT_C(20.0), A_FLOAT_C(6000.0));
    a_pid_fuzzy_kpid(&inc_pid, 600, A_FLOAT_C(20.0), A_FLOAT_C(6000.0));
    for (unsigned int i = 0; i < 200; ++i)
    {
        a_float_t in = input(A_FLOAT_C(0.001) * a_float_c(, i));
        a_tf_iter(&pos_tf, a_pid_fuzzy_pos(&pos_pid, in, *pos_tf.output));
        a_tf_iter(&inc_tf, a_pid_fuzzy_inc(&inc_pid, in, *inc_tf.output));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              A_FLOAT_C(0.001) * a_float_c(, i), in, *pos_tf.output, *inc_tf.output);
    }
    a_pid_fuzzy_zero(&pos_pid);
    a_pid_fuzzy_zero(&inc_pid);
    a_tf_zero(&pos_tf);
    a_tf_zero(&inc_tf);

    return 0;
}