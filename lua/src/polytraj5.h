/***
 quintic polynomial trajectory
 @classmod a.polytraj5
*/

#ifndef LUA_LIBA_POLYTRAJ5_H
#define LUA_LIBA_POLYTRAJ5_H

#include "a.h"

/***
 quintic polynomial trajectory
 @field q coefficients of position
 @field v coefficients of velocity
 @field a coefficients of acceleration
 @table a.polytraj5
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function new
*/
int liba_polytraj5_new(lua_State *L);

/***
 generate for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_polytraj5_gen(lua_State *L);

/***
 calculate for quintic polynomial trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj5_pos(lua_State *L);

/***
 calculate for quintic polynomial trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj5_vel(lua_State *L);

/***
 calculate for quintic polynomial trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj5_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytraj5.h */
