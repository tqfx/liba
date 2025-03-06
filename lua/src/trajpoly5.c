/***
 quintic polynomial trajectory
 @module liba.trajpoly5
*/

#include "trajpoly5.h"
#include "a/trajpoly5.h"

static int liba_trajpoly5_gen_(lua_State *L, a_trajpoly5 *ctx, int arg, int top)
{
    a_real p0 = 0, v0 = 0, a0 = 0;
    a_real p1 = 0, v1 = 0, a1 = 0;
    a_real ts = 0;
    switch (top)
    {
    default:
    case 7:
        a1 = (a_real)luaL_checknumber(L, arg + 7);
        A_FALLTHROUGH;
    case 6:
        a0 = (a_real)luaL_checknumber(L, arg + 6);
        A_FALLTHROUGH;
    case 5:
        v1 = (a_real)luaL_checknumber(L, arg + 5);
        A_FALLTHROUGH;
    case 4:
        v0 = (a_real)luaL_checknumber(L, arg + 4);
        A_FALLTHROUGH;
    case 3:
        p1 = (a_real)luaL_checknumber(L, arg + 3);
        A_FALLTHROUGH;
    case 2:
        p0 = (a_real)luaL_checknumber(L, arg + 2);
        A_FALLTHROUGH;
    case 1:
        ts = (a_real)luaL_checknumber(L, arg + 1);
        A_FALLTHROUGH;
    case 0:
        if (ctx == NULL)
        {
            ctx = lua_newclass(L, a_trajpoly5);
            lua_registry_get(L, liba_trajpoly5_new);
            lua_setmetatable(L, -2);
        }
        a_trajpoly5_gen(ctx, ts, p0, p1, v0, v1, a0, a1);
    }
    return 1;
}

/***
 constructor for quintic polynomial trajectory
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
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
    liba_trajpoly5_gen_(L, NULL, 0, top > 2 ? top : 3);
    return 1;
}

/***
 generate for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number ts difference between final time and initial time
 @tparam number p0 initial position
 @tparam number p1 final position
 @tparam[opt] number v0 initial velocity
 @tparam[opt] number v1 final velocity
 @tparam[opt] number a0 initial acceleration
 @tparam[opt] number a1 final acceleration
 @treturn a.trajpoly5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_trajpoly5_gen(lua_State *L)
{
    a_trajpoly5 *const ctx = (a_trajpoly5 *)lua_touserdata(L, 1);
    if (ctx)
    {
        int const top = lua_gettop(L);
        liba_trajpoly5_gen_(L, ctx, 1, top > 3 ? top - 1 : 3);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 compute position for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajpoly5_pos(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_pos(ctx, x));
        return 1;
    }
    return 0;
}

/***
 compute velocity for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajpoly5_vel(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_vel(ctx, x));
        return 1;
    }
    return 0;
}

/***
 compute acceleration for quintic polynomial trajectory
 @tparam a.trajpoly5 ctx quintic polynomial trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajpoly5_acc(lua_State *L)
{
    a_trajpoly5 const *const ctx = (a_trajpoly5 const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajpoly5_acc(ctx, x));
        return 1;
    }
    return 0;
}

static int liba_trajpoly5_set(lua_State *L)
{
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xE8859EEB: /* __name */
    case 0xA65758B2: /* __index */
    case 0xAEB551C6: /* __newindex */
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
    a_real c[A_LEN(ctx->c) - 1];
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x000032D9: /* c0 */
        lua_array_num_new(L, ctx->c, A_LEN(ctx->c));
        break;
    case 0x000032DA: /* c1 */
        a_trajpoly5_c1(ctx, c);
        lua_array_num_new(L, c, A_LEN(ctx->c) - 1);
        break;
    case 0x000032DB: /* c2 */
        a_trajpoly5_c2(ctx, c);
        lua_array_num_new(L, c, A_LEN(ctx->c) - 2);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_trajpoly5_new);
        lua_pushstring(L, "c0");
        lua_array_num_new(L, ctx->c, A_LEN(ctx->c));
        lua_rawset(L, -3);
        lua_pushstring(L, "c1");
        a_trajpoly5_c1(ctx, c);
        lua_array_num_new(L, c, A_LEN(ctx->c) - 1);
        lua_rawset(L, -3);
        lua_pushstring(L, "c2");
        a_trajpoly5_c2(ctx, c);
        lua_array_num_new(L, c, A_LEN(ctx->c) - 2);
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
    static lua_fun const metas[] = {
        {"__newindex", liba_trajpoly5_set},
        {"__index", liba_trajpoly5_get},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_trajpoly5_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.trajpoly5");
    lua_registry_set(L, liba_trajpoly5_new);

    return 1;
}
