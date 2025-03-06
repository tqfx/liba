/***
 linear regression
 @module liba.regress_linear
*/

#include "regress_linear.h"
#include "a/regress_linear.h"

/***
 destructor for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @function die
*/
int liba_regress_linear_die(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_alloc(L, ctx->coef_p, 0);
        ctx->coef_p = 0;
        ctx->coef_n = 0;
    }
    return 0;
}

/***
 constructor for linear regression
 @tparam table coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_linear linear regression userdata
 @function new
*/
int liba_regress_linear_new(lua_State *L)
{
    a_real b, *p;
    unsigned int n = 0;
    a_regress_linear *ctx;
    luaL_checktype(L, 1, LUA_TTABLE);
    b = (a_real)luaL_optnumber(L, 2, 0);
    p = lua_array_num_get(L, 1, NULL, &n, 1);
    ctx = lua_newclass(L, a_regress_linear);
    lua_registry_get(L, liba_regress_linear_new);
    lua_setmetatable(L, -2);
    a_regress_linear_init(ctx, p, n, b);
    return 1;
}

/***
 initialize for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam number coef regression coefficient
 @tparam number bias intercept
 @treturn a.regress_linear linear regression userdata
 @function init
*/
int liba_regress_linear_init(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real b, *p;
        unsigned int n = (unsigned int)ctx->coef_n;
        luaL_checktype(L, 2, LUA_TTABLE);
        b = (a_real)luaL_optnumber(L, 3, 0);
        p = lua_array_num_get(L, 2, ctx->coef_p, &n, 1);
        a_regress_linear_init(ctx, p, n, b);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 compute predicted value for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam number val independent variable
 @treturn number predicted value
 @function eval
*/
int liba_regress_linear_eval(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real *p;
        luaL_checktype(L, 2, LUA_TTABLE);
        p = lua_array_num_get(L, 2, NULL, NULL, 1);
        lua_pushnumber(L, (lua_Number)a_regress_linear_eval(ctx, p));
        lua_alloc(L, p, 0);
        return 1;
    }
    return 0;
}

/***
 compute residuals for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @treturn table residuals, specified as a numeric vector
 @function err
*/
int liba_regress_linear_err(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real *x, *y;
        unsigned int m = 0, n = 0;
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        x = lua_array_num_get(L, 2, NULL, &m, 1);
        y = lua_array_num_get(L, 3, NULL, &n, 1);
        m /= (unsigned int)ctx->coef_n;
        if (m < n) { n = m; }
        a_regress_linear_err(ctx, n, x, y, y);
        lua_array_num_new(L, y, n);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        return 1;
    }
    return 0;
}

/***
 gradient descent for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam table input predictor data, specified as a numeric vector
 @tparam number error residual, specified as a numeric scalar
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function gd
*/
int liba_regress_linear_gd(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real alpha, error, *input;
        luaL_checktype(L, 2, LUA_TTABLE);
        error = (a_real)luaL_checknumber(L, 3);
        alpha = (a_real)luaL_checknumber(L, 4);
        input = lua_array_num_get(L, 2, NULL, NULL, 1);
        a_regress_linear_gd(ctx, input, error, alpha);
        lua_alloc(L, input, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 stochastic gradient descent for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function sgd
*/
int liba_regress_linear_sgd(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real alpha, *x, *y;
        unsigned int m = 0, n = 0;
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        alpha = (a_real)luaL_checknumber(L, 4);
        x = lua_array_num_get(L, 2, NULL, &m, 1);
        y = lua_array_num_get(L, 3, NULL, &n, 1);
        m /= (unsigned int)ctx->coef_n;
        if (m < n) { n = m; }
        a_regress_linear_sgd(ctx, n, x, y, alpha);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 batch gradient descent for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number alpha learning rate for gradient descent
 @treturn a.regress_linear linear regression userdata
 @function bgd
*/
int liba_regress_linear_bgd(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real alpha, *x, *y;
        unsigned int m = 0, n = 0;
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        alpha = (a_real)luaL_checknumber(L, 4);
        x = lua_array_num_get(L, 2, NULL, &m, 1);
        y = lua_array_num_get(L, 3, NULL, &n, 1);
        m /= (unsigned int)ctx->coef_n;
        if (m < n) { n = m; }
        a_regress_linear_err(ctx, n, x, y, y);
        a_regress_linear_bgd(ctx, n, x, y, alpha);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 mini-batch gradient descent for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @tparam table x predictor data, specified as a numeric matrix
 @tparam table y response data, specified as a numeric vector
 @tparam number delta threshold for gradient descent value
 @tparam number lrmax maximum learning rate of iterations
 @tparam number lrmin minimum learning rate of iterations
 @tparam[opt] integer lrtim total number of learning rate steps
 @tparam[opt] integer epoch maximum number of epochs
 @tparam[opt] integer batch batch size of data
 @treturn number change in loss function
 @function mgd
*/
int liba_regress_linear_mgd(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_real *x, *y, *err, r;
        unsigned int m = 0, n = 0;
        a_real delta, lrmax, lrmin;
        unsigned int lrtim, epoch, batch;
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        delta = (a_real)luaL_checknumber(L, 4);
        lrmax = (a_real)luaL_checknumber(L, 5);
        lrmin = (a_real)luaL_checknumber(L, 6);
        lrtim = (unsigned int)luaL_optinteger(L, 7, 100);
        epoch = (unsigned int)luaL_optinteger(L, 8, 1000);
        batch = (unsigned int)luaL_optinteger(L, 9, 10);
        x = lua_array_num_get(L, 2, NULL, &m, 1);
        y = lua_array_num_get(L, 3, NULL, &n, 1);
        m /= (unsigned int)ctx->coef_n;
        if (m < n) { n = m; }
        err = (a_real *)lua_alloc(L, NULL, sizeof(a_real) * n);
        /* clang-format off */
        r = a_regress_linear_mgd(ctx, n, x, y, err,
            delta, lrmax, lrmin, lrtim, epoch, batch);
        /* clang-format on */
        lua_pushnumber(L, (lua_Number)r);
        lua_alloc(L, err, 0);
        lua_alloc(L, y, 0);
        lua_alloc(L, x, 0);
        return 1;
    }
    return 0;
}

/***
 zeroing for linear regression
 @tparam a.regress_linear ctx linear regression userdata
 @treturn a.regress_linear linear regression userdata
 @function zero
*/
int liba_regress_linear_zero(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_regress_linear_zero(ctx);
        return 1;
    }
    return 0;
}

static int liba_regress_linear_set(lua_State *L)
{
    a_regress_linear *const ctx = (a_regress_linear *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0D6147ED: /* coef */
    {
        unsigned int n = (unsigned int)ctx->coef_n;
        luaL_checktype(L, 3, LUA_TTABLE);
        ctx->coef_p = lua_array_num_get(L, 3, ctx->coef_p, &n, 1);
        ctx->coef_n = n;
        break;
    }
    case 0x0D3D661D: /* bias */
    {
        ctx->bias = (a_real)luaL_checknumber(L, 3);
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

static int liba_regress_linear_get(lua_State *L)
{
    a_regress_linear const *const ctx = (a_regress_linear const *)lua_touserdata(L, 1);
    switch (a_hash_bkdr(lua_tostring(L, 2), 0))
    {
    case 0x0D6147ED: /* coef */
        lua_array_num_new(L, ctx->coef_p, (unsigned int)ctx->coef_n);
        break;
    case 0x0D3D661D: /* bias */
        lua_pushnumber(L, (lua_Number)ctx->bias);
        break;
    case 0xA65758B2: /* __index */
        lua_registry_get(L, liba_regress_linear_new);
        lua_pushstring(L, "coef");
        lua_array_num_new(L, ctx->coef_p, (unsigned int)ctx->coef_n);
        lua_rawset(L, -3);
        lua_num_set(L, -1, "bias", ctx->bias);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_replace(L, 1);
        lua_rawget(L, 1);
    }
    return 1;
}

static int liba_regress_linear_(lua_State *L)
{
    lua_pushcfunction(L, liba_regress_linear_new);
    lua_replace(L, 1);
    lua_call(L, lua_gettop(L) - 1, 1);
    return 1;
}

int luaopen_liba_regress_linear(lua_State *L)
{
    static lua_fun const funcs[] = {
        {"init", liba_regress_linear_init},
        {"eval", liba_regress_linear_eval},
        {"zero", liba_regress_linear_zero},
        {"err", liba_regress_linear_err},
        {"gd", liba_regress_linear_gd},
        {"sgd", liba_regress_linear_sgd},
        {"bgd", liba_regress_linear_bgd},
        {"mgd", liba_regress_linear_mgd},
        {"new", liba_regress_linear_new},
    };
    static lua_fun const metas[] = {
        {"__newindex", liba_regress_linear_set},
        {"__index", liba_regress_linear_get},
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 503)
        {"__close", liba_regress_linear_die},
#endif /* LUA_VERSION_NUM */
        {"__gc", liba_regress_linear_die},
    };

    lua_createtable(L, 0, A_LEN(funcs));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__call", liba_regress_linear_);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, A_LEN(metas) + A_LEN(funcs) + 1);
    lua_fun_reg(L, -1, metas, A_LEN(metas));
    lua_fun_reg(L, -1, funcs, A_LEN(funcs));
    lua_str_set(L, -1, "__name", "a.regress_linear");
    lua_registry_set(L, liba_regress_linear_new);

    return 1;
}
