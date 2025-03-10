/***
 High Pass Filter
 @module liba.hpf
*/

#include "hpf.h"
#include "a/hpf.h"

/***
 constructor for High Pass Filter
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.hpf High Pass Filter userdata
 @function new
*/
int liba_hpf_new(lua_State *L)
{
    a_hpf *ctx;
    a_real alpha;
    if (lua_gettop(L) > 1)
    {
        a_real fc = (a_real)luaL_checknumber(L, 1);
        a_real ts = (a_real)luaL_checknumber(L, 2);
        alpha = A_HPF_GEN(fc, ts);
    }
    else
    {
        alpha = (a_real)luaL_checknumber(L, 1);
    }
    ctx = lua_newclass(L, a_hpf);
    lua_registry_get(L, liba_hpf_new);
    lua_setmetatable(L, -2);
    a_hpf_init(ctx, alpha);
    return 1;
}

/***
 generate for High Pass Filter
 @tparam a.hpf ctx High Pass Filter userdata
 @tparam number fc cut-off frequency unit(hz)
 @tparam number ts sampling time unit(s)
 @treturn a.hpf High Pass Filter userdata
 @function gen
*/
int liba_hpf_gen(lua_State *L)
{
    a_hpf *const ctx = (a_hpf *)lua_touserdata(L, 1);
    if (ctx)
    {
        if (lua_gettop(L) > 2)
        {
            a_real fc = (a_real)luaL_checknumber(L, 2);
            a_real ts = (a_real)luaL_checknumber(L, 3);
            ctx->alpha = A_HPF_GEN(fc, ts);
        }
        else
        {
            ctx->alpha = (a_real)luaL_checknumber(L, 2);
        }
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 compute for High Pass Filter
 @tparam a.hpf ctx High Pass Filter userdata
 @tparam number x input value
 @treturn number output value
 @function iter
*/
int liba_hpf_iter(lua_State *L)
{
    a_hpf *const ctx = (a_hpf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_hpf_iter(ctx, x));
        return 1;
    }
    return 0;
}

/***
 zeroing for High Pass Filter
 @tparam a.hpf ctx High Pass Filter userdata
 @treturn a.hpf High Pass Filter userdata
 @function zero
*/
int liba_hpf_zero(lua_State *L)
{
    a_hpf *const ctx = (a_hpf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_hpf_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_hpf_set(lua_State *L)
{
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xE8859EEB: /* __name */
    case 0xE70C48C6: /* __call */
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

static int liba_hpf_get(lua_State *L)
{
    a_hpf const *const ctx = (a_hpf const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xB5485B9E: /* alpha */
        lua_pushnumber(L, (lua_Number)ctx->alpha);
        break;
    case 0x23C9C461: /* output */
        lua_pushnumber(L, (lua_Number)ctx->output);
        break;
    case 0x41FAB016: /* input */
        lua_pushnumber(L, (lua_Number)ctx->input);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_hpf_new);
        lua_num_set(L, -1, "alpha", ctx->alpha);
        lua_num_set(L, -1, "input", ctx->input);
        lua_num_set(L, -1, "output", ctx->output);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_hpf_(lua_State *L)
{
    lua_pushcfunction(L, liba_hpf_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_hpf(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_hpf_new},
        {"gen", liba_hpf_gen},
        {"iter", liba_hpf_iter},
        {"zero", liba_hpf_zero},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_hpf_set},
        {"__index", liba_hpf_get},
        {"__call", liba_hpf_iter},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_hpf_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.hpf");
    lua_registry_set(L, liba_hpf_new);

    return 1;
}
