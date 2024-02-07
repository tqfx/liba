/***
 cubic polynomial trajectory
 @classmod a.trajpoly3
*/

#ifndef LUA_LIBA_TRAJPOLY3_H
#define LUA_LIBA_TRAJPOLY3_H

#include "a.h"

/***
 cubic polynomial trajectory
 @field q coefficients of position
 @field v coefficients of velocity
 @field a coefficients of acceleration
 @table a.trajpoly3
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
 @treturn a.trajpoly3 cubic polynomial trajectory userdata
 @function new
*/
int liba_trajpoly3_new(lua_State *L);

/***
 generate for cubic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @treturn a.trajpoly3 cubic polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly3_gen(lua_State *L);

/***
 calculate position for cubic polynomial trajectory
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly3_pos(lua_State *L);

/***
 calculate velocity for cubic polynomial trajectory
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly3_vel(lua_State *L);

/***
 calculate acceleration for cubic polynomial trajectory
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly3_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* trajpoly3.h */
