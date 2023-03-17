/***
 algorithm library
 @module liba
*/

#include "a.h"
#include "a/math.h"
#include "a/version.h"

/***
 Brian Kernighan and Dennis Ritchie
 @tparam number str string to be processed
 @treturn integer hash value
 @function hash_bkdr
*/
static int LMODULE(hash_bkdr)(lua_State *const L)
{
    a_umax_t val = 0;
    int const n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        if (lua_type(L, i) == LUA_TSTRING)
        {
            val = a_hash_bkdr(lua_tostring(L, i), val);
        }
    }
    lua_pushinteger(L, (lua_Integer)val);
    return 1;
}

/***
 fast inverse square-root
 @tparam number x independent variable
 @tparam number ... independent variables
 @treturn number calculated result
 @function rsqrt
*/
static int LMODULE(rsqrt)(lua_State *const L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    int const n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        lua_Number x = luaL_checknumber(L, i);
#if A_REAL_TYPE == A_REAL_SINGLE
        x = (lua_Number)a_f32_rsqrt((a_f32_t)x);
#elif A_REAL_TYPE == A_REAL_DOUBLE
        x = (lua_Number)a_f64_rsqrt((a_f64_t)x);
#else /* !A_REAL_TYPE */
        x = (lua_Number)(1 / sqrt((double)x));
#endif /* A_REAL_TYPE */
        lua_pushnumber(L, x);
    }
    return n;
}

static lua_State *LMODULE(L) = A_NULL;
static a_vptr_t LMODULE(alloc)(a_vptr_t const vptr, a_size_t const size)
{
    return l_alloc(LMODULE(L), vptr, size);
}

int LMODULE0(lua_State *const L)
{
    LMODULE(L) = L;
    luaL_checkversion(L);
    a_alloc_reg(LMODULE(alloc));

    l_func_s const funcs[] = {
        {"hash_bkdr", LMODULE(hash_bkdr)},
        {"rsqrt", LMODULE(rsqrt)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(funcs));
    l_str_set(L, -1, "VERSION", A_VERSION);
    l_func_reg(L, -1, funcs);

    lua_pushstring(L, "mf");
    LMODULE_(mf, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "tf");
    LMODULE_(tf, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid");
    LMODULE_(pid, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "fpid");
    LMODULE_(fpid, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "complex");
    LMODULE_(complex, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack3");
    LMODULE_(polytrack3, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack5");
    LMODULE_(polytrack5, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack7");
    LMODULE_(polytrack7, L);
    lua_rawset(L, -3);

    lua_pushstring(L, "version");
    LMODULE_(version, L);
    lua_rawset(L, -3);

    return 1;
}

#include <stdio.h>
#include <inttypes.h>

int LMODULE(setter)(lua_State *const L)
{
    char h[11];
    char const *const s = lua_tostring(L, 2);
    (void)snprintf(h, 11, "0x%08" PRIX32, (a_u32_t)a_hash_bkdr(s, 0));
    return luaL_error(L, "field(%s) '%s' missing in setter", h, s);
}
