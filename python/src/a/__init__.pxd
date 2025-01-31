from libc.stddef cimport *
from libc.limits cimport *
from libc.stdint cimport *
from libc.float cimport *

cdef extern from "a/a.h":
    void A_ASSUME(bint) nogil

    ctypedef  int8_t a_i8
    ctypedef uint8_t a_u8
    ctypedef  int16_t a_i16
    ctypedef uint16_t a_u16
    ctypedef  int32_t a_i32
    ctypedef uint32_t a_u32
    ctypedef  int64_t a_i64
    ctypedef uint64_t a_u64
    ctypedef  intmax_t a_imax
    ctypedef uintmax_t a_umax
    ctypedef  intptr_t a_iptr
    ctypedef uintptr_t a_uptr
    ctypedef ptrdiff_t a_diff
    ctypedef    size_t a_size

    ctypedef  float a_f32
    ctypedef double a_f64
    ctypedef double a_real
    const a_real A_REAL_INF
    const a_real A_REAL_NAN
    const int A_REAL_SINGLE
    const int A_REAL_DOUBLE
    const int A_REAL_TYPE

    a_u16 a_u16_getl(const void *b) nogil
    a_u16 a_u16_getb(const void *b) nogil
    void a_u16_setl(void *b, a_u16 x) nogil
    void a_u16_setb(void *b, a_u16 x) nogil
    a_u32 a_u32_getl(const void *b) nogil
    a_u32 a_u32_getb(const void *b) nogil
    void a_u32_setl(void *b, a_u32 x) nogil
    void a_u32_setb(void *b, a_u32 x) nogil
    a_u64 a_u64_getl(const void *b) nogil
    a_u64 a_u64_getb(const void *b) nogil
    void a_u64_setl(void *b, a_u64 x) nogil
    void a_u64_setb(void *b, a_u64 x) nogil
