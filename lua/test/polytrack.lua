#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")

test.log("polytrack3")
test.dir(getmetatable(a.polytrack3))
local ctx = a.polytrack3.new({ 0, 0, 0 }, { 1, 1, 1 })
assert(ctx)
local ctx = a.polytrack3.new(0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytrack3.out(ctx, 0.5)) == "table")
assert(type(a.polytrack3.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack3.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack3.acc(ctx, 0.5)) == "number")
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
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.polytrack3
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table

test.log("polytrack5")
test.dir(getmetatable(a.polytrack5))
local ctx = a.polytrack5.new({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
assert(ctx)
local ctx = a.polytrack5.new(0, 1, 0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytrack5.out(ctx, 0.5)) == "table")
assert(type(a.polytrack5.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack5.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack5.acc(ctx, 0.5)) == "number")
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
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.polytrack5
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table

test.log("polytrack7")
test.dir(getmetatable(a.polytrack7))
local ctx = a.polytrack7.new({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
assert(ctx)
local ctx = a.polytrack7.new(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytrack7.out(ctx, 0.5)) == "table")
assert(type(a.polytrack7.pos(ctx, 0.5)) == "number")
assert(type(a.polytrack7.vel(ctx, 0.5)) == "number")
assert(type(a.polytrack7.acc(ctx, 0.5)) == "number")
assert(type(a.polytrack7.jer(ctx, 0.5)) == "number")
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
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.polytrack7
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
