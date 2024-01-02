/***
 algorithm library
 @module liba
*/

#include "a.h"
#include <stdio.h>
#include <inttypes.h>

/***
 Brian Kernighan and Dennis Ritchie
 @tparam number str string to be processed
 @treturn string hash value
 @function hash_bkdr
*/
static int liba_hash_bkdr(lua_State *const L)
{
    char str[11];
    a_u32_t val = 0;
    for (int Li = 1, Ln = lua_gettop(L); Li <= Ln; ++Li)
    {
        val = (a_u32_t)a_hash_bkdr(luaL_checklstring(L, Li, A_NULL), val);
    }
    (void)snprintf(str, 11, "0x%08" PRIX32, val);
    lua_pushstring(L, str);
    return 1;
}

#include "a/math.h"

/***
 square root of an unsigned integer
 @tparam integer x independent variable
 @tparam integer ... independent variables
 @treturn integer calculated result
 @function isqrt
*/
static int liba_isqrt(lua_State *const L)
{
    int const Ln = lua_gettop(L);
    for (int Li = 1; Li <= Ln; ++Li)
    {
        lua_Integer x = luaL_checkinteger(L, Li);
#if A_SIZE_MAX == A_U64_MAX
        x = (lua_Integer)a_u64_sqrt((a_u64_t)x);
#else /* !A_SIZE_MAX */
        x = (lua_Integer)a_u32_sqrt((a_u32_t)x);
#endif /* A_SIZE_MAX */
        lua_pushinteger(L, x);
    }
    return Ln;
}

/***
 reciprocal of square-root
 @tparam number x independent variable
 @tparam number ... independent variables
 @treturn number calculated result
 @function rsqrt
*/
static int liba_rsqrt(lua_State *const L)
{
    int const Ln = lua_gettop(L);
    for (int Li = 1; Li <= Ln; ++Li)
    {
        lua_Number x = luaL_checknumber(L, Li);
#if A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        x = (lua_Number)a_f64_rsqrt((a_f64_t)x);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        x = (lua_Number)a_f32_rsqrt((a_f32_t)x);
#else /* !A_FLOAT_TYPE */
        x = (lua_Number)(1 / sqrt((double)x));
#endif /* A_FLOAT_TYPE */
        lua_pushnumber(L, x);
    }
    return Ln;
}

#if !defined A_VERSION
#include "a/version.h"
#endif /* A_VERSION */

int luaopen_liba(lua_State *const L)
{
    luaL_checkversion(L);
    /***
     algorithm library
     @field VERSION algorithm library version string
     @table liba
    */
    static lua_fun_s const funcs[] = {
        {"hash_bkdr", liba_hash_bkdr},
        {"isqrt", liba_isqrt},
        {"rsqrt", liba_rsqrt},
    };
#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
    lua_fun_s func = {NULL, NULL};
    luaL_register(L, "liba", &func);
#else /* !LUA_VERSION_NUM */
    lua_createtable(L, 0, A_LEN(funcs) + 1);
#endif /* LUA_VERSION_NUM */
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "VERSION", A_VERSION);

    lua_pushstring(L, "complex");
    luaopen_liba_complex(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "mf");
    luaopen_liba_mf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid");
    luaopen_liba_pid(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid_fuzzy");
    luaopen_liba_pid_fuzzy(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid_neuro");
    luaopen_liba_pid_neuro(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytraj3");
    luaopen_liba_polytraj3(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytraj5");
    luaopen_liba_polytraj5(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytraj7");
    luaopen_liba_polytraj7(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "tf");
    luaopen_liba_tf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "version");
    luaopen_liba_version(L);
    lua_rawset(L, -3);

    return 1;
}

void *lua_alloc(lua_State *const L, void const *const ptr, size_t const siz)
{
    union
    {
        void const *ptr;
        void *p;
    } u = {ptr};
    void *ud = u.p;
    return lua_getallocf(L, &ud)(ud, u.p, 0, siz);
}

void lua_registry_get(lua_State *const L, int (*const fn)(lua_State *))
{
    union
    {
        int (*fn)(lua_State *);
        void *p;
    } u = {fn};
    lua_rawgetp(L, LUA_REGISTRYINDEX, u.p);
}

void lua_registry_set(lua_State *const L, int (*const fn)(lua_State *))
{
    union
    {
        int (*fn)(lua_State *);
        void *p;
    } u = {fn};
    lua_rawsetp(L, LUA_REGISTRYINDEX, u.p);
}

void lua_fun_set(lua_State *const L, int const idx, char const *const name, lua_CFunction const func)
{
    /* table[name]=func */
    lua_pushstring(L, name);
    lua_pushcclosure(L, func, 0);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void lua_fun_reg(lua_State *const L, int idx, lua_fun_s const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=func */
        lua_pushstring(L, tab->name);
        lua_pushcclosure(L, tab->func, 0);
        lua_rawset(L, idx);
    }
}

void lua_str_set(lua_State *const L, int const idx, char const *const name, char const *const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushstring(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

char const *lua_str_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    char const *s = lua_tostring(L, -1);
    lua_pop(L, 1);
    return s;
}

void lua_str_reg(lua_State *const L, int idx, lua_str_s const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushstring(L, tab->data);
        lua_rawset(L, idx);
    }
}

void lua_int_set(lua_State *const L, int const idx, char const *const name, LUA_INT const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushinteger(L, (lua_Integer)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

LUA_INT lua_int_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    LUA_INT x = (LUA_INT)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return x;
}

void lua_int_reg(lua_State *const L, int idx, lua_int_s const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushinteger(L, (lua_Integer)tab->data);
        lua_rawset(L, idx);
    }
}

void lua_num_set(lua_State *const L, int const idx, char const *const name, LUA_NUM const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushnumber(L, (lua_Number)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

LUA_NUM lua_num_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    LUA_NUM x = (LUA_NUM)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return x;
}

void lua_num_reg(lua_State *const L, int idx, lua_num_s const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushnumber(L, (lua_Number)tab->data);
        lua_rawset(L, idx);
    }
}

void lua_array_str_get(lua_State *const L, int const idx, char const **const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len) { num = (unsigned int)len; }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = lua_tostring(L, -1);
        lua_pop(L, 1);
    }
}

void lua_array_str_set(lua_State *const L, int idx, char const *const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushstring(L, ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

void lua_array_str_new(lua_State *const L, char const *const *const ptr, unsigned int num)
{
    lua_createtable(L, (int)num, 0);
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushstring(L, ptr[i]);
        lua_rawseti(L, -2, (int)num);
    }
}

void lua_array_int_get(lua_State *const L, int const idx, LUA_INT *const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len) { num = (unsigned int)len; }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = (LUA_INT)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
}

void lua_array_int_set(lua_State *const L, int idx, LUA_INT const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushinteger(L, (lua_Integer)ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

void lua_array_int_new(lua_State *const L, LUA_INT const *const ptr, unsigned int num)
{
    lua_createtable(L, (int)num, 0);
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushinteger(L, (lua_Integer)ptr[i]);
        lua_rawseti(L, -2, (int)num);
    }
}

void lua_array_num_get(lua_State *const L, int const idx, LUA_NUM *const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len) { num = (unsigned int)len; }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = (LUA_NUM)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
}

void lua_array_num_set(lua_State *const L, int idx, LUA_NUM const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

void lua_array_num_new(lua_State *const L, LUA_NUM const *const ptr, unsigned int num)
{
    lua_createtable(L, (int)num, 0);
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, -2, (int)num);
    }
}

size_t lua_table_num_len(lua_State *L, int idx);
size_t lua_table_num_len(lua_State *const L, int const idx) // NOLINT(misc-no-recursion)
{
    size_t num = 0;
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER) { ++num; }
        else if (e == LUA_TTABLE)
        {
            num += lua_table_num_len(L, -1);
        }
        lua_pop(L, 1);
    }
    return num;
}

LUA_NUM *lua_table_num_ptr(lua_State *L, int idx, LUA_NUM *ptr);
LUA_NUM *lua_table_num_ptr(lua_State *const L, int const idx, LUA_NUM *ptr) // NOLINT(misc-no-recursion)
{
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            *ptr++ = (LUA_NUM)lua_tonumber(L, -1);
        }
        else if (e == LUA_TTABLE)
        {
            ptr = lua_table_num_ptr(L, -1, ptr);
        }
        lua_pop(L, 1);
    }
    return ptr;
}

LUA_NUM *lua_table_num_get(lua_State *const L, int const idx, LUA_NUM const *const ptr, size_t *num)
{
    LUA_NUM *ret = (LUA_NUM *)(intptr_t)ptr; // NOLINT(performance-no-int-to-ptr)
    if (lua_type(L, idx) == LUA_TTABLE)
    {
        size_t tmp = 0;
        num = num ? num : &tmp;
        *num = lua_table_num_len(L, idx);
        if (*num)
        {
            ret = (LUA_NUM *)lua_alloc(L, ret, sizeof(LUA_NUM) * *num);
            lua_table_num_ptr(L, idx, ret);
        }
    }
    return ret;
}

#if defined(LUA_STACK)
void lua_stack_view(lua_State *const L, unsigned int const line)
{
    int const n = lua_gettop(L);
    printf("%u:", line);
    for (int i = 0; i++ != n;)
    {
        putchar(' ');
        switch (lua_type(L, i))
        {
        case LUA_TBOOLEAN:
            printf("%s", lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TLIGHTUSERDATA:
            printf("ptr:%p", lua_topointer(L, i));
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("\"%s\"", lua_tostring(L, i));
            break;
        case LUA_TTABLE:
            printf("tab:%p", lua_topointer(L, i));
            break;
        case LUA_TFUNCTION:
        {
            union
            {
                int (*fn)(lua_State *);
                void *p;
            } func = {lua_tocfunction(L, i)};
            printf("func:%p", func.p);
            break;
        }
        case LUA_TUSERDATA:
            printf("data:%p", lua_touserdata(L, i));
            break;
        case LUA_TTHREAD:
            printf("thrd:%p", (void *)lua_tothread(L, i));
            break;
        default: printf("%s", "nil");
        }
    }
    putchar('\n');
}
#endif /* LUA_STACK */
