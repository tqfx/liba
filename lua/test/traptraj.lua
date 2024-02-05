#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.traptraj))
local ctx = a.traptraj.new(10, 2, 2, -2, 0, 0)
assert(ctx)
local ctx = a.traptraj.new(10, 2, 2, -2)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.traptraj.pos(ctx, 0.5)) == "number")
assert(type(a.traptraj.vel(ctx, 0.5)) == "number")
assert(type(a.traptraj.acc(ctx, 0.5)) == "number")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx.ac) == "number")
assert(type(ctx.de) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.q2) == "number")
assert(type(ctx.t1) == "number")
assert(type(ctx.t2) == "number")
assert(type(ctx.vs) == "number")
assert(type(ctx.vc) == "number")
assert(type(ctx.ve) == "number")
assert(type(ctx.q) == "number")
assert(type(ctx.t) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.traptraj
---@field __name string
---@field __index table
---@field __newindex table
