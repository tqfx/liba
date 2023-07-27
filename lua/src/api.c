#include "api.h"

void *l_alloc(lua_State *const L, void const *const ptr, size_t const siz)
{
    void *ud;
    lua_Alloc alloc = lua_getallocf(L, &ud);
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    return alloc(ud, (void *)(intptr_t)ptr, 0, siz);
}

void l_func_set(lua_State *const L, int const idx, char const *const name, lua_CFunction const func)
{
    /* table[name]=func */
    lua_pushstring(L, name);
    lua_pushcclosure(L, func, 0);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void l_func_reg(lua_State *const L, int idx, l_func_s const *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=func */
        lua_pushstring(L, tab->name);
        lua_pushcclosure(L, tab->func, 0);
        lua_rawset(L, idx);
        ++tab;
    }
}

void l_str_set(lua_State *const L, int const idx, char const *const name, char const *const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushstring(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

char const *l_str_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    char const *data = lua_tostring(L, -1);
    lua_pop(L, 1);
    return data;
}

void l_str_reg(lua_State *const L, int idx, l_str_s const *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushstring(L, tab->data);
        lua_rawset(L, idx);
        ++tab;
    }
}

void l_int_set(lua_State *const L, int const idx, char const *const name, L_INT const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushinteger(L, (lua_Integer)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

L_INT l_int_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    L_INT x = (L_INT)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return x;
}

void l_int_reg(lua_State *const L, int idx, l_int_s const *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushinteger(L, (lua_Integer)tab->data);
        lua_rawset(L, idx);
        ++tab;
    }
}

void l_num_set(lua_State *const L, int const idx, char const *const name, L_NUM const data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushnumber(L, (lua_Number)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

L_NUM l_num_get(lua_State *const L, int const idx, char const *const name)
{
    /* data=table[name] */
    lua_pushstring(L, name);
    lua_rawget(L, idx < 0 ? idx - 1 : idx);
    L_NUM x = (L_NUM)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return x;
}

void l_num_reg(lua_State *const L, int idx, l_num_s const *tab)
{
    idx = idx < 0 ? idx - 2 : idx;
    while (tab->name)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushnumber(L, (lua_Number)tab->data);
        lua_rawset(L, idx);
        ++tab;
    }
}

void l_array_str_get(lua_State *const L, int const idx, char const **const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len)
    {
        num = (unsigned int)len;
    }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = lua_tostring(L, -1);
        lua_pop(L, 1);
    }
}

void l_array_str_set(lua_State *const L, int idx, char const *const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushstring(L, ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

void l_array_int_get(lua_State *const L, int const idx, L_INT *const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len)
    {
        num = (unsigned int)len;
    }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = (L_INT)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
}

void l_array_int_set(lua_State *const L, int idx, L_INT const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushinteger(L, (lua_Integer)ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

void l_array_num_get(lua_State *const L, int const idx, L_NUM *const ptr, unsigned int num)
{
    size_t len = (size_t)lua_rawlen(L, idx);
    if (num > len)
    {
        num = (unsigned int)len;
    }
    for (unsigned int i = num; i--; num = i)
    {
        lua_rawgeti(L, idx, (int)num);
        ptr[i] = (L_NUM)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
}

void l_array_num_set(lua_State *const L, int idx, L_NUM const *const ptr, unsigned int num)
{
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = num; i--; num = i)
    {
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, idx, (int)num);
    }
}

size_t l_table_num_len(lua_State *const L, int idx);
size_t l_table_num_len(lua_State *const L, int const idx) // NOLINT(misc-no-recursion)
{
    size_t num = 0;
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            ++num;
        }
        else if (e == LUA_TTABLE)
        {
            num += l_table_num_len(L, -1);
        }
        lua_pop(L, 1);
    }
    return num;
}

L_NUM *l_table_num_ptr(lua_State *const L, int idx, L_NUM *ptr);
L_NUM *l_table_num_ptr(lua_State *const L, int const idx, L_NUM *ptr) // NOLINT(misc-no-recursion)
{
    size_t n = (size_t)lua_rawlen(L, idx);
    for (unsigned int i = 0; i++ != n;)
    {
        lua_rawgeti(L, idx, (int)i);
        int e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            *ptr++ = (L_NUM)lua_tonumber(L, -1);
        }
        else if (e == LUA_TTABLE)
        {
            ptr = l_table_num_ptr(L, -1, ptr);
        }
        lua_pop(L, 1);
    }
    return ptr;
}

L_NUM *l_table_num_get(lua_State *const L, int const idx, L_NUM const *const ptr, size_t *num)
{
    L_NUM *ret = (L_NUM *)(intptr_t)ptr; // NOLINT(performance-no-int-to-ptr)
    if (lua_type(L, idx) == LUA_TTABLE)
    {
        size_t tmp = 0;
        num = num ? num : &tmp;
        *num = l_table_num_len(L, idx);
        if (*num)
        {
            ret = (L_NUM *)l_alloc(L, ret, sizeof(L_NUM) * *num);
            l_table_num_ptr(L, idx, ret);
        }
    }
    return ret;
}

void l_table_num_set(lua_State *const L, int idx, L_NUM const *ptr, size_t num, unsigned int const col)
{
    if (!col)
    {
        l_array_num_set(L, idx, ptr, (unsigned int)num);
        return;
    }
    size_t n = num / col;
    idx = idx < 0 ? idx - 1 : idx;
    for (unsigned int i = 0; i++ != n; ptr += col)
    {
        lua_createtable(L, (int)col, 0);
        l_array_num_set(L, -1, ptr, col);
        lua_rawseti(L, idx, (int)i);
    }
    num %= col;
    if (num)
    {
        lua_createtable(L, (int)num, 0);
        l_array_num_set(L, -1, ptr, (unsigned int)num);
        lua_rawseti(L, idx, (int)n + 1);
    }
}

#include <stdio.h>

void l_stack_type(lua_State *const L, int const line)
{
    char const *map[] = {"nil", "bool", "ptr", "num", "str", "tab", "func", "data", "thrd"};
    int const n = lua_gettop(L);
    printf("%i:", line);
    for (int i = 0; i++ != n;)
    {
        printf(" %s", map[lua_type(L, i) % (int)sizeof(map)]);
    }
    putchar('\n');
}

void l_stack_show(lua_State *const L, int line)
{
    int const n = lua_gettop(L);
    printf("%i:", line);
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
            printf("func:%p", L_FUNC2P(lua_tocfunction(L, i)));
            break;
        }
        case LUA_TUSERDATA:
            printf("data:%p", lua_touserdata(L, i));
            break;
        case LUA_TTHREAD:
            printf("thrd:%p", (void *)lua_tothread(L, i));
            break;
        default:
            printf("%s", "nil");
        }
    }
    putchar('\n');
}
