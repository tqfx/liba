/***
 32-bit Cyclic Redundancy Check
 @module liba.crc32
*/

#include "crc32.h"
#include "a/crc.h"

struct CRC32
{
    a_u32 table[0x100];
    a_u32 (*eval)(a_u32 const table[0x100], void const *pdata, a_size nbyte, a_u32 value);
};

/***
 constructor for 32-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc32 32-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc32_new(lua_State *L)
{
    a_u32 poly = 0;
    int reversed = 0;
    struct CRC32 *ctx;
    int top = lua_gettop(L);
    if (top > 1)
    {
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 2);
    }
    poly = lua_u32_get(L, 1);
    ctx = lua_newclass(L, struct CRC32);
    lua_registry_get(L, liba_crc32_new);
    lua_setmetatable(L, -2);
    if (reversed)
    {
        a_crc32l_init(ctx->table, poly);
        ctx->eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx->table, poly);
        ctx->eval = a_crc32m;
    }
    return 1;
}

/***
 generate for 32-bit Cyclic Redundancy Check
 @tparam a.crc32 ctx 32-bit Cyclic Redundancy Check userdata
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc32 32-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc32_gen(lua_State *L)
{
    a_u32 poly = 0;
    int reversed = 0;
    struct CRC32 *ctx;
    int top = lua_gettop(L);
    if (top > 2)
    {
        luaL_checktype(L, 3, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 3);
    }
    poly = lua_u32_get(L, 2);
    ctx = (struct CRC32 *)lua_touserdata(L, 1);
    if (reversed)
    {
        a_crc32l_init(ctx->table, poly);
        ctx->eval = a_crc32l;
    }
    else
    {
        a_crc32m_init(ctx->table, poly);
        ctx->eval = a_crc32m;
    }
    lua_pushvalue(L, 1);
    return 1;
}

/***
 calculate for 32-bit Cyclic Redundancy Check
 @tparam a.crc32 ctx 32-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc32_eval(lua_State *L)
{
    struct CRC32 *const ctx = (struct CRC32 *)lua_touserdata(L, 1);
    if (ctx)
    {
        size_t n = 0;
        a_u32 value = 0;
        char const *const p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u32_get(L, 3); }
        lua_u32_new(L, ctx->eval(ctx->table, p, n, value));
        return 1;
    }
    return 0;
}

/***
 pack a block and its 32-bit Cyclic Redundancy Check value
 @tparam a.crc32 ctx 32-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc32_pack(lua_State *L)
{
    struct CRC32 *const ctx = (struct CRC32 *)lua_touserdata(L, 1);
    if (ctx)
    {
        union
        {
            char const *s;
            a_byte *p;
        } u;
        size_t n = 0;
        a_u32 value = 0;
        char const *p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u32_get(L, 3); }
        value = ctx->eval(ctx->table, p, n, value);
        u.s = lua_pushfstring(L, "%s    ", p) + n;
        if (ctx->eval == a_crc32m)
        {
            u.p[0] = (a_byte)(value >> 0x18);
            u.p[1] = (a_byte)(value >> 0x10);
            u.p[2] = (a_byte)(value >> 0x08);
            u.p[3] = (a_byte)(value >> 0x00);
        }
        else
        {
            u.p[0] = (a_byte)(value >> 0x00);
            u.p[1] = (a_byte)(value >> 0x08);
            u.p[2] = (a_byte)(value >> 0x10);
            u.p[3] = (a_byte)(value >> 0x18);
        }
        return 1;
    }
    return 0;
}

static int liba_crc32_set(lua_State *L)
{
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
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

static int liba_crc32_get(lua_State *L)
{
    struct CRC32 const *const ctx = (struct CRC32 const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x014FE58A: // table
        lua_array_u32_new(L, ctx->table, 0x100);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_crc32_new);
        lua_pushstring(L, "table");
        lua_array_u32_new(L, ctx->table, 0x100);
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_crc32_(lua_State *L)
{
    lua_pushcfunction(L, liba_crc32_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_crc32(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_crc32_new},
        {"gen", liba_crc32_gen},
        {"eval", liba_crc32_eval},
        {"pack", liba_crc32_pack},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_crc32_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_crc32_set},
        {"__index", liba_crc32_get},
        {"__call", liba_crc32_eval},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.crc32");
    lua_registry_set(L, liba_crc32_new);

    return 1;
}
