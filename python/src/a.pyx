#cython: autotestdict=False
#cython: auto_pickle=False
#cython: boundscheck=False
#cython: wraparound=False
from a cimport *
from cpython cimport *
from cpython.array cimport array
from cython.parallel import prange

cdef inline array_i8(object o):
    return array('b', o)

cdef inline array_u8(object o):
    return array('B', o)

cdef inline array_i16(object o):
    return array('h', o)

cdef inline array_u16(object o):
    return array('H', o)

cdef inline array_i32(object o):
    if INT32_MAX == INT_MAX:
        return array('i', o)
    return array('l', o)

cdef inline array_u32(object o):
    if UINT32_MAX == UINT_MAX:
        return array('I', o)
    return array('L', o)

cdef inline array_i64(object o):
    if INT64_MAX == LONG_MAX:
        return array('l', o)
    return array('q', o)

cdef inline array_u64(object o):
    if UINT64_MAX == ULONG_MAX:
        return array('L', o)
    return array('Q', o)

cdef inline array_f32(object o):
    return array('f', o)

cdef inline array_f64(object o):
    return array('d', o)

cdef inline array_num(object o):
    if A_FLOAT_TYPE == A_FLOAT_SINGLE:
        return array('f', o)
    return array('d', o)

def hash_bkdr(bytes str, a_u32 val = 0) -> a_u32:
    return a_hash_bkdr(str, val)

def hash_sdbm(bytes str, a_u32 val = 0) -> a_u32:
    return a_hash_sdbm(str, val)

from a.crc cimport *

cdef class crc8:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u8((0,) * 0x100)
    def gen(self, a_u8 poly, bint reversed = False):
        if reversed:
            a_crc8l_init(<a_u8 *>self.table.data.as_voidptr, poly)
        else:
            a_crc8m_init(<a_u8 *>self.table.data.as_voidptr, poly)
        return self
    def __init__(self, a_u8 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u8 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return a_crc8(<a_u8 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u8 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(1)
        cdef unsigned char *p = <unsigned char *>block
        value = a_crc8(<a_u8 *>self.table.data.as_voidptr, p, n, value)
        p[n] = value
        return block

cdef class crc16:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u16((0,) * 0x100)
    cdef a_u16 (*eval)(const a_u16 *, const void *, a_size, a_u16)
    def gen(self, a_u16 poly, bint reversed = False):
        if reversed:
            a_crc16l_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16l
        else:
            a_crc16m_init(<a_u16 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc16m
        return self
    def __init__(self, a_u16 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u16 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u16 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u16 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(2)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u16 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc16m:
            a_u16_setb(p + n, value)
        else:
            a_u16_setl(p + n, value)
        return block

cdef class crc32:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u32((0,) * 0x100)
    cdef a_u32 (*eval)(const a_u32 *, const void *, a_size, a_u32)
    def gen(self, a_u32 poly, bint reversed = False):
        if reversed:
            a_crc32l_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32l
        else:
            a_crc32m_init(<a_u32 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc32m
        return self
    def __init__(self, a_u32 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u32 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u32 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u32 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(4)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u32 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc32m:
            a_u32_setb(p + n, value)
        else:
            a_u32_setl(p + n, value)
        return block

cdef class crc64:
    cdef readonly array table
    def __cinit__(self):
        self.table = array_u64((0,) * 0x100)
    cdef a_u64 (*eval)(const a_u64 *, const void *, a_size, a_u64)
    def gen(self, a_u64 poly, bint reversed = False):
        if reversed:
            a_crc64l_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64l
        else:
            a_crc64m_init(<a_u64 *>self.table.data.as_voidptr, poly)
            self.eval = a_crc64m
        return self
    def __init__(self, a_u64 poly, bint reversed = False):
        self.gen(poly, reversed)
    def __call__(self, bytes block, a_u64 value = 0):
        cdef const unsigned char *p = <const unsigned char *>block
        return self.eval(<a_u64 *>self.table.data.as_voidptr, p, len(block), value)
    def pack(self, bytes block, a_u64 value = 0):
        cdef size_t n = len(block)
        block = block + bytes(8)
        cdef unsigned char *p = <unsigned char *>block
        value = self.eval(<a_u64 *>self.table.data.as_voidptr, p, n, value)
        if self.eval == a_crc64m:
            a_u64_setb(p + n, value)
        else:
            a_u64_setl(p + n, value)
        return block

from a.hpf cimport *

cdef class hpf:
    cdef a_hpf ctx
    def __init__(self, a_float fc, a_float ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
    def gen(self, a_float fc, a_float ts):
        a_hpf_init(&self.ctx, a_hpf_gen(fc, ts))
        return self
    def __call__(self, a_float x):
        return a_hpf_iter(&self.ctx, x)
    def zero(self):
        a_hpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_float alpha):
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
    def __init__(self, a_float fc, a_float ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
    def gen(self, a_float fc, a_float ts):
        a_lpf_init(&self.ctx, a_lpf_gen(fc, ts))
        return self
    def __call__(self, a_float x):
        return a_lpf_iter(&self.ctx, x)
    def zero(self):
        a_lpf_zero(&self.ctx)
        return self
    property alpha:
        def __get__(self):
            return self.ctx.alpha
        def __set__(self, a_float alpha):
            self.ctx.alpha = alpha
    property output:
        def __get__(self):
            return self.ctx.output

from a.math cimport *

def isqrt(x: int):
    if x <= 1:
        return x
    x0 = 1 << ((x.bit_length() + 1) >> 1)
    x1 = (x0 + x // x0) >> 1
    while x0 > x1:
        x0 = x1
        x1 = (x0 + x // x0) >> 1
    return x0

def sqrt_u32(x):
    cdef array y
    cdef a_u32 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_u32(x)
        p = <a_u32 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_u32_sqrt(p[i])
        return array_u16(y)
    return a_u32_sqrt(x)

def sqrt_u64(x):
    cdef array y
    cdef a_u64 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_u64(x)
        p = <a_u64 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_u64_sqrt(p[i])
        return array_u32(y)
    return a_u64_sqrt(x)

def rsqrt_f32(x):
    cdef array y
    cdef a_f32 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_f32(x)
        p = <a_f32 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_f32_rsqrt(p[i])
        return y
    return a_f32_rsqrt(x)

def rsqrt_f64(x):
    cdef array y
    cdef a_f64 *p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_f64(x)
        p = <a_f64 *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_f64_rsqrt(p[i])
        return y
    return a_f64_rsqrt(x)

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
    def __call__(unsigned int e, x, a):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        cdef unsigned int m = e
        cdef array a_ = array_num(a)
        cdef a_float *a_p = <a_float *>a_.data.as_voidptr
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf(m, p[i], a_p)
            return y
        return a_mf(m, x, a_p)
    @staticmethod
    def gauss(x, a_float sigma, a_float c):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gauss(p[i], sigma, c)
            return y
        return a_mf_gauss(x, sigma, c)
    @staticmethod
    def gauss2(x, a_float sigma1, a_float c1, a_float sigma2, a_float c2):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gauss2(p[i], sigma1, c1, sigma2, c2)
            return y
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2)
    @staticmethod
    def gbell(x, a_float a, a_float b, a_float c):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gbell(p[i], a, b, c)
            return y
        return a_mf_gbell(x, a, b, c)
    @staticmethod
    def sig(x, a_float a, a_float c):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_sig(p[i], a, c)
            return y
        return a_mf_sig(x, a, c)
    @staticmethod
    def dsig(x, a_float a1, a_float c1, a_float a2, a_float c2):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_dsig(p[i], a1, c1, a2, c2)
            return y
        return a_mf_dsig(x, a1, c1, a2, c2)
    @staticmethod
    def psig(x, a_float a1, a_float c1, a_float a2, a_float c2):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_psig(p[i], a1, c1, a2, c2)
            return y
        return a_mf_psig(x, a1, c1, a2, c2)
    @staticmethod
    def trap(x, a_float a, a_float b, a_float c, a_float d):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_trap(p[i], a, b, c, d)
            return y
        return a_mf_trap(x, a, b, c, d)
    @staticmethod
    def tri(x, a_float a, a_float b, a_float c):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_tri(p[i], a, b, c)
            return y
        return a_mf_tri(x, a, b, c)
    @staticmethod
    def lins(x, a_float a, a_float b):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_lins(p[i], a, b)
            return y
        return a_mf_lins(x, a, b)
    @staticmethod
    def linz(x, a_float a, a_float b):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_linz(p[i], a, b)
            return y
        return a_mf_linz(x, a, b)
    @staticmethod
    def s(x, a_float a, a_float b):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_s(p[i], a, b)
            return y
        return a_mf_s(x, a, b)
    @staticmethod
    def z(x, a_float a, a_float b):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_z(p[i], a, b)
            return y
        return a_mf_z(x, a, b)
    @staticmethod
    def pi(x, a_float a, a_float b, a_float c, a_float d):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_pi(p[i], a, b, c, d)
            return y
        return a_mf_pi(x, a, b, c, d)

from a.pid cimport *

cdef class pid:
    cdef a_pid ctx
    def __init__(self):
        self.ctx.kp = 1
        self.ctx.summax = +A_FLOAT_INF
        self.ctx.summin = -A_FLOAT_INF
        self.ctx.outmax = +A_FLOAT_INF
        self.ctx.outmin = -A_FLOAT_INF
        a_pid_init(&self.ctx)
    def kpid(self, a_float kp, a_float ki, a_float kd):
        a_pid_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_run(&self.ctx, set, fdb)
    def pos(self, a_float set, a_float fdb):
        return a_pid_pos(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_float kp):
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_float ki):
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_float kd):
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.summax
        def __set__(self, a_float summax):
            self.ctx.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.summin
        def __set__(self, a_float summin):
            self.ctx.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.sum
    property outmax:
        def __get__(self):
            return self.ctx.outmax
        def __set__(self, a_float outmax):
            self.ctx.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.outmin
        def __set__(self, a_float outmin):
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
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.kp = self.ctx.pid.kp = 1
        self.ctx.op = a_fuzzy_equ
        a_pid_fuzzy_init(&self.ctx)
    def op(self, unsigned int op):
        a_pid_fuzzy_set_op(&self.ctx, op)
        return self
    def rule(self, me, mec, mkp, mki, mkd):
        self.me = array_num((_2 for _1 in me for _2 in _1))
        self.mec = array_num((_2 for _1 in mec for _2 in _1))
        self.mkp = array_num((_2 for _1 in mkp for _2 in _1))
        self.mki = array_num((_2 for _1 in mki for _2 in _1))
        self.mkd = array_num((_2 for _1 in mkd for _2 in _1))
        a_pid_fuzzy_rule(&self.ctx, <unsigned int>len(me),
                         <a_float *>self.me.data.as_voidptr,
                         <a_float *>self.mec.data.as_voidptr,
                         <a_float *>self.mkp.data.as_voidptr,
                         <a_float *>self.mki.data.as_voidptr,
                         <a_float *>self.mkd.data.as_voidptr)
        return self
    def set_block(self, unsigned int num):
        cdef void *ptr = a_pid_fuzzy_block(&self.ctx)
        ptr = PyMem_Realloc(ptr, A_PID_FUZZY_BLOCK(num))
        a_pid_fuzzy_set_block(&self.ctx, ptr, num)
        return self
    def kpid(self, a_float kp, a_float ki, a_float kd):
        a_pid_fuzzy_kpid(&self.ctx, kp, ki, kd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_fuzzy_run(&self.ctx, set, fdb)
    def pos(self, a_float set, a_float fdb):
        return a_pid_fuzzy_pos(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_fuzzy_inc(&self.ctx, set, fdb)
    def __dealloc__(self):
        PyMem_Free(a_pid_fuzzy_block(&self.ctx))
    def zero(self):
        a_pid_fuzzy_zero(&self.ctx)
        return self
    property kp:
        def __get__(self):
            return self.ctx.kp
        def __set__(self, a_float kp):
            self.ctx.pid.kp = kp
            self.ctx.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.ki
        def __set__(self, a_float ki):
            self.ctx.pid.ki = ki
            self.ctx.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.kd
        def __set__(self, a_float kd):
            self.ctx.pid.kd = kd
            self.ctx.kd = kd
    property summax:
        def __get__(self):
            return self.ctx.pid.summax
        def __set__(self, a_float summax):
            self.ctx.pid.summax = summax
    property summin:
        def __get__(self):
            return self.ctx.pid.summin
        def __set__(self, a_float summin):
            self.ctx.pid.summin = summin
    property sum:
        def __get__(self):
            return self.ctx.pid.sum
    property outmax:
        def __get__(self):
            return self.ctx.pid.outmax
        def __set__(self, a_float outmax):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.pid.outmin
        def __set__(self, a_float outmin):
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
    property order:
        def __get__(self):
            return self.ctx.order
    property block:
        def __get__(self):
            return self.ctx.block
        def __set__(self, unsigned int block):
            self.set_block(block)

from a.pid_neuro cimport *

cdef class pid_neuro:
    cdef a_pid_neuro ctx
    def __init__(self):
        self.ctx.pid.summax = +A_FLOAT_INF
        self.ctx.pid.summin = -A_FLOAT_INF
        self.ctx.pid.outmax = +A_FLOAT_INF
        self.ctx.pid.outmin = -A_FLOAT_INF
        self.ctx.k = self.ctx.pid.kp = 1
        self.ctx.wp = 0.1
        self.ctx.wi = 0.1
        self.ctx.wd = 0.1
        a_pid_neuro_init(&self.ctx)
    def kpid(self, a_float k, a_float kp, a_float ki, a_float kd):
        a_pid_neuro_kpid(&self.ctx, k, kp, ki, kd)
        return self
    def wpid(self, a_float wp, a_float wi, a_float wd):
        a_pid_neuro_wpid(&self.ctx, wp, wi, wd)
        return self
    def run(self, a_float set, a_float fdb):
        return a_pid_neuro_run(&self.ctx, set, fdb)
    def inc(self, a_float set, a_float fdb):
        return a_pid_neuro_inc(&self.ctx, set, fdb)
    def zero(self):
        a_pid_neuro_zero(&self.ctx)
        return self
    property k:
        def __get__(self):
            return self.ctx.k
        def __set__(self, a_float k):
            self.ctx.k = k
    property kp:
        def __get__(self):
            return self.ctx.pid.kp
        def __set__(self, a_float kp):
            self.ctx.pid.kp = kp
    property ki:
        def __get__(self):
            return self.ctx.pid.ki
        def __set__(self, a_float ki):
            self.ctx.pid.ki = ki
    property kd:
        def __get__(self):
            return self.ctx.pid.kd
        def __set__(self, a_float kd):
            self.ctx.pid.kd = kd
    property wp:
        def __get__(self):
            return self.ctx.wp
        def __set__(self, a_float wp):
            self.ctx.wp = wp
    property wi:
        def __get__(self):
            return self.ctx.wi
        def __set__(self, a_float wi):
            self.ctx.wi = wi
    property wd:
        def __get__(self):
            return self.ctx.wd
        def __set__(self, a_float wd):
            self.ctx.wd = wd
    property outmax:
        def __get__(self):
            return self.ctx.pid.outmax
        def __set__(self, a_float outmax):
            self.ctx.pid.outmax = outmax
    property outmin:
        def __get__(self):
            return self.ctx.pid.outmin
        def __set__(self, a_float outmin):
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

def poly_eval(x, *a):
    cdef array y
    cdef array a_
    cdef a_float *p
    cdef a_float *a_p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size a_n = len(a)
    a_ = array_num(a)
    a_p = <a_float *>a_.data.as_voidptr
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_num(x)
        p = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_poly_eval(a_p, a_n, p[i])
        return y
    return a_poly_eval(a_p, a_n, x)

def poly_evar(x, *a):
    cdef array y
    cdef array a_
    cdef a_float *p
    cdef a_float *a_p
    cdef Py_ssize_t i
    cdef Py_ssize_t n
    cdef a_size a_n = len(a)
    a_ = array_num(a)
    a_p = <a_float *>a_.data.as_voidptr
    if PyObject_HasAttrString(x, "__contains__"):
        n = len(x)
        y = array_num(x)
        p = <a_float *>y.data.as_voidptr
        for i in prange(n, nogil=True):
            p[i] = a_poly_evar(a_p, a_n, p[i])
        return y
    return a_poly_evar(a_p, a_n, x)

from a.tf cimport *

cdef class tf:
    cdef a_tf ctx
    def __init__(self, num, den):
        tf.num.__set__(self, num)
        tf.den.__set__(self, den)
    def __call__(self, a_float x):
        return a_tf_iter(&self.ctx, x)
    def zero(self):
        a_tf_zero(&self.ctx)
        return self
    cdef array _num
    cdef readonly array input
    property num:
        def __get__(self):
            return self._num
        def __set__(self, num):
            self._num = array_num(num)
            self.input = array_num(num)
            a_tf_set_num(&self.ctx, <unsigned int>len(num), <a_float *>self._num.data.as_voidptr, <a_float *>self.input.data.as_voidptr)
    cdef array _den
    cdef readonly array output
    property den:
        def __get__(self):
            return self._den
        def __set__(self, den):
            self._den = array_num(den)
            self.output = array_num(den)
            a_tf_set_den(&self.ctx, <unsigned int>len(den), <a_float *>self._den.data.as_voidptr, <a_float *>self.output.data.as_voidptr)

from a.trajbell cimport *

cdef class trajbell:
    cdef a_trajbell ctx
    def gen(self, a_float jm, a_float am, a_float vm, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0):
        return a_trajbell_gen(&self.ctx, jm, am, vm, p0, p1, v0, v1)
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajbell_pos(&self.ctx, p[i])
            return x
        return a_trajbell_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajbell_vel(&self.ctx, p[i])
            return x
        return a_trajbell_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajbell_acc(&self.ctx, p[i])
            return x
        return a_trajbell_acc(&self.ctx, dt)
    def jer(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajbell_jer(&self.ctx, p[i])
            return x
        return a_trajbell_jer(&self.ctx, dt)
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
    def __init__(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0):
        a_trajpoly3_gen(&self.ctx, ts, p0, p1, v0, v1)
    def gen(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0):
        a_trajpoly3_gen(&self.ctx, ts, p0, p1, v0, v1)
        return self
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly3_pos(&self.ctx, p[i])
            return x
        return a_trajpoly3_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly3_vel(&self.ctx, p[i])
            return x
        return a_trajpoly3_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly3_acc(&self.ctx, p[i])
            return x
        return a_trajpoly3_acc(&self.ctx, dt)
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
    def __init__(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0):
        a_trajpoly5_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1)
    def gen(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0):
        a_trajpoly5_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1)
        return self
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly5_pos(&self.ctx, p[i])
            return x
        return a_trajpoly5_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly5_vel(&self.ctx, p[i])
            return x
        return a_trajpoly5_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly5_acc(&self.ctx, p[i])
            return x
        return a_trajpoly5_acc(&self.ctx, dt)
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
    def __init__(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
    def gen(self, a_float ts, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0, a_float a0 = 0, a_float a1 = 0, a_float j0 = 0, a_float j1 = 0):
        a_trajpoly7_gen(&self.ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1)
        return self
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly7_pos(&self.ctx, p[i])
            return x
        return a_trajpoly7_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly7_vel(&self.ctx, p[i])
            return x
        return a_trajpoly7_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly7_acc(&self.ctx, p[i])
            return x
        return a_trajpoly7_acc(&self.ctx, dt)
    def jer(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajpoly7_jer(&self.ctx, p[i])
            return x
        return a_trajpoly7_jer(&self.ctx, dt)
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
    def gen(self, a_float vm, a_float ac, a_float de, a_float p0, a_float p1, a_float v0 = 0, a_float v1 = 0):
        return a_trajtrap_gen(&self.ctx, vm, ac, de, p0, p1, v0, v1)
    def pos(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_pos(&self.ctx, p[i])
            return x
        return a_trajtrap_pos(&self.ctx, dt)
    def vel(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_vel(&self.ctx, p[i])
            return x
        return a_trajtrap_vel(&self.ctx, dt)
    def acc(self, dt):
        cdef array x
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(dt, "__contains__"):
            n = len(dt)
            x = array_num(dt)
            p = <a_float *>x.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_trajtrap_acc(&self.ctx, p[i])
            return x
        return a_trajtrap_acc(&self.ctx, dt)
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
    def __init__(self, unsigned int major = 0, unsigned int minor = 0, unsigned int third = 0, unsigned int extra = 0):
        self.ctx.major = major
        self.ctx.minor = minor
        self.ctx.third = third
        self.ctx.extra = extra
        self.ctx.alpha[0] = 46
    def __repr__(self):
        cdef char str[48]
        a_version_tostr(&self.ctx, str, sizeof(str))
        return str.decode()
    @staticmethod
    def check(unsigned int major = 0, unsigned int minor = 0, unsigned int patch = 0):
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
    def parse(self, bytes ver):
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
            cdef char alpha[5]
            a_version_alpha(&self.ctx, alpha)
            return alpha
        def __set__(self, bytes alpha):
            a_version_set_alpha(&self.ctx, alpha)
    MAJOR = A_VERSION_MAJOR
    MINOR = A_VERSION_MINOR
    PATCH = A_VERSION_PATCH
    TWEAK = A_VERSION_TWEAK

if PY_MAJOR_VERSION >= 3:
    VERSION = A_VERSION.decode()
else:
    VERSION = A_VERSION
