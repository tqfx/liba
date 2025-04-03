#include "a/trajbell.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_real a_trajbell_gen(a_trajbell *ctx, a_real jm, a_real am, a_real vm,
                      a_real p0, a_real p1, a_real v0, a_real v1)
{
    a_real p, ac, tj, _2tj, _2v0, _2v1, _tmp, temp, v0pv1, _2v02pv12;
    if (jm < 0) { jm = -jm; }
    if (am < 0) { am = -am; }
    if (vm < 0) { vm = -vm; }
    v0 = A_SAT(v0, -vm, +vm);
    v1 = A_SAT(v1, -vm, +vm);
    ctx->p0 = p0;
    ctx->p1 = p1;
    ctx->v0 = v0;
    ctx->v1 = v1;
    if (p0 > p1)
    {
        p0 = -p0;
        p1 = -p1;
        v0 = -v0;
        v1 = -v1;
    }
    ctx->vm = vm;
    ctx->jm = jm;
    _tmp = am * am;
    _2v0 = vm - v0;
    if (_2v0 * jm < _tmp)
    {
        ctx->taj = a_real_sqrt(_2v0 / jm);
        ctx->ta = 2 * ctx->taj;
        ctx->am = +jm * ctx->taj;
    }
    else
    {
        ctx->taj = am / jm;
        ctx->ta = ctx->taj + _2v0 / am;
        ctx->am = +am;
    }
    _2v1 = vm - v1;
    if (_2v1 * jm < _tmp)
    {
        ctx->tdj = a_real_sqrt(_2v1 / jm);
        ctx->td = 2 * ctx->tdj;
        ctx->dm = -jm * ctx->tdj;
    }
    else
    {
        ctx->tdj = am / jm;
        ctx->td = ctx->tdj + _2v1 / am;
        ctx->dm = -am;
    }
    p = p1 - p0;
    ctx->tv = p / vm - A_REAL_C(0.5) * ctx->ta * (1 + v0 / vm) - A_REAL_C(0.5) * ctx->td * (1 + v1 / vm);
    if (ctx->tv > 0) { goto exit; }
    ctx->tv = 0;
    _2v0 = 2 * v0;
    _2v1 = 2 * v1;
    v0pv1 = v0 + v1;
    ctx->am = ac = am;
    ctx->dm = ac * A_REAL_C(0.0625);
    _2v02pv12 = 2 * (v0 * v0 + v1 * v1);
    do {
        tj = am / jm;
        _2tj = 2 * tj;
        ctx->taj = tj;
        ctx->tdj = tj;
        _tmp = am * tj;
        temp = _tmp * _tmp + _2v02pv12 + (4 * p - _2tj * v0pv1) * am;
        _tmp += a_real_sqrt(temp);
        temp = 2 * am;
        ctx->ta = (_tmp - _2v0) / temp;
        if (ctx->ta < 0)
        {
            if (am == ctx->am || ac < ctx->dm)
            {
                ctx->ta = 0;
                ctx->taj = 0;
                ctx->td = 2 * p / v0pv1;
                _tmp = jm * p;
                temp = jm * (_tmp * p + (v1 - v0) * v0pv1 * v0pv1);
                if (temp < 0) { goto fail; }
                ctx->tdj = (_tmp - a_real_sqrt(temp)) / (jm * v0pv1);
                ctx->am = 0;
                ctx->dm = -jm * ctx->tdj;
                ctx->vm = v0;
                goto exit;
            }
            ac *= A_REAL_C(0.5);
            am += ac;
            continue;
        }
        ctx->td = (_tmp - _2v1) / temp;
        if (ctx->td < 0)
        {
            if (am == ctx->am || ac < ctx->dm)
            {
                ctx->td = 0;
                ctx->tdj = 0;
                ctx->ta = 2 * p / v0pv1;
                _tmp = jm * p;
                temp = jm * (_tmp * p + (v0 - v1) * v0pv1 * v0pv1);
                if (temp < 0) { goto fail; }
                ctx->taj = (_tmp - a_real_sqrt(temp)) / (jm * v0pv1);
                ctx->am = +jm * ctx->taj;
                ctx->dm = 0;
                ctx->vm = v0 + ctx->am * (ctx->ta - ctx->taj);
                goto exit;
            }
            ac *= A_REAL_C(0.5);
            am += ac;
            continue;
        }
        if (ctx->ta >= _2tj && ctx->td >= _2tj)
        {
            if (am == ctx->am || ac < ctx->dm)
            {
                ctx->am = +am;
                ctx->dm = -am;
                ctx->vm = v0 + ctx->am * (ctx->ta - tj);
                goto exit;
            }
            ac *= A_REAL_C(0.5);
            am += ac;
            continue;
        }
        ac *= A_REAL_C(0.5);
        am -= ac;
    } while (ac > A_REAL_EPSILON);
fail:
    ctx->t = 0;
    return 0;
exit:
    ctx->t = ctx->ta + ctx->tv + ctx->td;
    return ctx->t;
}

a_real a_trajbell_pos(a_trajbell const *ctx, a_real x)
{
    a_real y;
    a_real p0 = ctx->p0;
    a_real p1 = ctx->p1;
    a_real v0 = ctx->v0;
    a_real v1 = ctx->v1;
    int const rev = ctx->p0 > ctx->p1;
    if (rev)
    {
        p0 = -p0;
        p1 = -p1;
        v0 = -v0;
        v1 = -v1;
    }
    if (x < ctx->ta)
    {
        if (x < ctx->taj)
        {
            if (x <= 0) { return ctx->p0; }
            y = p0 + v0 * x + ctx->jm * x * x * x / 6;
            goto exit;
        }
        if (x < ctx->ta - ctx->taj)
        {
            y = p0 + v0 * x + ctx->am * (3 * x * x - 3 * x * ctx->taj + ctx->taj * ctx->taj) / 6;
            goto exit;
        }
        x = ctx->ta - x;
        y = p0 + A_REAL_C(0.5) * (ctx->vm + v0) * ctx->ta - ctx->vm * x + ctx->jm * x * x * x / 6;
        goto exit;
    }
    if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x < ctx->ta + ctx->tv)
        {
            y = p0 + A_REAL_C(0.5) * (ctx->vm + v0) * ctx->ta + ctx->vm * (x - ctx->ta);
            goto exit;
        }
        x -= ctx->t - ctx->td;
        y = p1 - A_REAL_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * x - ctx->jm * x * x * x / 6;
        goto exit;
    }
    if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            x -= ctx->t - ctx->td;
            y = p1 - A_REAL_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * x +
                ctx->dm * (3 * x * x - 3 * x * ctx->tdj + ctx->tdj * ctx->tdj) / 6;
            goto exit;
        }
        x = ctx->t - x;
        y = p1 - v1 * x - ctx->jm * x * x * x / 6;
        goto exit;
    }
    return ctx->p1;
exit:
    if (rev) { y = -y; }
    return y;
}

a_real a_trajbell_vel(a_trajbell const *ctx, a_real x)
{
    a_real y;
    a_real v0 = ctx->v0;
    a_real v1 = ctx->v1;
    int const rev = ctx->p0 > ctx->p1;
    if (rev)
    {
        v0 = -v0;
        v1 = -v1;
    }
    if (x < ctx->ta)
    {
        if (x < ctx->taj)
        {
            if (x <= 0) { return ctx->v0; }
            y = v0 + A_REAL_C(0.5) * ctx->jm * x * x;
            goto exit;
        }
        if (x < ctx->ta - ctx->taj)
        {
            y = v0 + ctx->am * (x - A_REAL_C(0.5) * ctx->taj);
            goto exit;
        }
        x = ctx->ta - x;
        y = ctx->vm - A_REAL_C(0.5) * ctx->jm * x * x;
        goto exit;
    }
    if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x < ctx->ta + ctx->tv)
        {
            y = ctx->vm;
            goto exit;
        }
        x -= ctx->t - ctx->td;
        y = ctx->vm - A_REAL_C(0.5) * ctx->jm * x * x;
        goto exit;
    }
    if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            y = ctx->vm + ctx->dm * (x - ctx->t + ctx->td - A_REAL_C(0.5) * ctx->tdj);
            goto exit;
        }
        x = ctx->t - x;
        y = v1 + A_REAL_C(0.5) * ctx->jm * x * x;
        goto exit;
    }
    return ctx->v1;
exit:
    if (rev) { y = -y; }
    return y;
}

a_real a_trajbell_acc(a_trajbell const *ctx, a_real x)
{
    a_real y;
    if (x < ctx->ta)
    {
        if (x >= ctx->taj)
        {
            if (x < ctx->ta - ctx->taj)
            {
                y = ctx->am;
                goto exit;
            }
            y = ctx->jm * (ctx->ta - x);
            goto exit;
        }
        if (x > 0)
        {
            y = ctx->jm * x;
            goto exit;
        }
    }
    else if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x >= ctx->ta + ctx->tv)
        {
            y = -ctx->jm * (x - ctx->t + ctx->td);
            goto exit;
        }
    }
    else if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            y = ctx->dm;
            goto exit;
        }
        y = -ctx->jm * (ctx->t - x);
        goto exit;
    }
    return 0;
exit:
    if (ctx->p0 > ctx->p1)
    {
        y = -y;
    }
    return y;
}

a_real a_trajbell_jer(a_trajbell const *ctx, a_real x)
{
    a_real y;
    if (x < ctx->ta)
    {
        if (x >= ctx->ta - ctx->taj)
        {
            y = -ctx->jm;
            goto exit;
        }
        if (x < ctx->taj && x >= 0)
        {
            y = +ctx->jm;
            goto exit;
        }
    }
    else if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x >= ctx->ta + ctx->tv)
        {
            y = -ctx->jm;
            goto exit;
        }
    }
    else if (x <= ctx->t)
    {
        if (x >= ctx->t - ctx->tdj)
        {
            y = +ctx->jm;
            goto exit;
        }
    }
    return 0;
exit:
    if (ctx->p0 > ctx->p1)
    {
        y = -y;
    }
    return y;
}
