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
int liba_pid_new(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_newuserdata(L, sizeof(a_pid_s));
    a_zero(ctx, sizeof(a_pid_s));
    lua_registry_get(L, liba_pid_new);
    lua_setmetatable(L, -2);
    ctx->kp = 1;
    ctx->summax = +A_FLOAT_INF;
    ctx->summin = -A_FLOAT_INF;
    ctx->outmax = +A_FLOAT_INF;
    ctx->outmin = -A_FLOAT_INF;
    a_pid_init(ctx);
    return 1;
}

/***
 calculate for PID controller
 @tparam a.pid ctx PID controller userdata
 @treturn a.pid PID controller userdata
 @function init
*/
int liba_pid_init(lua_State *const L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    ctx->kp = 1;
    ctx->summax = +A_FLOAT_INF;
    ctx->summin = -A_FLOAT_INF;
    ctx->outmax = +A_FLOAT_INF;
    ctx->outmin = -A_FLOAT_INF;
    a_pid_init(ctx);
    return 1;
}

/***
 zeroing for PID controller
 @tparam a.pid ctx PID controller userdata
 @treturn a.pid PID controller userdata
 @function zero
*/
int liba_pid_zero(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_zero(ctx);
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
 @function kpid
*/
int liba_pid_kpid(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const kp = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const ki = (a_float_t)luaL_checknumber(L, 3);
        a_float_t const kd = (a_float_t)luaL_checknumber(L, 4);
        a_pid_kpid(ctx, kp, ki, kd);
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
int liba_pid_run(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
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
int liba_pid_pos(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
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
int liba_pid_inc(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

static int liba_pid_set(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00003731: // kp
        ctx->kp = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->ki = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->kd = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: // summax
        ctx->summax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x10EA03AB: // summin
        ctx->summin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->outmax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->outmin = (a_float_t)luaL_checknumber(L, 3);
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

static int liba_pid_get(lua_State *const L)
{
    a_pid_s const *const ctx = (a_pid_s const *)lua_touserdata(L, 1);
    switch ((a_u32_t)a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00003731: // kp
        lua_pushnumber(L, (lua_Number)ctx->kp);
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, (lua_Number)ctx->ki);
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, (lua_Number)ctx->kd);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, (lua_Number)ctx->summax);
        break;
    case 0x10EA03AB: // summin
        lua_pushnumber(L, (lua_Number)ctx->summin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->outmax);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->outmin);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->out);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->fdb);
        break;
    case 0x001AAD55: // err
        lua_pushnumber(L, (lua_Number)ctx->err);
        break;
    case 0xA65758B2: // __index
        lua_registry_get(L, liba_pid_new);
        lua_num_set(L, -1, "kp", ctx->kp);
        lua_num_set(L, -1, "ki", ctx->ki);
        lua_num_set(L, -1, "kd", ctx->kd);
        lua_num_set(L, -1, "summax", ctx->summax);
        lua_num_set(L, -1, "summin", ctx->summin);
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

static int liba_pid_(lua_State *const L)
{
    lua_pushcfunction(L, liba_pid_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_pid(lua_State *const L)
{
    /***
     enumeration for PID controller
     @field RUN run and output setpoint
     @field POS positional PID controller
     @field INC incremental PID controller
     @table mode
    */
    static lua_int_s const enums[] = {
        {"RUN", A_PID_RUN},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
    };
    static lua_fun_s const funcs[] = {
        {"new", liba_pid_new},
        {"init", liba_pid_init},
        {"zero", liba_pid_zero},
        {"kpid", liba_pid_kpid},
        {"run", liba_pid_run},
        {"pos", liba_pid_pos},
        {"inc", liba_pid_inc},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs));
    lua_int_reg(L, -1, enums, A_LEN(enums));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));

    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_pid_);
    lua_setmetatable(L, -2);

    static lua_fun_s const metas[] = {
        {"__newindex", liba_pid_set},
        {"__index", liba_pid_get},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.pid");

    lua_registry_set(L, liba_pid_new);
    return 1;
}
