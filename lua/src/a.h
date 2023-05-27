#ifndef L_A_H
#define L_A_H

#include "api.h"

#define L_MODULE(P, F) P##liba##F

#define LMODULE(F) L_MODULE(, _##F)
#define LMODULE1(F, a) L_MODULE(, _##F)(a)
#define LMODULE2(F, a, b) L_MODULE(, _##F)(a, b)
#define LMODULE_(F, L) L_MODULE(luaopen_, _##F)(L)
#define LMODULE0(L) L_MODULE(luaopen_, )(L)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE0(lua_State *L);
A_PUBLIC int LMODULE_(mf, lua_State *L);
A_PUBLIC int LMODULE_(tf, lua_State *L);
A_PUBLIC int LMODULE_(pid, lua_State *L);
A_PUBLIC int LMODULE_(pid_fuzzy, lua_State *L);
A_PUBLIC int LMODULE_(complex, lua_State *L);
A_PUBLIC int LMODULE_(polytrack3, lua_State *L);
A_PUBLIC int LMODULE_(polytrack5, lua_State *L);
A_PUBLIC int LMODULE_(polytrack7, lua_State *L);
A_PUBLIC int LMODULE_(version, lua_State *L);
A_PUBLIC int LMODULE(setter)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* a.h */
