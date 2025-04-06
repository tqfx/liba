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
 @ingroup liba
 @addtogroup a_str basic string library
 @{
*/

/* clang-format off */
#define A_STR_INIT {A_NULL, 0, 0}
/* clang-format on */

/*!
 @brief instance structure for basic string
*/
typedef struct a_str
{
    char *ptr_; /*!< string */
    a_size num_; /*!< length */
    a_size mem_; /*!< memory */
} a_str;

/*!
 @brief string for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return string
*/
A_INTERN char *a_str_ptr(a_str const *ctx) { return ctx->ptr_; }

/*!
 @brief length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of length
*/
A_INTERN a_size a_str_len(a_str const *ctx) { return ctx->num_; }

/*!
 @brief memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return size of memory
*/
A_INTERN a_size a_str_mem(a_str const *ctx) { return ctx->mem_; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than memory
 @note should check for out of bounds
 @return specified character pointer
*/
A_INTERN char *a_str_at_(a_str const *ctx, a_size idx) { return ctx->ptr_ + idx; }

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character less than memory
 @return specified character pointer
  @retval 0 out of bounds
*/
A_INTERN char *a_str_at(a_str const *ctx, a_size idx)
{
    return idx < ctx->mem_ ? ctx->ptr_ + idx : A_NULL;
}

/*!
 @brief access specified character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] idx index of character -length < idx < length
 @return specified character pointer
  @retval 0 out of bounds
*/
A_INTERN char *a_str_of(a_str const *ctx, a_diff idx)
{
    a_size const num = idx >= 0 ? a_size_c(idx) : a_size_c(idx) + ctx->num_;
    return num < ctx->mem_ ? ctx->ptr_ + num : A_NULL;
}

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] num new length for a pointer to string structure
 @note length must less than memory
*/
A_INTERN void a_str_setn_(a_str *ctx, a_size num) { ctx->num_ = num; }

/*!
 @brief set length for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] num new length for a pointer to string structure
 @return error code value
  @retval 0 success
*/
A_INTERN int a_str_setn(a_str *ctx, a_size num)
{
    int const rc = (num <= ctx->mem_ ? A_SUCCESS : A_OBOUNDS);
    if (rc == 0) { ctx->num_ = num; }
    return rc;
}

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
 @brief swap the contents of two pointers to string structure
 @param[in] lhs points to an instance of string structure
 @param[in] rhs points to an instance of string structure
*/
A_EXTERN void a_str_swap(a_str *lhs, a_str *rhs);

/*!
 @brief terminate a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @note should use free to release this memory
 @return string of string structure
*/
A_EXTERN char *a_str_exit(a_str *ctx);

/*!
 @brief allocate memory for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] mem new memory capacity of string
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_str_setm(a_str *ctx, a_size mem);
A_EXTERN int a_str_setm_(a_str *ctx, a_size mem);

/*!
 @brief compare the memory block 0 with the memory block 1
 @param[in] p0 points to memory block 0 to be compared
 @param[in] n0 length of memory block 0 to be compared
 @param[in] p1 points to memory block 1 to be compared
 @param[in] n1 length of memory block 1 to be compared
 @return relationship between the memory blocks
  @retval <0 memory block 0 < memory block 1
  @retval >0 memory block 0 > memory block 1
  @retval 0 memory block 0 == memory block 1
*/
A_EXTERN int a_str_cmp_(void const *p0, a_size n0, void const *p1, a_size n1);

/*!
 @brief compare the string `lhs` with the string `rhs`
 @param[in] lhs string structure to be compared
 @param[in] rhs string structure to be compared
 @return relationship between the strings
  @retval <0 string `lhs` < string `rhs`
  @retval >0 string `lhs` > string `rhs`
  @retval 0 string `lhs` == string `rhs`
*/
A_EXTERN int a_str_cmp(a_str const *lhs, a_str const *rhs);

/*!
 @brief compare the string `ctx` with the memory block
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to memory block to be compared
 @param[in] nbyte length of memory block to be compared
 @return relationship between the strings
  @retval <0 string `ctx` < memory block
  @retval >0 string `ctx` > memory block
  @retval 0 string `ctx` == memory block
*/
A_EXTERN int a_str_cmpn(a_str const *ctx, void const *pdata, a_size nbyte);

/*!
 @brief compare the string `ctx` with the C string `str`
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return relationship between the strings
  @retval <0 string `ctx` < C string `str`
  @retval >0 string `ctx` > C string `str`
  @retval 0 string `ctx` == C string `str`
*/
A_EXTERN int a_str_cmps(a_str const *ctx, void const *str);

/*!
 @brief get character for a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @return parsed character
  @retval ~0 failure
*/
A_EXTERN int a_str_getc(a_str *ctx);
A_EXTERN int a_str_getc_(a_str *ctx);

/*!
 @brief concatenate character to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] c character to be parsed
 @return parsed character
  @retval ~0 failure
*/
A_EXTERN int a_str_catc(a_str *ctx, int c);
A_EXTERN int a_str_catc_(a_str *ctx, int c);

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
 @brief concatenate memory block to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] pdata points to memory block to put
 @param[in] nbyte length of memory block to put
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_str_catn(a_str *ctx, void const *pdata, a_size nbyte);
A_EXTERN int a_str_catn_(a_str *ctx, void const *pdata, a_size nbyte);

/*!
 @brief concatenate C string to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] str string terminated with a null character
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_str_cats(a_str *ctx, void const *str);
A_EXTERN int a_str_cats_(a_str *ctx, void const *str);

/*!
 @brief format string append to a pointer to string structure via va_list
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be parsed
 @param[in] va instance of variable argument
 @return number of parsed characters
*/
A_EXTERN A_FORMAT(__printf__, 2, 0) int a_str_catv(a_str *ctx, char const *fmt, va_list va);

/*!
 @brief format string append to a pointer to string structure
 @param[in] ctx points to an instance of string structure
 @param[in] fmt format of string to be parsed
 @return number of parsed characters
*/
A_EXTERN A_FORMAT(__printf__, 2, 3) int a_str_catf(a_str *ctx, char const *fmt, ...);

/*!
 @brief concatenate the string structure obj to the string structure ctx
 @param[in] ctx points to an instance of string structure
 @param[in] obj input source pointing to an instance
 @return error code value
  @retval 0 success
*/
A_EXTERN int a_str_cat(a_str *ctx, a_str const *obj);
A_EXTERN int a_str_cat_(a_str *ctx, a_str const *obj);

/*!
 @brief length for a pointer to string structure using UTF-8
 @param[in] ctx points to an instance of string structure
 @return number of code points
*/
A_EXTERN a_size a_str_utflen(a_str const *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} a_str */

#endif /* a/str.h */
