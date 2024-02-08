/***
 trapezoidal velocity trajectory
 @classmod a.trajtrap
*/

#ifndef LUA_LIBA_TRAJTRAP_H
#define LUA_LIBA_TRAJTRAP_H

#include "a.h"

/***
 trapezoidal velocity trajectory
 @field t total duration
 @field q0 initial position
 @field q1 final position
 @field v0 initial velocity
 @field v1 final velocity
 @field vc constant velocity
 @field ta time before constant velocity
 @field td time after constant velocity
 @field qa position before constant velocity
 @field qd position after constant velocity
 @field ac acceleration before constant velocity
 @field de acceleration after constant velocity
 @table a.trajtrap
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for trapezoidal velocity trajectory
 @treturn a.trajtrap trapezoidal velocity trajectory userdata
 @function new
*/
int liba_trajtrap_new(lua_State *L);

/***
 generate for trapezoidal velocity trajectory
 @tparam number vm defines the maximum velocity during system operation
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total duration
 @function gen
*/
int liba_trajtrap_gen(lua_State *L);

/***
 calculate position for trapezoidal velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajtrap_pos(lua_State *L);

/***
 calculate velocity for trapezoidal velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajtrap_vel(lua_State *L);

/***
 calculate acceleration for trapezoidal velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajtrap_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* trajtrap.h */
