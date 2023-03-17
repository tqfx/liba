/***
 algorithm library version
 @classmod version
*/

/***
 algorithm library version
 @field major version major number
 @field minor version minor number
 @field patch version patch number
 @table version
*/

#ifndef L_VERSION_H
#define L_VERSION_H

#include "a.h"
#include "a/version.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(version_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(version_meta_)(lua_State *L, int ret);

/***
 constructor for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn algorithm library version userdata
 @function new
*/
A_PUBLIC int LMODULE(version_new)(lua_State *L);

/***
 initialize function for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn algorithm library version userdata
 @function init
*/
A_PUBLIC int LMODULE(version_init)(lua_State *L);

/***
 compare the version lhs with the version rhs
 @tparam lhs version structure to be compared
 @tparam rhs version structure to be compared
 @treturn integer `<0` version lhs < version rhs
 @treturn integer `>0` version lhs > version rhs
 @treturn integer 0 version lhs == version rhs
 @function cmp
*/
A_PUBLIC int LMODULE(version_cmp)(lua_State *L);

/***
 version lhs less than version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function lt
*/
A_PUBLIC int LMODULE(version_lt)(lua_State *L);

/***
 version lhs greater than version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function gt
*/
A_PUBLIC int LMODULE(version_gt)(lua_State *L);

/***
 version lhs less than or equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function le
*/
A_PUBLIC int LMODULE(version_le)(lua_State *L);

/***
 version lhs greater than or equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function ge
*/
A_PUBLIC int LMODULE(version_ge)(lua_State *L);

/***
 version lhs equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function eq
*/
A_PUBLIC int LMODULE(version_eq)(lua_State *L);

/***
 version lhs not equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function ne
*/
A_PUBLIC int LMODULE(version_ne)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* version.h */
