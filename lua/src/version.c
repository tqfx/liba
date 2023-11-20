/***
 algorithm library version
 @module liba.version
*/

#include "version.h"
#include <string.h>

static int LMODULE(version_tostring)(lua_State *const L)
{
    a_version_s const *const ctx = (a_version_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_pushfstring(L, "%d.%d.%d", ctx->major, ctx->minor, ctx->patch);
        return 1;
    }
    return 0;
}

static int LMODULE(version_init_)(lua_State *const L, a_version_s *const ctx)
{
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 3:
        ctx->patch = (unsigned int)luaL_checkinteger(L, 3);
        A_FALLTHROUGH;
    case 2:
        ctx->minor = (unsigned int)luaL_checkinteger(L, 2);
        A_FALLTHROUGH;
    case 1:
        if (lua_type(L, 1) == LUA_TSTRING)
        {
            a_version_parse(ctx, lua_tostring(L, 1));
            break;
        }
        ctx->major = (unsigned int)luaL_checkinteger(L, 1);
        A_FALLTHROUGH;
    default:
        break;
    }
    return 1;
}

/***
 constructor for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn a.version algorithm library version userdata
 @function new
*/
int LMODULE(version_new)(lua_State *const L)
{
    a_version_s *const ctx = (a_version_s *)lua_newuserdata(L, sizeof(a_version_s));
    a_zero(ctx, sizeof(a_version_s));
    LMODULE2(version_meta_, L, 1);
    lua_setmetatable(L, -2);
    return LMODULE2(version_init_, L, ctx);
}

/***
 initialize function for algorithm library version
 @tparam a.version ctx algorithm library version userdata
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn a.version algorithm library version userdata
 @function init
*/
int LMODULE(version_init)(lua_State *const L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_version_s *const ctx = (a_version_s *)lua_touserdata(L, 1);
    return LMODULE2(version_init_, L, ctx);
}

/***
 algorithm library version parse
 @tparam a.version ctx algorithm library version userdata
 @tparam string version string to be parsed
 @treturn a.version algorithm library version userdata
 @function parse
*/
int LMODULE(version_parse)(lua_State *const L)
{
    a_version_s *const ctx = (a_version_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_version_parse(ctx, lua_tostring(L, 2));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

/***
 compare the version lhs with the version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer <0 version lhs < version rhs
 @treturn integer >0 version lhs > version rhs
 @treturn integer 0 version lhs == version rhs
 @function cmp
*/
int LMODULE(version_cmp)(lua_State *const L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    luaL_checktype(L, 2, LUA_TUSERDATA);
    a_version_s const *const lhs = (a_version_s const *)lua_touserdata(L, 1);
    a_version_s const *const rhs = (a_version_s const *)lua_touserdata(L, 2);
    lua_pushinteger(L, a_version_cmp(lhs, rhs));
    return 1;
}

/***
 algorithm library version check
 @tparam integer major required major number
 @tparam integer minor required minor number
 @tparam integer patch required patch number
 @treturn integer <0 library version is higher than required version
 @treturn integer >0 library version is lower than required version
 @treturn integer 0 library version is equal to required version
 @function check
*/
static int LMODULE(version_check)(lua_State *const L)
{
    a_version_s v = A_VERSION_C(0, 0, 0);
    switch (lua_gettop(L) & 0x3)
    {
    case 3:
        v.patch = (unsigned int)luaL_checkinteger(L, 3);
        A_FALLTHROUGH;
    case 2:
        v.minor = (unsigned int)luaL_checkinteger(L, 2);
        A_FALLTHROUGH;
    case 1:
        v.major = (unsigned int)luaL_checkinteger(L, 1);
        A_FALLTHROUGH;
    default:
        break;
    }
#undef a_version_check
    lua_pushinteger(L, a_version_check(v.major, v.minor, v.patch));
    return 1;
}

#undef FUNC
#define FUNC(func)                                              \
    int LMODULE(version_##func)(lua_State *const L)             \
    {                                                           \
        luaL_checktype(L, 1, LUA_TUSERDATA);                    \
        luaL_checktype(L, 2, LUA_TUSERDATA);                    \
        a_version_s *lhs = (a_version_s *)lua_touserdata(L, 1); \
        a_version_s *rhs = (a_version_s *)lua_touserdata(L, 2); \
        lua_pushboolean(L, a_version_##func(lhs, rhs));         \
        return 1;                                               \
    }
/***
 version lhs is less than version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function lt
*/
FUNC(lt)
/***
 version lhs is greater than version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function gt
*/
FUNC(gt)
/***
 version lhs is less than or equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function le
*/
FUNC(le)
/***
 version lhs is greater than or equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function ge
*/
FUNC(ge)
/***
 version lhs is equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function eq
*/
FUNC(eq)
/***
 version lhs is not equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn integer result of comparison
 @function ne
*/
FUNC(ne)
#undef FUNC

static int LMODULE(version_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_version_s *const ctx = (a_version_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x86720331: // major
        ctx->major = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0x87857C2D: // minor
        ctx->minor = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0xBB1DBE50: // patch
        ctx->patch = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0x0CD3E494: // __lt
    case 0x0CD3E485: // __le
    case 0x0CD3E0FC: // __eq
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
    case 0x5DA21A54: // __tostring
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int LMODULE(version_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_version_s const *const ctx = (a_version_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x86720331: // major
        lua_pushinteger(L, (lua_Integer)ctx->major);
        break;
    case 0x87857C2D: // minor
        lua_pushinteger(L, (lua_Integer)ctx->minor);
        break;
    case 0xBB1DBE50: // patch
        lua_pushinteger(L, (lua_Integer)ctx->patch);
        break;
    case 0xBB1D406B: // parse
        lua_pushcfunction(L, LMODULE(version_parse));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(version_init));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(version_new));
        break;
    case 0x001A24B2: // cmp
        lua_pushcfunction(L, LMODULE(version_cmp));
        break;
    case 0x000037B8: // lt
        lua_pushcfunction(L, LMODULE(version_lt));
        break;
    case 0x00003529: // gt
        lua_pushcfunction(L, LMODULE(version_gt));
        break;
    case 0x000037A9: // le
        lua_pushcfunction(L, LMODULE(version_le));
        break;
    case 0x0000351A: // ge
        lua_pushcfunction(L, LMODULE(version_ge));
        break;
    case 0x00003420: // eq
        lua_pushcfunction(L, LMODULE(version_eq));
        break;
    case 0x000038AF: // ne
        lua_pushcfunction(L, LMODULE(version_ne));
        break;
    case 0xA65758B2: // __index
    {
        l_int_s const enums[] = {
            {"major", (lua_Integer)ctx->major},
            {"minor", (lua_Integer)ctx->minor},
            {"patch", (lua_Integer)ctx->patch},
            {NULL, 0},
        };
        l_func_s const funcs[] = {
            {"parse", LMODULE(version_parse)},
            {"init", LMODULE(version_init)},
            {"new", LMODULE(version_new)},
            {"cmp", LMODULE(version_cmp)},
            {"lt", LMODULE(version_lt)},
            {"gt", LMODULE(version_gt)},
            {"le", LMODULE(version_le)},
            {"ge", LMODULE(version_ge)},
            {"eq", LMODULE(version_eq)},
            {"ne", LMODULE(version_ne)},
            {NULL, NULL},
        };
        lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
        l_int_reg(L, -1, enums);
        l_func_reg(L, -1, funcs);
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int LMODULE_(version, lua_State *const L)
{
    /***
     algorithm library version number
     @field MAJOR algorithm library version major
     @field MINOR algorithm library version minor
     @field PATCH algorithm library version patch
     @field TWEAK algorithm library version tweak
     @table liba.version
    */
    l_int_s const enums[] = {
        {"MAJOR", A_VERSION_MAJOR},
        {"MINOR", A_VERSION_MINOR},
        {"PATCH", A_VERSION_PATCH},
        {"TWEAK", A_VERSION_TWEAK},
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"check", LMODULE(version_check)},
        {"parse", LMODULE(version_parse)},
        {"init", LMODULE(version_init)},
        {"new", LMODULE(version_new)},
        {"cmp", LMODULE(version_cmp)},
        {"lt", LMODULE(version_lt)},
        {"gt", LMODULE(version_gt)},
        {"le", LMODULE(version_le)},
        {"ge", LMODULE(version_ge)},
        {"eq", LMODULE(version_eq)},
        {"ne", LMODULE(version_ne)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_PRI, LMODULE(version_tostring)},
        {L_FUN, LMODULE(version_init)},
        {L_GET, LMODULE(version_get)},
        {L_SET, LMODULE(version_set)},
        {L_EQ, LMODULE(version_eq)},
        {L_LT, LMODULE(version_lt)},
        {L_LE, LMODULE(version_le)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    l_str_set(L, -1, L_NAME, LMODULES("version"));
    l_func_reg(L, -1, metas);

    LMODULE2(version_meta_, L, 0);
    LMODULE2(version_func_, L, 0);

    return LMODULE2(version_func_, L, 1);
}

int LMODULE(version_func_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(version_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(version_func_));
    return 0;
}

int LMODULE(version_meta_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(version_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(version_meta_));
    return 0;
}
