/***
 hepta polynomial trajectory
 @module liba.polytraj7
*/

#include "polytraj7.h"
#include "a/polytraj7.h"

static int liba_polytraj7_gen_(lua_State *const L, a_polytraj7_s *const ctx)
{
    a_float_t t0 = 0, q0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_float_t t1 = 0, q1 = 0, v1 = 0, a1 = 0, j1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    default:
    case 10:
        j1 = (a_float_t)luaL_checknumber(L, 10);
        A_FALLTHROUGH;
    case 9:
        j0 = (a_float_t)luaL_checknumber(L, 9);
        A_FALLTHROUGH;
    case 8:
        a1 = (a_float_t)luaL_checknumber(L, 8);
        A_FALLTHROUGH;
    case 7:
        a0 = (a_float_t)luaL_checknumber(L, 7);
        A_FALLTHROUGH;
    case 6:
        v1 = (a_float_t)luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    case 5:
        v0 = (a_float_t)luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    case 4:
        q1 = (a_float_t)luaL_checknumber(L, 4);
        A_FALLTHROUGH;
    case 3:
        q0 = (a_float_t)luaL_checknumber(L, 3);
        A_FALLTHROUGH;
    case 2:
        t1 = (a_float_t)luaL_checknumber(L, 2);
        A_FALLTHROUGH;
    case 1:
        t0 = (a_float_t)luaL_checknumber(L, 1);
        A_FALLTHROUGH;
    case 0:;
    }
    a_polytraj7_gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    return 1;
}

/***
 constructor for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
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
int liba_polytraj7_new(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        a_polytraj7_s *const ctx = (a_polytraj7_s *)lua_newuserdata(L, sizeof(a_polytraj7_s));
        liba_polytraj7_meta_(L, 1);
        lua_setmetatable(L, -2);
        return liba_polytraj7_gen_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_float_t source[5] = {0};
        a_float_t target[5] = {0};
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_array_num_get(L, 1, source, A_LEN(source));
        lua_array_num_get(L, 2, target, A_LEN(target));
        a_polytraj7_s *const ctx = (a_polytraj7_s *)lua_newuserdata(L, sizeof(a_polytraj7_s));
        liba_polytraj7_meta_(L, 1);
        lua_setmetatable(L, -2);
        a_polytraj7_gen(ctx,
                        source[0], target[0],
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
 @tparam number t0 time for source
 @tparam number t1 time for target
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
int liba_polytraj7_gen(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 2);
    if (top > 4 && type == LUA_TNUMBER)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytraj7_s *const ctx = (a_polytraj7_s *)lua_touserdata(L, 1);
        return liba_polytraj7_gen_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_float_t source[5] = {0};
        a_float_t target[5] = {0};
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_polytraj7_s *const ctx = (a_polytraj7_s *)lua_touserdata(L, 1);
        lua_array_num_get(L, 2, source, A_LEN(source));
        lua_array_num_get(L, 3, target, A_LEN(target));
        a_polytraj7_gen(ctx,
                        source[0], target[0],
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
int liba_polytraj7_pos(lua_State *const L)
{
    a_polytraj7_s const *const ctx = (a_polytraj7_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
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
int liba_polytraj7_vel(lua_State *const L)
{
    a_polytraj7_s const *const ctx = (a_polytraj7_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
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
int liba_polytraj7_acc(lua_State *const L)
{
    a_polytraj7_s const *const ctx = (a_polytraj7_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
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
int liba_polytraj7_jer(lua_State *const L)
{
    a_polytraj7_s const *const ctx = (a_polytraj7_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj7_jer(ctx, dt));
        return 1;
    }
    return 0;
}

static int liba_polytraj7_set(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int liba_polytraj7_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytraj7_s const *const ctx = (a_polytraj7_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
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
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_polytraj7_new);
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, liba_polytraj7_gen);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, liba_polytraj7_pos);
        break;
    case 0x001F1A41: // vel
        lua_pushcfunction(L, liba_polytraj7_vel);
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, liba_polytraj7_acc);
        break;
    case 0x001BF5DB: // jer
        lua_pushcfunction(L, liba_polytraj7_jer);
        break;
    case 0xA65758B2: // __index
        liba_polytraj7_meta_(L, 1);
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        lua_setfield(L, -2, "q");
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        lua_setfield(L, -2, "v");
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        lua_setfield(L, -2, "a");
        lua_array_num_new(L, ctx->j, A_LEN(ctx->j));
        lua_setfield(L, -2, "j");
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_polytraj7(lua_State *const L)
{
    lua_fun_s const funcs[] = {
        {"new", liba_polytraj7_new},
        {"gen", liba_polytraj7_gen},
        {"pos", liba_polytraj7_pos},
        {"vel", liba_polytraj7_vel},
        {"acc", liba_polytraj7_acc},
        {"jer", liba_polytraj7_jer},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, funcs);

    lua_fun_s const metas[] = {
        {"__newindex", liba_polytraj7_set},
        {"__index", liba_polytraj7_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, metas);
    lua_fun_reg(L, -1, funcs);
    lua_str_set(L, -1, "__name", "a.polytraj7");

    liba_polytraj7_meta_(L, 0);
    liba_polytraj7_func_(L, 0);

    return liba_polytraj7_func_(L, 1);
}

int liba_polytraj7_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj7_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj7_func_));
    return 0;
}

int liba_polytraj7_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj7_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj7_meta_));
    return 0;
}
