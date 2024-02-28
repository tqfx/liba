/***
 proportional integral derivative controller
 @classmod a.pid
*/

#ifndef LUA_LIBA_PID_H
#define LUA_LIBA_PID_H

#include "a.h"

/***
 proportional integral derivative controller
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field summax maximum integral output
 @field summin minimum integral output
 @field sum controller integral output
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller final output
 @field fdb cache feedback
 @field err cache error
 @table a.pid
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for PID controller
 @treturn a.pid PID controller userdata
 @function new
*/
int liba_pid_new(lua_State *L);

/***
 initialize for PID controller
 @treturn a.pid PID controller userdata
 @function init
*/
int liba_pid_init(lua_State *L);

/***
 set proportional integral derivative constant for PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid PID controller userdata
 @function kpid
*/
int liba_pid_kpid(lua_State *L);

/***
 calculate for PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_run(lua_State *L);

/***
 calculate for positional PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
int liba_pid_pos(lua_State *L);

/***
 calculate for incremental PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
int liba_pid_inc(lua_State *L);

/***
 zeroing for PID controller
 @treturn a.pid PID controller userdata
 @function zero
*/
int liba_pid_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid.h */
