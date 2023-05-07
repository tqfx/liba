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
    pid(a_real_t jdt, a_real_t jmin, a_real_t jmax)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_inc(&this->ctx);
    }
    pid(a_real_t jdt, a_real_t jmin, a_real_t jmax, a_real_t jsum)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_pos(&this->ctx, jsum);
    }
    pid(a_real_t jdt, a_real_t jkp, a_real_t jki, a_real_t jkd, a_real_t jmin, a_real_t jmax)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
        a_pid_inc(&this->ctx);
    }
    pid(a_real_t jdt, a_real_t jkp, a_real_t jki, a_real_t jkd, a_real_t jmin, a_real_t jmax, a_real_t jsum)
    {
        a_pid_init(&this->ctx, jdt, jmin, jmax);
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
        a_pid_pos(&this->ctx, jsum);
    }
    ~pid() { a_pid_exit(&this->ctx); }
    a_real_t iter(a_real_t jset, a_real_t jfdb)
    {
        return a_pid_outv(&this->ctx, jset, jfdb);
    }
    void zero() { a_pid_zero(&this->ctx); }
    void kpid(a_real_t jkp, a_real_t jki, a_real_t jkd)
    {
        a_pid_kpid(&this->ctx, jkp, jki, jkd);
    }
    void time(a_real_t jdt) { a_pid_set_dt(&this->ctx, jdt); }
    void pos(a_real_t jmax) { a_pid_pos(&this->ctx, jmax); }
    void inc() { a_pid_inc(&this->ctx); }
    void off() { a_pid_off(&this->ctx); }
};

#include "a/fpid.h"

class fpid
{
    a_fpid_s ctx;
    a_real_t *me;
    a_real_t *mec;
    a_real_t *mkp;
    a_real_t *mki;
    a_real_t *mkd;
    a_vptr_t buf;

    a_real_t *from(emscripten::val x)
    {
        x = emscripten::val::array()["concat"].call<emscripten::val>("apply", emscripten::val::array(), x);
        a_uint_t num = x["length"].as<a_uint_t>();
        a_real_t *ptr = new a_real_t[num];
        for (a_uint_t i = 0; i < num; ++i)
        {
            ptr[i] = x[i].as<a_real_t>();
        }
        return ptr;
    }

public:
    fpid(a_uint_t jnum, a_real_t jdt, emscripten::val jme, emscripten::val jmec,
         emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd, a_real_t jmin, a_real_t jmax)
    {
        this->me = from(jme);
        this->mec = from(jmec);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        a_uint_t col = jmkp["length"].as<a_uint_t>();
        a_fpid_init(&this->ctx, jdt, col, this->me, this->mec,
                    this->mkp, this->mki, this->mkd, jmin, jmax);
        this->buf = malloc(A_FPID_BUF1(jnum));
        a_fpid_buf1(&this->ctx, this->buf, jnum);
        a_fpid_inc(&this->ctx);
    }
    fpid(a_uint_t jnum, a_real_t jdt, emscripten::val jme, emscripten::val jmec,
         emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd, a_real_t jmin, a_real_t jmax, a_real_t jsum)
    {
        fpid(jnum, jdt, jme, jmec, jmkp, jmki, jmkd, jmin, jmax);
        a_fpid_pos(&this->ctx, jsum);
    }
    ~fpid()
    {
        a_fpid_exit(&this->ctx);
        delete[] this->me;
        delete[] this->mec;
        delete[] this->mkp;
        delete[] this->mki;
        delete[] this->mkd;
        free(this->buf);
    }
    void buff(a_uint_t jmax)
    {
        this->buf = realloc(this->buf, A_FPID_BUF1(jmax));
        a_fpid_buf1(&this->ctx, this->buf, jmax);
    }
    void base(emscripten::val jme, emscripten::val jmec, emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd)
    {
        this->me = from(jme);
        this->mec = from(jmec);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        a_uint_t col = jmkp["length"].as<a_uint_t>();
        a_fpid_base(&this->ctx, col, this->me, this->mec, this->mkp, this->mki, this->mkd);
    }
    a_real_t iter(a_real_t jset, a_real_t jfdb)
    {
        return a_fpid_outv(&this->ctx, jset, jfdb);
    }
    void zero() { a_fpid_zero(&this->ctx); }
    void kpid(a_real_t jkp, a_real_t jki, a_real_t jkd)
    {
        a_fpid_kpid(&this->ctx, jkp, jki, jkd);
    }
    void time(a_real_t jdt) { a_pid_set_dt(&this->ctx.pid, jdt); }
    void pos(a_real_t jmax) { a_fpid_pos(&this->ctx, jmax); }
    void inc() { a_fpid_inc(&this->ctx); }
    void off() { a_fpid_off(&this->ctx); }
};

#include "a/polytrack.h"

class polytrack3
{
    a_polytrack3_s ctx;

public:
    polytrack3(a_real_t jt0, a_real_t jt1, a_real_t jq0, a_real_t jq1, a_real_t jv0 = 0, a_real_t jv1 = 0)
    {
        a_polytrack3_init(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1);
    }
    a_real_t pos(a_real_t jts)
    {
        return a_polytrack3_pos(&this->ctx, jts);
    }
    a_real_t vec(a_real_t jts)
    {
        return a_polytrack3_vec(&this->ctx, jts);
    }
    a_real_t acc(a_real_t jts)
    {
        return a_polytrack3_acc(&this->ctx, jts);
    }
    emscripten::val out(a_real_t jts)
    {
        a_real_t out[3];
        a_polytrack3_out(&this->ctx, jts, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack5
{
    a_polytrack5_s ctx;

public:
    polytrack5(a_real_t jt0, a_real_t jt1, a_real_t jq0, a_real_t jq1, a_real_t jv0 = 0, a_real_t jv1 = 0, a_real_t ja0 = 0, a_real_t ja1 = 0)
    {
        a_polytrack5_init(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1);
    }
    a_real_t pos(a_real_t jts)
    {
        return a_polytrack5_pos(&this->ctx, jts);
    }
    a_real_t vec(a_real_t jts)
    {
        return a_polytrack5_vec(&this->ctx, jts);
    }
    a_real_t acc(a_real_t jts)
    {
        return a_polytrack5_acc(&this->ctx, jts);
    }
    emscripten::val out(a_real_t jts)
    {
        a_real_t out[3];
        a_polytrack5_out(&this->ctx, jts, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack7
{
    a_polytrack7_s ctx;

public:
    polytrack7(a_real_t jt0, a_real_t jt1, a_real_t jq0, a_real_t jq1, a_real_t jv0 = 0, a_real_t jv1 = 0, a_real_t ja0 = 0, a_real_t ja1 = 0, a_real_t jj0 = 0, a_real_t jj1 = 0)
    {
        a_polytrack7_init(&this->ctx, jt0, jt1, jq0, jq1, jv0, jv1, ja0, ja1, jj0, jj1);
    }
    a_real_t pos(a_real_t jts)
    {
        return a_polytrack7_pos(&this->ctx, jts);
    }
    a_real_t vec(a_real_t jts)
    {
        return a_polytrack7_vec(&this->ctx, jts);
    }
    a_real_t acc(a_real_t jts)
    {
        return a_polytrack7_acc(&this->ctx, jts);
    }
    a_real_t jer(a_real_t jts)
    {
        return a_polytrack7_jer(&this->ctx, jts);
    }
    emscripten::val out(a_real_t jts)
    {
        a_real_t out[4];
        a_polytrack7_out(&this->ctx, jts, out);
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
        .constructor<a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .function("iter", &pid::iter)
        .function("zero", &pid::zero)
        .function("kpid", &pid::kpid)
        .function("time", &pid::time)
        .function("pos", &pid::pos)
        .function("inc", &pid::inc)
        .function("off", &pid::off);
    emscripten::class_<fpid>("fpid")
        .constructor<a_uint_t, a_real_t, emscripten::val, emscripten::val,
                     emscripten::val, emscripten::val, emscripten::val, a_real_t, a_real_t>()
        .constructor<a_uint_t, a_real_t, emscripten::val, emscripten::val,
                     emscripten::val, emscripten::val, emscripten::val, a_real_t, a_real_t, a_real_t>()
        .function("iter", &fpid::iter)
        .function("zero", &fpid::zero)
        .function("buff", &fpid::buff)
        .function("base", &fpid::base)
        .function("kpid", &fpid::kpid)
        .function("time", &fpid::time)
        .function("pos", &fpid::pos)
        .function("inc", &fpid::inc)
        .function("off", &fpid::off);
    emscripten::class_<polytrack3>("polytrack3")
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .function("pos", &polytrack3::pos)
        .function("vec", &polytrack3::vec)
        .function("acc", &polytrack3::acc)
        .function("out", &polytrack3::out);
    emscripten::class_<polytrack5>("polytrack5")
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .function("pos", &polytrack5::pos)
        .function("vec", &polytrack5::vec)
        .function("acc", &polytrack5::acc)
        .function("out", &polytrack5::out);
    emscripten::class_<polytrack7>("polytrack7")
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
        .constructor<a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t, a_real_t>()
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
