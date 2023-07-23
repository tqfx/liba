#include "a/host/a.h"
#include <emscripten/bind.h>

#include "a/version.h"

static emscripten::val version()
{
    return emscripten::val(a_version());
}

#include "a/pid.h"

class pid
{
    a_pid_s ctx;

    void init()
    {
        this->ctx.kp = 0;
        this->ctx.ki = 0;
        this->ctx.kd = 0;
        a_pid_init(&this->ctx, 0);
    }

public:
    pid()
    {
        this->ctx.summax = 0;
        this->ctx.outmax = -A_FLOAT_INF;
        this->ctx.outmin = +A_FLOAT_INF;
        this->ctx.mode = A_PID_INC;
        this->init();
    }
    pid(a_float_t jmin, a_float_t jmax)
    {
        this->ctx.summax = 0;
        this->ctx.outmax = jmax;
        this->ctx.outmin = jmin;
        this->ctx.mode = A_PID_INC;
        this->init();
    }
    pid(a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        this->ctx.summax = jsum;
        this->ctx.outmax = jmax;
        this->ctx.outmin = jmin;
        this->ctx.mode = A_PID_POS;
        this->init();
    }
    void kpid(a_float_t jkp, a_float_t jki, a_float_t jkd)
    {
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
    }
    a_float_t iter(a_float_t jset, a_float_t jfdb)
    {
        return a_pid_outf(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_zero(&this->ctx); }
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
        this->ctx.pid.kp = 0;
        this->ctx.pid.ki = 0;
        this->ctx.pid.kd = 0;
        this->ctx.op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
        this->ctx.kp = 0;
        this->ctx.ki = 0;
        this->ctx.kd = 0;
        this->ctx.col = 0;
        this->ctx.buf = 0;
        this->me = nullptr;
        this->mec = nullptr;
        this->mkp = nullptr;
        this->mki = nullptr;
        this->mkd = nullptr;
        this->buf = nullptr;
        a_pid_fuzzy_init(&this->ctx, 0);
    }

public:
    pid_fuzzy()
    {
        this->ctx.pid.summax = 0;
        this->ctx.pid.outmax = -A_FLOAT_INF;
        this->ctx.pid.outmin = +A_FLOAT_INF;
        this->ctx.pid.mode = A_PID_INC;
        this->init();
    }
    pid_fuzzy(a_float_t jmin, a_float_t jmax)
    {
        this->ctx.pid.summax = 0;
        this->ctx.pid.outmax = jmax;
        this->ctx.pid.outmin = jmin;
        this->ctx.pid.mode = A_PID_INC;
        this->init();
    }
    pid_fuzzy(a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        this->ctx.pid.summax = jsum;
        this->ctx.pid.outmax = jmax;
        this->ctx.pid.outmin = jmin;
        this->ctx.pid.mode = A_PID_POS;
        this->init();
    }
    ~pid_fuzzy()
    {
        a_alloc(this->me, 0);
        a_alloc(this->mec, 0);
        a_alloc(this->mkp, 0);
        a_alloc(this->mki, 0);
        a_alloc(this->mkd, 0);
        a_alloc(this->buf, 0);
    }
    void rule(emscripten::val const &jme, emscripten::val const &jmec,
              emscripten::val const &jmkp, emscripten::val const &jmki, emscripten::val const &jmkd)
    {
        this->me = float_array(concat(jme), jme["length"].as<a_size_t>(), this->me);
        this->mec = float_array(concat(jmec), jmec["length"].as<a_size_t>(), this->mec);
        this->mkp = float_array(concat(jmkp), jmkp["length"].as<a_size_t>(), this->mkp);
        this->mki = float_array(concat(jmki), jmki["length"].as<a_size_t>(), this->mki);
        this->mkd = float_array(concat(jmkd), jmkd["length"].as<a_size_t>(), this->mkd);
        a_pid_fuzzy_rule(&this->ctx, jme["length"].as<unsigned int>(), this->me, this->mec, this->mkp, this->mki, this->mkd);
    }
    void kpid(a_float_t jkp, a_float_t jki, a_float_t jkd)
    {
        a_pid_fuzzy_kpid(&this->ctx, jkp, jki, jkd);
    }
    void buff(unsigned int jnum)
    {
        this->buf = a_alloc(this->buf, A_PID_FUZZY_BUF1(jnum));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jnum);
    }
    void op(unsigned int jop)
    {
        a_pid_fuzzy_set_op(&this->ctx, jop);
    }
    a_float_t iter(a_float_t jset, a_float_t jfdb)
    {
        return a_pid_fuzzy_outf(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_fuzzy_zero(&this->ctx); }
};

#include "a/pid/neuron.h"

class pid_neuron
{
    a_pid_neuron_s ctx;

    void init()
    {
        this->ctx.pid.kp = 0;
        this->ctx.pid.ki = 0;
        this->ctx.pid.kd = 0;
        this->ctx.wp.f = 1;
        this->ctx.wi.f = 0;
        this->ctx.wd.f = 0;
        this->ctx.k = 1;
        a_pid_neuron_init(&this->ctx, 0);
    }

public:
    pid_neuron()
    {
        this->ctx.pid.summax = 0;
        this->ctx.pid.outmax = -A_FLOAT_INF;
        this->ctx.pid.outmin = +A_FLOAT_INF;
        this->ctx.pid.mode = A_PID_INC;
        this->init();
    }
    pid_neuron(a_float_t jmin, a_float_t jmax)
    {
        this->ctx.pid.summax = 0;
        this->ctx.pid.outmax = jmax;
        this->ctx.pid.outmin = jmin;
        this->ctx.pid.mode = A_PID_INC;
        this->init();
    }
    void kpid(a_float_t jk, a_float_t jkp, a_float_t jki, a_float_t jkd)
    {
        a_pid_neuron_kpid(&this->ctx, jk, jkp, jki, jkd);
    }
    void wpid(a_float_t jwp, a_float_t jwi, a_float_t jwd)
    {
        a_pid_neuron_wpid(&this->ctx, jwp, jwi, jwd);
    }
    a_float_t iter(a_float_t jset, a_float_t jfdb)
    {
        return a_pid_neuron_outf(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_neuron_zero(&this->ctx); }
};

#include "a/polytrack.h"

class polytrack3
{
    a_polytrack3_s ctx;

public:
    polytrack3(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1,
               a_float_t jv0 = 0, a_float_t jv1 = 0)
    {
        a_polytrack3_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack3_pos(&this->ctx, jdt);
    }
    a_float_t vel(a_float_t jdt)
    {
        return a_polytrack3_vel(&this->ctx, jdt);
    }
    a_float_t acc(a_float_t jdt)
    {
        return a_polytrack3_acc(&this->ctx, jdt);
    }
    emscripten::val out(a_float_t jdt)
    {
        a_float_t out[3];
        a_polytrack3_out(&this->ctx, jdt, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack5
{
    a_polytrack5_s ctx;

public:
    polytrack5(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1,
               a_float_t jv0 = 0, a_float_t jv1 = 0,
               a_float_t ja0 = 0, a_float_t ja1 = 0)
    {
        a_polytrack5_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack5_pos(&this->ctx, jdt);
    }
    a_float_t vel(a_float_t jdt)
    {
        return a_polytrack5_vel(&this->ctx, jdt);
    }
    a_float_t acc(a_float_t jdt)
    {
        return a_polytrack5_acc(&this->ctx, jdt);
    }
    emscripten::val out(a_float_t jdt)
    {
        a_float_t out[3];
        a_polytrack5_out(&this->ctx, jdt, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack7
{
    a_polytrack7_s ctx;

public:
    polytrack7(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1,
               a_float_t jv0 = 0, a_float_t jv1 = 0,
               a_float_t ja0 = 0, a_float_t ja1 = 0,
               a_float_t jj0 = 0, a_float_t jj1 = 0)
    {
        a_polytrack7_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, jj0, jj1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack7_pos(&this->ctx, jdt);
    }
    a_float_t vel(a_float_t jdt)
    {
        return a_polytrack7_vel(&this->ctx, jdt);
    }
    a_float_t acc(a_float_t jdt)
    {
        return a_polytrack7_acc(&this->ctx, jdt);
    }
    a_float_t jer(a_float_t jdt)
    {
        return a_polytrack7_jer(&this->ctx, jdt);
    }
    emscripten::val out(a_float_t jdt)
    {
        a_float_t out[4];
        a_polytrack7_out(&this->ctx, jdt, out);
        return emscripten::val(emscripten::typed_memory_view(4, out));
    }
};

#include "a/tf.h"

class tf
{
    a_tf_s ctx;

    a_float_t *num_p;
    void set_num_(emscripten::val const &jnum, a_float_t *num)
    {
        a_size_t num_n = jnum["length"].as<a_size_t>();
        this->num_p = float_array(jnum, num_n * 2, num);
        a_tf_set_num(&this->ctx, num_n, this->num_p, this->num_p + num_n);
    }
    a_float_t *den_p;
    void set_den_(emscripten::val const &jden, a_float_t *den)
    {
        a_size_t den_n = jden["length"].as<a_size_t>();
        this->den_p = float_array(jden, den_n * 2, den);
        a_tf_set_den(&this->ctx, den_n, this->den_p, this->den_p + den_n);
    }

public:
    tf(emscripten::val const &jnum, emscripten::val const &jden)
    {
        this->set_num_(jnum, nullptr);
        this->set_den_(jden, nullptr);
    }
    ~tf()
    {
        a_alloc(this->num_p, 0);
        a_alloc(this->den_p, 0);
    }
    emscripten::val input()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.num_n, this->ctx.input));
    }
    emscripten::val num()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.num_n, this->ctx.num_p));
    }
    void set_num(emscripten::val const &jnum)
    {
        this->set_num_(jnum, this->num_p);
    }
    emscripten::val output()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.den_n, this->ctx.output));
    }
    emscripten::val den()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.den_n, this->ctx.den_p));
    }
    void set_den(emscripten::val const &jden)
    {
        this->set_den_(jden, this->den_p);
    }
    a_float_t iter(a_float_t jx)
    {
        return a_tf_iter(&this->ctx, jx);
    }
    void zero() { a_tf_zero(&this->ctx); }
};

#include "a/math.h"
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
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
    emscripten::function("version", version);
}
