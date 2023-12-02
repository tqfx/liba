#define MAIN_(x) A_CAST_2(x, _pid_expert)
#include "test.h"
#include "a/tf.h"
#undef A_EXTERN
#define A_EXTERN A_EXPORT extern

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
    a_float_t ec; //!< error change
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
 @brief zeroing for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
A_EXTERN void a_pid_expert_zero(a_pid_expert_s *ctx);

/*!
 @brief initialize for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
A_EXTERN void a_pid_expert_init(a_pid_expert_s *ctx);

/*!
 @brief set proportional integral derivative constant for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_expert_kpid(a_pid_expert_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd);

/*!
 @brief calculate for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_float_t a_pid_expert_iter(a_pid_expert_s *ctx, a_float_t set, a_float_t fdb);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_PID_EXPERT */

#endif /* a/pid_expert.h */

#include "a/math.h"

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
    test_init(argc, argv, 1);

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf_s tf;
    a_float_t tf_input[A_LEN(num)];
    a_float_t tf_output[A_LEN(den)];
    a_tf_init(&tf, A_LEN(num), num, tf_input, A_LEN(den), den, tf_output);

    a_pid_expert_s ctx;
    ctx.pid.kp = A_FLOAT_C(10.0);
    ctx.pid.ki = A_FLOAT_C(0.5);
    ctx.pid.kd = A_FLOAT_C(10.0);
    ctx.pid.outmax = +A_FLOAT_MAX;
    ctx.pid.outmin = -A_FLOAT_MAX;
    ctx.max1 = A_FLOAT_C(0.4);
    ctx.gain = A_FLOAT_C(2.0);
    ctx.max2 = A_FLOAT_C(0.1);
    ctx.loss = A_FLOAT_C(0.5);
    ctx.outmax = A_FLOAT_C(10.0);
    ctx.epsilon = A_FLOAT_C(0.01);
    a_pid_expert_init(&ctx);
    for (unsigned int i = 0; i < 500; ++i)
    {
        a_float_t in = input(A_FLOAT_C(0.001) * a_float_c(, i));
        a_tf_iter(&tf, a_pid_expert_iter(&ctx, in, *tf.output));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              A_FLOAT_C(0.001) * a_float_c(, i), in, *tf.output, ctx.pid.err);
    }
    a_pid_expert_zero(&ctx);
    a_tf_zero(&tf);

    return 0;
}
