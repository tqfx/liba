/***
 bell-shaped velocity trajectory
 @module liba.trajbell
*/

#include "trajbell.h"
#include "a/trajbell.h"

/***
 constructor for bell-shaped velocity trajectory
 @treturn a.trajbell bell-shaped velocity trajectory userdata
 @function new
*/
int liba_trajbell_new(lua_State *L)
{
    a_trajbell *const ctx = lua_newclass(L, a_trajbell);
    a_zero(ctx, sizeof(a_trajbell));
    lua_registry_get(L, liba_trajbell_new);
    lua_setmetatable(L, -2);
    return 1;
}

/***
 generate for bell-shaped velocity trajectory
 @tparam a.trajbell ctx bell-shaped velocity trajectory userdata
 @tparam number jm defines the maximum jerk during system operation
 @tparam number am defines the maximum acceleration during system operation
 @tparam number vm defines the maximum velocity during system operation
 @tparam number p0 defines the initial position
 @tparam number p1 defines the final position
 @tparam[opt] number v0 defines the initial velocity
 @tparam[opt] number v1 defines the final velocity
 @treturn number total duration
 @function gen
*/
int liba_trajbell_gen(lua_State *L)
{
    a_real v0 = 0, v1 = 0;
    a_real jm, am, vm, p0, p1;
    int const top = lua_gettop(L);
    a_trajbell *const ctx = (a_trajbell *)lua_touserdata(L, 1);
    if (ctx)
    {
        jm = (a_real)luaL_checknumber(L, 2);
        am = (a_real)luaL_checknumber(L, 3);
        vm = (a_real)luaL_checknumber(L, 4);
        p0 = (a_real)luaL_checknumber(L, 5);
        p1 = (a_real)luaL_checknumber(L, 6);
        if (top >= 7) { v0 = (a_real)luaL_checknumber(L, 7); }
        if (top >= 8) { v1 = (a_real)luaL_checknumber(L, 8); }
        a_trajbell_gen(ctx, jm, am, vm, p0, p1, v0, v1);
        lua_pushnumber(L, (lua_Number)ctx->t);
        return 1;
    }
    return 0;
}

/***
 compute position for bell-shaped velocity trajectory
 @tparam a.trajbell ctx bell-shaped velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_trajbell_pos(lua_State *L)
{
    a_trajbell const *const ctx = (a_trajbell const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajbell_pos(ctx, x));
        return 1;
    }
    return 0;
}

/***
 compute velocity for bell-shaped velocity trajectory
 @tparam a.trajbell ctx bell-shaped velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_trajbell_vel(lua_State *L)
{
    a_trajbell const *const ctx = (a_trajbell const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajbell_vel(ctx, x));
        return 1;
    }
    return 0;
}

/***
 compute acceleration for bell-shaped velocity trajectory
 @tparam a.trajbell ctx bell-shaped velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_trajbell_acc(lua_State *L)
{
    a_trajbell const *const ctx = (a_trajbell const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajbell_acc(ctx, x));
        return 1;
    }
    return 0;
}

/***
 compute jerk for bell-shaped velocity trajectory
 @tparam a.trajbell ctx bell-shaped velocity trajectory userdata
 @tparam number x difference between current time and initial time
 @treturn number jerk output
 @function jer
*/
int liba_trajbell_jer(lua_State *L)
{
    a_trajbell const *const ctx = (a_trajbell const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const x = (a_real)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_trajbell_jer(ctx, x));
        return 1;
    }
    return 0;
}

static int liba_trajbell_set(lua_State *L)
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

static int liba_trajbell_get(lua_State *L)
{
    a_trajbell const *const ctx = (a_trajbell const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00000074: /* t */
        lua_pushnumber(L, (lua_Number)ctx->t);
        break;
    case 0x00003BD2: /* tv */
        lua_pushnumber(L, (lua_Number)ctx->tv);
        break;
    case 0x00003BBD: /* ta */
        lua_pushnumber(L, (lua_Number)ctx->ta);
        break;
    case 0x00003BC0: /* td */
        lua_pushnumber(L, (lua_Number)ctx->td);
        break;
    case 0x001E9221: /* taj */
        lua_pushnumber(L, (lua_Number)ctx->taj);
        break;
    case 0x001E93AA: /* tdj */
        lua_pushnumber(L, (lua_Number)ctx->tdj);
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
    case 0x00003CCF: /* vm */
        lua_pushnumber(L, (lua_Number)ctx->vm);
        break;
    case 0x000036AB: /* jm */
        lua_pushnumber(L, (lua_Number)ctx->jm);
        break;
    case 0x00003210: /* am */
        lua_pushnumber(L, (lua_Number)ctx->am);
        break;
    case 0x00003399: /* dm */
        lua_pushnumber(L, (lua_Number)ctx->dm);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_trajbell_new);
        lua_num_set(L, -1, "t", ctx->t);
        lua_num_set(L, -1, "tv", ctx->tv);
        lua_num_set(L, -1, "ta", ctx->ta);
        lua_num_set(L, -1, "td", ctx->td);
        lua_num_set(L, -1, "taj", ctx->taj);
        lua_num_set(L, -1, "tdj", ctx->tdj);
        lua_num_set(L, -1, "p0", ctx->p0);
        lua_num_set(L, -1, "p1", ctx->p1);
        lua_num_set(L, -1, "v0", ctx->v0);
        lua_num_set(L, -1, "v1", ctx->v1);
        lua_num_set(L, -1, "vm", ctx->vm);
        lua_num_set(L, -1, "jm", ctx->jm);
        lua_num_set(L, -1, "am", ctx->am);
        lua_num_set(L, -1, "dm", ctx->dm);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_trajbell_(lua_State *L)
{
    lua_pushcfunction(L, liba_trajbell_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_trajbell(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_trajbell_new},
        {"gen", liba_trajbell_gen},
        {"pos", liba_trajbell_pos},
        {"vel", liba_trajbell_vel},
        {"acc", liba_trajbell_acc},
        {"jer", liba_trajbell_jer},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_trajbell_set},
        {"__index", liba_trajbell_get},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_trajbell_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.trajbell");
    lua_registry_set(L, liba_trajbell_new);

    return 1;
}
