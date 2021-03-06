/*!
 @file base.h
 @brief RFC 4648 compliant base implementation
 @details https://www.ietf.org/rfc/rfc4648.txt
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_BASE_H__
#define __A_BASE_H__

#include "../def.h"

enum
{
    A_BASE16_LOWER,
    A_BASE16_UPPER,
    A_BASE16_ALL,
};

enum
{
    A_BASE32_RFC4648,
    A_BASE32_BASE32HEX,
    A_BASE32_ZBASE32,
    A_BASE32_CROCKFORD,
    A_BASE32_ALL,
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Base16 encode a buffer
 @param[in] pdata input buffer to encode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the binary encoded data
 @param[in,out] siz max size and resulting size of the encoded data
 @param[in] id select case
  @arg A_BASE16_LOWER
  @arg A_BASE16_UPPER
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base16_encode(const void *pdata, size_t nbyte, void *out, size_t *siz, unsigned int id);

/*!
 @brief Base16 decode a buffer
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the binary decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base16_decode(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Base32 encode a buffer
 @param[in] pdata input buffer to encode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the binary encoded data
 @param[in,out] siz max size and resulting size of the encoded data
 @param[in] id select case
  @arg A_BASE32_RFC4648
  @arg A_BASE32_BASE32HEX
  @arg A_BASE32_ZBASE32
  @arg A_BASE32_CROCKFORD
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base32_encode(const void *pdata, size_t nbyte, void *out, size_t *siz, unsigned int id);

/*!
 @brief Base32 decode a buffer
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the binary decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @param[in] id select case
  @arg A_BASE32_RFC4648
  @arg A_BASE32_BASE32HEX
  @arg A_BASE32_ZBASE32
  @arg A_BASE32_CROCKFORD
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base32_decode(const void *pdata, size_t nbyte, void *out, size_t *siz, unsigned int id);

/*!
 @brief base64 Encode a buffer (NUL terminated)
 @param[in] pdata input buffer to encode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 encoded data
 @param[in,out] siz max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64_encode(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Dangerously relaxed base64 decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64_decode(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Strict base64 decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64_decode_strict(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Sane base64 decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64_decode_sane(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief base64 (URL Safe, RFC 4648 section 5) Encode a buffer (NUL terminated)
 @param[in] pdata input buffer to encode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 encoded data
 @param[in,out] siz max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64url_encode(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief base64 (URL Safe, RFC 4648 section 5) Encode a buffer (NUL terminated)
 @param[in] pdata input buffer to encode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 encoded data
 @param[in,out] siz max size and resulting size of the encoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64url_encode_strict(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Dangerously relaxed base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64url_decode(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Strict base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64url_decode_strict(const void *pdata, size_t nbyte, void *out, size_t *siz);

/*!
 @brief Sane base64 (URL Safe, RFC 4648 section 5) decode a block of memory
 @param[in] pdata input buffer to decode
 @param[in] nbyte length of the input buffer
 @param[out] out destination of the base64 decoded data
 @param[in,out] siz max size and resulting size of the decoded data
 @return the execution state of the function
  @retval 0 success
*/
A_PUBLIC int a_base64url_decode_sane(const void *pdata, size_t nbyte, void *out, size_t *siz);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_BASE_H__ */
