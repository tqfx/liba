/***
 cubic polynomial trajectory
 @classmod a.polytrack3
*/

/***
 cubic polynomial trajectory
 @field k coefficient table, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3
 @table a.polytrack3
*/

#ifndef L_POLYTRACK3_H
#define L_POLYTRACK3_H

#include "a.h"
#include "a/polytrack.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_polytrack3_func_(lua_State *L, int ret);
A_PUBLIC int liba_polytrack3_meta_(lua_State *L, int ret);

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
 @treturn a.polytrack3 cubic polynomial trajectory userdata
 @function new
*/
A_PUBLIC int liba_polytrack3_new(lua_State *L);

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
 @treturn a.polytrack3 cubic polynomial trajectory userdata
 @function gen
*/
A_PUBLIC int liba_polytrack3_gen(lua_State *L);

/***
 calculate for cubic polynomial trajectory
 @tparam number dt difference between current time and initial time
 @treturn table {position,velocity,acceleration}
 @function out
*/
A_PUBLIC int liba_polytrack3_out(lua_State *L);

/***
 calculate for cubic polynomial trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
A_PUBLIC int liba_polytrack3_pos(lua_State *L);

/***
 calculate for cubic polynomial trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
A_PUBLIC int liba_polytrack3_vel(lua_State *L);

/***
 calculate for cubic polynomial trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
A_PUBLIC int liba_polytrack3_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack3.h */
