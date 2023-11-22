/***
 proportional integral derivative controller
 @classmod a.pid
*/

/***
 proportional integral derivative controller
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field summax maximum integral output
 @field summin minimum integral output
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller output
 @field fdb cache feedback
 @field err cache error
 @table a.pid
*/

#ifndef L_PID_H
#define L_PID_H

#include "a.h"
#include "a/pid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_pid_func_(lua_State *L, int ret);
A_PUBLIC int liba_pid_meta_(lua_State *L, int ret);

/***
 constructor for PID controller
 @treturn a.pid PID controller userdata
 @function new
*/
A_PUBLIC int liba_pid_new(lua_State *L);

/***
 initialize for PID controller
 @treturn a.pid PID controller userdata
 @function init
*/
A_PUBLIC int liba_pid_init(lua_State *L);

/***
 zeroing for PID controller
 @treturn a.pid PID controller userdata
 @function zero
*/
A_PUBLIC int liba_pid_zero(lua_State *L);

/***
 set proportional integral derivative constant for PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid PID controller userdata
 @function kpid
*/
A_PUBLIC int liba_pid_kpid(lua_State *L);

/***
 calculate for PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function off
*/
A_PUBLIC int liba_pid_off(lua_State *L);

/***
 calculate for positional PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
A_PUBLIC int liba_pid_pos(lua_State *L);

/***
 calculate for incremental PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
A_PUBLIC int liba_pid_inc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
