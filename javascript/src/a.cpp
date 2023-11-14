#include "a/host/a.h"
#include <emscripten/bind.h>

#include "a/pid.h"

class pid
{
    a_pid_s ctx;

    void init()
    {
        ctx.kp = 0;
        ctx.ki = 0;
        ctx.kd = 0;
        a_pid_init(&ctx, 0);
    }

public:
    pid()
    {
        ctx.summax = 0;
        ctx.outmax = -A_FLOAT_INF;
        ctx.outmin = +A_FLOAT_INF;
        ctx.mode = A_PID_INC;
        init();
    }
    pid(a_float_t min, a_float_t max)
    {
        ctx.summax = 0;
        ctx.outmax = max;
        ctx.outmin = min;
        ctx.mode = A_PID_INC;
        init();
    }
    pid(a_float_t min, a_float_t max, a_float_t sum)
    {
        ctx.summax = sum;
        ctx.outmax = max;
        ctx.outmin = min;
        ctx.mode = A_PID_POS;
        init();
    }
    void kpid(a_float_t kp, a_float_t ki, a_float_t kd)
    {
        a_pid_kpid(&ctx, kp, ki, kd);
    }
    a_float_t iter(a_float_t set, a_float_t fdb)
    {
        return a_pid_outf(&ctx, set, fdb);
    }
    void zero() { a_pid_zero(&ctx); }
};

#include "a/pid/fuzzy.h"

static emscripten::val concat(emscripten::val x)
{
    return emscripten::val::array()["concat"].call<emscripten::val>("apply", emscripten::val::array(), x);
}

static a_float_t *float_array(emscripten::val const &x, a_size_t n, a_float_t *p)
{
    p = a_float_c(*, a_alloc(p, sizeof(a_float_t) * n));
    a_size_t length = x["length"].as<a_size_t>();
    for (a_size_t i = 0; i < length; ++i)
    {
        p[i] = x[i].as<a_float_t>();
    }
    return p;
}

class pid_fuzzy
{
    a_pid_fuzzy_s ctx;
    a_float_t *me;
    a_float_t *mec;
    a_float_t *mkp;
    a_float_t *mki;
    a_float_t *mkd;
    void *buf;

    void init()
    {
        ctx.pid.kp = 0;
        ctx.pid.ki = 0;
        ctx.pid.kd = 0;
        ctx.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
        ctx.kp = 0;
        ctx.ki = 0;
        ctx.kd = 0;
        ctx.col = 0;
        ctx.buf = 0;
        me = nullptr;
        mec = nullptr;
        mkp = nullptr;
        mki = nullptr;
        mkd = nullptr;
        buf = nullptr;
        a_pid_fuzzy_init(&ctx, 0);
    }

public:
    pid_fuzzy()
    {
        ctx.pid.summax = 0;
        ctx.pid.outmax = -A_FLOAT_INF;
        ctx.pid.outmin = +A_FLOAT_INF;
        ctx.pid.mode = A_PID_INC;
        init();
    }
    pid_fuzzy(a_float_t min, a_float_t max)
    {
        ctx.pid.summax = 0;
        ctx.pid.outmax = max;
        ctx.pid.outmin = min;
        ctx.pid.mode = A_PID_INC;
        init();
    }
    pid_fuzzy(a_float_t min, a_float_t max, a_float_t sum)
    {
        ctx.pid.summax = sum;
        ctx.pid.outmax = max;
        ctx.pid.outmin = min;
        ctx.pid.mode = A_PID_POS;
        init();
    }
    ~pid_fuzzy()
    {
        a_alloc(me, 0);
        a_alloc(mec, 0);
        a_alloc(mkp, 0);
        a_alloc(mki, 0);
        a_alloc(mkd, 0);
        a_alloc(buf, 0);
    }
    void rule(emscripten::val const &_me, emscripten::val const &_mec,
              emscripten::val const &_mkp, emscripten::val const &_mki, emscripten::val const &_mkd)
    {
        me = float_array(concat(_me), _me["length"].as<a_size_t>(), me);
        mec = float_array(concat(_mec), _mec["length"].as<a_size_t>(), mec);
        mkp = float_array(concat(_mkp), _mkp["length"].as<a_size_t>(), mkp);
        mki = float_array(concat(_mki), _mki["length"].as<a_size_t>(), mki);
        mkd = float_array(concat(_mkd), _mkd["length"].as<a_size_t>(), mkd);
        a_pid_fuzzy_rule(&ctx, _me["length"].as<unsigned int>(), me, mec, mkp, mki, mkd);
    }
    void kpid(a_float_t kp, a_float_t ki, a_float_t kd)
    {
        a_pid_fuzzy_kpid(&ctx, kp, ki, kd);
    }
    void buff(unsigned int num)
    {
        buf = a_alloc(buf, A_PID_FUZZY_BUF1(num));
        a_pid_fuzzy_buf1(&ctx, buf, num);
    }
    void op(unsigned int op)
    {
        a_pid_fuzzy_set_op(&ctx, op);
    }
    a_float_t iter(a_float_t set, a_float_t fdb)
    {
        return a_pid_fuzzy_outf(&ctx, set, fdb);
    }
    void zero() { a_pid_fuzzy_zero(&ctx); }
};

#include "a/pid/neuron.h"

class pid_neuron
{
    a_pid_neuron_s ctx;

    void init()
    {
        ctx.pid.kp = 0;
        ctx.pid.ki = 0;
        ctx.pid.kd = 0;
        ctx.wp.f = 1;
        ctx.wi.f = 0;
        ctx.wd.f = 0;
        ctx.k = 1;
        a_pid_neuron_init(&ctx, 0);
    }

public:
    pid_neuron()
    {
        ctx.pid.summax = 0;
        ctx.pid.outmax = -A_FLOAT_INF;
        ctx.pid.outmin = +A_FLOAT_INF;
        ctx.pid.mode = A_PID_INC;
        init();
    }
    pid_neuron(a_float_t min, a_float_t max)
    {
        ctx.pid.summax = 0;
        ctx.pid.outmax = max;
        ctx.pid.outmin = min;
        ctx.pid.mode = A_PID_INC;
        init();
    }
    void kpid(a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd)
    {
        a_pid_neuron_kpid(&ctx, k, kp, ki, kd);
    }
    void wpid(a_float_t wp, a_float_t wi, a_float_t wd)
    {
        a_pid_neuron_wpid(&ctx, wp, wi, wd);
    }
    a_float_t iter(a_float_t set, a_float_t fdb)
    {
        return a_pid_neuron_outf(&ctx, set, fdb);
    }
    void zero() { a_pid_neuron_zero(&ctx); }
};

#include "a/polytrack.h"

class polytrack3
{
    a_polytrack3_s ctx;

public:
    polytrack3(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0)
    {
        a_polytrack3_gen(&ctx, t0, t1, q0, q1, v0, v1);
    }
    a_float_t pos(a_float_t dt)
    {
        return a_polytrack3_pos(&ctx, dt);
    }
    a_float_t vel(a_float_t dt)
    {
        return a_polytrack3_vel(&ctx, dt);
    }
    a_float_t acc(a_float_t dt)
    {
        return a_polytrack3_acc(&ctx, dt);
    }
    emscripten::val out(a_float_t dt)
    {
        a_float_t out[3];
        a_polytrack3_out(&ctx, dt, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack5
{
    a_polytrack5_s ctx;

public:
    polytrack5(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0,
               a_float_t a0 = 0, a_float_t a1 = 0)
    {
        a_polytrack5_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1);
    }
    a_float_t pos(a_float_t dt)
    {
        return a_polytrack5_pos(&ctx, dt);
    }
    a_float_t vel(a_float_t dt)
    {
        return a_polytrack5_vel(&ctx, dt);
    }
    a_float_t acc(a_float_t dt)
    {
        return a_polytrack5_acc(&ctx, dt);
    }
    emscripten::val out(a_float_t dt)
    {
        a_float_t out[3];
        a_polytrack5_out(&ctx, dt, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack7
{
    a_polytrack7_s ctx;

public:
    polytrack7(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0,
               a_float_t a0 = 0, a_float_t a1 = 0,
               a_float_t j0 = 0, a_float_t j1 = 0)
    {
        a_polytrack7_gen(&ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    }
    a_float_t pos(a_float_t dt)
    {
        return a_polytrack7_pos(&ctx, dt);
    }
    a_float_t vel(a_float_t dt)
    {
        return a_polytrack7_vel(&ctx, dt);
    }
    a_float_t acc(a_float_t dt)
    {
        return a_polytrack7_acc(&ctx, dt);
    }
    a_float_t jer(a_float_t dt)
    {
        return a_polytrack7_jer(&ctx, dt);
    }
    emscripten::val out(a_float_t dt)
    {
        a_float_t out[4];
        a_polytrack7_out(&ctx, dt, out);
        return emscripten::val(emscripten::typed_memory_view(4, out));
    }
};

#include "a/tf.h"

class tf
{
    a_tf_s ctx;

    a_float_t *num_p;
    void set_num_(emscripten::val const &_num, a_float_t *num)
    {
        a_uint_t num_n = _num["length"].as<a_uint_t>();
        num_p = float_array(_num, a_size_c(, num_n) * 2, num);
        a_tf_set_num(&ctx, num_n, num_p, num_p + num_n);
    }
    a_float_t *den_p;
    void set_den_(emscripten::val const &_den, a_float_t *den)
    {
        a_uint_t den_n = _den["length"].as<a_uint_t>();
        den_p = float_array(_den, a_size_c(, den_n) * 2, den);
        a_tf_set_den(&ctx, den_n, den_p, den_p + den_n);
    }

public:
    tf(emscripten::val const &num, emscripten::val const &den)
    {
        set_num_(num, nullptr);
        set_den_(den, nullptr);
    }
    ~tf()
    {
        a_alloc(num_p, 0);
        a_alloc(den_p, 0);
    }
    emscripten::val input()
    {
        return emscripten::val(emscripten::typed_memory_view(ctx.num_n, ctx.input));
    }
    emscripten::val num()
    {
        return emscripten::val(emscripten::typed_memory_view(ctx.num_n, ctx.num_p));
    }
    void set_num(emscripten::val const &num)
    {
        set_num_(num, num_p);
    }
    emscripten::val output()
    {
        return emscripten::val(emscripten::typed_memory_view(ctx.den_n, ctx.output));
    }
    emscripten::val den()
    {
        return emscripten::val(emscripten::typed_memory_view(ctx.den_n, ctx.den_p));
    }
    void set_den(emscripten::val const &den)
    {
        set_den_(den, den_p);
    }
    a_float_t iter(a_float_t x)
    {
        return a_tf_iter(&ctx, x);
    }
    void zero() { a_tf_zero(&ctx); }
};

#include "a/math.h"
#include "a/version.h"
#if __has_warning("-Wglobal-constructors")
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif /* -Wglobal-constructors */
EMSCRIPTEN_BINDINGS(module) // NOLINT
{
    emscripten::function("f32_rsqrt", a_f32_rsqrt);
    emscripten::function("f64_rsqrt", a_f64_rsqrt);
    emscripten::constant("MF_NUL", A_MF_NUL);
    emscripten::function("mf_gauss", a_mf_gauss);
    emscripten::constant("MF_GAUSS", A_MF_GAUSS);
    emscripten::function("mf_gbell", a_mf_gbell);
    emscripten::constant("MF_GBELL", A_MF_GBELL);
    emscripten::function("mf_sig", a_mf_sig);
    emscripten::constant("MF_SIG", A_MF_SIG);
    emscripten::function("mf_trap", a_mf_trap);
    emscripten::constant("MF_TRAP", A_MF_TRAP);
    emscripten::function("mf_tri", a_mf_tri);
    emscripten::constant("MF_TRI", A_MF_TRI);
    emscripten::function("mf_z", a_mf_z);
    emscripten::constant("MF_Z", A_MF_Z);
    emscripten::constant("PID_OFF", A_PID_OFF);
    emscripten::constant("PID_POS", A_PID_POS);
    emscripten::constant("PID_INC", A_PID_INC);
    emscripten::constant("PID_FUZZY_EQU", A_PID_FUZZY_EQU);
    emscripten::constant("PID_FUZZY_CAP", A_PID_FUZZY_CAP);
    emscripten::constant("PID_FUZZY_CAP_ALGEBRA", A_PID_FUZZY_CAP_ALGEBRA);
    emscripten::constant("PID_FUZZY_CAP_BOUNDED", A_PID_FUZZY_CAP_BOUNDED);
    emscripten::constant("PID_FUZZY_CUP", A_PID_FUZZY_CUP);
    emscripten::constant("PID_FUZZY_CUP_ALGEBRA", A_PID_FUZZY_CUP_ALGEBRA);
    emscripten::constant("PID_FUZZY_CUP_BOUNDED", A_PID_FUZZY_CUP_BOUNDED);
    emscripten::class_<pid>("pid")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t>()
        .function("kpid", &pid::kpid)
        .function("iter", &pid::iter)
        .function("zero", &pid::zero);
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t>()
        .function("rule", &pid_fuzzy::rule)
        .function("kpid", &pid_fuzzy::kpid)
        .function("buff", &pid_fuzzy::buff)
        .function("op", &pid_fuzzy::op)
        .function("iter", &pid_fuzzy::iter)
        .function("zero", &pid_fuzzy::zero);
    emscripten::class_<pid_neuron>("pid_neuron")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .function("kpid", &pid_neuron::kpid)
        .function("wpid", &pid_neuron::wpid)
        .function("iter", &pid_neuron::iter)
        .function("zero", &pid_neuron::zero);
    emscripten::class_<polytrack3>("polytrack3")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", &polytrack3::pos)
        .function("vel", &polytrack3::vel)
        .function("acc", &polytrack3::acc)
        .function("out", &polytrack3::out);
    emscripten::class_<polytrack5>("polytrack5")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", &polytrack5::pos)
        .function("vel", &polytrack5::vel)
        .function("acc", &polytrack5::acc)
        .function("out", &polytrack5::out);
    emscripten::class_<polytrack7>("polytrack7")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", &polytrack7::pos)
        .function("vel", &polytrack7::vel)
        .function("acc", &polytrack7::acc)
        .function("jer", &polytrack7::jer)
        .function("out", &polytrack7::out);
    emscripten::class_<tf>("tf")
        .constructor<emscripten::val, emscripten::val>()
        .function("input", &tf::input)
        .function("num", &tf::num)
        .function("set_num", &tf::set_num)
        .function("output", &tf::output)
        .function("den", &tf::den)
        .function("set_den", &tf::set_den)
        .function("iter", &tf::iter)
        .function("zero", &tf::zero);
    emscripten::class_<a::version>("version")
        .constructor<>()
        .constructor<a_uint_t>()
        .constructor<a_uint_t, a_uint_t>()
        .constructor<a_uint_t, a_uint_t, a_uint_t>()
        .property("major", &a::version::major)
        .property("minor", &a::version::minor)
        .property("patch", &a::version::patch)
        .function("str", emscripten::optional_override([](a::version const &v) {
                      return std::to_string(v.major) + "." + std::to_string(v.minor) + "." + std::to_string(v.patch);
                  }))
        .function("lt", &a::version::operator<)
        .function("gt", &a::version::operator>)
        .function("le", &a::version::operator<=)
        .function("ge", &a::version::operator>=)
        .function("eq", &a::version::operator==)
        .function("ne", &a::version::operator!=)
        .function("cmp", emscripten::optional_override([](a::version const &lhs, a::version const &rhs) {
                      return a_version_cmp(&lhs, &rhs);
                  }));
    emscripten::function("version_check", &a_version_check);
    emscripten::constant("VERSION", std::string{A_VERSION});
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
}
