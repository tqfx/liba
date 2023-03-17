#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.tf))

local num = { 6.59492796e-05, 6.54019884e-05 }
local den = { -1.97530991, 0.97530991 }

ctx = a.tf.new(num, den)
test:r(getmetatable(ctx))
assert(type(a.tf.proc(ctx, 1)) == "number")
assert(type(a.tf:proc(ctx, 1)) == "number")
assert(type(a.tf.zero(ctx)) == "userdata")
assert(type(a.tf:zero(ctx)) == "userdata")
ctx = a:tf(num, den)
assert(type(ctx.proc(ctx, 1)) == "number")
assert(type(ctx.zero(ctx)) == "userdata")
assert(type(ctx:proc(1)) == "number")
assert(type(ctx:zero()) == "userdata")
test:r(ctx.num)
test:r(ctx.den)
ctx.num = { 1, 2 }
assert(type(ctx.num) == "table")
ctx.den = { 3, 4 }
assert(type(ctx.den) == "table")
