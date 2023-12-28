/***
 quintic polynomial trajectory
 @module liba.polytraj5
*/

#include "polytraj5.h"
#include "a/polytraj5.h"

static int liba_polytraj5_gen_(lua_State *const L, a_polytraj5_s *const ctx, int const arg, int const top)
{
    a_float_t t0 = 0, q0 = 0, v0 = 0, a0 = 0;
    a_float_t t1 = 0, q1 = 0, v1 = 0, a1 = 0;
    switch (top)
    {
    default:
    case 8:
        a1 = (a_float_t)luaL_checknumber(L, arg + 8);
        A_FALLTHROUGH;
    case 7:
        a0 = (a_float_t)luaL_checknumber(L, arg + 7);
        A_FALLTHROUGH;
    case 6:
        v1 = (a_float_t)luaL_checknumber(L, arg + 6);
        A_FALLTHROUGH;
    case 5:
        v0 = (a_float_t)luaL_checknumber(L, arg + 5);
        A_FALLTHROUGH;
    case 4:
        q1 = (a_float_t)luaL_checknumber(L, arg + 4);
        A_FALLTHROUGH;
    case 3:
        q0 = (a_float_t)luaL_checknumber(L, arg + 3);
        A_FALLTHROUGH;
    case 2:
        t1 = (a_float_t)luaL_checknumber(L, arg + 2);
        A_FALLTHROUGH;
    case 1:
        t0 = (a_float_t)luaL_checknumber(L, arg + 1);
        A_FALLTHROUGH;
    case 0:;
    }
    a_polytraj5_gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1);
    return 1;
}

/***
 constructor for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function new
*/
int liba_polytraj5_new(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_newuserdata(L, sizeof(a_polytraj5_s));
        lua_registry_get(L, liba_polytraj5_new);
        lua_setmetatable(L, -2);
        return liba_polytraj5_gen_(L, ctx, 0, top);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_float_t source[4] = {0};
        a_float_t target[4] = {0};
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_array_num_get(L, 1, source, A_LEN(source));
        lua_array_num_get(L, 2, target, A_LEN(target));
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_newuserdata(L, sizeof(a_polytraj5_s));
        lua_registry_get(L, liba_polytraj5_new);
        lua_setmetatable(L, -2);
        a_polytraj5_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3]);
        return 1;
    }
    return 0;
}

/***
 generate for quintic polynomial trajectory
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_polytraj5_gen(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 2);
    if (top > 4 && type == LUA_TNUMBER)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        return liba_polytraj5_gen_(L, ctx, 1, top - 1);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_float_t source[4] = {0};
        a_float_t target[4] = {0};
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_touserdata(L, 1);
        lua_array_num_get(L, 2, source, A_LEN(source));
        lua_array_num_get(L, 3, target, A_LEN(target));
        a_polytraj5_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3]);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory position
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj5_pos(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory velocity
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj5_vel(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory acceleration
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj5_acc(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_acc(ctx, dt));
        return 1;
    }
    return 0;
}

static int liba_polytraj5_set(lua_State *const L)
{
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
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

static int liba_polytraj5_get(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
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
        lua_registry_get(L, liba_polytraj5_new);
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

static int liba_polytraj5_(lua_State *const L)
{
    lua_pushcfunction(L, liba_polytraj5_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_polytraj5(lua_State *const L)
{
    static lua_fun_s const funcs[] = {
        {"new", liba_polytraj5_new},
        {"gen", liba_polytraj5_gen},
        {"pos", liba_polytraj5_pos},
        {"vel", liba_polytraj5_vel},
        {"acc", liba_polytraj5_acc},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));

    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_polytraj5_);
    lua_setmetatable(L, -2);

    static lua_fun_s const metas[] = {
        {"__newindex", liba_polytraj5_set},
        {"__index", liba_polytraj5_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.polytraj5");

    lua_registry_set(L, liba_polytraj5_new);
    return 1;
}
