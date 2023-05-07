/***
 hepta polynomial trajectory
 @classmod polytrack7
*/

/***
 hepta polynomial trajectory
 @field k quantity table
 @field t time table
 @field p position table
 @field v velocity table
 @field a acceleration table
 @field j jerk table
 @field t0 time for source
 @field t1 time for target
 @field q0 position for source
 @field q1 position for target
 @field v0 velocity for source
 @field v1 velocity for target
 @field a0 acceleration for source
 @field a1 acceleration for target
 @field j0 jerk for source
 @field j1 jerk for target
 @table polytrack7
*/

#ifndef L_POLYTRACK7_H
#define L_POLYTRACK7_H

#include "a.h"
#include "a/polytrack.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(polytrack7_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(polytrack7_meta_)(lua_State *L, int ret);

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
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function new
*/
A_PUBLIC int LMODULE(polytrack7_new)(lua_State *L);

/***
 initialize function for hepta polynomial trajectory
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
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function init
*/
A_PUBLIC int LMODULE(polytrack7_init)(lua_State *L);

/***
 generation function for hepta polynomial trajectory
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function gen
*/
A_PUBLIC int LMODULE(polytrack7_gen)(lua_State *L);

/***
 calculate function for hepta polynomial trajectory
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration,jerk}
 @function out
*/
A_PUBLIC int LMODULE(polytrack7_out)(lua_State *L);

/***
 calculate function for hepta polynomial trajectory position
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
A_PUBLIC int LMODULE(polytrack7_pos)(lua_State *L);

/***
 calculate function for hepta polynomial trajectory velocity
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
A_PUBLIC int LMODULE(polytrack7_vec)(lua_State *L);

/***
 calculate function for hepta polynomial trajectory acceleration
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
A_PUBLIC int LMODULE(polytrack7_acc)(lua_State *L);

/***
 calculate function for hepta polynomial trajectory jerk
 @tparam number ts current time unit(s)
 @treturn number jerk output
 @function jer
*/
A_PUBLIC int LMODULE(polytrack7_jer)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* polytrack7.h */
