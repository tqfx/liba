#include "a/trajbell.h"
#include "a/math.h"

#if A_PREREQ_GNUC(3, 0) || __has_warning("-Wfloat-equal")
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif /* -Wfloat-equal */

a_float a_trajbell_gen(a_trajbell *ctx, a_float jm, a_float am, a_float vm,
                       a_float p0, a_float p1, a_float v0, a_float v1)
{
    a_float p, ac, tj, _2tj, _2v0, _2v1, _tmp, temp, v0pv1, _2v02pv12;
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
        ctx->taj = a_float_sqrt(_2v0 / jm);
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
        ctx->tdj = a_float_sqrt(_2v1 / jm);
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
    ctx->tv = p / vm - A_FLOAT_C(0.5) * ctx->ta * (1 + v0 / vm) - A_FLOAT_C(0.5) * ctx->td * (1 + v1 / vm);
    if (ctx->tv > 0) { goto out; }
    ctx->tv = 0;
    _2v0 = 2 * v0;
    _2v1 = 2 * v1;
    v0pv1 = v0 + v1;
    ctx->am = ac = am;
    ctx->dm = ac * A_FLOAT_C(0.0625);
    _2v02pv12 = 2 * (v0 * v0 + v1 * v1);
    do {
        tj = am / jm;
        _2tj = 2 * tj;
        ctx->taj = tj;
        ctx->tdj = tj;
        _tmp = am * tj;
        temp = _tmp * _tmp + _2v02pv12 + (4 * p - _2tj * v0pv1) * am;
        _tmp += a_float_sqrt(temp);
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
                ctx->tdj = (_tmp - a_float_sqrt(temp)) / (jm * v0pv1);
                ctx->am = 0;
                ctx->dm = -jm * ctx->tdj;
                ctx->vm = v0;
                goto out;
            }
            ac *= A_FLOAT_C(0.5);
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
                ctx->taj = (_tmp - a_float_sqrt(temp)) / (jm * v0pv1);
                ctx->am = +jm * ctx->taj;
                ctx->dm = 0;
                ctx->vm = v0 + ctx->am * (ctx->ta - ctx->taj);
                goto out;
            }
            ac *= A_FLOAT_C(0.5);
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
                goto out;
            }
            ac *= A_FLOAT_C(0.5);
            am += ac;
            continue;
        }
        ac *= A_FLOAT_C(0.5);
        am -= ac;
    } while (ac > A_FLOAT_EPSILON);
fail:
    ctx->t = 0;
    return 0;
out:
    ctx->t = ctx->ta + ctx->tv + ctx->td;
    return ctx->t;
}

a_float a_trajbell_pos(a_trajbell const *ctx, a_float x)
{
    a_float out;
    a_float p0 = ctx->p0;
    a_float p1 = ctx->p1;
    a_float v0 = ctx->v0;
    a_float v1 = ctx->v1;
    a_bool const rev = ctx->p0 > ctx->p1;
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
            out = p0 + v0 * x + ctx->jm * x * x * x / 6;
            goto out;
        }
        if (x < ctx->ta - ctx->taj)
        {
            out = p0 + v0 * x + ctx->am * (3 * x * x - 3 * x * ctx->taj + ctx->taj * ctx->taj) / 6;
            goto out;
        }
        x = ctx->ta - x;
        out = p0 + A_FLOAT_C(0.5) * (ctx->vm + v0) * ctx->ta - ctx->vm * x + ctx->jm * x * x * x / 6;
        goto out;
    }
    if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x < ctx->ta + ctx->tv)
        {
            out = p0 + A_FLOAT_C(0.5) * (ctx->vm + v0) * ctx->ta + ctx->vm * (x - ctx->ta);
            goto out;
        }
        x -= ctx->t - ctx->td;
        out = p1 - A_FLOAT_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * x - ctx->jm * x * x * x / 6;
        goto out;
    }
    if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            x -= ctx->t - ctx->td;
            out = p1 - A_FLOAT_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * x +
                  ctx->dm * (3 * x * x - 3 * x * ctx->tdj + ctx->tdj * ctx->tdj) / 6;
            goto out;
        }
        x = ctx->t - x;
        out = p1 - v1 * x - ctx->jm * x * x * x / 6;
        goto out;
    }
    return ctx->p1;
out:
    return rev ? -out : out;
}

a_float a_trajbell_vel(a_trajbell const *ctx, a_float x)
{
    a_float out;
    a_float v0 = ctx->v0;
    a_float v1 = ctx->v1;
    a_bool const rev = ctx->p0 > ctx->p1;
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
            out = v0 + A_FLOAT_C(0.5) * ctx->jm * x * x;
            goto out;
        }
        if (x < ctx->ta - ctx->taj)
        {
            out = v0 + ctx->am * (x - A_FLOAT_C(0.5) * ctx->taj);
            goto out;
        }
        x = ctx->ta - x;
        out = ctx->vm - A_FLOAT_C(0.5) * ctx->jm * x * x;
        goto out;
    }
    if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x < ctx->ta + ctx->tv)
        {
            out = ctx->vm;
            goto out;
        }
        x -= ctx->t - ctx->td;
        out = ctx->vm - A_FLOAT_C(0.5) * ctx->jm * x * x;
        goto out;
    }
    if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            out = ctx->vm + ctx->dm * (x - ctx->t + ctx->td - A_FLOAT_C(0.5) * ctx->tdj);
            goto out;
        }
        x = ctx->t - x;
        out = v1 + A_FLOAT_C(0.5) * ctx->jm * x * x;
        goto out;
    }
    return ctx->v1;
out:
    return rev ? -out : out;
}

a_float a_trajbell_acc(a_trajbell const *ctx, a_float x)
{
    a_float out;
    if (x < ctx->ta)
    {
        if (x >= ctx->taj)
        {
            if (x < ctx->ta - ctx->taj)
            {
                out = ctx->am;
                goto out;
            }
            out = ctx->jm * (ctx->ta - x);
            goto out;
        }
        if (x > 0)
        {
            out = ctx->jm * x;
            goto out;
        }
    }
    else if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x >= ctx->ta + ctx->tv)
        {
            out = -ctx->jm * (x - ctx->t + ctx->td);
            goto out;
        }
    }
    else if (x < ctx->t)
    {
        if (x < ctx->t - ctx->tdj)
        {
            out = ctx->dm;
            goto out;
        }
        out = -ctx->jm * (ctx->t - x);
        goto out;
    }
    return 0;
out:
    if (ctx->p0 > ctx->p1)
    {
        return -out;
    }
    return out;
}

a_float a_trajbell_jer(a_trajbell const *ctx, a_float x)
{
    a_float out;
    if (x < ctx->ta)
    {
        if (x >= ctx->ta - ctx->taj)
        {
            out = -ctx->jm;
            goto out;
        }
        if (x < ctx->taj && x >= 0)
        {
            out = +ctx->jm;
            goto out;
        }
    }
    else if (x < ctx->t - ctx->td + ctx->tdj)
    {
        if (x >= ctx->ta + ctx->tv)
        {
            out = -ctx->jm;
            goto out;
        }
    }
    else if (x <= ctx->t)
    {
        if (x >= ctx->t - ctx->tdj)
        {
            out = +ctx->jm;
            goto out;
        }
    }
    return 0;
out:
    if (ctx->p0 > ctx->p1)
    {
        return -out;
    }
    return out;
}
