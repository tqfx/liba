/***
 algorithm library version
 @classmod a.version
*/

#ifndef LUA_LIBA_VERSION_H
#define LUA_LIBA_VERSION_H

#include "a.h"

/***
 algorithm library version
 @field major version major number
 @field minor version minor number
 @field third version third number
 @field extra version extra number
 @field alpha version alphabet
 @table a.version
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer third version third number
 @tparam[opt] integer extra version extra number
 @treturn a.version algorithm library version userdata
 @function new
*/
int liba_version_new(lua_State *L);

/***
 initialize for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer third version third number
 @tparam[opt] integer extra version extra number
 @treturn a.version algorithm library version userdata
 @function init
*/
int liba_version_init(lua_State *L);

/***
 parse version string to version
 @tparam string version string to be parsed
 @treturn a.version algorithm library version userdata
 @function parse
*/
int liba_version_parse(lua_State *L);

/***
 compare the version self with the version that
 @tparam a.version that version userdata
 @treturn integer <0 version self < version that
 @treturn integer >0 version self > version that
 @treturn integer 0 version self == version that
 @function cmp
*/
int liba_version_cmp(lua_State *L);

/***
 version self is less than version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function lt
*/
int liba_version_lt(lua_State *L);

/***
 version self is greater than version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function gt
*/
int liba_version_gt(lua_State *L);

/***
 version self is less than or equal to version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function le
*/
int liba_version_le(lua_State *L);

/***
 version self is greater than or equal to version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function ge
*/
int liba_version_ge(lua_State *L);

/***
 version self is equal to version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function eq
*/
int liba_version_eq(lua_State *L);

/***
 version self is not equal to version that
 @tparam a.version that version userdata
 @treturn bool result of comparison
 @function ne
*/
int liba_version_ne(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* version.h */
