/***
 64-bit Cyclic Redundancy Check
 @module liba.crc64
*/

#include "crc64.h"
#include "a/crc.h"

struct crc64
{
    a_u64 table[0x100];
    a_u64 (*eval)(a_u64 const table[0x100], void const *pdata, a_size nbyte, a_u64 value);
};

/***
 constructor for 64-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc64 64-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc64_new(lua_State *L)
{
    a_u64 poly = 0;
    int reversed = 0;
    struct crc64 *ctx;
    int top = lua_gettop(L);
    if (top > 1)
    {
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 2);
    }
    poly = lua_u64_get(L, 1);
    ctx = lua_newclass(L, struct crc64);
    lua_registry_get(L, liba_crc64_new);
    lua_setmetatable(L, -2);
    if (reversed)
    {
        a_crc64l_init(ctx->table, poly);
        ctx->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx->table, poly);
        ctx->eval = a_crc64m;
    }
    return 1;
}

/***
 generate for 64-bit Cyclic Redundancy Check
 @tparam a.crc64 ctx 64-bit Cyclic Redundancy Check userdata
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc64 64-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc64_gen(lua_State *L)
{
    a_u64 poly = 0;
    int reversed = 0;
    struct crc64 *ctx;
    int top = lua_gettop(L);
    if (top > 2)
    {
        luaL_checktype(L, 3, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 3);
    }
    poly = lua_u64_get(L, 2);
    ctx = (struct crc64 *)lua_touserdata(L, 1);
    if (reversed)
    {
        a_crc64l_init(ctx->table, poly);
        ctx->eval = a_crc64l;
    }
    else
    {
        a_crc64m_init(ctx->table, poly);
        ctx->eval = a_crc64m;
    }
    lua_pushvalue(L, 1);
    return 1;
}

/***
 compute for 64-bit Cyclic Redundancy Check
 @tparam a.crc64 ctx 64-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc64_eval(lua_State *L)
{
    struct crc64 *const ctx = (struct crc64 *)lua_touserdata(L, 1);
    if (ctx)
    {
        size_t n = 0;
        a_u64 value = 0;
        char const *const p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u64_get(L, 3); }
        lua_u64_new(L, ctx->eval(ctx->table, p, n, value));
        return 1;
    }
    return 0;
}

/***
 pack a block and its 64-bit Cyclic Redundancy Check value
 @tparam a.crc64 ctx 64-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc64_pack(lua_State *L)
{
    struct crc64 *const ctx = (struct crc64 *)lua_touserdata(L, 1);
    if (ctx)
    {
        union
        {
            char const *s;
            a_byte *p;
        } u;
        size_t n = 0;
        a_u64 value = 0;
        char const *p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u64_get(L, 3); }
        u.s = lua_pushfstring(L, "%s        ", p) + n;
        value = ctx->eval(ctx->table, p, n, value);
        ctx->eval == a_crc64m
            ? a_u64_setb(u.p, value)
            : a_u64_setl(u.p, value);
        return 1;
    }
    return 0;
}

static int liba_crc64_set(lua_State *L)
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

static int liba_crc64_get(lua_State *L)
{
    struct crc64 const *const ctx = (struct crc64 const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x014FE58A: /* table */
        lua_array_u64_new(L, ctx->table, 0x100);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_crc64_new);
        lua_pushstring(L, "table");
        lua_array_u64_new(L, ctx->table, 0x100);
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_crc64_(lua_State *L)
{
    lua_pushcfunction(L, liba_crc64_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_crc64(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_crc64_new},
        {"gen", liba_crc64_gen},
        {"eval", liba_crc64_eval},
        {"pack", liba_crc64_pack},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_crc64_set},
        {"__index", liba_crc64_get},
        {"__call", liba_crc64_eval},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_crc64_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.crc64");
    lua_registry_set(L, liba_crc64_new);

    return 1;
}
