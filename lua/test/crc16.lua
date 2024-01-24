#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.crc16))
local ctx = a.crc16.new(0x1021)
assert(ctx)
local ctx = a.crc16.new(0x8005, true)
assert(ctx)
assert(type(ctx.table) == "table")
test.dir(getmetatable(ctx))
local text = "0123456789"
ctx:gen(0x1021)
assert(a.crc16.eval(ctx, text) == 0x9C58)
assert(a.crc16.eval(ctx, a.crc16.pack(ctx, text)) == 0)
ctx:gen(0x8005, true)
assert(ctx:eval(text) == 0x443D)
assert(ctx:eval(ctx:pack(text)) == 0)
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.crc16
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
