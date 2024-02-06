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

/***
 constructor for cubic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @treturn a.polytraj3 cubic polynomial trajectory userdata
 @function new
*/
int liba_polytraj3_new(lua_State *L);

/***
 generate for cubic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
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
