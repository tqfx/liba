#define LIBA_FPID_C
#include "fpid.h"

a_real_t a_fpid_op_or(a_real_t const l, a_real_t const r) { return l + r - l * r; }

a_real_t a_fpid_op_and(a_real_t const l, a_real_t const r) { return l * r; }

a_real_t a_fpid_op_equ(a_real_t const l, a_real_t const r)
{
    return a_real_sqrt(l * r) * a_real_sqrt(1 - (1 - l) * (1 - r));
}

a_void_t a_fpid_set_op(a_fpid_s *const ctx, a_uint_t op)
{
    ctx->pid->reg &= ~A_FPID_FUZZY_MASK;
    op &= A_FPID_FUZZY_MASK;
    ctx->pid->reg |= op;
    switch (op)
    {
    case A_FPID_OR_ALGEBRA:
        ctx->op = a_fpid_op_or;
        break;
    case A_FPID_OR_BOUNDED:
    case A_FPID_AND:
        ctx->op = a_real_min;
        break;
    case A_FPID_AND_ALGEBRA:
        ctx->op = a_fpid_op_and;
        break;
    case A_FPID_AND_BOUNDED:
    case A_FPID_OR:
        ctx->op = a_real_max;
        break;
    case A_FPID_EQU:
    default:
        ctx->op = a_fpid_op_equ;
    }
}

a_uint_t a_fpid_mf(a_real_t const *a, a_real_t const x, a_uint_t *idx, a_real_t *mms)
{
    a_uint_t num = 0;
    a_int_t e = A_MF_NUL;
    for (a_uint_t i = 0; (void)(e = a_int_c(*a++)), e != A_MF_NUL; ++i)
    {
        a_real_t y = 0;
        switch (e)
        {
        case A_MF_GAUSS:
            y = a_mf_gauss(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_GBELL:
            y = a_mf_gbell(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_SIG:
            y = a_mf_sig(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_TRAP:
            y = a_mf_trap(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_TRI:
            y = a_mf_tri(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_Z:
            y = a_mf_z(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_NUL:
        default:
            goto out;
        }
        if (y > 0)
        {
            ++num;
            *idx++ = i;
            *mms++ = y;
        }
    }
out:
    return num;
}

a_fpid_s *a_fpid_off(a_fpid_s *const ctx)
{
    a_pid_off(ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_inc(a_fpid_s *const ctx)
{
    a_pid_inc(ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_pos(a_fpid_s *const ctx, a_real_t const max)
{
    a_pid_pos(ctx->pid, max);
    return ctx;
}

a_fpid_s *a_fpid_ilim(a_fpid_s *const ctx, a_real_t const min, a_real_t const max)
{
    a_real_t const x = a_real_c((a_fpid_col(ctx) - 1) >> 1 << 1);
    ctx->sigma = x / (max - min);
    return ctx;
}

a_fpid_s *a_fpid_olim(a_fpid_s *const ctx, a_real_t const min, a_real_t const max)
{
    a_real_t const x = a_real_c((a_fpid_col(ctx) - 1) >> 1 << 1);
    ctx->alpha = (max - min) / x;
    ctx->pid->outmin = min;
    ctx->pid->outmax = max;
    return ctx;
}

a_fpid_s *a_fpid_buf1(a_fpid_s *const ctx, a_vptr_t ptr, a_size_t max)
{
    a_fpid_set_bufnum(ctx, (a_uint_t)max);
    max <<= 1;
    ctx->idx = a_uint_p(ptr);
    ptr = a_byte_p(ptr) + sizeof(a_uint_t) * max;
    ctx->mms = a_real_p(ptr);
    ptr = a_byte_p(ptr) + sizeof(a_real_t) * max;
    ctx->mat = a_real_p(ptr);
    return ctx;
}

a_fpid_s *a_fpid_kpid(a_fpid_s *const ctx, a_real_t const kp, a_real_t const ki, a_real_t const kd)
{
    a_pid_kpid(ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
    return ctx;
}

a_fpid_s *a_fpid_buff(a_fpid_s *const ctx, a_uint_t *const idx, a_real_t *const mms, a_real_t *const mat)
{
    ctx->idx = idx;
    ctx->mms = mms;
    ctx->mat = mat;
    return ctx;
}

a_fpid_s *a_fpid_setp(a_fpid_s *const ctx, a_uint_t const num, a_real_t *const out, a_real_t *const fdb,
                      a_real_t *const sum, a_real_t *const ec, a_real_t *const e)
{
    a_pid_setp(ctx->pid, num, out, fdb, sum, ec, e);
    return ctx;
}

a_fpid_s *a_fpid_base(a_fpid_s *const ctx, a_uint_t const num, a_real_t const *const mmp,
                      a_real_t const *const mkp, a_real_t const *const mki, a_real_t const *const mkd)
{
    a_fpid_set_col(ctx, num);
    ctx->mmp = mmp;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    return ctx;
}

a_fpid_s *a_fpid_init(a_fpid_s *const ctx, a_real_t const dt, a_uint_t const num, a_real_t const *const mmp,
                      a_real_t const *const mkp, a_real_t const *const mki, a_real_t const *const mkd,
                      a_real_t const imin, a_real_t const imax, a_real_t const omin, a_real_t const omax)
{
    a_real_t x = a_real_c((num - 1) >> 1 << 1);
    a_pid_init(ctx->pid, dt, omin, omax);
    a_fpid_base(ctx, num, mmp, mkp, mki, mkd);
    ctx->sigma = x / (imax - imin);
    ctx->alpha = (omax - omin) / x;
    ctx->op = a_fpid_op_equ;
    ctx->idx = A_NULL;
    ctx->mms = A_NULL;
    ctx->mat = A_NULL;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return ctx;
}

a_fpid_s *a_fpid_exit(a_fpid_s *const ctx) { return a_fpid_zero(ctx); }

a_fpid_s *a_fpid_zero(a_fpid_s *const ctx)
{
    a_pid_zero(ctx->pid);
    return ctx;
}

static void a_fpid_proc_(a_fpid_s *const ctx, a_real_t ev[2], a_uint_t const num)
{
    /* quantize input */
    ev[0] = ctx->sigma * ev[0] / (1 << 0);
    ev[1] = ctx->sigma * ev[1] / (1 << 1);
    /* calculate membership */
    a_uint_t const ne = a_fpid_mf(ctx->mmp, ev[0], ctx->idx + 00, ctx->mms + 00);
    a_uint_t const nc = a_fpid_mf(ctx->mmp, ev[1], ctx->idx + ne, ctx->mms + ne);
    if (!ne || !nc)
    {
        return;
    }
    /* joint membership */
    a_real_t inv = 0;
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t const col = i * nc;
        for (a_uint_t j = 0; j != nc; ++j)
        {
            a_uint_t const idx = col + j; /* mat(i,j)=f(e[i],ec[j]) */
            ctx->mat[idx] = ctx->op(ctx->mms[i], ctx->mms[ne + j]);
            inv += ctx->mat[idx];
        }
    }
    inv = ctx->alpha / inv;
    /* mean of centers defuzzifier */
    a_real_t qv[3] = {0, 0, 0};
    if (ctx->mkp)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const col = i * nc;
            a_uint_t const idx = ctx->idx[i] * num;
            for (a_uint_t j = 0; j != nc; ++j) /* mat(i,j) * kp(e[i],ec[j]) */
            {
                qv[0] += ctx->mat[col + j] * ctx->mkp[ctx->idx[ne + j] + idx];
            }
        }
        qv[0] *= inv;
    }
    if (ctx->mki)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const col = i * nc;
            a_uint_t const idx = ctx->idx[i] * num;
            for (a_uint_t j = 0; j != nc; ++j) /* mat(i,j) * ki(e[i],ec[j]) */
            {
                qv[1] += ctx->mat[col + j] * ctx->mki[ctx->idx[ne + j] + idx];
            }
        }
        qv[1] *= inv;
    }
    if (ctx->mkd)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const col = i * nc;
            a_uint_t const idx = ctx->idx[i] * num;
            for (a_uint_t j = 0; j != nc; ++j) /* mat(i,j) * kd(e[i],ec[j]) */
            {
                qv[2] += ctx->mat[col + j] * ctx->mkd[ctx->idx[ne + j] + idx];
            }
        }
        qv[2] *= inv;
    }
    a_pid_kpid(ctx->pid, qv[0] + ctx->kp, qv[1] + ctx->ki, qv[2] + ctx->kd);
}

a_real_t a_fpid_outv(a_fpid_s *const ctx, a_real_t const set, a_real_t const fdb)
{
    a_real_t ev[2];
    a_real_t const e = ev[0] = set - fdb;
    a_real_t const ec = ev[1] = e - ctx->pid->e.v;
    a_fpid_proc_(ctx, ev, a_fpid_col(ctx));
    return a_pid_outv_(ctx->pid, a_pid_mode(ctx->pid), set, fdb, ec, e);
}

a_real_t *a_fpid_outp(a_fpid_s *const ctx, a_real_t *const set, a_real_t *const fdb)
{
    a_uint_t const col = a_fpid_col(ctx);
    a_uint_t const num = a_pid_num(ctx->pid);
    a_uint_t const reg = a_pid_mode(ctx->pid);
    for (a_uint_t i = 0; i != num; ++i)
    {
        a_real_t ev[2];
        a_real_t const e = ev[0] = set[i] - fdb[i];
        a_real_t const ec = ev[1] = e - ctx->pid->e.p[i];
        a_fpid_proc_(ctx, ev, col);
        a_pid_outp_(ctx->pid, reg, set[i], fdb[i], ec, e, i);
    }
    return ctx->pid->out.p;
}
