/***
 transfer function
 @classmod a.tf
*/

#ifndef LUA_LIBA_TF_H
#define LUA_LIBA_TF_H

#include "a.h"

/***
 transfer function
 @field num numerator table
 @field den denominator table
 @field input input table
 @field output output table
 @table a.tf
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int liba_tf_func_(lua_State *L, int ret);
int liba_tf_meta_(lua_State *L, int ret);

/***
 destructor for transfer function
 @function die
*/
int liba_tf_die(lua_State *L);

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function new
*/
int liba_tf_new(lua_State *L);

/***
 initialize for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function init
*/
int liba_tf_init(lua_State *L);

/***
 calculate for transfer function
 @tparam number x input
 @treturn number output
 @function iter
*/
int liba_tf_iter(lua_State *L);

/***
 zeroing for transfer function
 @treturn a.tf transfer function userdata
 @function zero
*/
int liba_tf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* tf.h */
