/***
 hepta polynomial trajectory
 @classmod a.trajpoly7
*/

#ifndef LUA_LIBA_TRAJPOLY7_H
#define LUA_LIBA_TRAJPOLY7_H

#include "a.h"

/***
 hepta polynomial trajectory
 @field p coefficients of position
 @field v coefficients of velocity
 @field a coefficients of acceleration
 @field j coefficients of jerk
 @table a.trajpoly7
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for hepta polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @tparam[opt] number j0 initial jerk
 @tparam[opt] number j1 final jerk
 @treturn a.trajpoly7 hepta polynomial trajectory userdata
 @function new
*/
int liba_trajpoly7_new(lua_State *L);

/***
 generate for hepta polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @tparam[opt] number j0 initial jerk
 @tparam[opt] number j1 final jerk
 @treturn a.trajpoly7 hepta polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly7_gen(lua_State *L);

/***
 calculate position for hepta polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly7_pos(lua_State *L);

/***
 calculate velocity for hepta polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly7_vel(lua_State *L);

/***
 calculate acceleration for hepta polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly7_acc(lua_State *L);

/***
 calculate jerk for hepta polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_trajpoly7_jer(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* trajpoly7.h */
