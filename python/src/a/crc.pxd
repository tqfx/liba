from a cimport *

cdef extern from "a/crc.h":
    const a_u8_t A_CRC8_POLY
    const a_u8_t A_CRC8_INIT
    void a_crc8l_init(a_u8_t *table, a_u8_t poly)
    void a_crc8h_init(a_u8_t *table, a_u8_t poly)
    a_u8_t a_crc8(const a_u8_t *table, const void *pdata, a_size_t nbyte, a_u8_t value)
    const a_u16_t A_CRC16_POLY
    const a_u16_t A_CRC16_INIT
    void a_crc16l_init(a_u16_t *table, a_u16_t poly)
    void a_crc16h_init(a_u16_t *table, a_u16_t poly)
    a_u16_t a_crc16l(const a_u16_t *table, const void *pdata, a_size_t nbyte, a_u16_t value)
    a_u16_t a_crc16h(const a_u16_t *table, const void *pdata, a_size_t nbyte, a_u16_t value)
    const a_u32_t A_CRC32_POLY
    const a_u32_t A_CRC32_INIT
    void a_crc32l_init(a_u32_t *table, a_u32_t poly)
    void a_crc32h_init(a_u32_t *table, a_u32_t poly)
    a_u32_t a_crc32l(const a_u32_t *table, const void *pdata, a_size_t nbyte, a_u32_t value)
    a_u32_t a_crc32h(const a_u32_t *table, const void *pdata, a_size_t nbyte, a_u32_t value)
    const a_u64_t A_CRC64_POLY
    const a_u64_t A_CRC64_INIT
    void a_crc64l_init(a_u64_t *table, a_u64_t poly)
    void a_crc64h_init(a_u64_t *table, a_u64_t poly)
    a_u64_t a_crc64l(const a_u64_t *table, const void *pdata, a_size_t nbyte, a_u64_t value)
    a_u64_t a_crc64h(const a_u64_t *table, const void *pdata, a_size_t nbyte, a_u64_t value)
    const unsigned int A_CRC_SIZ
