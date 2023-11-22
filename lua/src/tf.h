/***
 transfer function
 @classmod a.tf
*/

/***
 transfer function
 @field num numerator table
 @field den denominator table
 @field input input table
 @field output output table
 @table a.tf
*/

#ifndef L_TF_H
#define L_TF_H

#include "a.h"
#include "a/tf.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_tf_func_(lua_State *L, int ret);
A_PUBLIC int liba_tf_meta_(lua_State *L, int ret);

/***
 destructor for transfer function
 @function die
*/
A_PUBLIC int liba_tf_die(lua_State *L);

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function new
*/
A_PUBLIC int liba_tf_new(lua_State *L);

/***
 initialize for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function init
*/
A_PUBLIC int liba_tf_init(lua_State *L);

/***
 calculate for transfer function
 @tparam number x input
 @treturn number output
 @function iter
*/
A_PUBLIC int liba_tf_iter(lua_State *L);

/***
 zeroing for transfer function
 @treturn a.tf transfer function userdata
 @function zero
*/
A_PUBLIC int liba_tf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* tf.h */
