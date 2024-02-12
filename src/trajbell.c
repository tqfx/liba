#include "a/trajbell.h"
#include "a/math.h"

a_float a_trajbell_gen(a_trajbell *ctx, a_float jm, a_float am, a_float vm,
                       a_float q0, a_float q1, a_float v0, a_float v1)
{
    a_float q, tj, v02, v12, _2v0, _2v1, _tmp, temp, v1pv0;
    if (jm < 0) { jm = -jm; }
    if (am < 0) { am = -am; }
    if (vm < 0) { vm = -vm; }
    if (v0 < -vm) { v0 = -vm; }
    else if (v0 > vm) { v0 = vm; }
    if (v1 < -vm) { v1 = -vm; }
    else if (v1 > vm) { v1 = vm; }
    ctx->q0 = q0;
    ctx->q1 = q1;
    ctx->v0 = v0;
    ctx->v1 = v1;
    if (q0 > q1)
    {
        q0 = -q0;
        q1 = -q1;
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
    q = q1 - q0;
    ctx->tv = q / vm - A_FLOAT_C(0.5) * ctx->ta * (1 + v0 / vm) - A_FLOAT_C(0.5) * ctx->td * (1 + v1 / vm);
    if (ctx->tv > 0) { goto out; }
    ctx->tv = 0;
    v02 = v0 * v0;
    v12 = v1 * v1;
    _2v0 = 2 * v0;
    _2v1 = 2 * v1;
    v1pv0 = v1 + v0;
    do {
        tj = am / jm;
        ctx->taj = tj;
        ctx->tdj = tj;
        _tmp = am * tj;
        temp = _tmp * _tmp + 2 * (v02 + v12) + (4 * q - 2 * v1pv0 * tj) * am;
        _tmp += a_float_sqrt(temp);
        temp = 2 * am;
        ctx->ta = (_tmp - _2v0) / temp;
        if (ctx->ta < 0)
        {
            ctx->ta = 0;
            ctx->taj = 0;
            ctx->td = 2 * q / v1pv0;
            _tmp = jm * q;
            temp = jm * (_tmp * q + (v1 - v0) * v1pv0 * v1pv0);
            if (temp < 0) { goto fail; }
            ctx->tdj = (_tmp - a_float_sqrt(temp)) / (jm * v1pv0);
            ctx->am = 0;
            ctx->dm = -jm * ctx->tdj;
            ctx->vm = v0;
            goto out;
        }
        ctx->td = (_tmp - _2v1) / temp;
        if (ctx->td < 0)
        {
            ctx->td = 0;
            ctx->tdj = 0;
            ctx->ta = 2 * q / v1pv0;
            _tmp = jm * q;
            temp = jm * (_tmp * q + (v0 - v1) * v1pv0 * v1pv0);
            if (temp < 0) { goto fail; }
            ctx->taj = (_tmp - a_float_sqrt(temp)) / (jm * v1pv0);
            ctx->am = +jm * ctx->taj;
            ctx->dm = 0;
            ctx->vm = v0 + ctx->am * (ctx->ta - ctx->taj);
            goto out;
        }
        _tmp = 2 * tj;
        if (ctx->ta >= _tmp && ctx->td >= _tmp)
        {
            ctx->am = +am;
            ctx->dm = -am;
            ctx->vm = v0 + ctx->am * (ctx->ta - tj);
            goto out;
        }
        am *= A_FLOAT_C(0.5);
    } while (am > A_FLOAT_C(0.01));
fail:
    ctx->t = 0;
    return 0;
out:
    ctx->t = ctx->ta + ctx->tv + ctx->td;
    return ctx->t;
}

a_float a_trajbell_pos(a_trajbell const *ctx, a_float dt)
{
    a_float out;
    a_float q0 = ctx->q0;
    a_float q1 = ctx->q1;
    a_float v0 = ctx->v0;
    a_float v1 = ctx->v1;
    a_bool const rev = ctx->q0 > ctx->q1;
    if (rev)
    {
        q0 = -q0;
        q1 = -q1;
        v0 = -v0;
        v1 = -v1;
    }
    if (dt < ctx->ta)
    {
        if (dt < ctx->taj)
        {
            if (dt <= 0) { return ctx->q0; }
            out = q0 + v0 * dt + ctx->jm * dt * dt * dt / 6;
            goto out;
        }
        if (dt < ctx->ta - ctx->taj)
        {
            out = q0 + v0 * dt + ctx->am * (3 * dt * dt - 3 * dt * ctx->taj + ctx->taj * ctx->taj) / 6;
            goto out;
        }
        dt = ctx->ta - dt;
        out = q0 + A_FLOAT_C(0.5) * (ctx->vm + v0) * ctx->ta - ctx->vm * dt + ctx->jm * dt * dt * dt / 6;
        goto out;
    }
    if (dt < ctx->t - ctx->td + ctx->tdj)
    {
        if (dt < ctx->ta + ctx->tv)
        {
            out = q0 + A_FLOAT_C(0.5) * (ctx->vm + v0) * ctx->ta + ctx->vm * (dt - ctx->ta);
            goto out;
        }
        dt -= ctx->t - ctx->td;
        out = q1 - A_FLOAT_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * dt - ctx->jm * dt * dt * dt / 6;
        goto out;
    }
    if (dt < ctx->t)
    {
        if (dt < ctx->t - ctx->tdj)
        {
            dt -= ctx->t - ctx->td;
            out = q1 - A_FLOAT_C(0.5) * (ctx->vm + v1) * ctx->td + ctx->vm * dt +
                  ctx->dm * (3 * dt * dt - 3 * dt * ctx->tdj + ctx->tdj * ctx->tdj) / 6;
            goto out;
        }
        dt = ctx->t - dt;
        out = q1 - v1 * dt - ctx->jm * dt * dt * dt / 6;
        goto out;
    }
    return ctx->q1;
out:
    return rev ? -out : out;
}

a_float a_trajbell_vel(a_trajbell const *ctx, a_float dt)
{
    a_float out;
    a_float v0 = ctx->v0;
    a_float v1 = ctx->v1;
    a_bool const rev = ctx->q0 > ctx->q1;
    if (rev)
    {
        v0 = -v0;
        v1 = -v1;
    }
    if (dt < ctx->ta)
    {
        if (dt < ctx->taj)
        {
            if (dt <= 0) { return ctx->v0; }
            out = v0 + A_FLOAT_C(0.5) * ctx->jm * dt * dt;
            goto out;
        }
        if (dt < ctx->ta - ctx->taj)
        {
            out = v0 + ctx->am * (dt - A_FLOAT_C(0.5) * ctx->taj);
            goto out;
        }
        dt = ctx->ta - dt;
        out = ctx->vm - A_FLOAT_C(0.5) * ctx->jm * dt * dt;
        goto out;
    }
    if (dt < ctx->t - ctx->td + ctx->tdj)
    {
        if (dt < ctx->ta + ctx->tv)
        {
            out = ctx->vm;
            goto out;
        }
        dt -= ctx->t - ctx->td;
        out = ctx->vm - A_FLOAT_C(0.5) * ctx->jm * dt * dt;
        goto out;
    }
    if (dt < ctx->t)
    {
        if (dt < ctx->t - ctx->tdj)
        {
            out = ctx->vm + ctx->dm * (dt - ctx->t + ctx->td - A_FLOAT_C(0.5) * ctx->tdj);
            goto out;
        }
        dt = ctx->t - dt;
        out = v1 + A_FLOAT_C(0.5) * ctx->jm * dt * dt;
        goto out;
    }
    return ctx->v1;
out:
    return rev ? -out : out;
}

a_float a_trajbell_acc(a_trajbell const *ctx, a_float dt)
{
    a_float out;
    if (dt < ctx->ta)
    {
        if (dt >= ctx->taj)
        {
            if (dt < ctx->ta - ctx->taj)
            {
                out = ctx->am;
                goto out;
            }
            out = ctx->jm * (ctx->ta - dt);
            goto out;
        }
        if (dt > 0)
        {
            out = ctx->jm * dt;
            goto out;
        }
    }
    else if (dt < ctx->t - ctx->td + ctx->tdj)
    {
        if (dt >= ctx->ta + ctx->tv)
        {
            out = -ctx->jm * (dt - ctx->t + ctx->td);
            goto out;
        }
    }
    else if (dt < ctx->t)
    {
        if (dt < ctx->t - ctx->tdj)
        {
            out = ctx->dm;
            goto out;
        }
        out = -ctx->jm * (ctx->t - dt);
        goto out;
    }
    return 0;
out:
    if (ctx->q0 > ctx->q1)
    {
        return -out;
    }
    return out;
}

a_float a_trajbell_jer(a_trajbell const *ctx, a_float dt)
{
    a_float out;
    if (dt < ctx->ta)
    {
        if (dt >= ctx->ta - ctx->taj)
        {
            out = -ctx->jm;
            goto out;
        }
        if (dt < ctx->taj && dt >= 0)
        {
            out = +ctx->jm;
            goto out;
        }
    }
    else if (dt < ctx->t - ctx->td + ctx->tdj)
    {
        if (dt >= ctx->ta + ctx->tv)
        {
            out = -ctx->jm;
            goto out;
        }
    }
    else if (dt <= ctx->t)
    {
        if (dt >= ctx->t - ctx->tdj)
        {
            out = +ctx->jm;
            goto out;
        }
    }
    return 0;
out:
    if (ctx->q0 > ctx->q1)
    {
        return -out;
    }
    return out;
}
