/***
 membership function
 @module liba.mf
*/

#include "a.h"
#include "a/mf.h"

/***
 gaussian membership function
 @tparam number x input value for which to compute membership value.
 @tparam number sigma is the standard deviation.
 @tparam number c is the mean.
 @treturn number membership value.
 @function gauss
*/
static int liba_mf_gauss_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const sigma = (a_float)luaL_checknumber(L, arg + 2);
    a_float const c = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_gauss(x, sigma, c));
    return 1;
}
static int liba_mf_gauss(lua_State *const L)
{
    return liba_mf_gauss_(L, 0);
}

/***
 product of two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number sigma1 is the standard deviation of the left gaussian function.
 @tparam number c1 is the mean of the left gaussian function.
 @tparam number sigma2 is the standard deviation of the right gaussian function.
 @tparam number c2 is the mean of the right gaussian function.
 @treturn number membership value.
 @function gauss2
*/
static int liba_mf_gauss2_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const sigma1 = (a_float)luaL_checknumber(L, arg + 2);
    a_float const c1 = (a_float)luaL_checknumber(L, arg + 3);
    a_float const sigma2 = (a_float)luaL_checknumber(L, arg + 4);
    a_float const c2 = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_gauss2(x, sigma1, c1, sigma2, c2));
    return 1;
}
static int liba_mf_gauss2(lua_State *const L)
{
    return liba_mf_gauss2_(L, 0);
}

/***
 generalized bell-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines the width of the membership function, where a larger value creates a wider membership function.
 @tparam number b defines the shape of the curve on either side of the central plateau, where a larger value creates a more steep transition.
 @tparam number c defines the center of the membership function.
 @treturn number membership value.
 @function gbell
*/
static int liba_mf_gbell_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    a_float const c = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_gbell(x, a, b, c));
    return 1;
}
static int liba_mf_gbell(lua_State *const L)
{
    return liba_mf_gbell_(L, 0);
}

/***
 sigmoidal membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines the width of the transition area.
 @tparam number c defines the center of the transition area.
 @treturn number membership value.
 @function sig
*/
static int liba_mf_sig_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const c = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_sig(x, a, c));
    return 1;
}
static int liba_mf_sig(lua_State *const L)
{
    return liba_mf_sig_(L, 0);
}

/***
 difference between two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number a1 defines the width of the first transition area.
 @tparam number c1 defines the center of the first transition area.
 @tparam number a2 defines the width of the second transition area.
 @tparam number c2 defines the center of the second transition area.
 @treturn number membership value.
 @function dsig
*/
static int liba_mf_dsig_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a1 = (a_float)luaL_checknumber(L, arg + 2);
    a_float const c1 = (a_float)luaL_checknumber(L, arg + 3);
    a_float const a2 = (a_float)luaL_checknumber(L, arg + 4);
    a_float const c2 = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_dsig(x, a1, c1, a2, c2));
    return 1;
}
static int liba_mf_dsig(lua_State *const L)
{
    return liba_mf_dsig_(L, 0);
}

/***
 product of two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number a1 defines the width of the first transition area.
 @tparam number c1 defines the center of the first transition area.
 @tparam number a2 defines the width of the second transition area.
 @tparam number c2 defines the center of the second transition area.
 @treturn number membership value.
 @function psig
*/
static int liba_mf_psig_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a1 = (a_float)luaL_checknumber(L, arg + 2);
    a_float const c1 = (a_float)luaL_checknumber(L, arg + 3);
    a_float const a2 = (a_float)luaL_checknumber(L, arg + 4);
    a_float const c2 = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_psig(x, a1, c1, a2, c2));
    return 1;
}
static int liba_mf_psig(lua_State *const L)
{
    return liba_mf_psig_(L, 0);
}

/***
 trapezoidal membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its left shoulder.
 @tparam number c defines its right shoulder.
 @tparam number d defines its right foot.
 @treturn number membership value.
 @function trap
*/
static int liba_mf_trap_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    a_float const c = (a_float)luaL_checknumber(L, arg + 4);
    a_float const d = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_trap(x, a, b, c, d));
    return 1;
}
static int liba_mf_trap(lua_State *const L)
{
    return liba_mf_trap_(L, 0);
}

/***
 triangular membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its peak.
 @tparam number c defines its right foot.
 @treturn number membership value.
 @function tri
*/
static int liba_mf_tri_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    a_float const c = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_tri(x, a, b, c));
    return 1;
}
static int liba_mf_tri(lua_State *const L)
{
    return liba_mf_tri_(L, 0);
}

/***
 linear s-shaped saturation membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its foot.
 @tparam number b defines its shoulder.
 @treturn number membership value.
 @function lins
*/
static int liba_mf_lins_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_lins(x, a, b));
    return 1;
}
static int liba_mf_lins(lua_State *const L)
{
    return liba_mf_lins_(L, 0);
}

/***
 linear z-shaped saturation membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its shoulder.
 @tparam number b defines its foot.
 @treturn number membership value.
 @function linz
*/
static int liba_mf_linz_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_linz(x, a, b));
    return 1;
}
static int liba_mf_linz(lua_State *const L)
{
    return liba_mf_linz_(L, 0);
}

/***
 s-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its foot.
 @tparam number b defines its shoulder.
 @treturn number membership value.
 @function s
*/
static int liba_mf_s_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_s(x, a, b));
    return 1;
}
static int liba_mf_s(lua_State *const L)
{
    return liba_mf_s_(L, 0);
}

/***
 z-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its shoulder.
 @tparam number b defines its foot.
 @treturn number membership value.
 @function z
*/
static int liba_mf_z_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    lua_pushnumber(L, (lua_Number)a_mf_z(x, a, b));
    return 1;
}
static int liba_mf_z(lua_State *const L)
{
    return liba_mf_z_(L, 0);
}

/***
 z-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its left shoulder.
 @tparam number c defines its right shoulder.
 @tparam number d defines its right foot.
 @treturn number membership value.
 @function pi
*/
static int liba_mf_pi_(lua_State *const L, int const arg)
{
    a_float const x = (a_float)luaL_checknumber(L, arg + 1);
    a_float const a = (a_float)luaL_checknumber(L, arg + 2);
    a_float const b = (a_float)luaL_checknumber(L, arg + 3);
    a_float const c = (a_float)luaL_checknumber(L, arg + 4);
    a_float const d = (a_float)luaL_checknumber(L, arg + 4);
    lua_pushnumber(L, (lua_Number)a_mf_pi(x, a, b, c, d));
    return 1;
}
static int liba_mf_pi(lua_State *const L)
{
    return liba_mf_pi_(L, 0);
}

/***
 membership function
 @tparam int e type for membership function
 @tparam number x input value for which to compute membership value.
 @tparam number ... is an array that stores parameters.
 @treturn number membership value.
 @function mf
*/
static int liba_mf_mf(lua_State *const L)
{
    lua_Integer const e = luaL_checkinteger(L, 1);
    switch (e)
    {
    case A_MF_PI:
        return liba_mf_pi_(L, 1);
    case A_MF_Z:
        return liba_mf_z_(L, 1);
    case A_MF_S:
        return liba_mf_s_(L, 1);
    case A_MF_LINZ:
        return liba_mf_linz_(L, 1);
    case A_MF_LINS:
        return liba_mf_lins_(L, 1);
    case A_MF_TRI:
        return liba_mf_tri_(L, 1);
    case A_MF_TRAP:
        return liba_mf_trap_(L, 1);
    case A_MF_PSIG:
        return liba_mf_psig_(L, 1);
    case A_MF_DSIG:
        return liba_mf_dsig_(L, 1);
    case A_MF_SIG:
        return liba_mf_sig_(L, 1);
    case A_MF_GBELL:
        return liba_mf_gbell_(L, 1);
    case A_MF_GAUSS2:
        return liba_mf_gauss2_(L, 1);
    case A_MF_GAUSS:
        return liba_mf_gauss_(L, 1);
    case A_MF_NUL:
    default:
        return 0;
    }
}

static int liba_mf_(lua_State *const L)
{
    lua_pushcfunction(L, liba_mf_mf);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_mf(lua_State *const L)
{
    /***
     enumeration for membership function
     @field NUL none
     @field GAUSS gaussian membership function
     @field GAUSS2 gaussian combination membership function
     @field GBELL generalized bell-shaped membership function
     @field SIG sigmoidal membership function
     @field DSIG difference between two sigmoidal membership functions
     @field PSIG product of two sigmoidal membership functions
     @field TRAP trapezoidal membership function
     @field TRI triangular membership function
     @field LINS linear s-shaped saturation membership function
     @field LINZ linear z-shaped saturation membership function
     @field S s-shaped membership function
     @field Z z-shaped membership function
     @field PI pi-shaped membership function
     @table mf
    */
    static lua_int const enums[] = {
        {"NUL", A_MF_NUL},
        {"GAUSS", A_MF_GAUSS},
        {"GAUSS2", A_MF_GAUSS2},
        {"GBELL", A_MF_GBELL},
        {"SIG", A_MF_SIG},
        {"DSIG", A_MF_DSIG},
        {"PSIG", A_MF_PSIG},
        {"TRAP", A_MF_TRAP},
        {"TRI", A_MF_TRI},
        {"LINS", A_MF_LINS},
        {"LINZ", A_MF_LINZ},
        {"S", A_MF_S},
        {"Z", A_MF_Z},
        {"PI", A_MF_PI},
    };
    static lua_fun const funcs[] = {
        {"gauss", liba_mf_gauss},
        {"gauss2", liba_mf_gauss2},
        {"gbell", liba_mf_gbell},
        {"sig", liba_mf_sig},
        {"dsig", liba_mf_dsig},
        {"psig", liba_mf_psig},
        {"trap", liba_mf_trap},
        {"tri", liba_mf_tri},
        {"lins", liba_mf_lins},
        {"linz", liba_mf_linz},
        {"s", liba_mf_s},
        {"z", liba_mf_z},
        {"pi", liba_mf_pi},
        {"mf", liba_mf_mf},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs));
    lua_int_reg(L, -1, enums, A_LEN(enums));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_mf_);
    lua_setmetatable(L, -2);
    return 1;
}
