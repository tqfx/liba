#include "a/a.h"
#include <emscripten/bind.h>
#if defined(__has_feature) && __has_feature(address_sanitizer)
#include <sanitizer/lsan_interface.h>
#endif /* -fsanitize=address */

namespace
{

struct js_array_num
{
    unsigned int idx, num;
    a_float *ptr;
};

static A_INLINE void js_array_num_init(js_array_num &buf, a_float const *ptr = nullptr, unsigned int num = 0)
{
    union
    {
        a_float const *p;
        a_float *o;
    } u = {ptr};
    buf.idx = 0;
    buf.num = num;
    buf.ptr = u.o;
}

static unsigned int js_array_num_len(emscripten::val const &x, int dim = 8) // NOLINT(misc-no-recursion)
{
    unsigned int num = 0;
    unsigned int i = 0, n = x["length"].as<unsigned int>();
    for (--dim; i < n; ++i)
    {
        emscripten::val const &o = x[i];
        if (o.isNumber()) { ++num; }
        else if (o.isArray() && dim > 0)
        {
            num += js_array_num_len(o, dim);
        }
    }
    return num;
}

static void js_array_num_ptr(emscripten::val const &x, js_array_num &buf, int dim = 8) // NOLINT(misc-no-recursion)
{
    unsigned int i = 0, n = x["length"].as<unsigned int>();
    for (--dim; i < n; ++i)
    {
        emscripten::val const &o = x[i];
        if (o.isNumber())
        {
            buf.ptr[buf.idx++] = o.as<a_float>();
        }
        else if (o.isArray() && dim > 0)
        {
            js_array_num_ptr(o, buf, dim);
        }
    }
}

static void js_array_num_get(emscripten::val const &x, js_array_num &buf)
{
    unsigned int n = js_array_num_len(x);
    if (n > buf.num)
    {
        buf.ptr = a_cast_s(a_float *, a_alloc(buf.ptr, sizeof(a_float) * n));
    }
    js_array_num_ptr(x, buf);
    buf.num = n;
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
    std::vector<a_byte> pack_;
    A_INLINE emscripten::val table_r() const
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
        if (pack_.size() < m) { pack_.resize(m); }
        std::copy(block.data(), block.data() + n, pack_.data());
        *(pack_.data() + n) = a_crc8(table, block.data(), n, value);
        return emscripten::val(emscripten::typed_memory_view(m, pack_.data()));
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
    std::vector<a_byte> pack_;
    a_u16 (*eval)(a_u16 const[0x100], void const *, a_size, a_u16);
    A_INLINE emscripten::val table_r() const
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
        if (pack_.size() < m) { pack_.resize(m); }
        std::copy(block.data(), block.data() + n, pack_.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = pack_.data() + n;
        eval == a_crc16m ? a_u16_setb(p, value) : a_u16_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, pack_.data()));
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
    std::vector<a_byte> pack_;
    a_u32 (*eval)(a_u32 const[0x100], void const *, a_size, a_u32);
    A_INLINE emscripten::val table_r() const
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
        if (pack_.size() < m) { pack_.resize(m); }
        std::copy(block.data(), block.data() + n, pack_.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = pack_.data() + n;
        eval == a_crc32m ? a_u32_setb(p, value) : a_u32_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, pack_.data()));
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
    std::vector<a_byte> pack_;
    a_u64 (*eval)(a_u64 const[0x100], void const *, a_size, a_u64);
    A_INLINE emscripten::val table_r() const
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
        if (pack_.size() < m) { pack_.resize(m); }
        std::copy(block.data(), block.data() + n, pack_.data());
        value = eval(table, block.data(), n, value);
        a_byte *p = pack_.data() + n;
        eval == a_crc64m ? a_u64_setb(p, value) : a_u64_setl(p, value);
        return emscripten::val(emscripten::typed_memory_view(m, pack_.data()));
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
    A_INLINE a_float alpha_r() const { return alpha; }
    A_INLINE a_float output_r() const { return output; }
    A_INLINE a_float input_r() const { return input; }
    A_INLINE hpf(a_float fc, a_float ts)
    {
        alpha = A_HPF_GEN(fc, ts);
        output = 0;
        input = 0;
    }
    A_INLINE hpf(a_float alpha_)
    {
        alpha = alpha_;
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
    A_INLINE a_float alpha_r() const { return alpha; }
    A_INLINE a_float output_r() const { return output; }
    A_INLINE lpf(a_float fc, a_float ts)
    {
        alpha = A_LPF_GEN(fc, ts);
        output = 0;
    }
    A_INLINE lpf(a_float alpha_)
    {
        alpha = alpha_;
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
    A_INLINE pid *set_kpid(a_float kp_, a_float ki_, a_float kd_)
    {
        a_pid::set_kpid(kp_, ki_, kd_);
        return this;
    }
    A_INLINE a_float run(a_float set, a_float fdb_)
    {
        return a_pid::run(set, fdb_);
    }
    A_INLINE a_float pos(a_float set, a_float fdb_)
    {
        return a_pid::pos(set, fdb_);
    }
    A_INLINE a_float inc(a_float set, a_float fdb_)
    {
        return a_pid::inc(set, fdb_);
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
    A_INLINE a_float kp_r() const { return kp; }
    A_INLINE void kp_w(a_float kp_) { kp = kp_; }
    A_INLINE a_float ki_r() const { return ki; }
    A_INLINE void ki_w(a_float ki_) { ki = ki_; }
    A_INLINE a_float kd_r() const { return kd; }
    A_INLINE void kd_w(a_float kd_) { kd = kd_; }
    A_INLINE a_float summax_r() const { return summax; }
    A_INLINE void summax_w(a_float summax_) { summax = summax_; }
    A_INLINE a_float summin_r() const { return summin; }
    A_INLINE void summin_w(a_float summin_) { summin = summin_; }
    A_INLINE a_float outmax_r() const { return outmax; }
    A_INLINE void outmax_w(a_float outmax_) { outmax = outmax_; }
    A_INLINE a_float outmin_r() const { return outmin; }
    A_INLINE void outmin_w(a_float outmin_) { outmin = outmin_; }
    A_INLINE a_float sum_r() const { return sum; }
    A_INLINE a_float out_r() const { return out; }
    A_INLINE a_float fdb_r() const { return fdb; }
    A_INLINE a_float err_r() const { return err; }
};

#include "a/pid_fuzzy.h"
#include "a/math.h"

struct pid_fuzzy: public a_pid_fuzzy
{
    A_INLINE pid_fuzzy *set_rule(emscripten::val const &me_,
                                 emscripten::val const &mec_,
                                 emscripten::val const &mkp_,
                                 emscripten::val const &mki_,
                                 emscripten::val const &mkd_)
    {
        js_array_num buf;
        js_array_num_init(buf, me);
        js_array_num_get(me_, buf);
        me = buf.ptr;
        js_array_num_init(buf, mec);
        js_array_num_get(mec_, buf);
        mec = buf.ptr;
        js_array_num_init(buf, mkp);
        js_array_num_get(mkp_, buf);
        nrule = a_u32_sqrt(buf.num);
        mkp = buf.ptr;
        js_array_num_init(buf, mki);
        js_array_num_get(mki_, buf);
        mki = buf.ptr;
        js_array_num_init(buf, mkd);
        js_array_num_get(mkd_, buf);
        mkd = buf.ptr;
        return this;
    }
    A_INLINE pid_fuzzy *set_opr(unsigned int opr_)
    {
        a_pid_fuzzy::set_opr(opr_);
        return this;
    }
    A_INLINE pid_fuzzy *set_nfuzz(unsigned int num)
    {
        void *ptr = a_alloc(a_pid_fuzzy::bfuzz(), A_PID_FUZZY_BFUZZ(num));
        a_pid_fuzzy::set_bfuzz(ptr, num);
        return this;
    }
    A_INLINE pid_fuzzy *set_kpid(a_float kp_, a_float ki_, a_float kd_)
    {
        a_pid_fuzzy::set_kpid(kp_, ki_, kd_);
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
        nrule = 0;
        nfuzz = 0;
        opr = a_fuzzy_equ;
        a_pid_fuzzy_init(this);
    }
    A_INLINE ~pid_fuzzy()
    {
        union
        {
            a_float const *p;
            a_float *o;
        } u;
        a_alloc(a_pid_fuzzy_bfuzz(this), 0);
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
    A_INLINE a_float kp_r() const { return kp; }
    A_INLINE void kp_w(a_float kp_) { kp = kp_; }
    A_INLINE a_float ki_r() const { return ki; }
    A_INLINE void ki_w(a_float ki_) { ki = ki_; }
    A_INLINE a_float kd_r() const { return kd; }
    A_INLINE void kd_w(a_float kd_) { kd = kd_; }
    A_INLINE a_float summax_r() const { return pid.summax; }
    A_INLINE void summax_w(a_float summax) { pid.summax = summax; }
    A_INLINE a_float summin_r() const { return pid.summin; }
    A_INLINE void summin_w(a_float summin) { pid.summin = summin; }
    A_INLINE a_float outmax_r() const { return pid.outmax; }
    A_INLINE void outmax_w(a_float outmax) { pid.outmax = outmax; }
    A_INLINE a_float outmin_r() const { return pid.outmin; }
    A_INLINE void outmin_w(a_float outmin) { pid.outmin = outmin; }
    A_INLINE a_float sum_r() const { return pid.sum; }
    A_INLINE a_float out_r() const { return pid.out; }
    A_INLINE a_float fdb_r() const { return pid.fdb; }
    A_INLINE a_float err_r() const { return pid.err; }
    A_INLINE unsigned int nrule_r() const { return nrule; }
    A_INLINE unsigned int nfuzz_r() const { return nfuzz; }
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
    A_INLINE pid_neuro *set_kpid(a_float k_, a_float kp, a_float ki, a_float kd)
    {
        a_pid_neuro::set_kpid(k_, kp, ki, kd);
        return this;
    }
    A_INLINE pid_neuro *set_wpid(a_float wp_, a_float wi_, a_float wd_)
    {
        a_pid_neuro::set_wpid(wp_, wi_, wd_);
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
    A_INLINE a_float k_r() const { return k; }
    A_INLINE void k_w(a_float k_) { k = k_; }
    A_INLINE a_float kp_r() const { return pid.kp; }
    A_INLINE void kp_w(a_float kp) { pid.kp = kp; }
    A_INLINE a_float ki_r() const { return pid.ki; }
    A_INLINE void ki_w(a_float ki) { pid.ki = ki; }
    A_INLINE a_float kd_r() const { return pid.kd; }
    A_INLINE void kd_w(a_float kd) { pid.kd = kd; }
    A_INLINE a_float wp_r() const { return wp; }
    A_INLINE void wp_w(a_float wp_) { wp = wp_; }
    A_INLINE a_float wi_r() const { return wi; }
    A_INLINE void wi_w(a_float wi_) { wi = wi_; }
    A_INLINE a_float wd_r() const { return wd; }
    A_INLINE void wd_w(a_float wd_) { wd = wd_; }
    A_INLINE a_float outmax_r() const { return pid.outmax; }
    A_INLINE void outmax_w(a_float outmax) { pid.outmax = outmax; }
    A_INLINE a_float outmin_r() const { return pid.outmin; }
    A_INLINE void outmin_w(a_float outmin) { pid.outmin = outmin; }
    A_INLINE a_float out_r() const { return pid.out; }
    A_INLINE a_float fdb_r() const { return pid.fdb; }
    A_INLINE a_float err_r() const { return pid.err; }
    A_INLINE a_float ec_r() const { return ec; }
};

#include "a/regress_simple.h"

struct regress_simple: public a_regress_simple
{
    A_INLINE a_float coef_r() const { return coef; }
    A_INLINE void coef_w(a_float coef_) { coef = coef_; }
    A_INLINE a_float bias_r() const { return bias; }
    A_INLINE void bias_w(a_float bias_) { bias = bias_; }
    A_INLINE regress_simple(a_float a = 1, a_float b = 0)
    {
        a_regress_simple::init(a, b);
    }
    A_INLINE a_float eval(a_float val) const
    {
        return a_regress_simple::eval(val);
    }
    A_INLINE a_float evar(a_float val) const
    {
        return a_regress_simple::evar(val);
    }
    A_INLINE regress_simple *ols_(emscripten::val const &x_, emscripten::val const &y_, a_float x_mean, a_float y_mean)
    {
        js_array_num x, y;
        js_array_num_init(x);
        js_array_num_init(y);
        js_array_num_get(x_, x);
        js_array_num_get(y_, y);
        a_regress_simple::ols(A_MIN(x.num, y.num), x.ptr, y.ptr, x_mean, y_mean);
        a_alloc(y.ptr, 0);
        a_alloc(x.ptr, 0);
        return this;
    }
    A_INLINE regress_simple *olsx(emscripten::val const &x_, emscripten::val const &y_, a_float x_mean)
    {
        js_array_num x, y;
        js_array_num_init(x);
        js_array_num_init(y);
        js_array_num_get(x_, x);
        js_array_num_get(y_, y);
        a_regress_simple::olsx(A_MIN(x.num, y.num), x.ptr, y.ptr, x_mean);
        a_alloc(y.ptr, 0);
        a_alloc(x.ptr, 0);
        return this;
    }
    A_INLINE regress_simple *olsy(emscripten::val const &x_, emscripten::val const &y_, a_float y_mean)
    {
        js_array_num x, y;
        js_array_num_init(x);
        js_array_num_init(y);
        js_array_num_get(x_, x);
        js_array_num_get(y_, y);
        a_regress_simple::olsy(A_MIN(x.num, y.num), x.ptr, y.ptr, y_mean);
        a_alloc(y.ptr, 0);
        a_alloc(x.ptr, 0);
        return this;
    }
    A_INLINE regress_simple *ols(emscripten::val const &x_, emscripten::val const &y_)
    {
        js_array_num x, y;
        js_array_num_init(x);
        js_array_num_init(y);
        js_array_num_get(x_, x);
        js_array_num_get(y_, y);
        a_regress_simple::ols(A_MIN(x.num, y.num), x.ptr, y.ptr);
        a_alloc(y.ptr, 0);
        a_alloc(x.ptr, 0);
        return this;
    }
    A_INLINE regress_simple *zero()
    {
        a_regress_simple::zero();
        return this;
    }
};

#include "a/tf.h"

struct tf: public a_tf
{
    void set_num_(emscripten::val const &num_, js_array_num &buf)
    {
        unsigned int n = js_array_num_len(num_);
        if (n > buf.num)
        {
            buf.ptr = a_cast_s(a_float *, a_alloc(buf.ptr, sizeof(a_float) * n * 2));
        }
        js_array_num_ptr(num_, buf);
        a_tf_set_num(this, n, buf.ptr, buf.ptr + n);
    }
    void set_den_(emscripten::val const &den_, js_array_num &buf)
    {
        unsigned int n = js_array_num_len(den_);
        if (n > buf.num)
        {
            buf.ptr = a_cast_s(a_float *, a_alloc(buf.ptr, sizeof(a_float) * n * 2));
        }
        js_array_num_ptr(den_, buf);
        a_tf_set_den(this, n, buf.ptr, buf.ptr + n);
    }
    A_INLINE tf(emscripten::val const &num_, emscripten::val const &den_)
    {
        js_array_num num, den;
        js_array_num_init(num);
        js_array_num_init(den);
        set_num_(num_, num);
        set_den_(den_, den);
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
    A_INLINE emscripten::val input_r() const { return js_array_num_new(input, num_n); }
    A_INLINE emscripten::val output_r() const { return js_array_num_new(output, den_n); }
    A_INLINE emscripten::val num_r() const { return js_array_num_new(num_p, num_n); }
    A_INLINE emscripten::val den_r() const { return js_array_num_new(den_p, den_n); }
    A_INLINE tf *set_num(emscripten::val const &num_)
    {
        js_array_num num;
        js_array_num_init(num, num_p, num_n);
        set_num_(num_, num);
        return this;
    }
    A_INLINE tf *set_den(emscripten::val const &den_)
    {
        js_array_num den;
        js_array_num_init(den, den_p, den_n);
        set_den_(den_, den);
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
    A_INLINE a_float gen(a_float jm_, a_float am_, a_float vm_, a_float p0_, a_float p1_,
                         a_float v0_ = 0, a_float v1_ = 0)
    {
        return a_trajbell::gen(jm_, am_, vm_, p0_, p1_, v0_, v1_);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajbell::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajbell::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajbell::acc(x); }
    A_INLINE a_float jer(a_float x) const { return a_trajbell::jer(x); }
    A_INLINE a_float t_r() const { return t; }
    A_INLINE a_float tv_r() const { return tv; }
    A_INLINE a_float ta_r() const { return ta; }
    A_INLINE a_float td_r() const { return td; }
    A_INLINE a_float taj_r() const { return taj; }
    A_INLINE a_float tdj_r() const { return tdj; }
    A_INLINE a_float p0_r() const { return p0; }
    A_INLINE a_float p1_r() const { return p1; }
    A_INLINE a_float v0_r() const { return v0; }
    A_INLINE a_float v1_r() const { return v1; }
    A_INLINE a_float vm_r() const { return vm; }
    A_INLINE a_float jm_r() const { return jm; }
    A_INLINE a_float am_r() const { return am; }
    A_INLINE a_float dm_r() const { return dm; }
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
    A_INLINE emscripten::val p_r() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val v_r() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val a_r() const { return js_array_num_new(a, A_LEN(a)); }
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
    A_INLINE emscripten::val p_r() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val v_r() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val a_r() const { return js_array_num_new(a, A_LEN(a)); }
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
    A_INLINE emscripten::val p_r() const { return js_array_num_new(p, A_LEN(p)); }
    A_INLINE emscripten::val v_r() const { return js_array_num_new(v, A_LEN(v)); }
    A_INLINE emscripten::val a_r() const { return js_array_num_new(a, A_LEN(a)); }
    A_INLINE emscripten::val j_r() const { return js_array_num_new(j, A_LEN(j)); }
};

#include "a/trajtrap.h"

struct trajtrap: public a_trajtrap
{
    A_INLINE a_float gen(a_float vm, a_float ac_, a_float de_, a_float p0_, a_float p1_,
                         a_float v0_ = 0, a_float v1_ = 0)
    {
        return a_trajtrap::gen(vm, ac_, de_, p0_, p1_, v0_, v1_);
    }
    A_INLINE a_float pos(a_float x) const { return a_trajtrap::pos(x); }
    A_INLINE a_float vel(a_float x) const { return a_trajtrap::vel(x); }
    A_INLINE a_float acc(a_float x) const { return a_trajtrap::acc(x); }
    A_INLINE a_float t_r() const { return t; }
    A_INLINE a_float p0_r() const { return p0; }
    A_INLINE a_float p1_r() const { return p1; }
    A_INLINE a_float v0_r() const { return v0; }
    A_INLINE a_float v1_r() const { return v1; }
    A_INLINE a_float vc_r() const { return vc; }
    A_INLINE a_float ta_r() const { return ta; }
    A_INLINE a_float td_r() const { return td; }
    A_INLINE a_float pa_r() const { return pa; }
    A_INLINE a_float pd_r() const { return pd; }
    A_INLINE a_float ac_r() const { return ac; }
    A_INLINE a_float de_r() const { return de; }
};

#include "a/version.h"

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
    A_INLINE std::string toString() const
    {
        char str[48];
        a_version::tostr(str, sizeof(str));
        return std::string(str);
    }
    A_INLINE version(unsigned int major_ = 0,
                     unsigned int minor_ = 0,
                     unsigned int third_ = 0,
                     unsigned int extra_ = 0)
    {
        major = major_;
        minor = minor_;
        third = third_;
        extra = extra_;
        alpha_[0] = '.';
        alpha_[1] = 0;
        alpha_[2] = 0;
        alpha_[3] = 0;
    }
    A_INLINE void major_w(unsigned int major_) { major = major_; }
    A_INLINE unsigned int major_r() const { return major; }
    A_INLINE void minor_w(unsigned int minor_) { minor = minor_; }
    A_INLINE unsigned int minor_r() const { return minor; }
    A_INLINE void third_w(unsigned int third_) { third = third_; }
    A_INLINE unsigned int third_r() const { return third; }
    A_INLINE void extra_w(unsigned int extra_) { extra = extra_; }
    A_INLINE unsigned int extra_r() const { return extra; }
    A_INLINE void alpha_w(std::string const &str)
    {
        a_version::set_alpha(str.c_str());
    }
    A_INLINE std::string alpha_r() const
    {
        char str[sizeof(alpha_) + 1];
        a_version::alpha(str);
        return std::string(str);
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

#if __has_warning("-Wglobal-constructors")
#pragma clang diagnostic ignored "-Wglobal-constructors"
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
        .property("table", &crc8::table_r)
        .function("eval", &crc8::operator())
        .function("pack", &crc8::pack)
        .function("gen", &crc8::gen, emscripten::allow_raw_pointers());
    emscripten::class_<crc16>("crc16")
        .constructor<a_u16>()
        .constructor<a_u16, bool>()
        .property("table", &crc16::table_r)
        .function("eval", &crc16::operator())
        .function("pack", &crc16::pack)
        .function("gen", &crc16::gen, emscripten::allow_raw_pointers());
    emscripten::class_<crc32>("crc32")
        .constructor<a_u32>()
        .constructor<a_u32, bool>()
        .property("table", &crc32::table_r)
        .function("eval", &crc32::operator())
        .function("pack", &crc32::pack)
        .function("gen", &crc32::gen, emscripten::allow_raw_pointers());
#if defined(WASM_BIGINT)
    emscripten::class_<crc64>("crc64")
        .constructor<a_u64>()
        .constructor<a_u64, bool>()
        .property("table", &crc64::table_r)
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
        .property("alpha", &hpf::alpha_r)
        .property("output", &hpf::output_r)
        .property("input", &hpf::input_r);
    emscripten::class_<lpf>("lpf")
        .constructor<a_float>()
        .constructor<a_float, a_float>()
        .function("iter", &lpf::operator())
        .function("gen", &lpf::gen, emscripten::allow_raw_pointers())
        .function("zero", &lpf::zero, emscripten::allow_raw_pointers())
        .property("alpha", &lpf::alpha_r)
        .property("output", &lpf::output_r);
    emscripten::class_<pid>("pid")
        .constructor<>()
        .function("set_kpid", &pid::set_kpid, emscripten::allow_raw_pointers())
        .function("zero", &pid::zero, emscripten::allow_raw_pointers())
        .function("run", &pid::run)
        .function("pos", &pid::pos)
        .function("inc", &pid::inc)
        .property("kp", &pid::kp_r, &pid::kp_w)
        .property("ki", &pid::ki_r, &pid::ki_w)
        .property("kd", &pid::kd_r, &pid::kd_w)
        .property("summax", &pid::summax_r, &pid::summax_w)
        .property("summin", &pid::summin_r, &pid::summin_w)
        .property("outmax", &pid::outmax_r, &pid::outmax_w)
        .property("outmin", &pid::outmin_r, &pid::outmin_w)
        .property("sum", &pid::sum_r)
        .property("out", &pid::out_r)
        .property("fdb", &pid::fdb_r)
        .property("err", &pid::err_r);
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<>()
        .function("set_opr", &pid_fuzzy::set_opr, emscripten::allow_raw_pointers())
        .function("set_nfuzz", &pid_fuzzy::set_nfuzz, emscripten::allow_raw_pointers())
        .function("set_rule", &pid_fuzzy::set_rule, emscripten::allow_raw_pointers())
        .function("set_kpid", &pid_fuzzy::set_kpid, emscripten::allow_raw_pointers())
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
        .property("kp", &pid_fuzzy::kp_r, &pid_fuzzy::kp_w)
        .property("ki", &pid_fuzzy::ki_r, &pid_fuzzy::ki_w)
        .property("kd", &pid_fuzzy::kd_r, &pid_fuzzy::kd_w)
        .property("summax", &pid_fuzzy::summax_r, &pid_fuzzy::summax_w)
        .property("summin", &pid_fuzzy::summin_r, &pid_fuzzy::summin_w)
        .property("outmax", &pid_fuzzy::outmax_r, &pid_fuzzy::outmax_w)
        .property("outmin", &pid_fuzzy::outmin_r, &pid_fuzzy::outmin_w)
        .property("sum", &pid_fuzzy::sum_r)
        .property("out", &pid_fuzzy::out_r)
        .property("fdb", &pid_fuzzy::fdb_r)
        .property("err", &pid_fuzzy::err_r)
        .property("nrule", &pid_fuzzy::nrule_r)
        .property("nfuzz", &pid_fuzzy::nfuzz_r, &pid_fuzzy::set_nfuzz);
    emscripten::class_<pid_neuro>("pid_neuro")
        .constructor<>()
        .function("set_kpid", &pid_neuro::set_kpid, emscripten::allow_raw_pointers())
        .function("set_wpid", &pid_neuro::set_wpid, emscripten::allow_raw_pointers())
        .function("zero", &pid_neuro::zero, emscripten::allow_raw_pointers())
        .function("run", &pid_neuro::run)
        .function("inc", &pid_neuro::inc)
        .property("k", &pid_neuro::k_r, &pid_neuro::k_w)
        .property("kp", &pid_neuro::kp_r, &pid_neuro::kp_w)
        .property("ki", &pid_neuro::ki_r, &pid_neuro::ki_w)
        .property("kd", &pid_neuro::kd_r, &pid_neuro::kd_w)
        .property("wp", &pid_neuro::wp_r, &pid_neuro::wp_w)
        .property("wi", &pid_neuro::wi_r, &pid_neuro::wi_w)
        .property("wd", &pid_neuro::wd_r, &pid_neuro::wd_w)
        .property("outmax", &pid_neuro::outmax_r, &pid_neuro::outmax_w)
        .property("outmin", &pid_neuro::outmin_r, &pid_neuro::outmin_w)
        .property("out", &pid_neuro::out_r)
        .property("fdb", &pid_neuro::fdb_r)
        .property("err", &pid_neuro::err_r)
        .property("ec", &pid_neuro::ec_r);
    emscripten::class_<regress_simple>("regress_simple")
        .constructor<>()
        .constructor<a_float>()
        .constructor<a_float, a_float>()
        .function("eval", &regress_simple::eval)
        .function("evar", &regress_simple::evar)
        .function("ols_", &regress_simple::ols_, emscripten::allow_raw_pointers())
        .function("olsx", &regress_simple::olsx, emscripten::allow_raw_pointers())
        .function("olsy", &regress_simple::olsy, emscripten::allow_raw_pointers())
        .function("ols", &regress_simple::ols, emscripten::allow_raw_pointers())
        .function("zero", &regress_simple::zero, emscripten::allow_raw_pointers())
        .property("coef", &regress_simple::coef_r, &regress_simple::coef_w)
        .property("bias", &regress_simple::bias_r, &regress_simple::bias_w);
    emscripten::class_<tf>("tf")
        .constructor<emscripten::val, emscripten::val>()
        .function("set_num", &tf::set_num, emscripten::allow_raw_pointers())
        .function("set_den", &tf::set_den, emscripten::allow_raw_pointers())
        .function("zero", &tf::zero, emscripten::allow_raw_pointers())
        .function("iter", &tf::operator())
        .property("input", &tf::input_r)
        .property("output", &tf::output_r)
        .property("num", &tf::num_r, &tf::set_num)
        .property("den", &tf::den_r, &tf::set_den);
    emscripten::class_<trajbell>("trajbell")
        .constructor<>()
        .function("gen", &trajbell::gen)
        .function("pos", &trajbell::pos)
        .function("vel", &trajbell::vel)
        .function("acc", &trajbell::acc)
        .function("jer", &trajbell::jer)
        .property("t", &trajbell::t_r)
        .property("tv", &trajbell::tv_r)
        .property("ta", &trajbell::ta_r)
        .property("td", &trajbell::td_r)
        .property("taj", &trajbell::taj_r)
        .property("tdj", &trajbell::tdj_r)
        .property("p0", &trajbell::p0_r)
        .property("p1", &trajbell::p1_r)
        .property("v0", &trajbell::v0_r)
        .property("v1", &trajbell::v1_r)
        .property("vm", &trajbell::vm_r)
        .property("jm", &trajbell::jm_r)
        .property("am", &trajbell::am_r)
        .property("dm", &trajbell::dm_r);
    emscripten::class_<trajpoly3>("trajpoly3")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly3::pos)
        .function("vel", &trajpoly3::vel)
        .function("acc", &trajpoly3::acc)
        .property("p", &trajpoly3::p_r)
        .property("v", &trajpoly3::v_r)
        .property("a", &trajpoly3::a_r);
    emscripten::class_<trajpoly5>("trajpoly5")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly5::pos)
        .function("vel", &trajpoly5::vel)
        .function("acc", &trajpoly5::acc)
        .property("p", &trajpoly5::p_r)
        .property("v", &trajpoly5::v_r)
        .property("a", &trajpoly5::a_r);
    emscripten::class_<trajpoly7>("trajpoly7")
        .constructor<a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .constructor<a_float, a_float, a_float, a_float, a_float, a_float, a_float, a_float, a_float>()
        .function("pos", &trajpoly7::pos)
        .function("vel", &trajpoly7::vel)
        .function("acc", &trajpoly7::acc)
        .function("jer", &trajpoly7::jer)
        .property("p", &trajpoly7::p_r)
        .property("v", &trajpoly7::v_r)
        .property("a", &trajpoly7::a_r)
        .property("j", &trajpoly7::j_r);
    emscripten::class_<trajtrap>("trajtrap")
        .constructor<>()
        .function("gen", &trajtrap::gen)
        .function("pos", &trajtrap::pos)
        .function("vel", &trajtrap::vel)
        .function("acc", &trajtrap::acc)
        .property("t", &trajtrap::t_r)
        .property("p0", &trajtrap::p0_r)
        .property("p1", &trajtrap::p1_r)
        .property("v0", &trajtrap::v0_r)
        .property("v1", &trajtrap::v1_r)
        .property("vc", &trajtrap::vc_r)
        .property("ta", &trajtrap::ta_r)
        .property("td", &trajtrap::td_r)
        .property("pa", &trajtrap::pa_r)
        .property("pd", &trajtrap::pd_r)
        .property("ac", &trajtrap::ac_r)
        .property("de", &trajtrap::de_r);
    emscripten::class_<version>("version")
        .constructor<>()
        .constructor<a_uint>()
        .constructor<a_uint, a_uint>()
        .constructor<a_uint, a_uint, a_uint>()
        .constructor<a_uint, a_uint, a_uint, a_uint>()
        .property("major", &version::major_r, &version::major_w)
        .property("minor", &version::minor_r, &version::minor_w)
        .property("third", &version::third_r, &version::third_w)
        .property("extra", &version::extra_r, &version::extra_w)
        .property("alpha", &version::alpha_r, &version::alpha_w)
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
