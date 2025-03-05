/***
 quintic polynomial trajectory
 @classmod a.trajpoly5
*/

#ifndef LUA_LIBA_TRAJPOLY5_H
#define LUA_LIBA_TRAJPOLY5_H

#include "a.h"

/***
 quintic polynomial trajectory
 @field c0 coefficients of position
 @field c1 coefficients of velocity
 @field c2 coefficients of acceleration
 @table a.trajpoly5
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.trajpoly5 quintic polynomial trajectory userdata
 @function new
*/
int liba_trajpoly5_new(lua_State *L);

/***
 generate for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.trajpoly5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly5_gen(lua_State *L);

/***
 calculate position for quintic polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly5_pos(lua_State *L);

/***
 calculate velocity for quintic polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly5_vel(lua_State *L);

/***
 calculate acceleration for quintic polynomial trajectory
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly5_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* trajpoly5.h */
