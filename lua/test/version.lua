#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.version))
local v000 = a.version.new()
local v100 = a.version.new(1)
local v010 = a.version.new(0, 1)
local v001 = a.version.new(0, 0, 1)
local vctx = a.version.new(a.VERSION)
assert(type(vctx.major) == "number")
assert(type(vctx.minor) == "number")
assert(type(vctx.third) == "number")
assert(type(vctx.extra) == "number")
assert(a.version.eq(v000, v000))
assert(a.version.ne(v000, v010))
assert(a.version.lt(v000, v010))
assert(not a.version.lt(v000, v000))
assert(a.version.gt(v010, v000))
assert(not a.version.gt(v000, v000))
assert(a.version.le(v000, v010))
assert(not a.version.le(v010, v000))
assert(a.version.ge(v010, v000))
assert(not a.version.ge(v000, v010))
assert(a.version.cmp(v000, v100) < 0)
assert(a.version.cmp(v000, v010) < 0)
assert(a.version.cmp(v000, v001) < 0)
assert(a.version.cmp(v100, v000) > 0)
assert(a.version.cmp(v010, v000) > 0)
assert(a.version.cmp(v001, v000) > 0)
assert(a.version.cmp(v000, v000) == 0)
assert(v000 == v000)
assert(v000 ~= v010)
assert(v000 < v010)
assert(not (v000 < v000))
assert(v010 > v000)
assert(not (v000 > v000))
assert(v000 <= v010)
assert(not (v010 <= v000))
assert(v010 >= v010)
assert(not (v000 >= v010))
test.dir(vctx.__index)
vctx.__lt = nil
assert(vctx.__lt)
vctx.__le = nil
assert(vctx.__le)
vctx.__eq = nil
assert(vctx.__eq)
vctx.__name = nil
assert(vctx.__name)
vctx.__call = nil
assert(vctx.__call)
vctx.__index = nil
assert(vctx.__index)
vctx.__newindex = nil
assert(vctx.__newindex)
vctx.__tostring = nil
assert(vctx.__tostring)
test.log("version", a.VERSION)
test.log("major", a.version.MAJOR)
test.log("minor", a.version.MINOR)
test.log("patch", a.version.PATCH)
test.log("tweak", a.version.TWEAK)
test.log(vctx(), "0.0.0", a.version.check())
---@class a.version
---@field __lt function
---@field __le function
---@field __eq function
---@field __name string
---@field __call function
---@field __index table
---@field __newindex table
---@field __tostring function
