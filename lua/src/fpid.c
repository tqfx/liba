/***
 fuzzy proportional integral derivative controller
 @module liba.fpid
*/

#include "fpid.h"
#include <string.h>

static int LMODULE(fpid_init_)(lua_State *const L, a_fpid_s *const ctx)
{
    a_vptr_t const buf = a_fpid_bufptr(ctx);
    a_uint_t const num = (a_uint_t)luaL_checkinteger(L, 1);
    a_real_t const dt = (a_real_t)luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    luaL_checktype(L, 4, LUA_TTABLE);
    luaL_checktype(L, 5, LUA_TTABLE);
    luaL_checktype(L, 6, LUA_TTABLE);
    luaL_checktype(L, 7, LUA_TTABLE);
    a_real_t const min = (a_real_t)luaL_checknumber(L, 8);
    a_real_t const max = (a_real_t)luaL_checknumber(L, 9);
    a_uint_t const col = (a_uint_t)lua_rawlen(L, 5);
    a_real_t const *const me = l_table_num_get(L, 3, ctx->me, 0);
    a_real_t const *const mec = l_table_num_get(L, 4, ctx->mec, 0);
    a_real_t const *const mkp = l_table_num_get(L, 5, ctx->mkp, 0);
    a_real_t const *const mki = l_table_num_get(L, 6, ctx->mki, 0);
    a_real_t const *const mkd = l_table_num_get(L, 7, ctx->mkd, 0);
    a_fpid_init(ctx, dt, col, me, mec, mkp, mki, mkd, min, max);
    a_fpid_buf1(ctx, l_alloc(L, buf, A_FPID_BUF1(num)), num);
    lua_isnumber(L, 10)
        ? a_fpid_pos(ctx, (a_real_t)lua_tonumber(L, 10))
        : a_fpid_inc(ctx);
    return 1;
}

/***
 destructor for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @function die
*/
int LMODULE(fpid_die)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        ctx->me = A_REAL_P(l_alloc(L, ctx->me, 0));
        ctx->mec = A_REAL_P(l_alloc(L, ctx->mec, 0));
        ctx->mkp = A_REAL_P(l_alloc(L, ctx->mkp, 0));
        ctx->mki = A_REAL_P(l_alloc(L, ctx->mki, 0));
        ctx->mkd = A_REAL_P(l_alloc(L, ctx->mkd, 0));
        ctx->idx = a_uint_p(l_alloc(L, a_fpid_bufptr(ctx), 0));
        ctx->val = 0;
    }
    return 0;
}

/***
 constructor for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function new
*/
int LMODULE(fpid_new)(lua_State *const L)
{
    if (lua_gettop(L) > 8)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_fpid_s *const ctx = (a_fpid_s *)lua_newuserdata(L, sizeof(a_fpid_s));
        a_zero(ctx, sizeof(a_fpid_s));
        LMODULE2(fpid_meta_, L, 1);
        lua_setmetatable(L, -2);
        return LMODULE2(fpid_init_, L, ctx);
    }
    return 0;
}

/***
 initialize function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function init
*/
int LMODULE(fpid_init)(lua_State *const L)
{
    if (lua_gettop(L) > 9)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return LMODULE2(fpid_init_, L, ctx);
    }
    return 0;
}

/***
 calculate function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function iter
*/
int LMODULE(fpid_iter)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t const set = (a_real_t)luaL_checknumber(L, -2);
        a_real_t const fdb = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_fpid_outv(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function zero
*/
int LMODULE(fpid_zero)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_zero(ctx);
        return 1;
    }
    return 0;
}

/***
 set rule base for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
int LMODULE(fpid_base)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -6);
    if (ctx)
    {
        a_uint_t const num = (a_uint_t)lua_rawlen(L, -3);
        a_real_t const *const me = l_table_num_get(L, -5, ctx->me, 0);
        a_real_t const *const mec = l_table_num_get(L, -4, ctx->mec, 0);
        a_real_t const *const mkp = l_table_num_get(L, -3, ctx->mkp, 0);
        a_real_t const *const mki = l_table_num_get(L, -2, ctx->mki, 0);
        a_real_t const *const mkd = l_table_num_get(L, -1, ctx->mkd, 0);
        a_fpid_base(ctx, num, me, mec, mkp, mki, mkd);
        lua_pop(L, 5);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative constant for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn fpid fuzzy PID controller userdata
 @function kpid
*/
int LMODULE(fpid_kpid)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_real_t const kp = (a_real_t)luaL_checknumber(L, -3);
        a_real_t const ki = (a_real_t)luaL_checknumber(L, -2);
        a_real_t const kd = (a_real_t)luaL_checknumber(L, -1);
        a_fpid_kpid(ctx, kp, ki, kd);
        lua_pop(L, 3);
        return 1;
    }
    return 0;
}

/***
 positional fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number max maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function pos
*/
int LMODULE(fpid_pos)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_fpid_pos(ctx, (a_real_t)luaL_checknumber(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

/***
 incremental fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function inc
*/
int LMODULE(fpid_inc)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_inc(ctx);
        return 1;
    }
    return 0;
}

/***
 turn off fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function off
*/
int LMODULE(fpid_off)(lua_State *const L)
{
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_off(ctx);
        return 1;
    }
    return 0;
}

static int LMODULE(fpid_set)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_fpid_s *const ctx = (a_fpid_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        a_pid_set_dt(&ctx->pid, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x00003731: // kp
        ctx->kp = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->ki = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->kd = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0019E5B7: // buf
    {
        a_uint_t max = (a_uint_t)luaL_checkinteger(L, -1);
        a_vptr_t ptr = l_alloc(L, a_fpid_bufptr(ctx), A_FPID_BUF1(max));
        a_fpid_buf1(ctx, ptr, max);
        break;
    }
    case 0x10E9FF9D: // summax
        ctx->pid.summax = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        a_pid_set_mode(&ctx->pid, (a_uint_t)luaL_checkinteger(L, 3));
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

static int LMODULE(fpid_get)(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_fpid_s const *const ctx = (a_fpid_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        lua_pushnumber(L, (lua_Number)a_pid_dt(&ctx->pid));
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
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->pid.outmin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->pid.outmax);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, (lua_Number)ctx->pid.summax);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->pid.out.v);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->pid.fdb.v);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, (lua_Number)ctx->pid.ec.v);
        break;
    case 0x00000065: // e
        lua_pushnumber(L, (lua_Number)ctx->pid.e.v);
        break;
    case 0x001A25B4: // col
        lua_pushinteger(L, (lua_Integer)a_fpid_col(ctx));
        break;
    case 0x0019E5B7: // buf
        lua_pushinteger(L, (lua_Integer)a_fpid_bufnum(ctx));
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, (lua_Integer)a_pid_mode(&ctx->pid));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, LMODULE(fpid_new));
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, LMODULE(fpid_init));
        break;
    case 0x0E3068C8: // iter
        lua_pushcfunction(L, LMODULE(fpid_iter));
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, LMODULE(fpid_zero));
        break;
    case 0x0D3B56FD: // base
        lua_pushcfunction(L, LMODULE(fpid_base));
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, LMODULE(fpid_kpid));
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, LMODULE(fpid_pos));
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, LMODULE(fpid_inc));
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, LMODULE(fpid_off));
        break;
    case 0xA65758B2: // __index
    {
        l_int_s const enums[] = {
            {"col", (lua_Integer)a_fpid_col(ctx)},
            {"buf", (lua_Integer)a_fpid_bufnum(ctx)},
            {"mode", (lua_Integer)a_pid_mode(&ctx->pid)},
            {NULL, 0},
        };
        l_num_s const datas[] = {
            {"dt", a_pid_dt(&ctx->pid)},
            {"kp", ctx->kp},
            {"ki", ctx->ki},
            {"kd", ctx->kd},
            {"outmin", ctx->pid.outmin},
            {"outmax", ctx->pid.outmax},
            {"summax", ctx->pid.summax},
            {"out", ctx->pid.out.v},
            {"fdb", ctx->pid.fdb.v},
            {"ec", ctx->pid.ec.v},
            {"e", ctx->pid.e.v},
            {NULL, 0},
        };
        l_func_s const funcs[] = {
            {"init", LMODULE(fpid_init)},
            {"iter", LMODULE(fpid_iter)},
            {"zero", LMODULE(fpid_zero)},
            {"base", LMODULE(fpid_base)},
            {"kpid", LMODULE(fpid_kpid)},
            {"pos", LMODULE(fpid_pos)},
            {"inc", LMODULE(fpid_inc)},
            {"off", LMODULE(fpid_off)},
            {"new", LMODULE(fpid_new)},
            {NULL, NULL},
        };
        lua_createtable(L, 0, L_COUNT(enums) + L_COUNT(datas) + L_COUNT(funcs) - 3);
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
 instance for fuzzy PID controller
 @field OFF turn off fuzzy PID controller
 @field POS positional fuzzy PID controller
 @field INC incremental fuzzy PID controller
 @table fpid
*/
int LMODULE_(fpid, lua_State *const L)
{
    l_int_s const enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"init", LMODULE(fpid_init)},
        {"iter", LMODULE(fpid_iter)},
        {"zero", LMODULE(fpid_zero)},
        {"base", LMODULE(fpid_base)},
        {"kpid", LMODULE(fpid_kpid)},
        {"pos", LMODULE(fpid_pos)},
        {"inc", LMODULE(fpid_inc)},
        {"off", LMODULE(fpid_off)},
        {"new", LMODULE(fpid_new)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(enums) + L_COUNT(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    l_func_set(L, -1, L_NEW, LMODULE(fpid_new));
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_NEW, LMODULE(fpid_iter)},
        {L_DIE, LMODULE(fpid_die)},
        {L_SET, LMODULE(fpid_set)},
        {L_GET, LMODULE(fpid_get)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_COUNT(metas));
    l_str_set(L, -1, L_NAME, "fpid");
    l_func_reg(L, -1, metas);

    LMODULE2(fpid_meta_, L, 0);
    LMODULE2(fpid_func_, L, 0);

    return LMODULE2(fpid_func_, L, 1);
}

int LMODULE(fpid_func_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(fpid_func_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}

int LMODULE(fpid_meta_)(lua_State *const L, int const ret)
{
    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    void *const p = (void *)(intptr_t)LMODULE(fpid_meta_);
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, p);
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, p);
    return 0;
}
