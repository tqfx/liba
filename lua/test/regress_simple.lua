#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.regress_simple))

local x = { 0, 1, 2, 3, 4 }
local y = { 1, 2, 3, 4, 5 }

local ctx = a.regress_simple.new()
test.dir(getmetatable(ctx))
assert(type(a.regress_simple.eval(ctx, 1)) == "number")
assert(type(a.regress_simple.evar(ctx, 1)) == "number")
assert(type(a.regress_simple.ols_(ctx, x, y, 2, 3)) == "userdata")
assert(type(a.regress_simple.olsx(ctx, x, y, 2)) == "userdata")
assert(type(a.regress_simple.olsy(ctx, x, y, 3)) == "userdata")
assert(type(a.regress_simple.ols(ctx, x, y)) == "userdata")
assert(type(a.regress_simple.zero(ctx)) == "userdata")
assert(type(ctx.eval(ctx, 1)) == "number")
assert(type(ctx.evar(ctx, 1)) == "number")
assert(type(ctx.ols_(ctx, x, y, 2, 3)) == "userdata")
assert(type(ctx.olsx(ctx, x, y, 2)) == "userdata")
assert(type(ctx.olsy(ctx, x, y, 3)) == "userdata")
assert(type(ctx.ols(ctx, x, y)) == "userdata")
assert(type(ctx.zero(ctx)) == "userdata")
assert(type(ctx:eval(1)) == "number")
assert(type(ctx:evar(1)) == "number")
assert(type(ctx:ols_(x, y, 2, 3)) == "userdata")
assert(type(ctx:olsx(x, y, 2)) == "userdata")
assert(type(ctx:olsy(x, y, 3)) == "userdata")
assert(type(ctx:ols(x, y)) == "userdata")
assert(type(ctx:zero()) == "userdata")
test.dir(ctx.coef)
test.dir(ctx.bias)
ctx.coef = 1
ctx.bias = 1
assert(type(ctx.coef) == "number")
assert(type(ctx.bias) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.regress_simple
---@field __name string
---@field __index table
---@field __newindex table
