/***
 single neuron proportional integral derivative controller
 @module liba.pid_neuron
*/

#include "neuron.h"

static int LMODULE(pid_neuron_init_)(lua_State *const L, a_pid_neuron_s *const ctx)
{
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 5: /* kp, ki, kd, outmin, outmax */
    {
        ctx->pid.outmax = (a_float_t)luaL_checknumber(L, 5);
        ctx->pid.outmin = (a_float_t)luaL_checknumber(L, 4);
        ctx->pid.kd = (a_float_t)luaL_checknumber(L, 3);
        ctx->pid.ki = (a_float_t)luaL_checknumber(L, 2);
        ctx->pid.kp = (a_float_t)luaL_checknumber(L, 1);
        if (ctx->pid.mode != A_PID_POS)
        {
            ctx->pid.mode = A_PID_INC;
        }
        break;
    }
    case 2: /* outmin, outmax */
    {
        ctx->pid.outmax = (a_float_t)luaL_checknumber(L, 2);
        ctx->pid.outmin = (a_float_t)luaL_checknumber(L, 1);
        ctx->pid.mode = A_PID_INC;
        break;
    }
    default:
        ctx->pid.outmax = +A_FLOAT_INF;
        ctx->pid.outmin = -A_FLOAT_INF;
        ctx->pid.mode = A_PID_INC;
        break;
    }
    a_pid_neuron_init(ctx, 0);
    return 1;
}

/***
 constructor for single neuron PID controller
 @tparam[opt] number kp proportional learning constant
 @tparam[opt] number ki integral learning constant
 @tparam[opt] number kd derivative learning constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid_neuron single neuron PID controller userdata
 @function new
*/
int LMODULE(pid_neuron_new)(lua_State *const L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_newuserdata(L, sizeof(a_pid_neuron_s));
    a_zero(ctx, sizeof(a_pid_neuron_s));
    ctx->pid.summax = +A_FLOAT_INF;
    LMODULE2(pid_neuron_meta_, L, 1);
    lua_setmetatable(L, -2);
    return LMODULE2(pid_neuron_init_, L, ctx);
}

/***
 initialize function for single neuron PID controller
 @param ctx single neuron PID controller userdata
 @tparam[opt] number kp proportional learning constant
 @tparam[opt] number ki integral learning constant
 @tparam[opt] number kd derivative learning constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid_neuron single neuron PID controller userdata
 @function init
*/
int LMODULE(pid_neuron_init)(lua_State *const L)
{
    if (lua_gettop(L))
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return LMODULE2(pid_neuron_init_, L, ctx);
    }
    return 0;
}

/***
 set proportional integral derivative constant for single neuron PID controller
 @param ctx single neuron PID controller userdata
 @tparam number k proportional output coefficient
 @tparam number kp proportional learning constant
 @tparam number ki integral learning constant
 @tparam number kd derivative learning constant
 @treturn pid_neuron single neuron PID controller userdata
 @function kpid
*/
int LMODULE(pid_neuron_kpid)(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, -5);
    if (ctx)
    {
        a_float_t const k = (a_float_t)luaL_checknumber(L, -4);
        a_float_t const kp = (a_float_t)luaL_checknumber(L, -3);
        a_float_t const ki = (a_float_t)luaL_checknumber(L, -2);
        a_float_t const kd = (a_float_t)luaL_checknumber(L, -1);
        a_pid_neuron_kpid(ctx, k, kp, ki, kd);
        lua_pop(L, 4);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative weight for single neuron PID controller
 @param ctx single neuron PID controller userdata
 @tparam number wp proportional weight
 @tparam number wi integral weight
 @tparam number wd derivative weight
 @treturn pid_neuron single neuron PID controller userdata
 @function wpid
*/
int LMODULE(pid_neuron_wpid)(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_float_t const wp = (a_float_t)luaL_checknumber(L, -3);
        a_float_t const wi = (a_float_t)luaL_checknumber(L, -2);
        a_float_t const wd = (a_float_t)luaL_checknumber(L, -1);
        a_pid_neuron_wpid(ctx, wp, wi, wd);
        lua_pop(L, 3);
        return 1;
    }
    return 0;
}

/***
 calculate function for single neuron PID controller
 @param ctx single neuron PID controller userdata
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
int LMODULE(pid_neuron_iter)(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, -2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_pid_neuron_outf(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero clear function for single neuron PID controller
 @param ctx single neuron PID controller userdata
 @treturn pid_neuron single neuron PID controller userdata
 @function zero
*/
int LMODULE(pid_neuron_zero)(lua_State *const L)
{
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_neuron_zero(ctx);
        return 1;
    }
    return 0;
}

static int LMODULE(pid_neuron_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_neuron_s *const ctx = (a_pid_neuron_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00003731: // kp
        ctx->pid.kp = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->pid.ki = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->pid.kd = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: // summax
        ctx->pid.summax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->pid.outmax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->pid.outmin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        ctx->pid.mode = (unsigned int)luaL_checkinteger(L, 3);
        break;
    case 0x00003D55: // wp
        ctx->wp.f = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003D4E: // wi
        ctx->wi.f = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003D49: // wd
        ctx->wd.f = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0000006B: // k
        ctx->k = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0xE8859EEB: // __name
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

static int LMODULE(pid_neuron_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_neuron_s const *const ctx = (a_pid_neuron_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00003731: // kp
        lua_pushnumber(L, (lua_Number)ctx->pid.kp);
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, (lua_Number)ctx->pid.ki);
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, (lua_Number)ctx->pid.kd);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, (lua_Number)ctx->pid.summax);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->pid.outmax);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->pid.outmin);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->pid.out.f);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->pid.fdb.f);
        break;
    case 0x001AAD55: // err
        lua_pushnumber(L, (lua_Number)ctx->pid.err.f);
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, (lua_Integer)ctx->pid.mode);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, (lua_Number)ctx->ec.f);
        break;
    case 0x00003D55: // wp
        lua_pushnumber(L, (lua_Number)ctx->wp.f);
        break;
    case 0x00003D4E: // wi
        lua_pushnumber(L, (lua_Number)ctx->wi.f);
        break;
    case 0x00003D49: // wd
        lua_pushnumber(L, (lua_Number)ctx->wd.f);
        break;
    case 0x0000006B: // k
        lua_pushnumber(L, (lua_Number)ctx->k);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(pid_neuron_new));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(pid_neuron_init));
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, LMODULE(pid_neuron_kpid));
        break;
    case 0x100F9D1C: // wpid
        lua_pushcfunction(L, LMODULE(pid_neuron_wpid));
        break;
    case 0x0E3068C8: // iter
        lua_pushcfunction(L, LMODULE(pid_neuron_iter));
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, LMODULE(pid_neuron_zero));
        break;
    case 0xA65758B2: // __index
    {
        l_int_s const enums[] = {
            {"mode", (lua_Integer)ctx->pid.mode},
            {NULL, 0},
        };
        l_num_s const datas[] = {
            {"kp", ctx->pid.kp},
            {"ki", ctx->pid.ki},
            {"kd", ctx->pid.kd},
            {"summax", ctx->pid.summax},
            {"outmax", ctx->pid.outmax},
            {"outmin", ctx->pid.outmin},
            {"out", ctx->pid.out.f},
            {"fdb", ctx->pid.fdb.f},
            {"err", ctx->pid.err.f},
            {"ec", ctx->ec.f},
            {"wp", ctx->wp.f},
            {"wi", ctx->wi.f},
            {"wd", ctx->wd.f},
            {"k", ctx->k},
            {NULL, 0},
        };
        l_func_s const funcs[] = {
            {"init", LMODULE(pid_neuron_init)},
            {"kpid", LMODULE(pid_neuron_kpid)},
            {"wpid", LMODULE(pid_neuron_wpid)},
            {"iter", LMODULE(pid_neuron_iter)},
            {"zero", LMODULE(pid_neuron_zero)},
            {"new", LMODULE(pid_neuron_new)},
            {NULL, NULL},
        };
        lua_createtable(L, 0, A_LEN(enums) + A_LEN(datas) + A_LEN(funcs) - 3);
        l_int_reg(L, -1, enums);
        l_num_reg(L, -1, datas);
        l_func_reg(L, -1, funcs);
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

/***
 instance for single neuron PID controller
 @table pid_neuron
*/
int LMODULE_(pid_neuron, lua_State *const L)
{
    l_int_s const enums[] = {
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"init", LMODULE(pid_neuron_init)},
        {"kpid", LMODULE(pid_neuron_kpid)},
        {"wpid", LMODULE(pid_neuron_wpid)},
        {"iter", LMODULE(pid_neuron_iter)},
        {"zero", LMODULE(pid_neuron_zero)},
        {"new", LMODULE(pid_neuron_new)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(pid_neuron_new));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_NEW, LMODULE(pid_neuron_iter)},
        {L_SET, LMODULE(pid_neuron_set)},
        {L_GET, LMODULE(pid_neuron_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    l_str_set(L, -1, L_NAME, LMODULES("pid.neuron"));
    l_func_reg(L, -1, metas);

    LMODULE2(pid_neuron_meta_, L, 0);
    LMODULE2(pid_neuron_func_, L, 0);

    return LMODULE2(pid_neuron_func_, L, 1);
}

int LMODULE(pid_neuron_func_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_neuron_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_neuron_func_));
    return 0;
}

int LMODULE(pid_neuron_meta_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_neuron_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_neuron_meta_));
    return 0;
}
