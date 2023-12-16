/***
 fuzzy proportional integral derivative controller
 @module liba.pid_fuzzy
*/

#include "pid_fuzzy.h"
#include "a/pid_fuzzy.h"

/***
 destructor for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @function die
*/
int liba_pid_fuzzy_die(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_alloc(L, ctx->me, 0);
        lua_alloc(L, ctx->mec, 0);
        lua_alloc(L, ctx->mkp, 0);
        lua_alloc(L, ctx->mki, 0);
        lua_alloc(L, ctx->mkd, 0);
        lua_alloc(L, a_pid_fuzzy_joint(ctx), 0);
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
int liba_pid_fuzzy_new(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_newuserdata(L, sizeof(a_pid_fuzzy_s));
    a_zero(ctx, sizeof(a_pid_fuzzy_s));
    liba_pid_fuzzy_meta_(L, 1);
    lua_setmetatable(L, -2);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->pid.kp = ctx->kp = 1;
    ctx->op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(ctx);
    return 1;
}

/***
 initialize for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function init
*/
int liba_pid_fuzzy_init(lua_State *const L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    ctx->pid.summax = +A_FLOAT_INF;
    ctx->pid.summin = -A_FLOAT_INF;
    ctx->pid.outmax = +A_FLOAT_INF;
    ctx->pid.outmin = -A_FLOAT_INF;
    ctx->pid.kp = ctx->kp = 1;
    ctx->op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
    a_pid_fuzzy_init(ctx);
    return 1;
}

/***
 zeroing for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function zero
*/
int liba_pid_fuzzy_zero(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_fuzzy_zero(ctx);
        return 1;
    }
    return 0;
}

/***
 set fuzzy relational operator for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam int op enumeration for fuzzy PID controller operator
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function op
*/
int liba_pid_fuzzy_op(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_pid_fuzzy_set_op(ctx, (unsigned int)luaL_checkinteger(L, 2));
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
 @function rule
*/
int liba_pid_fuzzy_rule(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        unsigned int const num = (unsigned int)lua_rawlen(L, 2);
        a_float_t const *const me = lua_table_num_get(L, 2, ctx->me, 0);
        a_float_t const *const mec = lua_table_num_get(L, 3, ctx->mec, 0);
        a_float_t const *const mkp = lua_table_num_get(L, 4, ctx->mkp, 0);
        a_float_t const *const mki = lua_table_num_get(L, 5, ctx->mki, 0);
        a_float_t const *const mkd = lua_table_num_get(L, 6, ctx->mkd, 0);
        a_pid_fuzzy_rule(ctx, num, me, mec, mkp, mki, mkd);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 set joint buffer for fuzzy PID controller
 @tparam a.pid_fuzzy ctx fuzzy PID controller userdata
 @tparam int num maximum number triggered by the rule
 @treturn a.pid_fuzzy fuzzy PID controller userdata
 @function set_joint
*/
int liba_pid_fuzzy_joint(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        unsigned int const num = (unsigned int)luaL_checkinteger(L, 2);
        void *ptr = lua_alloc(L, a_pid_fuzzy_joint(ctx), A_PID_FUZZY_JOINT(num));
        a_pid_fuzzy_set_joint(ctx, ptr, num);
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
 @function kpid
*/
int liba_pid_fuzzy_kpid(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const kp = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const ki = (a_float_t)luaL_checknumber(L, 3);
        a_float_t const kd = (a_float_t)luaL_checknumber(L, 4);
        a_pid_fuzzy_kpid(ctx, kp, ki, kd);
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
int liba_pid_fuzzy_run(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
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
int liba_pid_fuzzy_pos(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
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
int liba_pid_fuzzy_inc(lua_State *const L)
{
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const set = (a_float_t)luaL_checknumber(L, 2);
        a_float_t const fdb = (a_float_t)luaL_checknumber(L, 3);
        lua_pushnumber(L, (lua_Number)a_pid_fuzzy_inc(ctx, set, fdb));
        return 1;
    }
    return 0;
}

static int liba_pid_fuzzy_set(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_fuzzy_s *const ctx = (a_pid_fuzzy_s *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00003731: // kp
        ctx->pid.kp = ctx->kp = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->pid.ki = ctx->ki = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->pid.kd = ctx->kd = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x10E9FF9D: // summax
        ctx->pid.summax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x10EA03AB: // summin
        ctx->pid.summin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F10E: // outmax
        ctx->pid.outmax = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x23C8F51C: // outmin
        ctx->pid.outmin = (a_float_t)luaL_checknumber(L, 3);
        break;
    case 0x53A8DB2E: // joint
    {
        unsigned int const num = (unsigned int)luaL_checkinteger(L, 3);
        void *ptr = lua_alloc(L, a_pid_fuzzy_joint(ctx), A_PID_FUZZY_JOINT(num));
        a_pid_fuzzy_set_joint(ctx, ptr, num);
        break;
    }
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

static int liba_pid_fuzzy_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_pid_fuzzy_s const *const ctx = (a_pid_fuzzy_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
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
        lua_pushnumber(L, (lua_Number)ctx->pid.summax);
        break;
    case 0x10EA03AB: // summin
        lua_pushnumber(L, (lua_Number)ctx->pid.summin);
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
    case 0xABD2FFCA: // order
        lua_pushinteger(L, (lua_Integer)ctx->order);
        break;
    case 0x53A8DB2E: // joint
        lua_pushinteger(L, (lua_Integer)ctx->joint);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_pid_fuzzy_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, liba_pid_fuzzy_init);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, liba_pid_fuzzy_zero);
        break;
    case 0x0000393D: // op
        lua_pushcfunction(L, liba_pid_fuzzy_op);
        break;
    case 0x0F6569CC: // rule
        lua_pushcfunction(L, liba_pid_fuzzy_rule);
        break;
    case 0xE89684D9: // set_joint
        lua_pushcfunction(L, liba_pid_fuzzy_joint);
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, liba_pid_fuzzy_kpid);
        break;
    case 0x001E164F: // run
        lua_pushcfunction(L, liba_pid_fuzzy_run);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, liba_pid_fuzzy_pos);
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, liba_pid_fuzzy_inc);
        break;
    case 0xA65758B2: // __index
        liba_pid_fuzzy_meta_(L, 1);
        lua_num_set(L, -1, "kp", ctx->kp);
        lua_num_set(L, -1, "ki", ctx->ki);
        lua_num_set(L, -1, "kd", ctx->kd);
        lua_num_set(L, -1, "summax", ctx->pid.summax);
        lua_num_set(L, -1, "summin", ctx->pid.summin);
        lua_num_set(L, -1, "outmax", ctx->pid.outmax);
        lua_num_set(L, -1, "outmin", ctx->pid.outmin);
        lua_num_set(L, -1, "out", ctx->pid.out);
        lua_num_set(L, -1, "fdb", ctx->pid.fdb);
        lua_num_set(L, -1, "err", ctx->pid.err);
        lua_int_set(L, -1, "order", (lua_Integer)ctx->order);
        lua_int_set(L, -1, "joint", (lua_Integer)ctx->joint);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_pid_fuzzy(lua_State *const L)
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
    lua_int_s const enums[] = {
        {"CAP", A_PID_FUZZY_CAP},
        {"CAP_ALGEBRA", A_PID_FUZZY_CAP_ALGEBRA},
        {"CAP_BOUNDED", A_PID_FUZZY_CAP_BOUNDED},
        {"CUP", A_PID_FUZZY_CUP},
        {"CUP_ALGEBRA", A_PID_FUZZY_CUP_ALGEBRA},
        {"CUP_BOUNDED", A_PID_FUZZY_CUP_BOUNDED},
        {"EQU", A_PID_FUZZY_EQU},
        {NULL, 0},
    };
    lua_fun_s const funcs[] = {
        {"new", liba_pid_fuzzy_new},
        {"init", liba_pid_fuzzy_init},
        {"zero", liba_pid_fuzzy_zero},
        {"op", liba_pid_fuzzy_op},
        {"rule", liba_pid_fuzzy_rule},
        {"set_joint", liba_pid_fuzzy_joint},
        {"kpid", liba_pid_fuzzy_kpid},
        {"run", liba_pid_fuzzy_run},
        {"pos", liba_pid_fuzzy_pos},
        {"inc", liba_pid_fuzzy_inc},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
    lua_int_reg(L, -1, enums);
    lua_fun_reg(L, -1, funcs);

    lua_fun_s const metas[] = {
        {"__newindex", liba_pid_fuzzy_set},
        {"__index", liba_pid_fuzzy_get},
        {"__gc", liba_pid_fuzzy_die},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, metas);
    lua_fun_reg(L, -1, funcs);
    lua_str_set(L, -1, "__name", "a.pid_fuzzy");

    liba_pid_fuzzy_meta_(L, 0);
    liba_pid_fuzzy_func_(L, 0);

    return liba_pid_fuzzy_func_(L, 1);
}

int liba_pid_fuzzy_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_fuzzy_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_fuzzy_func_));
    return 0;
}

int liba_pid_fuzzy_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_fuzzy_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_pid_fuzzy_meta_));
    return 0;
}
