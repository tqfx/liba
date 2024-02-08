#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.trajtrap))
local ctx = a.trajtrap.new()
assert(ctx)
test.dir(getmetatable(ctx))
assert(a.trajtrap.gen(ctx, 2, 2, -2, 0, 4) > 0)
assert(type(a.trajtrap.pos(ctx, 0.5)) == "number")
assert(type(a.trajtrap.vel(ctx, 0.5)) == "number")
assert(type(a.trajtrap.acc(ctx, 0.5)) == "number")
assert(ctx.gen(ctx, 2, 2, -2, 0, 4) > 0)
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(ctx:gen(2, 2, -2, 0, 4) > 0)
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx.t) == "number")
assert(type(ctx.q0) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.v0) == "number")
assert(type(ctx.v1) == "number")
assert(type(ctx.vc) == "number")
assert(type(ctx.ta) == "number")
assert(type(ctx.td) == "number")
assert(type(ctx.qa) == "number")
assert(type(ctx.qd) == "number")
assert(type(ctx.ac) == "number")
assert(type(ctx.de) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.trajtrap
---@field __name string
---@field __index table
---@field __newindex table
