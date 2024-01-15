/*!
 @file str.h
 @brief basic string library
*/

#ifndef LIBA_STR_H
#define LIBA_STR_H

#include "a.h"
#include <stdarg.h>
#include <string.h>

/*!
 @ingroup A
 @addtogroup A_STR basic string library
 @{
*/

// clang-format off
#define A_STR_NUL {A_NULL, 0, 0}
// clang-format on

/*!
 @brief instance structure for basic string
*/
typedef struct a_str
{
    char *_ptr; /*!< string */
    a_size _num; /*!< length */
    a_size _mem; /*!< memory */
} a_str;

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INTERN char *a_str_ptr(a_str const *ctx) { return ctx->_ptr; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INTERN a_size a_str_len(a_str const *ctx) { return ctx->_num; }

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INTERN a_size a_str_mem(a_str const *ctx) { return ctx->_mem; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than memory
 @note should check if string is empty
 @return specified character
*/
A_INTERN char a_str_at_(a_str const *ctx, a_size idx) { return ctx->_ptr[idx]; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than length
 @return specified character
  @retval 0 out of bounds
*/
A_INTERN char a_str_at(a_str const *ctx, a_size idx)
{
    return a_likely(idx < ctx->_num) ? ctx->_ptr[idx] : 0;
}

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character -length < idx < length
 @return specified character
  @retval 0 out of bounds
*/
A_INTERN char a_str_idx(a_str const *ctx, a_diff idx)
{
    a_size const num = idx < 0 ? a_size_c(idx) + ctx->_num : a_size_c(idx);
    return a_likely(num < ctx->_num) ? ctx->_ptr[num] : 0;
}

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] len new length for a pointer to string structure
 @note length must less than memory
*/
A_INTERN void a_str_set_len_(a_str *ctx, a_size len) { ctx->_num = len; }

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] len new length for a pointer to string structure
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_INTERN int a_str_set_len(a_str *ctx, a_size len)
{
    return a_likely(len < ctx->_mem) ? ((void)(ctx->_num = len), A_SUCCESS) : A_FAILURE;
}

/*!
 @brief drop all characters for a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_INTERN void a_str_drop(a_str *ctx) { ctx->_num = 0; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to string structure from memory
*/
A_EXTERN a_str *a_str_new(void);

/*!
 @brief deallocate a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_die(a_str *ctx);

/*!
 @brief constructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_ctor(a_str *ctx);

/*!
 @brief destructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_dtor(a_str *ctx);

/*!
 @brief initialize a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to initialize
 @param[in] nbyte length of data to initialize
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_init(a_str *ctx, void const *pdata, a_size nbyte);

/*!
 @brief initialize a pointer to string structure by copying
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_copy(a_str *ctx, a_str const *obj);

/*!
 @brief initialize a pointer to string structure by moving
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN void a_str_move(a_str *ctx, a_str *obj);

/*!
 @brief terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @note should use free to release this memory
 @return string of string structure
*/
A_EXTERN char *a_str_exit(a_str *ctx);

/*!
 @brief compare the string lhs with the string rhs
 @param[in] lhs string structure to be compared
 @param[in] rhs string structure to be compared
 @return relationship between the strings
  @retval <0 string lhs < string rhs
  @retval >0 string lhs > string rhs
  @retval 0 string lhs == string rhs
*/
A_EXTERN int a_str_cmp(a_str const *lhs, a_str const *rhs);

/*!
 @brief allocate memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem new memory capacity of string
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_alloc(a_str *ctx, a_size mem);
A_EXTERN int a_str_alloc_(a_str *ctx, a_size mem);

/*!
 @brief get character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return parsed character
  @retval ~0 failure
*/
A_EXTERN int a_str_getc(a_str *ctx);
A_EXTERN int a_str_getc_(a_str *ctx);

/*!
 @brief put character to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character to be parsed
 @return parsed character
  @retval ~0 failure
*/
A_EXTERN int a_str_putc(a_str *ctx, int c);
A_EXTERN int a_str_putc_(a_str *ctx, int c);

/*!
 @brief get memory block to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to memory block to get
 @param[in] nbyte length of memory block to get
 @return number of parsed characters
*/
A_EXTERN a_size a_str_getn(a_str *ctx, void *pdata, a_size nbyte);
A_EXTERN a_size a_str_getn_(a_str *ctx, void *pdata, a_size nbyte);

/*!
 @brief put memory block to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to memory block to put
 @param[in] nbyte length of memory block to put
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_putn(a_str *ctx, void const *pdata, a_size nbyte);
A_EXTERN int a_str_putn_(a_str *ctx, void const *pdata, a_size nbyte);

/*!
 @brief put string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_puts(a_str *ctx, void const *str);
A_EXTERN int a_str_puts_(a_str *ctx, void const *str);

/*!
 @brief concat the string structure obj to the string structure ctx
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_cat(a_str *ctx, a_str const *obj);
A_EXTERN int a_str_cat_(a_str *ctx, a_str const *obj);

/*!
 @brief format string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be parsed
 @param[in] va instance of variable argument
 @return number of parsed characters
*/
A_EXTERN int a_str_putf_(a_str *ctx, char const *fmt, va_list va) A_FORMAT(printf, 2, 0);

/*!
 @brief format string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be parsed
 @return number of parsed characters
*/
A_EXTERN int a_str_putf(a_str *ctx, char const *fmt, ...) A_FORMAT(printf, 2, 3);

/*!
 @brief length for a pointer to string structure using UTF-8
 @param[in] ctx points to an instance of string structure
 @return number of code points
*/
A_EXTERN a_size a_str_utflen(a_str const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_STR */

#endif /* a/str.h */
