/*!
 @file utf.h
 @brief Unicode Transformation Format
  | Unicode | UTF-8 |
  |---------|-------|
  | U+0000000 ~ U+0000007F | 0XXXXXXX |
  | U+0000080 ~ U+000007FF | 110XXXXX 10XXXXXX |
  | U+0000800 ~ U+0000FFFF | 1110XXXX 10XXXXXX 10XXXXXX |
  | U+0010000 ~ U+001FFFFF | 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX |
  | U+0200000 ~ U+03FFFFFF | 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX |
  | U+4000000 ~ U+7FFFFFFF | 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX |
*/

#ifndef LIBA_UTF_H
#define LIBA_UTF_H

#include "a.h"

/*!
 @ingroup liba
 @addtogroup a_utf Unicode Transformation Format
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief encode one unicode code point into UTF-8
 @param[in] val the unicode code point to be encoded
 @param[in] buf a buffer to store a UTF-8 character
 @return number of bytes used in the UTF-8 encoding
*/
A_EXTERN unsigned int a_utf_encode(a_u32 val, void *buf);

/*!
 @brief decode one unicode code point from UTF-8
 @param[in] ptr points to the buffer containing the UTF-8 byte
 @param[in] num number of the buffer containing the UTF-8 byte
 @param[out] val store the unicode code point
  @arg 0 don't return the unicode code point
 @return offset to the next character
  @retval 0 null character or invalid
*/
A_EXTERN unsigned int a_utf_decode(void const *ptr, a_size num, a_u32 *val);

/*!
 @brief number of unicode code points in a UTF-8 encoded byte sequence
 @param[in] ptr points to the buffer containing the UTF-8 byte
 @param[in] num number of the buffer containing the UTF-8 byte
 @param[out] stop store the number of consumed bytes
  @arg 0 don't return the number of consumed bytes
 @return number of unicode code points
*/
A_EXTERN a_size a_utf_length(void const *ptr, a_size num, a_size *stop);
A_EXTERN a_size a_utf_length_(void const *ptr, a_size num);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_utf */

#endif /* a/utf.h */
