/***
 complex number
 @classmod a.complex
*/

#ifndef LUA_LIBA_COMPLEX_H
#define LUA_LIBA_COMPLEX_H

#include "a.h"

/***
 complex number
 @field real real part of complex number
 @field imag imaginary part of complex number
 @table a.complex
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for complex number from rectangular Cartesian components
 @tparam[opt] number|string|a.complex real real part of complex number
 @tparam[opt] number imag imaginary part of complex number
 @treturn a.complex complex number userdata
 @function new
*/
int liba_complex_new(lua_State *L);

/***
 constructor for complex number from polar form
 @tparam[opt] number r a distance from a reference point
 @tparam[opt] number theta an angle from a reference direction
 @treturn a.complex complex number userdata
 @function polar
*/
int liba_complex_polar(lua_State *L);

/***
 complex number self is equal to complex number other
 @tparam a.complex other other complex number
 @treturn bool result of comparison
 @function eq
*/
int liba_complex_eq(lua_State *L);

/***
 complex number self is not equal to complex number other
 @tparam a.complex other other complex number
 @treturn bool result of comparison
 @function ne
*/
int liba_complex_ne(lua_State *L);

/***
 computes the natural logarithm of magnitude of a complex number
 @treturn number log|z|
 @function logabs
*/
int liba_complex_logabs(lua_State *L);

/***
 computes the squared magnitude of a complex number
 @treturn number a^2+b^2
 @function abs2
*/
int liba_complex_abs2(lua_State *L);

/***
 computes the magnitude of a complex number
 @treturn number sqrt{a^2+b^2}
 @function abs
*/
int liba_complex_abs(lua_State *L);

/***
 computes the phase angle of a complex number
 @treturn number arctan(b/a)
 @function arg
*/
int liba_complex_arg(lua_State *L);

/***
 computes the complex conjugate
 @treturn a.complex complex number userdata
 @function conj
*/
int liba_complex_conj(lua_State *L);

/***
 computes the complex negative
 @treturn a.complex complex number userdata
 @function unm
*/
int liba_complex_neg(lua_State *L);

/***
 inverse of a complex number
 @treturn a.complex complex number userdata
 @function inv
*/
int liba_complex_inv(lua_State *L);

/***
 addition of complex numbers
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function add
*/
int liba_complex_add(lua_State *L);

/***
 subtraction of complex numbers
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sub
*/
int liba_complex_sub(lua_State *L);

/***
 multiplication of complex numbers
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function mul
*/
int liba_complex_mul(lua_State *L);

/***
 division of complex numbers
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function div
*/
int liba_complex_div(lua_State *L);

/***
 complex number z raised to complex power a
 @tparam a.complex a complex number userdata
 @treturn a.complex complex number userdata
 @function pow
*/
int liba_complex_pow(lua_State *L);

/***
 computes the complex base-b logarithm
 @tparam a.complex b complex number userdata
 @treturn a.complex complex number userdata
 @function logb
*/
int liba_complex_logb(lua_State *L);

/***
 computes the complex base-e exponential
 @treturn a.complex complex number userdata
 @function exp
*/
int liba_complex_exp(lua_State *L);

/***
 computes the complex natural logarithm
 @treturn a.complex complex number userdata
 @function log
*/
int liba_complex_log(lua_State *L);

/***
 computes the complex square root
 @treturn a.complex complex number userdata
 @function sqrt
*/
int liba_complex_sqrt(lua_State *L);

/***
 computes the complex base-2 logarithm
 @treturn a.complex complex number userdata
 @function log2
*/
int liba_complex_log2(lua_State *L);

/***
 computes the complex base-10 logarithm
 @treturn a.complex complex number userdata
 @function log10
*/
int liba_complex_log10(lua_State *L);

/***
 computes the complex sine
 @treturn a.complex complex number userdata
 @function sin
*/
int liba_complex_sin(lua_State *L);

/***
 computes the complex cosine
 @treturn a.complex complex number userdata
 @function cos
*/
int liba_complex_cos(lua_State *L);

/***
 computes the complex tangent
 @treturn a.complex complex number userdata
 @function tan
*/
int liba_complex_tan(lua_State *L);

/***
 computes the complex secant
 @treturn a.complex complex number userdata
 @function sec
*/
int liba_complex_sec(lua_State *L);

/***
 computes the complex cosecant
 @treturn a.complex complex number userdata
 @function csc
*/
int liba_complex_csc(lua_State *L);

/***
 computes the complex cotangent
 @treturn a.complex complex number userdata
 @function cot
*/
int liba_complex_cot(lua_State *L);

/***
 computes the complex arc sine
 @treturn a.complex complex number userdata
 @function asin
*/
int liba_complex_asin(lua_State *L);

/***
 computes the complex arc cosine
 @treturn a.complex complex number userdata
 @function acos
*/
int liba_complex_acos(lua_State *L);

/***
 computes the complex arc tangent
 @treturn a.complex complex number userdata
 @function atan
*/
int liba_complex_atan(lua_State *L);

/***
 computes the complex arc secant
 @treturn a.complex complex number userdata
 @function asec
*/
int liba_complex_asec(lua_State *L);

/***
 computes the complex arc cosecant
 @treturn a.complex complex number userdata
 @function acsc
*/
int liba_complex_acsc(lua_State *L);

/***
 computes the complex arc cotangent
 @treturn a.complex complex number userdata
 @function acot
*/
int liba_complex_acot(lua_State *L);

/***
 computes the complex hyperbolic sine
 @treturn a.complex complex number userdata
 @function sinh
*/
int liba_complex_sinh(lua_State *L);

/***
 computes the complex hyperbolic cosine
 @treturn a.complex complex number userdata
 @function cosh
*/
int liba_complex_cosh(lua_State *L);

/***
 computes the complex hyperbolic tangent
 @treturn a.complex complex number userdata
 @function tanh
*/
int liba_complex_tanh(lua_State *L);

/***
 computes the complex hyperbolic secant
 @treturn a.complex complex number userdata
 @function sech
*/
int liba_complex_sech(lua_State *L);

/***
 computes the complex hyperbolic cosecant
 @treturn a.complex complex number userdata
 @function csch
*/
int liba_complex_csch(lua_State *L);

/***
 computes the complex hyperbolic cotangent
 @treturn a.complex complex number userdata
 @function coth
*/
int liba_complex_coth(lua_State *L);

/***
 computes the complex arc hyperbolic sine
 @treturn a.complex complex number userdata
 @function asinh
*/
int liba_complex_asinh(lua_State *L);

/***
 computes the complex arc hyperbolic cosine
 @treturn a.complex complex number userdata
 @function acosh
*/
int liba_complex_acosh(lua_State *L);

/***
 computes the complex arc hyperbolic tangent
 @treturn a.complex complex number userdata
 @function atanh
*/
int liba_complex_atanh(lua_State *L);

/***
 computes the complex arc hyperbolic secant
 @treturn a.complex complex number userdata
 @function asech
*/
int liba_complex_asech(lua_State *L);

/***
 computes the complex arc hyperbolic cosecant
 @treturn a.complex complex number userdata
 @function acsch
*/
int liba_complex_acsch(lua_State *L);

/***
 computes the complex arc hyperbolic cotangent
 @treturn a.complex complex number userdata
 @function acoth
*/
int liba_complex_acoth(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* complex.h */
