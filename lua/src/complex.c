/***
 complex number
 @module liba.complex
*/

#include "complex.h"
#include "a/complex.h"

static int liba_complex_isok(lua_State *L, int idx)
{
    int isok = 0;
    if (lua_getmetatable(L, idx))
    {
        lua_registry_get(L, liba_complex_new);
        isok = lua_rawequal(L, -1, -2);
        lua_pop(L, 2);
    }
    return isok;
}

static int liba_complex_from(lua_State *L, a_complex *z, int idx)
{
    int type = lua_type(L, idx);
    switch (type)
    {
    case LUA_TNUMBER:
        z->real = (a_real)lua_tonumber(L, idx);
        z->imag = 0;
        break;
    case LUA_TSTRING:
        a_complex_parse(z, lua_tostring(L, idx));
        break;
    case LUA_TUSERDATA:
        if (liba_complex_isok(L, idx))
        {
            *z = *(a_complex *)lua_touserdata(L, idx);
            break;
        }
        A_FALLTHROUGH;
    default:
        z->real = 0;
        z->imag = 0;
    }
    return type;
}

static a_complex *liba_complex_new_(lua_State *L)
{
    a_complex *const ctx = lua_newclass(L, a_complex);
    lua_registry_get(L, liba_complex_new);
    lua_setmetatable(L, -2);
    return ctx;
}

static int liba_complex_tostring(lua_State *L)
{
    a_complex const *const ctx = (a_complex const *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_pushfstring(L, "(%f,%f)", (double)ctx->real, (double)ctx->imag);
        return 1;
    }
    return 0;
}

/***
 constructor for complex number from real and imaginary parts
 @tparam[opt] number|string|a.complex real real part of complex number
 @tparam[opt] number imag imaginary part of complex number
 @treturn a.complex complex number userdata
 @function new
*/
int liba_complex_new(lua_State *L)
{
    a_complex z = A_COMPLEX_C(0, 0);
    int const top = lua_gettop(L);
    if (top >= 1)
    {
        int const type = liba_complex_from(L, &z, 1);
        if (type == LUA_TNUMBER && top >= 2)
        {
            z.imag = (a_real)lua_tonumber(L, 2);
        }
    }
    *liba_complex_new_(L) = z;
    return 1;
}

/***
 constructor for complex number from rectangular Cartesian components
 @tparam[opt] number real real part of complex number
 @tparam[opt] number imag imaginary part of complex number
 @treturn a.complex complex number userdata
 @function rect
*/
int liba_complex_rect(lua_State *L)
{
    a_real real = 0, imag = 0;
    int const top = lua_gettop(L);
    if (top >= 1) { real = (a_real)lua_tonumber(L, 1); }
    if (top >= 2) { imag = (a_real)lua_tonumber(L, 2); }
    a_complex_rect(liba_complex_new_(L), real, imag);
    return 1;
}

/***
 constructor for complex number from polar form
 @tparam[opt] number rho a distance from a reference point
 @tparam[opt] number theta an angle from a reference direction
 @treturn a.complex complex number userdata
 @function polar
*/
int liba_complex_polar(lua_State *L)
{
    a_real rho = 0, theta = 0;
    int const top = lua_gettop(L);
    if (top >= 1) { rho = (a_real)lua_tonumber(L, 1); }
    if (top >= 2) { theta = (a_real)lua_tonumber(L, 2); }
    a_complex_polar(liba_complex_new_(L), rho, theta);
    return 1;
}

/***
 complex number x is equal to complex number y
 @tparam a.complex x complex number on the left
 @tparam a.complex y complex number on the right
 @treturn bool result of comparison
 @function eq
*/
int liba_complex_eq(lua_State *L)
{
    if (lua_gettop(L) >= 2)
    {
        a_complex x, y;
        liba_complex_from(L, &x, 1);
        liba_complex_from(L, &y, 2);
        lua_pushboolean(L, a_complex_eq(x, y));
        return 1;
    }
    return 0;
}

/***
 complex number x is not equal to complex number y
 @tparam a.complex x complex number on the left
 @tparam a.complex y complex number on the right
 @treturn bool result of comparison
 @function ne
*/
int liba_complex_ne(lua_State *L)
{
    if (lua_gettop(L) >= 2)
    {
        a_complex x, y;
        liba_complex_from(L, &x, 1);
        liba_complex_from(L, &y, 2);
        lua_pushboolean(L, a_complex_ne(x, y));
        return 1;
    }
    return 0;
}

#undef F1
#define F1(func)                                   \
    int liba_complex_##func(lua_State *L)          \
    {                                              \
        if (lua_gettop(L) >= 1)                    \
        {                                          \
            a_complex z;                           \
            liba_complex_from(L, &z, 1);           \
            z.real = a_complex_##func(z);          \
            lua_pushnumber(L, (lua_Number)z.real); \
            return 1;                              \
        }                                          \
        return 0;                                  \
    }
/***
 computes the natural logarithm of magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number log|z|
 @function logabs
*/
F1(logabs)
/***
 computes the squared magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number a^2+b^2
 @function abs2
*/
F1(abs2)
/***
 computes the magnitude of a complex number
 @tparam a.complex z complex number userdata
 @treturn number sqrt{a^2+b^2}
 @function abs
*/
F1(abs)
/***
 computes the phase angle of a complex number
 @tparam a.complex z complex number userdata
 @treturn number arctan(b/a)
 @function arg
*/
F1(arg)
#undef F1
#define F1(func)                          \
    int liba_complex_##func(lua_State *L) \
    {                                     \
        if (lua_gettop(L) >= 1)           \
        {                                 \
            a_complex z, *ctx;            \
            ctx = liba_complex_new_(L);   \
            liba_complex_from(L, &z, 1);  \
            a_complex_##func(ctx, z);     \
            return 1;                     \
        }                                 \
        return 0;                         \
    }
/***
 computes the projection on Riemann sphere
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function proj
*/
F1(proj)
/***
 computes the complex conjugate
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function conj
*/
F1(conj)
/***
 computes the complex negative
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function unm
*/
F1(neg)
/***
 inverse of a complex number
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function inv
*/
F1(inv)
#undef F1
#define F1(func)                          \
    int liba_complex_##func(lua_State *L) \
    {                                     \
        if (lua_gettop(L) >= 2)           \
        {                                 \
            a_complex x, y, *ctx;         \
            ctx = liba_complex_new_(L);   \
            liba_complex_from(L, &x, 1);  \
            liba_complex_from(L, &y, 2);  \
            a_complex_##func(ctx, x, y);  \
            return 1;                     \
        }                                 \
        return 0;                         \
    }
#undef F2
#define F2(func)                                            \
    int liba_complex_##func(lua_State *L)                   \
    {                                                       \
        if (lua_gettop(L) >= 2)                             \
        {                                                   \
            a_complex x, y, *ctx = liba_complex_new_(L);    \
            liba_complex_from(L, &x, 1);                    \
            if (liba_complex_from(L, &y, 2) == LUA_TNUMBER) \
            {                                               \
                a_complex_##func##_real(ctx, x, y.real);    \
            }                                               \
            else { a_complex_##func(ctx, x, y); }           \
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
F2(add)
/***
 subtraction of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function sub
*/
F2(sub)
/***
 multiplication of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function mul
*/
F2(mul)
/***
 division of complex numbers
 @tparam a.complex x complex number userdata
 @tparam a.complex y complex number userdata
 @treturn a.complex complex number userdata
 @function div
*/
F2(div)
/***
 complex number z raised to complex power a
 @tparam a.complex z complex number userdata
 @tparam a.complex a complex number userdata
 @treturn a.complex complex number userdata
 @function pow
*/
F1(pow)
/***
 computes the complex base-b logarithm
 @tparam a.complex z complex number userdata
 @tparam a.complex b complex number userdata
 @treturn a.complex complex number userdata
 @function logb
*/
F1(logb)
#undef F1
#define F1(func)                          \
    int liba_complex_##func(lua_State *L) \
    {                                     \
        if (lua_gettop(L) >= 1)           \
        {                                 \
            a_complex z, *ctx;            \
            ctx = liba_complex_new_(L);   \
            liba_complex_from(L, &z, 1);  \
            a_complex_##func(ctx, z);     \
            return 1;                     \
        }                                 \
        return 0;                         \
    }
#undef F2
#define F2(func)                                      \
    int liba_complex_##func(lua_State *L)             \
    {                                                 \
        if (lua_gettop(L) >= 1)                       \
        {                                             \
            a_complex z, *ctx = liba_complex_new_(L); \
            int type = liba_complex_from(L, &z, 1);   \
            if (type == LUA_TNUMBER)                  \
            {                                         \
                a_complex_##func##_real(ctx, z.real); \
            }                                         \
            else { a_complex_##func(ctx, z); }        \
            return 1;                                 \
        }                                             \
        return 0;                                     \
    }
/***
 computes the complex base-e exponential
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function exp
*/
F1(exp)
/***
 computes the complex natural logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log
*/
F1(log)
/***
 computes the complex square root
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sqrt
*/
F2(sqrt)
/***
 computes the complex base-2 logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log2
*/
F1(log2)
/***
 computes the complex base-10 logarithm
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function log10
*/
F1(log10)
/***
 computes the complex sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sin
*/
F1(sin)
/***
 computes the complex cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cos
*/
F1(cos)
/***
 computes the complex tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function tan
*/
F1(tan)
/***
 computes the complex secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sec
*/
F1(sec)
/***
 computes the complex cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function csc
*/
F1(csc)
/***
 computes the complex cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cot
*/
F1(cot)
/***
 computes the complex arc sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asin
*/
F2(asin)
/***
 computes the complex arc cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acos
*/
F2(acos)
/***
 computes the complex arc tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function atan
*/
F1(atan)
/***
 computes the complex arc secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asec
*/
F2(asec)
/***
 computes the complex arc cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acsc
*/
F2(acsc)
/***
 computes the complex arc cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acot
*/
F1(acot)
/***
 computes the complex hyperbolic sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sinh
*/
F1(sinh)
/***
 computes the complex hyperbolic cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function cosh
*/
F1(cosh)
/***
 computes the complex hyperbolic tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function tanh
*/
F1(tanh)
/***
 computes the complex hyperbolic secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function sech
*/
F1(sech)
/***
 computes the complex hyperbolic cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function csch
*/
F1(csch)
/***
 computes the complex hyperbolic cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function coth
*/
F1(coth)
/***
 computes the complex arc hyperbolic sine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asinh
*/
F1(asinh)
/***
 computes the complex arc hyperbolic cosine
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acosh
*/
F2(acosh)
/***
 computes the complex arc hyperbolic tangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function atanh
*/
F2(atanh)
/***
 computes the complex arc hyperbolic secant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function asech
*/
F1(asech)
/***
 computes the complex arc hyperbolic cosecant
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acsch
*/
F1(acsch)
/***
 computes the complex arc hyperbolic cotangent
 @tparam a.complex z complex number userdata
 @treturn a.complex complex number userdata
 @function acoth
*/
F1(acoth)

static int liba_complex_set(lua_State *L)
{
    a_complex *const ctx = (a_complex *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0F6133A2: /* real */
        ctx->real = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x0E2E9172: /* imag */
        ctx->imag = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x001E0FA9: /* rho */
    {
        a_real const rho = (a_real)luaL_checknumber(L, 3);
        a_real const theta = a_complex_arg(*ctx);
        a_complex_polar(ctx, rho, theta);
        break;
    }
    case 0x0240D1F6: /* theta */
    {
        a_real const theta = (a_real)luaL_checknumber(L, 3);
        a_real const rho = a_complex_abs(*ctx);
        a_complex_polar(ctx, rho, theta);
        break;
    }
    case 0x0CD3E0FC: /* __eq */
    case 0x906DF07D: /* __len */
    case 0x90705068: /* __unm */
    case 0x906B0E8D: /* __add */
    case 0x906FCDE0: /* __sub */
    case 0x906E3BB4: /* __mul */
    case 0x906BDA49: /* __div */
    case 0x906F01C8: /* __pow */
    case 0xE8859EEB: /* __name */
    case 0xA65758B2: /* __index */
    case 0xAEB551C6: /* __newindex */
    case 0x5DA21A54: /* __tostring */
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawset(L, 1);
    }
    return 0;
}

static int liba_complex_get(lua_State *L)
{
    a_complex const *const ctx = (a_complex const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0F6133A2: /* real */
        lua_pushnumber(L, (lua_Number)ctx->real);
        break;
    case 0x0E2E9172: /* imag */
        lua_pushnumber(L, (lua_Number)ctx->imag);
        break;
    case 0x001E0FA9: /* rho */
        lua_pushnumber(L, (lua_Number)a_complex_abs(*ctx));
        break;
    case 0x0240D1F6: /* theta */
        lua_pushnumber(L, (lua_Number)a_complex_arg(*ctx));
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_complex_new);
        lua_num_set(L, -1, "real", ctx->real);
        lua_num_set(L, -1, "imag", ctx->imag);
        lua_num_set(L, -1, "rho", a_complex_abs(*ctx));
        lua_num_set(L, -1, "theta", a_complex_arg(*ctx));
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_complex_(lua_State *L)
{
    lua_pushcfunction(L, liba_complex_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_complex(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_complex_new},
        {"rect", liba_complex_rect},
        {"polar", liba_complex_polar},
        {"eq", liba_complex_eq},
        {"ne", liba_complex_ne},
        {"logabs", liba_complex_logabs},
        {"proj", liba_complex_proj},
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
    static lua_fun const metas[] = {
        {"__tostring", liba_complex_tostring},
        {"__newindex", liba_complex_set},
        {"__index", liba_complex_get},
        {"__len", liba_complex_abs},
        {"__unm", liba_complex_neg},
        {"__add", liba_complex_add},
        {"__sub", liba_complex_sub},
        {"__mul", liba_complex_mul},
        {"__div", liba_complex_div},
        {"__pow", liba_complex_pow},
        {"__eq", liba_complex_eq},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_complex_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.complex");
    lua_registry_set(L, liba_complex_new);

    return 1;
}
