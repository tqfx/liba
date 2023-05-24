#ifndef L_API_H
#define L_API_H

#if !defined L_API
#define L_API
#endif /* L_API */
#if !defined L_NUM
#define L_NUM a_float_t
#endif /* L_NUM */
#if !defined L_INT
#define L_INT lua_Integer
#endif /* L_INT */

#if defined(_MSC_VER)
#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "a/a.h"
#include "a/host/a.h"

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

typedef struct
{
    char const *name;
    lua_CFunction func;
} l_func_s;

typedef struct
{
    char const *name;
    char const *data;
} l_str_s;

typedef struct
{
    char const *name;
    L_INT data;
} l_int_s;

typedef struct
{
    char const *name;
    L_NUM data;
} l_num_s;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 501)
LUALIB_API void luaL_checkversion_(lua_State *L, lua_Number ver, size_t sz);
#define luaL_checkversion(L) luaL_checkversion_(L, LUA_VERSION_NUM, sizeof(lua_Number) + sizeof(lua_Integer) * 16)
#else /* !LUA_VERSION_NUM */
#define luaL_checkversion(L)
#endif /* LUA_VERSION_NUM */

#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
#define lua_rawsetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_insert(L, -2), lua_rawset(L, idx))
#define lua_rawgetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_rawget(L, idx))
#define lua_rawlen(L, i) lua_objlen(L, i)
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

LUALIB_API void luaL_where(lua_State *L, int lvl);
LUALIB_API int luaL_error(lua_State *L, char const *fmt, ...);

L_API void *l_alloc(lua_State *L, void const *ptr, size_t siz);

L_API void l_func_reg(lua_State *L, int idx, l_func_s const *tab);
L_API void l_func_set(lua_State *L, int idx, char const *name, lua_CFunction func);

L_API void l_str_reg(lua_State *L, int idx, l_str_s const *tab);
L_API char const *l_str_get(lua_State *L, int idx, char const *name);
L_API void l_str_set(lua_State *L, int idx, char const *name, char const *data);

L_API void l_int_reg(lua_State *L, int idx, l_int_s const *tab);
L_API void l_int_set(lua_State *L, int idx, char const *name, L_INT data);
L_API L_INT l_int_get(lua_State *L, int idx, char const *name);

L_API void l_num_reg(lua_State *L, int idx, l_num_s const *tab);
L_API void l_num_set(lua_State *L, int idx, char const *name, L_NUM data);
L_API L_NUM l_num_get(lua_State *L, int idx, char const *name);

L_API void l_array_str_get(lua_State *L, int idx, char const **ptr, unsigned int num);
L_API void l_array_str_set(lua_State *L, int idx, char const *const *ptr, unsigned int num);

L_API void l_array_int_get(lua_State *L, int idx, L_INT *ptr, unsigned int num);
L_API void l_array_int_set(lua_State *L, int idx, L_INT const *ptr, unsigned int num);

L_API void l_array_num_get(lua_State *L, int idx, L_NUM *ptr, unsigned int num);
L_API void l_array_num_set(lua_State *L, int idx, L_NUM const *ptr, unsigned int num);

L_API L_NUM *l_table_num_get(lua_State *L, int idx, L_NUM const *ptr, size_t *num);
L_API void l_table_num_set(lua_State *L, int idx, L_NUM const *ptr, size_t num, unsigned int col);

L_API void l_stack_type(lua_State *L, int line);
L_API void l_stack_show(lua_State *L, int line);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define L_COUNT(A) (sizeof(A) / sizeof(*(A)))
#define L_STACK(L) l_stack_show(L, __LINE__)
#define L_NAME "__name"
#define L_NEW "__call"
#define L_DIE "__gc"
#define L_LEN "__len"
#define L_GET "__index"
#define L_SET "__newindex"
#define L_PRI "__tostring"
#define L_UNM "__unm"
#define L_ADD "__add"
#define L_SUB "__sub"
#define L_MUL "__mul"
#define L_DIV "__div"
#define L_POW "__pow"
#define L_EQ "__eq"
#define L_LT "__lt"
#define L_LE "__le"

#endif /* api.h */
