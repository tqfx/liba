/*!
 @file crc.h
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
*/

#ifndef LIBA_CRC_H
#define LIBA_CRC_H

#include "a.h"

#define A_CRC_SIZ 0x100

#define A_CRC8_POLY A_U8_C(0x31)
#define A_CRC8_INIT A_U8_C(0x00)

#define A_CRC16_POLY A_U16_C(0xA001)
#define A_CRC16_INIT A_U16_C(0x0000)

#define A_CRC32_POLY A_U32_C(0xEDB88320)
#define A_CRC32_INIT A_U32_C(0xFFFFFFFF)

#define A_CRC64_POLY A_U64_C(0x42F0E1EBA9EA3693)
#define A_CRC64_INIT A_U64_C(0xFFFFFFFFFFFFFFFF)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN void a_crc8le_init(a_u8 table[A_CRC_SIZ], a_u8 poly);
A_EXTERN void a_crc8be_init(a_u8 table[A_CRC_SIZ], a_u8 poly);
A_EXTERN a_u8 a_crc8(a_u8 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u8 value);

A_EXTERN void a_crc16le_init(a_u16 table[A_CRC_SIZ], a_u16 poly);
A_EXTERN void a_crc16be_init(a_u16 table[A_CRC_SIZ], a_u16 poly);
A_EXTERN a_u16 a_crc16le(a_u16 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u16 value);
A_EXTERN a_u16 a_crc16be(a_u16 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u16 value);

A_EXTERN void a_crc32le_init(a_u32 table[A_CRC_SIZ], a_u32 poly);
A_EXTERN void a_crc32be_init(a_u32 table[A_CRC_SIZ], a_u32 poly);
A_EXTERN a_u32 a_crc32le(a_u32 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u32 value);
A_EXTERN a_u32 a_crc32be(a_u32 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u32 value);

A_EXTERN void a_crc64le_init(a_u64 table[A_CRC_SIZ], a_u64 poly);
A_EXTERN void a_crc64be_init(a_u64 table[A_CRC_SIZ], a_u64 poly);
A_EXTERN a_u64 a_crc64le(a_u64 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u64 value);
A_EXTERN a_u64 a_crc64be(a_u64 const table[A_CRC_SIZ], void const *pdata, a_size nbyte, a_u64 value);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a/crc.h */
