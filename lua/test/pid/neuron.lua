#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "../?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:dir(getmetatable(a.pid.neuron))
assert(a.pid.neuron.new())
assert(a.pid.neuron.new(-10, 10))
assert(a.pid.neuron.new(10, 0.1, 1, -10, 10))
ctx = a.pid.neuron.new(-10, 10)
assert(type(a.pid.neuron.kpid(ctx, 4, 3, 2, 1)) == "userdata")
assert(type(a.pid.neuron:kpid(ctx, 4, 3, 2, 1)) == "userdata")
assert(type(a.pid.neuron.wpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.neuron:wpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid.neuron.iter(ctx, 1, 0)) == "number")
assert(type(a.pid.neuron:iter(ctx, 1, 0)) == "number")
assert(type(a.pid.neuron.zero(ctx)) == "userdata")
assert(type(a.pid.neuron:zero(ctx)) == "userdata")
test:dir(getmetatable(ctx))
ctx = a.pid:neuron(-10, 10, 10)
ctx:kpid(4, 3, 2, 1):wpid(3, 2, 1)
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
assert(type(ctx.ec) == "number")
assert(type(ctx.wp) == "number")
assert(type(ctx.wi) == "number")
assert(type(ctx.wd) == "number")
assert(type(ctx.k) == "number")
assert(ctx.mode == a.pid.INC)
ctx.mode = a.pid.OFF
ctx.outmin = -10
ctx.outmax = 10
ctx.summax = 5
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
ctx.wp = 3
ctx.wi = 2
ctx.wd = 1
ctx.k = 0
