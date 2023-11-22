/***
 single neuron proportional integral derivative controller
 @classmod a.pid.neuron
*/

/***
 single neuron proportional integral derivative controller
 @field k proportional output coefficient
 @field kp proportional learning constant
 @field ki integral learning constant
 @field kd derivative learning constant
 @field wp proportional weight
 @field wi integral weight
 @field wd derivative weight
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller output
 @field fdb cache feedback
 @field err cache error
 @field ec error change
 @table a.pid.neuron
*/

#ifndef L_PID_NEURON_H
#define L_PID_NEURON_H

#include "../pid.h"
#include "a/pid/neuron.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_pid_neuron_func_(lua_State *L, int ret);
A_PUBLIC int liba_pid_neuron_meta_(lua_State *L, int ret);

/***
 constructor for single neuron PID controller
 @treturn a.pid.neuron single neuron PID controller userdata
 @function new
*/
A_PUBLIC int liba_pid_neuron_new(lua_State *L);

/***
 initialize for single neuron PID controller
 @treturn a.pid.neuron single neuron PID controller userdata
 @function init
*/
A_PUBLIC int liba_pid_neuron_init(lua_State *L);

/***
 zeroing for single neuron PID controller
 @treturn a.pid.neuron single neuron PID controller userdata
 @function zero
*/
A_PUBLIC int liba_pid_neuron_zero(lua_State *L);

/***
 set proportional integral derivative constant for single neuron PID controller
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn a.pid.neuron single neuron PID controller userdata
 @function kpid
*/
A_PUBLIC int liba_pid_neuron_kpid(lua_State *L);

/***
 set proportional integral derivative weight for single neuron PID controller
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn a.pid.neuron single neuron PID controller userdata
 @function wpid
*/
A_PUBLIC int liba_pid_neuron_wpid(lua_State *L);

/***
 calculate for single neuron PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function off
*/
A_PUBLIC int liba_pid_neuron_off(lua_State *L);

/***
 calculate for incremental single neuron PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
A_PUBLIC int liba_pid_neuron_inc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/neuron.h */
