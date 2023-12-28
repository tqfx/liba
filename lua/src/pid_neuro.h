/***
 single neuron proportional integral derivative controller
 @classmod a.pid_neuro
*/

#ifndef LUA_LIBA_PID_NEURON_H
#define LUA_LIBA_PID_NEURON_H

#include "a.h"

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
 @table a.pid_neuro
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for single neuron PID controller
 @treturn a.pid_neuro single neuron PID controller userdata
 @function new
*/
int liba_pid_neuro_new(lua_State *L);

/***
 initialize for single neuron PID controller
 @treturn a.pid_neuro single neuron PID controller userdata
 @function init
*/
int liba_pid_neuro_init(lua_State *L);

/***
 zeroing for single neuron PID controller
 @treturn a.pid_neuro single neuron PID controller userdata
 @function zero
*/
int liba_pid_neuro_zero(lua_State *L);

/***
 set proportional integral derivative constant for single neuron PID controller
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn a.pid_neuro single neuron PID controller userdata
 @function kpid
*/
int liba_pid_neuro_kpid(lua_State *L);

/***
 set proportional integral derivative weight for single neuron PID controller
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn a.pid_neuro single neuron PID controller userdata
 @function wpid
*/
int liba_pid_neuro_wpid(lua_State *L);

/***
 calculate for single neuron PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_neuro_run(lua_State *L);

/***
 calculate for incremental single neuron PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
int liba_pid_neuro_inc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/neuron.h */
