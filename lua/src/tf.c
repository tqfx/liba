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
int liba_tf_die(lua_State *const L)
{
    a_tf_s *const ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        ctx->num_p = (a_float_t const *)lua_alloc(L, ctx->num_p, 0);
        ctx->num_n = 0;
        ctx->input = 0;
        ctx->den_p = (a_float_t const *)lua_alloc(L, ctx->den_p, 0);
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
int liba_tf_new(lua_State *const L)
{
    if (lua_gettop(L) > 1)
    {
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        unsigned int const num_n = (unsigned int)lua_rawlen(L, 1);
        a_float_t *const num_p = (a_float_t *)lua_alloc(L, NULL, sizeof(a_float_t) * num_n * 2);
        lua_array_num_get(L, 1, num_p, num_n);
        unsigned int const den_n = (unsigned int)lua_rawlen(L, 2);
        a_float_t *const den_p = (a_float_t *)lua_alloc(L, NULL, sizeof(a_float_t) * den_n * 2);
        lua_array_num_get(L, 2, den_p, den_n);
        a_tf_s *const ctx = (a_tf_s *)lua_newuserdata(L, sizeof(a_tf_s));
        liba_tf_meta_(L, 1);
        lua_setmetatable(L, -2);
        a_tf_init(ctx, num_n, num_p, num_p + num_n, den_n, den_p, den_p + den_n);
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
int liba_tf_init(lua_State *const L)
{
    if (lua_gettop(L) > 2)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_tf_s *const ctx = (a_tf_s *)lua_touserdata(L, 1);
        unsigned int const num_n = (unsigned int)lua_rawlen(L, 2);
        a_float_t *const num_p = (a_float_t *)lua_alloc(L, ctx->num_p, sizeof(a_float_t) * num_n * 2);
        lua_array_num_get(L, 2, num_p, num_n);
        unsigned int const den_n = (unsigned int)lua_rawlen(L, 3);
        a_float_t *const den_p = (a_float_t *)lua_alloc(L, ctx->den_p, sizeof(a_float_t) * den_n * 2);
        lua_array_num_get(L, 3, den_p, den_n);
        a_tf_init(ctx, num_n, num_p, num_p + num_n, den_n, den_p, den_p + den_n);
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
int liba_tf_iter(lua_State *const L)
{
    a_tf_s *const ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t x = (a_float_t)luaL_checknumber(L, 2);
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
int liba_tf_zero(lua_State *const L)
{
    a_tf_s *const ctx = (a_tf_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_tf_zero(ctx);
        return 1;
    }
    return 0;
}

#undef funcs
#define funcs liba_tf_funcs
static lua_fun_s const funcs[] = {
    {"init", liba_tf_init},
    {"iter", liba_tf_iter},
    {"zero", liba_tf_zero},
    {"new", liba_tf_new},
    {"die", liba_tf_die},
    {NULL, NULL},
};

static int liba_tf_set(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_tf_s *const ctx = (a_tf_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x001D0A2A: // num
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        unsigned int const num_n = (unsigned int)lua_rawlen(L, 3);
        a_float_t *const num_p = (a_float_t *)lua_alloc(L, ctx->num_p, sizeof(a_float_t) * num_n * 2);
        lua_array_num_get(L, 3, num_p, num_n);
        a_tf_set_num(ctx, num_n, num_p, num_p + num_n);
        break;
    }
    case 0x001A63A1: // den
    {
        luaL_checktype(L, 3, LUA_TTABLE);
        unsigned int const den_n = (unsigned int)lua_rawlen(L, 3);
        a_float_t *const den_p = (a_float_t *)lua_alloc(L, ctx->den_p, sizeof(a_float_t) * den_n * 2);
        lua_array_num_get(L, 3, den_p, den_n);
        a_tf_set_den(ctx, den_n, den_p, den_p + den_n);
        break;
    }
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
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

static int liba_tf_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_tf_s const *const ctx = (a_tf_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
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
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_tf_new);
        break;
    case 0x001A65A4: // die
        lua_pushcfunction(L, liba_tf_die);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, liba_tf_init);
        break;
    case 0x0E3068C8: // iter
        lua_pushcfunction(L, liba_tf_iter);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, liba_tf_zero);
        break;
    case 0xA65758B2: // __index
    {
        lua_createtable(L, 0, A_LEN(funcs) + 1);
        lua_fun_reg(L, -1, funcs);
        lua_array_num_new(L, ctx->num_p, ctx->num_n);
        lua_setfield(L, -2, "num");
        lua_array_num_new(L, ctx->den_p, ctx->den_n);
        lua_setfield(L, -2, "den");
        lua_array_num_new(L, ctx->input, ctx->num_n);
        lua_setfield(L, -2, "input");
        lua_array_num_new(L, ctx->output, ctx->den_n);
        lua_setfield(L, -2, "output");
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_tf(lua_State *const L)
{
    lua_createtable(L, 0, A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__newindex", liba_setter);
    lua_setmetatable(L, -2);

    lua_fun_s const metas[] = {
        {"__newindex", liba_tf_set},
        {"__index", liba_tf_get},
        {"__call", liba_tf_iter},
        {"__gc", liba_tf_die},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    lua_str_set(L, -1, "__name", "a.tf");
    lua_fun_reg(L, -1, metas);

    liba_tf_meta_(L, 0);
    liba_tf_func_(L, 0);

    return liba_tf_func_(L, 1);
}

int liba_tf_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_tf_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_tf_func_));
    return 0;
}

int liba_tf_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_tf_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_tf_meta_));
    return 0;
}
