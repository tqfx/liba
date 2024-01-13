from a cimport *

cdef extern from "a/crc.h":
    const a_u8 A_CRC8_POLY
    const a_u8 A_CRC8_INIT
    void a_crc8le_init(a_u8 *table, a_u8 poly)
    void a_crc8be_init(a_u8 *table, a_u8 poly)
    a_u8 a_crc8(const a_u8 *table, const void *pdata, a_size nbyte, a_u8 value)
    const a_u16 A_CRC16_POLY
    const a_u16 A_CRC16_INIT
    void a_crc16le_init(a_u16 *table, a_u16 poly)
    void a_crc16be_init(a_u16 *table, a_u16 poly)
    a_u16 a_crc16le(const a_u16 *table, const void *pdata, a_size nbyte, a_u16 value)
    a_u16 a_crc16be(const a_u16 *table, const void *pdata, a_size nbyte, a_u16 value)
    const a_u32 A_CRC32_POLY
    const a_u32 A_CRC32_INIT
    void a_crc32le_init(a_u32 *table, a_u32 poly)
    void a_crc32be_init(a_u32 *table, a_u32 poly)
    a_u32 a_crc32le(const a_u32 *table, const void *pdata, a_size nbyte, a_u32 value)
    a_u32 a_crc32be(const a_u32 *table, const void *pdata, a_size nbyte, a_u32 value)
    const a_u64 A_CRC64_POLY
    const a_u64 A_CRC64_INIT
    void a_crc64le_init(a_u64 *table, a_u64 poly)
    void a_crc64be_init(a_u64 *table, a_u64 poly)
    a_u64 a_crc64le(const a_u64 *table, const void *pdata, a_size nbyte, a_u64 value)
    a_u64 a_crc64be(const a_u64 *table, const void *pdata, a_size nbyte, a_u64 value)
    const unsigned int A_CRC_SIZ
