#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.regress_linear))

local x = { 0, 1, 2, 3, 4 }
local y = { 1, 2, 3, 4, 5 }

local ctx = a.regress_linear.new({ 1 })
test.dir(getmetatable(ctx))
assert(type(a.regress_linear.eval(ctx, { 1 })) == "number")
assert(type(a.regress_linear.err(ctx, x, y)) == "table")
assert(type(a.regress_linear.gd(ctx, { 0 }, 1, 0.1)) == "userdata")
assert(type(a.regress_linear.sgd(ctx, x, y, 0.1)) == "userdata")
assert(type(a.regress_linear.bgd(ctx, x, y, 0.1)) == "userdata")
assert(type(a.regress_linear.mgd(ctx, x, y, 1e-3, 1.0, 0.1)) == "number")
assert(type(a.regress_linear.zero(ctx)) == "userdata")
assert(type(ctx.eval(ctx, { 1 })) == "number")
assert(type(ctx.err(ctx, x, y)) == "table")
assert(type(ctx.gd(ctx, { 0 }, 1, 0.1)) == "userdata")
assert(type(ctx.sgd(ctx, x, y, 0.1)) == "userdata")
assert(type(ctx.bgd(ctx, x, y, 0.1)) == "userdata")
assert(type(ctx.mgd(ctx, x, y, 1e-3, 1.0, 0.1)) == "number")
assert(type(ctx.zero(ctx)) == "userdata")
assert(type(ctx:eval({ 1 })) == "number")
assert(type(ctx:err(x, y)) == "table")
assert(type(ctx:gd({ 0 }, 1, 0.1)) == "userdata")
assert(type(ctx:sgd(x, y, 0.1)) == "userdata")
assert(type(ctx:bgd(x, y, 0.1)) == "userdata")
assert(type(ctx:mgd(x, y, 1e-3, 1.0, 0.1)) == "number")
assert(type(ctx:zero()) == "userdata")
test.dir(ctx.coef)
test.dir(ctx.bias)
ctx.coef = { 1 }
ctx.bias = 1
assert(type(ctx.coef) == "table")
assert(type(ctx.bias) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.regress_linear
---@field __name string
---@field __index table
---@field __newindex table
