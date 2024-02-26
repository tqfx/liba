/***
 single neuron proportional integral derivative controller
 @module liba.pid_neuro
*/

#include "pid_neuro.h"
#include "a/pid_neuro.h"

/***
 constructor for single neuron PID controller
 @treturn a.pid_neuro single neuron PID controller userdata
 @function new
*/
int liba_pid_neuro_new(lua_State *L)
{
    a_pid_neuro *const ctx = lua_newclass(L, a_pid_neuro);
    lua_registry_get(L, liba_pid_neuro_new);
    lua_setmetatable(L, -2);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->pid.kp = ctx->k = 1;
    ctx->pid.ki = 0;
    ctx->pid.kd = 0;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(ctx);
    return 1;
}

/***
 initialize for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @treturn a.pid_neuro single neuron PID controller userdata
 @function init
*/
int liba_pid_neuro_init(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    ctx->pid.kp = 1;
    ctx->pid.ki = 0;
    ctx->pid.kd = 0;
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->k = 1;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuro_init(ctx);
    return 1;
}

/***
 set proportional integral derivative constant for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn a.pid_neuro single neuron PID controller userdata
 @function kpid
*/
int liba_pid_neuro_kpid(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const k = (a_float)luaL_checknumber(L, 2);
        a_float const kp = (a_float)luaL_checknumber(L, 3);
        a_float const ki = (a_float)luaL_checknumber(L, 4);
        a_float const kd = (a_float)luaL_checknumber(L, 5);
        a_pid_neuro_kpid(ctx, k, kp, ki, kd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative weight for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn a.pid_neuro single neuron PID controller userdata
 @function wpid
*/
int liba_pid_neuro_wpid(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const wp = (a_float)luaL_checknumber(L, 2);
        a_float const wi = (a_float)luaL_checknumber(L, 3);
        a_float const wd = (a_float)luaL_checknumber(L, 4);
        a_pid_neuro_wpid(ctx, wp, wi, wd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_neuro_run(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const set = (a_float)luaL_checknumber(L, 2);
        a_float const fdb = (a_float)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_neuro_run(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function inc
*/
int liba_pid_neuro_inc(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float const set = (a_float)luaL_checknumber(L, 2);
        a_float const fdb = (a_float)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_neuro_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 zeroing for single neuron PID controller
 @tparam a.pid_neuro ctx single neuron PID controller userdata
 @treturn a.pid_neuro single neuron PID controller userdata
 @function zero
*/
int liba_pid_neuro_zero(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_neuro_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_pid_neuro_set(lua_State *L)
{
    a_pid_neuro *const ctx = (a_pid_neuro *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0000006B: // k
        ctx->k = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x00003731: // kp
        ctx->pid.kp = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->pid.ki = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->pid.kd = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x00003D55: // wp
        ctx->wp = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x00003D4E: // wi
        ctx->wi = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x00003D49: // wd
        ctx->wd = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->pid.outmax = (a_float)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->pid.outmin = (a_float)luaL_checknumber(L, 3);
        break;
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawset(L, 1);
    }
    return 0;
}

static int liba_pid_neuro_get(lua_State *L)
{
    a_pid_neuro const *const ctx = (a_pid_neuro const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0000006B: // k
        lua_pushnumber(L, (lua_Number)ctx->k);
        break;
    case 0x00003731: // kp
        lua_pushnumber(L, (lua_Number)ctx->pid.kp);
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, (lua_Number)ctx->pid.ki);
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, (lua_Number)ctx->pid.kd);
        break;
    case 0x00003D55: // wp
        lua_pushnumber(L, (lua_Number)ctx->wp);
        break;
    case 0x00003D4E: // wi
        lua_pushnumber(L, (lua_Number)ctx->wi);
        break;
    case 0x00003D49: // wd
        lua_pushnumber(L, (lua_Number)ctx->wd);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->pid.outmax);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->pid.outmin);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->pid.out);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->pid.fdb);
        break;
    case 0x001AAD55: // err
        lua_pushnumber(L, (lua_Number)ctx->pid.err);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, (lua_Number)ctx->ec);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_pid_neuro_new);
        lua_num_set(L, -1, "kp", ctx->pid.kp);
        lua_num_set(L, -1, "ki", ctx->pid.ki);
        lua_num_set(L, -1, "kd", ctx->pid.kd);
        lua_num_set(L, -1, "summax", ctx->pid.summax);
        lua_num_set(L, -1, "summin", ctx->pid.summin);
        lua_num_set(L, -1, "outmax", ctx->pid.outmax);
        lua_num_set(L, -1, "outmin", ctx->pid.outmin);
        lua_num_set(L, -1, "out", ctx->pid.out);
        lua_num_set(L, -1, "fdb", ctx->pid.fdb);
        lua_num_set(L, -1, "err", ctx->pid.err);
        lua_num_set(L, -1, "ec", ctx->ec);
        lua_num_set(L, -1, "wp", ctx->wp);
        lua_num_set(L, -1, "wi", ctx->wi);
        lua_num_set(L, -1, "wd", ctx->wd);
        lua_num_set(L, -1, "k", ctx->k);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_pid_neuro_(lua_State *L)
{
    lua_pushcfunction(L, liba_pid_neuro_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_pid_neuro(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"new", liba_pid_neuro_new},
        {"init", liba_pid_neuro_init},
        {"kpid", liba_pid_neuro_kpid},
        {"wpid", liba_pid_neuro_wpid},
        {"run", liba_pid_neuro_run},
        {"inc", liba_pid_neuro_inc},
        {"zero", liba_pid_neuro_zero},
    };
    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_pid_neuro_);
    lua_setmetatable(L, -2);

    static lua_fun const metas[] = {
        {"__newindex", liba_pid_neuro_set},
        {"__index", liba_pid_neuro_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.pid_neuro");
    lua_registry_set(L, liba_pid_neuro_new);

    return 1;
}
