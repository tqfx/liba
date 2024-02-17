/***
 8-bit Cyclic Redundancy Check
 @module liba.crc8
*/

#include "crc8.h"
#include "a/crc.h"

struct crc8
{
    a_u8 table[0x100];
};

/***
 constructor for 8-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc8 8-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc8_new(lua_State *L)
{
    a_u8 poly = 0;
    int reversed = 0;
    struct crc8 *ctx;
    int top = lua_gettop(L);
    if (top > 1)
    {
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 2);
    }
    poly = lua_u8_get(L, 1);
    ctx = lua_newclass(L, struct crc8);
    lua_registry_get(L, liba_crc8_new);
    lua_setmetatable(L, -2);
    reversed ? a_crc8l_init(ctx->table, poly)
             : a_crc8m_init(ctx->table, poly);
    return 1;
}

/***
 generate for 8-bit Cyclic Redundancy Check
 @tparam a.crc8 ctx 8-bit Cyclic Redundancy Check userdata
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc8 8-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc8_gen(lua_State *L)
{
    a_u8 poly = 0;
    int reversed = 0;
    struct crc8 *ctx;
    int top = lua_gettop(L);
    if (top > 2)
    {
        luaL_checktype(L, 3, LUA_TBOOLEAN);
        reversed = lua_toboolean(L, 3);
    }
    poly = lua_u8_get(L, 2);
    ctx = (struct crc8 *)lua_touserdata(L, 1);
    reversed ? a_crc8l_init(ctx->table, poly)
             : a_crc8m_init(ctx->table, poly);
    lua_pushvalue(L, 1);
    return 1;
}

/***
 calculate for 8-bit Cyclic Redundancy Check
 @tparam a.crc8 ctx 8-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc8_eval(lua_State *L)
{
    struct crc8 *const ctx = (struct crc8 *)lua_touserdata(L, 1);
    if (ctx)
    {
        size_t n = 0;
        a_u8 value = 0;
        char const *const p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u8_get(L, 3); }
        lua_u8_new(L, a_crc8(ctx->table, p, n, value));
        return 1;
    }
    return 0;
}

/***
 pack a block and its 8-bit Cyclic Redundancy Check value
 @tparam a.crc8 ctx 8-bit Cyclic Redundancy Check userdata
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc8_pack(lua_State *L)
{
    struct crc8 *const ctx = (struct crc8 *)lua_touserdata(L, 1);
    if (ctx)
    {
        union
        {
            char const *s;
            a_byte *p;
        } u;
        size_t n = 0;
        a_u8 value = 0;
        char const *p = luaL_checklstring(L, 2, &n);
        if (lua_gettop(L) > 2) { value = lua_u8_get(L, 3); }
        u.s = lua_pushfstring(L, "%s ", p) + n;
        *u.p = a_crc8(ctx->table, p, n, value);
        return 1;
    }
    return 0;
}

static int liba_crc8_set(lua_State *L)
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

static int liba_crc8_get(lua_State *L)
{
    struct crc8 const *const ctx = (struct crc8 const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x014FE58A: // table
        lua_array_u8_new(L, ctx->table, 0x100);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_crc8_new);
        lua_pushstring(L, "table");
        lua_array_u8_new(L, ctx->table, 0x100);
        lua_rawset(L, -3);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_crc8_(lua_State *L)
{
    lua_pushcfunction(L, liba_crc8_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_crc8(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_crc8_new},
        {"gen", liba_crc8_gen},
        {"eval", liba_crc8_eval},
        {"pack", liba_crc8_pack},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_crc8_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_crc8_set},
        {"__index", liba_crc8_get},
        {"__call", liba_crc8_eval},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.crc8");
    lua_registry_set(L, liba_crc8_new);

    return 1;
}
