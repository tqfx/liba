#include "a/host/a.h"
#include <emscripten/bind.h>

static emscripten::val js_concat(emscripten::val x)
{
    emscripten::val empty = emscripten::val::array();
    return empty["concat"].call<emscripten::val>("apply", empty, x);
}

static a_float_t *js_array_num_get(emscripten::val const &x, a_size_t n, a_float_t *p)
{
    p = a_float_c(*, a_alloc(p, sizeof(a_float_t) * n));
    a_size_t length = x["length"].as<a_size_t>();
    for (a_size_t i = 0; i < length; ++i)
    {
        p[i] = x[i].as<a_float_t>();
    }
    return p;
}

static emscripten::val js_array_num_new(a_float_t const *p, a_size_t n)
{
    return emscripten::val(emscripten::typed_memory_view(n, p));
}

#include "a/mf.h"

class mf
{
public:
    static unsigned int const NUL;
    static a_float_t gauss(a_float_t x, a_float_t sigma, a_float_t c)
    {
        return a_mf_gauss(x, sigma, c);
    }
    static unsigned int const GAUSS;
    static a_float_t gauss2(a_float_t x, a_float_t sigma1, a_float_t c1, a_float_t sigma2, a_float_t c2)
    {
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2);
    }
    static unsigned int const GAUSS2;
    static a_float_t gbell(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    {
        return a_mf_gbell(x, a, b, c);
    }
    static unsigned int const GBELL;
    static a_float_t sig(a_float_t x, a_float_t a, a_float_t c)
    {
        return a_mf_sig(x, a, c);
    }
    static unsigned int const SIG;
    static a_float_t dsig(a_float_t x, a_float_t a1, a_float_t c1, a_float_t a2, a_float_t c2)
    {
        return a_mf_dsig(x, a1, c1, a2, c2);
    }
    static unsigned int const DSIG;
    static a_float_t psig(a_float_t x, a_float_t a1, a_float_t c1, a_float_t a2, a_float_t c2)
    {
        return a_mf_psig(x, a1, c1, a2, c2);
    }
    static unsigned int const PSIG;
    static a_float_t trap(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d)
    {
        return a_mf_trap(x, a, b, c, d);
    }
    static unsigned int const TRAP;
    static a_float_t tri(a_float_t x, a_float_t a, a_float_t b, a_float_t c)
    {
        return a_mf_tri(x, a, b, c);
    }
    static unsigned int const TRI;
    static a_float_t lins(a_float_t x, a_float_t a, a_float_t b)
    {
        return a_mf_lins(x, a, b);
    }
    static unsigned int const LINS;
    static a_float_t linz(a_float_t x, a_float_t a, a_float_t b)
    {
        return a_mf_linz(x, a, b);
    }
    static unsigned int const LINZ;
    static a_float_t s(a_float_t x, a_float_t a, a_float_t b)
    {
        return a_mf_s(x, a, b);
    }
    static unsigned int const S;
    static a_float_t z(a_float_t x, a_float_t a, a_float_t b)
    {
        return a_mf_z(x, a, b);
    }
    static unsigned int const Z;
    static a_float_t pi(a_float_t x, a_float_t a, a_float_t b, a_float_t c, a_float_t d)
    {
        return a_mf_pi(x, a, b, c, d);
    }
    static unsigned int const PI;
};
unsigned int const mf::NUL = A_MF_NUL;
unsigned int const mf::GAUSS = A_MF_GAUSS;
unsigned int const mf::GAUSS2 = A_MF_GAUSS2;
unsigned int const mf::GBELL = A_MF_GBELL;
unsigned int const mf::SIG = A_MF_SIG;
unsigned int const mf::DSIG = A_MF_DSIG;
unsigned int const mf::PSIG = A_MF_PSIG;
unsigned int const mf::TRAP = A_MF_TRAP;
unsigned int const mf::TRI = A_MF_TRI;
unsigned int const mf::LINS = A_MF_LINS;
unsigned int const mf::LINZ = A_MF_LINZ;
unsigned int const mf::S = A_MF_S;
unsigned int const mf::Z = A_MF_Z;
unsigned int const mf::PI = A_MF_PI;

#include "a/pid.h"

class pid: public a_pid_s
{
public:
    static unsigned int const OFF;
    static unsigned int const POS;
    static unsigned int const INC;
    pid()
    {
        kp = 1;
        ki = 0;
        kd = 0;
        summax = +A_FLOAT_INF;
        summin = -A_FLOAT_INF;
        outmax = +A_FLOAT_INF;
        outmin = -A_FLOAT_INF;
        a_pid_init(this);
    }
};
unsigned int const pid::OFF = A_PID_OFF;
unsigned int const pid::POS = A_PID_POS;
unsigned int const pid::INC = A_PID_INC;

#include "a/pid/fuzzy.h"

class pid_fuzzy: public a_pid_fuzzy_s
{
public:
    static unsigned int const CAP;
    static unsigned int const CAP_ALGEBRA;
    static unsigned int const CAP_BOUNDED;
    static unsigned int const CUP;
    static unsigned int const CUP_ALGEBRA;
    static unsigned int const CUP_BOUNDED;
    static unsigned int const EQU;
    pid_fuzzy()
    {
        pid.kp = 1;
        pid.ki = 0;
        pid.kd = 0;
        pid.summax = +A_FLOAT_INF;
        pid.summin = -A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        kp = 1;
        ki = 0;
        kd = 0;
        me = nullptr;
        mec = nullptr;
        mkp = nullptr;
        mki = nullptr;
        mkd = nullptr;
        idx = nullptr;
        val = nullptr;
        op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
        order = 0;
        joint = 0;
        a_pid_fuzzy_init(this);
    }
    ~pid_fuzzy()
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u;
        a_alloc(a_pid_fuzzy_joint(this), 0);
        u.p = me;
        a_alloc(u.o, 0);
        u.p = mec;
        a_alloc(u.o, 0);
        u.p = mkp;
        a_alloc(u.o, 0);
        u.p = mki;
        a_alloc(u.o, 0);
        u.p = mkd;
        a_alloc(u.o, 0);
    }
    unsigned int get_joint() const { return joint; }
    void set_joint(unsigned int num)
    {
        void *ptr = a_alloc(a_pid_fuzzy_joint(this), A_PID_FUZZY_JOINT(num));
        a_pid_fuzzy_set_joint(reinterpret_cast<a_pid_fuzzy_s *>(this), ptr, num);
    }
    a_float_t get_summax() const { return pid.summax; }
    void set_summax(a_float_t summax) { pid.summax = summax; }
    a_float_t get_summin() const { return pid.summin; }
    void set_summin(a_float_t summin) { pid.summin = summin; }
    a_float_t get_outmax() const { return pid.outmax; }
    void set_outmax(a_float_t outmax) { pid.outmax = outmax; }
    a_float_t get_outmin() const { return pid.outmin; }
    void set_outmin(a_float_t outmin) { pid.outmin = outmin; }
    a_float_t get_out() const { return pid.out; }
    a_float_t get_fdb() const { return pid.fdb; }
    a_float_t get_err() const { return pid.err; }
};
unsigned int const pid_fuzzy::CAP = A_PID_FUZZY_CAP;
unsigned int const pid_fuzzy::CAP_ALGEBRA = A_PID_FUZZY_CAP_ALGEBRA;
unsigned int const pid_fuzzy::CAP_BOUNDED = A_PID_FUZZY_CAP_BOUNDED;
unsigned int const pid_fuzzy::CUP = A_PID_FUZZY_CUP;
unsigned int const pid_fuzzy::CUP_ALGEBRA = A_PID_FUZZY_CUP_ALGEBRA;
unsigned int const pid_fuzzy::CUP_BOUNDED = A_PID_FUZZY_CUP_BOUNDED;
unsigned int const pid_fuzzy::EQU = A_PID_FUZZY_EQU;

#include "a/pid/neuron.h"

class pid_neuron: public a_pid_neuron_s
{
public:
    pid_neuron()
    {
        pid.summax = +A_FLOAT_INF;
        pid.summin = -A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        pid.kp = 0;
        pid.ki = 0;
        pid.kd = 0;
        k = 1;
        wp = A_FLOAT_C(0.1);
        wi = A_FLOAT_C(0.1);
        wd = A_FLOAT_C(0.1);
        a_pid_neuron_init(this);
    }
    a_float_t get_kp() const { return pid.kp; }
    void set_kp(a_float_t kp) { pid.kp = kp; }
    a_float_t get_ki() const { return pid.ki; }
    void set_ki(a_float_t ki) { pid.ki = ki; }
    a_float_t get_kd() const { return pid.kd; }
    void set_kd(a_float_t kd) { pid.kd = kd; }
    a_float_t get_wp() const { return wp; }
    void set_wp(a_float_t _wp) { wp = _wp; }
    a_float_t get_wi() const { return wi; }
    void set_wi(a_float_t _wi) { wi = _wi; }
    a_float_t get_wd() const { return wd; }
    void set_wd(a_float_t _wd) { wd = _wd; }
    a_float_t get_outmax() const { return pid.outmax; }
    void set_outmax(a_float_t outmax) { pid.outmax = outmax; }
    a_float_t get_outmin() const { return pid.outmin; }
    void set_outmin(a_float_t outmin) { pid.outmin = outmin; }
    a_float_t get_out() const { return pid.out; }
    a_float_t get_fdb() const { return pid.fdb; }
    a_float_t get_err() const { return pid.err; }
    a_float_t get_ec() const { return ec; }
};

#include "a/polytraj.h"

class polytraj3: public a_polytraj3_s
{
public:
    polytraj3(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
              a_float_t v0 = 0, a_float_t v1 = 0)
    {
        a_polytraj3_gen(this, t0, t1, q0, q1, v0, v1);
    }
    emscripten::val get_q() const { return js_array_num_new(q, A_LEN(q)); }
    emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
};

class polytraj5: public a_polytraj5_s
{
public:
    polytraj5(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
              a_float_t v0 = 0, a_float_t v1 = 0,
              a_float_t a0 = 0, a_float_t a1 = 0)
    {
        a_polytraj5_gen(this, t0, t1, q0, q1, v0, v1, a0, a1);
    }
    emscripten::val get_q() const { return js_array_num_new(q, A_LEN(q)); }
    emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
};

class polytraj7: public a_polytraj7_s
{
public:
    polytraj7(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
              a_float_t v0 = 0, a_float_t v1 = 0,
              a_float_t a0 = 0, a_float_t a1 = 0,
              a_float_t j0 = 0, a_float_t j1 = 0)
    {
        a_polytraj7_gen(this, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    }
    emscripten::val get_q() const { return js_array_num_new(q, A_LEN(q)); }
    emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
    emscripten::val get_j() const { return js_array_num_new(j, A_LEN(j)); }
};

#include "a/tf.h"

class tf: public a_tf_s
{
    void set_num_(emscripten::val const &_num, a_float_t *num)
    {
        a_uint_t num_n = _num["length"].as<a_uint_t>();
        a_float_t *p = js_array_num_get(_num, a_size_c(, num_n) * 2, num);
        a_tf_set_num(this, num_n, p, p + num_n);
    }
    void set_den_(emscripten::val const &_den, a_float_t *den)
    {
        a_uint_t den_n = _den["length"].as<a_uint_t>();
        a_float_t *p = js_array_num_get(_den, a_size_c(, den_n) * 2, den);
        a_tf_set_den(this, den_n, p, p + den_n);
    }

public:
    tf(emscripten::val const &num, emscripten::val const &den)
    {
        set_num_(num, nullptr);
        set_den_(den, nullptr);
    }
    ~tf()
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u;
        u.p = num_p;
        a_alloc(u.o, 0);
        u.p = den_p;
        a_alloc(u.o, 0);
    }
    emscripten::val get_input() const { return js_array_num_new(input, num_n); }
    emscripten::val get_output() const { return js_array_num_new(output, den_n); }
    emscripten::val get_num() const { return js_array_num_new(num_p, num_n); }
    emscripten::val get_den() const { return js_array_num_new(den_p, den_n); }
    tf *set_num(emscripten::val const &num)
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u = {num_p};
        set_num_(num, u.o);
        return this;
    }
    tf *set_den(emscripten::val const &den)
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u = {den_p};
        set_den_(den, u.o);
        return this;
    }
};

#include "a/math.h"
#include "a/version.h"
#undef a_version_check
#if __has_warning("-Wglobal-constructors")
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif /* -Wglobal-constructors */
EMSCRIPTEN_BINDINGS(liba) // NOLINT
{
    emscripten::function("f32_rsqrt", a_f32_rsqrt);
    emscripten::function("f64_rsqrt", a_f64_rsqrt);
    emscripten::class_<mf>("mf")
        .class_property("NUL", &mf::NUL)
        .class_function("gauss", &mf::gauss)
        .class_property("GAUSS", &mf::GAUSS)
        .class_function("gauss2", &mf::gauss2)
        .class_property("GAUSS2", &mf::GAUSS2)
        .class_function("gbell", &mf::gbell)
        .class_property("GBELL", &mf::GBELL)
        .class_function("sig", &mf::sig)
        .class_property("SIG", &mf::SIG)
        .class_function("dsig", &mf::dsig)
        .class_property("DSIG", &mf::DSIG)
        .class_function("psig", &mf::psig)
        .class_property("PSIG", &mf::PSIG)
        .class_function("trap", &mf::trap)
        .class_property("TRAP", &mf::TRAP)
        .class_function("tri", &mf::tri)
        .class_property("TRI", &mf::TRI)
        .class_function("lins", &mf::lins)
        .class_property("LINS", &mf::LINS)
        .class_function("linz", &mf::linz)
        .class_property("LINZ", &mf::LINZ)
        .class_function("s", &mf::s)
        .class_property("S", &mf::S)
        .class_function("z", &mf::z)
        .class_property("Z", &mf::Z)
        .class_function("pi", &mf::pi)
        .class_property("PI", &mf::PI);
    emscripten::class_<pid>("pid")
        .constructor<>()
        .function("kpid", emscripten::optional_override([](pid *ctx, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_kpid(reinterpret_cast<a_pid_s *>(ctx), kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("off", emscripten::optional_override([](pid *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_off(reinterpret_cast<a_pid_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("pos", emscripten::optional_override([](pid *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_pos(reinterpret_cast<a_pid_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("inc", emscripten::optional_override([](pid *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_inc(reinterpret_cast<a_pid_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid *ctx) {
                      a_pid_zero(reinterpret_cast<a_pid_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .class_property("OFF", &pid::OFF)
        .class_property("POS", &pid::POS)
        .class_property("INC", &pid::INC)
        .property<a_float_t, void>("kp", &pid::kp)
        .property<a_float_t, void>("ki", &pid::ki)
        .property<a_float_t, void>("kd", &pid::kd)
        .property<a_float_t, void>("summax", &pid::summax)
        .property<a_float_t, void>("summin", &pid::summin)
        .property<a_float_t, void>("outmax", &pid::outmax)
        .property<a_float_t, void>("outmin", &pid::outmin)
        .property<a_float_t, void>("out", &pid::out)
        .property<a_float_t, void>("fdb", &pid::fdb)
        .property<a_float_t, void>("err", &pid::err);
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<>()
        .function("op", emscripten::optional_override([](pid_fuzzy *ctx, unsigned int op) {
                      a_pid_fuzzy_set_op(reinterpret_cast<a_pid_fuzzy_s *>(ctx), op);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("rule", emscripten::optional_override([](pid_fuzzy *ctx, emscripten::val const &me, emscripten::val const &mec, emscripten::val const &mkp, emscripten::val const &mki, emscripten::val const &mkd) {
                      union
                      {
                          a_float_t const *p;
                          a_float_t *o;
                      } u;
                      ctx->order = me["length"].as<unsigned int>();
                      u.p = ctx->me;
                      ctx->me = js_array_num_get(js_concat(me), me["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mec;
                      ctx->mec = js_array_num_get(js_concat(mec), mec["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mkp;
                      ctx->mkp = js_array_num_get(js_concat(mkp), mkp["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mki;
                      ctx->mki = js_array_num_get(js_concat(mki), mki["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mkd;
                      ctx->mkd = js_array_num_get(js_concat(mkd), mkd["length"].as<a_size_t>(), u.o);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("set_joint", emscripten::optional_override([](pid_fuzzy *ctx, unsigned int num) {
                      ctx->set_joint(num);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("kpid", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_fuzzy_kpid(reinterpret_cast<a_pid_fuzzy_s *>(ctx), kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("off", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_fuzzy_off(reinterpret_cast<a_pid_fuzzy_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("pos", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_fuzzy_pos(reinterpret_cast<a_pid_fuzzy_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("inc", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_fuzzy_inc(reinterpret_cast<a_pid_fuzzy_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid_fuzzy *ctx) {
                      a_pid_fuzzy_zero(reinterpret_cast<a_pid_fuzzy_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .class_property("CAP", &pid_fuzzy::CAP)
        .class_property("CAP_ALGEBRA", &pid_fuzzy::CAP_ALGEBRA)
        .class_property("CAP_BOUNDED", &pid_fuzzy::CAP_BOUNDED)
        .class_property("CUP", &pid_fuzzy::CUP)
        .class_property("CUP_ALGEBRA", &pid_fuzzy::CUP_ALGEBRA)
        .class_property("CUP_BOUNDED", &pid_fuzzy::CUP_BOUNDED)
        .class_property("EQU", &pid_fuzzy::EQU)
        .property<a_float_t, void>("kp", &pid_fuzzy::kp)
        .property<a_float_t, void>("ki", &pid_fuzzy::ki)
        .property<a_float_t, void>("kd", &pid_fuzzy::kd)
        .property("summax", &pid_fuzzy::get_summax, &pid_fuzzy::set_summax)
        .property("summin", &pid_fuzzy::get_summin, &pid_fuzzy::set_summin)
        .property("outmax", &pid_fuzzy::get_outmax, &pid_fuzzy::set_outmax)
        .property("outmin", &pid_fuzzy::get_outmin, &pid_fuzzy::set_outmin)
        .property("out", &pid_fuzzy::get_out)
        .property("fdb", &pid_fuzzy::get_fdb)
        .property("err", &pid_fuzzy::get_err)
        .property<unsigned int, void>("order", &pid_fuzzy::order)
        .property("joint", &pid_fuzzy::get_joint, &pid_fuzzy::set_joint);
    emscripten::class_<pid_neuron>("pid_neuron")
        .constructor<>()
        .function("kpid", emscripten::optional_override([](pid_neuron *ctx, a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_neuron_kpid(reinterpret_cast<a_pid_neuron_s *>(ctx), k, kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("wpid", emscripten::optional_override([](pid_neuron *ctx, a_float_t wp, a_float_t wi, a_float_t wd) {
                      a_pid_neuron_wpid(reinterpret_cast<a_pid_neuron_s *>(ctx), wp, wi, wd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("off", emscripten::optional_override([](pid_neuron *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_neuron_off(reinterpret_cast<a_pid_neuron_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("inc", emscripten::optional_override([](pid_neuron *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_neuron_inc(reinterpret_cast<a_pid_neuron_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid_neuron *ctx) {
                      a_pid_neuron_zero(reinterpret_cast<a_pid_neuron_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .property<a_float_t, void>("k", &pid_neuron::k)
        .property("kp", &pid_neuron::get_kp, &pid_neuron::set_kp)
        .property("ki", &pid_neuron::get_ki, &pid_neuron::set_ki)
        .property("kd", &pid_neuron::get_kd, &pid_neuron::set_kd)
        .property("wp", &pid_neuron::get_wp, &pid_neuron::set_wp)
        .property("wi", &pid_neuron::get_wi, &pid_neuron::set_wi)
        .property("wd", &pid_neuron::get_wd, &pid_neuron::set_wd)
        .property("outmax", &pid_neuron::get_outmax, &pid_neuron::set_outmax)
        .property("outmin", &pid_neuron::get_outmin, &pid_neuron::set_outmin)
        .property("out", &pid_neuron::get_out)
        .property("fdb", &pid_neuron::get_fdb)
        .property("err", &pid_neuron::get_err)
        .property("ec", &pid_neuron::get_ec);
    emscripten::class_<polytraj3>("polytraj3")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytraj3 *ctx, a_float_t dt) {
                      return a_polytraj3_pos(reinterpret_cast<polytraj3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytraj3 *ctx, a_float_t dt) {
                      return a_polytraj3_vel(reinterpret_cast<polytraj3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytraj3 *ctx, a_float_t dt) {
                      return a_polytraj3_acc(reinterpret_cast<polytraj3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .property("q", &polytraj3::get_q)
        .property("v", &polytraj3::get_v)
        .property("a", &polytraj3::get_a);
    emscripten::class_<polytraj5>("polytraj5")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytraj5 *ctx, a_float_t dt) {
                      return a_polytraj5_pos(reinterpret_cast<polytraj5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytraj5 *ctx, a_float_t dt) {
                      return a_polytraj5_vel(reinterpret_cast<polytraj5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytraj5 *ctx, a_float_t dt) {
                      return a_polytraj5_acc(reinterpret_cast<polytraj5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .property("q", &polytraj5::get_q)
        .property("v", &polytraj5::get_v)
        .property("a", &polytraj5::get_a);
    emscripten::class_<polytraj7>("polytraj7")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytraj7 *ctx, a_float_t dt) {
                      return a_polytraj7_pos(reinterpret_cast<polytraj7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytraj7 *ctx, a_float_t dt) {
                      return a_polytraj7_vel(reinterpret_cast<polytraj7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytraj7 *ctx, a_float_t dt) {
                      return a_polytraj7_acc(reinterpret_cast<polytraj7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("jer", emscripten::optional_override([](polytraj7 *ctx, a_float_t dt) {
                      return a_polytraj7_jer(reinterpret_cast<polytraj7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .property("q", &polytraj7::get_q)
        .property("v", &polytraj7::get_v)
        .property("a", &polytraj7::get_a)
        .property("j", &polytraj7::get_j);
    emscripten::class_<tf>("tf")
        .constructor<emscripten::val, emscripten::val>()
        .function("iter", emscripten::optional_override([](tf *ctx, a_float_t x) {
                      return a_tf_iter(reinterpret_cast<a_tf_s *>(ctx), x);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](tf *ctx) {
                      a_tf_zero(reinterpret_cast<a_tf_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("set_num", &tf::set_num, emscripten::allow_raw_pointers())
        .function("set_den", &tf::set_den, emscripten::allow_raw_pointers())
        .property("input", &tf::get_input)
        .property("output", &tf::get_output)
        .property("num", &tf::get_num, &tf::set_num)
        .property("den", &tf::get_den, &tf::set_den);
    emscripten::class_<a::version>("version")
        .constructor<>()
        .constructor<a_uint_t>()
        .constructor<a_uint_t, a_uint_t>()
        .constructor<a_uint_t, a_uint_t, a_uint_t>()
        .property<unsigned int, void>("major", &a::version::major)
        .property<unsigned int, void>("minor", &a::version::minor)
        .property<unsigned int, void>("patch", &a::version::patch)
        .function("toString", emscripten::optional_override([](a::version const *ctx) {
                      return std::to_string(ctx->major) + "." + std::to_string(ctx->minor) + "." + std::to_string(ctx->patch);
                  }),
                  emscripten::allow_raw_pointers())
        .function("parse", emscripten::optional_override([](a::version *ctx, std::string const &ver) {
                      a_version_parse(ctx, ver.c_str());
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("lt", &a::version::operator<)
        .function("gt", &a::version::operator>)
        .function("le", &a::version::operator<=)
        .function("ge", &a::version::operator>=)
        .function("eq", &a::version::operator==)
        .function("ne", &a::version::operator!=)
        .function("cmp", &a_version_cmp, emscripten::allow_raw_pointers())
        .class_function("check", emscripten::optional_override([](unsigned int major, unsigned int minor, unsigned int patch) {
                            return a_version_check(major, minor, patch);
                        }),
                        emscripten::allow_raw_pointers())
        .class_property("MAJOR", &a::version::MAJOR)
        .class_property("MINOR", &a::version::MINOR)
        .class_property("PATCH", &a::version::PATCH)
        .class_property("TWEAK", &a::version::TWEAK);
    emscripten::constant("VERSION", std::string(A_VERSION));
}
