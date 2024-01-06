/***
 High Pass Filter
 @classmod a.hpf
*/

#ifndef LUA_LIBA_HPF_H
#define LUA_LIBA_HPF_H

#include "a.h"

/***
 High Pass Filter
 @field alpha filter coefficient [0,1]
 @field output filter output
 @field input filter input
 @table a.hpf
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for High Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.hpf High Pass Filter userdata
 @function new
*/
int liba_hpf_new(lua_State *L);

/***
 generate for High Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.hpf High Pass Filter userdata
 @function gen
*/
int liba_hpf_gen(lua_State *L);

/***
 calculate for High Pass Filter
 @tparam number x input value
 @treturn number output value
 @function iter
*/
int liba_hpf_iter(lua_State *L);

/***
 zeroing for High Pass Filter
 @treturn a.hpf High Pass Filter userdata
 @function zero
*/
int liba_hpf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* hpf.h */
