/***
 quintic polynomial trajectory
 @module liba.trajpoly5
*/

#include "trajpoly5.h"
#include "a/trajpoly5.h"

static int liba_trajpoly5_gen_(lua_State *L, a_trajpoly5 *ctx, int arg, int top)
{
    a_float q0 = 0, v0 = 0, a0 = 0;
    a_float q1 = 0, v1 = 0, a1 = 0;
    a_float ts = 0;
    switch (top)
    {
    default:
    case 7:
        a1 = (a_float)luaL_checknumber(L, arg + 7);
        A_FALLTHROUGH;
    case 6:
        a0 = (a_float)luaL_checknumber(L, arg + 6);
        A_FALLTHROUGH;
    case 5:
        v1 = (a_float)luaL_checknumber(L, arg + 5);
        A_FALLTHROUGH;
    case 4:
        v0 = (a_float)luaL_checknumber(L, arg + 4);
        A_FALLTHROUGH;
    case 3:
        q1 = (a_float)luaL_checknumber(L, arg + 3);
        A_FALLTHROUGH;
    case 2:
        q0 = (a_float)luaL_checknumber(L, arg + 2);
        A_FALLTHROUGH;
    case 1:
        ts = (a_float)luaL_checknumber(L, arg + 1);
        A_FALLTHROUGH;
    case 0:
        a_trajpoly5_gen(ctx, ts, q0, q1, v0, v1, a0, a1);
    }
    return 1;
}

/***
 constructor for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.trajpoly5 quintic polynomial trajectory userdata
 @function new
*/
int liba_trajpoly5_new(lua_State *L)
{
    int const top = lua_gettop(L);
    if (top > 2)
    {
        a_trajpoly5 *const ctx = lua_newclass(L, a_trajpoly5);
        lua_registry_get(L, liba_trajpoly5_new);
        lua_setmetatable(L, -2);
        return liba_trajpoly5_gen_(L, ctx, 0, top);
    }
    return 0;
}

/***
 generate for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number ts difference between final time and initial time
 @tparam number q0 initial position
 @tparam number q1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.trajpoly5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly5_gen(lua_State *L)
{
    int const top = lua_gettop(L);
    if (top > 3)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_trajpoly5 *const ctx = (a_trajpoly5 *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        return liba_trajpoly5_gen_(L, ctx, 1, top - 1);
    }
    return 0;
}

/***
 calculate position for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly5_pos(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate velocity for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly5_vel(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate acceleration for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly5_acc(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_acc(ctx, dt));
        return 1;
    }
    return 0;
}

static int liba_trajpoly5_set(lua_State *L)
{
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xE8859EEB: // __name
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

static int liba_trajpoly5_get(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00000071: // q
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        break;
    case 0x00000076: // v
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        break;
    case 0x00000061: // a
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_trajpoly5_new);
        lua_pushstring(L, "q");
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        lua_rawset(L, -3);
        lua_pushstring(L, "v");
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        lua_rawset(L, -3);
        lua_pushstring(L, "a");
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_trajpoly5_(lua_State *L)
{
    lua_pushcfunction(L, liba_trajpoly5_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_trajpoly5(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_trajpoly5_new},
        {"gen", liba_trajpoly5_gen},
        {"pos", liba_trajpoly5_pos},
        {"vel", liba_trajpoly5_vel},
        {"acc", liba_trajpoly5_acc},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_trajpoly5_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_trajpoly5_set},
        {"__index", liba_trajpoly5_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.trajpoly5");
    lua_registry_set(L, liba_trajpoly5_new);

    return 1;
}
