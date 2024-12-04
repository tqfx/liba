#if !defined _GNU_SOURCE && defined(__linux__)
#define _GNU_SOURCE 1
#endif /* _GNU_SOURCE */
#include "a.h"

void *lua_alloc(lua_State *L, void const *ptr_, size_t siz)
{
    void *ud = (void *)(a_uptr)ptr_; /* NOLINT */
    void *ptr = (void *)(a_uptr)ptr_; /* NOLINT */
    return lua_getallocf(L, &ud)(ud, ptr, 0, siz);
}

void lua_registry_get(lua_State *L, int (*fn)(lua_State *))
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *)(a_uptr)fn); /* NOLINT */
}

void lua_registry_set(lua_State *L, int (*fn)(lua_State *))
{
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void *)(a_uptr)fn); /* NOLINT */
}

void lua_fun_set(lua_State *L, int idx, char const *name, lua_CFunction func)
{
    /* table[name]=func */
    lua_pushstring(L, name);
    lua_pushcclosure(L, func, 0);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

void lua_fun_reg(lua_State *L, int idx, lua_fun const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=func */
        lua_pushstring(L, tab->name);
        lua_pushcclosure(L, tab->func, 0);
        lua_rawset(L, idx);
    }
}

void lua_str_set(lua_State *L, int idx, char const *name, char const *data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushstring(L, data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

char const *lua_str_get(lua_State *L, int idx, char const *name)
{
    /* data=table[name] */
    char const *s;
    lua_getfield(L, idx, name);
    s = lua_tostring(L, -1);
    lua_pop(L, 1);
    return s;
}

void lua_str_reg(lua_State *L, int idx, lua_str const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushstring(L, tab->data);
        lua_rawset(L, idx);
    }
}

void lua_int_set(lua_State *L, int idx, char const *name, LUA_INT data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushinteger(L, (lua_Integer)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

LUA_INT lua_int_get(lua_State *L, int idx, char const *name)
{
    /* data=table[name] */
    lua_Integer x;
    lua_getfield(L, idx, name);
    x = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return (LUA_INT)x;
}

void lua_int_reg(lua_State *L, int idx, lua_int const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushinteger(L, (lua_Integer)tab->data);
        lua_rawset(L, idx);
    }
}

void lua_num_set(lua_State *L, int idx, char const *name, LUA_NUM data)
{
    /* table[name]=data */
    lua_pushstring(L, name);
    lua_pushnumber(L, (lua_Number)data);
    lua_rawset(L, idx < 0 ? idx - 2 : idx);
}

LUA_NUM lua_num_get(lua_State *L, int idx, char const *name)
{
    /* data=table[name] */
    lua_Number x;
    lua_getfield(L, idx, name);
    x = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return (LUA_NUM)x;
}

void lua_num_reg(lua_State *L, int idx, lua_num const *tab, size_t len)
{
    for (idx = idx < 0 ? idx - 2 : idx; len--; ++tab)
    {
        /* table[name]=data */
        lua_pushstring(L, tab->name);
        lua_pushnumber(L, (lua_Number)tab->data);
        lua_rawset(L, idx);
    }
}

unsigned int lua_array_len(lua_State *L, int idx)
{
    if (luaL_callmeta(L, idx, "__len"))
    {
        unsigned int n;
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 501)
        int isnum;
        n = (unsigned int)lua_tointegerx(L, -1, &isnum);
        if (A_UNLIKELY(!isnum))
        {
            luaL_error(L, "object length is not an integer");
        }
#else /* !LUA_VERSION_NUM */
        n = (unsigned int)lua_tointeger(L, -1);
#endif /* LUA_VERSION_NUM */
        lua_pop(L, 1);
        return n;
    }
    return (unsigned int)lua_rawlen(L, idx);
}

void lua_array_str_get(lua_State *L, int idx, char const **ptr, unsigned int num)
{
    unsigned int i, n = lua_array_len(L, idx);
    if (num < n) { n = num; }
    for (i = n; i--; n = i)
    {
        lua_geti(L, idx, (lua_Integer)n);
        ptr[i] = lua_tostring(L, -1);
        lua_pop(L, 1);
    }
}

void lua_array_str_set(lua_State *L, int idx, char const *const *ptr, unsigned int num)
{
    unsigned int i;
    idx = idx < 0 ? idx - 1 : idx;
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushstring(L, ptr[i]);
        lua_rawseti(L, idx, n);
    }
}

void lua_array_str_new(lua_State *L, char const *const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushstring(L, ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

void lua_array_int_get(lua_State *L, int idx, LUA_INT *ptr, unsigned int num)
{
    unsigned int i, n = lua_array_len(L, idx);
    if (num < n) { n = num; }
    for (i = n; i--; n = i)
    {
        lua_geti(L, idx, (lua_Integer)n);
        ptr[i] = (LUA_INT)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
}

void lua_array_int_set(lua_State *L, int idx, LUA_INT const *ptr, unsigned int num)
{
    unsigned int i;
    idx = idx < 0 ? idx - 1 : idx;
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushinteger(L, (lua_Integer)ptr[i]);
        lua_rawseti(L, idx, n);
    }
}

void lua_array_int_new(lua_State *L, LUA_INT const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushinteger(L, (lua_Integer)ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

unsigned int lua_array_num_len(lua_State *L, int idx, int dim) /* NOLINT(misc-no-recursion) */
{
    unsigned int i = 0, n = lua_array_len(L, idx), num = 0;
    for (--dim; i++ != n;)
    {
        int e;
        lua_geti(L, idx, (lua_Integer)i);
        e = lua_type(L, -1);
        if (e == LUA_TNUMBER) { ++num; }
        else if (e == LUA_TTABLE && dim > 0)
        {
            num += lua_array_num_len(L, -1, dim);
        }
        lua_pop(L, 1);
    }
    return num;
}

LUA_NUM *lua_array_num_ptr(lua_State *L, int idx, LUA_NUM *ptr, int dim) /* NOLINT(misc-no-recursion) */
{
    unsigned int i = 0, n = lua_array_len(L, idx);
    for (--dim; i++ != n;)
    {
        int e;
        lua_geti(L, idx, (lua_Integer)i);
        e = lua_type(L, -1);
        if (e == LUA_TNUMBER)
        {
            *ptr++ = (LUA_NUM)lua_tonumber(L, -1);
        }
        else if (e == LUA_TTABLE && dim > 0)
        {
            ptr = lua_array_num_ptr(L, -1, ptr, dim);
        }
        lua_pop(L, 1);
    }
    return ptr;
}

LUA_NUM *lua_array_num_get(lua_State *L, int idx, LUA_NUM const *ptr, unsigned int *num, int dim)
{
    LUA_NUM *p = (LUA_NUM *)(a_uptr)ptr; /* NOLINT(performance-no-int-to-ptr) */
    unsigned int n = lua_array_num_len(L, idx, dim), n_ = 0;
    if (!num) { num = &n_; }
    if (n > *num)
    {
        p = (LUA_NUM *)lua_alloc(L, p, sizeof(LUA_NUM) * n);
    }
    lua_array_num_ptr(L, idx, p, dim);
    *num = n;
    return p;
}

void lua_array_num_set(lua_State *L, int idx, LUA_NUM const *ptr, unsigned int num)
{
    unsigned int i;
    idx = idx < 0 ? idx - 1 : idx;
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, idx, n);
    }
}

void lua_array_num_new(lua_State *L, LUA_NUM const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_pushnumber(L, (lua_Number)ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

#include <stdio.h>
#include <stdlib.h>
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf sprintf_s
#endif /* _MSC_VER */

void lua_u8_new(lua_State *L, a_u8 value)
{
    lua_pushinteger(L, (lua_Integer)value);
}

a_u8 lua_u8_get(lua_State *L, int idx)
{
    a_u8 value = 0;
    switch (lua_type(L, idx))
    {
    default: A_FALLTHROUGH;
    case LUA_TNUMBER: value = (a_u8)luaL_checkinteger(L, idx); break;
    case LUA_TSTRING: value = (a_u8)strtoul(lua_tostring(L, idx), NULL, 0);
    }
    return value;
}

void lua_u16_new(lua_State *L, a_u16 value)
{
    lua_pushinteger(L, (lua_Integer)value);
}

a_u16 lua_u16_get(lua_State *L, int idx)
{
    a_u16 value = 0;
    switch (lua_type(L, idx))
    {
    default: A_FALLTHROUGH;
    case LUA_TNUMBER: value = (a_u16)luaL_checkinteger(L, idx); break;
    case LUA_TSTRING: value = (a_u16)strtoul(lua_tostring(L, idx), NULL, 0);
    }
    return value;
}

void lua_u32_new(lua_State *L, a_u32 value)
{
    char buf[8 + 3];
    (void)snprintf(buf, sizeof(buf), "0x%08" A_PRI32 "X", value);
    lua_pushstring(L, buf);
}

a_u32 lua_u32_get(lua_State *L, int idx)
{
    a_u32 value = 0;
    switch (lua_type(L, idx))
    {
    default: A_FALLTHROUGH;
    case LUA_TNUMBER: value = (a_u32)luaL_checkinteger(L, idx); break;
    case LUA_TSTRING: value = (a_u32)strtoul(lua_tostring(L, idx), NULL, 0);
    }
    return value;
}

void lua_u64_new(lua_State *L, a_u64 value)
{
    char buf[16 + 3];
    (void)snprintf(buf, sizeof(buf), "0x%016" A_PRI64 "X", value);
    lua_pushstring(L, buf);
}

a_u64 lua_u64_get(lua_State *L, int idx)
{
    a_u64 value = 0;
    switch (lua_type(L, idx))
    {
    default: A_FALLTHROUGH;
    case LUA_TNUMBER: value = (a_u64)luaL_checkinteger(L, idx); break;
#if defined(_MSC_VER) && (_MSC_VER < 1800) ||        \
    defined(__WATCOMC__) && (__WATCOMC__ >= 1100) || \
    defined(__BORLANDC__) && (__BORLANDC__ >= 0x530)
    case LUA_TSTRING: value = _strtoui64(lua_tostring(L, idx), NULL, 0);
#elif ULONG_MAX > 0xFFFFFFFFUL
    case LUA_TSTRING: value = (a_u64)strtoul(lua_tostring(L, idx), NULL, 0);
#else /* >long */
    case LUA_TSTRING: value = (a_u64)strtoull(lua_tostring(L, idx), NULL, 0);
#endif /* long */
    }
    return value;
}

void lua_array_u8_new(lua_State *L, a_u8 const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_u8_new(L, ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

void lua_array_u16_new(lua_State *L, a_u16 const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_u16_new(L, ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

void lua_array_u32_new(lua_State *L, a_u32 const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_u32_new(L, ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

void lua_array_u64_new(lua_State *L, a_u64 const *ptr, unsigned int num)
{
    unsigned int i;
    lua_createtable(L, (int)num, 0);
    for (i = num; i--; num = i)
    {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
        lua_Integer n = (lua_Integer)num;
#else /* !LUA_VERSION_NUM */
        int n = (int)num;
#endif /* LUA_VERSION_NUM */
        lua_u64_new(L, ptr[i]);
        lua_rawseti(L, -2, n);
    }
}

#if defined(LUA_STACK)
void lua_stack_view(lua_State *L, unsigned int line)
{
    int i;
    int const n = lua_gettop(L);
    printf("%u:", line);
    for (i = 0; i++ != n;)
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
