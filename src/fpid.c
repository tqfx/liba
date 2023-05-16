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
    ctx->pid.reg &= ~A_FPID_FUZZY_MASK;
    op &= A_FPID_FUZZY_MASK;
    ctx->pid.reg |= op;
    switch (op)
    {
    case A_FPID_OR_ALGEBRA:
        ctx->op = a_fpid_op_or;
        break;
    case A_FPID_OR_BOUNDED:
    case A_FPID_AND_DEFAULT:
        ctx->op = a_real_min;
        break;
    case A_FPID_AND_ALGEBRA:
        ctx->op = a_fpid_op_and;
        break;
    case A_FPID_AND_BOUNDED:
    case A_FPID_OR_DEFAULT:
        ctx->op = a_real_max;
        break;
    case A_FPID_EQU:
    default:
        ctx->op = a_fpid_op_equ;
    }
}

a_uint_t a_fpid_mf(a_real_t const *a, a_real_t const x, a_uint_t *idx, a_real_t *val)
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
        if (y > A_REAL_EPSILON)
        {
            ++num;
            *idx++ = i;
            *val++ = y;
        }
    }
out:
    return num;
}

a_fpid_s *a_fpid_off(a_fpid_s *const ctx)
{
    a_pid_off(&ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_inc(a_fpid_s *const ctx)
{
    a_pid_inc(&ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_pos(a_fpid_s *const ctx, a_real_t const max)
{
    a_pid_pos(&ctx->pid, max);
    return ctx;
}

a_fpid_s *a_fpid_kpid(a_fpid_s *const ctx, a_real_t const kp, a_real_t const ki, a_real_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
    return ctx;
}

a_fpid_s *a_fpid_buf1(a_fpid_s *const ctx, a_vptr_t ptr, a_size_t max)
{
    a_fpid_set_bufmax(ctx, (a_uint_t)max);
    ctx->idx = a_uint_p(ptr);
    ptr = a_byte_p(ptr) + sizeof(a_uint_t) * (max << 1);
    ctx->val = a_real_p(ptr);
    return ctx;
}

a_fpid_s *a_fpid_buff(a_fpid_s *const ctx, a_uint_t *const idx, a_real_t *const val)
{
    ctx->idx = idx;
    ctx->val = val;
    return ctx;
}

a_fpid_s *a_fpid_chan(a_fpid_s *const ctx, a_uint_t const num, a_real_t *const out, a_real_t *const fdb,
                      a_real_t *const sum, a_real_t *const ec, a_real_t *const e)
{
    a_pid_chan(&ctx->pid, num, out, fdb, sum, ec, e);
    return ctx;
}

a_fpid_s *a_fpid_base(a_fpid_s *const ctx, a_uint_t const col, a_real_t const *const me, a_real_t const *const mec,
                      a_real_t const *const mkp, a_real_t const *const mki, a_real_t const *const mkd)
{
    a_fpid_set_col(ctx, col);
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    return ctx;
}

a_fpid_s *a_fpid_init(a_fpid_s *const ctx, a_real_t const dt, a_uint_t const col, a_real_t const *const me, a_real_t const *const mec,
                      a_real_t const *const mkp, a_real_t const *const mki, a_real_t const *const mkd, a_real_t const min, a_real_t const max)
{
    a_pid_init(&ctx->pid, dt, min, max);
    a_fpid_base(ctx, col, me, mec, mkp, mki, mkd);
    ctx->op = a_fpid_op_equ;
    ctx->idx = A_NULL;
    ctx->val = A_NULL;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return ctx;
}

a_fpid_s *a_fpid_exit(a_fpid_s *const ctx) { return a_fpid_zero(ctx); }

a_fpid_s *a_fpid_zero(a_fpid_s *const ctx)
{
    a_pid_zero(&ctx->pid);
    return ctx;
}

static void a_fpid_iter_(a_fpid_s *const ctx, a_uint_t const col, a_real_t ec, a_real_t e)
{
    /* calculate membership */
    a_uint_t const ne = a_fpid_mf(ctx->me, e, ctx->idx, ctx->val);
    a_uint_t const nec = a_fpid_mf(ctx->mec, ec, ctx->idx + ne, ctx->val + ne);
    if (!ne || !nec)
    {
        return;
    }
    a_real_t *const mat = ctx->val + ne + nec;
    /* joint membership */
    a_real_t inv = 0;
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t const row = nec * i;
        for (a_uint_t j = 0; j != nec; ++j)
        {
            a_uint_t const idx = row + j; /* mat(i,j)=f(e[i],ec[j]) */
            mat[idx] = ctx->op(ctx->val[i], ctx->val[ne + j]);
            inv += mat[idx];
        }
    }
    inv = 1 / inv;
    /* mean of centers defuzzifier */
    a_real_t qv[3] = {0, 0, 0};
    if (ctx->mkp)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const row = nec * i;
            a_uint_t const idx = col * ctx->idx[i];
            for (a_uint_t j = 0; j != nec; ++j) /* mat(i,j) * kp(e[i],ec[j]) */
            {
                qv[0] += mat[row + j] * ctx->mkp[idx + ctx->idx[ne + j]];
            }
        }
        qv[0] *= inv;
    }
    if (ctx->mki)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const row = nec * i;
            a_uint_t const idx = col * ctx->idx[i];
            for (a_uint_t j = 0; j != nec; ++j) /* mat(i,j) * ki(e[i],ec[j]) */
            {
                qv[1] += mat[row + j] * ctx->mki[idx + ctx->idx[ne + j]];
            }
        }
        qv[1] *= inv;
    }
    if (ctx->mkd)
    {
        for (a_uint_t i = 0; i != ne; ++i)
        {
            a_uint_t const row = nec * i;
            a_uint_t const idx = col * ctx->idx[i];
            for (a_uint_t j = 0; j != nec; ++j) /* mat(i,j) * kd(e[i],ec[j]) */
            {
                qv[2] += mat[row + j] * ctx->mkd[idx + ctx->idx[ne + j]];
            }
        }
        qv[2] *= inv;
    }
    a_pid_kpid(&ctx->pid, ctx->kp + qv[0], ctx->ki + qv[1], ctx->kd + qv[2]);
}

a_real_t a_fpid_outf(a_fpid_s *const ctx, a_real_t const set, a_real_t const fdb)
{
    a_real_t const e = set - fdb;
    a_real_t const ec = e - ctx->pid.e.f;
    a_fpid_iter_(ctx, a_fpid_col(ctx), ec, e);
    return a_pid_outf_(&ctx->pid, a_pid_mode(&ctx->pid), set, fdb, ec, e);
}

a_real_t const *a_fpid_outp(a_fpid_s *const ctx, a_real_t const *const set, a_real_t const *const fdb)
{
    a_uint_t const col = a_fpid_col(ctx);
    a_uint_t const num = a_pid_num(&ctx->pid);
    a_uint_t const mode = a_pid_mode(&ctx->pid);
    for (a_uint_t i = 0; i != num; ++i)
    {
        a_real_t const e = set[i] - fdb[i];
        a_real_t const ec = e - ctx->pid.e.p[i];
        a_fpid_iter_(ctx, col, ec, e);
        a_pid_outp_(&ctx->pid, mode, set[i], fdb[i], ec, e, i);
    }
    return ctx->pid.out.p;
}
