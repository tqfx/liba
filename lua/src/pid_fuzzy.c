/***
 fuzzy proportional integral derivative controller
 @module liba.pid_fuzzy
*/

#include "pid_fuzzy.h"
#include "a/pid_fuzzy.h"
#include "a/math.h"

/***
 destructor for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @function die
*/
int liba_pid_fuzzy_die(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_alloc(L, ctx->me, 0);
        lua_alloc(L, ctx->mec, 0);
        lua_alloc(L, ctx->mkp, 0);
        lua_alloc(L, ctx->mki, 0);
        lua_alloc(L, ctx->mkd, 0);
        lua_alloc(L, a_pid_fuzzy_bfuzz(ctx), 0);
        ctx->me = 0;
        ctx->mec = 0;
        ctx->mkp = 0;
        ctx->mki = 0;
        ctx->mkd = 0;
        ctx->idx = 0;
        ctx->val = 0;
    }
    return 0;
}

/***
 constructor for fuzzy PID controller
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function new
*/
int liba_pid_fuzzy_new(lua_State *L)
{
    a_pid_fuzzy *const ctx = lua_newclass(L, a_pid_fuzzy);
    lua_registry_get(L, liba_pid_fuzzy_new);
    lua_setmetatable(L, -2);
    ctx->pid.kp = ctx->kp = 1;
    ctx->pid.ki = ctx->ki = 0;
    ctx->pid.kd = ctx->kd = 0;
    ctx->pid.summax = +A_REAL_INF;
    ctx->pid.summin = -A_REAL_INF;
    ctx->pid.outmax = +A_REAL_INF;
    ctx->pid.outmin = -A_REAL_INF;
    ctx->me = 0;
    ctx->mec = 0;
    ctx->mkp = 0;
    ctx->mki = 0;
    ctx->mkd = 0;
    ctx->idx = 0;
    ctx->val = 0;
    ctx->nrule = 0;
    ctx->nfuzz = 0;
    ctx->opr = a_fuzzy_equ;
    a_pid_fuzzy_init(ctx);
    return 1;
}

/***
 initialize for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function init
*/
int liba_pid_fuzzy_init(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        ctx->pid.kp = ctx->kp = 1;
        ctx->pid.ki = ctx->ki = 0;
        ctx->pid.kd = ctx->kd = 0;
        ctx->pid.summax = +A_REAL_INF;
        ctx->pid.summin = -A_REAL_INF;
        ctx->pid.outmax = +A_REAL_INF;
        ctx->pid.outmin = -A_REAL_INF;
        ctx->opr = a_fuzzy_equ;
        a_pid_fuzzy_init(ctx);
        return 1;
    }
    return 0;
}

/***
 set fuzzy relational operator for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam int opr enumeration for fuzzy PID controller operator
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_opr
*/
int liba_pid_fuzzy_set_opr(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_fuzzy_set_opr(ctx, (unsigned int)luaL_checkinteger(L, 2));
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set memory block for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam int num maximum number triggered by the rule
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_nfuzz
*/
int liba_pid_fuzzy_set_nfuzz(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        unsigned int const num = (unsigned int)luaL_checkinteger(L, 2);
        void *ptr = lua_alloc(L, a_pid_fuzzy_bfuzz(ctx), A_PID_FUZZY_BFUZZ(num));
        a_pid_fuzzy_set_bfuzz(ctx, ptr, num);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set rule base for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table which must be a square matrix
 @tparam table mki points to Ki's rule base table which must be a square matrix
 @tparam table mkd points to Kd's rule base table which must be a square matrix
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_rule
*/
int liba_pid_fuzzy_set_rule(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const *me;
        a_real const *mec;
        a_real const *mkp;
        a_real const *mki;
        a_real const *mkd;
        unsigned int n = 0;
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        luaL_checktype(L, 4, LUA_TTABLE);
        luaL_checktype(L, 5, LUA_TTABLE);
        luaL_checktype(L, 6, LUA_TTABLE);
        me = lua_array_num_get(L, 2, ctx->me, 0, 2);
        mec = lua_array_num_get(L, 3, ctx->mec, 0, 2);
        mkp = lua_array_num_get(L, 4, ctx->mkp, &n, 2);
        mki = lua_array_num_get(L, 5, ctx->mki, 0, 2);
        mkd = lua_array_num_get(L, 6, ctx->mkd, 0, 2);
        a_pid_fuzzy_set_rule(ctx, a_u32_sqrt(n), me, mec, mkp, mki, mkd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set proportional integral derivative constant for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_kpid
*/
int liba_pid_fuzzy_set_kpid(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const kp = (a_real)luaL_checknumber(L, 2);
        a_real const ki = (a_real)luaL_checknumber(L, 3);
        a_real const kd = (a_real)luaL_checknumber(L, 4);
        a_pid_fuzzy_set_kpid(ctx, kp, ki, kd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function run
*/
int liba_pid_fuzzy_run(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_fuzzy_run(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for positional fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
int liba_pid_fuzzy_pos(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_fuzzy_pos(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 calculate for incremental fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
int liba_pid_fuzzy_inc(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real const set = (a_real)luaL_checknumber(L, 2);
        a_real const fdb = (a_real)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_fuzzy_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

/***
 zeroing for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function zero
*/
int liba_pid_fuzzy_zero(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_fuzzy_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_pid_fuzzy_set(lua_State *L)
{
    a_pid_fuzzy *const ctx = (a_pid_fuzzy *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x00003731: /* kp */
        ctx->pid.kp = ctx->kp = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: /* ki */
        ctx->pid.ki = ctx->ki = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x00003725: /* kd */
        ctx->pid.kd = ctx->kd = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: /* summax */
        ctx->pid.summax = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x10EA03AB: /* summin */
        ctx->pid.summin = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: /* outmax */
        ctx->pid.outmax = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: /* outmin */
        ctx->pid.outmin = (a_real)luaL_checknumber(L, 3);
        break;
    case 0x98AE2495: /* nfuzz */
    {
        unsigned int const num = (unsigned int)luaL_checkinteger(L, 3);
        void *ptr = lua_alloc(L, a_pid_fuzzy_bfuzz(ctx), A_PID_FUZZY_BFUZZ(num));
        a_pid_fuzzy_set_bfuzz(ctx, ptr, num);
        break;
    }
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

static int liba_pid_fuzzy_get(lua_State *L)
{
    a_pid_fuzzy const *const ctx = (a_pid_fuzzy const *)lua_touserdata(L, 1);
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
        lua_pushnumber(L, (lua_Number)ctx->pid.summax);
        break;
    case 0x10EA03AB: /* summin */
        lua_pushnumber(L, (lua_Number)ctx->pid.summin);
        break;
    case 0x001E5957: /* sum */
        lua_pushnumber(L, (lua_Number)ctx->pid.sum);
        break;
    case 0x23C8F10E: /* outmax */
        lua_pushnumber(L, (lua_Number)ctx->pid.outmax);
        break;
    case 0x23C8F51C: /* outmin */
        lua_pushnumber(L, (lua_Number)ctx->pid.outmin);
        break;
    case 0x001D4D3A: /* out */
        lua_pushnumber(L, (lua_Number)ctx->pid.out);
        break;
    case 0x001AE924: /* fdb */
        lua_pushnumber(L, (lua_Number)ctx->pid.fdb);
        break;
    case 0x001AAD55: /* err */
        lua_pushnumber(L, (lua_Number)ctx->pid.err);
        break;
    case 0x9A49C09A: /* nrule */
        lua_pushinteger(L, (lua_Integer)ctx->nrule);
        break;
    case 0x98AE2495: /* nfuzz */
        lua_pushinteger(L, (lua_Integer)ctx->nfuzz);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_pid_fuzzy_new);
        lua_num_set(L, -1, "kp", ctx->kp);
        lua_num_set(L, -1, "ki", ctx->ki);
        lua_num_set(L, -1, "kd", ctx->kd);
        lua_num_set(L, -1, "summax", ctx->pid.summax);
        lua_num_set(L, -1, "summin", ctx->pid.summin);
        lua_num_set(L, -1, "sum", ctx->pid.sum);
        lua_num_set(L, -1, "outmax", ctx->pid.outmax);
        lua_num_set(L, -1, "outmin", ctx->pid.outmin);
        lua_num_set(L, -1, "out", ctx->pid.out);
        lua_num_set(L, -1, "fdb", ctx->pid.fdb);
        lua_num_set(L, -1, "err", ctx->pid.err);
        lua_int_set(L, -1, "nrule", (lua_Integer)ctx->nrule);
        lua_int_set(L, -1, "nfuzz", (lua_Integer)ctx->nfuzz);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_pid_fuzzy_(lua_State *L)
{
    lua_pushcfunction(L, liba_pid_fuzzy_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_pid_fuzzy(lua_State *L)
{
    /***
     enumeration for fuzzy relational operator
     @field CAP         min(a,b)
     @field CAP_ALGEBRA a*b
     @field CAP_BOUNDED max(a+b-1,0)
     @field CUP         max(a,b)
     @field CUP_ALGEBRA a+b-a*b
     @field CUP_BOUNDED min(a+b,1)
     @field EQU         sqrt(a,b)*sqrt(1-(1-a)*(1-b))
     @table op
    */
    static lua_int const enums[] = {
        {"CAP", A_PID_FUZZY_CAP},
        {"CAP_ALGEBRA", A_PID_FUZZY_CAP_ALGEBRA},
        {"CAP_BOUNDED", A_PID_FUZZY_CAP_BOUNDED},
        {"CUP", A_PID_FUZZY_CUP},
        {"CUP_ALGEBRA", A_PID_FUZZY_CUP_ALGEBRA},
        {"CUP_BOUNDED", A_PID_FUZZY_CUP_BOUNDED},
        {"EQU", A_PID_FUZZY_EQU},
    };
    static lua_fun const funcs[] = {
        {"new", liba_pid_fuzzy_new},
        {"init", liba_pid_fuzzy_init},
        {"set_opr", liba_pid_fuzzy_set_opr},
        {"set_nfuzz", liba_pid_fuzzy_set_nfuzz},
        {"set_rule", liba_pid_fuzzy_set_rule},
        {"set_kpid", liba_pid_fuzzy_set_kpid},
        {"run", liba_pid_fuzzy_run},
        {"pos", liba_pid_fuzzy_pos},
        {"inc", liba_pid_fuzzy_inc},
        {"zero", liba_pid_fuzzy_zero},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_pid_fuzzy_set},
        {"__index", liba_pid_fuzzy_get},
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 503)
        {"__close", liba_pid_fuzzy_die},
#endif /* LUA_VERSION_NUM */
        {"__gc", liba_pid_fuzzy_die},
    };

    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs));
    lua_int_reg(L, -1, enums, A_LEN(enums));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_pid_fuzzy_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.pid_fuzzy");
    lua_registry_set(L, liba_pid_fuzzy_new);

    return 1;
}
