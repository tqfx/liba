from a cimport *

cdef extern from "a/crc.h":
    void a_crc8m_init(a_u8 *table, a_u8 poly) nogil
    void a_crc8l_init(a_u8 *table, a_u8 poly) nogil
    a_u8 a_crc8(const a_u8 *table, const void *pdata, a_size nbyte, a_u8 value) nogil
    void a_crc16m_init(a_u16 *table, a_u16 poly) nogil
    void a_crc16l_init(a_u16 *table, a_u16 poly) nogil
    a_u16 a_crc16m(const a_u16 *table, const void *pdata, a_size nbyte, a_u16 value) nogil
    a_u16 a_crc16l(const a_u16 *table, const void *pdata, a_size nbyte, a_u16 value) nogil
    void a_crc32m_init(a_u32 *table, a_u32 poly) nogil
    void a_crc32l_init(a_u32 *table, a_u32 poly) nogil
    a_u32 a_crc32m(const a_u32 *table, const void *pdata, a_size nbyte, a_u32 value) nogil
    a_u32 a_crc32l(const a_u32 *table, const void *pdata, a_size nbyte, a_u32 value) nogil
    void a_crc64m_init(a_u64 *table, a_u64 poly) nogil
    void a_crc64l_init(a_u64 *table, a_u64 poly) nogil
    a_u64 a_crc64m(const a_u64 *table, const void *pdata, a_size nbyte, a_u64 value) nogil
    a_u64 a_crc64l(const a_u64 *table, const void *pdata, a_size nbyte, a_u64 value) nogil
