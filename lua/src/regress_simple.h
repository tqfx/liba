/***
 simple linear regression
 @classmod a.regress_simple
*/

#ifndef LUA_LIBA_REGRESS_SIMPLE_H
#define LUA_LIBA_REGRESS_SIMPLE_H

#include "a.h"

/***
 simple linear regression
 @field coef regression coefficient
 @field bias intercept
 @table a.regress_simple
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for simple linear regression
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_simple simple linear regression userdata
 @function new
*/
int liba_regress_simple_new(lua_State *L);

/***
 initialize for simple linear regression
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_simple simple linear regression userdata
 @function init
*/
int liba_regress_simple_init(lua_State *L);

/***
 compute predicted value for simple linear regression
 @tparam number val independent variable
 @treturn number predicted value
 @function eval
*/
int liba_regress_simple_eval(lua_State *L);

/***
 compute predicted value for simple linear regression
 @tparam number val dependent variable
 @treturn number predicted value
 @function evar
*/
int liba_regress_simple_evar(lua_State *L);

/***
 ordinary least squares for simple linear regression
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number x_mean mean of predictor data
 @tparam number y_mean mean of response data
 @treturn a.regress_simple simple linear regression userdata
 @function ols_
*/
int liba_regress_simple_ols_(lua_State *L);

/***
 ordinary least squares for simple linear regression
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number x_mean mean of predictor data
 @treturn a.regress_simple simple linear regression userdata
 @function olsx
*/
int liba_regress_simple_olsx(lua_State *L);

/***
 ordinary least squares for simple linear regression
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number y_mean mean of response data
 @treturn a.regress_simple simple linear regression userdata
 @function olsy
*/
int liba_regress_simple_olsy(lua_State *L);

/***
 ordinary least squares for simple linear regression
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @treturn a.regress_simple simple linear regression userdata
 @function ols
*/
int liba_regress_simple_ols(lua_State *L);

/***
 zeroing for simple linear regression
 @treturn a.regress_simple simple linear regression userdata
 @function zero
*/
int liba_regress_simple_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* regress_simple.h */
