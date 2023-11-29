#ifndef L_A_H
#define L_A_H

#include "api.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int luaopen_liba(lua_State *L);
A_PUBLIC int luaopen_liba_mf(lua_State *L);
A_PUBLIC int luaopen_liba_tf(lua_State *L);
A_PUBLIC int luaopen_liba_pid(lua_State *L);
A_PUBLIC int luaopen_liba_pid_fuzzy(lua_State *L);
A_PUBLIC int luaopen_liba_pid_neuron(lua_State *L);
A_PUBLIC int luaopen_liba_complex(lua_State *L);
A_PUBLIC int luaopen_liba_polytraj3(lua_State *L);
A_PUBLIC int luaopen_liba_polytraj5(lua_State *L);
A_PUBLIC int luaopen_liba_polytraj7(lua_State *L);
A_PUBLIC int luaopen_liba_version(lua_State *L);
A_PUBLIC int liba_setter(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a.h */
