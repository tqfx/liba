/***
 trapezoidal velocity trajectory
 @module liba.trajtrap
*/

#include "trajtrap.h"
#include "a/trajtrap.h"

/***
 constructor for trapezoidal velocity trajectory
 @treturn a.trajtrap trapezoidal velocity trajectory userdata
 @function new
*/
int liba_trajtrap_new(lua_State *L)
{
    a_trajtrap *const ctx = lua_newclass(L, a_trajtrap);
    a_zero(ctx, sizeof(a_trajtrap));
    lua_registry_get(L, liba_trajtrap_new);
    lua_setmetatable(L, -2);
    return 1;
}

/***
 generate for trapezoidal velocity trajectory
 @tparam a.trajtrap ctx trapezoidal velocity trajectory userdata
 @tparam number vm defines the maximum velocity during system operation
 @tparam number ac defines the acceleration before constant velocity
 @tparam number de defines the acceleration after constant velocity
 @tparam number p0 defines the initial position
 @tparam number p1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total duration
 @function gen
*/
int liba_trajtrap_gen(lua_State *L)
{
    a_float v0 = 0, v1 = 0;
    a_float vm, ac, de, p0, p1;
    int const top = lua_gettop(L);
    a_trajtrap *const ctx = (a_trajtrap *)lua_touserdata(L, 1);
    if (ctx)
    {
        vm = (a_float)luaL_checknumber(L, 2);
        ac = (a_float)luaL_checknumber(L, 3);
        de = (a_float)luaL_checknumber(L, 4);
        p0 = (a_float)luaL_checknumber(L, 5);
        p1 = (a_float)luaL_checknumber(L, 6);
        if (top >= 7) { v0 = (a_float)luaL_checknumber(L, 7); }
        if (top >= 8) { v1 = (a_float)luaL_checknumber(L, 8); }
        a_trajtrap_gen(ctx, vm, ac, de, p0, p1, v0, v1);
        lua_pushnumber(L, (lua_Number)ctx->t);
        return 1;
    }
    return 0;
}

/***
 calculate position for trapezoidal velocity trajectory
 @tparam a.trajtrap ctx trapezoidal velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajtrap_pos(lua_State *L)
{
    a_trajtrap const *const ctx = (a_trajtrap const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajtrap_pos(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate velocity for trapezoidal velocity trajectory
 @tparam a.trajtrap ctx trapezoidal velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajtrap_vel(lua_State *L)
{
    a_trajtrap const *const ctx = (a_trajtrap const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajtrap_vel(ctx, x));
        return 1;
    }
    return 0;
}

/***
 calculate acceleration for trapezoidal velocity trajectory
 @tparam a.trajtrap ctx trapezoidal velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajtrap_acc(lua_State *L)
{
    a_trajtrap const *const ctx = (a_trajtrap const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const x = (a_float)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajtrap_acc(ctx, x));
        return 1;
    }
    return 0;
}

static int liba_trajtrap_set(lua_State *L)
{
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0xE8859EEB: /* __name */
    case 0xA65758B2: /* __index */
    case 0xAEB551C6: /* __newindex */
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawset(L, 1);
    }
    return 0;
}

static int liba_trajtrap_get(lua_State *L)
{
    a_trajtrap const *const ctx = (a_trajtrap const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00000074: /* t */
        lua_pushnumber(L, (lua_Number)ctx->t);
        break;
    case 0x00003980: /* p0 */
        lua_pushnumber(L, (lua_Number)ctx->p0);
        break;
    case 0x00003981: /* p1 */
        lua_pushnumber(L, (lua_Number)ctx->p1);
        break;
    case 0x00003C92: /* v0 */
        lua_pushnumber(L, (lua_Number)ctx->v0);
        break;
    case 0x00003C93: /* v1 */
        lua_pushnumber(L, (lua_Number)ctx->v1);
        break;
    case 0x00003CC5: /* vc */
        lua_pushnumber(L, (lua_Number)ctx->vc);
        break;
    case 0x00003BBD: /* ta */
        lua_pushnumber(L, (lua_Number)ctx->ta);
        break;
    case 0x00003BC0: /* td */
        lua_pushnumber(L, (lua_Number)ctx->td);
        break;
    case 0x000039B1: /* pa */
        lua_pushnumber(L, (lua_Number)ctx->pa);
        break;
    case 0x000039B4: /* pd */
        lua_pushnumber(L, (lua_Number)ctx->pd);
        break;
    case 0x00003206: /* ac */
        lua_pushnumber(L, (lua_Number)ctx->ac);
        break;
    case 0x00003391: /* de */
        lua_pushnumber(L, (lua_Number)ctx->de);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_trajtrap_new);
        lua_num_set(L, -1, "t", ctx->t);
        lua_num_set(L, -1, "p0", ctx->p0);
        lua_num_set(L, -1, "p1", ctx->p1);
        lua_num_set(L, -1, "v0", ctx->v0);
        lua_num_set(L, -1, "v1", ctx->v1);
        lua_num_set(L, -1, "vc", ctx->vc);
        lua_num_set(L, -1, "ta", ctx->ta);
        lua_num_set(L, -1, "td", ctx->td);
        lua_num_set(L, -1, "pa", ctx->pa);
        lua_num_set(L, -1, "pd", ctx->pd);
        lua_num_set(L, -1, "ac", ctx->ac);
        lua_num_set(L, -1, "de", ctx->de);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_trajtrap_(lua_State *L)
{
    lua_pushcfunction(L, liba_trajtrap_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_trajtrap(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_trajtrap_new},
        {"gen", liba_trajtrap_gen},
        {"pos", liba_trajtrap_pos},
        {"vel", liba_trajtrap_vel},
        {"acc", liba_trajtrap_acc},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_trajtrap_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_trajtrap_set},
        {"__index", liba_trajtrap_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.trajtrap");
    lua_registry_set(L, liba_trajtrap_new);

    return 1;
}
