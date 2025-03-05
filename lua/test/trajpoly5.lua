#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.trajpoly5))
local ctx = a.trajpoly5.new(1, 0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.trajpoly5.pos(ctx, 0.5)) == "number")
assert(type(a.trajpoly5.vel(ctx, 0.5)) == "number")
assert(type(a.trajpoly5.acc(ctx, 0.5)) == "number")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx.c0) == "table")
assert(type(ctx.c1) == "table")
assert(type(ctx.c2) == "table")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.trajpoly5
---@field __name string
---@field __index table
---@field __newindex table
