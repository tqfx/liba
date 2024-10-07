#ifndef LUA_LIBA_A_H
#define LUA_LIBA_A_H

#if defined(_MSC_VER)
#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "a/a.h"
#if __has_warning("-Wcomma")
#pragma clang diagnostic ignored "-Wcomma"
#endif /* -Wcomma */
#if __has_warning("-Wdocumentation")
#pragma clang diagnostic ignored "-Wdocumentation"
#endif /* -Wdocumentation */
#if __has_warning("-Wdocumentation-unknown-command")
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif /* -Wdocumentation-unknown-command */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#include <lua.h>

#if !defined LUA_INT
#define LUA_INT lua_Integer
#endif /* LUA_INT */
#if !defined LUA_NUM
#define LUA_NUM a_float
#endif /* LUA_NUM */

typedef struct
{
    char const *name;
    lua_CFunction func;
} lua_fun;

typedef struct
{
    char const *name;
    char const *data;
} lua_str;

typedef struct
{
    char const *name;
    LUA_INT data;
} lua_int;

typedef struct
{
    char const *name;
    LUA_NUM data;
} lua_num;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 503)
#define lua_newclass(L, T) (T *)lua_newuserdatauv(L, sizeof(T), 0)
#else /* !LUA_VERSION_NUM */
#define lua_newclass(L, T) (T *)lua_newuserdata(L, sizeof(T))
#endif /* LUA_VERSION_NUM */

#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 501)
LUALIB_API void luaL_checkversion_(lua_State *L, lua_Number ver, size_t sz);
#define luaL_checkversion(L) luaL_checkversion_(L, LUA_VERSION_NUM, sizeof(lua_Number) + sizeof(lua_Integer) * 16)
#else /* !LUA_VERSION_NUM */
#define luaL_checkversion(L) (void)0
#endif /* LUA_VERSION_NUM */

#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
LUALIB_API void luaL_register(lua_State *L, char const *libname, lua_fun const *l);
#define lua_rawsetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_insert(L, -2), lua_rawset(L, idx))
#define lua_rawgetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_rawget(L, idx))
#define lua_rawlen lua_objlen
#endif /* LUA_VERSION_NUM */

LUALIB_API char const *luaL_checklstring(lua_State *L, int numArg, size_t *l);
LUALIB_API char const *luaL_optlstring(lua_State *L, int numArg, char const *def, size_t *l);

LUALIB_API lua_Integer luaL_checkinteger(lua_State *L, int numArg);
LUALIB_API lua_Integer luaL_optinteger(lua_State *L, int nArg, lua_Integer def);

LUALIB_API lua_Number luaL_checknumber(lua_State *L, int numArg);
LUALIB_API lua_Number luaL_optnumber(lua_State *L, int nArg, lua_Number def);

LUALIB_API void luaL_checkstack(lua_State *L, int sz, char const *msg);
LUALIB_API void luaL_checktype(lua_State *L, int narg, int t);
LUALIB_API void luaL_checkany(lua_State *L, int narg);

LUALIB_API int luaL_error(lua_State *L, char const *fmt, ...);
LUALIB_API void luaL_where(lua_State *L, int lvl);

void lua_u8_new(lua_State *L, a_u8 value);
a_u8 lua_u8_get(lua_State *L, int idx);
void lua_u16_new(lua_State *L, a_u16 value);
a_u16 lua_u16_get(lua_State *L, int idx);
void lua_u32_new(lua_State *L, a_u32 value);
a_u32 lua_u32_get(lua_State *L, int idx);
void lua_u64_new(lua_State *L, a_u64 value);
a_u64 lua_u64_get(lua_State *L, int idx);

void *lua_alloc(lua_State *L, void const *ptr, size_t siz);

void lua_registry_get(lua_State *L, int (*fn)(lua_State *));
void lua_registry_set(lua_State *L, int (*fn)(lua_State *));

void lua_fun_reg(lua_State *L, int idx, lua_fun const *tab, size_t len);
void lua_fun_set(lua_State *L, int idx, char const *name, lua_CFunction func);

void lua_str_reg(lua_State *L, int idx, lua_str const *tab, size_t len);
void lua_str_set(lua_State *L, int idx, char const *name, char const *data);
char const *lua_str_get(lua_State *L, int idx, char const *name);

void lua_int_reg(lua_State *L, int idx, lua_int const *tab, size_t len);
void lua_int_set(lua_State *L, int idx, char const *name, LUA_INT data);
LUA_INT lua_int_get(lua_State *L, int idx, char const *name);

void lua_num_reg(lua_State *L, int idx, lua_num const *tab, size_t len);
void lua_num_set(lua_State *L, int idx, char const *name, LUA_NUM data);
LUA_NUM lua_num_get(lua_State *L, int idx, char const *name);

void lua_array_u8_new(lua_State *L, a_u8 const *ptr, unsigned int num);
void lua_array_u16_new(lua_State *L, a_u16 const *ptr, unsigned int num);
void lua_array_u32_new(lua_State *L, a_u32 const *ptr, unsigned int num);
void lua_array_u64_new(lua_State *L, a_u64 const *ptr, unsigned int num);

void lua_array_str_new(lua_State *L, char const *const *ptr, unsigned int num);
void lua_array_str_get(lua_State *L, int idx, char const **ptr, unsigned int num);
void lua_array_str_set(lua_State *L, int idx, char const *const *ptr, unsigned int num);

void lua_array_int_new(lua_State *L, LUA_INT const *ptr, unsigned int num);
void lua_array_int_get(lua_State *L, int idx, LUA_INT *ptr, unsigned int num);
void lua_array_int_set(lua_State *L, int idx, LUA_INT const *ptr, unsigned int num);

void lua_array_num_new(lua_State *L, LUA_NUM const *ptr, unsigned int num);
void lua_array_num_get(lua_State *L, int idx, LUA_NUM *ptr, unsigned int num);
void lua_array_num_set(lua_State *L, int idx, LUA_NUM const *ptr, unsigned int num);

unsigned int lua_table_num_len(lua_State *L, int idx, int dim);
LUA_NUM *lua_table_num_ptr(lua_State *L, int idx, LUA_NUM *ptr, int dim);
LUA_NUM *lua_table_num_get(lua_State *L, int idx, LUA_NUM const *ptr, unsigned int *num, int dim);

void lua_stack_view(lua_State *L, unsigned int line);
// #define LUA_STACK(L) lua_stack_view(L, __LINE__)

A_PUBLIC int luaopen_liba(lua_State *L);
A_PUBLIC int luaopen_liba_complex(lua_State *L);
A_PUBLIC int luaopen_liba_crc16(lua_State *L);
A_PUBLIC int luaopen_liba_crc32(lua_State *L);
A_PUBLIC int luaopen_liba_crc64(lua_State *L);
A_PUBLIC int luaopen_liba_crc8(lua_State *L);
A_PUBLIC int luaopen_liba_hpf(lua_State *L);
A_PUBLIC int luaopen_liba_lpf(lua_State *L);
A_PUBLIC int luaopen_liba_mf(lua_State *L);
A_PUBLIC int luaopen_liba_pid(lua_State *L);
A_PUBLIC int luaopen_liba_pid_fuzzy(lua_State *L);
A_PUBLIC int luaopen_liba_pid_neuro(lua_State *L);
A_PUBLIC int luaopen_liba_regress_simple(lua_State *L);
A_PUBLIC int luaopen_liba_tf(lua_State *L);
A_PUBLIC int luaopen_liba_trajbell(lua_State *L);
A_PUBLIC int luaopen_liba_trajpoly3(lua_State *L);
A_PUBLIC int luaopen_liba_trajpoly5(lua_State *L);
A_PUBLIC int luaopen_liba_trajpoly7(lua_State *L);
A_PUBLIC int luaopen_liba_trajtrap(lua_State *L);
A_PUBLIC int luaopen_liba_version(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a.h */
