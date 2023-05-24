from a.pid cimport *

cdef extern from "a/fpid.h":
    ctypedef struct a_fpid_s:
        a_pid_s pid
        a_float_t kp
        a_float_t ki
        a_float_t kd
    a_size_t A_FPID_BUF1(unsigned int max)
    a_fpid_s *a_fpid_off(a_fpid_s *ctx)
    a_fpid_s *a_fpid_inc(a_fpid_s *ctx)
    a_fpid_s *a_fpid_pos(a_fpid_s *ctx, a_float_t max)
    a_fpid_s *a_fpid_buf1(a_fpid_s *ctx, void *ptr, a_size_t max)
    a_fpid_s *a_fpid_kpid(a_fpid_s *ctx, a_float_t kp, a_float_t ki, a_float_t kd)
    a_fpid_s *a_fpid_buff(a_fpid_s *ctx, unsigned int *idx, a_float_t *mms, a_float_t *mat)
    a_fpid_s *a_fpid_setv(a_fpid_s *ctx, a_float_t *out, a_float_t *fdb, a_float_t *sum, a_float_t *ec, a_float_t *e)
    a_fpid_s *a_fpid_base(a_fpid_s *ctx, unsigned int col, const a_float_t *mec, const a_float_t *mec,
                          const a_float_t *mkp, const a_float_t *mki, const a_float_t *mkd)
    a_fpid_s *a_fpid_init(a_fpid_s *ctx, a_float_t dt, unsigned int col, const a_float_t *mec, const a_float_t *mec,
                          const a_float_t *mkp, const a_float_t *mki, const a_float_t *mkd, a_float_t min, a_float_t max)
    a_float_t a_fpid_outf(a_fpid_s *ctx, a_float_t set, a_float_t fdb)
    const a_float_t *a_fpid_outp(a_fpid_s *ctx, const a_float_t *set, const a_float_t *fdb)
    a_fpid_s *a_fpid_exit(a_fpid_s *ctx)
    a_fpid_s *a_fpid_zero(a_fpid_s *ctx)
    unsigned int a_fpid_bufnum(const a_fpid_s *ctx)
    void * a_fpid_bufptr(const a_fpid_s *ctx)
    unsigned int a_fpid_col(const a_fpid_s *ctx)
