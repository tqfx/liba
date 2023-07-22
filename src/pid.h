#ifndef PID_H
#define PID_H

#include "a/pid.h"

#define A_PID_CHAN(ctx)     \
    do                      \
    {                       \
        (ctx)->out.p = out; \
        (ctx)->fdb.p = fdb; \
        (ctx)->tmp.p = tmp; \
        (ctx)->err.p = err; \
    } while (0)

#define A_PID_ZERO(ctx, _) \
    do                     \
    {                      \
        (ctx)->out _ = 0;  \
        (ctx)->fdb _ = 0;  \
        (ctx)->tmp _ = 0;  \
        (ctx)->err _ = 0;  \
    } while (0)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN void a_pid_outf_(a_pid_s *ctx, a_float_t set, a_float_t fdb, a_float_t ec, a_float_t e);
A_HIDDEN void a_pid_outp_(a_pid_s const *ctx, a_float_t set, a_float_t fdb, a_float_t ec, a_float_t e, unsigned int i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
