from a cimport *

cdef extern from "a/crc.h":
    const a_u8_t A_CRC8_POLY
    const a_u8_t A_CRC8_INIT
    void a_crc8le_init(a_u8_t *table, a_u8_t poly)
    void a_crc8be_init(a_u8_t *table, a_u8_t poly)
    a_u8_t a_crc8(const a_u8_t *table, const void *pdata, a_size_t nbyte, a_u8_t value)
    const a_u16_t A_CRC16_POLY
    const a_u16_t A_CRC16_INIT
    void a_crc16le_init(a_u16_t *table, a_u16_t poly)
    void a_crc16be_init(a_u16_t *table, a_u16_t poly)
    a_u16_t a_crc16le(const a_u16_t *table, const void *pdata, a_size_t nbyte, a_u16_t value)
    a_u16_t a_crc16be(const a_u16_t *table, const void *pdata, a_size_t nbyte, a_u16_t value)
    const a_u32_t A_CRC32_POLY
    const a_u32_t A_CRC32_INIT
    void a_crc32le_init(a_u32_t *table, a_u32_t poly)
    void a_crc32be_init(a_u32_t *table, a_u32_t poly)
    a_u32_t a_crc32le(const a_u32_t *table, const void *pdata, a_size_t nbyte, a_u32_t value)
    a_u32_t a_crc32be(const a_u32_t *table, const void *pdata, a_size_t nbyte, a_u32_t value)
    const a_u64_t A_CRC64_POLY
    const a_u64_t A_CRC64_INIT
    void a_crc64le_init(a_u64_t *table, a_u64_t poly)
    void a_crc64be_init(a_u64_t *table, a_u64_t poly)
    a_u64_t a_crc64le(const a_u64_t *table, const void *pdata, a_size_t nbyte, a_u64_t value)
    a_u64_t a_crc64be(const a_u64_t *table, const void *pdata, a_size_t nbyte, a_u64_t value)
    const unsigned int A_CRC_SIZ
