#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.trajbell))
local ctx = a.trajbell.new()
assert(ctx)
test.dir(getmetatable(ctx))
assert(a.trajbell.gen(ctx, 3, 2, 3, 0, 10) > 0)
assert(type(a.trajbell.pos(ctx, 0.5)) == "number")
assert(type(a.trajbell.vel(ctx, 0.5)) == "number")
assert(type(a.trajbell.acc(ctx, 0.5)) == "number")
assert(type(a.trajbell.jer(ctx, 0.5)) == "number")
assert(ctx.gen(ctx, 3, 2, 3, 0, 10) > 0)
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx.jer(ctx, 0.5)) == "number")
assert(ctx:gen(3, 2, 3, 0, 10) > 0)
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx:jer(0.5)) == "number")
assert(type(ctx.t) == "number")
assert(type(ctx.tv) == "number")
assert(type(ctx.ta) == "number")
assert(type(ctx.td) == "number")
assert(type(ctx.taj) == "number")
assert(type(ctx.tdj) == "number")
assert(type(ctx.q0) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.v0) == "number")
assert(type(ctx.v1) == "number")
assert(type(ctx.vm) == "number")
assert(type(ctx.jm) == "number")
assert(type(ctx.am) == "number")
assert(type(ctx.dm) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.trajbell
---@field __name string
---@field __index table
---@field __newindex table
