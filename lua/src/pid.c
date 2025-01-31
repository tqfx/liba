/***
 proportional integral derivative controller
 @module liba.pid
*/

#include "pid.h"
#include "a/pid.h"

/***
 constructor for PID controller
 @treturn a.pid PID controller userdata
 @function new
*/
int liba_pid_new(lua_State *L)
{
    a_pid *const ctx = lua_newclass(L, a_pid);
    lua_registry_get(L, liba_pid_new);
    lua_setmetatable(L, -2);
    ctx->kp = 1;
    ctx->ki = 0;
    ctx->kd = 0;
    ctx->summax = +A_REAL_INF;
    ctx->summin = -A_REAL_INF;
    ctx->outmax = +A_REAL_INF;
    ctx->outmin = -A_REAL_INF;
    a_pid_init(ctx);
    return 1;
}

/***
 calculate for PID controller
 @tparam a.pid ctx PID controller userdata
 @treturn a.pid PID controller userdata
 @function init
*/
int liba_pid_init(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        ctx->kp = 1;
        ctx->ki = 0;
        ctx->kd = 0;
        ctx->summax = +A_REAL_INF;
        ctx->summin = -A_REAL_INF;
        ctx->outmax = +A_REAL_INF;
        ctx->outmin = -A_REAL_INF;
        a_pid_init(ctx);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative constant for PID controller
 @tparam a.pid ctx PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid PID controller userdata
 @function set_kpid
*/
int liba_pid_set_kpid(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const kp = (a_real)luaL_checknumber(L, 2);
        a_real const ki = (a_real)luaL_checknumber(L, 3);
        a_real const kd = (a_real)luaL_checknumber(L, 4);
        a_pid_set_kpid(ctx, kp, ki, kd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for PID controller
 @tparam a.pid ctx PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_run(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_run(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for positional PID controller
 @tparam a.pid ctx PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
int liba_pid_pos(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_pos(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for incremental PID controller
 @tparam a.pid ctx PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
int liba_pid_inc(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 zeroing for PID controller
 @tparam a.pid ctx PID controller userdata
 @treturn a.pid PID controller userdata
 @function zero
*/
int liba_pid_zero(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_pid_set(lua_State *L)
{
    a_pid *const ctx = (a_pid *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00003731: /* kp */
        ctx->kp = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: /* ki */
        ctx->ki = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x00003725: /* kd */
        ctx->kd = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: /* summax */
        ctx->summax = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x10EA03AB: /* summin */
        ctx->summin = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: /* outmax */
        ctx->outmax = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: /* outmin */
        ctx->outmin = (a_real)luaL_checknumber(L, 3);
        break;
    case 0xE8859EEB: /* __name */
    case 0xE70C48C6: /* __call */
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

static int liba_pid_get(lua_State *L)
{
    a_pid const *const ctx = (a_pid const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00003731: /* kp */
        lua_pushnumber(L, (lua_Number)ctx->kp);
        break;
    case 0x0000372A: /* ki */
        lua_pushnumber(L, (lua_Number)ctx->ki);
        break;
    case 0x00003725: /* kd */
        lua_pushnumber(L, (lua_Number)ctx->kd);
        break;
    case 0x10E9FF9D: /* summax */
        lua_pushnumber(L, (lua_Number)ctx->summax);
        break;
    case 0x10EA03AB: /* summin */
        lua_pushnumber(L, (lua_Number)ctx->summin);
        break;
    case 0x001E5957: /* sum */
        lua_pushnumber(L, (lua_Number)ctx->sum);
        break;
    case 0x23C8F10E: /* outmax */
        lua_pushnumber(L, (lua_Number)ctx->outmax);
        break;
    case 0x23C8F51C: /* outmin */
        lua_pushnumber(L, (lua_Number)ctx->outmin);
        break;
    case 0x001D4D3A: /* out */
        lua_pushnumber(L, (lua_Number)ctx->out);
        break;
    case 0x001AE924: /* fdb */
        lua_pushnumber(L, (lua_Number)ctx->fdb);
        break;
    case 0x001AAD55: /* err */
        lua_pushnumber(L, (lua_Number)ctx->err);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_pid_new);
        lua_num_set(L, -1, "kp", ctx->kp);
        lua_num_set(L, -1, "ki", ctx->ki);
        lua_num_set(L, -1, "kd", ctx->kd);
        lua_num_set(L, -1, "summax", ctx->summax);
        lua_num_set(L, -1, "summin", ctx->summin);
        lua_num_set(L, -1, "sum", ctx->sum);
        lua_num_set(L, -1, "outmax", ctx->outmax);
        lua_num_set(L, -1, "outmin", ctx->outmin);
        lua_num_set(L, -1, "out", ctx->out);
        lua_num_set(L, -1, "fdb", ctx->fdb);
        lua_num_set(L, -1, "err", ctx->err);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_pid_(lua_State *L)
{
    lua_pushcfunction(L, liba_pid_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_pid(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_pid_new},
        {"init", liba_pid_init},
        {"set_kpid", liba_pid_set_kpid},
        {"run", liba_pid_run},
        {"pos", liba_pid_pos},
        {"inc", liba_pid_inc},
        {"zero", liba_pid_zero},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_pid_set},
        {"__index", liba_pid_get},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_pid_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.pid");
    lua_registry_set(L, liba_pid_new);

    return 1;
}
