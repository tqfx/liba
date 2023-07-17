/*!
 @file oop.h
 @brief Object Oriented Programming Macros
*/

#ifndef LIBA_OOP_H
#define LIBA_OOP_H

#include "a.h"

#include <stdlib.h>

/*!
 @ingroup A
 @addtogroup A_OOP Object Oriented Programming
 @{
*/

/*!
 @brief Generates a parameterless function that creates an object
 @param type object definition
 @param func function symbol
 @param ctor constructor
*/
#define A_OOP_NEW(type, func, ctor)               \
    type *func(void)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx);                            \
        }                                         \
        return ctx;                               \
    }

/*!
 @brief Generates a parameterized function that creates an object
 @code{.c}
 #undef ARGS
 #define ARGS double x, double y
 A_OOP_NEW_VA(a_rect_s, a_rect_new, a_rect_ctor, ARGS, x, y)
 @endcode
 @param type object definition
 @param func function symbol
 @param ctor constructor
 @param args macro for declaring parameters
 @param ... declared parameter variable name
*/
#define A_OOP_NEW_VA(type, func, ctor, args, ...) \
    type *func(args)                              \
    {                                             \
        type *ctx = (type *)malloc(sizeof(type)); \
        if (ctx)                                  \
        {                                         \
            ctor(ctx, __VA_ARGS__);               \
        }                                         \
        return ctx;                               \
    }

/*!
 @brief Generates a parameterless function that destroys an object
 @param type object definition
 @param func function symbol
 @param dtor destructor
*/
#define A_OOP_DIE(type, func, dtor) \
    void func(type *ctx)            \
    {                               \
        if (ctx)                    \
        {                           \
            dtor(ctx);              \
            free(ctx);              \
        }                           \
    }

/*!
 @brief Generates a parameterized function that destroys an object
 @code{.c}
 #undef ARGS
 #define ARGS void (*func)(void *)
 A_OOP_DIE_VA(a_vec_s, a_vec_die, a_vec_dtor, ARGS, func)
 @endcode
 @param type object definition
 @param func function symbol
 @param dtor destructor
 @param args macro for declaring parameters
 @param ... declared parameter variable name
*/
#define A_OOP_DIE_VA(type, func, dtor, args, ...) \
    void func(type *ctx, args)                    \
    {                                             \
        if (ctx)                                  \
        {                                         \
            dtor(ctx, __VA_ARGS__);               \
            free(ctx);                            \
        }                                         \
    }

#define A_OOP_CREATE A_OOP_NEW
#define A_OOP_DELETE A_OOP_DIE
#define A_OOP_CREATE_VA A_OOP_NEW_VA
#define A_OOP_DELETE_VA A_OOP_DIE_VA

/*! @} A_OOP */

#endif /* a/oop.h */
