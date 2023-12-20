/***
 cubic polynomial trajectory
 @classmod a.polytraj3
*/

#ifndef LUA_LIBA_POLYTRAJ3_H
#define LUA_LIBA_POLYTRAJ3_H

#include "a.h"

/***
 cubic polynomial trajectory
 @field q coefficients of position
 @field v coefficients of velocity
 @field a coefficients of acceleration
 @table a.polytraj3
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int liba_polytraj3_func_(lua_State *L, int op);
int liba_polytraj3_meta_(lua_State *L, int op);

/***
 constructor for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj3 cubic polynomial trajectory userdata
 @function new
*/
int liba_polytraj3_new(lua_State *L);

/***
 generate for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj3 cubic polynomial trajectory userdata
 @function gen
*/
int liba_polytraj3_gen(lua_State *L);

/***
 calculate for cubic polynomial trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj3_pos(lua_State *L);

/***
 calculate for cubic polynomial trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj3_vel(lua_State *L);

/***
 calculate for cubic polynomial trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj3_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytraj3.h */
