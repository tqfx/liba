/***
 hepta polynomial trajectory
 @module liba.trajpoly7
*/

#include "trajpoly7.h"
#include "a/trajpoly7.h"

static int liba_trajpoly7_gen_(lua_State *L, a_trajpoly7 *ctx, int arg, int top)
{
    a_float p0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_float p1 = 0, v1 = 0, a1 = 0, j1 = 0;
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
        p1 = (a_float)luaL_checknumber(L, arg + 3);
        A_FALLTHROUGH;
    case 2:
        p0 = (a_float)luaL_checknumber(L, arg + 2);
        A_FALLTHROUGH;
    case 1:
        ts = (a_float)luaL_checknumber(L, arg + 1);
        A_FALLTHROUGH;
    case 0:
        if (ctx == NULL)
        {
            ctx = lua_newclass(L, a_trajpoly7);
            lua_registry_get(L, liba_trajpoly7_new);
            lua_setmetatable(L, -2);
        }
        a_trajpoly7_gen(ctx, ts, p0, p1, v0, v1, a0, a1, j0, j1);
    }
    return 1;
}

/***
 constructor for hepta polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @tparam[opt] number j0 initial jerk
 @tparam[opt] number j1 final jerk
 @treturn a.trajpoly7 hepta polynomial trajectory userdata
 @function new
*/
int liba_trajpoly7_new(lua_State *L)
{
    int const top = lua_gettop(L);
    liba_trajpoly7_gen_(L, NULL, 0, top > 2 ? top : 3);
    return 1;
}

/***
 generate for hepta polynomial trajectory
 @tparam a.trajpoly7 ctx hepta polynomial trajectory userdata
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @tparam[opt] number j0 initial jerk
 @tparam[opt] number j1 final jerk
 @treturn a.trajpoly7 hepta polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly7_gen(lua_State *L)
{
    a_trajpoly7 *const ctx = (a_trajpoly7 *)lua_touserdata(L, 1);
    if (ctx)
    {
        int const top = lua_gettop(L);
        liba_trajpoly7_gen_(L, ctx, 1, top > 3 ? top - 1 : 3);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate position for hepta polynomial trajectory
 @tparam a.trajpoly7 ctx hepta polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly7_pos(lua_State *L)
{
    a_trajpoly7 const *const ctx = (a_trajpoly7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly7_pos(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate velocity for hepta polynomial trajectory
 @tparam a.trajpoly7 ctx hepta polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly7_vel(lua_State *L)
{
    a_trajpoly7 const *const ctx = (a_trajpoly7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly7_vel(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate acceleration for hepta polynomial trajectory
 @tparam a.trajpoly7 ctx hepta polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly7_acc(lua_State *L)
{
    a_trajpoly7 const *const ctx = (a_trajpoly7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly7_acc(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate jerk for hepta polynomial trajectory
 @tparam a.trajpoly7 ctx hepta polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_trajpoly7_jer(lua_State *L)
{
    a_trajpoly7 const *const ctx = (a_trajpoly7 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly7_jer(ctx, x));
        return 1;
    }
    return 0;
}

static int liba_trajpoly7_set(lua_State *L)
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

static int liba_trajpoly7_get(lua_State *L)
{
    a_trajpoly7 const *const ctx = (a_trajpoly7 const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00000070: // p
        lua_array_num_new(L, ctx->p, A_LEN(ctx->p));
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
        lua_registry_get(L, liba_trajpoly7_new);
        lua_pushstring(L, "p");
        lua_array_num_new(L, ctx->p, A_LEN(ctx->p));
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

static int liba_trajpoly7_(lua_State *L)
{
    lua_pushcfunction(L, liba_trajpoly7_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_trajpoly7(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_trajpoly7_new},
        {"gen", liba_trajpoly7_gen},
        {"pos", liba_trajpoly7_pos},
        {"vel", liba_trajpoly7_vel},
        {"acc", liba_trajpoly7_acc},
        {"jer", liba_trajpoly7_jer},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_trajpoly7_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_trajpoly7_set},
        {"__index", liba_trajpoly7_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.trajpoly7");
    lua_registry_set(L, liba_trajpoly7_new);

    return 1;
}
