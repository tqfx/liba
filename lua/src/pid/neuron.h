/***
 single neuron proportional integral derivative controller
 @classmod liba.pid.neuron
*/

/***
 single neuron proportional integral derivative controller
 @field kp proportional learning constant
 @field ki integral learning constant
 @field kd derivative learning constant
 @field summax maximum integral output
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller output
 @field fdb cache feedback
 @field err cache error
 @field mode controller mode
 @field ec error change
 @field wp proportional weight
 @field wi integral weight
 @field wd derivative weight
 @field k proportional output coefficient
 @table liba.pid.neuron
*/

#ifndef L_PID_NEURON_H
#define L_PID_NEURON_H

#include "../pid.h"
#include "a/pid/neuron.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(pid_neuron_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(pid_neuron_meta_)(lua_State *L, int ret);

/***
 constructor for single neuron PID controller
 @tparam[opt] number kp proportional learning constant
 @tparam[opt] number ki integral learning constant
 @tparam[opt] number kd derivative learning constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid_neuron single neuron PID controller userdata
 @function new
*/
A_PUBLIC int LMODULE(pid_neuron_new)(lua_State *L);

/***
 initialize function for single neuron PID controller
 @tparam[opt] number kp proportional learning constant
 @tparam[opt] number ki integral learning constant
 @tparam[opt] number kd derivative learning constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid_neuron single neuron PID controller userdata
 @function init
*/
A_PUBLIC int LMODULE(pid_neuron_init)(lua_State *L);

/***
 set proportional integral derivative constant for single neuron PID controller
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn pid_neuron single neuron PID controller userdata
 @function kpid
*/
A_PUBLIC int LMODULE(pid_neuron_kpid)(lua_State *L);

/***
 set proportional integral derivative weight for single neuron PID controller
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn pid_neuron single neuron PID controller userdata
 @function wpid
*/
A_PUBLIC int LMODULE(pid_neuron_wpid)(lua_State *L);

/***
 calculate function for single neuron PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
A_PUBLIC int LMODULE(pid_neuron_iter)(lua_State *L);

/***
 zero clear function for single neuron PID controller
 @treturn pid_neuron single neuron PID controller userdata
 @function zero
*/
A_PUBLIC int LMODULE(pid_neuron_zero)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/neuron.h */
