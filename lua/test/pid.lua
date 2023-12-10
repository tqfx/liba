#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.pid))
local ctx = a.pid.new()
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.pid.kpid(ctx, 10, 0.1, 1)) == "userdata")
assert(type(a.pid.run(ctx, 1, 0)) == "number")
assert(type(a.pid.pos(ctx, 1, 0)) == "number")
assert(type(a.pid.inc(ctx, 1, 0)) == "number")
assert(type(a.pid.zero(ctx)) == "userdata")
ctx:kpid(3, 2, 1):zero()
assert(type(ctx:run(1, 0)) == "number")
assert(type(ctx:pos(1, 0)) == "number")
assert(type(ctx:inc(1, 0)) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.summax) == "number")
assert(type(ctx.summin) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
ctx.outmin = -10
ctx.outmax = 10
ctx.summin = -5
ctx.summax = 5
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.pid
---@field __name string
---@field __index table
---@field __newindex table
