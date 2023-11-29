#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")

test.log("polytraj3")
test.dir(getmetatable(a.polytraj3))
local ctx = a.polytraj3.new({ 0, 0, 0 }, { 1, 1, 1 })
assert(ctx)
local ctx = a.polytraj3.new(0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytraj3.out(ctx, 0.5)) == "table")
assert(type(a.polytraj3.pos(ctx, 0.5)) == "number")
assert(type(a.polytraj3.vel(ctx, 0.5)) == "number")
assert(type(a.polytraj3.acc(ctx, 0.5)) == "number")
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
---@class a.polytraj3
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table

test.log("polytraj5")
test.dir(getmetatable(a.polytraj5))
local ctx = a.polytraj5.new({ 0, 0, 0, 0 }, { 1, 1, 1, 1 })
assert(ctx)
local ctx = a.polytraj5.new(0, 1, 0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytraj5.out(ctx, 0.5)) == "table")
assert(type(a.polytraj5.pos(ctx, 0.5)) == "number")
assert(type(a.polytraj5.vel(ctx, 0.5)) == "number")
assert(type(a.polytraj5.acc(ctx, 0.5)) == "number")
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
---@class a.polytraj5
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table

test.log("polytraj7")
test.dir(getmetatable(a.polytraj7))
local ctx = a.polytraj7.new({ 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 })
assert(ctx)
local ctx = a.polytraj7.new(0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
assert(ctx)
test.dir(getmetatable(ctx))
assert(type(a.polytraj7.out(ctx, 0.5)) == "table")
assert(type(a.polytraj7.pos(ctx, 0.5)) == "number")
assert(type(a.polytraj7.vel(ctx, 0.5)) == "number")
assert(type(a.polytraj7.acc(ctx, 0.5)) == "number")
assert(type(a.polytraj7.jer(ctx, 0.5)) == "number")
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
---@class a.polytraj7
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
