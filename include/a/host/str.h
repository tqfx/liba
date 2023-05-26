/*!
 @file str.h
 @brief basic string library
*/

#ifndef LIBA_HOST_STR_H
#define LIBA_HOST_STR_H

#include "a.h"
#include <string.h>
#include <stdarg.h>

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
typedef struct a_str_s
{
    char *_ptr; /*!< string */
    a_size_t _num; /*!< length */
    a_size_t _mem; /*!< memory */
} a_str_s;

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INTERN char *a_str_ptr(a_str_s const *const ctx) { return ctx->_ptr; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INTERN a_size_t a_str_len(a_str_s const *const ctx) { return ctx->_num; }

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INTERN a_size_t a_str_mem(a_str_s const *const ctx) { return ctx->_mem; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than memory
 @note should check if string is empty
 @return specified character
*/
A_INTERN char a_str_at_(a_str_s const *const ctx, a_size_t const idx) { return ctx->_ptr[idx]; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than length
 @return specified character
  @retval 0 out of bounds
*/
A_INTERN char a_str_at(a_str_s const *const ctx, a_size_t const idx)
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
A_INTERN char a_str_idx(a_str_s const *const ctx, a_diff_t const idx)
{
    a_size_t const num = idx < 0 ? a_size_c(, idx) + ctx->_num : a_size_c(, idx);
    return a_likely(num < ctx->_num) ? ctx->_ptr[num] : 0;
}

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] len new length for a pointer to string structure
 @note length must less than memory
*/
A_INLINE void a_str_set_len_(a_str_s *const ctx, a_size_t const len) { ctx->_num = len; }

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] len new length for a pointer to string structure
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_INLINE int a_str_set_len(a_str_s *const ctx, a_size_t const len)
{
    return a_likely(len < ctx->_mem) ? ((void)(ctx->_num = len), A_SUCCESS) : A_FAILURE;
}

/*!
 @brief drop all characters for a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_INTERN void a_str_drop(a_str_s *const ctx) { ctx->_num = 0; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief allocate a pointer to string structure from memory
*/
A_EXTERN a_str_s *a_str_new(void);

/*!
 @brief deallocate a pointer to string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_die(a_str_s *ctx);

/*!
 @brief constructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_ctor(a_str_s *ctx);

/*!
 @brief destructor for string structure
 @param[in] ctx points to an instance of string structure
*/
A_EXTERN void a_str_dtor(a_str_s *ctx);

/*!
 @brief initialize a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to data to initialize
 @param[in] nbyte length of data to initialize
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_init(a_str_s *ctx, void const *pdata, a_size_t nbyte);

/*!
 @brief initialize a pointer to string structure by copying
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_copy(a_str_s *ctx, a_str_s const *obj);

/*!
 @brief initialize a pointer to string structure by moving
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
*/
A_EXTERN a_str_s *a_str_move(a_str_s *ctx, a_str_s *obj);

/*!
 @brief terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @note should use free to release this memory
 @return string of string structure
*/
A_EXTERN char *a_str_exit(a_str_s *ctx);

/*!
 @brief compare the string lhs with the string rhs
 @param[in] lhs string structure to be compared
 @param[in] rhs string structure to be compared
 @return relationship between the strings
  @retval <0 string lhs < string rhs
  @retval >0 string lhs > string rhs
  @retval 0 string lhs == string rhs
*/
A_EXTERN int a_str_cmp(a_str_s const *lhs, a_str_s const *rhs);

/*!
 @brief allocate memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem new memory capacity of string
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_alloc(a_str_s *ctx, a_size_t mem);
A_EXTERN int a_str_alloc_(a_str_s *ctx, a_size_t mem);

/*!
 @brief get character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return deleted character
  @retval EOF failure
*/
A_EXTERN int a_str_getc(a_str_s *ctx);
A_EXTERN int a_str_getc_(a_str_s *ctx);

/*!
 @brief put character to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character to be printed
 @return printed character
  @retval EOF failure
*/
A_EXTERN int a_str_putc(a_str_s *ctx, int c);
A_EXTERN int a_str_putc_(a_str_s *ctx, int c);

/*!
 @brief put memory block to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to memory block to put
 @param[in] nbyte length of memory block to put
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_putn(a_str_s *ctx, void const *pdata, a_size_t nbyte);
A_EXTERN int a_str_putn_(a_str_s *ctx, void const *pdata, a_size_t nbyte);

/*!
 @brief put string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_puts(a_str_s *ctx, void const *str);

/*!
 @brief concat the string structure obj to the string structure ctx
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return the execution state of the function
  @retval 0 success
  @retval 1 failure
*/
A_EXTERN int a_str_cat(a_str_s *ctx, a_str_s const *obj);

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @param[in] va instance of variable argument
 @return number of printed characters
  @retval EOF failure
*/
A_EXTERN int a_str_vprintf(a_str_s *ctx, char const *fmt, va_list va) A_FORMAT(printf, 2, 0);

/*!
 @brief print string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be printed
 @return number of printed characters
  @retval EOF failure
*/
A_EXTERN int a_str_printf(a_str_s *ctx, char const *fmt, ...) A_FORMAT(printf, 2, 3);

/*!
 @brief length for a pointer to string structure using UTF-8
 @param[in] ctx points to an instance of string structure
 @return number of code points
*/
A_EXTERN a_size_t a_str_utflen(a_str_s const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/* inline function for generic */
A_INTERN void *a_str_new_(void) { return a_str_new(); }
A_INTERN void a_str_die_(void *ctx) { a_str_die(a_cast_s(a_str_s *, ctx)); }
A_INTERN void a_str_ctor_(void *ctx) { a_str_ctor(a_cast_s(a_str_s *, ctx)); }
A_INTERN void a_str_dtor_(void *ctx) { a_str_dtor(a_cast_s(a_str_s *, ctx)); }

/*! @} A_STR */

#endif /* host/str.h */
