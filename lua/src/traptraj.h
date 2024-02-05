/***
 trapezoidal velocity profile trajectory
 @classmod a.traptraj
*/

#ifndef LUA_LIBA_POLYTRAJ3_H
#define LUA_LIBA_POLYTRAJ3_H

#include "a.h"

/***
 trapezoidal velocity profile trajectory
 @field ac acceleration before constant velocity
 @field de acceleration after constant velocity
 @field q1 position before constant velocity
 @field q2 position after constant velocity
 @field t1 time before constant velocity
 @field t2 time after constant velocity
 @field vs initial velocity
 @field vc constant velocity
 @field ve final velocity
 @field q final position
 @field t total time
 @table a.traptraj
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for trapezoidal velocity profile trajectory
 @tparam number qm defines the distance from the start point to the end point
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam[opt] number vs defines the starting velocity
 @tparam[opt] number ve defines the ending velocity
 @treturn a.traptraj trapezoidal velocity profile trajectory userdata
 @function new
*/
int liba_traptraj_new(lua_State *L);

/***
 generate for trapezoidal velocity profile trajectory
 @tparam number qm defines the distance from the start point to the end point
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam[opt] number vs defines the starting velocity
 @tparam[opt] number ve defines the ending velocity
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
