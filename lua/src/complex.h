/***
 complex number
 @classmod complex
*/

/***
 complex number
 @field real real part of complex number
 @field imag imaginary part of complex number
 @table complex
*/

#ifndef L_COMPLEX_H
#define L_COMPLEX_H

#include "a.h"
#include "a/complex.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(complex_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(complex_meta_)(lua_State *L, int ret);

/***
 constructor for complex number from rectangular Cartesian components
 @tparam number real real part of complex number
 @tparam number imag imaginary part of complex number
 @treturn complex complex number userdata
 @function new
*/
A_PUBLIC int LMODULE(complex_new)(lua_State *L);

/***
 constructor for complex number from polar form
 @tparam number r a distance from a reference point
 @tparam number theta an angle from a reference direction
 @treturn complex complex number userdata
 @function polar
*/
A_PUBLIC int LMODULE(complex_polar)(lua_State *L);

/***
 computes the natural logarithm of magnitude of a complex number
 @treturn complex complex number userdata
 @function logabs
*/
A_PUBLIC int LMODULE(complex_logabs)(lua_State *L);

/***
 computes the squared magnitude of a complex number
 @treturn complex complex number userdata
 @function abs2
*/
A_PUBLIC int LMODULE(complex_abs2)(lua_State *L);

/***
 computes the magnitude of a complex number
 @treturn complex complex number userdata
 @function abs
*/
A_PUBLIC int LMODULE(complex_abs)(lua_State *L);

/***
 computes the phase angle of a complex number
 @treturn complex complex number userdata
 @function arg
*/
A_PUBLIC int LMODULE(complex_arg)(lua_State *L);

/***
 computes the complex conjugate
 @treturn complex complex number userdata
 @function conj
*/
A_PUBLIC int LMODULE(complex_conj)(lua_State *L);

/***
 computes the complex negative
 @treturn complex complex number userdata
 @function unm
*/
A_PUBLIC int LMODULE(complex_neg)(lua_State *L);

/***
 inverse of a complex number
 @treturn complex complex number userdata
 @function inv
*/
A_PUBLIC int LMODULE(complex_inv)(lua_State *L);

/***
 addition of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function add
*/
A_PUBLIC int LMODULE(complex_add)(lua_State *L);

/***
 subtraction of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sub
*/
A_PUBLIC int LMODULE(complex_sub)(lua_State *L);

/***
 multiplication of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function mul
*/
A_PUBLIC int LMODULE(complex_mul)(lua_State *L);

/***
 division of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function div
*/
A_PUBLIC int LMODULE(complex_div)(lua_State *L);

/***
 complex number z raised to complex power a
 @tparam complex a complex number userdata
 @treturn complex complex number userdata
 @function pow
*/
A_PUBLIC int LMODULE(complex_pow)(lua_State *L);

/***
 computes the complex base-b logarithm
 @tparam complex b complex number userdata
 @treturn complex complex number userdata
 @function logb
*/
A_PUBLIC int LMODULE(complex_logb)(lua_State *L);

/***
 computes the complex base-e exponential
 @treturn complex complex number userdata
 @function exp
*/
A_PUBLIC int LMODULE(complex_exp)(lua_State *L);

/***
 computes the complex natural logarithm
 @treturn complex complex number userdata
 @function log
*/
A_PUBLIC int LMODULE(complex_log)(lua_State *L);

/***
 computes the complex square root
 @treturn complex complex number userdata
 @function sqrt
*/
A_PUBLIC int LMODULE(complex_sqrt)(lua_State *L);

/***
 computes the complex base-2 logarithm
 @treturn complex complex number userdata
 @function log2
*/
A_PUBLIC int LMODULE(complex_log2)(lua_State *L);

/***
 computes the complex base-10 logarithm
 @treturn complex complex number userdata
 @function log10
*/
A_PUBLIC int LMODULE(complex_log10)(lua_State *L);

/***
 computes the complex sine
 @treturn complex complex number userdata
 @function sin
*/
A_PUBLIC int LMODULE(complex_sin)(lua_State *L);

/***
 computes the complex cosine
 @treturn complex complex number userdata
 @function cos
*/
A_PUBLIC int LMODULE(complex_cos)(lua_State *L);

/***
 computes the complex tangent
 @treturn complex complex number userdata
 @function tan
*/
A_PUBLIC int LMODULE(complex_tan)(lua_State *L);

/***
 computes the complex secant
 @treturn complex complex number userdata
 @function sec
*/
A_PUBLIC int LMODULE(complex_sec)(lua_State *L);

/***
 computes the complex cosecant
 @treturn complex complex number userdata
 @function csc
*/
A_PUBLIC int LMODULE(complex_csc)(lua_State *L);

/***
 computes the complex cotangent
 @treturn complex complex number userdata
 @function cot
*/
A_PUBLIC int LMODULE(complex_cot)(lua_State *L);

/***
 computes the complex arc sine
 @treturn complex complex number userdata
 @function asin
*/
A_PUBLIC int LMODULE(complex_asin)(lua_State *L);

/***
 computes the complex arc cosine
 @treturn complex complex number userdata
 @function acos
*/
A_PUBLIC int LMODULE(complex_acos)(lua_State *L);

/***
 computes the complex arc tangent
 @treturn complex complex number userdata
 @function atan
*/
A_PUBLIC int LMODULE(complex_atan)(lua_State *L);

/***
 computes the complex arc secant
 @treturn complex complex number userdata
 @function asec
*/
A_PUBLIC int LMODULE(complex_asec)(lua_State *L);

/***
 computes the complex arc cosecant
 @treturn complex complex number userdata
 @function acsc
*/
A_PUBLIC int LMODULE(complex_acsc)(lua_State *L);

/***
 computes the complex arc cotangent
 @treturn complex complex number userdata
 @function acot
*/
A_PUBLIC int LMODULE(complex_acot)(lua_State *L);

/***
 computes the complex hyperbolic sine
 @treturn complex complex number userdata
 @function sinh
*/
A_PUBLIC int LMODULE(complex_sinh)(lua_State *L);

/***
 computes the complex hyperbolic cosine
 @treturn complex complex number userdata
 @function cosh
*/
A_PUBLIC int LMODULE(complex_cosh)(lua_State *L);

/***
 computes the complex hyperbolic tangent
 @treturn complex complex number userdata
 @function tanh
*/
A_PUBLIC int LMODULE(complex_tanh)(lua_State *L);

/***
 computes the complex hyperbolic secant
 @treturn complex complex number userdata
 @function sech
*/
A_PUBLIC int LMODULE(complex_sech)(lua_State *L);

/***
 computes the complex hyperbolic cosecant
 @treturn complex complex number userdata
 @function csch
*/
A_PUBLIC int LMODULE(complex_csch)(lua_State *L);

/***
 computes the complex hyperbolic cotangent
 @treturn complex complex number userdata
 @function coth
*/
A_PUBLIC int LMODULE(complex_coth)(lua_State *L);

/***
 computes the complex arc hyperbolic sine
 @treturn complex complex number userdata
 @function asinh
*/
A_PUBLIC int LMODULE(complex_asinh)(lua_State *L);

/***
 computes the complex arc hyperbolic cosine
 @treturn complex complex number userdata
 @function acosh
*/
A_PUBLIC int LMODULE(complex_acosh)(lua_State *L);

/***
 computes the complex arc hyperbolic tangent
 @treturn complex complex number userdata
 @function atanh
*/
A_PUBLIC int LMODULE(complex_atanh)(lua_State *L);

/***
 computes the complex arc hyperbolic secant
 @treturn complex complex number userdata
 @function asech
*/
A_PUBLIC int LMODULE(complex_asech)(lua_State *L);

/***
 computes the complex arc hyperbolic cosecant
 @treturn complex complex number userdata
 @function acsch
*/
A_PUBLIC int LMODULE(complex_acsch)(lua_State *L);

/***
 computes the complex arc hyperbolic cotangent
 @treturn complex complex number userdata
 @function acoth
*/
A_PUBLIC int LMODULE(complex_acoth)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* complex.h */
