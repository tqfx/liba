#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.crc64))
local ctx = a.crc64.new('0x000000000000001B')
assert(ctx)
local ctx = a.crc64.new('0x42F0E1EBA9EA3693', true)
assert(ctx)
assert(type(ctx.table) == "table")
test.dir(getmetatable(ctx))
local text = "0123456789"
ctx:gen('0x000000000000001B')
assert(a.crc64.eval(ctx, text) == '0xE4FFBEA588AFC790')
assert(tonumber(a.crc64.eval(ctx, a.crc64.pack(ctx, text))) == 0)
ctx:gen('0x42F0E1EBA9EA3693', true)
assert(ctx:eval(text) == '0xDA60676A5CDE0008')
assert(tonumber(ctx:eval(ctx:pack(text))) == 0)
ctx.__name = nil
assert(ctx.__name)
ctx.__call = nil
assert(ctx.__call)
ctx.__index = nil
assert(ctx.__index)
ctx.__newindex = nil
assert(ctx.__newindex)
---@class a.crc64
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
