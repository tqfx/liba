#cython: binding=True
#cython: autotestdict=False
#cython: auto_pickle=False
#cython: boundscheck=False
#cython: wraparound=False
#cython: initializedcheck=False
#cython: language_level=3str
#cython: c_string_type=bytes
#cython: c_string_encoding=utf-8
from cython.parallel import prange
from cython.view cimport array
from cpython cimport *
from a cimport *

cdef a_diff get_len(object x, int d):
    cdef a_diff i = 0, n = 0
    cdef object o = iter(x)
    cdef list L = [o]
    while L:
        try:
            o = next(L[i])
            if PyObject_HasAttrString(o, "__len__"):
                if len(L) < d:
                    o = iter(o)
                    L.append(o)
                    i += 1
            else:
                n += 1
        except StopIteration:
            L.pop()
            i -= 1
    return n

cdef array u16_new(a_diff n):
    return array(shape=(n,), itemsize=2, format='H', mode='c')

cdef array u32_new(a_diff n):
    cdef str u32 = 'I'
    if UINT32_MAX > UINT_MAX:
        u32 = 'L'
    return array(shape=(n,), itemsize=4, format=u32, mode='c')

cdef a_u32 *u32_set(void *p, object x, int d):
    cdef a_u32 *r = <a_u32 *>p
    cdef object o = iter(x)
    cdef a_diff i = 0
    cdef list L = [o]
    while L:
        try:
            o = next(L[i])
            if PyObject_HasAttrString(o, "__len__"):
                if len(L) < d:
                    o = iter(o)
                    L.append(o)
                    i += 1
            else:
                r[0] = o
                r += 1
        except StopIteration:
            L.pop()
            i -= 1
    return <a_u32 *>p

cdef array u32_get(object x, int d):
    cdef a_diff n = get_len(x, d)
    cdef array r = u32_new(n)
    u32_set(r.data, x, d)
    return r

cpdef array new_u32(object x, int d=1):
    if PyObject_HasAttrString(x, "__len__"):
        return u32_get(x, d)
    return u32_new(x)

cdef array u64_new(a_diff n):
    cdef str u64 = 'L'
    if UINT64_MAX > ULONG_MAX:
        u64 = 'Q'
    return array(shape=(n,), itemsize=8, format=u64, mode='c')

cdef a_u64 *u64_set(void *p, object x, int d):
    cdef a_u64 *r = <a_u64 *>p
    cdef object o = iter(x)
    cdef a_diff i = 0
    cdef list L = [o]
    while L:
        try:
            o = next(L[i])
            if PyObject_HasAttrString(o, "__len__"):
                if len(L) < d:
                    o = iter(o)
                    L.append(o)
                    i += 1
            else:
                r[0] = o
                r += 1
        except StopIteration:
            L.pop()
            i -= 1
    return <a_u64 *>p

cdef array u64_get(object x, int d):
    cdef a_diff n = get_len(x, d)
    cdef array r = u64_new(n)
    u64_set(r.data, x, d)
    return r

cpdef array new_u64(object x, int d=1):
    if PyObject_HasAttrString(x, "__len__"):
        return u64_get(x, d)
    return u64_new(x)

cdef array f32_new(a_diff n):
    return array(shape=(n,), itemsize=4, format='f', mode='c')

cdef a_f32 *f32_set(void *p, object x, int d):
    cdef a_f32 *r = <a_f32 *>p
    cdef object o = iter(x)
    cdef a_diff i = 0
    cdef list L = [o]
    while L:
        try:
            o = next(L[i])
            if PyObject_HasAttrString(o, "__len__"):
                if len(L) < d:
                    o = iter(o)
                    L.append(o)
                    i += 1
            else:
                r[0] = o
                r += 1
        except StopIteration:
            L.pop()
            i -= 1
    return <a_f32 *>p

cdef array f32_get(object x, int d):
    cdef a_diff n = get_len(x, d)
    cdef array r = f32_new(n)
    f32_set(r.data, x, d)
    return r

cpdef array new_f32(object x, int d=1):
    if PyObject_HasAttrString(x, "__len__"):
        return f32_get(x, d)
    return f32_new(x)

cdef array f64_new(a_diff n):
    return array(shape=(n,), itemsize=8, format='d', mode='c')

cdef a_f64 *f64_set(void *p, object x, int d):
    cdef a_f64 *r = <a_f64 *>p
    cdef object o = iter(x)
    cdef a_diff i = 0
    cdef list L = [o]
    while L:
        try:
            o = next(L[i])
            if PyObject_HasAttrString(o, "__len__"):
                if len(L) < d:
                    o = iter(o)
                    L.append(o)
                    i += 1
            else:
                r[0] = o
                r += 1
        except StopIteration:
            L.pop()
            i -= 1
    return <a_f64 *>p

cdef array f64_get(object x, int d):
    cdef a_diff n = get_len(x, d)
    cdef array r = f64_new(n)
    f64_set(r.data, x, d)
    return r

cpdef array new_f64(object x, int d=1):
    if PyObject_HasAttrString(x, "__len__"):
        return f64_get(x, d)
    return f64_new(x)

cdef array (*real_new)(a_diff)
cdef array (*real_get)(object,int)
if A_REAL_TYPE == A_REAL_SINGLE:
    real_new = f32_new
    real_get = f32_get
    new_real = new_f32
else:
    real_new = f64_new
    real_get = f64_get
    new_real = new_f64

from a.crc cimport *

cdef class crc8:
    cdef a_u8[0x100] table
    property table:
        def __get__(self):
            return <const a_u8[::1]>self.table
    def gen(self, a_u8 poly, bint reversed=0):
        if reversed:
            a_crc8l_init(self.table, poly)
        else:
            a_crc8m_init(self.table, poly)
        return self
    def __init__(self, a_u8 poly, bint reversed=0):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u8 value=0):
        return a_crc8(self.table, <char *>block, len(block), value)
    def pack(self, bytes block, a_u8 value=0):
        cdef size_t n = len(block)
        block = block + bytes(1)
        cdef char *p = <char *>block
        value = a_crc8(self.table, p, n, value)
        p[n] = value
        return block

cdef class crc16:
    cdef a_u16[0x100] table
    property table:
        def __get__(self):
            return <const a_u16[::1]>self.table
    cdef a_u16 (*eval)(const a_u16 *, const void *, a_size, a_u16)
    def gen(self, a_u16 poly, bint reversed=0):
        if reversed:
            a_crc16l_init(self.table, poly)
            self.eval = a_crc16l
        else:
            a_crc16m_init(self.table, poly)
            self.eval = a_crc16m
        return self
    def __init__(self, a_u16 poly, bint reversed=0):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u16 value=0):
        return self.eval(self.table, <char *>block, len(block), value)
    def pack(self, bytes block, a_u16 value=0):
        cdef size_t n = len(block)
        block = block + bytes(2)
        cdef char *p = <char *>block
        value = self.eval(self.table, p, n, value)
        if self.eval == a_crc16m:
            a_u16_setb(p + n, value)
        else:
            a_u16_setl(p + n, value)
        return block

cdef class crc32:
    cdef a_u32[0x100] table
    property table:
        def __get__(self):
            return <const a_u32[::1]>self.table
    cdef a_u32 (*eval)(const a_u32 *, const void *, a_size, a_u32)
    def gen(self, a_u32 poly, bint reversed=0):
        if reversed:
            a_crc32l_init(self.table, poly)
            self.eval = a_crc32l
        else:
            a_crc32m_init(self.table, poly)
            self.eval = a_crc32m
        return self
    def __init__(self, a_u32 poly, bint reversed=0):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u32 value=0):
        return self.eval(self.table, <char *>block, len(block), value)
    def pack(self, bytes block, a_u32 value=0):
        cdef size_t n = len(block)
        block = block + bytes(4)
        cdef char *p = <char *>block
        value = self.eval(self.table, p, n, value)
        if self.eval == a_crc32m:
            a_u32_setb(p + n, value)
        else:
            a_u32_setl(p + n, value)
        return block

cdef class crc64:
    cdef a_u64[0x100] table
    property table:
        def __get__(self):
            return <const a_u64[::1]>self.table
    cdef a_u64 (*eval)(const a_u64 *, const void *, a_size, a_u64)
    def gen(self, a_u64 poly, bint reversed=0):
        if reversed:
            a_crc64l_init(self.table, poly)
            self.eval = a_crc64l
        else:
            a_crc64m_init(self.table, poly)
            self.eval = a_crc64m
        return self
    def __init__(self, a_u64 poly, bint reversed=0):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u64 value=0):
        return self.eval(self.table, <char *>block, len(block), value)
    def pack(self, bytes block, a_u64 value=0):
        cdef size_t n = len(block)
        block = block + bytes(8)
        cdef char *p = <char *>block
        value = self.eval(self.table, p, n, value)
        if self.eval == a_crc64m:
            a_u64_setb(p + n, value)
        else:
            a_u64_setl(p + n, value)
        return block

from a.hash cimport *

def hash_bkdr(const char *str, a_u32 val=0):
    return a_hash_bkdr(str, val)

def hash_sdbm(const char *str, a_u32 val=0):
    return a_hash_sdbm(str, val)

from a.hpf cimport *

cdef class hpf:
    cdef a_hpf ctx
    def __init__(self, a_real fc, a_real ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
    def gen(self, a_real fc, a_real ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
        return self
    def __call__(self, a_real x):
        return a_hpf_iter(&self.ctx, x)
    def zero(self):
        a_hpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_real alpha):
            self.ctx.alpha = alpha
    property output:
        def __get__(self):
            return self.ctx.output
    property input:
        def __get__(self):
            return self.ctx.input

from a.lpf cimport *

cdef class lpf:
    cdef a_lpf ctx
    def __init__(self, a_real fc, a_real ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
    def gen(self, a_real fc, a_real ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
        return self
    def __call__(self, a_real x):
        return a_lpf_iter(&self.ctx, x)
    def zero(self):
        a_lpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_real alpha):
            self.ctx.alpha = alpha
    property output:
        def __get__(self):
            return self.ctx.output

from a.math cimport *

def isqrt(x: int):
    cdef object x0, x1
    if x <= 1:
        return x
    x0 = 1 << ((x.bit_length() + 1) >> 1)
    x1 = (x0 + x // x0) >> 1
    while x0 > x1:
        x0 = x1
        x1 = (x0 + x // x0) >> 1
    return x0

def sqrt_u32(object x):
    cdef array r
    cdef a_diff i
    cdef a_u16 *q
    cdef const a_u32[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = u16_new(p.shape[0])
        q = <a_u16 *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_u32_sqrt(p[i])
        return r
    return a_u32_sqrt(x)

def sqrt_u64(object x):
    cdef array r
    cdef a_diff i
    cdef a_u32 *q
    cdef const a_u64[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = u32_new(p.shape[0])
        q = <a_u32 *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_u64_sqrt(p[i])
        return r
    return a_u64_sqrt(x)

def rsqrt_f32(object x):
    cdef array r
    cdef a_diff i
    cdef a_f32 *q
    cdef const a_f32[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = f32_new(p.shape[0])
        q = <a_f32 *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_f32_rsqrt(p[i])
        return r
    return a_f32_rsqrt(x)

def rsqrt_f64(object x):
    cdef array r
    cdef a_diff i
    cdef a_f64 *q
    cdef const a_f64[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = f64_new(p.shape[0])
        q = <a_f64 *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_f64_rsqrt(p[i])
        return r
    return a_f64_rsqrt(x)

def real_sum(const a_real[::1] x):
    return a_real_sum(x.shape[0], &x[0])

def real_sum1(const a_real[::1] x):
    return a_real_sum1(x.shape[0], &x[0])

def real_sum2(const a_real[::1] x):
    return a_real_sum2(x.shape[0], &x[0])

def real_mean(const a_real[::1] x):
    return a_real_mean(x.shape[0], &x[0])

from a.mf cimport *

cdef class mf:
    NUL    = A_MF_NUL
    GAUSS  = A_MF_GAUSS
    GAUSS2 = A_MF_GAUSS2
    GBELL  = A_MF_GBELL
    SIG    = A_MF_SIG
    DSIG   = A_MF_DSIG
    PSIG   = A_MF_PSIG
    TRAP   = A_MF_TRAP
    TRI    = A_MF_TRI
    LINS   = A_MF_LINS
    LINZ   = A_MF_LINZ
    S      = A_MF_S
    Z      = A_MF_Z
    PI     = A_MF_PI
    @staticmethod
    def mf(unsigned int e, object x, const a_real[::1] a):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf(e, p[i], &a[0])
            return r
        return a_mf(e, x, &a[0])
    @staticmethod
    def gauss(object x, a_real sigma, a_real c):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_gauss(p[i], sigma, c)
            return r
        return a_mf_gauss(x, sigma, c)
    @staticmethod
    def gauss2(object x, a_real sigma1, a_real c1, a_real sigma2, a_real c2):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_gauss2(p[i], sigma1, c1, sigma2, c2)
            return r
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2)
    @staticmethod
    def gbell(object x, a_real a, a_real b, a_real c):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_gbell(p[i], a, b, c)
            return r
        return a_mf_gbell(x, a, b, c)
    @staticmethod
    def sig(object x, a_real a, a_real c):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_sig(p[i], a, c)
            return r
        return a_mf_sig(x, a, c)
    @staticmethod
    def dsig(object x, a_real a1, a_real c1, a_real a2, a_real c2):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_dsig(p[i], a1, c1, a2, c2)
            return r
        return a_mf_dsig(x, a1, c1, a2, c2)
    @staticmethod
    def psig(object x, a_real a1, a_real c1, a_real a2, a_real c2):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_psig(p[i], a1, c1, a2, c2)
            return r
        return a_mf_psig(x, a1, c1, a2, c2)
    @staticmethod
    def trap(object x, a_real a, a_real b, a_real c, a_real d):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_trap(p[i], a, b, c, d)
            return r
        return a_mf_trap(x, a, b, c, d)
    @staticmethod
    def tri(object x, a_real a, a_real b, a_real c):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_tri(p[i], a, b, c)
            return r
        return a_mf_tri(x, a, b, c)
    @staticmethod
    def lins(object x, a_real a, a_real b):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_lins(p[i], a, b)
            return r
        return a_mf_lins(x, a, b)
    @staticmethod
    def linz(object x, a_real a, a_real b):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_linz(p[i], a, b)
            return r
        return a_mf_linz(x, a, b)
    @staticmethod
    def s(object x, a_real a, a_real b):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_s(p[i], a, b)
            return r
        return a_mf_s(x, a, b)
    @staticmethod
    def z(object x, a_real a, a_real b):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_z(p[i], a, b)
            return r
        return a_mf_z(x, a, b)
    @staticmethod
    def pi(object x, a_real a, a_real b, a_real c, a_real d):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_mf_pi(p[i], a, b, c, d)
            return r
        return a_mf_pi(x, a, b, c, d)

from a.pid cimport *

cdef class pid:
    cdef a_pid ctx
    def __init__(self):
        self.ctx.kp = 1
        self.ctx.summax = +A_REAL_INF
        self.ctx.summin = -A_REAL_INF
        self.ctx.outmax = +A_REAL_INF
        self.ctx.outmin = -A_REAL_INF
        a_pid_init(&self.ctx)
    def set_kpid(self, a_real kp, a_real ki, a_real kd):
        a_pid_set_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_real set, a_real fdb):
        return a_pid_run(&self.ctx, set, fdb)
    def pos(self, a_real set, a_real fdb):
        return a_pid_pos(&self.ctx, set, fdb)
    def inc(self, a_real set, a_real fdb):
        return a_pid_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_real kp):
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_real ki):
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_real kd):
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.summax
        def __set__(self, a_real summax):
            self.ctx.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.summin
        def __set__(self, a_real summin):
            self.ctx.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.sum
    property outmax:
        def __get__(self):
            return self.ctx.outmax
        def __set__(self, a_real outmax):
            self.ctx.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.outmin
        def __set__(self, a_real outmin):
            self.ctx.outmin = outmin
    property out:
        def __get__(self):
            return self.ctx.out
    property fdb:
        def __get__(self):
            return self.ctx.fdb
    property err:
        def __get__(self):
            return self.ctx.err

from a.pid_fuzzy cimport *

cdef class pid_fuzzy:
    CAP = A_PID_FUZZY_CAP
    CAP_ALGEBRA = A_PID_FUZZY_CAP_ALGEBRA
    CAP_BOUNDED = A_PID_FUZZY_CAP_BOUNDED
    CUP = A_PID_FUZZY_CUP
    CUP_ALGEBRA = A_PID_FUZZY_CUP_ALGEBRA
    CUP_BOUNDED = A_PID_FUZZY_CUP_BOUNDED
    EQU = A_PID_FUZZY_EQU
    cdef a_pid_fuzzy ctx
    cdef readonly array me
    cdef readonly array mec
    cdef readonly array mkp
    cdef readonly array mki
    cdef readonly array mkd
    def __init__(self):
        self.ctx.pid.summax = +A_REAL_INF
        self.ctx.pid.summin = -A_REAL_INF
        self.ctx.pid.outmax = +A_REAL_INF
        self.ctx.pid.outmin = -A_REAL_INF
        self.ctx.kp = self.ctx.pid.kp = 1
        self.ctx.opr = a_fuzzy_equ
        a_pid_fuzzy_init(&self.ctx)
    def set_opr(self, unsigned int opr):
        a_pid_fuzzy_set_opr(&self.ctx, opr)
        return self
    def set_nfuzz(self, unsigned int num):
        cdef void *ptr = a_pid_fuzzy_bfuzz(&self.ctx)
        ptr = PyMem_Realloc(ptr, A_PID_FUZZY_BFUZZ(num))
        a_pid_fuzzy_set_bfuzz(&self.ctx, ptr, num)
        return self
    def set_rule(self, me, mec, mkp, mki, mkd):
        self.me = real_get(me, 2)
        self.mec = real_get(mec, 2)
        self.mkp = real_get(mkp, 2)
        self.mki = real_get(mki, 2)
        self.mkd = real_get(mkd, 2)
        cdef a_u32 n = <a_u32>self.mkp.shape[0]
        a_pid_fuzzy_set_rule(&self.ctx, a_u32_sqrt(n),
                        <const a_real *>self.me.data,
                        <const a_real *>self.mec.data,
                        <const a_real *>self.mkp.data,
                        <const a_real *>self.mki.data,
                        <const a_real *>self.mkd.data)
        return self
    def set_kpid(self, a_real kp, a_real ki, a_real kd):
        a_pid_fuzzy_set_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_real set, a_real fdb):
        return a_pid_fuzzy_run(&self.ctx, set, fdb)
    def pos(self, a_real set, a_real fdb):
        return a_pid_fuzzy_pos(&self.ctx, set, fdb)
    def inc(self, a_real set, a_real fdb):
        return a_pid_fuzzy_inc(&self.ctx, set, fdb)
    def __dealloc__(self):
        PyMem_Free(a_pid_fuzzy_bfuzz(&self.ctx))
    def zero(self):
        a_pid_fuzzy_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_real kp):
            self.ctx.pid.kp = kp
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_real ki):
            self.ctx.pid.ki = ki
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_real kd):
            self.ctx.pid.kd = kd
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.pid.summax
        def __set__(self, a_real summax):
            self.ctx.pid.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.pid.summin
        def __set__(self, a_real summin):
            self.ctx.pid.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.pid.sum
    property outmax:
        def __get__(self):
            return self.ctx.pid.outmax
        def __set__(self, a_real outmax):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.pid.outmin
        def __set__(self, a_real outmin):
            self.ctx.pid.outmin = outmin
    property out:
        def __get__(self):
            return self.ctx.pid.out
    property fdb:
        def __get__(self):
            return self.ctx.pid.fdb
    property err:
        def __get__(self):
            return self.ctx.pid.err
    property nrule:
        def __get__(self):
            return self.ctx.nrule
    property nfuzz:
        def __get__(self):
            return self.ctx.nfuzz
        def __set__(self, unsigned int nfuzz):
            self.set_nfuzz(nfuzz)

from a.pid_neuro cimport *

cdef class pid_neuro:
    cdef a_pid_neuro ctx
    def __init__(self):
        self.ctx.pid.summax = +A_REAL_INF
        self.ctx.pid.summin = -A_REAL_INF
        self.ctx.pid.outmax = +A_REAL_INF
        self.ctx.pid.outmin = -A_REAL_INF
        self.ctx.k = self.ctx.pid.kp = 1
        self.ctx.wp = 0.1
        self.ctx.wi = 0.1
        self.ctx.wd = 0.1
        a_pid_neuro_init(&self.ctx)
    def set_kpid(self, a_real k, a_real kp, a_real ki, a_real kd):
        a_pid_neuro_set_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def set_wpid(self, a_real wp, a_real wi, a_real wd):
        a_pid_neuro_set_wpid(&self.ctx, wp, wi, wd)
        return self
    def run(self, a_real set, a_real fdb):
        return a_pid_neuro_run(&self.ctx, set, fdb)
    def inc(self, a_real set, a_real fdb):
        return a_pid_neuro_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_neuro_zero(&self.ctx)
        return self
    property k:
        def __get__(self):
            return self.ctx.k
        def __set__(self, a_real k):
            self.ctx.k = k
    property kp:
        def __get__(self):
            return self.ctx.pid.kp
        def __set__(self, a_real kp):
            self.ctx.pid.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.pid.ki
        def __set__(self, a_real ki):
            self.ctx.pid.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.pid.kd
        def __set__(self, a_real kd):
            self.ctx.pid.kd = kd
    property wp:
        def __get__(self):
            return self.ctx.wp
        def __set__(self, a_real wp):
            self.ctx.wp = wp
    property wi:
        def __get__(self):
            return self.ctx.wi
        def __set__(self, a_real wi):
            self.ctx.wi = wi
    property wd:
        def __get__(self):
            return self.ctx.wd
        def __set__(self, a_real wd):
            self.ctx.wd = wd
    property outmax:
        def __get__(self):
            return self.ctx.pid.outmax
        def __set__(self, a_real outmax):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.pid.outmin
        def __set__(self, a_real outmin):
            self.ctx.pid.outmin = outmin
    property out:
        def __get__(self):
            return self.ctx.pid.out
    property fdb:
        def __get__(self):
            return self.ctx.pid.fdb
    property err:
        def __get__(self):
            return self.ctx.pid.err
    property ec:
        def __get__(self):
            return self.ctx.ec

from a.poly cimport *

def poly_eval(object x, const a_real[::1] a):
    cdef array r
    cdef a_diff i
    cdef a_real *q
    cdef const a_real[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = real_new(p.shape[0])
        q = <a_real *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_poly_eval(&a[0], a.shape[0], p[i])
        return r
    return a_poly_eval(&a[0], a.shape[0], x)

def poly_evar(object x, const a_real[::1] a):
    cdef array r
    cdef a_diff i
    cdef a_real *q
    cdef const a_real[::1] p
    if PyObject_HasAttrString(x, "__len__"):
        p = x
        r = real_new(p.shape[0])
        q = <a_real *>r.data
        A_ASSUME(p.shape[0])
        for i in prange(p.shape[0], nogil=True):
            q[i] = a_poly_evar(&a[0], a.shape[0], p[i])
        return r
    return a_poly_evar(&a[0], a.shape[0], x)

from a.regress_linear cimport *

cdef class regress_linear:
    cdef a_regress_linear ctx
    def __init__(self, object coef, a_real bias=0):
        if PyObject_HasAttrString(coef, "__len__"):
            self.coef_ = real_get(coef, 1)
        else:
            self.coef_ = real_new(1)
            self.coef_[0] = coef
        a_regress_linear_init(&self.ctx, <a_real *>self.coef_.data, self.coef_.shape[0], bias)
    def eval(self, const a_real[::1] x):
        cdef array r
        cdef a_diff i
        cdef a_real *y
        cdef a_diff n = x.shape[0] // self.ctx.coef_n
        if n > 1:
            r = real_new(n)
            y = <a_real *>r.data
            for i in prange(n, nogil=True):
                y[i] = a_regress_linear_eval(&self.ctx, &x[i * self.ctx.coef_n])
            return r
        return a_regress_linear_eval(&self.ctx, &x[0])
    def err(self, const a_real[::1] x, const a_real[::1] y):
        cdef a_diff m = x.shape[0] // self.ctx.coef_n
        cdef a_diff n = min(m, y.shape[0])
        cdef array r = real_new(n)
        a_regress_linear_err(&self.ctx, n, &x[0], &y[0], <a_real *>r.data)
        return r
    def gd(self, const a_real[::1] input, a_real error, a_real alpha):
        a_regress_linear_gd(&self.ctx, &input[0], error, alpha)
        return self
    def sgd(self, const a_real[::1] x, const a_real[::1] y, a_real alpha):
        cdef a_diff m = x.shape[0] // self.ctx.coef_n
        cdef a_diff n = min(m, y.shape[0])
        a_regress_linear_sgd(&self.ctx, n, &x[0], &y[0], alpha)
        return self
    def bgd(self, const a_real[::1] x, const a_real[::1] y, a_real alpha):
        cdef a_diff m = x.shape[0] // self.ctx.coef_n
        cdef a_diff n = min(m, y.shape[0])
        cdef array r = real_new(n)
        a_regress_linear_err(&self.ctx, n, &x[0], &y[0], <a_real *>r.data)
        a_regress_linear_bgd(&self.ctx, n, &x[0], <a_real *>r.data, alpha)
        return self
    def mgd(self, const a_real[::1] x, const a_real[::1] y, a_real delta, a_real lrmax, a_real lrmin, a_size lrtim=100, a_size epoch=1000, a_size batch=10):
        cdef a_diff m = x.shape[0] // self.ctx.coef_n
        cdef a_diff n = min(m, y.shape[0])
        cdef array r = real_new(n)
        return a_regress_linear_mgd(&self.ctx, n, &x[0], &y[0], <a_real *>r.data, delta, lrmax, lrmin, lrtim, epoch, batch)
    def zero(self):
        a_regress_linear_zero(&self.ctx)
        return self
    cdef array coef_
    property coef:
        def __get__(self):
            return self.coef_
        def __set__(self, object coef):
            if PyObject_HasAttrString(coef, "__len__"):
                self.coef_ = real_get(coef, 1)
            else:
                self.coef_ = real_new(1)
                self.coef_[0] = coef
            self.ctx.coef_p = <a_real *>self.coef_.data
            self.ctx.coef_n = self.coef_.shape[0]
    property bias:
        def __get__(self):
            return self.ctx.bias
        def __set__(self, a_real bias):
            self.ctx.bias = bias

from a.regress_simple cimport *

cdef class regress_simple:
    cdef a_regress_simple ctx
    def __init__(self, a_real coef=1, a_real bias=0):
        a_regress_simple_init(&self.ctx, coef, bias)
    def eval(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_regress_simple_eval(&self.ctx, p[i])
            return r
        return a_regress_simple_eval(&self.ctx, x)
    def evar(self, object y):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(y, "__len__"):
            p = y
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_regress_simple_evar(&self.ctx, p[i])
            return r
        return a_regress_simple_evar(&self.ctx, y)
    def ols_(self, const a_real[::1] x, const a_real[::1] y, a_real x_mean, a_real y_mean):
        a_regress_simple_ols_(&self.ctx, min(x.shape[0], y.shape[0]), &x[0], &y[0], x_mean, y_mean)
        return self
    def olsx(self, const a_real[::1] x, const a_real[::1] y, a_real x_mean):
        a_regress_simple_olsx(&self.ctx, min(x.shape[0], y.shape[0]), &x[0], &y[0], x_mean)
        return self
    def olsy(self, const a_real[::1] x, const a_real[::1] y, a_real y_mean):
        a_regress_simple_olsy(&self.ctx, min(x.shape[0], y.shape[0]), &x[0], &y[0], y_mean)
        return self
    def ols(self, const a_real[::1] x, const a_real[::1] y):
        a_regress_simple_ols(&self.ctx, min(x.shape[0], y.shape[0]), &x[0], &y[0])
        return self
    def zero(self):
        a_regress_simple_zero(&self.ctx)
        return self
    property coef:
        def __get__(self):
            return self.ctx.coef
        def __set__(self, a_real coef):
            self.ctx.coef = coef
    property bias:
        def __get__(self):
            return self.ctx.bias
        def __set__(self, a_real bias):
            self.ctx.bias = bias

from a.tf cimport *

cdef class tf:
    cdef a_tf ctx
    def __init__(self, object num, object den):
        tf.num.__set__(self, num)
        tf.den.__set__(self, den)
    def __call__(self, a_real x):
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        a_tf_zero(&self.ctx)
        return self
    cdef readonly array input
    cdef array num_
    property num:
        def __get__(self):
            return self.num_
        def __set__(self, object num):
            self.num_ = real_get(num, 1)
            self.input = real_new(self.num_.shape[0])
            a_tf_set_num(&self.ctx, <unsigned int>self.num_.shape[0],
                                    <const a_real *>self.num_.data,
                                    <a_real *>self.input.data)
    cdef readonly array output
    cdef array den_
    property den:
        def __get__(self):
            return self.den_
        def __set__(self, object den):
            self.den_ = real_get(den, 1)
            self.output = real_new(self.den_.shape[0])
            a_tf_set_den(&self.ctx, <unsigned int>self.den_.shape[0],
                                    <const a_real *>self.den_.data,
                                    <a_real *>self.output.data)

from a.trajbell cimport *

cdef class trajbell:
    cdef a_trajbell ctx
    def gen(self, a_real jm, a_real am, a_real vm, a_real p0, a_real p1, a_real v0=0, a_real v1=0):
        return a_trajbell_gen(&self.ctx, jm, am, vm, p0, p1, v0, v1)
    def pos(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajbell_pos(&self.ctx, p[i])
            return r
        return a_trajbell_pos(&self.ctx, x)
    def vel(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajbell_vel(&self.ctx, p[i])
            return r
        return a_trajbell_vel(&self.ctx, x)
    def acc(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajbell_acc(&self.ctx, p[i])
            return r
        return a_trajbell_acc(&self.ctx, x)
    def jer(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajbell_jer(&self.ctx, p[i])
            return r
        return a_trajbell_jer(&self.ctx, x)
    property t:
        def __get__(self):
            return self.ctx.t
    property tv:
        def __get__(self):
            return self.ctx.tv
    property ta:
        def __get__(self):
            return self.ctx.ta
    property td:
        def __get__(self):
            return self.ctx.td
    property taj:
        def __get__(self):
            return self.ctx.taj
    property tdj:
        def __get__(self):
            return self.ctx.tdj
    property p0:
        def __get__(self):
            return self.ctx.p0
    property p1:
        def __get__(self):
            return self.ctx.p1
    property v0:
        def __get__(self):
            return self.ctx.v0
    property v1:
        def __get__(self):
            return self.ctx.v1
    property vm:
        def __get__(self):
            return self.ctx.vm
    property jm:
        def __get__(self):
            return self.ctx.jm
    property am:
        def __get__(self):
            return self.ctx.am
    property dm:
        def __get__(self):
            return self.ctx.dm

from a.trajpoly3 cimport *

cdef class trajpoly3:
    cdef a_trajpoly3 ctx
    def __init__(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0):
        a_trajpoly3_gen(&self.ctx, ts, p0, p1, v0, v1)
    def gen(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0):
        a_trajpoly3_gen(&self.ctx, ts, p0, p1, v0, v1)
        return self
    def pos(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly3_pos(&self.ctx, p[i])
            return r
        return a_trajpoly3_pos(&self.ctx, x)
    def vel(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly3_vel(&self.ctx, p[i])
            return r
        return a_trajpoly3_vel(&self.ctx, x)
    def acc(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly3_acc(&self.ctx, p[i])
            return r
        return a_trajpoly3_acc(&self.ctx, x)
    property p:
        def __get__(self):
            return self.ctx.p
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a

from a.trajpoly5 cimport *

cdef class trajpoly5:
    cdef a_trajpoly5 ctx
    def __init__(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0, a_real a0=0, a_real a1=0):
        a_trajpoly5_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1)
    def gen(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0, a_real a0=0, a_real a1=0):
        a_trajpoly5_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1)
        return self
    def pos(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly5_pos(&self.ctx, p[i])
            return r
        return a_trajpoly5_pos(&self.ctx, x)
    def vel(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly5_vel(&self.ctx, p[i])
            return r
        return a_trajpoly5_vel(&self.ctx, x)
    def acc(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly5_acc(&self.ctx, p[i])
            return r
        return a_trajpoly5_acc(&self.ctx, x)
    property p:
        def __get__(self):
            return self.ctx.p
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a

from a.trajpoly7 cimport *

cdef class trajpoly7:
    cdef a_trajpoly7 ctx
    def __init__(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0, a_real a0=0, a_real a1=0, a_real j0=0, a_real j1=0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
    def gen(self, a_real ts, a_real p0, a_real p1, a_real v0=0, a_real v1=0, a_real a0=0, a_real a1=0, a_real j0=0, a_real j1=0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
        return self
    def pos(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly7_pos(&self.ctx, p[i])
            return r
        return a_trajpoly7_pos(&self.ctx, x)
    def vel(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly7_vel(&self.ctx, p[i])
            return r
        return a_trajpoly7_vel(&self.ctx, x)
    def acc(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly7_acc(&self.ctx, p[i])
            return r
        return a_trajpoly7_acc(&self.ctx, x)
    def jer(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajpoly7_jer(&self.ctx, p[i])
            return r
        return a_trajpoly7_jer(&self.ctx, x)
    property p:
        def __get__(self):
            return self.ctx.p
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a
    property j:
        def __get__(self):
            return self.ctx.j

from a.trajtrap cimport *

cdef class trajtrap:
    cdef a_trajtrap ctx
    def gen(self, a_real vm, a_real ac, a_real de, a_real p0, a_real p1, a_real v0=0, a_real v1=0):
        return a_trajtrap_gen(&self.ctx, vm, ac, de, p0, p1, v0, v1)
    def pos(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajtrap_pos(&self.ctx, p[i])
            return r
        return a_trajtrap_pos(&self.ctx, x)
    def vel(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajtrap_vel(&self.ctx, p[i])
            return r
        return a_trajtrap_vel(&self.ctx, x)
    def acc(self, object x):
        cdef array r
        cdef a_diff i
        cdef a_real *q
        cdef const a_real[::1] p
        if PyObject_HasAttrString(x, "__len__"):
            p = x
            r = real_new(p.shape[0])
            q = <a_real *>r.data
            A_ASSUME(p.shape[0])
            for i in prange(p.shape[0], nogil=True):
                q[i] = a_trajtrap_acc(&self.ctx, p[i])
            return r
        return a_trajtrap_acc(&self.ctx, x)
    property t:
        def __get__(self):
            return self.ctx.t
    property p0:
        def __get__(self):
            return self.ctx.p0
    property p1:
        def __get__(self):
            return self.ctx.p1
    property v0:
        def __get__(self):
            return self.ctx.v0
    property v1:
        def __get__(self):
            return self.ctx.v1
    property vc:
        def __get__(self):
            return self.ctx.vc
    property ta:
        def __get__(self):
            return self.ctx.ta
    property td:
        def __get__(self):
            return self.ctx.td
    property pa:
        def __get__(self):
            return self.ctx.pa
    property pd:
        def __get__(self):
            return self.ctx.pd
    property ac:
        def __get__(self):
            return self.ctx.ac
    property de:
        def __get__(self):
            return self.ctx.de

from a.version cimport *

cdef class version:
    cdef a_version ctx
    def __init__(self, unsigned int major=0, unsigned int minor=0, unsigned int third=0, unsigned int extra=0):
        self.ctx.major = major
        self.ctx.minor = minor
        self.ctx.third = third
        self.ctx.extra = extra
        self.ctx.alpha_[0] = 46
    def __repr__(self):
        cdef char[48] str
        a_version_tostr(&self.ctx, str, sizeof(str))
        return str.decode()
    @staticmethod
    def check(unsigned int major=0, unsigned int minor=0, unsigned int patch=0):
        return a_version_check(major, minor, patch)
    def cmp(self, version that):
        return a_version_cmp(&self.ctx, &that.ctx)
    def __lt__(self, version that):
        return a_version_lt(&self.ctx, &that.ctx)
    def __gt__(self, version that):
        return a_version_gt(&self.ctx, &that.ctx)
    def __le__(self, version that):
        return a_version_le(&self.ctx, &that.ctx)
    def __ge__(self, version that):
        return a_version_ge(&self.ctx, &that.ctx)
    def __eq__(self, version that):
        return a_version_eq(&self.ctx, &that.ctx)
    def __ne__(self, version that):
        return a_version_ne(&self.ctx, &that.ctx)
    def parse(self, const char *ver):
        a_version_parse(&self.ctx, ver)
        return self
    def __hash__(self):
        return object.__hash__(self)
    property major:
        def __get__(self):
            return self.ctx.major
        def __set__(self, unsigned int major):
            self.ctx.major = major
    property minor:
        def __get__(self):
            return self.ctx.minor
        def __set__(self, unsigned int minor):
            self.ctx.minor = minor
    property third:
        def __get__(self):
            return self.ctx.third
        def __set__(self, unsigned int third):
            self.ctx.third = third
    property extra:
        def __get__(self):
            return self.ctx.extra
        def __set__(self, unsigned int extra):
            self.ctx.extra = extra
    property alpha:
        def __get__(self):
            cdef char[5] alpha
            a_version_alpha(&self.ctx, alpha)
            return alpha
        def __set__(self, const char *alpha):
            a_version_set_alpha(&self.ctx, alpha)
    MAJOR = A_VERSION_MAJOR
    MINOR = A_VERSION_MINOR
    PATCH = A_VERSION_PATCH
    TWEAK = A_VERSION_TWEAK

if PY_MAJOR_VERSION >= 3:
    VERSION = A_VERSION.decode()
else:
    VERSION = A_VERSION
