/***
 trapezoidal velocity profile trajectory
 @module liba.traptraj
*/

#include "traptraj.h"
#include "a/traptraj.h"

static lua_Number liba_traptraj_gen_(lua_State *L, a_traptraj *ctx, int arg, int top)
{
    a_float v0 = 0, v1 = 0;
    a_float vm, ac, de, q0, q1;
    vm = (a_float)luaL_checknumber(L, arg + 1);
    ac = (a_float)luaL_checknumber(L, arg + 2);
    de = (a_float)luaL_checknumber(L, arg + 3);
    q0 = (a_float)luaL_checknumber(L, arg + 4);
    q1 = (a_float)luaL_checknumber(L, arg + 5);
    if (top >= 6) { v0 = (a_float)luaL_checknumber(L, arg + 6); }
    if (top >= 7) { v1 = (a_float)luaL_checknumber(L, arg + 7); }
    return (lua_Number)a_traptraj_gen(ctx, vm, ac, de, q0, q1, v0, v1);
}

/***
 constructor for trapezoidal velocity profile trajectory
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn a.traptraj trapezoidal velocity profile trajectory userdata
 @function new
*/
int liba_traptraj_new(lua_State *L)
{
    int const top = lua_gettop(L);
    if (top > 4)
    {
        a_traptraj *const ctx = lua_newclass(L, a_traptraj);
        lua_registry_get(L, liba_traptraj_new);
        lua_setmetatable(L, -2);
        if (liba_traptraj_gen_(L, ctx, 0, top) <= 0)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

/***
 generate for trapezoidal velocity profile trajectory
 @tparam a.traptraj ctx trapezoidal velocity profile trajectory userdata
 @tparam number vm defines the maximum velocity at which the system can work
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number q0 defines the initial position
 @tparam number q1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total time
 @function gen
*/
int liba_traptraj_gen(lua_State *L)
{
    int const top = lua_gettop(L);
    if (top > 5)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_traptraj *const ctx = (a_traptraj *)lua_touserdata(L, 1);
        lua_pushnumber(L, liba_traptraj_gen_(L, ctx, 1, top - 1));
        return 1;
    }
    return 0;
}

/***
 calculate for trapezoidal velocity profile trajectory position
 @tparam a.traptraj ctx trapezoidal velocity profile trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_traptraj_pos(lua_State *L)
{
    a_traptraj const *const ctx = (a_traptraj const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_traptraj_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for trapezoidal velocity profile trajectory velocity
 @tparam a.traptraj ctx trapezoidal velocity profile trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_traptraj_vel(lua_State *L)
{
    a_traptraj const *const ctx = (a_traptraj const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_traptraj_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for trapezoidal velocity profile trajectory acceleration
 @tparam a.traptraj ctx trapezoidal velocity profile trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_traptraj_acc(lua_State *L)
{
    a_traptraj const *const ctx = (a_traptraj const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const dt = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_traptraj_acc(ctx, dt));
        return 1;
    }
    return 0;
}

static int liba_traptraj_set(lua_State *L)
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

static int liba_traptraj_get(lua_State *L)
{
    a_traptraj const *const ctx = (a_traptraj const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00000074: // t
        lua_pushnumber(L, (lua_Number)ctx->t);
        break;
    case 0x00003A03: // q0
        lua_pushnumber(L, (lua_Number)ctx->q0);
        break;
    case 0x00003A04: // q1
        lua_pushnumber(L, (lua_Number)ctx->q1);
        break;
    case 0x00003C92: // v0
        lua_pushnumber(L, (lua_Number)ctx->v0);
        break;
    case 0x00003C93: // v1
        lua_pushnumber(L, (lua_Number)ctx->v1);
        break;
    case 0x00003CC5: // vc
        lua_pushnumber(L, (lua_Number)ctx->vc);
        break;
    case 0x00003BBD: // ta
        lua_pushnumber(L, (lua_Number)ctx->ta);
        break;
    case 0x00003BC0: // td
        lua_pushnumber(L, (lua_Number)ctx->td);
        break;
    case 0x00003A34: // qa
        lua_pushnumber(L, (lua_Number)ctx->qa);
        break;
    case 0x00003A37: // qd
        lua_pushnumber(L, (lua_Number)ctx->qd);
        break;
    case 0x00003206: // ac
        lua_pushnumber(L, (lua_Number)ctx->ac);
        break;
    case 0x00003391: // de
        lua_pushnumber(L, (lua_Number)ctx->de);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_traptraj_new);
        lua_num_set(L, -1, "t", ctx->t);
        lua_num_set(L, -1, "q0", ctx->q0);
        lua_num_set(L, -1, "q1", ctx->q1);
        lua_num_set(L, -1, "v0", ctx->v0);
        lua_num_set(L, -1, "v1", ctx->v1);
        lua_num_set(L, -1, "vc", ctx->vc);
        lua_num_set(L, -1, "ta", ctx->ta);
        lua_num_set(L, -1, "td", ctx->td);
        lua_num_set(L, -1, "qa", ctx->qa);
        lua_num_set(L, -1, "qd", ctx->qd);
        lua_num_set(L, -1, "ac", ctx->ac);
        lua_num_set(L, -1, "de", ctx->de);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_traptraj_(lua_State *L)
{
    lua_pushcfunction(L, liba_traptraj_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_traptraj(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_traptraj_new},
        {"gen", liba_traptraj_gen},
        {"pos", liba_traptraj_pos},
        {"vel", liba_traptraj_vel},
        {"acc", liba_traptraj_acc},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_traptraj_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_traptraj_set},
        {"__index", liba_traptraj_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.traptraj");
    lua_registry_set(L, liba_traptraj_new);

    return 1;
}
