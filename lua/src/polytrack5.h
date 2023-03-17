/***
 quintic polynomial trajectory
 @classmod polytrack5
*/

/***
 quintic polynomial trajectory
 @field k quantity table
 @field t time table
 @field p position table
 @field v velocity table
 @field a acceleration table
 @field t0 time for source
 @field t1 time for target
 @field q0 position for source
 @field q1 position for target
 @field v0 velocity for source
 @field v1 velocity for target
 @field a0 acceleration for source
 @field a1 acceleration for target
 @table polytrack5
*/

#ifndef L_POLYTRACK5_H
#define L_POLYTRACK5_H

#include "a.h"
#include "a/polytrack.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(polytrack5_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(polytrack5_meta_)(lua_State *L, int ret);

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
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function new
*/
A_PUBLIC int LMODULE(polytrack5_new)(lua_State *L);

/***
 initialize function for quintic polynomial trajectory
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
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function init
*/
A_PUBLIC int LMODULE(polytrack5_init)(lua_State *L);

/***
 generation function for quintic polynomial trajectory
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function gen
*/
A_PUBLIC int LMODULE(polytrack5_gen)(lua_State *L);

/***
 process function for quintic polynomial trajectory
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration}
 @function out
*/
A_PUBLIC int LMODULE(polytrack5_out)(lua_State *L);

/***
 process function for quintic polynomial trajectory position
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
A_PUBLIC int LMODULE(polytrack5_pos)(lua_State *L);

/***
 process function for quintic polynomial trajectory velocity
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
A_PUBLIC int LMODULE(polytrack5_vec)(lua_State *L);

/***
 process function for quintic polynomial trajectory acceleration
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
A_PUBLIC int LMODULE(polytrack5_acc)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack5.h */
