/***
 simple linear regression
 @module liba.regress_simple
*/

#include "regress_simple.h"
#include "a/regress_simple.h"

/***
 constructor for simple linear regression
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_simple simple linear regression userdata
 @function new
*/
int liba_regress_simple_new(lua_State *L)
{
    a_float a = (a_float)luaL_optnumber(L, 1, 1);
    a_float b = (a_float)luaL_optnumber(L, 2, 0);
    a_regress_simple *const ctx = lua_newclass(L, a_regress_simple);
    lua_registry_get(L, liba_regress_simple_new);
    lua_setmetatable(L, -2);
    a_regress_simple_init(ctx, a, b);
    return 1;
}

/***
 initialize for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_simple simple linear regression userdata
 @function init
*/
int liba_regress_simple_init(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_float a = (a_float)luaL_optnumber(L, 2, 1);
    a_float b = (a_float)luaL_optnumber(L, 3, 0);
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    a_regress_simple_init(ctx, a, b);
    lua_pushvalue(L, 1);
    return 1;
}

/***
 calculate predicted value for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam number val independent variable
 @treturn number predicted value
 @function eval
*/
int liba_regress_simple_eval(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_regress_simple_eval(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate predicted value for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam number val dependent variable
 @treturn number predicted value
 @function evar
*/
int liba_regress_simple_evar(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_regress_simple_eval(ctx, x));
        return 1;
    }
    return 0;
}

/***
 ordinary least squares for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number x_mean mean of predictor data
 @tparam number y_mean mean of response data
 @treturn a.regress_simple simple linear regression userdata
 @function ols_
*/
int liba_regress_simple_ols_(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_float x_mean = (a_float)luaL_checknumber(L, 4);
        a_float y_mean = (a_float)luaL_checknumber(L, 5);
        unsigned int const n = (unsigned int)lua_rawlen(L, 2);
        a_float *const x = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 2, x, n);
        a_float *const y = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 3, x, n);
        a_regress_simple_ols_(ctx, n, x, y, x_mean, y_mean);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 ordinary least squares for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number x_mean mean of predictor data
 @treturn a.regress_simple simple linear regression userdata
 @function olsx
*/
int liba_regress_simple_olsx(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_float x_mean = (a_float)luaL_checknumber(L, 4);
        unsigned int const n = (unsigned int)lua_rawlen(L, 2);
        a_float *const x = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 2, x, n);
        a_float *const y = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 3, x, n);
        a_regress_simple_olsx(ctx, n, x, y, x_mean);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 ordinary least squares for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @tparam number y_mean mean of response data
 @treturn a.regress_simple simple linear regression userdata
 @function olsy
*/
int liba_regress_simple_olsy(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_float y_mean = (a_float)luaL_checknumber(L, 4);
        unsigned int const n = (unsigned int)lua_rawlen(L, 2);
        a_float *const x = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 2, x, n);
        a_float *const y = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 3, x, n);
        a_regress_simple_olsy(ctx, n, x, y, y_mean);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 ordinary least squares for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @tparam table x predictor data, specified as a numeric vector
 @tparam table y response data, specified as a numeric vector
 @treturn a.regress_simple simple linear regression userdata
 @function ols
*/
int liba_regress_simple_ols(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        unsigned int const n = (unsigned int)lua_rawlen(L, 2);
        a_float *const x = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 2, x, n);
        a_float *const y = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * n);
        lua_array_num_get(L, 3, x, n);
        a_regress_simple_ols(ctx, n, x, y);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 zeroing for simple linear regression
 @tparam a.regress_simple ctx simple linear regression userdata
 @treturn a.regress_simple simple linear regression userdata
 @function zero
*/
int liba_regress_simple_zero(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_regress_simple_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_regress_simple_set(lua_State *L)
{
    a_regress_simple *const ctx = (a_regress_simple *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0D6147ED: // coef
    {
        ctx->coef = (a_float)luaL_checknumber(L, 3);
        break;
    }
    case 0x0D3D661D: // bias
    {
        ctx->bias = (a_float)luaL_checknumber(L, 3);
        break;
    }
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawset(L, 1);
    }
    return 0;
}

static int liba_regress_simple_get(lua_State *L)
{
    a_regress_simple const *const ctx = (a_regress_simple const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0D6147ED: // coef
        lua_pushnumber(L, (lua_Number)ctx->coef);
        break;
    case 0x0D3D661D: // bias
        lua_pushnumber(L, (lua_Number)ctx->bias);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_regress_simple_new);
        lua_num_set(L, -1, "coef", ctx->coef);
        lua_num_set(L, -1, "bias", ctx->bias);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_regress_simple_(lua_State *L)
{
    lua_pushcfunction(L, liba_regress_simple_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_regress_simple(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"init", liba_regress_simple_init},
        {"eval", liba_regress_simple_eval},
        {"evar", liba_regress_simple_evar},
        {"zero", liba_regress_simple_zero},
        {"ols_", liba_regress_simple_ols_},
        {"olsx", liba_regress_simple_olsx},
        {"olsy", liba_regress_simple_olsy},
        {"ols", liba_regress_simple_ols},
        {"new", liba_regress_simple_new},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_regress_simple_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_regress_simple_set},
        {"__index", liba_regress_simple_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.regress_simple");
    lua_registry_set(L, liba_regress_simple_new);

    return 1;
}
