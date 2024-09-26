/***
 algorithm library
 @module liba
*/

#include "a.h"

/***
 a hash function whose prime number is 131
 @tparam string str string to be processed
 @tparam[opt] integer initial value
 @treturn string hash value
 @function hash_bkdr
*/
static int liba_hash_bkdr(lua_State *L)
{
    a_u32 val = 0;
    int top = lua_gettop(L);
    if (top > 1) { val = lua_u32_get(L, 2); }
    if (top > 0) { val = a_hash_bkdr(luaL_checklstring(L, 1, A_NULL), val); }
    lua_u32_new(L, val);
    return 1;
}

/***
 a hash function whose prime number is 65599
 @tparam string str string to be processed
 @tparam[opt] integer initial value
 @treturn string hash value
 @function hash_sdbm
*/
static int liba_hash_sdbm(lua_State *L)
{
    a_u32 val = 0;
    int top = lua_gettop(L);
    if (top > 1) { val = lua_u32_get(L, 2); }
    if (top > 0) { val = a_hash_sdbm(luaL_checklstring(L, 1, A_NULL), val); }
    lua_u32_new(L, val);
    return 1;
}

#include "a/math.h"

/***
 square root of an unsigned integer
 @tparam integer ... independent variables
 @treturn integer calculated result
 @function isqrt
*/
static int liba_isqrt(lua_State *L)
{
    int const Ln = lua_gettop(L);
    for (int Li = 1; Li <= Ln; ++Li)
    {
        lua_Integer x = luaL_checkinteger(L, Li);
#if A_SIZE_MAX == A_U32_MAX
        x = (lua_Integer)a_u32_sqrt((a_u32)x);
#else /* !A_SIZE_MAX */
        x = (lua_Integer)a_u64_sqrt((a_u64)x);
#endif /* A_SIZE_MAX */
        lua_pushinteger(L, x);
    }
    return Ln;
}

/***
 reciprocal of square-root
 @tparam number ... independent variables
 @treturn number calculated result
 @function rsqrt
*/
static int liba_rsqrt(lua_State *L)
{
    int const Ln = lua_gettop(L);
    for (int Li = 1; Li <= Ln; ++Li)
    {
        lua_Number x = luaL_checknumber(L, Li);
#if A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        x = (lua_Number)a_f64_rsqrt((a_f64)x);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        x = (lua_Number)a_f32_rsqrt((a_f32)x);
#else /* !A_FLOAT_TYPE */
        x = (lua_Number)(1 / sqrt((double)x));
#endif /* A_FLOAT_TYPE */
        lua_pushnumber(L, x);
    }
    return Ln;
}

#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */

int luaopen_liba(lua_State *L)
{
    luaL_checkversion(L);
    /***
     algorithm library
     @field VERSION algorithm library version string
     @table liba
    */
    static lua_fun const funcs[] = {
        {"hash_bkdr", liba_hash_bkdr},
        {"hash_sdbm", liba_hash_sdbm},
        {"isqrt", liba_isqrt},
        {"rsqrt", liba_rsqrt},
    };
#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
    lua_fun func = {NULL, NULL};
    luaL_register(L, "liba", &func);
#else /* !LUA_VERSION_NUM */
    lua_createtable(L, 0, A_LEN(funcs) + 1);
#endif /* LUA_VERSION_NUM */
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "VERSION", A_VERSION);

    lua_pushstring(L, "complex");
    luaopen_liba_complex(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "crc16");
    luaopen_liba_crc16(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "crc32");
    luaopen_liba_crc32(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "crc64");
    luaopen_liba_crc64(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "crc8");
    luaopen_liba_crc8(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "hpf");
    luaopen_liba_hpf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "lpf");
    luaopen_liba_lpf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "mf");
    luaopen_liba_mf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid");
    luaopen_liba_pid(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid_fuzzy");
    luaopen_liba_pid_fuzzy(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid_neuro");
    luaopen_liba_pid_neuro(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "regress_simple");
    luaopen_liba_regress_simple(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "tf");
    luaopen_liba_tf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "trajbell");
    luaopen_liba_trajbell(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "trajpoly3");
    luaopen_liba_trajpoly3(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "trajpoly5");
    luaopen_liba_trajpoly5(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "trajpoly7");
    luaopen_liba_trajpoly7(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "trajtrap");
    luaopen_liba_trajtrap(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "version");
    luaopen_liba_version(L);
    lua_rawset(L, -3);

    return 1;
}
