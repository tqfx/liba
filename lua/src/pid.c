/***
 proportional integral derivative controller
 @module liba.pid
*/

#include "pid.h"

static int LMODULE(pid_init_)(lua_State *const L, a_pid_s *const ctx)
{
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 6: /* kp, ki, kd, outmin, outmax, summax */
    {
        ctx->summax = (a_float_t)luaL_checknumber(L, 6);
        ctx->mode = A_PID_POS;
        A_FALLTHROUGH;
    }
    case 5: /* kp, ki, kd, outmin, outmax */
    {
        ctx->outmax = (a_float_t)luaL_checknumber(L, 5);
        ctx->outmin = (a_float_t)luaL_checknumber(L, 4);
        ctx->kd = (a_float_t)luaL_checknumber(L, 3);
        ctx->ki = (a_float_t)luaL_checknumber(L, 2);
        ctx->kp = (a_float_t)luaL_checknumber(L, 1);
        if (ctx->mode != A_PID_POS)
        {
            ctx->mode = A_PID_INC;
        }
        break;
    }
    case 3: /* outmin, outmax, summax */
    {
        ctx->summax = (a_float_t)luaL_checknumber(L, 3);
        ctx->mode = A_PID_POS;
        A_FALLTHROUGH;
    }
    case 2: /* outmin, outmax */
    {
        ctx->outmax = (a_float_t)luaL_checknumber(L, 2);
        ctx->outmin = (a_float_t)luaL_checknumber(L, 1);
        if (ctx->mode != A_PID_POS)
        {
            ctx->mode = A_PID_INC;
        }
        break;
    }
    default:
        ctx->outmax = +A_FLOAT_INF;
        ctx->outmin = -A_FLOAT_INF;
        ctx->mode = A_PID_INC;
        break;
    }
    a_pid_init(ctx, 0);
    return 1;
}

/***
 constructor for PID controller
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function new
*/
int LMODULE(pid_new)(lua_State *const L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_pid_s *const ctx = (a_pid_s *)lua_newuserdata(L, sizeof(a_pid_s));
    a_zero(ctx, sizeof(a_pid_s));
    ctx->summax = +A_FLOAT_INF;
    LMODULE2(pid_meta_, L, 1);
    lua_setmetatable(L, -2);
    return LMODULE2(pid_init_, L, ctx);
}

/***
 calculate function for PID controller
 @param ctx PID controller userdata
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function init
*/
int LMODULE(pid_init)(lua_State *const L)
{
    if (lua_gettop(L))
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return LMODULE2(pid_init_, L, ctx);
    }
    return 0;
}

/***
 set proportional integral derivative constant for PID controller
 @param ctx PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn pid PID controller userdata
 @function kpid
*/
int LMODULE(pid_kpid)(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_float_t const kp = (a_float_t)luaL_checknumber(L, -3);
        a_float_t const ki = (a_float_t)luaL_checknumber(L, -2);
        a_float_t const kd = (a_float_t)luaL_checknumber(L, -1);
        a_pid_kpid(ctx, kp, ki, kd);
        lua_pop(L, 3);
        return 1;
    }
    return 0;
}

/***
 calculate function for PID controller
 @param ctx PID controller userdata
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
int LMODULE(pid_iter)(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, -2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_pid_outf(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero clear function for PID controller
 @param ctx PID controller userdata
 @treturn pid PID controller userdata
 @function zero
*/
int LMODULE(pid_zero)(lua_State *const L)
{
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_pid_zero(ctx);
        return 1;
    }
    return 0;
}

static int LMODULE(pid_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_s *const ctx = (a_pid_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
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
    case 0x23C8F10E: // outmax
        ctx->outmax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->outmin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        ctx->mode = (unsigned int)luaL_checkinteger(L, 3);
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

static int LMODULE(pid_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_s const *const ctx = (a_pid_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0EB84F77: // mode
        lua_pushinteger(L, (lua_Integer)ctx->mode);
        break;
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
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->outmax);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->outmin);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->out.f);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->fdb.f);
        break;
    case 0x001AAD55: // err
        lua_pushnumber(L, (lua_Number)ctx->err.f);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(pid_new));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(pid_init));
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, LMODULE(pid_kpid));
        break;
    case 0x0E3068C8: // iter
        lua_pushcfunction(L, LMODULE(pid_iter));
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, LMODULE(pid_zero));
        break;
    case 0xA65758B2: // __index
    {
        l_int_s const enums[] = {
            {"mode", (lua_Integer)ctx->mode},
            {NULL, 0},
        };
        l_num_s const datas[] = {
            {"kp", ctx->kp},
            {"ki", ctx->ki},
            {"kd", ctx->kd},
            {"summax", ctx->summax},
            {"outmax", ctx->outmax},
            {"outmin", ctx->outmin},
            {"out", ctx->out.f},
            {"fdb", ctx->fdb.f},
            {"err", ctx->err.f},
            {NULL, 0},
        };
        l_func_s const funcs[] = {
            {"init", LMODULE(pid_init)},
            {"kpid", LMODULE(pid_kpid)},
            {"iter", LMODULE(pid_iter)},
            {"zero", LMODULE(pid_zero)},
            {"new", LMODULE(pid_new)},
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
 instance for PID controller
 @field OFF turn off PID controller
 @field POS positional PID controller
 @field INC incremental PID controller
 @table pid
*/
int LMODULE_(pid, lua_State *const L)
{
    l_int_s const enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"init", LMODULE(pid_init)},
        {"kpid", LMODULE(pid_kpid)},
        {"iter", LMODULE(pid_iter)},
        {"zero", LMODULE(pid_zero)},
        {"new", LMODULE(pid_new)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(pid_new));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_NEW, LMODULE(pid_iter)},
        {L_SET, LMODULE(pid_set)},
        {L_GET, LMODULE(pid_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    l_str_set(L, -1, L_NAME, LMODULES("pid"));
    l_func_reg(L, -1, metas);

    LMODULE2(pid_meta_, L, 0);
    LMODULE2(pid_func_, L, 0);

    return LMODULE2(pid_func_, L, 1);
}

int LMODULE(pid_func_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_func_));
    return 0;
}

int LMODULE(pid_meta_)(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, LFUNC2P(pid_meta_));
    return 0;
}
