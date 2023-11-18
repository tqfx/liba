#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
for i, v in pairs(arg) do
    if i == 1 then
        io.output(v)
        break
    end
end
test.dir(a)
test.log(a.rsqrt(1, 2, 4))
---@diagnostic disable-next-line: param-type-mismatch
assert(a:rsqrt(1))
