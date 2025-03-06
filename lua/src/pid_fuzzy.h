/***
 fuzzy proportional integral derivative controller
 @classmod a.pid_fuzzy
*/

#ifndef LUA_LIBA_PID_FUZZY_H
#define LUA_LIBA_PID_FUZZY_H

#include "a.h"

/***
 fuzzy proportional integral derivative controller
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
 @field nrule number of order in the square matrix
 @field nfuzz maximum number triggered by the rule
 @table a.pid_fuzzy
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 destructor for fuzzy PID controller
 @function die
*/
int liba_pid_fuzzy_die(lua_State *L);

/***
 constructor for fuzzy PID controller
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function new
*/
int liba_pid_fuzzy_new(lua_State *L);

/***
 initialize for fuzzy PID controller
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function init
*/
int liba_pid_fuzzy_init(lua_State *L);

/***
 set fuzzy relational operator for fuzzy PID controller
 @tparam int opr enumeration for fuzzy PID controller operator
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_opr
*/
int liba_pid_fuzzy_set_opr(lua_State *L);

/***
 set memory block for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_nfuzz
*/
int liba_pid_fuzzy_set_nfuzz(lua_State *L);

/***
 set rule base for fuzzy PID controller
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table which must be a square matrix
 @tparam table mki points to Ki's rule base table which must be a square matrix
 @tparam table mkd points to Kd's rule base table which must be a square matrix
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_rule
*/
int liba_pid_fuzzy_set_rule(lua_State *L);

/***
 set proportional integral derivative constant for fuzzy PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_kpid
*/
int liba_pid_fuzzy_set_kpid(lua_State *L);

/***
 compute for fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_fuzzy_run(lua_State *L);

/***
 compute for positional fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
int liba_pid_fuzzy_pos(lua_State *L);

/***
 compute for incremental fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
int liba_pid_fuzzy_inc(lua_State *L);

/***
 zeroing for fuzzy PID controller
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function zero
*/
int liba_pid_fuzzy_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/fuzzy.h */
