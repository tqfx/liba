#include "a/a.h"
#include <emscripten/bind.h>
#if defined(__has_feature) && __has_feature(address_sanitizer)
#include <sanitizer/lsan_interface.h>
#endif /* -fsanitize=address */

namespace
{

static emscripten::val js_concat(emscripten::val x)
{
    emscripten::val val = emscripten::val::array();
    return val["concat"].call<emscripten::val>("apply", val, x);
}

static a_float *js_array_num_get(emscripten::val const &x, a_float *p, a_size n)
{
    a_size length = x["length"].as<a_size>();
    n = (n < length ? length : n) * sizeof(a_float);
    p = a_cast_s(a_float *, a_alloc(p, n));
    for (a_size i = 0; i < length; ++i)
    {
        p[i] = x[i].as<a_float>();
    }
    return p;
}

static emscripten::val js_array_num_new(a_float const *p, a_size n)
{
    return emscripten::val(emscripten::typed_memory_view(n, p));
}

static a_u32 hash_bkdr(std::string const &str, a_u32 val)
{
    return a_hash_bkdr_(str.data(), str.length(), val);
}

static a_u32 hash_sdbm(std::string const &str, a_u32 val)
{
    return a_hash_sdbm_(str.data(), str.length(), val);
}

} /* namespace */

#include "a/crc.h"

struct crc8
{
    a_u8 table[0x100];
    std::vector<a_byte> _pack;
    A_INLINE emscripten::val get_table() const
    {
        return emscripten::val(emscripten::typed_memory_view(0x100, table));
    }
    A_INLINE a_u8 operator()(std::string const &block, a_u8 value = 0) const
    {
        return a_crc8(table, block.data(), block.length(), value);
    }
    A_INLINE emscripten::val pack(std::string const &block, a_u8 value = 0)
    {
        size_t n = block.length();
        size_t m = block.length() + sizeof(value);
        if (_pack.size() < m) { _pack.resize(m); }
        std::copy(block.data(), block.data() + n, _pack.data());
        *(_pack.data() + n) = a_crc8(table, block.data(), n, value);
        return emscripten::val(emscripten::typed_memory_view(m, _pack.data()));
    }
    A_INLINE crc8 *gen(a_u8 poly, bool reversed = false)
    {
        reversed ? a_crc8l_init(table, poly) : a_crc8m_init(table, poly);
        return this;
    }
    A_INLINE crc8(a_u8 poly, bool reversed = false)
    {
        gen(poly, reversed);
    }
};

struct crc16
{
    a_u16 table[0x100];
    std::vector<a_byte> _pack;
    a_u16 (*eval)(a_u16 const[0x100], void const *, a_size, a_u16);
    A_INLINE emscripten::val get_table() const
    {
        return emscripten::val(emscripten::typed_memory_view(0x100, table));
    }
    A_INLINE a_u16 operator()(std::string const &block, a_u16 value = 0) const
    {
        return eval(table, block.data(), block.length(), value);
    }
    A_INLINE emscripten::val pack(std::string const &block, a_u16 value = 0)
    {
        size_t n = block.length();
        size_t m = block.length() + sizeof(value);
        if (_pack.size() < m) { _pack.resize(m); }
        std::copy(block.data(), block.data() + n, _pack.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = _pack.data() + n;
        eval == a_crc16m ? a_u16_setb(p, value) : a_u16_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, _pack.data()));
    }
    A_INLINE crc16 *gen(a_u16 poly, bool reversed = false)
    {
        if (reversed)
        {
            a_crc16l_init(table, poly);
            eval = a_crc16l;
        }
        else
        {
            a_crc16m_init(table, poly);
            eval = a_crc16m;
        }
        return this;
    }
    A_INLINE crc16(a_u16 poly, bool reversed = false)
    {
        gen(poly, reversed);
    }
};

struct crc32
{
    a_u32 table[0x100];
    std::vector<a_byte> _pack;
    a_u32 (*eval)(a_u32 const[0x100], void const *, a_size, a_u32);
    A_INLINE emscripten::val get_table() const
    {
        return emscripten::val(emscripten::typed_memory_view(0x100, table));
    }
    A_INLINE a_u32 operator()(std::string const &block, a_u32 value = 0) const
    {
        return eval(table, block.data(), block.length(), value);
    }
    A_INLINE emscripten::val pack(std::string const &block, a_u32 value = 0)
    {
        size_t n = block.length();
        size_t m = block.length() + sizeof(value);
        if (_pack.size() < m) { _pack.resize(m); }
        std::copy(block.data(), block.data() + n, _pack.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = _pack.data() + n;
        eval == a_crc32m ? a_u32_setb(p, value) : a_u32_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, _pack.data()));
    }
    A_INLINE crc32 *gen(a_u32 poly, bool reversed = false)
    {
        if (reversed)
        {
            a_crc32l_init(table, poly);
            eval = a_crc32l;
        }
        else
        {
            a_crc32m_init(table, poly);
            eval = a_crc32m;
        }
        return this;
    }
    A_INLINE crc32(a_u32 poly, bool reversed = false)
    {
        gen(poly, reversed);
    }
};

#if defined(WASM_BIGINT)
struct crc64
{
    a_u64 table[0x100];
    std::vector<a_byte> _pack;
    a_u64 (*eval)(a_u64 const[0x100], void const *, a_size, a_u64);
    A_INLINE emscripten::val get_table() const
    {
        return emscripten::val(emscripten::typed_memory_view(0x100, table));
    }
    A_INLINE emscripten::val operator()(std::string const &block, a_u64 value = 0) const
    {
        return emscripten::val(eval(table, block.data(), block.length(), value));
    }
    A_INLINE emscripten::val pack(std::string const &block, a_u64 value = 0)
    {
        size_t n = block.length();
        size_t m = block.length() + sizeof(value);
        if (_pack.size() < m) { _pack.resize(m); }
        std::copy(block.data(), block.data() + n, _pack.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = _pack.data() + n;
        eval == a_crc64m ? a_u64_setb(p, value) : a_u64_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, _pack.data()));
    }
    A_INLINE crc64 *gen(a_u64 poly, bool reversed = false)
    {
        if (reversed)
        {
            a_crc64l_init(table, poly);
            eval = a_crc64l;
        }
        else
        {
            a_crc64m_init(table, poly);
            eval = a_crc64m;
        }
        return this;
    }
    A_INLINE crc64(a_u64 poly, bool reversed = false)
    {
        gen(poly, reversed);
    }
};
#endif /* WASM_BIGINT */

#include "a/hpf.h"

struct hpf: public a_hpf
{
    A_INLINE hpf(a_float fc, a_float ts)
    {
        alpha = A_HPF_GEN(fc, ts);
        output = 0;
        input = 0;
    }
    A_INLINE hpf(a_float _alpha)
    {
        alpha = _alpha;
        output = 0;
        input = 0;
    }
    A_INLINE hpf *gen(a_float fc, a_float ts)
    {
        a_hpf::gen(fc, ts);
        return this;
    }
    A_INLINE a_float operator()(a_float x)
    {
        return a_hpf::operator()(x);
    }
    A_INLINE hpf *zero()
    {
        a_hpf::zero();
        return this;
    }
};

#include "a/lpf.h"

struct lpf: public a_lpf
{
    A_INLINE lpf(a_float fc, a_float ts)
    {
        alpha = A_LPF_GEN(fc, ts);
        output = 0;
    }
    A_INLINE lpf(a_float _alpha)
    {
        alpha = _alpha;
        output = 0;
    }
    A_INLINE lpf *gen(a_float fc, a_float ts)
    {
        a_lpf::gen(fc, ts);
        return this;
    }
    A_INLINE a_float operator()(a_float x)
    {
        return a_lpf::operator()(x);
    }
    A_INLINE lpf *zero()
    {
        a_lpf::zero();
        return this;
    }
};

#include "a/mf.h"

struct mf
{
    static unsigned int const NUL;
    static a_float gauss(a_float x, a_float sigma, a_float c)
    {
        return a_mf_gauss(x, sigma, c);
    }
    static unsigned int const GAUSS;
    static a_float gauss2(a_float x, a_float sigma1, a_float c1, a_float sigma2, a_float c2)
    {
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2);
    }
    static unsigned int const GAUSS2;
    static a_float gbell(a_float x, a_float a, a_float b, a_float c)
    {
        return a_mf_gbell(x, a, b, c);
    }
    static unsigned int const GBELL;
    static a_float sig(a_float x, a_float a, a_float c)
    {
        return a_mf_sig(x, a, c);
    }
    static unsigned int const SIG;
    static a_float dsig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2)
    {
        return a_mf_dsig(x, a1, c1, a2, c2);
    }
    static unsigned int const DSIG;
    static a_float psig(a_float x, a_float a1, a_float c1, a_float a2, a_float c2)
    {
        return a_mf_psig(x, a1, c1, a2, c2);
    }
    static unsigned int const PSIG;
    static a_float trap(a_float x, a_float a, a_float b, a_float c, a_float d)
    {
        return a_mf_trap(x, a, b, c, d);
    }
    static unsigned int const TRAP;
    static a_float tri(a_float x, a_float a, a_float b, a_float c)
    {
        return a_mf_tri(x, a, b, c);
    }
    static unsigned int const TRI;
    static a_float lins(a_float x, a_float a, a_float b)
    {
        return a_mf_lins(x, a, b);
    }
    static unsigned int const LINS;
    static a_float linz(a_float x, a_float a, a_float b)
    {
        return a_mf_linz(x, a, b);
    }
    static unsigned int const LINZ;
    static a_float s(a_float x, a_float a, a_float b)
    {
        return a_mf_s(x, a, b);
    }
    static unsigned int const S;
    static a_float z(a_float x, a_float a, a_float b)
    {
        return a_mf_z(x, a, b);
    }
    static unsigned int const Z;
    static a_float pi(a_float x, a_float a, a_float b, a_float c, a_float d)
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

struct pid: public a_pid
{
    A_INLINE pid *kpid(a_float _kp, a_float _ki, a_float _kd)
    {
        a_pid::kpid(_kp, _ki, _kd);
        return this;
    }
    A_INLINE a_float run(a_float set, a_float _fdb)
    {
        return a_pid::run(set, _fdb);
    }
    A_INLINE a_float pos(a_float set, a_float _fdb)
    {
        return a_pid::pos(set, _fdb);
    }
    A_INLINE a_float inc(a_float set, a_float _fdb)
    {
        return a_pid::inc(set, _fdb);
    }
    A_INLINE pid *zero()
    {
        a_pid::zero();
        return this;
    }
    A_INLINE pid()
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

#include "a/pid_fuzzy.h"

struct pid_fuzzy: public a_pid_fuzzy
{
    A_INLINE pid_fuzzy *rule(emscripten::val const &_me,
                             emscripten::val const &_mec,
                             emscripten::val const &_mkp,
                             emscripten::val const &_mki,
                             emscripten::val const &_mkd)
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u;
        order = _me["length"].as<unsigned int>();
        u.p = me;
        emscripten::val val = js_concat(_me);
        me = js_array_num_get(val, u.o, 0);
        val.delete_(val);
        u.p = mec;
        val = js_concat(_mec);
        mec = js_array_num_get(val, u.o, 0);
        val.delete_(val);
        u.p = mkp;
        val = js_concat(_mkp);
        mkp = js_array_num_get(val, u.o, 0);
        val.delete_(val);
        u.p = mki;
        val = js_concat(_mki);
        mki = js_array_num_get(val, u.o, 0);
        val.delete_(val);
        u.p = mkd;
        val = js_concat(_mkd);
        mkd = js_array_num_get(val, u.o, 0);
        val.delete_(val);
        return this;
    }
    A_INLINE pid_fuzzy *set_op(unsigned int _op)
    {
        a_pid_fuzzy::set_op(_op);
        return this;
    }
    A_INLINE pid_fuzzy *set_block(unsigned int num)
    {
        void *ptr = a_alloc(a_pid_fuzzy_block(this), A_PID_FUZZY_BLOCK(num));
        a_pid_fuzzy_set_block(this, ptr, num);
        return this;
    }
    A_INLINE pid_fuzzy *kpid(a_float _kp, a_float _ki, a_float _kd)
    {
        a_pid_fuzzy::kpid(_kp, _ki, _kd);
        return this;
    }
    A_INLINE a_float run(a_float set, a_float fdb)
    {
        return a_pid_fuzzy::run(set, fdb);
    }
    A_INLINE a_float pos(a_float set, a_float fdb)
    {
        return a_pid_fuzzy::pos(set, fdb);
    }
    A_INLINE a_float inc(a_float set, a_float fdb)
    {
        return a_pid_fuzzy::inc(set, fdb);
    }
    A_INLINE pid_fuzzy *zero()
    {
        a_pid_fuzzy::zero();
        return this;
    }
    A_INLINE pid_fuzzy()
    {
        pid.kp = kp = 1;
        pid.ki = ki = 0;
        pid.kd = kd = 0;
        pid.summax = +A_FLOAT_INF;
        pid.summin = -A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        me = nullptr;
        mec = nullptr;
        mkp = nullptr;
        mki = nullptr;
        mkd = nullptr;
        idx = nullptr;
        val = nullptr;
        order = 0;
        block = 0;
        op = a_fuzzy_equ;
        a_pid_fuzzy_init(this);
    }
    A_INLINE ~pid_fuzzy()
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u;
        a_alloc(a_pid_fuzzy_block(this), 0);
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
    A_INLINE unsigned int get_block() const { return block; }
    A_INLINE a_float get_summax() const { return pid.summax; }
    A_INLINE void set_summax(a_float summax) { pid.summax = summax; }
    A_INLINE a_float get_summin() const { return pid.summin; }
    A_INLINE void set_summin(a_float summin) { pid.summin = summin; }
    A_INLINE a_float get_outmax() const { return pid.outmax; }
    A_INLINE void set_outmax(a_float outmax) { pid.outmax = outmax; }
    A_INLINE a_float get_outmin() const { return pid.outmin; }
    A_INLINE void set_outmin(a_float outmin) { pid.outmin = outmin; }
    A_INLINE a_float get_sum() const { return pid.sum; }
    A_INLINE a_float get_out() const { return pid.out; }
    A_INLINE a_float get_fdb() const { return pid.fdb; }
    A_INLINE a_float get_err() const { return pid.err; }
    static unsigned int const CAP;
    static unsigned int const CAP_ALGEBRA;
    static unsigned int const CAP_BOUNDED;
    static unsigned int const CUP;
    static unsigned int const CUP_ALGEBRA;
    static unsigned int const CUP_BOUNDED;
    static unsigned int const EQU;
};
unsigned int const pid_fuzzy::CAP = A_PID_FUZZY_CAP;
unsigned int const pid_fuzzy::CAP_ALGEBRA = A_PID_FUZZY_CAP_ALGEBRA;
unsigned int const pid_fuzzy::CAP_BOUNDED = A_PID_FUZZY_CAP_BOUNDED;
unsigned int const pid_fuzzy::CUP = A_PID_FUZZY_CUP;
unsigned int const pid_fuzzy::CUP_ALGEBRA = A_PID_FUZZY_CUP_ALGEBRA;
unsigned int const pid_fuzzy::CUP_BOUNDED = A_PID_FUZZY_CUP_BOUNDED;
unsigned int const pid_fuzzy::EQU = A_PID_FUZZY_EQU;

#include "a/pid_neuro.h"

struct pid_neuro: public a_pid_neuro
{
    A_INLINE pid_neuro *kpid(a_float _k, a_float kp, a_float ki, a_float kd)
    {
        a_pid_neuro::kpid(_k, kp, ki, kd);
        return this;
    }
    A_INLINE pid_neuro *wpid(a_float _wp, a_float _wi, a_float _wd)
    {
        a_pid_neuro::wpid(_wp, _wi, _wd);
        return this;
    }
    A_INLINE a_float run(a_float set, a_float fdb)
    {
        return a_pid_neuro::run(set, fdb);
    }
    A_INLINE a_float inc(a_float set, a_float fdb)
    {
        return a_pid_neuro::inc(set, fdb);
    }
    A_INLINE pid_neuro *zero()
    {
        a_pid_neuro::zero();
        return this;
    }
    A_INLINE pid_neuro()
    {
        pid.summax = +A_FLOAT_INF;
        pid.summin = -A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        pid.kp = k = 1;
        pid.ki = 0;
        pid.kd = 0;
        wp = A_FLOAT_C(0.1);
        wi = A_FLOAT_C(0.1);
        wd = A_FLOAT_C(0.1);
        a_pid_neuro_init(this);
    }
    A_INLINE a_float get_kp() const { return pid.kp; }
    A_INLINE void set_kp(a_float kp) { pid.kp = kp; }
    A_INLINE a_float get_ki() const { return pid.ki; }
    A_INLINE void set_ki(a_float ki) { pid.ki = ki; }
    A_INLINE a_float get_kd() const { return pid.kd; }
    A_INLINE void set_kd(a_float kd) { pid.kd = kd; }
    A_INLINE a_float get_outmax() const { return pid.outmax; }
    A_INLINE void set_outmax(a_float outmax) { pid.outmax = outmax; }
    A_INLINE a_float get_outmin() const { return pid.outmin; }
    A_INLINE void set_outmin(a_float outmin) { pid.outmin = outmin; }
    A_INLINE a_float get_out() const { return pid.out; }
    A_INLINE a_float get_fdb() const { return pid.fdb; }
    A_INLINE a_float get_err() const { return pid.err; }
};

#include "a/tf.h"

struct tf: public a_tf
{
    void set_num_(emscripten::val const &_num, a_float *num)
    {
        a_uint num_n = _num["length"].as<a_uint>();
        a_float *p = js_array_num_get(_num, num, a_size_c(num_n) * 2);
        a_tf_set_num(this, num_n, p, p + num_n);
    }
    void set_den_(emscripten::val const &_den, a_float *den)
    {
        a_uint den_n = _den["length"].as<a_uint>();
        a_float *p = js_array_num_get(_den, den, a_size_c(den_n) * 2);
        a_tf_set_den(this, den_n, p, p + den_n);
    }
    A_INLINE tf(emscripten::val const &num, emscripten::val const &den)
    {
        set_num_(num, nullptr);
        set_den_(den, nullptr);
    }
    ~tf()
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u;
        u.p = num_p;
        a_alloc(u.o, 0);
        u.p = den_p;
        a_alloc(u.o, 0);
    }
    A_INLINE emscripten::val get_input() const { return js_array_num_new(input, num_n); }
    A_INLINE emscripten::val get_output() const { return js_array_num_new(output, den_n); }
    A_INLINE emscripten::val get_num() const { return js_array_num_new(num_p, num_n); }
    A_INLINE emscripten::val get_den() const { return js_array_num_new(den_p, den_n); }
    A_INLINE tf *set_num(emscripten::val const &num)
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u = {num_p};
        set_num_(num, u.o);
        return this;
    }
    A_INLINE tf *set_den(emscripten::val const &den)
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u = {den_p};
        set_den_(den, u.o);
        return this;
    }
    A_INLINE a_float operator()(a_float x) const
    {
        return a_tf::operator()(x);
    }
    A_INLINE tf *zero()
    {
        a_tf::zero();
        return this;
    }
};

#include "a/trajbell.h"

struct trajbell: public a_trajbell
{
    A_INLINE a_float gen(a_float _jm, a_float _am, a_float _vm, a_float _p0, a_float _p1,
                         a_float _v0 = 0, a_float _v1 = 0)
    {
        return a_trajbell::gen(_jm, _am, _vm, _p0, _p1, _v0, _v1);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajbell::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajbell::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajbell::acc(x); }
    A_INLINE a_float jer(a_float x) const { return a_trajbell::jer(x); }
};

#include "a/trajpoly3.h"

struct trajpoly3: public a_trajpoly3
{
    A_INLINE trajpoly3(a_float ts, a_float p0, a_float p1,
                       a_float v0 = 0, a_float v1 = 0)
    {
        a_trajpoly3_gen(this, ts, p0, p1, v0, v1);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajpoly3::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajpoly3::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajpoly3::acc(x); }
    A_INLINE emscripten::val get_p() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
};

#include "a/trajpoly5.h"

struct trajpoly5: public a_trajpoly5
{
    A_INLINE trajpoly5(a_float ts, a_float p0, a_float p1,
                       a_float v0 = 0, a_float v1 = 0,
                       a_float a0 = 0, a_float a1 = 0)
    {
        a_trajpoly5_gen(this, ts, p0, p1, v0, v1, a0, a1);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajpoly5::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajpoly5::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajpoly5::acc(x); }
    A_INLINE emscripten::val get_p() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
};

#include "a/trajpoly7.h"

struct trajpoly7: public a_trajpoly7
{
    A_INLINE trajpoly7(a_float ts, a_float p0, a_float p1,
                       a_float v0 = 0, a_float v1 = 0,
                       a_float a0 = 0, a_float a1 = 0,
                       a_float j0 = 0, a_float j1 = 0)
    {
        a_trajpoly7_gen(this, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajpoly7::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajpoly7::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajpoly7::acc(x); }
    A_INLINE a_float jer(a_float x) const { return a_trajpoly7::jer(x); }
    A_INLINE emscripten::val get_p() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val get_v() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val get_a() const { return js_array_num_new(a, A_LEN(a)); }
    A_INLINE emscripten::val get_j() const { return js_array_num_new(j, A_LEN(j)); }
};

#include "a/trajtrap.h"

struct trajtrap: public a_trajtrap
{
    A_INLINE a_float gen(a_float vm, a_float _ac, a_float _de, a_float _p0, a_float _p1,
                         a_float _v0 = 0, a_float _v1 = 0)
    {
        return a_trajtrap::gen(vm, _ac, _de, _p0, _p1, _v0, _v1);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajtrap::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajtrap::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajtrap::acc(x); }
};

#include "a/version.h"
#undef a_version_check

struct version: public a_version
{
    A_INLINE a_int cmp(version const &ver) const
    {
        return a_version::cmp(ver);
    }
    A_INLINE a_bool operator<(version const &ver) const
    {
        return a_version::operator<(ver);
    }
    A_INLINE a_bool operator>(version const &ver) const
    {
        return a_version::operator>(ver);
    }
    A_INLINE a_bool operator<=(version const &ver) const
    {
        return a_version::operator<=(ver);
    }
    A_INLINE a_bool operator>=(version const &ver) const
    {
        return a_version::operator>=(ver);
    }
    A_INLINE a_bool operator==(version const &ver) const
    {
        return a_version::operator==(ver);
    }
    A_INLINE a_bool operator!=(version const &ver) const
    {
        return a_version::operator!=(ver);
    }
    A_INLINE version *parse(std::string const &ver)
    {
        a_version::parse(ver.c_str());
        return this;
    }
    A_INLINE void set_alpha(std::string const &str)
    {
        a_version::set_alpha(str.c_str());
    }
    A_INLINE std::string get_alpha() const
    {
        char str[sizeof(alpha) + 1];
        a_version::get_alpha(str);
        return std::string(str);
    }
    A_INLINE std::string toString() const
    {
        char str[48];
        a_version::tostr(str, sizeof(str));
        return std::string(str);
    }
    A_INLINE version(unsigned int _major = 0,
                     unsigned int _minor = 0,
                     unsigned int _third = 0,
                     unsigned int _extra = 0)
    {
        major = _major;
        minor = _minor;
        third = _third;
        extra = _extra;
        alpha[0] = '.';
        alpha[1] = 0;
        alpha[2] = 0;
        alpha[3] = 0;
    }
    static unsigned int const MAJOR;
    static unsigned int const MINOR;
    static unsigned int const PATCH;
    static a_u32 const TWEAK;
};
unsigned int const version::MAJOR = A_VERSION_MAJOR;
unsigned int const version::MINOR = A_VERSION_MINOR;
unsigned int const version::PATCH = A_VERSION_PATCH;
a_u32 const version::TWEAK = A_VERSION_TWEAK;

#include "a/math.h"
#if __has_warning("-Wglobal-constructors")
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif /* -Wglobal-constructors */
EMSCRIPTEN_BINDINGS(liba) // NOLINT
{
    emscripten::function("isqrt", a_u32_sqrt);
    emscripten::function("rsqrt", a_f64_rsqrt);
    emscripten::function("hash_bkdr", hash_bkdr);
    emscripten::function("hash_sdbm", hash_sdbm);
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
    emscripten::class_<crc8>("crc8")
        .constructor<a_u8>()
        .constructor<a_u8, bool>()
        .property("table", &crc8::get_table)
        .function("eval", &crc8::operator())
        .function("pack", &crc8::pack)
        .function("gen", &crc8::gen, emscripten::allow_raw_pointers());
    emscripten::class_<crc16>("crc16")
        .constructor<a_u16>()
        .constructor<a_u16, bool>()
        .property("table", &crc16::get_table)
        .function("eval", &crc16::operator())
        .function("pack", &crc16::pack)
        .function("gen", &crc16::gen, emscripten::allow_raw_pointers());
    emscripten::class_<crc32>("crc32")
        .constructor<a_u32>()
        .constructor<a_u32, bool>()
        .property("table", &crc32::get_table)
        .function("eval", &crc32::operator())
        .function("pack", &crc32::pack)
        .function("gen", &crc32::gen, emscripten::allow_raw_pointers());
#if defined(WASM_BIGINT)
    emscripten::class_<crc64>("crc64")
        .constructor<a_u64>()
        .constructor<a_u64, bool>()
        .property("table", &crc64::get_table)
        .function("eval", &crc64::operator())
        .function("pack", &crc64::pack)
        .function("gen", &crc64::gen, emscripten::allow_raw_pointers());
#endif /* WASM_BIGINT */
    emscripten::class_<hpf>("hpf")
        .constructor<a_float>()
        .constructor<a_float, a_float>()
        .function("iter", &hpf::operator())
        .function("gen", &hpf::gen, emscripten::allow_raw_pointers())
        .function("zero", &hpf::zero, emscripten::allow_raw_pointers())
        .property<a_float const, void>("alpha", &hpf::alpha)
        .property<a_float const, void>("output", &hpf::output)
        .property<a_float const, void>("input", &hpf::input);
    emscripten::class_<lpf>("lpf")
        .constructor<a_float>()
        .constructor<a_float, a_float>()
        .function("iter", &lpf::operator())
        .function("gen", &lpf::gen, emscripten::allow_raw_pointers())
        .function("zero", &lpf::zero, emscripten::allow_raw_pointers())
        .property<a_float const, void>("alpha", &lpf::alpha)
        .property<a_float const, void>("output", &lpf::output);
    emscripten::class_<pid>("pid")
        .constructor<>()
        .function("kpid", &pid::kpid, emscripten::allow_raw_pointers())
        .function("zero", &pid::zero, emscripten::allow_raw_pointers())
        .function("run", &pid::run)
        .function("pos", &pid::pos)
        .function("inc", &pid::inc)
        .property<a_float, void>("kp", &pid::kp)
        .property<a_float, void>("ki", &pid::ki)
        .property<a_float, void>("kd", &pid::kd)
        .property<a_float, void>("summax", &pid::summax)
        .property<a_float, void>("summin", &pid::summin)
        .property<a_float, void>("outmax", &pid::outmax)
        .property<a_float, void>("outmin", &pid::outmin)
        .property<a_float const, void>("sum", &pid::sum)
        .property<a_float const, void>("out", &pid::out)
        .property<a_float const, void>("fdb", &pid::fdb)
        .property<a_float const, void>("err", &pid::err);
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<>()
        .function("op", &pid_fuzzy::set_op, emscripten::allow_raw_pointers())
        .function("rule", &pid_fuzzy::rule, emscripten::allow_raw_pointers())
        .function("set_block", &pid_fuzzy::set_block, emscripten::allow_raw_pointers())
        .function("kpid", &pid_fuzzy::kpid, emscripten::allow_raw_pointers())
        .function("zero", &pid_fuzzy::zero, emscripten::allow_raw_pointers())
        .function("run", &pid_fuzzy::run)
        .function("pos", &pid_fuzzy::pos)
        .function("inc", &pid_fuzzy::inc)
        .class_property("CAP", &pid_fuzzy::CAP)
        .class_property("CAP_ALGEBRA", &pid_fuzzy::CAP_ALGEBRA)
        .class_property("CAP_BOUNDED", &pid_fuzzy::CAP_BOUNDED)
        .class_property("CUP", &pid_fuzzy::CUP)
        .class_property("CUP_ALGEBRA", &pid_fuzzy::CUP_ALGEBRA)
        .class_property("CUP_BOUNDED", &pid_fuzzy::CUP_BOUNDED)
        .class_property("EQU", &pid_fuzzy::EQU)
        .property<a_float, void>("kp", &pid_fuzzy::kp)
        .property<a_float, void>("ki", &pid_fuzzy::ki)
        .property<a_float, void>("kd", &pid_fuzzy::kd)
        .property("summax", &pid_fuzzy::get_summax, &pid_fuzzy::set_summax)
        .property("summin", &pid_fuzzy::get_summin, &pid_fuzzy::set_summin)
        .property("outmax", &pid_fuzzy::get_outmax, &pid_fuzzy::set_outmax)
        .property("outmin", &pid_fuzzy::get_outmin, &pid_fuzzy::set_outmin)
        .property("sum", &pid_fuzzy::get_sum)
        .property("out", &pid_fuzzy::get_out)
        .property("fdb", &pid_fuzzy::get_fdb)
        .property("err", &pid_fuzzy::get_err)
        .property<unsigned int const, void>("order", &pid_fuzzy::order)
        .property("block", &pid_fuzzy::get_block, &pid_fuzzy::set_block);
    emscripten::class_<pid_neuro>("pid_neuro")
        .constructor<>()
        .function("kpid", &pid_neuro::kpid, emscripten::allow_raw_pointers())
        .function("wpid", &pid_neuro::wpid, emscripten::allow_raw_pointers())
        .function("zero", &pid_neuro::zero, emscripten::allow_raw_pointers())
        .function("run", &pid_neuro::run)
        .function("inc", &pid_neuro::inc)
        .property<a_float, void>("k", &pid_neuro::k)
        .property("kp", &pid_neuro::get_kp, &pid_neuro::set_kp)
        .property("ki", &pid_neuro::get_ki, &pid_neuro::set_ki)
        .property("kd", &pid_neuro::get_kd, &pid_neuro::set_kd)
        .property<a_float, void>("wp", &pid_neuro::wp)
        .property<a_float, void>("wi", &pid_neuro::wi)
        .property<a_float, void>("wd", &pid_neuro::wd)
        .property("outmax", &pid_neuro::get_outmax, &pid_neuro::set_outmax)
        .property("outmin", &pid_neuro::get_outmin, &pid_neuro::set_outmin)
        .property("out", &pid_neuro::get_out)
        .property("fdb", &pid_neuro::get_fdb)
        .property("err", &pid_neuro::get_err)
        .property<a_float const, void>("ec", &pid_neuro::ec);
    emscripten::class_<tf>("tf")
        .constructor<emscripten::val, emscripten::val>()
        .function("set_num", &tf::set_num, emscripten::allow_raw_pointers())
        .function("set_den", &tf::set_den, emscripten::allow_raw_pointers())
        .function("zero", &tf::zero, emscripten::allow_raw_pointers())
        .function("iter", &tf::operator())
        .property("input", &tf::get_input)
        .property("output", &tf::get_output)
        .property("num", &tf::get_num, &tf::set_num)
        .property("den", &tf::get_den, &tf::set_den);
    emscripten::class_<trajbell>("trajbell")
        .constructor<>()
        .function("gen", &trajbell::gen)
        .function("pos", &trajbell::pos)
        .function("vel", &trajbell::vel)
        .function("acc", &trajbell::acc)
        .function("jer", &trajbell::jer)
        .property<a_float const, void>("t", &trajbell::t)
        .property<a_float const, void>("tv", &trajbell::tv)
        .property<a_float const, void>("ta", &trajbell::ta)
        .property<a_float const, void>("td", &trajbell::td)
        .property<a_float const, void>("taj", &trajbell::taj)
        .property<a_float const, void>("tdj", &trajbell::tdj)
        .property<a_float const, void>("p0", &trajbell::p0)
        .property<a_float const, void>("p1", &trajbell::p1)
        .property<a_float const, void>("v0", &trajbell::v0)
        .property<a_float const, void>("v1", &trajbell::v1)
        .property<a_float const, void>("vm", &trajbell::vm)
        .property<a_float const, void>("jm", &trajbell::jm)
        .property<a_float const, void>("am", &trajbell::am)
        .property<a_float const, void>("dm", &trajbell::dm);
    emscripten::class_<trajpoly3>("trajpoly3")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly3::pos)
        .function("vel", &trajpoly3::vel)
        .function("acc", &trajpoly3::acc)
        .property("p", &trajpoly3::get_p)
        .property("v", &trajpoly3::get_v)
        .property("a", &trajpoly3::get_a);
    emscripten::class_<trajpoly5>("trajpoly5")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly5::pos)
        .function("vel", &trajpoly5::vel)
        .function("acc", &trajpoly5::acc)
        .property("p", &trajpoly5::get_p)
        .property("v", &trajpoly5::get_v)
        .property("a", &trajpoly5::get_a);
    emscripten::class_<trajpoly7>("trajpoly7")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly7::pos)
        .function("vel", &trajpoly7::vel)
        .function("acc", &trajpoly7::acc)
        .function("jer", &trajpoly7::jer)
        .property("p", &trajpoly7::get_p)
        .property("v", &trajpoly7::get_v)
        .property("a", &trajpoly7::get_a)
        .property("j", &trajpoly7::get_j);
    emscripten::class_<trajtrap>("trajtrap")
        .constructor<>()
        .function("gen", &trajtrap::gen)
        .function("pos", &trajtrap::pos)
        .function("vel", &trajtrap::vel)
        .function("acc", &trajtrap::acc)
        .property<a_float const, void>("t", &trajtrap::t)
        .property<a_float const, void>("p0", &trajtrap::p0)
        .property<a_float const, void>("p1", &trajtrap::p1)
        .property<a_float const, void>("v0", &trajtrap::v0)
        .property<a_float const, void>("v1", &trajtrap::v1)
        .property<a_float const, void>("vc", &trajtrap::vc)
        .property<a_float const, void>("ta", &trajtrap::ta)
        .property<a_float const, void>("td", &trajtrap::td)
        .property<a_float const, void>("pa", &trajtrap::pa)
        .property<a_float const, void>("pd", &trajtrap::pd)
        .property<a_float const, void>("ac", &trajtrap::ac)
        .property<a_float const, void>("de", &trajtrap::de);
    emscripten::class_<version>("version")
        .constructor<>()
        .constructor<a_uint>()
        .constructor<a_uint, a_uint>()
        .constructor<a_uint, a_uint, a_uint>()
        .constructor<a_uint, a_uint, a_uint, a_uint>()
        .property<a_uint, void>("major", &a_version::major)
        .property<a_uint, void>("minor", &a_version::minor)
        .property<a_uint, void>("third", &a_version::third)
        .property<a_uint, void>("extra", &a_version::extra)
        .property("alpha", &version::get_alpha, &version::set_alpha)
        .function("parse", &version::parse, emscripten::allow_raw_pointers())
        .function("cmp", &version::cmp)
        .function("lt", &version::operator<)
        .function("gt", &version::operator>)
        .function("le", &version::operator<=)
        .function("ge", &version::operator>=)
        .function("eq", &version::operator==)
        .function("ne", &version::operator!=)
        .function("toString", &version::toString)
        .class_property("MAJOR", &version::MAJOR)
        .class_property("MINOR", &version::MINOR)
        .class_property("PATCH", &version::PATCH)
        .class_property("TWEAK", &version::TWEAK)
        .class_function("check", &a_version_check);
    emscripten::constant("VERSION", std::string(A_VERSION));
#if defined(__has_feature) && __has_feature(address_sanitizer)
    emscripten::function("do_leak_check", &__lsan_do_recoverable_leak_check);
#endif /* -fsanitize=address */
}
