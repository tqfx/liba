#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.pid_neuro))
local ctx = a.pid_neuro.new()
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.pid_neuro.kpid(ctx, 4, 3, 2, 1)) == "userdata")
assert(type(a.pid_neuro.wpid(ctx, 3, 2, 1)) == "userdata")
assert(type(a.pid_neuro.run(ctx, 1, 0)) == "number")
assert(type(a.pid_neuro.inc(ctx, 1, 0)) == "number")
assert(type(a.pid_neuro.zero(ctx)) == "userdata")
ctx:kpid(4, 3, 2, 1):wpid(3, 2, 1):zero()
assert(type(ctx:run(1, 0)) == "number")
assert(type(ctx:inc(1, 0)) == "number")
assert(type(ctx.k) == "number")
assert(type(ctx.wp) == "number")
assert(type(ctx.wi) == "number")
assert(type(ctx.wd) == "number")
assert(type(ctx.kp) == "number")
assert(type(ctx.ki) == "number")
assert(type(ctx.kd) == "number")
assert(type(ctx.outmax) == "number")
assert(type(ctx.outmin) == "number")
assert(type(ctx.out) == "number")
assert(type(ctx.fdb) == "number")
assert(type(ctx.err) == "number")
assert(type(ctx.ec) == "number")
ctx.outmin = -10
ctx.outmax = 10
ctx.kp = 3
ctx.ki = 2
ctx.kd = 1
ctx.wp = 3
ctx.wi = 2
ctx.wd = 1
ctx.k = 0
ctx.__name = nil
assert(ctx.__name)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.pid_neuro
---@field __name string
---@field __index table
---@field __newindex table
