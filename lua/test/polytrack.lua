#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")

test:w("polytrack3")
test:r(getmetatable(a.polytrack3))
ctx = a.polytrack3.new({ 0, 0, 0 }, { 1, 1, 1 })
ctx = a.polytrack3.new(0, 1, 0, 1, 0, 1)
assert(type(a.polytrack3.out(ctx, 0.5)) == "table")
assert(type(a.polytrack3:out(ctx, 0.5)) == "table")
assert(type(a.polytrack3.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack3:vel(ctx, 0.5)) == "number")
assert(type(a.polytrack3.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack3:acc(ctx, 0.5)) == "number")
ctx = a:polytrack3({ 0, 0, 0 }, { 1, 1, 1 })
ctx = a:polytrack3(0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")

test:w("polytrack5")
test:r(getmetatable(a.polytrack5))
ctx = a.polytrack5.new({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
ctx = a.polytrack5.new(0, 1, 0, 1, 0, 1, 0, 1)
assert(type(a.polytrack3.out(ctx, 0.5)) == "table")
assert(type(a.polytrack3:out(ctx, 0.5)) == "table")
assert(type(a.polytrack3.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack3:vel(ctx, 0.5)) == "number")
assert(type(a.polytrack3.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack3:acc(ctx, 0.5)) == "number")
ctx = a:polytrack5({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
ctx = a:polytrack5(0, 1, 0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")

test:w("polytrack7")
test:r(getmetatable(a.polytrack7))
ctx = a.polytrack7.new({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
ctx = a.polytrack7.new(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
assert(type(a.polytrack7.out(ctx, 0.5)) == "table")
assert(type(a.polytrack7:out(ctx, 0.5)) == "table")
assert(type(a.polytrack7.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack7:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack7.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack7:vel(ctx, 0.5)) == "number")
assert(type(a.polytrack7.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack7:acc(ctx, 0.5)) == "number")
assert(type(a.polytrack7.jer(ctx, 0.5)) == "number")
assert(type(a.polytrack7:jer(ctx, 0.5)) == "number")
ctx = a:polytrack7({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
ctx = a:polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vel(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx.jer(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vel(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx:jer(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")
