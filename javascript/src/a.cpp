#include "a.h"
#include "a/math.h"
#include "a/version.h"

emscripten::val version()
{
    return emscripten::val(a_version());
}

#include "a/pid.h"

class pid
{
    a_pid_s ctx;

public:
    pid(a_float_t jdt, a_float_t jmin, a_float_t jmax)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_inc(&this->ctx);
    }
    pid(a_float_t jdt, a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_pos(&this->ctx, jsum);
    }
    pid(a_float_t jdt, a_float_t jkp, a_float_t jki, a_float_t jkd, a_float_t jmin, a_float_t jmax)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
        a_pid_inc(&this->ctx);
    }
    pid(a_float_t jdt, a_float_t jkp, a_float_t jki, a_float_t jkd, a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
        a_pid_pos(&this->ctx, jsum);
    }
    a_float_t iter(a_float_t jset, a_float_t jfdb)
    {
        return a_pid_outf(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_zero(&this->ctx); }
    void kpid(a_float_t jkp, a_float_t jki, a_float_t jkd)
    {
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
    }
    void time(a_float_t jdt) { a_pid_set_dt(&this->ctx, jdt); }
    void pos(a_float_t jmax) { a_pid_pos(&this->ctx, jmax); }
    void inc() { a_pid_inc(&this->ctx); }
    void off() { a_pid_off(&this->ctx); }
};

#include "a/pid_fuzzy.h"

static emscripten::val concat(emscripten::val x)
{
    return emscripten::val::array()["concat"].call<emscripten::val>("apply", emscripten::val::array(), x);
}

static a_float_t *floats(emscripten::val const &x, a_size_t n, a_float_t *p)
{
    p = a_float_c(*, realloc(p, sizeof(a_float_t) * n));
    for (a_size_t i = 0; i < n; ++i)
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

public:
    pid_fuzzy(unsigned int jnum, a_float_t jdt, emscripten::val const &jme, emscripten::val const &jmec,
              emscripten::val const &jmkp, emscripten::val const &jmki, emscripten::val const &jmkd,
              a_float_t jmin, a_float_t jmax)
    {
        this->me = floats(concat(jme), jme["length"].as<a_size_t>(), nullptr);
        this->mec = floats(concat(jmec), jmec["length"].as<a_size_t>(), nullptr);
        this->mkp = floats(concat(jmkp), jmkp["length"].as<a_size_t>(), nullptr);
        this->mki = floats(concat(jmki), jmki["length"].as<a_size_t>(), nullptr);
        this->mkd = floats(concat(jmkd), jmkd["length"].as<a_size_t>(), nullptr);
        unsigned int col = jmkp["length"].as<unsigned int>();
        a_pid_fuzzy_init(&this->ctx, jdt, col, this->me, this->mec,
                         this->mkp, this->mki, this->mkd, jmin, jmax);
        this->buf = malloc(A_PID_FUZZY_BUF1(jnum));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jnum);
        a_pid_fuzzy_inc(&this->ctx);
    }
    pid_fuzzy(unsigned int jnum, a_float_t jdt, emscripten::val const &jme, emscripten::val const &jmec,
              emscripten::val const &jmkp, emscripten::val const &jmki, emscripten::val const &jmkd,
              a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        this->me = floats(concat(jme), jme["length"].as<a_size_t>(), nullptr);
        this->mec = floats(concat(jmec), jmec["length"].as<a_size_t>(), nullptr);
        this->mkp = floats(concat(jmkp), jmkp["length"].as<a_size_t>(), nullptr);
        this->mki = floats(concat(jmki), jmki["length"].as<a_size_t>(), nullptr);
        this->mkd = floats(concat(jmkd), jmkd["length"].as<a_size_t>(), nullptr);
        unsigned int col = jmkp["length"].as<unsigned int>();
        a_pid_fuzzy_init(&this->ctx, jdt, col, this->me, this->mec,
                         this->mkp, this->mki, this->mkd, jmin, jmax);
        this->buf = malloc(A_PID_FUZZY_BUF1(jnum));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jnum);
        a_pid_fuzzy_pos(&this->ctx, jsum);
    }
    ~pid_fuzzy()
    {
        free(this->me);
        free(this->mec);
        free(this->mkp);
        free(this->mki);
        free(this->mkd);
        free(this->buf);
    }
    void buff(unsigned int jnum)
    {
        this->buf = realloc(this->buf, A_PID_FUZZY_BUF1(jnum));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jnum);
    }
    void base(emscripten::val const &jme, emscripten::val const &jmec,
              emscripten::val const &jmkp, emscripten::val const &jmki, emscripten::val const &jmkd)
    {
        this->me = floats(concat(jme), jme["length"].as<a_size_t>(), this->me);
        this->mec = floats(concat(jmec), jmec["length"].as<a_size_t>(), this->mec);
        this->mkp = floats(concat(jmkp), jmkp["length"].as<a_size_t>(), this->mkp);
        this->mki = floats(concat(jmki), jmki["length"].as<a_size_t>(), this->mki);
        this->mkd = floats(concat(jmkd), jmkd["length"].as<a_size_t>(), this->mkd);
        unsigned int col = jmkp["length"].as<unsigned int>();
        a_pid_fuzzy_base(&this->ctx, col, this->me, this->mec, this->mkp, this->mki, this->mkd);
    }
    a_float_t iter(a_float_t jset, a_float_t jfdb)
    {
        return a_pid_fuzzy_outf(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_fuzzy_zero(&this->ctx); }
    void kpid(a_float_t jkp, a_float_t jki, a_float_t jkd)
    {
        a_pid_fuzzy_kpid(&this->ctx, jkp, jki, jkd);
    }
    void time(a_float_t jdt) { a_pid_set_dt(&this->ctx.pid, jdt); }
    void pos(a_float_t jmax) { a_pid_fuzzy_pos(&this->ctx, jmax); }
    void inc() { a_pid_fuzzy_inc(&this->ctx); }
    void off() { a_pid_fuzzy_off(&this->ctx); }
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
    a_float_t *den_p;

    void set_num_(const emscripten::val &jnum, a_float_t *input)
    {
        a_size_t num_n = jnum["length"].as<a_size_t>();
        this->num_p = floats(jnum, num_n * 2, input);
        a_tf_set_num(&this->ctx, num_n, this->num_p, this->num_p + num_n);
    }
    void set_den_(const emscripten::val &jden, a_float_t *output)
    {
        a_size_t den_n = jden["length"].as<a_size_t>();
        this->den_p = floats(jden, den_n * 2, output);
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
        free(this->num_p);
        free(this->den_p);
    }
    emscripten::val num()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.num_n, this->ctx.num_p));
    }
    void set_num(const emscripten::val &jnum)
    {
        this->set_num_(jnum, this->ctx.input);
    }
    emscripten::val den()
    {
        return emscripten::val(emscripten::typed_memory_view(this->ctx.den_n, this->ctx.den_p));
    }
    void set_den(const emscripten::val &jden)
    {
        this->set_den_(jden, this->ctx.output);
    }
    a_float_t iter(a_float_t jx)
    {
        return a_tf_iter(&this->ctx, jx);
    }
    void zero() { a_tf_zero(&this->ctx); }
};

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("f32_rsqrt", a_f32_rsqrt);
    emscripten::function("f64_rsqrt", a_f64_rsqrt);
    emscripten::constant("MF_NUL", 0);
    emscripten::function("mf_gauss", a_mf_gauss);
    emscripten::constant("MF_GAUSS", 1);
    emscripten::function("mf_gbell", a_mf_gbell);
    emscripten::constant("MF_GBELL", 2);
    emscripten::function("mf_sig", a_mf_sig);
    emscripten::constant("MF_SIG", 3);
    emscripten::function("mf_trap", a_mf_trap);
    emscripten::constant("MF_TRAP", 4);
    emscripten::function("mf_tri", a_mf_tri);
    emscripten::constant("MF_TRI", 5);
    emscripten::function("mf_z", a_mf_z);
    emscripten::constant("MF_Z", 6);
    emscripten::constant("PID_OFF", 0);
    emscripten::constant("PID_POS", 1);
    emscripten::constant("PID_INC", 2);
    emscripten::class_<pid>("pid")
        .constructor<a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("iter", &pid::iter)
        .function("zero", &pid::zero)
        .function("kpid", &pid::kpid)
        .function("time", &pid::time)
        .function("pos", &pid::pos)
        .function("inc", &pid::inc)
        .function("off", &pid::off);
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<unsigned int, a_float_t, emscripten::val, emscripten::val,
                     emscripten::val, emscripten::val, emscripten::val, a_float_t, a_float_t>()
        .constructor<unsigned int, a_float_t, emscripten::val, emscripten::val,
                     emscripten::val, emscripten::val, emscripten::val, a_float_t, a_float_t, a_float_t>()
        .function("iter", &pid_fuzzy::iter)
        .function("zero", &pid_fuzzy::zero)
        .function("buff", &pid_fuzzy::buff)
        .function("base", &pid_fuzzy::base)
        .function("kpid", &pid_fuzzy::kpid)
        .function("time", &pid_fuzzy::time)
        .function("pos", &pid_fuzzy::pos)
        .function("inc", &pid_fuzzy::inc)
        .function("off", &pid_fuzzy::off);
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
        .function("num", &tf::num)
        .function("set_num", &tf::set_num)
        .function("den", &tf::den)
        .function("set_den", &tf::set_den)
        .function("iter", &tf::iter)
        .function("zero", &tf::zero);
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
    emscripten::function("version", version);
}
