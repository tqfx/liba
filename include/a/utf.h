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
 @ingroup A
 @addtogroup A_UTF Unicode Transformation Format
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief encode one unicode code point into UTF-8
 @param[in] str a buffer to store a UTF-8 character
 @param[in] val the unicode value to be encoded
 @return offset to the next character
*/
A_EXTERN unsigned int a_utf_encode(void *str, a_u32_t val);

/*!
 @brief decode one unicode code point from UTF-8
 @param[in] str string terminated with a null character
 @param[in,out] val a pointer to a variable that stores unicode
 @return offset to the next character
  @retval 0 null character or invalid
*/
A_EXTERN unsigned int a_utf_decode(void const *str, a_u32_t *val);

/*!
 @brief length of a UTF-8 string terminated with a null character
 @param[in] str string terminated with a null character
 @return length of the UTF-8 string
*/
A_EXTERN a_size_t a_utf_length(void const *str);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_utf_len(str) a_utf_length(str)

/*! @} A_UTF */

#endif /* a/utf.h */
