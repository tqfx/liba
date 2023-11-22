/***
 quintic polynomial trajectory
 @classmod a.polytrack5
*/

/***
 quintic polynomial trajectory
 @field k coefficient table, q(t)=k_0+k_1(t-t_0)+k_2(t-t_0)^2+k_3(t-t_0)^3+k_4(t-t_0)^4+k_5(t-t_0)^5
 @table a.polytrack5
*/

#ifndef L_POLYTRACK5_H
#define L_POLYTRACK5_H

#include "a.h"
#include "a/polytrack.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_polytrack5_func_(lua_State *L, int ret);
A_PUBLIC int liba_polytrack5_meta_(lua_State *L, int ret);

/***
 constructor for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytrack5 quintic polynomial trajectory userdata
 @function new
*/
A_PUBLIC int liba_polytrack5_new(lua_State *L);

/***
 generate for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytrack5 quintic polynomial trajectory userdata
 @function gen
*/
A_PUBLIC int liba_polytrack5_gen(lua_State *L);

/***
 calculate for quintic polynomial trajectory
 @tparam number dt difference between current time and initial time
 @treturn table {position,velocity,acceleration}
 @function out
*/
A_PUBLIC int liba_polytrack5_out(lua_State *L);

/***
 calculate for quintic polynomial trajectory position
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
A_PUBLIC int liba_polytrack5_pos(lua_State *L);

/***
 calculate for quintic polynomial trajectory velocity
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
A_PUBLIC int liba_polytrack5_vel(lua_State *L);

/***
 calculate for quintic polynomial trajectory acceleration
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
A_PUBLIC int liba_polytrack5_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack5.h */
