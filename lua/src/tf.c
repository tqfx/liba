/***
 transfer function
 @module liba.tf
*/

#include "tf.h"
#include "a/tf.h"

/***
 destructor for transfer function
 @tparam a.tf ctx transfer function userdata
 @function die
*/
int liba_tf_die(lua_State *L)
{
    a_tf *const ctx = (a_tf *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_alloc(L, ctx->num_p, 0);
        ctx->num_p = 0;
        ctx->num_n = 0;
        ctx->input = 0;
        lua_alloc(L, ctx->den_p, 0);
        ctx->den_p = 0;
        ctx->den_n = 0;
        ctx->output = 0;
    }
    return 0;
}

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function new
*/
int liba_tf_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        unsigned int const num_n = lua_array_num_len(L, 1, 1);
        unsigned int const den_n = lua_array_num_len(L, 2, 1);
        a_tf *const ctx = lua_newclass(L, a_tf);
        a_zero(ctx, sizeof(a_tf));
        lua_registry_get(L, liba_tf_new);
        lua_setmetatable(L, -2);
        if (num_n)
        {
            a_float *num_p = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * num_n * 2);
            a_tf_set_num(ctx, num_n, num_p, num_p + num_n);
            lua_array_num_ptr(L, 1, num_p, 1);
        }
        if (den_n)
        {
            a_float *den_p = (a_float *)lua_alloc(L, NULL, sizeof(a_float) * den_n * 2);
            a_tf_set_den(ctx, den_n, den_p, den_p + den_n);
            lua_array_num_ptr(L, 2, den_p, 1);
        }
        return 1;
    }
    return 0;
}

/***
 initialize for transfer function
 @tparam a.tf ctx transfer function userdata
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn a.tf transfer function userdata
 @function init
*/
int liba_tf_init(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_tf *const ctx = (a_tf *)lua_touserdata(L, 1);
        unsigned int const num_n = lua_array_num_len(L, 2, 1);
        unsigned int const den_n = lua_array_num_len(L, 3, 1);
        if (num_n > ctx->num_n)
        {
            a_float *num_p = (a_float *)lua_alloc(L, ctx->num_p, sizeof(a_float) * num_n * 2);
            a_tf_set_num(ctx, num_n, num_p, num_p + num_n);
            lua_array_num_ptr(L, 2, num_p, 1);
        }
        else { ctx->num_n = num_n; }
        if (den_n > ctx->den_n)
        {
            a_float *den_p = (a_float *)lua_alloc(L, ctx->den_p, sizeof(a_float) * den_n * 2);
            a_tf_set_den(ctx, den_n, den_p, den_p + den_n);
            lua_array_num_ptr(L, 3, den_p, 1);
        }
        else { ctx->den_n = den_n; }
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for transfer function
 @tparam a.tf ctx transfer function userdata
 @tparam number x input
 @treturn number output
 @function iter
*/
int liba_tf_iter(lua_State *L)
{
    a_tf *const ctx = (a_tf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_tf_iter(ctx, x));
        return 1;
    }
    return 0;
}

/***
 zeroing for transfer function
 @tparam a.tf ctx transfer function userdata
 @treturn a.tf transfer function userdata
 @function zero
*/
int liba_tf_zero(lua_State *L)
{
    a_tf *const ctx = (a_tf *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_tf_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_tf_set(lua_State *L)
{
    a_tf *const ctx = (a_tf *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x001D0A2A: // num
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        unsigned int const num_n = lua_array_num_len(L, 3, 1);
        if (num_n > ctx->num_n)
        {
            a_float *num_p = (a_float *)lua_alloc(L, ctx->num_p, sizeof(a_float) * num_n * 2);
            a_tf_set_num(ctx, num_n, num_p, num_p + num_n);
            lua_array_num_ptr(L, 3, num_p, 1);
        }
        else { ctx->num_n = num_n; }
        break;
    }
    case 0x001A63A1: // den
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        unsigned int const den_n = lua_array_num_len(L, 3, 1);
        if (den_n > ctx->den_n)
        {
            a_float *den_p = (a_float *)lua_alloc(L, ctx->den_p, sizeof(a_float) * den_n * 2);
            a_tf_set_den(ctx, den_n, den_p, den_p + den_n);
            lua_array_num_ptr(L, 3, den_p, 1);
        }
        else { ctx->den_n = den_n; }
        break;
    }
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

static int liba_tf_get(lua_State *L)
{
    a_tf const *const ctx = (a_tf const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x001D0A2A: // num
        lua_array_num_new(L, ctx->num_p, ctx->num_n);
        break;
    case 0x001A63A1: // den
        lua_array_num_new(L, ctx->den_p, ctx->den_n);
        break;
    case 0x41FAB016: // input
        lua_array_num_new(L, ctx->input, ctx->num_n);
        break;
    case 0x23C9C461: // output
        lua_array_num_new(L, ctx->output, ctx->den_n);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_tf_new);
        lua_pushstring(L, "num");
        lua_array_num_new(L, ctx->num_p, ctx->num_n);
        lua_rawset(L, -3);
        lua_pushstring(L, "den");
        lua_array_num_new(L, ctx->den_p, ctx->den_n);
        lua_rawset(L, -3);
        lua_pushstring(L, "input");
        lua_array_num_new(L, ctx->input, ctx->num_n);
        lua_rawset(L, -3);
        lua_pushstring(L, "output");
        lua_array_num_new(L, ctx->output, ctx->den_n);
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_tf_(lua_State *L)
{
    lua_pushcfunction(L, liba_tf_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_tf(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"init", liba_tf_init},
        {"iter", liba_tf_iter},
        {"zero", liba_tf_zero},
        {"new", liba_tf_new},
        {"die", liba_tf_die},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_tf_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_tf_set},
        {"__index", liba_tf_get},
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 503)
        {"__close", liba_tf_die},
#endif /* LUA_VERSION_NUM */
        {"__call", liba_tf_iter},
        {"__gc", liba_tf_die},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.tf");
    lua_registry_set(L, liba_tf_new);

    return 1;
}
