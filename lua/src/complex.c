/***
 complex number
 @module liba.complex
*/

#include "complex.h"
#include "a/complex.h"

#if A_PREREQ_GNUC(2, 95) || __has_warning("-Waggregate-return")
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* -Waggregate-return */

static int liba_complex_isok(lua_State *const L, int const idx)
{
    int ok = 0;
    if (lua_getmetatable(L, idx))
    {
        lua_registry_get(L, liba_complex_new);
        ok = lua_rawequal(L, -1, -2);
        lua_pop(L, 2);
    }
    return ok;
}

static a_complex_s liba_complex_from(lua_State *const L, int const idx)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    switch (lua_type(L, idx))
    {
    case LUA_TUSERDATA:
        if (liba_complex_isok(L, idx)) { z = *(a_complex_s *)lua_touserdata(L, idx); }
        break;
    case LUA_TSTRING:
    case LUA_TNUMBER:
        a_complex_real(z) = (a_float_t)lua_tonumber(L, idx);
        break;
    default:
        break;
    }
    return z;
}

static a_complex_s *liba_complex_new_(lua_State *const L)
{
    a_complex_s *const ctx = lua_newclass(L, a_complex_s);
    lua_registry_get(L, liba_complex_new);
    lua_setmetatable(L, -2);
    return ctx;
}

static int liba_complex_tostring(lua_State *const L)
{
    a_complex_s const *const ctx = (a_complex_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_pushfstring(L, "(%f,%f)",
                        (double)a_complex_real(*ctx),
                        (double)a_complex_imag(*ctx));
        return 1;
    }
    return 0;
}

/***
 constructor for complex number from rectangular Cartesian components
 @tparam number real real part of complex number
 @tparam number imag imaginary part of complex number
 @treturn a.complex complex number userdata
 @function new
*/
int liba_complex_new(lua_State *const L)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    int const top = lua_gettop(L);
    if (top >= 2) { a_complex_imag(z) = (a_float_t)lua_tonumber(L, 2); }
    if (top >= 1) { a_complex_real(z) = (a_float_t)lua_tonumber(L, 1); }
    *liba_complex_new_(L) = z;
    return 1;
}

/***
 constructor for complex number from polar form
 @tparam number r a distance from a reference point
 @tparam number theta an angle from a reference direction
 @treturn a.complex complex number userdata
 @function polar
*/
int liba_complex_polar(lua_State *const L)
{
    a_float_t theta = A_FLOAT_C(0.0);
    a_float_t r = A_FLOAT_C(0.0);
    int const top = lua_gettop(L);
    if (top >= 2) { theta = (a_float_t)lua_tonumber(L, 2); }
    if (top >= 1) { r = (a_float_t)lua_tonumber(L, 1); }
    *liba_complex_new_(L) = a_complex_polar(r, theta);
    return 1;
}

#undef FUNC
#define FUNC(func)                                         \
    int liba_complex_##func(lua_State *const L)            \
    {                                                      \
        if (lua_gettop(L) >= 1)                            \
        {                                                  \
            a_complex_s const z = liba_complex_from(L, 1); \
            a_float_t const x = a_complex_##func(z);       \
            lua_pushnumber(L, (lua_Number)x);              \
            return 1;                                      \
        }                                                  \
        return 0;                                          \
    }
/***
 computes the natural logarithm of magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number log|z|
 @function logabs
*/
FUNC(logabs)
/***
 computes the squared magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number a^2+b^2
 @function abs2
*/
FUNC(abs2)
/***
 computes the magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number sqrt{a^2+b^2}
 @function abs
*/
FUNC(abs)
/***
 computes the phase angle of a complex number
 @tparam a.complex z complex number userdata
 @treturn number arctan(b/a)
 @function arg
*/
FUNC(arg)
#undef FUNC
#define FUNC(func)                                         \
    int liba_complex_##func(lua_State *const L)            \
    {                                                      \
        if (lua_gettop(L) >= 1)                            \
        {                                                  \
            a_complex_s const z = liba_complex_from(L, 1); \
            *liba_complex_new_(L) = a_complex_##func(z);   \
            return 1;                                      \
        }                                                  \
        return 0;                                          \
    }
/***
 computes the complex conjugate
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function conj
*/
FUNC(conj)
/***
 computes the complex negative
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function unm
*/
FUNC(neg)
/***
 inverse of a complex number
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function inv
*/
FUNC(inv)
#undef FUNC
#define FUNC(func)                                          \
    int liba_complex_##func(lua_State *const L)             \
    {                                                       \
        if (lua_gettop(L) >= 2)                             \
        {                                                   \
            a_complex_s const x = liba_complex_from(L, 1);  \
            a_complex_s const y = liba_complex_from(L, 2);  \
            *liba_complex_new_(L) = a_complex_##func(x, y); \
            return 1;                                       \
        }                                                   \
        return 0;                                           \
    }
/***
 addition of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function add
*/
FUNC(add)
/***
 subtraction of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function sub
*/
FUNC(sub)
/***
 multiplication of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function mul
*/
FUNC(mul)
/***
 division of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function div
*/
FUNC(div)
/***
 complex number z raised to complex power a
 @tparam a.complex z complex number userdata
 @tparam a.complex a complex number userdata
 @treturn a.complex complex number userdata
 @function pow
*/
FUNC(pow)
/***
 computes the complex base-b logarithm
 @tparam a.complex z complex number userdata
 @tparam a.complex b complex number userdata
 @treturn a.complex complex number userdata
 @function logb
*/
FUNC(logb)
#undef FUNC
#define FUNC(func)                                         \
    int liba_complex_##func(lua_State *const L)            \
    {                                                      \
        if (lua_gettop(L) >= 1)                            \
        {                                                  \
            a_complex_s const z = liba_complex_from(L, 1); \
            *liba_complex_new_(L) = a_complex_##func(z);   \
            return 1;                                      \
        }                                                  \
        return 0;                                          \
    }
/***
 computes the complex base-e exponential
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function exp
*/
FUNC(exp)
/***
 computes the complex natural logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log
*/
FUNC(log)
/***
 computes the complex square root
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sqrt
*/
FUNC(sqrt)
/***
 computes the complex base-2 logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log2
*/
FUNC(log2)
/***
 computes the complex base-10 logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log10
*/
FUNC(log10)
/***
 computes the complex sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sin
*/
FUNC(sin)
/***
 computes the complex cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cos
*/
FUNC(cos)
/***
 computes the complex tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function tan
*/
FUNC(tan)
/***
 computes the complex secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sec
*/
FUNC(sec)
/***
 computes the complex cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function csc
*/
FUNC(csc)
/***
 computes the complex cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cot
*/
FUNC(cot)
/***
 computes the complex arc sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asin
*/
FUNC(asin)
/***
 computes the complex arc cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acos
*/
FUNC(acos)
/***
 computes the complex arc tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function atan
*/
FUNC(atan)
/***
 computes the complex arc secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asec
*/
FUNC(asec)
/***
 computes the complex arc cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acsc
*/
FUNC(acsc)
/***
 computes the complex arc cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acot
*/
FUNC(acot)
/***
 computes the complex hyperbolic sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sinh
*/
FUNC(sinh)
/***
 computes the complex hyperbolic cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cosh
*/
FUNC(cosh)
/***
 computes the complex hyperbolic tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function tanh
*/
FUNC(tanh)
/***
 computes the complex hyperbolic secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sech
*/
FUNC(sech)
/***
 computes the complex hyperbolic cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function csch
*/
FUNC(csch)
/***
 computes the complex hyperbolic cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function coth
*/
FUNC(coth)
/***
 computes the complex arc hyperbolic sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asinh
*/
FUNC(asinh)
/***
 computes the complex arc hyperbolic cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acosh
*/
FUNC(acosh)
/***
 computes the complex arc hyperbolic tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function atanh
*/
FUNC(atanh)
/***
 computes the complex arc hyperbolic secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asech
*/
FUNC(asech)
/***
 computes the complex arc hyperbolic cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acsch
*/
FUNC(acsch)
/***
 computes the complex arc hyperbolic cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acoth
*/
FUNC(acoth)

static int liba_complex_set(lua_State *const L)
{
    a_complex_s *const ctx = (a_complex_s *)lua_touserdata(L, 1);
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0F6133A2: // real
        a_complex_real(*ctx) = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0E2E9172: // imag
        a_complex_imag(*ctx) = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x90705068: // __unm
    case 0x906B0E8D: // __add
    case 0x906FCDE0: // __sub
    case 0x906E3BB4: // __mul
    case 0x906BDA49: // __div
    case 0x906F01C8: // __pow
    case 0x906DF07D: // __len
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
    case 0x5DA21A54: // __tostring
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawset(L, 1);
    }
    return 0;
}

static int liba_complex_get(lua_State *const L)
{
    a_complex_s const *const ctx = (a_complex_s const *)lua_touserdata(L, 1);
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0F6133A2: // real
        lua_pushnumber(L, (lua_Number)a_complex_real(*ctx));
        break;
    case 0x0E2E9172: // imag
        lua_pushnumber(L, (lua_Number)a_complex_imag(*ctx));
        break;
    case 0x00000072: // r
        lua_pushnumber(L, (lua_Number)a_complex_abs(*ctx));
        break;
    case 0x0240D1F6: // theta
        lua_pushnumber(L, (lua_Number)a_complex_arg(*ctx));
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_complex_new);
        lua_num_set(L, -1, "real", a_complex_real(*ctx));
        lua_num_set(L, -1, "imag", a_complex_imag(*ctx));
        lua_num_set(L, -1, "r", a_complex_abs(*ctx));
        lua_num_set(L, -1, "theta", a_complex_arg(*ctx));
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_complex_(lua_State *const L)
{
    lua_pushcfunction(L, liba_complex_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_complex(lua_State *const L)
{
    static lua_fun_s const funcs[] = {
        {"new", liba_complex_new},
        {"polar", liba_complex_polar},
        {"logabs", liba_complex_logabs},
        {"conj", liba_complex_conj},
        {"abs2", liba_complex_abs2},
        {"abs", liba_complex_abs},
        {"arg", liba_complex_arg},
        {"unm", liba_complex_neg},
        {"add", liba_complex_add},
        {"sub", liba_complex_sub},
        {"mul", liba_complex_mul},
        {"div", liba_complex_div},
        {"inv", liba_complex_inv},
        {"pow", liba_complex_pow},
        {"exp", liba_complex_exp},
        {"log", liba_complex_log},
        {"log2", liba_complex_log2},
        {"log10", liba_complex_log10},
        {"logb", liba_complex_logb},
        {"sqrt", liba_complex_sqrt},
        {"sin", liba_complex_sin},
        {"cos", liba_complex_cos},
        {"tan", liba_complex_tan},
        {"sec", liba_complex_sec},
        {"csc", liba_complex_csc},
        {"cot", liba_complex_cot},
        {"asin", liba_complex_asin},
        {"acos", liba_complex_acos},
        {"atan", liba_complex_atan},
        {"asec", liba_complex_asec},
        {"acsc", liba_complex_acsc},
        {"acot", liba_complex_acot},
        {"sinh", liba_complex_sinh},
        {"cosh", liba_complex_cosh},
        {"tanh", liba_complex_tanh},
        {"sech", liba_complex_sech},
        {"csch", liba_complex_csch},
        {"coth", liba_complex_coth},
        {"asinh", liba_complex_asinh},
        {"acosh", liba_complex_acosh},
        {"atanh", liba_complex_atanh},
        {"asech", liba_complex_asech},
        {"acsch", liba_complex_acsch},
        {"acoth", liba_complex_acoth},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));

    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_complex_);
    lua_setmetatable(L, -2);

    static lua_fun_s const metas[] = {
        {"__tostring", liba_complex_tostring},
        {"__newindex", liba_complex_set},
        {"__index", liba_complex_get},
        {"__unm", liba_complex_neg},
        {"__add", liba_complex_add},
        {"__sub", liba_complex_sub},
        {"__mul", liba_complex_mul},
        {"__div", liba_complex_div},
        {"__pow", liba_complex_pow},
        {"__len", liba_complex_abs},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.complex");

    lua_registry_set(L, liba_complex_new);
    return 1;
}
