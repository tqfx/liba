#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.pid))
assert(a.pid.new(1, -10, 10))
assert(a.pid.new(1, -10, 10, 10))
assert(a.pid.new(1, 10, 0.1, 1, -10, 10))
assert(a.pid.new(1, 10, 0.1, 1, -10, 10, 10))
ctx = a.pid.new(1, 10, 0.1, 1, -10, 10, 10)
assert(type(a.pid.kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid:kpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.iter(ctx, 1, 0)) == "number")
assert(type(a.pid:iter(ctx, 1, 0)) == "number")
assert(type(a.pid.zero(ctx)) == "userdata")
assert(type(a.pid:zero(ctx)) == "userdata")
assert(type(a.pid.pos(ctx, 10)) == "userdata")
assert(type(a.pid:pos(ctx, 10)) == "userdata")
assert(type(a.pid.inc(ctx)) == "userdata")
assert(type(a.pid:inc(ctx)) == "userdata")
assert(type(a.pid.off(ctx)) == "userdata")
assert(type(a.pid:off(ctx)) == "userdata")
test:r(getmetatable(ctx))
ctx = a:pid(1, 10, 0.1, 1, -10, 10, 10)
ctx:kpid(3, 2, 1):off():inc():pos(10)
assert(type(ctx(1, 0)) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.summax) == "number")
assert(type(ctx.dt) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
assert(ctx.mode == a.pid.POS)
ctx.mode = a.pid.OFF
ctx.outmin = -10
ctx.outmax = 10
ctx.summax = 5
ctx.dt = 0.1
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
