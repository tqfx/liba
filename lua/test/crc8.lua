#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.crc8))
local ctx = a.crc8.new(0x07)
assert(ctx)
local ctx = a.crc8.new(0x31, true)
assert(ctx)
assert(type(ctx.table) == "table")
test.dir(getmetatable(ctx))
local text = "0123456789"
ctx:gen(0x07)
assert(a.crc8.eval(ctx, text) == 0x45)
assert(a.crc8.eval(ctx, a.crc8.pack(ctx, text)) == 0)
ctx:gen(0x31, true)
assert(ctx:eval(text) == 0x75)
assert(ctx:eval(ctx:pack(text)) == 0)
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.crc8
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
