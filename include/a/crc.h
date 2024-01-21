/*!
 @file crc.h
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
*/

#ifndef LIBA_CRC_H
#define LIBA_CRC_H

#include "a.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN void a_crc8m_init(a_u8 table[0x100], a_u8 poly);
A_EXTERN void a_crc8l_init(a_u8 table[0x100], a_u8 poly);
A_EXTERN a_u8 a_crc8(a_u8 const table[0x100], void const *pdata, a_size nbyte, a_u8 value);

A_EXTERN void a_crc16l_init(a_u16 table[0x100], a_u16 poly);
A_EXTERN void a_crc16m_init(a_u16 table[0x100], a_u16 poly);
A_EXTERN a_u16 a_crc16l(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);
A_EXTERN a_u16 a_crc16m(a_u16 const table[0x100], void const *pdata, a_size nbyte, a_u16 value);

A_EXTERN void a_crc32l_init(a_u32 table[0x100], a_u32 poly);
A_EXTERN void a_crc32m_init(a_u32 table[0x100], a_u32 poly);
A_EXTERN a_u32 a_crc32l(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);
A_EXTERN a_u32 a_crc32m(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);

A_EXTERN void a_crc64l_init(a_u64 table[0x100], a_u64 poly);
A_EXTERN void a_crc64m_init(a_u64 table[0x100], a_u64 poly);
A_EXTERN a_u64 a_crc64l(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
A_EXTERN a_u64 a_crc64m(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a/crc.h */
