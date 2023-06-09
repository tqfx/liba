from a cimport *

cdef extern from "a/pid.h":
    ctypedef enum a_pid_e:
        A_PID_OFF
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_s:
        a_float_t outmin
        a_float_t outmax
        a_float_t summax
        a_float_u out
        a_float_u fdb
        a_float_u err
    a_pid_s *a_pid_off(a_pid_s *ctx)
    a_pid_s *a_pid_inc(a_pid_s *ctx)
    a_pid_s *a_pid_pos(a_pid_s *ctx, a_float_t max)
    a_pid_s *a_pid_kpid(a_pid_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd)
    a_pid_s *a_pid_chan(a_pid_s *ctx, unsigned int num, a_float_t *out, a_float_t *fdb, a_float_t *tmp, a_float_t *err)
    a_pid_s *a_pid_init(a_pid_s *ctx, a_float_t dt, a_float_t min, a_float_t max)
    a_float_t a_pid_outf(a_pid_s *ctx, a_float_t set, a_float_t fdb)
    const a_float_t *a_pid_outp(a_pid_s *ctx, const a_float_t *set, const a_float_t *fdb)
    a_pid_s *a_pid_exit(a_pid_s *ctx)
    a_pid_s *a_pid_zero(a_pid_s *ctx)
    a_float_t a_pid_dt(const a_pid_s *ctx)
    void a_pid_set_dt(a_pid_s *ctx, a_float_t dt)
    a_float_t a_pid_kp(const a_pid_s *ctx)
    void a_pid_set_kp(a_pid_s *ctx, a_float_t kp)
    a_float_t a_pid_ki(const a_pid_s *ctx)
    void a_pid_set_ki(a_pid_s *ctx, a_float_t ki)
    a_float_t a_pid_kd(const a_pid_s *ctx)
    void a_pid_set_kd(a_pid_s *ctx, a_float_t kd)
    unsigned int a_pid_num(const a_pid_s *ctx)
    void a_pid_set_num(a_pid_s *ctx, unsigned int num)
    unsigned int a_pid_reg(const a_pid_s *ctx)
    void a_pid_set_reg(a_pid_s *ctx, unsigned int reg)
    unsigned int a_pid_mode(const a_pid_s *ctx)
    void a_pid_set_mode(a_pid_s *ctx, unsigned int mode)
