/***
 hepta polynomial trajectory
 @module liba.polytraj7
*/

#include "polytraj7.h"
#include "a/polytraj7.h"

static int liba_polytraj7_gen_(lua_State *L, a_polytraj7 *ctx, int arg, int top)
{
    a_float q0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_float q1 = 0, v1 = 0, a1 = 0, j1 = 0;
    a_float ts = 0;
    switch (top)
    {
    default:
    case 9:
        j1 = (a_float)luaL_checknumber(L, arg + 9);
        A_FALLTHROUGH;
    case 8:
        j0 = (a_float)luaL_checknumber(L, arg + 8);
        A_FALLTHROUGH;
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
    case 0:;
    }
    a_polytraj7_gen(ctx, ts, q0, q1, v0, v1, a0, a1, j0, j1);
    return 1;
}

/***
 constructor for hepta polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj7 hepta polynomial trajectory userdata
 @function new
*/
int liba_polytraj7_new(lua_State *L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 1);
    if (top > 2 && type == LUA_TNUMBER)
    {
        a_polytraj7 *const ctx = lua_newclass(L, a_polytraj7);
        lua_registry_get(L, liba_polytraj7_new);
        lua_setmetatable(L, -2);
        return liba_polytraj7_gen_(L, ctx, 0, top);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_float source[5] = {0};
        a_float target[5] = {0};
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_array_num_get(L, 1, source, A_LEN(source));
        lua_array_num_get(L, 2, target, A_LEN(target));
        a_polytraj7 *const ctx = lua_newclass(L, a_polytraj7);
        lua_registry_get(L, liba_polytraj7_new);
        lua_setmetatable(L, -2);
        a_polytraj7_gen(ctx, target[0] - source[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3],
                        source[4], target[4]);
        return 1;
    }
    return 0;
}

/***
 generate for hepta polynomial trajectory
 @tparam a.polytraj7 ctx hepta polynomial trajectory userdata
 @tparam number ts difference between final time and initial time
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj7 hepta polynomial trajectory userdata
 @function gen
*/
int liba_polytraj7_gen(lua_State *L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 2);
    if (top > 3 && type == LUA_TNUMBER)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytraj7 *const ctx = (a_polytraj7 *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        return liba_polytraj7_gen_(L, ctx, 1, top - 1);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_float source[5] = {0};
        a_float target[5] = {0};
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_polytraj7 *const ctx = (a_polytraj7 *)lua_touserdata(L, 1);
        lua_array_num_get(L, 2, source, A_LEN(source));
        lua_array_num_get(L, 3, target, A_LEN(target));
        a_polytraj7_gen(ctx, target[0] - source[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3],
                        source[4], target[4]);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for hepta polynomial trajectory position
 @tparam a.polytraj7 ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj7_pos(lua_State *L)
{
    a_polytraj7 const *const ctx = (a_polytraj7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj7_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for hepta polynomial trajectory velocity
 @tparam a.polytraj7 ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj7_vel(lua_State *L)
{
    a_polytraj7 const *const ctx = (a_polytraj7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj7_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for hepta polynomial trajectory acceleration
 @tparam a.polytraj7 ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj7_acc(lua_State *L)
{
    a_polytraj7 const *const ctx = (a_polytraj7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj7_acc(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for hepta polynomial trajectory jerk
 @tparam a.polytraj7 ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_polytraj7_jer(lua_State *L)
{
    a_polytraj7 const *const ctx = (a_polytraj7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj7_jer(ctx, dt));
        return 1;
    }
    return 0;
}

static int liba_polytraj7_set(lua_State *L)
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

static int liba_polytraj7_get(lua_State *L)
{
    a_polytraj7 const *const ctx = (a_polytraj7 const *)lua_touserdata(L, 1);
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
    case 0x0000006A: // j
        lua_array_num_new(L, ctx->j, A_LEN(ctx->j));
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_polytraj7_new);
        lua_pushstring(L, "q");
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        lua_rawset(L, -3);
        lua_pushstring(L, "v");
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        lua_rawset(L, -3);
        lua_pushstring(L, "a");
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        lua_rawset(L, -3);
        lua_pushstring(L, "j");
        lua_array_num_new(L, ctx->j, A_LEN(ctx->j));
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_polytraj7_(lua_State *L)
{
    lua_pushcfunction(L, liba_polytraj7_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_polytraj7(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_polytraj7_new},
        {"gen", liba_polytraj7_gen},
        {"pos", liba_polytraj7_pos},
        {"vel", liba_polytraj7_vel},
        {"acc", liba_polytraj7_acc},
        {"jer", liba_polytraj7_jer},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_polytraj7_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_polytraj7_set},
        {"__index", liba_polytraj7_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.polytraj7");
    lua_registry_set(L, liba_polytraj7_new);

    return 1;
}
