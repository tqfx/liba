/***
 Low Pass Filter
 @classmod a.lpf
*/

#ifndef LUA_LIBA_LPF_H
#define LUA_LIBA_LPF_H

#include "a.h"

/***
 Low Pass Filter
 @field alpha filter coefficient [0,1]
 @field output filter output
 @table a.lpf
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for Low Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.lpf Low Pass Filter userdata
 @function new
*/
int liba_lpf_new(lua_State *L);

/***
 generate for Low Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.lpf Low Pass Filter userdata
 @function gen
*/
int liba_lpf_gen(lua_State *L);

/***
 compute for Low Pass Filter
 @tparam number x input value
 @treturn number output value
 @function iter
*/
int liba_lpf_iter(lua_State *L);

/***
 zeroing for Low Pass Filter
 @treturn a.lpf Low Pass Filter userdata
 @function zero
*/
int liba_lpf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* lpf.h */
