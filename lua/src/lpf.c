/***
 Low Pass Filter
 @module liba.lpf
*/

#include "lpf.h"
#include "a/lpf.h"

/***
 constructor for Low Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.lpf Low Pass Filter userdata
 @function new
*/
int liba_lpf_new(lua_State *L)
{
    int top = lua_gettop(L);
    if (top > 1)
    {
        a_float fc = (a_float)luaL_checknumber(L, 1);
        a_float ts = (a_float)luaL_checknumber(L, 2);
        a_lpf *const ctx = lua_newclass(L, a_lpf);
        lua_registry_get(L, liba_lpf_new);
        lua_setmetatable(L, -2);
        a_lpf_init(ctx, A_LPF_GEN(fc, ts));
        return 1;
    }
    if (top > 0)
    {
        a_float alpha = (a_float)luaL_checknumber(L, 1);
        a_lpf *const ctx = lua_newclass(L, a_lpf);
        lua_registry_get(L, liba_lpf_new);
        lua_setmetatable(L, -2);
        a_lpf_init(ctx, alpha);
        return 1;
    }
    return 0;
}

/***
 generate for Low Pass Filter
 @tparam a.lpf ctx Low Pass Filter userdata
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.lpf Low Pass Filter userdata
 @function gen
*/
int liba_lpf_gen(lua_State *L)
{
    int top = lua_gettop(L);
    if (top > 2)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_lpf *const ctx = (a_lpf *)lua_touserdata(L, 1);
        a_float fc = (a_float)luaL_checknumber(L, 2);
        a_float ts = (a_float)luaL_checknumber(L, 3);
        ctx->alpha = A_LPF_GEN(fc, ts);
        lua_pushvalue(L, 1);
        return 1;
    }
    if (top > 1)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_lpf *const ctx = (a_lpf *)lua_touserdata(L, 1);
        ctx->alpha = (a_float)luaL_checknumber(L, 2);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for Low Pass Filter
 @tparam a.lpf ctx Low Pass Filter userdata
 @tparam number x input value
 @treturn number output value
 @function iter
*/
int liba_lpf_iter(lua_State *L)
{
    a_lpf *const ctx = (a_lpf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_lpf_iter(ctx, x));
        return 1;
    }
    return 0;
}

/***
 zeroing for Low Pass Filter
 @tparam a.lpf ctx Low Pass Filter userdata
 @treturn a.lpf Low Pass Filter userdata
 @function zero
*/
int liba_lpf_zero(lua_State *L)
{
    a_lpf *const ctx = (a_lpf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_lpf_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_lpf_set(lua_State *L)
{
    switch ((a_u32)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
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

static int liba_lpf_get(lua_State *L)
{
    a_lpf const *const ctx = (a_lpf const *)lua_touserdata(L, 1);
    switch ((a_u32)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xB5485B9E: // alpha
        lua_pushnumber(L, (lua_Number)ctx->alpha);
        break;
    case 0x23C9C461: // output
        lua_pushnumber(L, (lua_Number)ctx->output);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_lpf_new);
        lua_num_set(L, -1, "alpha", ctx->alpha);
        lua_num_set(L, -1, "output", ctx->output);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_lpf_(lua_State *L)
{
    lua_pushcfunction(L, liba_lpf_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_lpf(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_lpf_new},
        {"gen", liba_lpf_gen},
        {"iter", liba_lpf_iter},
        {"zero", liba_lpf_zero},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_lpf_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_lpf_set},
        {"__index", liba_lpf_get},
        {"__call", liba_lpf_iter},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.lpf");
    lua_registry_set(L, liba_lpf_new);

    return 1;
}
