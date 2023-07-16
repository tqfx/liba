#ifndef TEST_PID_EXPERT_H
#define TEST_PID_EXPERT_H
#define MAIN_(s, argc, argv) A_CASE_2(pid_expert, s)(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/math.h"

/*!
 @file pid_expert.h
 @brief expert proportional integral derivative controller
*/

#ifndef LIBA_PID_EXPERT_H
#define LIBA_PID_EXPERT_H

#include "a/pid.h"

/*!
 @ingroup A
 @addtogroup A_PID_EXPERT expert proportional integral derivative controller
 @{
*/

/*!
 @brief instance structure for expert PID controller
*/
typedef struct a_pid_expert_s
{
    a_pid_s pid; //!< instance structure for PID controller
    a_float_u ec; //!< error change
    a_float_t outmax; //!< maximum output
    a_float_t epsilon; //!< precision
    a_float_t max1; //!< first error bound
    a_float_t gain; //!< gain coefficient
    a_float_t max2; //!< second error bound
    a_float_t loss; //!< loss coefficient
} a_pid_expert_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize function for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] num number of controller channel
*/
A_EXTERN void a_pid_expert_init(a_pid_expert_s *ctx, unsigned int num);

/*!
 @brief set buffer for multichannel expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] num number of controller output
 @param[in] out points to controller output
 @param[in] fdb points to cache feedback buffer
 @param[in] tmp points to cache variable buffer
 @param[in] err points to cache error buffer
 @param[in] ec points to error change buffer
*/
A_EXTERN void a_pid_expert_chan(a_pid_expert_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb,
                                a_float_t *tmp, a_float_t *err, a_float_t *ec);

/*!
 @brief set proportional integral derivative constant for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_expert_kpid(a_pid_expert_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief calculate function for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output value
*/
A_EXTERN a_float_t a_pid_expert_outf(a_pid_expert_s *ctx, a_float_t set, a_float_t fdb);

/*!
 @brief calculate function for multichannel expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
*/
A_EXTERN a_float_t const *a_pid_expert_outp(a_pid_expert_s *ctx, a_float_t const *set, a_float_t const *fdb);

/*!
 @brief zero clear function for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
A_EXTERN void a_pid_expert_zero(a_pid_expert_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_EXPERT */

#endif /* pid_expert.h */

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input[a_count_of(num)];
    a_float_t output[a_count_of(den)];
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, input, a_count_of(den), den, output);
    a_pid_expert_s ctx;
    ctx.pid.kp = A_FLOAT_C(400.0);
    ctx.pid.ki = A_FLOAT_C(200.0);
    ctx.pid.kd = A_FLOAT_C(0.005);
    ctx.pid.outmax = +10;
    ctx.pid.outmin = -10;
    ctx.pid.mode = A_PID_INC;
    ctx.max1 = A_FLOAT_C(0.4);
    ctx.gain = A_FLOAT_C(2.0);
    ctx.max2 = A_FLOAT_C(0.1);
    ctx.loss = A_FLOAT_C(0.5);
    ctx.outmax = A_FLOAT_C(10.0);
    ctx.epsilon = A_FLOAT_C(0.01);
    a_pid_expert_init(&ctx, 0);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        a_tf_iter(&tf, a_pid_expert_outf(&ctx, 1, output[0]));
    }
    a_pid_expert_zero(&ctx);
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
    a_pid_expert_s ctx;
    ctx.pid.kp = A_FLOAT_C(400.0);
    ctx.pid.ki = A_FLOAT_C(200.0);
    ctx.pid.kd = A_FLOAT_C(0.005);
    ctx.pid.outmax = +10;
    ctx.pid.outmin = -10;
    ctx.pid.mode = A_PID_INC;
    ctx.max1 = A_FLOAT_C(0.4);
    ctx.gain = A_FLOAT_C(2.0);
    ctx.max2 = A_FLOAT_C(0.1);
    ctx.loss = A_FLOAT_C(0.5);
    ctx.outmax = A_FLOAT_C(10.0);
    ctx.epsilon = A_FLOAT_C(0.01);
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        static a_float_t ec[3];
        a_pid_expert_chan(&ctx, 3, out, fdb, tmp, err, ec);
    }
    a_float_t set[3] = {1, 1, 1};
    for (unsigned int n = 0; n < 1000; ++n)
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].output;
        }
        a_float_t const *const out = a_pid_expert_outp(&ctx, set, fdb);
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

    a_pid_expert_s ctx;
    ctx.pid.kp = A_FLOAT_C(10.0);
    ctx.pid.ki = A_FLOAT_C(0.5);
    ctx.pid.kd = A_FLOAT_C(10.0);
    ctx.pid.outmax = +A_FLOAT_MAX;
    ctx.pid.outmin = -A_FLOAT_MAX;
    ctx.pid.mode = A_PID_INC;
    ctx.max1 = A_FLOAT_C(0.4);
    ctx.gain = A_FLOAT_C(2.0);
    ctx.max2 = A_FLOAT_C(0.1);
    ctx.loss = A_FLOAT_C(0.5);
    ctx.outmax = A_FLOAT_C(10.0);
    ctx.epsilon = A_FLOAT_C(0.01);
    a_pid_expert_init(&ctx, 0);
    for (unsigned int i = 0; i < 500; ++i)
    {
        a_float_t in = input(A_FLOAT_C(0.001) * i);
        a_tf_iter(&tf, a_pid_expert_outf(&ctx, in, *tf.output));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
               A_FLOAT_C(0.001) * i, in, *tf.output, ctx.pid.err.f);
#endif /* MAIN_ONCE */
    }
    a_pid_expert_zero(&ctx);
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

#endif /* pid_expert.h */
