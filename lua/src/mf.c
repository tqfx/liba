/***
 membership function
 @module liba.mf
*/

#include "a.h"
#include "a/mf.h"

/***
 gaussian membership function
 @tparam number x any element
 @tparam number sigma sigma
 @tparam number c c
 @treturn number membership
 @function gauss
*/
static int LMODULE(mf_gauss)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const sigma = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_gauss(x, sigma, c));
    return 1;
}

/***
 generalized bell-shaped membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @treturn number membership
 @function gbell
*/
static int LMODULE(mf_gbell)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const a = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const b = (a_float_t)luaL_checknumber(L, 3);
    a_float_t const c = (a_float_t)luaL_checknumber(L, 4);
    lua_pushnumber(L, (lua_Number)a_mf_gbell(x, a, b, c));
    return 1;
}

/***
 sigmoidal membership function
 @tparam number x any element
 @tparam number a a
 @tparam number c c
 @treturn number membership
 @function sig
*/
static int LMODULE(mf_sig)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const a = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_sig(x, a, c));
    return 1;
}

/***
 trapezoidal membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @tparam number d d
 @treturn number membership
 @function trap
*/
static int LMODULE(mf_trap)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const a = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const b = (a_float_t)luaL_checknumber(L, 3);
    a_float_t const c = (a_float_t)luaL_checknumber(L, 4);
    a_float_t const d = (a_float_t)luaL_checknumber(L, 5);
    lua_pushnumber(L, (lua_Number)a_mf_trap(x, a, b, c, d));
    return 1;
}

/***
 triangular membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @treturn number membership
 @function tri
*/
static int LMODULE(mf_tri)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const a = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const b = (a_float_t)luaL_checknumber(L, 3);
    a_float_t const c = (a_float_t)luaL_checknumber(L, 4);
    lua_pushnumber(L, (lua_Number)a_mf_tri(x, a, b, c));
    return 1;
}

/***
 z-shaped membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @treturn number membership
 @function z
*/
static int LMODULE(mf_z)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_float_t const x = (a_float_t)luaL_checknumber(L, 1);
    a_float_t const a = (a_float_t)luaL_checknumber(L, 2);
    a_float_t const b = (a_float_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_z(x, a, b));
    return 1;
}

/***
 membership function
 @tparam int e type for membership function
 @tparam number x any element
 @tparam number ... paramarrays
 @treturn number membership
 @function mf
*/
static int LMODULE(mf)(lua_State *const L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    lua_Integer const e = luaL_checkinteger(L, 1);
    lua_remove(L, 1);
    switch (e)
    {
    case A_MF_GAUSS:
        return LMODULE(mf_gauss)(L);
    case A_MF_GBELL:
        return LMODULE(mf_gbell)(L);
    case A_MF_SIG:
        return LMODULE(mf_sig)(L);
    case A_MF_TRAP:
        return LMODULE(mf_trap)(L);
    case A_MF_TRI:
        return LMODULE(mf_tri)(L);
    case A_MF_Z:
        return LMODULE(mf_z)(L);
    case A_MF_NUL:
    default:
        return 0;
    }
}

/***
 type for membership function
 @field NUL none
 @field GAUSS gaussian membership function
 @field GBELL generalized bell-shaped membership function
 @field SIG sigmoidal membership function
 @field TRAP trapezoidal membership function
 @field TRI triangular membership function
 @field Z z-shaped membership function
 @table mf
*/
int LMODULE_(mf, lua_State *const L)
{
    l_int_s const enums[] = {
        {"NUL", A_MF_NUL},
        {"GAUSS", A_MF_GAUSS},
        {"GBELL", A_MF_GBELL},
        {"SIG", A_MF_SIG},
        {"TRAP", A_MF_TRAP},
        {"TRI", A_MF_TRI},
        {"Z", A_MF_Z},
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"gauss", LMODULE(mf_gauss)},
        {"gbell", LMODULE(mf_gbell)},
        {"sig", LMODULE(mf_sig)},
        {"trap", LMODULE(mf_trap)},
        {"tri", LMODULE(mf_tri)},
        {"z", LMODULE(mf_z)},
        {NULL, NULL},
    };
    l_func_s const metas[] = {
        {"__call", LMODULE(mf)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(enums) + L_COUNT(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, L_COUNT(metas) - 1);
    l_func_reg(L, -1, metas);
    lua_setmetatable(L, -2);
    return 1;
}
