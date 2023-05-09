include "__init__.pxi"
from libc.stddef cimport *
from libc.stdint cimport *

cdef extern from "a/a.h":

    ctypedef  int   a_bool_t
    ctypedef void   a_void_t
    ctypedef size_t a_size_t

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

    ctypedef   signed int a_i_t
    ctypedef unsigned int a_u_t
    ctypedef   signed long a_il_t
    ctypedef unsigned long a_ul_t
    ctypedef   signed short a_is_t
    ctypedef unsigned short a_us_t
    ctypedef   signed long long a_ill_t
    ctypedef unsigned long long a_ull_t

    ctypedef          int  a_int_t
    ctypedef unsigned int a_uint_t

    ctypedef unsigned char a_byte_t
    ctypedef          char a_char_t

    ctypedef char       * a_str_t
    ctypedef const char *a_cstr_t
    ctypedef void       *a_vptr_t
    ctypedef const void *a_cptr_t

    ctypedef  float a_f32_t
    ctypedef double a_f64_t
    IF A_SIZE_REAL == 8:
        ctypedef double a_real_t
    IF A_SIZE_REAL == 4:
        ctypedef float a_real_t
    ctypedef union a_real_u:
        a_real_t f
        a_real_t *p
