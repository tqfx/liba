/***
 bell-shaped velocity trajectory
 @classmod a.trajbell
*/

#ifndef LUA_LIBA_TRAJBELL_H
#define LUA_LIBA_TRAJBELL_H

#include "a.h"

/***
 bell-shaped velocity trajectory
 @field t total duration
 @field tv constant velocity phase
 @field ta acceleration phase
 @field td deceleration phase
 @field taj time-interval in which the jerk is constant (j max or j min ) during the acceleration phase
 @field tdj time-interval in which the jerk is constant (j max or j min ) during the deceleration phase
 @field q0 initial position
 @field q1 final position
 @field v0 initial velocity
 @field v1 final velocity
 @field vm maximum velocity
 @field jm maximum jerk
 @field am maximum acceleration
 @field dm maximum deceleration
 @table a.trajbell
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for bell-shaped velocity trajectory
 @treturn a.trajbell bell-shaped velocity trajectory userdata
 @function new
*/
int liba_trajbell_new(lua_State *L);

/***
 generate for bell-shaped velocity trajectory
 @tparam number jm defines the maximum jerk during system operation
 @tparam number am defines the maximum acceleration during system operation
 @tparam number vm defines the maximum velocity during system operation
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total duration
 @function gen
*/
int liba_trajbell_gen(lua_State *L);

/***
 calculate position for bell-shaped velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajbell_pos(lua_State *L);

/***
 calculate velocity for bell-shaped velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajbell_vel(lua_State *L);

/***
 calculate acceleration for bell-shaped velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajbell_acc(lua_State *L);

/***
 calculate jerk for bell-shaped velocity trajectory
 @tparam number dt difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_trajbell_jer(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* trajbell.h */
