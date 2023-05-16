from a cimport *

cdef extern from "a/pid.h":
    ctypedef enum a_pid_e:
        A_PID_OFF
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_s:
        a_real_t outmin
        a_real_t outmax
        a_real_t summax
        a_real_u out
        a_real_u fdb
        a_real_u ec
        a_real_u e
    a_pid_s *a_pid_off(a_pid_s *ctx)
    a_pid_s *a_pid_inc(a_pid_s *ctx)
    a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max)
    a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
    a_pid_s *a_pid_chan(a_pid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
    a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t dt, a_real_t min, a_real_t max)
    a_real_t a_pid_outf(a_pid_s *ctx, a_real_t set, a_real_t fdb)
    const a_real_t *a_pid_outp(a_pid_s *ctx, const a_real_t *set, const a_real_t *fdb)
    a_pid_s *a_pid_exit(a_pid_s *ctx)
    a_pid_s *a_pid_zero(a_pid_s *ctx)
    a_real_t a_pid_dt(const a_pid_s *ctx)
    a_void_t a_pid_set_dt(a_pid_s *ctx, a_real_t dt)
    a_real_t a_pid_kp(const a_pid_s *ctx)
    a_void_t a_pid_set_kp(a_pid_s *ctx, a_real_t kp)
    a_real_t a_pid_ki(const a_pid_s *ctx)
    a_void_t a_pid_set_ki(a_pid_s *ctx, a_real_t ki)
    a_real_t a_pid_kd(const a_pid_s *ctx)
    a_void_t a_pid_set_kd(a_pid_s *ctx, a_real_t kd)
    a_uint_t a_pid_num(const a_pid_s *ctx)
    a_void_t a_pid_set_num(a_pid_s *ctx, a_uint_t num)
    a_uint_t a_pid_reg(const a_pid_s *ctx)
    a_void_t a_pid_set_reg(a_pid_s *ctx, a_uint_t reg)
    a_uint_t a_pid_mode(const a_pid_s *ctx)
    a_void_t a_pid_set_mode(a_pid_s *ctx, a_uint_t mode)
