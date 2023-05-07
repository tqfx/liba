/***
 fuzzy proportional integral derivative controller
 @classmod fpid
*/

/***
 fuzzy proportional integral derivative controller
 @field dt sampling time unit(s)
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field mode controller mode
 @field outmin minimum final output
 @field outmax maximum final output
 @field summax maximum integral output
 @field col number of columns in the rule base
 @field buf maximum number triggered by the rule
 @field out controller output
 @field fdb cache feedback
 @field ec error change
 @field e error input
 @table fpid
*/

#ifndef L_FPID_H
#define L_FPID_H

#include "pid.h"
#include "a/fpid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(fpid_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(fpid_meta_)(lua_State *L, int ret);

/***
 destructor for fuzzy PID controller
 @function die
*/
A_PUBLIC int LMODULE(fpid_die)(lua_State *L);

/***
 constructor for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number imin minimum input
 @tparam number imax maximum input
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function new
*/
A_PUBLIC int LMODULE(fpid_new)(lua_State *L);

/***
 initialize function for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function init
*/
A_PUBLIC int LMODULE(fpid_init)(lua_State *L);

/***
 calculate function for fuzzy PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
A_PUBLIC int LMODULE(fpid_iter)(lua_State *L);

/***
 zero function for fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function zero
*/
A_PUBLIC int LMODULE(fpid_zero)(lua_State *L);

/***
 set rule base for fuzzy PID controller
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
A_PUBLIC int LMODULE(fpid_base)(lua_State *L);

/***
 set proportional integral derivative constant for fuzzy PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn fpid fuzzy PID controller userdata
 @function kpid
*/
A_PUBLIC int LMODULE(fpid_kpid)(lua_State *L);

/***
 positional fuzzy PID controller
 @tparam number max maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function pos
*/
A_PUBLIC int LMODULE(fpid_pos)(lua_State *L);

/***
 incremental fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function inc
*/
A_PUBLIC int LMODULE(fpid_inc)(lua_State *L);

/***
 turn off fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function off
*/
A_PUBLIC int LMODULE(fpid_off)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* fpid.h */
