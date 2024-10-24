/***
 linear regression
 @classmod a.regress_linear
*/

#ifndef LUA_LIBA_REGRESS_LINEAR_H
#define LUA_LIBA_REGRESS_LINEAR_H

#include "a.h"

/***
 linear regression
 @field coef regression coefficient
 @field bias intercept
 @table a.regress_linear
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 destructor for linear regression
 @function die
*/
int liba_regress_linear_die(lua_State *L);

/***
 constructor for linear regression
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_linear linear regression userdata
 @function new
*/
int liba_regress_linear_new(lua_State *L);

/***
 initialize for linear regression
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_linear linear regression userdata
 @function init
*/
int liba_regress_linear_init(lua_State *L);

/***
 calculate predicted value for linear regression
 @tparam number val independent variable
 @treturn number predicted value
 @function eval
*/
int liba_regress_linear_eval(lua_State *L);

/***
 calculate residuals for linear regression
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @treturn table residuals, specified as a numeric vector
 @function err
*/
int liba_regress_linear_err(lua_State *L);

/***
 gradient descent for linear regression
 @tparam table input predictor data, specified as a numeric vector
 @tparam number error residual, specified as a numeric scalar
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function gd
*/
int liba_regress_linear_gd(lua_State *L);

/***
 stochastic gradient descent for linear regression
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function sgd
*/
int liba_regress_linear_sgd(lua_State *L);

/***
 batch gradient descent for linear regression
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function bgd
*/
int liba_regress_linear_bgd(lua_State *L);

/***
 mini-batch gradient descent for linear regression
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number delta threshold for gradient descent value
 @tparam number lrmax maximum learning rate of iterations
 @tparam number lrmin minimum learning rate of iterations
 @tparam[opt] integer lrtim total number of learning rate steps
 @tparam[opt] integer epoch maximum number of epochs
 @tparam[opt] integer batch batch size of data
 @treturn number change in loss function
 @function mgd
*/
int liba_regress_linear_mgd(lua_State *L);

/***
 zeroing for linear regression
 @treturn a.regress_linear linear regression userdata
 @function zero
*/
int liba_regress_linear_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* regress_linear.h */
