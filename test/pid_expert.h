#define MAIN(x) pid_expert##x
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

typedef struct a_pid_expert a_pid_expert;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
#define a_pid_expert_init(ctx) a_pid_expert_zero(ctx)

/*!
 @brief set proportional integral derivative constant for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_EXTERN void a_pid_expert_set_kpid(a_pid_expert *ctx, a_real kp, a_real ki, a_real kd);

/*!
 @brief calculate for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
 @param[in] set setpoint value
 @param[in] fdb feedback value
 @return output value
*/
A_EXTERN a_real a_pid_expert_iter(a_pid_expert *ctx, a_real set, a_real fdb);

/*!
 @brief zeroing for expert PID controller
 @param[in,out] ctx points to an instance of expert PID controller
*/
A_EXTERN void a_pid_expert_zero(a_pid_expert *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
struct pid_expert;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for expert PID controller
*/
struct a_pid_expert
{
    a_pid pid; /*!< instance structure for PID controller */
    a_real ec; /*!< error change */
    a_real outmax; /*!< maximum output */
    a_real epsilon; /*!< precision */
    a_real max1; /*!< first error bound */
    a_real gain; /*!< gain coefficient */
    a_real max2; /*!< second error bound */
    a_real loss; /*!< loss coefficient */
#if defined(__cplusplus)
    A_INLINE void init() { a_pid_expert_init(this); }
    A_INLINE void set_kpid(a_real kp, a_real ki, a_real kd)
    {
        a_pid_expert_set_kpid(this, kp, ki, kd);
    }
    A_INLINE a_real operator()(a_real set, a_real fdb)
    {
        return a_pid_expert_iter(this, set, fdb);
    }
    A_INLINE void zero() { a_pid_expert_zero(this); }
#endif /* __cplusplus */
};

/*! @} A_PID_EXPERT */

#endif /* a/pid_expert.h */

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
    a_pid_expert ctx;

    main_init(argc, argv, 1);
    a_tf_init(&tf, A_LEN(num), num, tf_input, A_LEN(den), den, tf_output);

    ctx.pid.kp = A_REAL_C(10.0);
    ctx.pid.ki = A_REAL_C(0.5);
    ctx.pid.kd = A_REAL_C(10.0);
    ctx.pid.outmax = +A_REAL_MAX;
    ctx.pid.outmin = -A_REAL_MAX;
    ctx.max1 = A_REAL_C(0.4);
    ctx.gain = A_REAL_C(2.0);
    ctx.max2 = A_REAL_C(0.1);
    ctx.loss = A_REAL_C(0.5);
    ctx.outmax = A_REAL_C(10.0);
    ctx.epsilon = A_REAL_C(0.01);
    a_pid_expert_init(&ctx);
    for (i = 0; i < 500; ++i)
    {
        a_real in = input(A_REAL_C(0.001) * a_real_c(i));
        a_tf_iter(&tf, a_pid_expert_iter(&ctx, in, *tf.output));
        debug("%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f,%+" A_REAL_PRI "f\n",
              A_REAL_C(0.001) * a_real_c(i), in, *tf.output, ctx.pid.err);
    }
    a_pid_expert_zero(&ctx);
    a_tf_zero(&tf);

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_BUILD_ASSERT(std::is_pod<a_pid_expert>::value);
#endif /* __cplusplus */

    return 0;
}
