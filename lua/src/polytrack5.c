/***
 quintic polynomial trajectory
 @module liba.polytrack5
*/

#include "polytrack5.h"

static int LMODULE(polytrack5_init_)(lua_State *const L, a_polytrack5_s *const ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0, a0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0, a1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
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
    a_polytrack5_init(ctx, t0, t1, q0, q1, v0, v1, a0, a1);
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
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function new
*/
int LMODULE(polytrack5_new)(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, -1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_polytrack5_s *const ctx = (a_polytrack5_s *)lua_newuserdata(L, sizeof(a_polytrack5_s));
        LMODULE2(polytrack5_meta_, L, 1);
        lua_setmetatable(L, -2);
        return LMODULE2(polytrack5_init_, L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_real_t target[4] = {0};
        a_real_t source[4] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        l_array_num_get(L, -1, target, L_COUNT(target));
        l_array_num_get(L, -2, source, L_COUNT(source));
        a_polytrack5_s *const ctx = (a_polytrack5_s *)lua_newuserdata(L, sizeof(a_polytrack5_s));
        LMODULE2(polytrack5_meta_, L, 1);
        lua_setmetatable(L, -2);
        a_polytrack5_init2(ctx, source, target);
        return 1;
    }
    return 0;
}

/***
 initialize function for quintic polynomial trajectory
 @param ctx quintic polynomial trajectory userdata
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
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function init
*/
int LMODULE(polytrack5_init)(lua_State *const L)
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
        a_polytrack5_s *const ctx = (a_polytrack5_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return LMODULE2(polytrack5_init_, L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_real_t target[4] = {0};
        a_real_t source[4] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_polytrack5_s *const ctx = (a_polytrack5_s *)lua_touserdata(L, -3);
        l_array_num_get(L, -1, target, L_COUNT(target));
        l_array_num_get(L, -2, source, L_COUNT(source));
        a_polytrack5_init2(ctx, source, target);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 generation function for quintic polynomial trajectory
 @param ctx quintic polynomial trajectory userdata
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function gen
*/
int LMODULE(polytrack5_gen)(lua_State *const L)
{
    a_polytrack5_s *const ctx = (a_polytrack5_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_polytrack5_gen(ctx);
        return 1;
    }
    return 0;
}

/***
 process function for quintic polynomial trajectory
 @param ctx quintic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration}
 @function out
*/
int LMODULE(polytrack5_out)(lua_State *const L)
{
    a_polytrack5_s const *const ctx = (a_polytrack5_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t const ts = (a_real_t)luaL_checknumber(L, -1);
        a_polytrack5_out(ctx, ts, out);
        lua_createtable(L, 3, 0);
        l_array_num_set(L, -1, out, 3);
        return 1;
    }
    return 0;
}

/***
 process function for quintic polynomial trajectory position
 @param ctx quintic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int LMODULE(polytrack5_pos)(lua_State *const L)
{
    a_polytrack5_s const *const ctx = (a_polytrack5_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack5_pos(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for quintic polynomial trajectory velocity
 @param ctx quintic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int LMODULE(polytrack5_vec)(lua_State *const L)
{
    a_polytrack5_s const *const ctx = (a_polytrack5_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack5_vec(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for quintic polynomial trajectory acceleration
 @param ctx quintic polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int LMODULE(polytrack5_acc)(lua_State *const L)
{
    a_polytrack5_s const *const ctx = (a_polytrack5_s const *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t const ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack5_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static int LMODULE(polytrack5_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00000074: // t
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, L_COUNT(ctx->t), 0);
        l_array_num_get(L, 3, ctx->t, L_COUNT(ctx->t));
        break;
    case 0x00000071: // q
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, L_COUNT(ctx->q), 0);
        l_array_num_get(L, 3, ctx->q, L_COUNT(ctx->q));
        break;
    case 0x00000076: // v
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, L_COUNT(ctx->v), 0);
        l_array_num_get(L, 3, ctx->v, L_COUNT(ctx->v));
        break;
    case 0x00000061: // a
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, L_COUNT(ctx->a), 0);
        l_array_num_get(L, 3, ctx->a, L_COUNT(ctx->a));
        break;
    case 0x00003B8C: // t0
        ctx->t[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003A03: // q0
        ctx->q[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003C92: // v0
        ctx->v[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x000031D3: // a0
        ctx->a[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003B8D: // t1
        ctx->t[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003A04: // q1
        ctx->q[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003C93: // v1
        ctx->v[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x000031D4: // a1
        ctx->a[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
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
    a_polytrack5_gen(ctx);
    return 0;
}

static int LMODULE(polytrack5_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytrack5_s const *const ctx = (a_polytrack5_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0000006B: // k
        lua_createtable(L, L_COUNT(ctx->k), 0);
        l_array_num_set(L, -1, ctx->k, L_COUNT(ctx->k));
        break;
    case 0x00000074: // t
        lua_createtable(L, L_COUNT(ctx->t), 0);
        l_array_num_set(L, -1, ctx->t, L_COUNT(ctx->t));
        break;
    case 0x00000071: // q
        lua_createtable(L, L_COUNT(ctx->q), 0);
        l_array_num_set(L, -1, ctx->q, L_COUNT(ctx->q));
        break;
    case 0x00000076: // a
        lua_createtable(L, L_COUNT(ctx->v), 0);
        l_array_num_set(L, -1, ctx->v, L_COUNT(ctx->v));
        break;
    case 0x00000061: // v
        lua_createtable(L, L_COUNT(ctx->a), 0);
        l_array_num_set(L, -1, ctx->a, L_COUNT(ctx->a));
        break;
    case 0x00003B8C: // t0
        lua_pushnumber(L, (lua_Number)ctx->t[0]);
        break;
    case 0x00003A03: // q0
        lua_pushnumber(L, (lua_Number)ctx->q[0]);
        break;
    case 0x00003C92: // v0
        lua_pushnumber(L, (lua_Number)ctx->v[0]);
        break;
    case 0x000031D3: // a0
        lua_pushnumber(L, (lua_Number)ctx->a[0]);
        break;
    case 0x00003B8D: // t1
        lua_pushnumber(L, (lua_Number)ctx->t[1]);
        break;
    case 0x00003A04: // q1
        lua_pushnumber(L, (lua_Number)ctx->q[1]);
        break;
    case 0x00003C93: // v1
        lua_pushnumber(L, (lua_Number)ctx->v[1]);
        break;
    case 0x000031D4: // a1
        lua_pushnumber(L, (lua_Number)ctx->a[1]);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(polytrack5_new));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(polytrack5_init));
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, LMODULE(polytrack5_gen));
        break;
    case 0x001D4D3A: // out
        lua_pushcfunction(L, LMODULE(polytrack5_out));
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, LMODULE(polytrack5_pos));
        break;
    case 0x001F1A38: // vec
        lua_pushcfunction(L, LMODULE(polytrack5_vec));
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, LMODULE(polytrack5_acc));
        break;
    case 0xA65758B2: // __index
    {
        l_num_s const datas[] = {
            {"t0", ctx->t[0]},
            {"q0", ctx->q[0]},
            {"v0", ctx->v[0]},
            {"a0", ctx->a[0]},
            {"t1", ctx->t[1]},
            {"q1", ctx->q[1]},
            {"v1", ctx->v[1]},
            {"a1", ctx->a[1]},
            {NULL, 0},
        };
        l_func_s const funcs[] = {
            {"init", LMODULE(polytrack5_init)},
            {"gen", LMODULE(polytrack5_gen)},
            {"out", LMODULE(polytrack5_out)},
            {"pos", LMODULE(polytrack5_pos)},
            {"vec", LMODULE(polytrack5_vec)},
            {"acc", LMODULE(polytrack5_acc)},
            {"new", LMODULE(polytrack5_new)},
            {NULL, NULL},
        };
        lua_createtable(L, 0, L_COUNT(datas) + L_COUNT(funcs) + 3);
        l_num_reg(L, -1, datas);
        l_func_reg(L, -1, funcs);
        lua_createtable(L, L_COUNT(ctx->k), 0);
        l_array_num_set(L, -1, ctx->k, L_COUNT(ctx->k));
        lua_setfield(L, -2, "k");
        lua_createtable(L, L_COUNT(ctx->t), 0);
        l_array_num_set(L, -1, ctx->t, L_COUNT(ctx->t));
        lua_setfield(L, -2, "t");
        lua_createtable(L, L_COUNT(ctx->q), 0);
        l_array_num_set(L, -1, ctx->q, L_COUNT(ctx->q));
        lua_setfield(L, -2, "q");
        lua_createtable(L, L_COUNT(ctx->v), 0);
        l_array_num_set(L, -1, ctx->v, L_COUNT(ctx->v));
        lua_setfield(L, -2, "v");
        lua_createtable(L, L_COUNT(ctx->a), 0);
        l_array_num_set(L, -1, ctx->a, L_COUNT(ctx->a));
        lua_setfield(L, -2, "a");
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int LMODULE_(polytrack5, lua_State *const L)
{
    l_func_s const funcs[] = {
        {"init", LMODULE(polytrack5_init)},
        {"gen", LMODULE(polytrack5_gen)},
        {"out", LMODULE(polytrack5_out)},
        {"pos", LMODULE(polytrack5_pos)},
        {"vec", LMODULE(polytrack5_vec)},
        {"acc", LMODULE(polytrack5_acc)},
        {"new", LMODULE(polytrack5_new)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(funcs) - 1);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(polytrack5_new));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_NEW, LMODULE(polytrack5_out)},
        {L_SET, LMODULE(polytrack5_set)},
        {L_GET, LMODULE(polytrack5_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(metas));
    l_str_set(L, -1, L_NAME, "polytrack5");
    l_func_reg(L, -1, metas);

    LMODULE2(polytrack5_meta_, L, 0);
    LMODULE2(polytrack5_func_, L, 0);

    return LMODULE2(polytrack5_func_, L, 1);
}

int LMODULE(polytrack5_func_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(polytrack5_func_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}

int LMODULE(polytrack5_meta_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(polytrack5_meta_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}
