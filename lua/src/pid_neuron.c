/***
 single neuron proportional integral derivative controller
 @module liba.pid_neuron
*/

#include "pid_neuron.h"
#include "a/pid_neuron.h"

/***
 constructor for single neuron PID controller
 @treturn a.pid_neuron single neuron PID controller userdata
 @function new
*/
int liba_pid_neuron_new(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_newuserdata(L, sizeof(a_pid_neuron_s));
    a_zero(ctx, sizeof(a_pid_neuron_s));
    liba_pid_neuron_meta_(L, 1);
    lua_setmetatable(L, -2);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->k = 1;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuron_init(ctx);
    return 1;
}

/***
 initialize for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @treturn a.pid_neuron single neuron PID controller userdata
 @function init
*/
int liba_pid_neuron_init(lua_State *const L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->k = 1;
    ctx->wp = A_FLOAT_C(0.1);
    ctx->wi = A_FLOAT_C(0.1);
    ctx->wd = A_FLOAT_C(0.1);
    a_pid_neuron_init(ctx);
    return 1;
}

/***
 zeroing for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @treturn a.pid_neuron single neuron PID controller userdata
 @function zero
*/
int liba_pid_neuron_zero(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_neuron_zero(ctx);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative constant for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn a.pid_neuron single neuron PID controller userdata
 @function kpid
*/
int liba_pid_neuron_kpid(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const k = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const kp = (a_float_t)luaL_checknumber(L, 3);
        a_float_t const ki = (a_float_t)luaL_checknumber(L, 4);
        a_float_t const kd = (a_float_t)luaL_checknumber(L, 5);
        a_pid_neuron_kpid(ctx, k, kp, ki, kd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative weight for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn a.pid_neuron single neuron PID controller userdata
 @function wpid
*/
int liba_pid_neuron_wpid(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const wp = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const wi = (a_float_t)luaL_checknumber(L, 3);
        a_float_t const wd = (a_float_t)luaL_checknumber(L, 4);
        a_pid_neuron_wpid(ctx, wp, wi, wd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function off
*/
int liba_pid_neuron_off(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_neuron_off(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for single neuron PID controller
 @tparam a.pid_neuron ctx single neuron PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function inc
*/
int liba_pid_neuron_inc(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_neuron_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

#undef funcs
#define funcs liba_pid_neuron_funcs
static lua_fun_s const funcs[] = {
    {"new", liba_pid_neuron_new},
    {"init", liba_pid_neuron_init},
    {"zero", liba_pid_neuron_zero},
    {"kpid", liba_pid_neuron_kpid},
    {"wpid", liba_pid_neuron_wpid},
    {"off", liba_pid_neuron_off},
    {"inc", liba_pid_neuron_inc},
    {NULL, NULL},
};

static int liba_pid_neuron_set(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0000006B: // k
        ctx->k = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003731: // kp
        ctx->pid.kp = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->pid.ki = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->pid.kd = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003D55: // wp
        ctx->wp = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003D4E: // wi
        ctx->wi = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003D49: // wd
        ctx->wd = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->pid.outmax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->pid.outmin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int liba_pid_neuron_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_neuron_s const *const ctx = (a_pid_neuron_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
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
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_pid_neuron_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, liba_pid_neuron_init);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, liba_pid_neuron_zero);
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, liba_pid_neuron_kpid);
        break;
    case 0x100F9D1C: // wpid
        lua_pushcfunction(L, liba_pid_neuron_wpid);
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, liba_pid_neuron_off);
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, liba_pid_neuron_inc);
        break;
    case 0xA65758B2: // __index
    {
        lua_num_s const reals[] = {
            {"kp", ctx->pid.kp},
            {"ki", ctx->pid.ki},
            {"kd", ctx->pid.kd},
            {"summax", ctx->pid.summax},
            {"outmax", ctx->pid.outmax},
            {"outmin", ctx->pid.outmin},
            {"out", ctx->pid.out},
            {"fdb", ctx->pid.fdb},
            {"err", ctx->pid.err},
            {"ec", ctx->ec},
            {"wp", ctx->wp},
            {"wi", ctx->wi},
            {"wd", ctx->wd},
            {"k", ctx->k},
            {NULL, 0},
        };
        lua_createtable(L, 0, A_LEN(reals) + A_LEN(funcs) - 2);
        lua_num_reg(L, -1, reals);
        lua_fun_reg(L, -1, funcs);
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_pid_neuron(lua_State *const L)
{
    lua_createtable(L, 0, A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__newindex", liba_setter);
    lua_setmetatable(L, -2);

    lua_fun_s const metas[] = {
        {"__newindex", liba_pid_neuron_set},
        {"__index", liba_pid_neuron_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    lua_str_set(L, -1, "__name", "a.pid_neuron");
    lua_fun_reg(L, -1, metas);

    liba_pid_neuron_meta_(L, 0);
    liba_pid_neuron_func_(L, 0);

    return liba_pid_neuron_func_(L, 1);
}

int liba_pid_neuron_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_neuron_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_neuron_func_));
    return 0;
}

int liba_pid_neuron_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_neuron_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_neuron_meta_));
    return 0;
}
