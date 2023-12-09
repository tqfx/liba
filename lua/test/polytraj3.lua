#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.polytraj3))
local ctx = a.polytraj3.new({ 0, 0, 0 }, { 1, 1, 1 })
assert(ctx)
local ctx = a.polytraj3.new(0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytraj3.pos(ctx, 0.5)) == "number")
assert(type(a.polytraj3.vel(ctx, 0.5)) == "number")
assert(type(a.polytraj3.acc(ctx, 0.5)) == "number")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx.q) == "table")
assert(type(ctx.v) == "table")
assert(type(ctx.a) == "table")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.polytraj3
---@field __name string
---@field __index table
---@field __newindex table
