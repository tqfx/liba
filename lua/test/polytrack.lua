#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")

test:p("polytrack3")
test:r(getmetatable(a.polytrack3))
ctx = a.polytrack3.new({ 0, 0, 0 }, { 1, 1, 1 })
ctx = a.polytrack3.new(0, 1, 0, 1, 0, 1)
assert(type(a.polytrack3.out(ctx, 0.5)) == "table")
assert(type(a.polytrack3:out(ctx, 0.5)) == "table")
assert(type(a.polytrack3.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3.vec(ctx, 0.5)) == "number")
assert(type(a.polytrack3:vec(ctx, 0.5)) == "number")
assert(type(a.polytrack3.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack3:acc(ctx, 0.5)) == "number")
ctx = a:polytrack3({ 0, 0, 0 }, { 1, 1, 1 })
ctx = a:polytrack3(0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vec(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vec(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")
assert(type(ctx.q) == "table")
assert(type(ctx.v) == "table")
assert(type(ctx.t0) == "number")
assert(type(ctx.q0) == "number")
assert(type(ctx.v0) == "number")
assert(type(ctx.t1) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.v1) == "number")
ctx.t = { 0, 1 }
ctx.q = { 0, 1 }
ctx.v = { 0, 1 }
ctx.t0 = 0
ctx.q0 = 0
ctx.v0 = 0
ctx.t1 = 1
ctx.q1 = 1
ctx.v1 = 1
ctx:gen()

test:p("polytrack5")
test:r(getmetatable(a.polytrack5))
ctx = a.polytrack5.new({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
ctx = a.polytrack5.new(0, 1, 0, 1, 0, 1, 0, 1)
assert(type(a.polytrack3.out(ctx, 0.5)) == "table")
assert(type(a.polytrack3:out(ctx, 0.5)) == "table")
assert(type(a.polytrack3.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3.vec(ctx, 0.5)) == "number")
assert(type(a.polytrack3:vec(ctx, 0.5)) == "number")
assert(type(a.polytrack3.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack3:acc(ctx, 0.5)) == "number")
ctx = a:polytrack5({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
ctx = a:polytrack5(0, 1, 0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vec(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vec(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")
assert(type(ctx.q) == "table")
assert(type(ctx.v) == "table")
assert(type(ctx.a) == "table")
assert(type(ctx.t0) == "number")
assert(type(ctx.q0) == "number")
assert(type(ctx.v0) == "number")
assert(type(ctx.a0) == "number")
assert(type(ctx.t1) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.v1) == "number")
assert(type(ctx.a1) == "number")
ctx.t = { 0, 1 }
ctx.q = { 0, 1 }
ctx.v = { 0, 1 }
ctx.a = { 0, 1 }
ctx.t0 = 0
ctx.q0 = 0
ctx.v0 = 0
ctx.a0 = 0
ctx.t1 = 1
ctx.q1 = 1
ctx.v1 = 1
ctx.a1 = 1
ctx:gen()

test:p("polytrack7")
test:r(getmetatable(a.polytrack7))
ctx = a.polytrack7.new({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
ctx = a.polytrack7.new(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
assert(type(a.polytrack7.out(ctx, 0.5)) == "table")
assert(type(a.polytrack7:out(ctx, 0.5)) == "table")
assert(type(a.polytrack7.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack7:pos(ctx, 0.5)) == "number")
assert(type(a.polytrack7.vec(ctx, 0.5)) == "number")
assert(type(a.polytrack7:vec(ctx, 0.5)) == "number")
assert(type(a.polytrack7.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack7:acc(ctx, 0.5)) == "number")
assert(type(a.polytrack7.jer(ctx, 0.5)) == "number")
assert(type(a.polytrack7:jer(ctx, 0.5)) == "number")
ctx = a:polytrack7({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
ctx = a:polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
test:r(getmetatable(ctx))
assert(type(ctx.out(ctx, 0.5)) == "table")
assert(type(ctx.pos(ctx, 0.5)) == "number")
assert(type(ctx.vec(ctx, 0.5)) == "number")
assert(type(ctx.acc(ctx, 0.5)) == "number")
assert(type(ctx.jer(ctx, 0.5)) == "number")
assert(type(ctx:out(0.5)) == "table")
assert(type(ctx:pos(0.5)) == "number")
assert(type(ctx:vec(0.5)) == "number")
assert(type(ctx:acc(0.5)) == "number")
assert(type(ctx:jer(0.5)) == "number")
assert(type(ctx(0.5)) == "table")
assert(type(ctx.k) == "table")
assert(type(ctx.q) == "table")
assert(type(ctx.v) == "table")
assert(type(ctx.a) == "table")
assert(type(ctx.j) == "table")
assert(type(ctx.t0) == "number")
assert(type(ctx.q0) == "number")
assert(type(ctx.v0) == "number")
assert(type(ctx.a0) == "number")
assert(type(ctx.j0) == "number")
assert(type(ctx.t1) == "number")
assert(type(ctx.q1) == "number")
assert(type(ctx.v1) == "number")
assert(type(ctx.a1) == "number")
assert(type(ctx.j1) == "number")
ctx.t = { 0, 1 }
ctx.q = { 0, 1 }
ctx.v = { 0, 1 }
ctx.a = { 0, 1 }
ctx.j = { 0, 1 }
ctx.t0 = 0
ctx.q0 = 0
ctx.v0 = 0
ctx.a0 = 0
ctx.j0 = 0
ctx.t1 = 1
ctx.q1 = 1
ctx.v1 = 1
ctx.a1 = 1
ctx.j1 = 1
ctx:gen()
