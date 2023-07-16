from libc.stddef cimport *
from libc.limits cimport *
from libc.stdint cimport *
from libc.float cimport *

cdef extern from "a/a.h":
    const int A_FLOAT_TYPE
    const int A_FLOAT_SINGLE
    const int A_FLOAT_DOUBLE

    ctypedef  int8_t a_i8_t
    ctypedef uint8_t a_u8_t
    ctypedef  int16_t a_i16_t
    ctypedef uint16_t a_u16_t
    ctypedef  int32_t a_i32_t
    ctypedef uint32_t a_u32_t
    ctypedef  int64_t a_i64_t
    ctypedef uint64_t a_u64_t
    ctypedef  intmax_t a_imax_t
    ctypedef uintmax_t a_umax_t
    ctypedef  intptr_t a_iptr_t
    ctypedef uintptr_t a_uptr_t
    ctypedef ptrdiff_t a_diff_t
    ctypedef    size_t a_size_t

    ctypedef  float a_f32_t
    ctypedef double a_f64_t
    ctypedef float a_float_t
    ctypedef union a_float_u:
        a_float_t f
        a_float_t *p
    const a_float_t A_FLOAT_INF
    const a_float_t A_FLOAT_NAN

    a_umax_t a_hash_bkdr(const char *str, a_umax_t val);
