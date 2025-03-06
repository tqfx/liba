#include "a/pid_fuzzy.h"
#include "a/mf.h"

a_real (*a_pid_fuzzy_opr(unsigned int opr))(a_real, a_real)
{
    switch (opr)
    {
    default:
    case A_PID_FUZZY_EQU:
        return a_fuzzy_equ;
    case A_PID_FUZZY_CAP:
        return a_fuzzy_cap;
    case A_PID_FUZZY_CAP_ALGEBRA:
        return a_fuzzy_cap_algebra;
    case A_PID_FUZZY_CAP_BOUNDED:
        return a_fuzzy_cap_bounded;
    case A_PID_FUZZY_CUP:
        return a_fuzzy_cup;
    case A_PID_FUZZY_CUP_ALGEBRA:
        return a_fuzzy_cup_algebra;
    case A_PID_FUZZY_CUP_BOUNDED:
        return a_fuzzy_cup_bounded;
    }
}

void a_pid_fuzzy_set_opr(a_pid_fuzzy *ctx, unsigned int opr) { ctx->opr = a_pid_fuzzy_opr(opr); }

A_HIDDEN unsigned int a_pid_fuzzy_mf(a_real x, unsigned int n, a_real const *a, unsigned int *idx, a_real *val);
unsigned int a_pid_fuzzy_mf(a_real x, unsigned int n, a_real const *a, unsigned int *idx, a_real *val)
{
    unsigned int i;
    unsigned int counter = 0;
    for (i = 0; i != n; ++i)
    {
        a_real y = 0;
        switch ((int)*a++)
        {
        default:
        case A_MF_NUL: goto out;
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
        }
        if (y > A_REAL_EPSILON)
        {
            *idx++ = i;
            *val++ = y;
            ++counter;
        }
    }
out:
    return counter;
}

void a_pid_fuzzy_set_rule(a_pid_fuzzy *ctx, unsigned int nrule, a_real const *me, a_real const *mec,
                          a_real const *mkp, a_real const *mki, a_real const *mkd)
{
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    ctx->nrule = nrule;
}

void *a_pid_fuzzy_bfuzz(a_pid_fuzzy const *ctx) { return ctx->idx; }
void a_pid_fuzzy_set_bfuzz(a_pid_fuzzy *ctx, void *ptr, a_size num)
{
    ctx->nfuzz = (unsigned int)num;
    ctx->idx = (unsigned int *)ptr;
    if (ptr) { ptr = (a_byte *)ptr + 2 * sizeof(unsigned int) * num; }
    ctx->val = (a_real *)ptr;
}

void a_pid_fuzzy_set_kpid(a_pid_fuzzy *ctx, a_real kp, a_real ki, a_real kd)
{
    a_pid_set_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN void a_pid_fuzzy_out_(a_pid_fuzzy *ctx, a_real ec, a_real e);
void a_pid_fuzzy_out_(a_pid_fuzzy *ctx, a_real ec, a_real e)
{
    unsigned int *idx, ne, nec;
    a_real *val, *mat, inv = 0;
    a_real kp = 0, ki = 0, kd = 0;
    /* compute membership */
    idx = ctx->idx;
    val = ctx->val;
    ne = a_pid_fuzzy_mf(e, ctx->nrule, ctx->me, idx, val);
    if (!ne) { goto pid; }
    idx = idx + ne;
    val = val + ne;
    nec = a_pid_fuzzy_mf(ec, ctx->nrule, ctx->mec, idx, val);
    if (!nec) { goto pid; }
    mat = val + nec;
    /* joint membership */
    {
        unsigned int i;
        a_real *it = mat;
        for (i = 0; i != ne; ++i)
        {
            unsigned int ii;
            for (ii = 0; ii != nec; ++ii)
            {
                *it = ctx->opr(ctx->val[i], val[ii]); /* mat(i,ii)=f(e[i],ec[ii]) */
                inv += *it++;
            }
            ctx->idx[i] *= ctx->nrule;
        }
        inv = 1 / inv;
    }
    /* mean of centers defuzzifier */
    if (ctx->mkp)
    {
        unsigned int i;
        a_real const *it = mat;
        for (i = 0; i != ne; ++i)
        {
            unsigned int ii;
            a_real const *const mkp = ctx->mkp + ctx->idx[i];
            for (ii = 0; ii != nec; ++ii)
            {
                kp += *it++ * mkp[idx[ii]]; /* += mat(i,ii) * mkp(e[i],ec[ii]) */
            }
        }
        kp *= inv;
    }
    if (ctx->mki)
    {
        unsigned int i;
        a_real const *it = mat;
        for (i = 0; i != ne; ++i)
        {
            unsigned int ii;
            a_real const *const mki = ctx->mki + ctx->idx[i];
            for (ii = 0; ii != nec; ++ii)
            {
                ki += *it++ * mki[idx[ii]]; /* += mat(i,ii) * mki(e[i],ec[ii]) */
            }
        }
        ki *= inv;
    }
    if (ctx->mkd)
    {
        unsigned int i;
        a_real const *it = mat;
        for (i = 0; i != ne; ++i)
        {
            unsigned int ii;
            a_real const *const mkd = ctx->mkd + ctx->idx[i];
            for (ii = 0; ii != nec; ++ii)
            {
                kd += *it++ * mkd[idx[ii]]; /* += mat(i,ii) * mkd(e[i],ec[ii]) */
            }
        }
        kd *= inv;
    }
pid:
    a_pid_set_kpid(&ctx->pid, ctx->kp + kp, ctx->ki + ki, ctx->kd + kd);
}

A_HIDDEN a_real a_pid_run_(a_pid *ctx, a_real set, a_real fdb, a_real err);
a_real a_pid_fuzzy_run(a_pid_fuzzy *ctx, a_real set, a_real fdb)
{
    a_real const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_run_(&ctx->pid, set, fdb, err);
}

A_HIDDEN a_real a_pid_pos_(a_pid *ctx, a_real fdb, a_real err);
a_real a_pid_fuzzy_pos(a_pid_fuzzy *ctx, a_real set, a_real fdb)
{
    a_real const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_pos_(&ctx->pid, fdb, err);
}

A_HIDDEN a_real a_pid_inc_(a_pid *ctx, a_real fdb, a_real err);
a_real a_pid_fuzzy_inc(a_pid_fuzzy *ctx, a_real set, a_real fdb)
{
    a_real const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_inc_(&ctx->pid, fdb, err);
}

void a_pid_fuzzy_zero(a_pid_fuzzy *ctx) { a_pid_zero(&ctx->pid); }
