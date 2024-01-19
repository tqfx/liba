#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(a.complex)
local x = a.complex.new(1, 2)
local y = a.complex.rect(2, 1)
local z = a.complex.polar(1, math.pi)
test.dir(getmetatable(z))
test.log(z:proj(), z:conj(), z.rho, z.theta)
z.real, z.imag = math.pi, math.pi
test.log("- " .. tostring(x) .. " = " .. tostring(-x))
test.log(tostring(x) .. " + " .. tostring(y) .. " = " .. tostring(x + y))
test.log(tostring(x) .. " - " .. tostring(y) .. " = " .. tostring(x - y))
test.log(tostring(x) .. " * " .. tostring(y) .. " = " .. tostring(x * y))
test.log(tostring(x) .. " / " .. tostring(y) .. " = " .. tostring(x / y))
test.log("- " .. tostring(x) .. " = " .. tostring(x:unm()))
test.log(tostring(x) .. " + " .. tostring(y) .. " = " .. tostring(x:add(y)))
test.log(tostring(x) .. " - " .. tostring(y) .. " = " .. tostring(x:sub(y)))
test.log(tostring(x) .. " * " .. tostring(y) .. " = " .. tostring(x:mul(y)))
test.log(tostring(x) .. " / " .. tostring(y) .. " = " .. tostring(x:div(y)))

assert(a.complex.exp(z))
assert(z:exp())
assert(a.complex.log(z))
assert(z:log())
assert(a.complex.sqrt(z))
assert(z:sqrt())
assert(a.complex.log2(z))
assert(z:log2())
assert(a.complex.log10(z))
assert(z:log10())
assert(a.complex.sin(z))
assert(z:sin())
assert(a.complex.cos(z))
assert(z:cos())
assert(a.complex.tan(z))
assert(z:tan())
assert(a.complex.sec(z))
assert(z:sec())
assert(a.complex.csc(z))
assert(z:csc())
assert(a.complex.cot(z))
assert(z:cot())
assert(a.complex.asin(z))
assert(z:asin())
assert(a.complex.acos(z))
assert(z:acos())
assert(a.complex.atan(z))
assert(z:atan())
assert(a.complex.asec(z))
assert(z:asec())
assert(a.complex.acsc(z))
assert(z:acsc())
assert(a.complex.acot(z))
assert(z:acot())
assert(a.complex.sinh(z))
assert(z:sinh())
assert(a.complex.cosh(z))
assert(z:cosh())
assert(a.complex.tanh(z))
assert(z:tanh())
assert(a.complex.sech(z))
assert(z:sech())
assert(a.complex.csch(z))
assert(z:csch())
assert(a.complex.coth(z))
assert(z:coth())
assert(a.complex.asinh(z))
assert(z:asinh())
assert(a.complex.acosh(z))
assert(z:acosh())
assert(a.complex.atanh(z))
assert(z:atanh())
assert(a.complex.asech(z))
assert(z:asech())
assert(a.complex.acsch(z))
assert(z:acsch())
assert(a.complex.acoth(z))
assert(z:acoth())
z.__unm = nil
assert(z.__unm)
z.__add = nil
assert(z.__add)
z.__sub = nil
assert(z.__sub)
z.__mul = nil
assert(z.__mul)
z.__div = nil
assert(z.__div)
z.__pow = nil
assert(z.__pow)
z.__len = nil
assert(z.__len)
z.__name = nil
assert(z.__name)
z.__index = nil
assert(z.__index)
z.__newindex = nil
assert(z.__newindex)
---@class a.complex
---@field __unm function
---@field __add function
---@field __sub function
---@field __mul function
---@field __div function
---@field __pow function
---@field __len function
---@field __name string
---@field __index table
---@field __newindex table
