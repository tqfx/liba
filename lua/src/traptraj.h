/***
 trapezoidal velocity profile trajectory
 @classmod a.traptraj
*/

#ifndef LUA_LIBA_POLYTRAJ3_H
#define LUA_LIBA_POLYTRAJ3_H

#include "a.h"

/***
 trapezoidal velocity profile trajectory
 @field t total time
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
 @table a.traptraj
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for trapezoidal velocity profile trajectory
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn a.traptraj trapezoidal velocity profile trajectory userdata
 @function new
*/
int liba_traptraj_new(lua_State *L);

/***
 generate for trapezoidal velocity profile trajectory
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total time
 @function gen
*/
int liba_traptraj_gen(lua_State *L);

/***
 calculate for trapezoidal velocity profile trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_traptraj_pos(lua_State *L);

/***
 calculate for trapezoidal velocity profile trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_traptraj_vel(lua_State *L);

/***
 calculate for trapezoidal velocity profile trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_traptraj_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* traptraj.h */
