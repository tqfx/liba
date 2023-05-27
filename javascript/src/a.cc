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
    ~pid() { a_pid_exit(&this->ctx); }
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

class pid_fuzzy
{
    a_pid_fuzzy_s ctx;
    a_float_t *me;
    a_float_t *mec;
    a_float_t *mkp;
    a_float_t *mki;
    a_float_t *mkd;
    void *buf;

    a_float_t *from(emscripten::val x)
    {
        x = emscripten::val::array()["concat"].call<emscripten::val>("apply", emscripten::val::array(), x);
        unsigned int num = x["length"].as<unsigned int>();
        a_float_t *ptr = new a_float_t[num];
        for (unsigned int i = 0; i < num; ++i)
        {
            ptr[i] = x[i].as<a_float_t>();
        }
        return ptr;
    }

public:
    pid_fuzzy(unsigned int jnum, a_float_t jdt, emscripten::val jme, emscripten::val jmec,
              emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd, a_float_t jmin, a_float_t jmax)
    {
        this->me = from(jme);
        this->mec = from(jmec);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        unsigned int col = jmkp["length"].as<unsigned int>();
        a_pid_fuzzy_init(&this->ctx, jdt, col, this->me, this->mec,
                         this->mkp, this->mki, this->mkd, jmin, jmax);
        this->buf = malloc(A_PID_FUZZY_BUF1(jnum));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jnum);
        a_pid_fuzzy_inc(&this->ctx);
    }
    pid_fuzzy(unsigned int jnum, a_float_t jdt, emscripten::val jme, emscripten::val jmec,
              emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd, a_float_t jmin, a_float_t jmax, a_float_t jsum)
    {
        pid_fuzzy(jnum, jdt, jme, jmec, jmkp, jmki, jmkd, jmin, jmax);
        a_pid_fuzzy_pos(&this->ctx, jsum);
    }
    ~pid_fuzzy()
    {
        a_pid_fuzzy_exit(&this->ctx);
        delete[] this->me;
        delete[] this->mec;
        delete[] this->mkp;
        delete[] this->mki;
        delete[] this->mkd;
        free(this->buf);
    }
    void buff(unsigned int jmax)
    {
        this->buf = realloc(this->buf, A_PID_FUZZY_BUF1(jmax));
        a_pid_fuzzy_buf1(&this->ctx, this->buf, jmax);
    }
    void base(emscripten::val jme, emscripten::val jmec, emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd)
    {
        this->me = from(jme);
        this->mec = from(jmec);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
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
    polytrack3(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1, a_float_t jv0 = 0, a_float_t jv1 = 0)
    {
        a_polytrack3_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack3_pos(&this->ctx, jdt);
    }
    a_float_t vec(a_float_t jdt)
    {
        return a_polytrack3_vec(&this->ctx, jdt);
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
    polytrack5(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1, a_float_t jv0 = 0, a_float_t jv1 = 0, a_float_t ja0 = 0, a_float_t ja1 = 0)
    {
        a_polytrack5_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack5_pos(&this->ctx, jdt);
    }
    a_float_t vec(a_float_t jdt)
    {
        return a_polytrack5_vec(&this->ctx, jdt);
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
    polytrack7(a_float_t jt0, a_float_t jt1, a_float_t jq0, a_float_t jq1, a_float_t jv0 = 0, a_float_t jv1 = 0, a_float_t ja0 = 0, a_float_t ja1 = 0, a_float_t jj0 = 0, a_float_t jj1 = 0)
    {
        a_polytrack7_gen(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, jj0, jj1);
    }
    a_float_t pos(a_float_t jdt)
    {
        return a_polytrack7_pos(&this->ctx, jdt);
    }
    a_float_t vec(a_float_t jdt)
    {
        return a_polytrack7_vec(&this->ctx, jdt);
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
        .function("vec", &polytrack3::vec)
        .function("acc", &polytrack3::acc)
        .function("out", &polytrack3::out);
    emscripten::class_<polytrack5>("polytrack5")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", &polytrack5::pos)
        .function("vec", &polytrack5::vec)
        .function("acc", &polytrack5::acc)
        .function("out", &polytrack5::out);
    emscripten::class_<polytrack7>("polytrack7")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", &polytrack7::pos)
        .function("vec", &polytrack7::vec)
        .function("acc", &polytrack7::acc)
        .function("jer", &polytrack7::jer)
        .function("out", &polytrack7::out);
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
    emscripten::function("version", version);
}
