/***
 algorithm library version
 @module liba.version
*/

#include "version.h"
#include "a/version.h"

static int liba_version_tostring(lua_State *L)
{
    a_version const *const ctx = (a_version const *)lua_touserdata(L, 1);
    if (ctx)
    {
        char str[48];
        a_version_tostr(ctx, str, sizeof(str));
        lua_pushstring(L, str);
        return 1;
    }
    return 0;
}

static int liba_version_init_(lua_State *L, a_version *ctx, int arg, int top)
{
    unsigned int major = 0, minor = 0, third = 0, extra = 0;
    char const *str = NULL;
    switch (top)
    {
    default:
    case 4:
        extra = (unsigned int)luaL_checkinteger(L, arg + 4);
        A_FALLTHROUGH;
    case 3:
        third = (unsigned int)luaL_checkinteger(L, arg + 3);
        A_FALLTHROUGH;
    case 2:
        minor = (unsigned int)luaL_checkinteger(L, arg + 2);
        A_FALLTHROUGH;
    case 1:
        if (lua_type(L, arg + 1) == LUA_TSTRING)
        {
            str = lua_tostring(L, arg + 1);
            break;
        }
        major = (unsigned int)luaL_checkinteger(L, arg + 1);
        A_FALLTHROUGH;
    case 0:;
    }
    if (ctx == NULL)
    {
        ctx = lua_newclass(L, a_version);
        lua_registry_get(L, liba_version_new);
        lua_setmetatable(L, -2);
    }
    ctx->alpha_[0] = '.';
    ctx->alpha_[1] = 0;
    ctx->alpha_[2] = 0;
    ctx->alpha_[3] = 0;
    if (str != NULL)
    {
        a_version_parse(ctx, str);
    }
    else
    {
        ctx->major = major;
        ctx->minor = minor;
        ctx->third = third;
        ctx->extra = extra;
    }
    return 1;
}

/***
 constructor for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer third version third number
 @tparam[opt] integer extra version extra number
 @treturn a.version algorithm library version userdata
 @function new
*/
int liba_version_new(lua_State *L)
{
    liba_version_init_(L, NULL, 0, lua_gettop(L));
    return 1;
}

/***
 initialize for algorithm library version
 @tparam a.version ctx algorithm library version userdata
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer third version third number
 @tparam[opt] integer extra version extra number
 @treturn a.version algorithm library version userdata
 @function init
*/
int liba_version_init(lua_State *L)
{
    a_version *const ctx = (a_version *)lua_touserdata(L, 1);
    if (ctx)
    {
        liba_version_init_(L, ctx, 1, lua_gettop(L) - 1);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 parse version string to version
 @tparam a.version ctx algorithm library version userdata
 @tparam string version string to be parsed
 @treturn a.version algorithm library version userdata
 @function parse
*/
int liba_version_parse(lua_State *L)
{
    a_version *const ctx = (a_version *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_version_parse(ctx, lua_tostring(L, 2));
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
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
static int liba_version_check(lua_State *L)
{
    a_version v = A_VERSION_0();
    switch (lua_gettop(L) & 0x3)
    {
    case 3:
        v.third = (unsigned int)luaL_checkinteger(L, 3);
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
    lua_pushinteger(L, a_version_check(v.major, v.minor, v.third));
    return 1;
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
int liba_version_cmp(lua_State *L)
{
    a_version const *lhs, *rhs;
    luaL_checktype(L, 1, LUA_TUSERDATA);
    luaL_checktype(L, 2, LUA_TUSERDATA);
    lhs = (a_version const *)lua_touserdata(L, 1);
    rhs = (a_version const *)lua_touserdata(L, 2);
    lua_pushinteger(L, a_version_cmp(lhs, rhs));
    return 1;
}

#undef F2
#define F2(func)                                        \
    int liba_version_##func(lua_State *L)               \
    {                                                   \
        a_version const *lhs, *rhs;                     \
        luaL_checktype(L, 1, LUA_TUSERDATA);            \
        luaL_checktype(L, 2, LUA_TUSERDATA);            \
        lhs = (a_version const *)lua_touserdata(L, 1);  \
        rhs = (a_version const *)lua_touserdata(L, 2);  \
        lua_pushboolean(L, a_version_##func(lhs, rhs)); \
        return 1;                                       \
    }
/***
 version lhs is less than version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function lt
*/
F2(lt)
/***
 version lhs is greater than version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function gt
*/
F2(gt)
/***
 version lhs is less than or equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function le
*/
F2(le)
/***
 version lhs is greater than or equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function ge
*/
F2(ge)
/***
 version lhs is equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function eq
*/
F2(eq)
/***
 version lhs is not equal to version rhs
 @tparam a.version lhs version userdata on the left
 @tparam a.version rhs version userdata on the right
 @treturn bool result of comparison
 @function ne
*/
F2(ne)

static int liba_version_set(lua_State *L)
{
    a_version *const ctx = (a_version *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x86720331: /* major */
        ctx->major = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0x87857C2D: /* minor */
        ctx->minor = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0x0241DD17: /* third */
        ctx->third = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0xFD1BE968: /* extra */
        ctx->extra = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0xB5485B9E: /* alpha */
    {
        char const *alpha = luaL_checklstring(L, 3, 0);
        a_version_set_alpha(ctx, alpha);
        break;
    }
    case 0x0CD3E494: /* __lt */
    case 0x0CD3E485: /* __le */
    case 0x0CD3E0FC: /* __eq */
    case 0xE8859EEB: /* __name */
    case 0xE70C48C6: /* __call */
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

static int liba_version_get(lua_State *L)
{
    a_version const *const ctx = (a_version const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x86720331: /* major */
        lua_pushinteger(L, (lua_Integer)ctx->major);
        break;
    case 0x87857C2D: /* minor */
        lua_pushinteger(L, (lua_Integer)ctx->minor);
        break;
    case 0x0241DD17: /* third */
        lua_pushinteger(L, (lua_Integer)ctx->third);
        break;
    case 0xFD1BE968: /* extra */
        lua_pushinteger(L, (lua_Integer)ctx->extra);
        break;
    case 0xB5485B9E: /* alpha */
    {
        char alpha[sizeof(ctx->alpha_) + 1];
        a_version_alpha(ctx, alpha);
        lua_pushstring(L, alpha);
        break;
    }
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_version_new);
        lua_int_set(L, -1, "major", (lua_Integer)ctx->major);
        lua_int_set(L, -1, "minor", (lua_Integer)ctx->minor);
        lua_int_set(L, -1, "third", (lua_Integer)ctx->third);
        lua_int_set(L, -1, "extra", (lua_Integer)ctx->extra);
        lua_str_set(L, -1, "alpha", ".");
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_version_(lua_State *L)
{
    lua_pushcfunction(L, liba_version_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_version(lua_State *L)
{
    /***
     algorithm library version number
     @field MAJOR algorithm library version major
     @field MINOR algorithm library version minor
     @field PATCH algorithm library version patch
     @field TWEAK algorithm library version tweak
     @table liba.version
    */
    static lua_int const enums[] = {
        {"MAJOR", A_VERSION_MAJOR},
        {"MINOR", A_VERSION_MINOR},
        {"PATCH", A_VERSION_PATCH},
        {"TWEAK", A_VERSION_TWEAK},
    };
    static lua_fun const funcs[] = {
        {"check", liba_version_check},
        {"parse", liba_version_parse},
        {"init", liba_version_init},
        {"new", liba_version_new},
        {"cmp", liba_version_cmp},
        {"lt", liba_version_lt},
        {"gt", liba_version_gt},
        {"le", liba_version_le},
        {"ge", liba_version_ge},
        {"eq", liba_version_eq},
        {"ne", liba_version_ne},
    };
    static lua_fun const metas[] = {
        {"__tostring", liba_version_tostring},
        {"__newindex", liba_version_set},
        {"__index", liba_version_get},
        {"__call", liba_version_init},
        {"__eq", liba_version_eq},
        {"__lt", liba_version_lt},
        {"__le", liba_version_le},
    };

    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs));
    lua_int_reg(L, -1, enums, A_LEN(enums));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_version_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs));
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs + 1, A_LEN(funcs) - 1);
    lua_str_set(L, -1, "__name", "a.version");
    lua_registry_set(L, liba_version_new);

    return 1;
}
