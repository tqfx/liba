#include "a/pid/fuzzy.h"
#include "a/fuzzy.h"
#include "a/math.h"
#include "a/mf.h"

A_HIDDEN a_float_t a_pid_fuzzy_equ(a_float_t a, a_float_t b);
a_float_t a_pid_fuzzy_equ(a_float_t const a, a_float_t const b)
{
    return a_float_sqrt(a * b) * a_float_sqrt(1 - (1 - a) * (1 - b));
}

a_float_t (*a_pid_fuzzy_op(unsigned int const op))(a_float_t, a_float_t)
{
    switch (op)
    {
    case A_PID_FUZZY_CUP_BOUNDED:
        return a_fuzzy_cup_bounded;
    case A_PID_FUZZY_CUP_ALGEBRA:
        return a_fuzzy_cup_algebra;
    case A_PID_FUZZY_CUP:
        return a_fuzzy_cup;
    case A_PID_FUZZY_CAP_BOUNDED:
        return a_fuzzy_cap_bounded;
    case A_PID_FUZZY_CAP_ALGEBRA:
        return a_fuzzy_cap_algebra;
    case A_PID_FUZZY_CAP:
        return a_fuzzy_cap;
    case A_PID_FUZZY_EQU:
    default:
        return a_pid_fuzzy_equ;
    }
}

void a_pid_fuzzy_set_op(a_pid_fuzzy_s *const ctx, unsigned int const op)
{
    ctx->op = a_pid_fuzzy_op(op);
}

A_HIDDEN unsigned int a_pid_fuzzy_mf(a_float_t x, unsigned int n, a_float_t const *a, unsigned int *idx, a_float_t *val);
unsigned int a_pid_fuzzy_mf(a_float_t const x, unsigned int const n, a_float_t const *a, unsigned int *idx, a_float_t *val)
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i != n; ++i)
    {
        a_float_t y = 0;
        switch ((int)*a++)
        {
        case A_MF_GAUSS:
            y = a_mf_gauss(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_GAUSS2:
            y = a_mf_gauss2(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_GBELL:
            y = a_mf_gbell(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_SIG:
            y = a_mf_sig(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_DSIG:
            y = a_mf_dsig(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_PSIG:
            y = a_mf_psig(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_TRAP:
            y = a_mf_trap(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_TRI:
            y = a_mf_tri(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_LINS:
            y = a_mf_lins(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_LINZ:
            y = a_mf_linz(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_S:
            y = a_mf_s(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_Z:
            y = a_mf_z(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_PI:
            y = a_mf_pi(x, a[0], a[1], a[2], a[3]);
            a += 4;
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

void a_pid_fuzzy_zero(a_pid_fuzzy_s *const ctx)
{
    a_pid_zero(&ctx->pid);
}

void a_pid_fuzzy_init(a_pid_fuzzy_s *const ctx)
{
    a_pid_init(&ctx->pid);
}

void a_pid_fuzzy_rule(a_pid_fuzzy_s *const ctx, unsigned int const order, a_float_t const *const me, a_float_t const *const mec,
                      a_float_t const *const mkp, a_float_t const *const mki, a_float_t const *const mkd)
{
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    ctx->order = order;
}

void *a_pid_fuzzy_joint(a_pid_fuzzy_s *const ctx) { return ctx->idx; }
void a_pid_fuzzy_set_joint(a_pid_fuzzy_s *const ctx, void *ptr, a_size_t const num)
{
    ctx->joint = (unsigned int)num;
    ctx->idx = (unsigned int *)ptr;
    ptr = (a_byte_t *)ptr + sizeof(unsigned int) * 2 * num;
    ctx->val = (a_float_t *)ptr;
}

void a_pid_fuzzy_kpid(a_pid_fuzzy_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN void a_pid_fuzzy_out_(a_pid_fuzzy_s *const ctx, a_float_t ec, a_float_t e);
void a_pid_fuzzy_out_(a_pid_fuzzy_s *const ctx, a_float_t const ec, a_float_t const e)
{
    a_float_t kp = 0;
    a_float_t ki = 0;
    a_float_t kd = 0;
    /* calculate membership */
    unsigned int const ne = a_pid_fuzzy_mf(e, ctx->order, ctx->me, ctx->idx, ctx->val);
    if (!ne)
    {
        goto pid;
    }
    unsigned int *const idx = ctx->idx + ne;
    a_float_t *const val = ctx->val + ne;
    unsigned int const nec = a_pid_fuzzy_mf(ec, ctx->order, ctx->mec, idx, val);
    if (!nec)
    {
        goto pid;
    }
    a_float_t *const mat = val + nec;
    /* joint membership */
    a_float_t inv = 0;
    {
        a_float_t *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            for (unsigned int j = 0; j != nec; ++j)
            {
                *it = ctx->op(ctx->val[i], val[j]); /* mat(i,j)=f(e[i],ec[j]) */
                inv += *it++;
            }
            ctx->idx[i] *= ctx->order;
        }
    }
    inv = 1 / inv;
    /* mean of centers defuzzifier */
    if (ctx->mkp)
    {
        a_float_t const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float_t const *const mkp = ctx->mkp + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                kp += *it++ * mkp[idx[j]]; /* += mat(i,j) * mkp(e[i],ec[j]) */
            }
        }
        kp *= inv;
    }
    if (ctx->mki)
    {
        a_float_t const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float_t const *const mki = ctx->mki + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                ki += *it++ * mki[idx[j]]; /* += mat(i,j) * mki(e[i],ec[j]) */
            }
        }
        ki *= inv;
    }
    if (ctx->mkd)
    {
        a_float_t const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float_t const *const mkd = ctx->mkd + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                kd += *it++ * mkd[idx[j]]; /* += mat(i,j) * mkd(e[i],ec[j]) */
            }
        }
        kd *= inv;
    }
pid:
    a_pid_kpid(&ctx->pid, ctx->kp + kp, ctx->ki + ki, ctx->kd + kd);
}

A_HIDDEN a_float_t a_pid_off_(a_pid_s *ctx, a_float_t set, a_float_t fdb, a_float_t err);
a_float_t a_pid_fuzzy_off(a_pid_fuzzy_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_off_(&ctx->pid, set, fdb, err);
}

A_HIDDEN a_float_t a_pid_pos_(a_pid_s *ctx, a_float_t fdb, a_float_t err);
a_float_t a_pid_fuzzy_pos(a_pid_fuzzy_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_pos_(&ctx->pid, fdb, err);
}

A_HIDDEN a_float_t a_pid_inc_(a_pid_s *ctx, a_float_t fdb, a_float_t err);
a_float_t a_pid_fuzzy_inc(a_pid_fuzzy_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_inc_(&ctx->pid, fdb, err);
}
