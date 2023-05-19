/***
 hepta polynomial trajectory
 @module liba.polytrack7
*/

#include "polytrack7.h"

static int LMODULE(polytrack7_gen_)(lua_State *const L, a_polytrack7_s *const ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0, a1 = 0, j1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 10:
        j1 = (a_real_t)luaL_checknumber(L, 10);
        A_FALLTHROUGH;
    case 9:
        j0 = (a_real_t)luaL_checknumber(L, 9);
        A_FALLTHROUGH;
    case 8:
        a1 = (a_real_t)luaL_checknumber(L, 8);
        A_FALLTHROUGH;
    case 7:
        a0 = (a_real_t)luaL_checknumber(L, 7);
        A_FALLTHROUGH;
    case 6:
        v1 = (a_real_t)luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    case 5:
        v0 = (a_real_t)luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    case 4:
        q1 = (a_real_t)luaL_checknumber(L, 4);
        q0 = (a_real_t)luaL_checknumber(L, 3);
        t1 = (a_real_t)luaL_checknumber(L, 2);
        t0 = (a_real_t)luaL_checknumber(L, 1);
        A_FALLTHROUGH;
    default:
        break;
    }
    a_polytrack7_gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
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
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function new
*/
int LMODULE(polytrack7_new)(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, -1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_polytrack7_s *const ctx = (a_polytrack7_s *)lua_newuserdata(L, sizeof(a_polytrack7_s));
        LMODULE2(polytrack7_meta_, L, 1);
        lua_setmetatable(L, -2);
        return LMODULE2(polytrack7_gen_, L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_real_t target[5] = {0};
        a_real_t source[5] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        l_array_num_get(L, -1, target, L_COUNT(target));
        l_array_num_get(L, -2, source, L_COUNT(source));
        a_polytrack7_s *const ctx = (a_polytrack7_s *)lua_newuserdata(L, sizeof(a_polytrack7_s));
        LMODULE2(polytrack7_meta_, L, 1);
        lua_setmetatable(L, -2);
        a_polytrack7_gen(ctx,
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
 generation function for hepta polynomial trajectory
 @param ctx hepta polynomial trajectory userdata
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
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function gen
*/
int LMODULE(polytrack7_gen)(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, -1);
    if (top > 4 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytrack7_s *const ctx = (a_polytrack7_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return LMODULE2(polytrack7_gen_, L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_real_t target[5] = {0};
        a_real_t source[5] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_polytrack7_s *const ctx = (a_polytrack7_s *)lua_touserdata(L, -3);
        l_array_num_get(L, -1, target, L_COUNT(target));
        l_array_num_get(L, -2, source, L_COUNT(source));
        a_polytrack7_gen(ctx,
                         source[0], target[0],
                         source[1], target[1],
                         source[2], target[2],
                         source[3], target[3],
                         source[4], target[4]);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 calculate function for hepta polynomial trajectory
 @param ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn table {position,velocity,acceleration,jerk}
 @function out
*/
int LMODULE(polytrack7_out)(lua_State *const L)
{
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[4];
        a_real_t const dt = (a_real_t)luaL_checknumber(L, -1);
        a_polytrack7_out(ctx, dt, out);
        lua_createtable(L, 4, 0);
        l_array_num_set(L, -1, out, 4);
        return 1;
    }
    return 0;
}

/***
 calculate function for hepta polynomial trajectory position
 @param ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int LMODULE(polytrack7_pos)(lua_State *const L)
{
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const dt = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate function for hepta polynomial trajectory velocity
 @param ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vec
*/
int LMODULE(polytrack7_vec)(lua_State *const L)
{
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const dt = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_vec(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate function for hepta polynomial trajectory acceleration
 @param ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int LMODULE(polytrack7_acc)(lua_State *const L)
{
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const dt = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_acc(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate function for hepta polynomial trajectory jerk
 @param ctx hepta polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int LMODULE(polytrack7_jer)(lua_State *const L)
{
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const dt = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_jer(ctx, dt));
        return 1;
    }
    return 0;
}

static int LMODULE(polytrack7_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytrack7_s *const ctx = (a_polytrack7_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        return 0;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
        return 0;
    }
    (void)ctx;
    return 0;
}

static int LMODULE(polytrack7_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytrack7_s const *const ctx = (a_polytrack7_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0000006B: // k
        lua_createtable(L, L_COUNT(ctx->k), 0);
        l_array_num_set(L, -1, ctx->k, L_COUNT(ctx->k));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(polytrack7_new));
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, LMODULE(polytrack7_gen));
        break;
    case 0x001D4D3A: // out
        lua_pushcfunction(L, LMODULE(polytrack7_out));
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, LMODULE(polytrack7_pos));
        break;
    case 0x001F1A38: // vec
        lua_pushcfunction(L, LMODULE(polytrack7_vec));
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, LMODULE(polytrack7_acc));
        break;
    case 0x001BF5DB: // jer
        lua_pushcfunction(L, LMODULE(polytrack7_jer));
        break;
    case 0xA65758B2: // __index
    {
        l_func_s const funcs[] = {
            {"new", LMODULE(polytrack7_new)},
            {"gen", LMODULE(polytrack7_gen)},
            {"out", LMODULE(polytrack7_out)},
            {"pos", LMODULE(polytrack7_pos)},
            {"vec", LMODULE(polytrack7_vec)},
            {"acc", LMODULE(polytrack7_acc)},
            {"jer", LMODULE(polytrack7_jer)},
            {NULL, NULL},
        };
        lua_createtable(L, 0, L_COUNT(funcs));
        l_func_reg(L, -1, funcs);
        lua_createtable(L, L_COUNT(ctx->k), 0);
        l_array_num_set(L, -1, ctx->k, L_COUNT(ctx->k));
        lua_setfield(L, -2, "k");
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int LMODULE_(polytrack7, lua_State *const L)
{
    l_func_s const funcs[] = {
        {"new", LMODULE(polytrack7_new)},
        {"gen", LMODULE(polytrack7_gen)},
        {"out", LMODULE(polytrack7_out)},
        {"pos", LMODULE(polytrack7_pos)},
        {"vec", LMODULE(polytrack7_vec)},
        {"acc", LMODULE(polytrack7_acc)},
        {"jer", LMODULE(polytrack7_jer)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(funcs) - 1);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(polytrack7_new));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_NEW, LMODULE(polytrack7_out)},
        {L_SET, LMODULE(polytrack7_set)},
        {L_GET, LMODULE(polytrack7_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(metas));
    l_str_set(L, -1, L_NAME, "polytrack7");
    l_func_reg(L, -1, metas);

    LMODULE2(polytrack7_meta_, L, 0);
    LMODULE2(polytrack7_func_, L, 0);

    return LMODULE2(polytrack7_func_, L, 1);
}

int LMODULE(polytrack7_func_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(polytrack7_func_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}

int LMODULE(polytrack7_meta_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(polytrack7_meta_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}
