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

A_EXTERN a_void_t a_crc8l_init(a_u8_t ctx[A_CRC_SIZ], a_u8_t poly);
A_EXTERN a_void_t a_crc8h_init(a_u8_t ctx[A_CRC_SIZ], a_u8_t poly);
A_EXTERN a_u8_t a_crc8(a_u8_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u8_t val);

A_EXTERN a_void_t a_crc16l_init(a_u16_t ctx[A_CRC_SIZ], a_u16_t poly);
A_EXTERN a_void_t a_crc16h_init(a_u16_t ctx[A_CRC_SIZ], a_u16_t poly);
A_EXTERN a_u16_t a_crc16l(a_u16_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u16_t val);
A_EXTERN a_u16_t a_crc16h(a_u16_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u16_t val);

A_EXTERN a_void_t a_crc32l_init(a_u32_t ctx[A_CRC_SIZ], a_u32_t poly);
A_EXTERN a_void_t a_crc32h_init(a_u32_t ctx[A_CRC_SIZ], a_u32_t poly);
A_EXTERN a_u32_t a_crc32l(a_u32_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u32_t val);
A_EXTERN a_u32_t a_crc32h(a_u32_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u32_t val);

A_EXTERN a_void_t a_crc64l_init(a_u64_t ctx[A_CRC_SIZ], a_u64_t poly);
A_EXTERN a_void_t a_crc64h_init(a_u64_t ctx[A_CRC_SIZ], a_u64_t poly);
A_EXTERN a_u64_t a_crc64l(a_u64_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u64_t val);
A_EXTERN a_u64_t a_crc64h(a_u64_t const ctx[A_CRC_SIZ], a_cptr_t pdata, a_size_t nbyte, a_u64_t val);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* crc.h */
