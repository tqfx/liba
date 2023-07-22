#define LIBA_PID_FUZZY_C
#include "fuzzy.h"
#include "a/math.h"

a_float_t a_pid_fuzzy_op_or(a_float_t const l, a_float_t const r) { return l + r - l * r; }

a_float_t a_pid_fuzzy_op_and(a_float_t const l, a_float_t const r) { return l * r; }

a_float_t a_pid_fuzzy_op_equ(a_float_t const l, a_float_t const r)
{
    return a_float_sqrt(l * r) * a_float_sqrt(1 - (1 - l) * (1 - r));
}

a_float_t (*a_pid_fuzzy_op(unsigned int const op))(a_float_t, a_float_t)
{
    switch (op)
    {
    case A_PID_FUZZY_OR_ALGEBRA:
        return a_pid_fuzzy_op_or;
    case A_PID_FUZZY_OR_BOUNDED:
    case A_PID_FUZZY_AND_DEFAULT:
        return a_float_min;
    case A_PID_FUZZY_AND_ALGEBRA:
        return a_pid_fuzzy_op_and;
    case A_PID_FUZZY_AND_BOUNDED:
    case A_PID_FUZZY_OR_DEFAULT:
        return a_float_max;
    case A_PID_FUZZY_EQU:
    default:
        return a_pid_fuzzy_op_equ;
    }
}

void a_pid_fuzzy_set_op(a_pid_fuzzy_s *const ctx, unsigned int const op)
{
    ctx->op = a_pid_fuzzy_op(op);
}

unsigned int a_pid_fuzzy_mf(a_float_t const x, unsigned int const n, a_float_t const *a, unsigned int *idx, a_float_t *val)
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i != n; ++i)
    {
        a_float_t y = 0;
        switch ((unsigned int)*a++)
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
            *idx++ = i;
            *val++ = y;
            ++counter;
        }
    }
out:
    return counter;
}

void a_pid_fuzzy_init(a_pid_fuzzy_s *const ctx, unsigned int const num)
{
    a_pid_init(&ctx->pid, num);
}

void a_pid_fuzzy_chan(a_pid_fuzzy_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err)
{
    a_pid_chan(&ctx->pid, num, out, fdb, tmp, err);
}

void a_pid_fuzzy_rule(a_pid_fuzzy_s *const ctx, unsigned int const col, a_float_t const *const me, a_float_t const *const mec,
                      a_float_t const *const mkp, a_float_t const *const mki, a_float_t const *const mkd)
{
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    ctx->col = col;
}

void a_pid_fuzzy_kpid(a_pid_fuzzy_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

void a_pid_fuzzy_buf1(a_pid_fuzzy_s *const ctx, void *ptr, a_size_t const num)
{
    ctx->buf = (unsigned int)num;
    ctx->idx = (unsigned int *)ptr;
    ptr = (a_byte_t *)ptr + sizeof(unsigned int) * 2 * num;
    ctx->val = (a_float_t *)ptr;
}

void a_pid_fuzzy_buff(a_pid_fuzzy_s *const ctx, unsigned int *const idx, a_float_t *const val)
{
    ctx->idx = idx;
    ctx->val = val;
}

void a_pid_fuzzy_zero(a_pid_fuzzy_s *const ctx)
{
    a_pid_zero(&ctx->pid);
}

void a_pid_fuzzy_out_(a_pid_fuzzy_s *const ctx, a_float_t const ec, a_float_t const e)
{
    a_float_t kp = 0;
    a_float_t ki = 0;
    a_float_t kd = 0;
    /* calculate membership */
    unsigned int const ne = a_pid_fuzzy_mf(e, ctx->col, ctx->me, ctx->idx, ctx->val);
    if (!ne)
    {
        goto pid;
    }
    unsigned int const nec = a_pid_fuzzy_mf(ec, ctx->col, ctx->mec, ctx->idx + ne, ctx->val + ne);
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
            unsigned int const idx = ctx->col * ctx->idx[i];
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
            unsigned int const idx = ctx->col * ctx->idx[i];
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
            unsigned int const idx = ctx->col * ctx->idx[i];
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
    a_float_t const ec = e - ctx->pid.err.f;
    a_pid_fuzzy_out_(ctx, ec, e);
    a_pid_outf_(&ctx->pid, set, fdb, ec, e);
    return ctx->pid.out.f;
}

a_float_t const *a_pid_fuzzy_outp(a_pid_fuzzy_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    for (unsigned int i = 0; i != ctx->pid.chan; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_float_t const ec = e - ctx->pid.err.p[i];
        a_pid_fuzzy_out_(ctx, ec, e);
        a_pid_outp_(&ctx->pid, set[i], fdb[i], ec, e, i);
    }
    return ctx->pid.out.p;
}

a_float_t const *a_pid_fuzzy_iter(a_pid_fuzzy_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    if (ctx->pid.chan)
    {
        return a_pid_fuzzy_outp(ctx, set, fdb);
    }
    a_pid_fuzzy_outf(ctx, *set, *fdb);
    return &ctx->pid.out.f;
}
