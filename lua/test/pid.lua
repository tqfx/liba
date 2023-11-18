#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.pid))
assert(a.pid.new())
assert(a.pid.new(-10, 10))
assert(a.pid.new(-10, 10, 10))
assert(a.pid.new(10, 0.1, 1, -10, 10))
assert(a.pid.new(10, 0.1, 1, -10, 10, 10))
local ctx = a.pid.new(10, 0.1, 1, -10, 10, 10)
assert(type(a.pid.kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.iter(ctx, 1, 0)) == "number")
assert(type(a.pid.zero(ctx)) == "userdata")
---@diagnostic disable: param-type-mismatch, redundant-parameter
assert(type(a.pid:kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid:iter(ctx, 1, 0)) == "number")
assert(type(a.pid:zero(ctx)) == "userdata")
---@diagnostic enable: param-type-mismatch, redundant-parameter
test.dir(getmetatable(ctx))
local ctx = a:pid(10, 0.1, 1, -10, 10, 10):kpid(3, 2, 1)
assert(type(ctx(1, 0)) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.summax) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
assert(ctx.mode == a.pid.POS)
ctx.mode = a.pid.OFF
ctx.outmin = -10
ctx.outmax = 10
ctx.summax = 5
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
