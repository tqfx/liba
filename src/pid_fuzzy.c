#define LIBA_PID_FUZZY_C
#include "pid_fuzzy.h"

a_float_t a_pid_fuzzy_op_or(a_float_t const l, a_float_t const r) { return l + r - l * r; }

a_float_t a_pid_fuzzy_op_and(a_float_t const l, a_float_t const r) { return l * r; }

a_float_t a_pid_fuzzy_op_equ(a_float_t const l, a_float_t const r)
{
    return a_float_sqrt(l * r) * a_float_sqrt(1 - (1 - l) * (1 - r));
}

void a_pid_fuzzy_set_op(a_pid_fuzzy_s *const ctx, unsigned int op)
{
    op &= A_PID_FUZZY_MSK;
    ctx->pid.reg = (~A_PID_FUZZY_MSK & ctx->pid.reg) | op;
    switch (op)
    {
    case A_PID_FUZZY_OR_ALGEBRA:
        ctx->op = a_pid_fuzzy_op_or;
        break;
    case A_PID_FUZZY_OR_BOUNDED:
    case A_PID_FUZZY_AND_DEFAULT:
        ctx->op = a_float_min;
        break;
    case A_PID_FUZZY_AND_ALGEBRA:
        ctx->op = a_pid_fuzzy_op_and;
        break;
    case A_PID_FUZZY_AND_BOUNDED:
    case A_PID_FUZZY_OR_DEFAULT:
        ctx->op = a_float_max;
        break;
    case A_PID_FUZZY_EQU:
    default:
        ctx->op = a_pid_fuzzy_op_equ;
    }
}

unsigned int a_pid_fuzzy_mf(a_float_t const *a, a_float_t const x, unsigned int *idx, a_float_t *val)
{
    int e = A_MF_NUL;
    unsigned int num = 0;
    for (unsigned int i = 0; (void)(e = (int)*a++), e != A_MF_NUL; ++i)
    {
        a_float_t y = 0;
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
        if (y > A_FLOAT_EPSILON)
        {
            ++num;
            *idx++ = i;
            *val++ = y;
        }
    }
out:
    return num;
}

a_pid_fuzzy_s *a_pid_fuzzy_off(a_pid_fuzzy_s *const ctx)
{
    a_pid_off(&ctx->pid);
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_inc(a_pid_fuzzy_s *const ctx)
{
    a_pid_inc(&ctx->pid);
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_pos(a_pid_fuzzy_s *const ctx, a_float_t const max)
{
    a_pid_pos(&ctx->pid, max);
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_kpid(a_pid_fuzzy_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_buf1(a_pid_fuzzy_s *const ctx, void *ptr, a_size_t max)
{
    a_pid_fuzzy_set_bufmax(ctx, (unsigned int)max);
    ctx->idx = (unsigned int *)ptr;
    ptr = (a_byte_t *)ptr + sizeof(unsigned int) * 2 * max;
    ctx->val = (a_float_t *)ptr;
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_buff(a_pid_fuzzy_s *const ctx, unsigned int *const idx, a_float_t *const val)
{
    ctx->idx = idx;
    ctx->val = val;
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_chan(a_pid_fuzzy_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb,
                                a_float_t *const sum, a_float_t *const ec, a_float_t *const e)
{
    a_pid_chan(&ctx->pid, num, out, fdb, sum, ec, e);
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_base(a_pid_fuzzy_s *const ctx, unsigned int const col, a_float_t const *const me, a_float_t const *const mec,
                                a_float_t const *const mkp, a_float_t const *const mki, a_float_t const *const mkd)
{
    a_pid_fuzzy_set_col(ctx, col);
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_init(a_pid_fuzzy_s *const ctx, a_float_t const dt, unsigned int const col, a_float_t const *const me, a_float_t const *const mec,
                                a_float_t const *const mkp, a_float_t const *const mki, a_float_t const *const mkd, a_float_t const min, a_float_t const max)
{
    a_pid_init(&ctx->pid, dt, min, max);
    a_pid_fuzzy_base(ctx, col, me, mec, mkp, mki, mkd);
    ctx->op = a_pid_fuzzy_op_equ;
    ctx->idx = A_NULL;
    ctx->val = A_NULL;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return ctx;
}

a_pid_fuzzy_s *a_pid_fuzzy_exit(a_pid_fuzzy_s *const ctx) { return a_pid_fuzzy_zero(ctx); }

a_pid_fuzzy_s *a_pid_fuzzy_zero(a_pid_fuzzy_s *const ctx)
{
    a_pid_zero(&ctx->pid);
    return ctx;
}

static void a_pid_fuzzy_iter_(a_pid_fuzzy_s *const ctx, unsigned int const col, a_float_t ec, a_float_t e)
{
    a_float_t kp = 0;
    a_float_t ki = 0;
    a_float_t kd = 0;
    /* calculate membership */
    unsigned int const ne = a_pid_fuzzy_mf(ctx->me, e, ctx->idx, ctx->val);
    if (!ne)
    {
        goto pid;
    }
    unsigned int const nec = a_pid_fuzzy_mf(ctx->mec, ec, ctx->idx + ne, ctx->val + ne);
    if (!nec)
    {
        goto pid;
    }
    a_float_t *const mat = ctx->val + ne + nec;
    /* joint membership */
    a_float_t inv = 0;
    for (unsigned int i = 0; i != ne; ++i)
    {
        unsigned int const row = nec * i;
        for (unsigned int j = 0; j != nec; ++j)
        {
            unsigned int const idx = row + j; /* mat(i,j)=f(e[i],ec[j]) */
            mat[idx] = ctx->op(ctx->val[i], ctx->val[ne + j]);
            inv += mat[idx];
        }
    }
    inv = 1 / inv;
    /* mean of centers defuzzifier */
    if (ctx->mkp)
    {
        for (unsigned int i = 0; i != ne; ++i)
        {
            unsigned int const row = nec * i;
            unsigned int const idx = col * ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j) /* mat(i,j) * kp(e[i],ec[j]) */
            {
                kp += mat[row + j] * ctx->mkp[idx + ctx->idx[ne + j]];
            }
        }
        kp *= inv;
    }
    if (ctx->mki)
    {
        for (unsigned int i = 0; i != ne; ++i)
        {
            unsigned int const row = nec * i;
            unsigned int const idx = col * ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j) /* mat(i,j) * ki(e[i],ec[j]) */
            {
                ki += mat[row + j] * ctx->mki[idx + ctx->idx[ne + j]];
            }
        }
        ki *= inv;
    }
    if (ctx->mkd)
    {
        for (unsigned int i = 0; i != ne; ++i)
        {
            unsigned int const row = nec * i;
            unsigned int const idx = col * ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j) /* mat(i,j) * kd(e[i],ec[j]) */
            {
                kd += mat[row + j] * ctx->mkd[idx + ctx->idx[ne + j]];
            }
        }
        kd *= inv;
    }
pid:
    a_pid_kpid(&ctx->pid, ctx->kp + kp, ctx->ki + ki, ctx->kd + kd);
}

a_float_t a_pid_fuzzy_outf(a_pid_fuzzy_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_float_t const ec = e - ctx->pid.e.f;
    a_pid_fuzzy_iter_(ctx, a_pid_fuzzy_col(ctx), ec, e);
    return a_pid_outf_(&ctx->pid, a_pid_mode(&ctx->pid), set, fdb, ec, e);
}

a_float_t const *a_pid_fuzzy_outp(a_pid_fuzzy_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    unsigned int const col = a_pid_fuzzy_col(ctx);
    unsigned int const num = a_pid_num(&ctx->pid);
    unsigned int const mode = a_pid_mode(&ctx->pid);
    for (unsigned int i = 0; i != num; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_float_t const ec = e - ctx->pid.e.p[i];
        a_pid_fuzzy_iter_(ctx, col, ec, e);
        a_pid_outp_(&ctx->pid, mode, set[i], fdb[i], ec, e, i);
    }
    return ctx->pid.out.p;
}
