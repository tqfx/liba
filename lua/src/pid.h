/***
 proportional integral derivative controller
 @classmod pid
*/

/***
 proportional integral derivative controller
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field summax maximum integral output
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller output
 @field fdb cache feedback
 @field err cache error
 @field mode controller mode
 @table pid
*/

#ifndef L_PID_H
#define L_PID_H

#include "a.h"
#include "a/pid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(pid_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(pid_meta_)(lua_State *L, int ret);

/***
 constructor for PID controller
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function new
*/
A_PUBLIC int LMODULE(pid_new)(lua_State *L);

/***
 initialize function for PID controller
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function init
*/
A_PUBLIC int LMODULE(pid_init)(lua_State *L);

/***
 set proportional integral derivative constant for PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn pid PID controller userdata
 @function kpid
*/
A_PUBLIC int LMODULE(pid_kpid)(lua_State *L);

/***
 calculate function for PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
A_PUBLIC int LMODULE(pid_iter)(lua_State *L);

/***
 zero clear function for PID controller
 @treturn pid PID controller userdata
 @function zero
*/
A_PUBLIC int LMODULE(pid_zero)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
