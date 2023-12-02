/***
 hepta polynomial trajectory
 @classmod a.polytraj7
*/

#ifndef LUA_LIBA_POLYTRAJ7_H
#define LUA_LIBA_POLYTRAJ7_H

#include "a.h"

/***
 hepta polynomial trajectory
 @field q coefficients of position
 @field v coefficients of velocity
 @field a coefficients of acceleration
 @field j coefficients of jerk
 @table a.polytraj7
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int liba_polytraj7_func_(lua_State *L, int ret);
int liba_polytraj7_meta_(lua_State *L, int ret);

/***
 constructor for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj7 hepta polynomial trajectory userdata
 @function new
*/
int liba_polytraj7_new(lua_State *L);

/***
 generate for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj7 hepta polynomial trajectory userdata
 @function gen
*/
int liba_polytraj7_gen(lua_State *L);

/***
 calculate for hepta polynomial trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj7_pos(lua_State *L);

/***
 calculate for hepta polynomial trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj7_vel(lua_State *L);

/***
 calculate for hepta polynomial trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj7_acc(lua_State *L);

/***
 calculate for hepta polynomial trajectory jerk
 @tparam number dt difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_polytraj7_jer(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytraj7.h */
