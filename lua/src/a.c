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
static int liba_hash_bkdr(lua_State *const L)
{
    a_umax_t val = 0;
    int const Ln = lua_gettop(L);
    for (int Li = 1; Li <= Ln; ++Li)
    {
        val = a_hash_bkdr(luaL_checklstring(L, Li, A_NULL), val);
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
static int liba_rsqrt(lua_State *const L)
{
    int Li;
    int const Ln = lua_gettop(L);
    for (Li = 1; Li <= Ln; ++Li)
    {
        lua_Number x = luaL_checknumber(L, Li);
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        x = (lua_Number)a_f32_rsqrt((a_f32_t)x);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        x = (lua_Number)a_f64_rsqrt((a_f64_t)x);
#else /* !A_FLOAT_TYPE */
        x = (lua_Number)(1 / sqrt((double)x));
#endif /* A_FLOAT_TYPE */
        lua_pushnumber(L, x);
    }
    return 1 + Ln - Li;
}

static lua_State *liba_L = A_NULL;
static void *liba_alloc(void *const addr, a_size_t const size)
{
    return l_alloc(liba_L, addr, size);
}

int luaopen_liba(lua_State *const L)
{
    luaL_checkversion(L);
    a_alloc = liba_alloc;
    liba_L = L;

    /***
     algorithm library
     @field VERSION algorithm library version string
     @table liba
    */
    l_func_s const funcs[] = {
        {"hash_bkdr", liba_hash_bkdr},
        {"rsqrt", liba_rsqrt},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    l_str_set(L, -1, "VERSION", A_VERSION);
    l_func_reg(L, -1, funcs);

    lua_pushstring(L, "mf");
    luaopen_liba_mf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "tf");
    luaopen_liba_tf(L);
    lua_rawset(L, -3);

    luaopen_liba_pid(L);
    lua_pushstring(L, "pid");
    lua_pushvalue(L, -2);
    lua_rawset(L, -4);
    {
        lua_pushstring(L, "fuzzy");
        luaopen_liba_pid_fuzzy(L);
        lua_rawset(L, -3);

        lua_pushstring(L, "neuron");
        luaopen_liba_pid_neuron(L);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);

    lua_pushstring(L, "complex");
    luaopen_liba_complex(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack3");
    luaopen_liba_polytrack3(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack5");
    luaopen_liba_polytrack5(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack7");
    luaopen_liba_polytrack7(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "version");
    luaopen_liba_version(L);
    lua_rawset(L, -3);

    return 1;
}

#include <stdio.h>
#include <inttypes.h>

int liba_setter(lua_State *const L)
{
    char h[11];
    char const *const s = lua_tostring(L, 2);
    (void)snprintf(h, 11, "0x%08" PRIX32, (a_u32_t)a_hash_bkdr(s, 0));
    return luaL_error(L, "field(%s) '%s' missing in setter", h, s);
}
