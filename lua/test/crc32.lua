#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.crc32))
local ctx = a.crc32.new("0x1EDC6F41")
assert(ctx)
local ctx = a.crc32.new("0x04C11DB7", true)
assert(ctx)
assert(type(ctx.table) == "table")
test.dir(getmetatable(ctx))
local text = "0123456789"
ctx:gen("0x1EDC6F41")
assert(a.crc32.eval(ctx, text) == "0x512B456E")
assert(tonumber(a.crc32.eval(ctx, a.crc32.pack(ctx, text))) == 0)
ctx:gen("0x04C11DB7", true)
assert(ctx:eval(text) == "0x450EAFB0")
assert(tonumber(ctx:eval(ctx:pack(text))) == 0)
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.crc32
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
