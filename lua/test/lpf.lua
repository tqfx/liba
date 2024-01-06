#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.lpf))
local ctx = a.lpf.new(0.1)
assert(ctx)
local ctx = a.lpf.new(10, 0.01)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.lpf.gen(ctx, 10, 0.01)) == "userdata")
assert(type(a.lpf.gen(ctx, 0.1)) == "userdata")
assert(type(a.lpf.iter(ctx, 1)) == "number")
assert(type(a.lpf.zero(ctx)) == "userdata")
assert(type(ctx.gen(ctx, 10, 0.01)) == "userdata")
assert(type(ctx.gen(ctx, 0.1)) == "userdata")
assert(type(ctx.iter(ctx, 1)) == "number")
assert(type(ctx.zero(ctx)) == "userdata")
assert(type(ctx:gen(10, 0.01)) == "userdata")
assert(type(ctx:gen(0.1)) == "userdata")
assert(type(ctx:iter(1)) == "number")
assert(type(ctx:zero()) == "userdata")
assert(type(ctx.alpha) == "number")
assert(type(ctx.output) == "number")
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.lpf
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
